
#include <rthw.h>
#include <rtthread.h>
#include "lpc17xx_pinsel.h"
#include "lpc17xx_uart.h"

#include "PinDefine.h"

#include "dev_uart.h"

#define DEV_UART_BAUDRATE     115200ul
#define LPC_DEV_UART		  LPC_UART3
#define DEV_UART_IRQn		  UART3_IRQn

struct dev_uart
{
	struct rt_device parent;
	
	/* buffer for reception */
	rt_uint8_t read_index, save_index;
	rt_uint8_t rx_buffer[RT_UART_RX_BUFFER_SIZE];
};

static struct dev_uart  s_dev_uart;

static void uart3_isr(void)
{
	rt_ubase_t level, iir;
    struct dev_uart* uart = &s_dev_uart;

    /* read IIR and clear it */
	iir = UART_GetIntId(LPC_DEV_UART);
	iir &= UART_IIR_INTID_MASK;

	if ((iir == UART_IIR_INTID_RDA) || (iir == UART_IIR_INTID_CTI))
	{
		/* Receive Data Available */
		while (LPC_DEV_UART->LSR & UART_LSR_RDR)
		{
			uart->rx_buffer[uart->save_index] = UART_ReceiveByte(LPC_DEV_UART);

			level = rt_hw_interrupt_disable();
			uart->save_index ++;
			if (uart->save_index >= RT_UART_RX_BUFFER_SIZE)
				uart->save_index = 0;
			rt_hw_interrupt_enable(level);
		}

		/* invoke callback */
		if(uart->parent.rx_indicate != RT_NULL)
		{
		    rt_size_t length;
		    if (uart->read_index > uart->save_index)
                length = RT_UART_RX_BUFFER_SIZE - uart->read_index + uart->save_index;
            else
                length = uart->save_index - uart->read_index;

            uart->parent.rx_indicate(&uart->parent, length);
		}
	}	
}

void UART3_IRQHandler(void)
{
	rt_interrupt_enter();
	
	uart3_isr();
	
	rt_interrupt_leave();
}

static void uart3_init(rt_uint32_t baudrate)
{
	PINSEL_CFG_Type PinSelCfgType;

	UART_CFG_Type UartCfgType;

	UART_FIFO_CFG_Type UartFIFOCfgType;

	//pin config
	//TXD
	PinSelCfgType.Portnum = PINSEL_PORT_0;
	PinSelCfgType.Pinnum  = PINSEL_PIN_0;
	PinSelCfgType.Funcnum = PINSEL_FUNC_2;
	PinSelCfgType.Pinmode = PINSEL_PINMODE_PULLUP;
	PinSelCfgType.OpenDrain = PINSEL_PINMODE_NORMAL;
	PINSEL_ConfigPin(&PinSelCfgType);

	//RXD
	PinSelCfgType.Portnum = PINSEL_PORT_0;
	PinSelCfgType.Pinnum  = PINSEL_PIN_1;
	PinSelCfgType.Funcnum = PINSEL_FUNC_2;
	PinSelCfgType.Pinmode = PINSEL_PINMODE_TRISTATE;
	PinSelCfgType.OpenDrain = PINSEL_PINMODE_NORMAL;
	PINSEL_ConfigPin(&PinSelCfgType);

	//init
	UartCfgType.Baud_rate = baudrate;
	UartCfgType.Parity    = UART_PARITY_NONE;
	UartCfgType.Databits  = UART_DATABIT_8;
	UartCfgType.Stopbits  = UART_STOPBIT_1;
	UART_Init(LPC_DEV_UART, &UartCfgType);

	//FIFO
	UartFIFOCfgType.FIFO_ResetRxBuf = ENABLE;
	UartFIFOCfgType.FIFO_ResetTxBuf = ENABLE;
	UartFIFOCfgType.FIFO_DMAMode    = DISABLE;
	UartFIFOCfgType.FIFO_Level      = UART_FIFO_TRGLEV2;
	UART_FIFOConfig(LPC_DEV_UART, &UartFIFOCfgType);

	//int
	UART_IntConfig(LPC_DEV_UART, UART_INTCFG_RBR, ENABLE);

	//enable
	UART_TxCmd(LPC_DEV_UART, ENABLE);
}

static rt_err_t rt_dev_uart_init (rt_device_t dev)
{
	uart3_init(DEV_UART_BAUDRATE);

	return RT_EOK;
}

