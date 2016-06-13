
#include <rthw.h>
#include <rtthread.h>
#include "lpc17xx_pinsel.h"
#include "lpc17xx_uart.h"

#include "PinDefine.h"

#include "slave_port_define.h"

#include "dev_slave_uart.h"

#define SLAVE_UART_BAUDRATE   115200ul
#define LPC_SLAVE_UART		  LPC_UART3
#define SLAVE_UART_IRQn		  UART3_IRQn

/* irq priority */
#define  UART3_IRQ_PRIORITY            5

struct dev_slave_uart
{
	struct rt_device parent;
	
	/* buffer for reception */
	rt_uint8_t read_index, save_index;
	rt_uint8_t rx_buffer[RT_UART_RX_BUFFER_SIZE];
};

static struct dev_slave_uart  s_dev_slave_uart;

static void uart3_isr(void)
{
	rt_ubase_t level, iir;
    struct dev_slave_uart* uart = &s_dev_slave_uart;

    /* read IIR and clear it */
	iir = UART_GetIntId(LPC_SLAVE_UART);
	iir &= UART_IIR_INTID_MASK;

	if ((iir == UART_IIR_INTID_RDA) || (iir == UART_IIR_INTID_CTI))
	{
		/* Receive Data Available */
        uart->rx_buffer[uart->save_index] = UART_ReceiveByte(LPC_SLAVE_UART);

        level = rt_hw_interrupt_disable();
		uart->save_index ++;
        if (uart->save_index >= RT_UART_RX_BUFFER_SIZE)
            uart->save_index = 0;
        rt_hw_interrupt_enable(level);

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
	UART_Init(LPC_SLAVE_UART, &UartCfgType);

	//FIFO
	UartFIFOCfgType.FIFO_ResetRxBuf = ENABLE;
	UartFIFOCfgType.FIFO_ResetTxBuf = ENABLE;
	UartFIFOCfgType.FIFO_DMAMode    = DISABLE;
	UartFIFOCfgType.FIFO_Level      = UART_FIFO_TRGLEV2;
	UART_FIFOConfig(LPC_SLAVE_UART, &UartFIFOCfgType);

	//int
	UART_IntConfig(LPC_SLAVE_UART, UART_INTCFG_RBR, ENABLE);

	NVIC_SetPriority(UART3_IRQn, UART3_IRQ_PRIORITY);
	
	//enable
	UART_TxCmd(LPC_SLAVE_UART, ENABLE);
}

static void select_gpio_init(void)
{
	SET_GPIO_OUTPUT(PIN_4051_EN);
	SET_GPIO_BIT(PIN_4051_EN);
	
	SET_GPIO_OUTPUT(PIN_H0_S1);
	CLR_GPIO_BIT(PIN_H0_S1);
	
	SET_GPIO_OUTPUT(PIN_H0_S2);
	CLR_GPIO_BIT(PIN_H0_S2);
	
	SET_GPIO_OUTPUT(PIN_H0_S3);
	CLR_GPIO_BIT(PIN_H0_S3);
}

static rt_err_t rt_dev_slave_uart_init (rt_device_t dev)
{
	uart3_init(SLAVE_UART_BAUDRATE);

	select_gpio_init();
	
	return RT_EOK;
}

static rt_err_t rt_dev_slave_uart_open(rt_device_t dev, rt_uint16_t oflag)
{
	RT_ASSERT(dev != RT_NULL);
	if (dev->flag & RT_DEVICE_FLAG_INT_RX)
	{
		/* Enable the UART Interrupt */
		NVIC_EnableIRQ(SLAVE_UART_IRQn);
	}

	return RT_EOK;
}

static rt_err_t rt_dev_slave_uart_close(rt_device_t dev)
{
	RT_ASSERT(dev != RT_NULL);
	if (dev->flag & RT_DEVICE_FLAG_INT_RX)
	{
		/* Disable the UART Interrupt */
		NVIC_DisableIRQ(SLAVE_UART_IRQn);
	}

	return RT_EOK;
}

static rt_size_t rt_dev_slave_uart_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
	rt_uint8_t* ptr;
	struct dev_slave_uart *uart = (struct dev_slave_uart*)dev;
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

static rt_size_t rt_dev_slave_uart_write(rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
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
				while ( !(LPC_SLAVE_UART->LSR & UART_LSR_THRE) );
				/* write data */
				LPC_SLAVE_UART->THR = '\r';
			}

			/* THRE status, contain valid data */
			while ( !(LPC_SLAVE_UART->LSR & UART_LSR_THRE) );	
			/* write data */
			LPC_SLAVE_UART->THR = *ptr;
			
			ptr ++;
			size --;
		}
	}
	else
	{
		while ( size != 0 )
		{
			/* THRE status, contain valid data */
			while ( !(LPC_SLAVE_UART->LSR & UART_LSR_THRE) );

			/* write data */
			LPC_SLAVE_UART->THR = *ptr;
	
			ptr++;
			size--;
		}
	}

	return (rt_size_t) ptr - (rt_size_t) buffer;
}

