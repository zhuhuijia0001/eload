#include <rthw.h>
#include <rtthread.h>

#include "Pindefine.h"

#include "dev_switch.h"

struct dev_switch
{
	struct rt_device parent;
};

static struct dev_switch s_dev_switch;

static void switch_to_channel_0(void)
{
	CLR_GPIO_BIT(PIN_H0_S1);

	CLR_GPIO_BIT(PIN_H0_S2);

	CLR_GPIO_BIT(PIN_H0_S3);
}

static void switch_to_channel_1(void)
{
	SET_GPIO_BIT(PIN_H0_S1);

	CLR_GPIO_BIT(PIN_H0_S2);

	CLR_GPIO_BIT(PIN_H0_S3);
}

static void switch_to_channel_2(void)
{
	CLR_GPIO_BIT(PIN_H0_S1);

	SET_GPIO_BIT(PIN_H0_S2);

	CLR_GPIO_BIT(PIN_H0_S3);
}

static void switch_to_channel_3(void)
{
	SET_GPIO_BIT(PIN_H0_S1);

	SET_GPIO_BIT(PIN_H0_S2);

	CLR_GPIO_BIT(PIN_H0_S3);
}

static void switch_to_channel_4(void)
{
	CLR_GPIO_BIT(PIN_H0_S1);

	CLR_GPIO_BIT(PIN_H0_S2);

	SET_GPIO_BIT(PIN_H0_S3);
}

static void switch_to_channel_5(void)
{
	SET_GPIO_BIT(PIN_H0_S1);

	CLR_GPIO_BIT(PIN_H0_S2);

	SET_GPIO_BIT(PIN_H0_S3);
}

static void switch_to_channel_6(void)
{
	CLR_GPIO_BIT(PIN_H0_S1);

	SET_GPIO_BIT(PIN_H0_S2);

	SET_GPIO_BIT(PIN_H0_S3);
}

static void switch_to_channel_7(void)
{
	SET_GPIO_BIT(PIN_H0_S1);

	SET_GPIO_BIT(PIN_H0_S2);

	SET_GPIO_BIT(PIN_H0_S3);
}

static void (*const s_switch_func[])(void) = 
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

static void switch_gpio_init(void)
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

static rt_err_t rt_dev_switch_init(rt_device_t dev)
{
	switch_gpio_init();
	
	return RT_EOK;
}

static rt_err_t rt_dev_switch_open(rt_device_t dev, rt_uint16_t oflag)
{
	return RT_EOK;
}

static rt_err_t rt_dev_switch_close(rt_device_t dev)
{
	return RT_EOK;
}

static rt_size_t rt_dev_switch_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
	return 0;
}

static rt_size_t rt_dev_switch_write(rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{	
	return 0;
}

static rt_err_t rt_dev_switch_control(rt_device_t dev, rt_uint8_t cmd, void *args)
{
	switch (cmd)
	{
	case CMD_ENABLE_SWITCH:
		CLR_GPIO_BIT(PIN_4051_EN);
	
		break;
	
	case CMD_DISABLE_SWITCH:
		SET_GPIO_BIT(PIN_4051_EN);
	
		break;
	
	case CMD_SWITCH:
		{
			rt_uint32_t ch = *(rt_uint32_t *)args;
			if (ch >= sizeof(s_switch_func) / sizeof(s_switch_func[0]))
			{
				goto ERROR;
			}
			
			s_switch_func[ch]();
		}
		
		break;
		
	default:
		goto ERROR;
	}
	
	return RT_EOK;
	
ERROR:
	return RT_ERROR;
}

void dev_switch_init(void)
{
	struct dev_switch *dev_switch;
	dev_switch = &s_dev_switch;
	
	/* device initialization */
	dev_switch->parent.type = RT_Device_Class_Char;

	/* device interface */
	dev_switch->parent.init 	 = rt_dev_switch_init;
	dev_switch->parent.open      = rt_dev_switch_open;
	dev_switch->parent.close     = rt_dev_switch_close;
	dev_switch->parent.read 	 = rt_dev_switch_read;
	dev_switch->parent.write     = rt_dev_switch_write;
	dev_switch->parent.control   = rt_dev_switch_control;
	dev_switch->parent.user_data = RT_NULL;
	
	rt_device_register(&dev_switch->parent, "switch", RT_DEVICE_FLAG_WRONLY);
}

