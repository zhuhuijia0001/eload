#include <rthw.h>
#include <rtthread.h>

#include "Pindefine.h"

#include "led_define.h"
#include "dev_led.h"

struct dev_led
{
	struct rt_device parent;
};

static struct dev_led s_dev_led;

static void ch1_pass_led_on(void)
{
	CLR_GPIO_BIT(PIN_CH1_PASS_LED);
}

static void ch2_pass_led_on(void)
{
	CLR_GPIO_BIT(PIN_CH2_PASS_LED);
}

static void ch3_pass_led_on(void)
{
	CLR_GPIO_BIT(PIN_CH3_PASS_LED);
}

static void ch4_pass_led_on(void)
{
	CLR_GPIO_BIT(PIN_CH4_PASS_LED);
}

static void ch5_pass_led_on(void)
{
	CLR_GPIO_BIT(PIN_CH5_PASS_LED);
}

static void ch6_pass_led_on(void)
{
	CLR_GPIO_BIT(PIN_CH6_PASS_LED);
}

static void ch7_pass_led_on(void)
{
	CLR_GPIO_BIT(PIN_CH7_PASS_LED);
}

static void ch8_pass_led_on(void)
{
	CLR_GPIO_BIT(PIN_CH8_PASS_LED);
}

static void (*const s_pass_led_on_func[])(void) = 
{
	[CH1_LED] = ch1_pass_led_on,
	
	[CH2_LED] = ch2_pass_led_on,

	[CH3_LED] = ch3_pass_led_on,
	
	[CH4_LED] = ch4_pass_led_on,
	
	[CH5_LED] = ch5_pass_led_on,
	
	[CH6_LED] = ch6_pass_led_on,
	
	[CH7_LED] = ch7_pass_led_on,
	
	[CH8_LED] = ch8_pass_led_on
};

static void ch1_pass_led_off(void)
{
	SET_GPIO_BIT(PIN_CH1_PASS_LED);
}

static void ch2_pass_led_off(void)
{
	SET_GPIO_BIT(PIN_CH2_PASS_LED);
}

static void ch3_pass_led_off(void)
{
	SET_GPIO_BIT(PIN_CH3_PASS_LED);
}

static void ch4_pass_led_off(void)
{
	SET_GPIO_BIT(PIN_CH4_PASS_LED);
}

static void ch5_pass_led_off(void)
{
	SET_GPIO_BIT(PIN_CH5_PASS_LED);
}

static void ch6_pass_led_off(void)
{
	SET_GPIO_BIT(PIN_CH6_PASS_LED);
}

static void ch7_pass_led_off(void)
{
	SET_GPIO_BIT(PIN_CH7_PASS_LED);
}

static void ch8_pass_led_off(void)
{
	SET_GPIO_BIT(PIN_CH8_PASS_LED);
}

static void (*const s_pass_led_off_func[])(void) = 
{
	[CH1_LED] = ch1_pass_led_off,
	
	[CH2_LED] = ch2_pass_led_off,

	[CH3_LED] = ch3_pass_led_off,
	
	[CH4_LED] = ch4_pass_led_off,
	
	[CH5_LED] = ch5_pass_led_off,
	
	[CH6_LED] = ch6_pass_led_off,
	
	[CH7_LED] = ch7_pass_led_off,
	
	[CH8_LED] = ch8_pass_led_off
};

static void ch1_fail_led_on(void)
{
	CLR_GPIO_BIT(PIN_CH1_FAIL_LED);
}

static void ch2_fail_led_on(void)
{
	CLR_GPIO_BIT(PIN_CH2_FAIL_LED);
}

static void ch3_fail_led_on(void)
{
	CLR_GPIO_BIT(PIN_CH3_FAIL_LED);
}

static void ch4_fail_led_on(void)
{
	CLR_GPIO_BIT(PIN_CH4_FAIL_LED);
}

static void ch5_fail_led_on(void)
{
	CLR_GPIO_BIT(PIN_CH5_FAIL_LED);
}

static void ch6_fail_led_on(void)
{
	CLR_GPIO_BIT(PIN_CH6_FAIL_LED);
}