static rt_err_t rt_dev_uart_open(rt_device_t dev, rt_uint16_t oflag)
{
	RT_ASSERT(dev != RT_NULL);
	if (dev->flag & RT_DEVICE_FLAG_INT_RX)
	{
		/* Enable the UART Interrupt */
		NVIC_EnableIRQ(DEV_UART_IRQn);
	}

	return RT_EOK;
}

static rt_err_t rt_dev_uart_close(rt_device_t dev)
{
	RT_ASSERT(dev != RT_NULL);
	if (dev->flag & RT_DEVICE_FLAG_INT_RX)
	{
		/* Disable the UART Interrupt */
		NVIC_DisableIRQ(DEV_UART_IRQn);
	}

	return RT_EOK;
}

static rt_size_t rt_dev_uart_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
	rt_uint8_t* ptr;
	struct dev_uart *uart = (struct dev_uart*)dev;
	RT_ASSERT(uart != RT_NULL);

	/* point to buffer */
	ptr = (rt_uint8_t*) buffer;
	if (dev->flag & RT_DEVICE_FLAG_INT_RX)
	{
		while (size)
		{
			/* interrupt receive */
			rt_base_t level;

			/* disable interrupt */
			level = rt_hw_interrupt_disable();
			if (uart->read_index != uart->save_index)
			{
				*ptr = uart->rx_buffer[uart->read_index];

				uart->read_index ++;
				if (uart->read_index >= RT_UART_RX_BUFFER_SIZE)
					uart->read_index = 0;
			}
			else
			{
				/* no data in rx buffer */

				/* enable interrupt */
				rt_hw_interrupt_enable(level);
				break;
			}

			/* enable interrupt */
			rt_hw_interrupt_enable(level);

			ptr ++;
			size --;
		}

		return (rt_uint32_t)ptr - (rt_uint32_t)buffer;
	}

	return 0;
}

static rt_size_t rt_dev_uart_write(rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{
	char *ptr;
	ptr = (char*)buffer;

	if (dev->flag & RT_DEVICE_FLAG_STREAM)
	{
		/* stream mode */
		while (size)
		{
			if (*ptr == '\n')
			{
				/* THRE status, contain valid data */
				while ( !(LPC_DEV_UART->LSR & UART_LSR_THRE) );
				/* write data */
				LPC_DEV_UART->THR = '\r';
			}

			/* THRE status, contain valid data */
			while ( !(LPC_DEV_UART->LSR & UART_LSR_THRE) );	
			/* write data */
			LPC_DEV_UART->THR = *ptr;
			
			ptr ++;
			size --;
		}
	}
	else
	{
		while ( size != 0 )
		{
			/* THRE status, contain valid data */
			while ( !(LPC_DEV_UART->LSR & UART_LSR_THRE) );

			/* write data */
			LPC_DEV_UART->THR = *ptr;
	
			ptr++;
			size--;
		}
	}

	return (rt_size_t) ptr - (rt_size_t) buffer;
}

static rt_err_t rt_dev_uart_control(rt_device_t dev, rt_uint8_t cmd, void *args)
{
	struct dev_uart *uart = (struct dev_uart*)dev;
	RT_ASSERT(uart != RT_NULL);
	
	switch (cmd)
	{
	case CMD_DEV_UART_RESET_FIFO:
		uart->read_index = uart->save_index = 0;
		
		break;
		
	default:
		goto ERROR;
	}
		
	return RT_EOK;
	
ERROR:
	return RT_ERROR;
}

void dev_uart_init(void)
{
	struct dev_uart* uart;

	/* get uart device */
	uart = &s_dev_uart;

	/* device initialization */
	uart->parent.type = RT_Device_Class_Char;
	rt_memset(uart->rx_buffer, 0, sizeof(uart->rx_buffer));
	uart->read_index = uart->save_index = 0;
	
	/* device interface */
	uart->parent.init 	    = rt_dev_uart_init;
	uart->parent.open 	    = rt_dev_uart_open;
	uart->parent.close      = rt_dev_uart_close;
	uart->parent.read 	    = rt_dev_uart_read;
	uart->parent.write      = rt_dev_uart_write;
	uart->parent.control    = rt_dev_uart_control;
	uart->parent.user_data  = RT_NULL;

	rt_device_register(&uart->parent,
		"uart3", RT_DEVICE_FLAG_RDWR | /*RT_DEVICE_FLAG_STREAM |*/ RT_DEVICE_FLAG_INT_RX);
}
