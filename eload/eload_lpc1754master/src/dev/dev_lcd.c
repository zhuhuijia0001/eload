
#include <rthw.h>
#include <rtthread.h>
#include "lpc17xx_pinsel.h"
#include "lpc17xx_uart.h"

#include "PinDefine.h"
#include "dev_lcd.h"

#define LCD_UART_BAUDRATE   115200ul
#define LPC_LCD_UART		LPC_UART0
#define LCD_UART_IRQn		UART0_IRQn

struct dev_lcd
{
	struct rt_device parent;
};

static struct dev_lcd  s_dev_lcd;

static void uart0_init(rt_uint32_t baudrate)
{
	PINSEL_CFG_Type PinSelCfgType;

	UART_CFG_Type UartCfgType;

	UART_FIFO_CFG_Type UartFIFOCfgType;

	//pin config
	//TXD
	PinSelCfgType.Portnum = PINSEL_PORT_0;
	PinSelCfgType.Pinnum  = PINSEL_PIN_2;
	PinSelCfgType.Funcnum = PINSEL_FUNC_1;
	PinSelCfgType.Pinmode = PINSEL_PINMODE_PULLUP;
	PinSelCfgType.OpenDrain = PINSEL_PINMODE_NORMAL;
	PINSEL_ConfigPin(&PinSelCfgType);

	//RXD
	PinSelCfgType.Portnum = PINSEL_PORT_0;
	PinSelCfgType.Pinnum  = PINSEL_PIN_3;
	PinSelCfgType.Funcnum = PINSEL_FUNC_1;
	PinSelCfgType.Pinmode = PINSEL_PINMODE_TRISTATE;
	PinSelCfgType.OpenDrain = PINSEL_PINMODE_NORMAL;
	PINSEL_ConfigPin(&PinSelCfgType);

	//init
	UartCfgType.Baud_rate = baudrate;
	UartCfgType.Parity    = UART_PARITY_NONE;
	UartCfgType.Databits  = UART_DATABIT_8;
	UartCfgType.Stopbits  = UART_STOPBIT_1;
	UART_Init(LPC_LCD_UART, &UartCfgType);

	//FIFO
	UartFIFOCfgType.FIFO_ResetRxBuf = ENABLE;
	UartFIFOCfgType.FIFO_ResetTxBuf = ENABLE;
	UartFIFOCfgType.FIFO_DMAMode    = DISABLE;
	UartFIFOCfgType.FIFO_Level      = UART_FIFO_TRGLEV0;
	UART_FIFOConfig(LPC_LCD_UART, &UartFIFOCfgType);

	//int
	UART_IntConfig(LPC_LCD_UART, UART_INTCFG_RBR, DISABLE);

	//enable
	UART_TxCmd(LPC_LCD_UART, ENABLE);
}

static void lcd_gpio_init(void)
{
	SET_GPIO_INPUT(PIN_LCD_BUSY);
}

static rt_err_t rt_dev_lcd_init (rt_device_t dev)
{
	uart0_init(LCD_UART_BAUDRATE);

	lcd_gpio_init();
	
	return RT_EOK;
}

static rt_err_t rt_dev_lcd_open(rt_device_t dev, rt_uint16_t oflag)
{
	RT_ASSERT(dev != RT_NULL);
	if (dev->flag & RT_DEVICE_FLAG_INT_RX)
	{
		/* Enable the UART Interrupt */
		NVIC_EnableIRQ(LCD_UART_IRQn);
	}

	return RT_EOK;
}

static rt_err_t rt_dev_lcd_close(rt_device_t dev)
{
	RT_ASSERT(dev != RT_NULL);
	if (dev->flag & RT_DEVICE_FLAG_INT_RX)
	{
		/* Disable the UART Interrupt */
		NVIC_DisableIRQ(LCD_UART_IRQn);
	}

	return RT_EOK;
}

static rt_size_t rt_dev_lcd_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
	return 0;
}

static rt_size_t rt_dev_lcd_write(rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
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
				while ( !(LPC_LCD_UART->LSR & UART_LSR_THRE) );
				/* write data */
				LPC_LCD_UART->THR = '\r';
			}

			/* THRE status, contain valid data */
			while ( !(LPC_LCD_UART->LSR & UART_LSR_THRE) );	
			/* write data */
			LPC_LCD_UART->THR = *ptr;
			
			ptr ++;
			size --;
		}
	}
	else
	{
		while ( size != 0 )
		{
			/* THRE status, contain valid data */
			while ( !(LPC_LCD_UART->LSR & UART_LSR_THRE) );
	
			/* write data */
			LPC_LCD_UART->THR = *ptr;
	
			ptr++;
			size--;
		}
	}

	return (rt_size_t) ptr - (rt_size_t) buffer;
}

static rt_err_t rt_dev_lcd_control(rt_device_t dev, rt_uint8_t cmd, void *args)
{	
	switch (cmd)
	{
	case CMD_LCD_QUERY_BUSY:
		*(int *)args =  GET_GPIO_BIT(PIN_LCD_BUSY);
		
	break;
		
	default:
		goto ERROR;
	}
	
	return RT_EOK;
	
ERROR:
	return RT_ERROR;
}

void dev_lcd_init(void)
{
	struct dev_lcd *lcd;

	/* get uart device */
	lcd = &s_dev_lcd;

	/* device initialization */
	lcd->parent.type = RT_Device_Class_Char;

	/* device interface */
	lcd->parent.init 	   = rt_dev_lcd_init;
	lcd->parent.open 	   = rt_dev_lcd_open;
	lcd->parent.close      = rt_dev_lcd_close;
	lcd->parent.read 	   = rt_dev_lcd_read;
	lcd->parent.write      = rt_dev_lcd_write;
	lcd->parent.control    = rt_dev_lcd_control;
	lcd->parent.user_data  = RT_NULL;

	rt_device_register(&lcd->parent,
		"uart0", RT_DEVICE_FLAG_WRONLY /*| RT_DEVICE_FLAG_STREAM | RT_DEVICE_FLAG_INT_RX*/);
}