static void ch7_fail_led_on(void)
{
	CLR_GPIO_BIT(PIN_CH7_FAIL_LED);
}

static void ch8_fail_led_on(void)
{
	CLR_GPIO_BIT(PIN_CH8_FAIL_LED);
}

static void (*const s_fail_led_on_func[])(void) = 
{
	[CH1_LED] = ch1_fail_led_on,
	
	[CH2_LED] = ch2_fail_led_on,

	[CH3_LED] = ch3_fail_led_on,
	
	[CH4_LED] = ch4_fail_led_on,
	
	[CH5_LED] = ch5_fail_led_on,
	
	[CH6_LED] = ch6_fail_led_on,
	
	[CH7_LED] = ch7_fail_led_on,
	
	[CH8_LED] = ch8_fail_led_on
};

static void ch1_fail_led_off(void)
{
	SET_GPIO_BIT(PIN_CH1_FAIL_LED);
}

static void ch2_fail_led_off(void)
{
	SET_GPIO_BIT(PIN_CH2_FAIL_LED);
}

static void ch3_fail_led_off(void)
{
	SET_GPIO_BIT(PIN_CH3_FAIL_LED);
}

static void ch4_fail_led_off(void)
{
	SET_GPIO_BIT(PIN_CH4_FAIL_LED);
}

static void ch5_fail_led_off(void)
{
	SET_GPIO_BIT(PIN_CH5_FAIL_LED);
}

static void ch6_fail_led_off(void)
{
	SET_GPIO_BIT(PIN_CH6_FAIL_LED);
}

static void ch7_fail_led_off(void)
{
	SET_GPIO_BIT(PIN_CH7_FAIL_LED);
}

static void ch8_fail_led_off(void)
{
	SET_GPIO_BIT(PIN_CH8_FAIL_LED);
}

static void (*const s_fail_led_off_func[])(void) = 
{
	[CH1_LED] = ch1_fail_led_off,
	
	[CH2_LED] = ch2_fail_led_off,

	[CH3_LED] = ch3_fail_led_off,
	
	[CH4_LED] = ch4_fail_led_off,
	
	[CH5_LED] = ch5_fail_led_off,
	
	[CH6_LED] = ch6_fail_led_off,
	
	[CH7_LED] = ch7_fail_led_off,
	
	[CH8_LED] = ch8_fail_led_off
};

static void led_gpio_init(void)
{
	SET_GPIO_OUTPUT(PIN_CH1_PASS_LED);
	SET_GPIO_BIT(PIN_CH1_PASS_LED);
	
	SET_GPIO_OUTPUT(PIN_CH1_FAIL_LED);
	SET_GPIO_BIT(PIN_CH1_FAIL_LED);

	SET_GPIO_OUTPUT(PIN_CH2_PASS_LED);
	SET_GPIO_BIT(PIN_CH2_PASS_LED);
	
	SET_GPIO_OUTPUT(PIN_CH2_FAIL_LED);
	SET_GPIO_BIT(PIN_CH2_FAIL_LED);	
	
	SET_GPIO_OUTPUT(PIN_CH3_PASS_LED);
	SET_GPIO_BIT(PIN_CH3_PASS_LED);
	
	SET_GPIO_OUTPUT(PIN_CH3_FAIL_LED);
	SET_GPIO_BIT(PIN_CH3_FAIL_LED);
	
	SET_GPIO_OUTPUT(PIN_CH4_PASS_LED);
	SET_GPIO_BIT(PIN_CH4_PASS_LED);
	
	SET_GPIO_OUTPUT(PIN_CH4_FAIL_LED);
	SET_GPIO_BIT(PIN_CH4_FAIL_LED);
	
	SET_GPIO_OUTPUT(PIN_CH5_PASS_LED);
	SET_GPIO_BIT(PIN_CH5_PASS_LED);
	
	SET_GPIO_OUTPUT(PIN_CH5_FAIL_LED);
	SET_GPIO_BIT(PIN_CH5_FAIL_LED);
	
	SET_GPIO_OUTPUT(PIN_CH6_PASS_LED);
	SET_GPIO_BIT(PIN_CH6_PASS_LED);
	
	SET_GPIO_OUTPUT(PIN_CH6_FAIL_LED);
	SET_GPIO_BIT(PIN_CH6_FAIL_LED);
	
	SET_GPIO_OUTPUT(PIN_CH7_PASS_LED);
	SET_GPIO_BIT(PIN_CH7_PASS_LED);
	
	SET_GPIO_OUTPUT(PIN_CH7_FAIL_LED);
	SET_GPIO_BIT(PIN_CH7_FAIL_LED);
	
	SET_GPIO_OUTPUT(PIN_CH8_PASS_LED);
	SET_GPIO_BIT(PIN_CH8_PASS_LED);
	
	SET_GPIO_OUTPUT(PIN_CH8_FAIL_LED);
	SET_GPIO_BIT(PIN_CH8_FAIL_LED);
}