static void switch_to_channel_0(void)
{
	SET_GPIO_BIT(PIN_4051_EN);
	
	CLR_GPIO_BIT(PIN_H0_S1);
	CLR_GPIO_BIT(PIN_H0_S2);
	CLR_GPIO_BIT(PIN_H0_S3);
	
	CLR_GPIO_BIT(PIN_4051_EN);
}

static void switch_to_channel_1(void)
{
	SET_GPIO_BIT(PIN_4051_EN);
	
	SET_GPIO_BIT(PIN_H0_S1);
	CLR_GPIO_BIT(PIN_H0_S2);
	CLR_GPIO_BIT(PIN_H0_S3);
	
	CLR_GPIO_BIT(PIN_4051_EN);
}

static void switch_to_channel_2(void)
{
	SET_GPIO_BIT(PIN_4051_EN);
	
	CLR_GPIO_BIT(PIN_H0_S1);
	SET_GPIO_BIT(PIN_H0_S2);
	CLR_GPIO_BIT(PIN_H0_S3);
	
	CLR_GPIO_BIT(PIN_4051_EN);
}

static void switch_to_channel_3(void)
{
	SET_GPIO_BIT(PIN_4051_EN);
	
	SET_GPIO_BIT(PIN_H0_S1);
	SET_GPIO_BIT(PIN_H0_S2);
	CLR_GPIO_BIT(PIN_H0_S3);
	
	CLR_GPIO_BIT(PIN_4051_EN);
}

static void switch_to_channel_4(void)
{
	SET_GPIO_BIT(PIN_4051_EN);
	
	CLR_GPIO_BIT(PIN_H0_S1);
	CLR_GPIO_BIT(PIN_H0_S2);
	SET_GPIO_BIT(PIN_H0_S3);
	
	CLR_GPIO_BIT(PIN_4051_EN);
}

static void switch_to_channel_5(void)
{
	SET_GPIO_BIT(PIN_4051_EN);
	
	SET_GPIO_BIT(PIN_H0_S1);
	CLR_GPIO_BIT(PIN_H0_S2);
	SET_GPIO_BIT(PIN_H0_S3);
	
	CLR_GPIO_BIT(PIN_4051_EN);
}

static void switch_to_channel_6(void)
{
	SET_GPIO_BIT(PIN_4051_EN);
	
	CLR_GPIO_BIT(PIN_H0_S1);
	SET_GPIO_BIT(PIN_H0_S2);
	SET_GPIO_BIT(PIN_H0_S3);
	
	CLR_GPIO_BIT(PIN_4051_EN);
}

static void switch_to_channel_7(void)
{
	SET_GPIO_BIT(PIN_4051_EN);
	
	SET_GPIO_BIT(PIN_H0_S1);
	SET_GPIO_BIT(PIN_H0_S2);
	SET_GPIO_BIT(PIN_H0_S3);
	
	CLR_GPIO_BIT(PIN_4051_EN);
}

static void (*const s_switch_fun_arr[])(void) = 
{
	[0] = switch_to_channel_0,
	
	[1] = switch_to_channel_1,
	
	[2] = switch_to_channel_2,
	
	[3] = switch_to_channel_3,
	
	[4] = switch_to_channel_4,
	
	[5] = switch_to_channel_5,
	
	[6] = switch_to_channel_6,
	
	[7] = switch_to_channel_7
};

static rt_err_t rt_dev_slave_uart_control(rt_device_t dev, rt_uint8_t cmd, void *args)
{
	struct dev_slave_uart *uart = (struct dev_slave_uart*)dev;
	RT_ASSERT(uart != RT_NULL);
	
	switch (cmd)
	{
	case CMD_SLAVE_UART_RESET_FIFO:
		uart->read_index = uart->save_index = 0;
		
		break;
		
	case CMD_SLAVE_UART_SWITCH_CHANNEL:
		{
			slave_com_port port = *(slave_com_port *)args;
			if (port < SLAVE_PORT_COUNT)
			{
				s_switch_fun_arr[port]();
			}
		}
				
		break;
		
	default:
		goto ERROR;
	}
		
	return RT_EOK;
	
ERROR:
	return RT_ERROR;
}

void dev_slave_uart_init(void)
{
	struct dev_slave_uart* uart;

	/* get uart device */
	uart = &s_dev_slave_uart;

	/* device initialization */
	uart->parent.type = RT_Device_Class_Char;
	rt_memset(uart->rx_buffer, 0, sizeof(uart->rx_buffer));
	uart->read_index = uart->save_index = 0;
	
	/* device interface */
	uart->parent.init 	    = rt_dev_slave_uart_init;
	uart->parent.open 	    = rt_dev_slave_uart_open;
	uart->parent.close      = rt_dev_slave_uart_close;
	uart->parent.read 	    = rt_dev_slave_uart_read;
	uart->parent.write      = rt_dev_slave_uart_write;
	uart->parent.control    = rt_dev_slave_uart_control;
	uart->parent.user_data  = RT_NULL;

	rt_device_register(&uart->parent,
		"uart3", RT_DEVICE_FLAG_WRONLY | /*RT_DEVICE_FLAG_STREAM |*/ RT_DEVICE_FLAG_INT_RX);
}