static rt_err_t rt_led_init (rt_device_t dev)
{
	led_gpio_init();
	
	return RT_EOK;
}

static rt_err_t rt_led_open(rt_device_t dev, rt_uint16_t oflag)
{
	return RT_EOK;
}

static rt_err_t rt_led_close(rt_device_t dev)
{
	return RT_EOK;
}

static rt_size_t rt_led_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
	return 0;
}

static rt_size_t rt_led_write(rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{	
	return 0;
}

static rt_err_t rt_led_control(rt_device_t dev, rt_uint8_t cmd, void *args)
{
	ch_led  ch;
	
	switch (cmd)
	{
	case CMD_LED_PASS_ON:
		ch = *(ch_led *)args;
		if (ch >= LED_NUM)
		{
			goto ERROR;
		}
		
		s_pass_led_on_func[ch]();
		
		break;
		
	case CMD_LED_PASS_OFF:
		ch = *(ch_led *)args;
		if (ch >= LED_NUM)
		{
			goto ERROR;
		}
		
		s_pass_led_off_func[ch]();
		
		break;	

	case CMD_LED_FAIL_ON:
		ch = *(ch_led *)args;
		if (ch >= LED_NUM)
		{
			goto ERROR;
		}
		
		s_fail_led_on_func[ch]();
		
		break;
		
	case CMD_LED_FAIL_OFF:
		ch = *(ch_led *)args;
		if (ch >= LED_NUM)
		{
			goto ERROR;
		}
		
		s_fail_led_off_func[ch]();
		
		break;

	case CMD_ALL_PASS_ON:
		{
			int i;
			for (i = 0; i < sizeof(s_pass_led_on_func) / sizeof(s_pass_led_on_func[0]); i++)
			{
				s_pass_led_on_func[i]();
			}
		}

		break;

	case CMD_ALL_PASS_OFF:
		{
			int i;
			for (i = 0; i < sizeof(s_pass_led_off_func) / sizeof(s_pass_led_off_func[0]); i++)
			{
				s_pass_led_off_func[i]();
			}
		}

		break;

	case CMD_ALL_FAIL_ON:
		{
			int i;
			for (i = 0; i < sizeof(s_fail_led_on_func) / sizeof(s_fail_led_on_func[0]); i++)
			{
				s_fail_led_on_func[i]();
			}
		}

		break;

	case CMD_ALL_FAIL_OFF:
		{
			int i;
			for (i = 0; i < sizeof(s_fail_led_off_func) / sizeof(s_fail_led_off_func[0]); i++)
			{
				s_fail_led_off_func[i]();
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

void dev_led_init(void)
{
	struct dev_led *dev_led;
	dev_led = &s_dev_led;
	
	/* device initialization */
	dev_led->parent.type = RT_Device_Class_Char;

	/* device interface */
	dev_led->parent.init 	  = rt_led_init;
	dev_led->parent.open 	  = rt_led_open;
	dev_led->parent.close     = rt_led_close;
	dev_led->parent.read 	  = rt_led_read;
	dev_led->parent.write     = rt_led_write;
	dev_led->parent.control   = rt_led_control;
	dev_led->parent.user_data = RT_NULL;
	
	rt_device_register(&dev_led->parent, "led", RT_DEVICE_FLAG_WRONLY);
}
