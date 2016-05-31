#include <rthw.h>
#include <rtthread.h>

#include "Pindefine.h"

#include "dev_relay.h"

enum
{
	RELAY_LOAD = 0,
	
	RELAY_EMPTY,

	RELAY_AC
};

struct dev_relay
{
	struct rt_device parent;
};

static struct dev_relay s_dev_relay;

static void relay_load_on(void)
{
	SET_GPIO_BIT(PIN_LOAD_RELAY);
}

static void relay_load_off(void)
{
	CLR_GPIO_BIT(PIN_LOAD_RELAY);
}

static void relay_empty_on(void)
{
	SET_GPIO_BIT(PIN_EMPTY_RELAY);
}

static void relay_empty_off(void)
{
	CLR_GPIO_BIT(PIN_EMPTY_RELAY);
}

static void relay_ac_on(void)
{
	SET_GPIO_BIT(PIN_AC_RELAY);
}

static void relay_ac_off(void)
{
	CLR_GPIO_BIT(PIN_AC_RELAY);
}

static void (*const s_relay_on_func[])(void) = 
{
	[RELAY_LOAD] = relay_load_on,
	
	[RELAY_EMPTY] = relay_empty_on,

	[RELAY_AC]   = relay_ac_on
};

static void (*const s_relay_off_func[])(void) = 
{
	[RELAY_LOAD] = relay_load_off,
	
	[RELAY_EMPTY] = relay_empty_off,

	[RELAY_AC]   = relay_ac_off
};

static void relay_gpio_init(void)
{
	SET_GPIO_OUTPUT(PIN_LOAD_RELAY);
	CLR_GPIO_BIT(PIN_LOAD_RELAY);
	
	SET_GPIO_OUTPUT(PIN_EMPTY_RELAY);
	CLR_GPIO_BIT(PIN_EMPTY_RELAY);	

	SET_GPIO_OUTPUT(PIN_AC_RELAY);
	CLR_GPIO_BIT(PIN_AC_RELAY);
}

static rt_err_t rt_dev_relay_init(rt_device_t dev)
{
	relay_gpio_init();
	
	return RT_EOK;
}

static rt_err_t rt_dev_relay_open(rt_device_t dev, rt_uint16_t oflag)
{
	return RT_EOK;
}

static rt_err_t rt_dev_relay_close(rt_device_t dev)
{
	return RT_EOK;
}

static rt_size_t rt_dev_relay_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
	return 0;
}

static rt_size_t rt_dev_relay_write(rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{	
	return 0;
}

static rt_err_t rt_dev_relay_control(rt_device_t dev, rt_uint8_t cmd, void *args)
{
	switch (cmd)
	{
	case CMD_RELAY_LOAD_ON:
		s_relay_on_func[RELAY_LOAD]();
	
		break;
	
	case CMD_RELAY_LOAD_OFF:
		s_relay_off_func[RELAY_LOAD]();
	
		break;
	
	case CMD_RELAY_EMPTY_ON:
		s_relay_on_func[RELAY_EMPTY]();
	
		break;
	
	case CMD_RELAY_EMPTY_OFF:
		s_relay_off_func[RELAY_EMPTY]();
	
		break;

	case CMD_RELAY_AC_ON:
		s_relay_on_func[RELAY_AC]();
	
		break;
	
	case CMD_RELAY_AC_OFF:
		s_relay_off_func[RELAY_AC]();
	
		break;
		
	default:
		goto ERROR;
	}
	
	return RT_EOK;
	
ERROR:
	return RT_ERROR;
}

void dev_relay_init(void)
{
	struct dev_relay *dev_relay;
	dev_relay = &s_dev_relay;
	
	/* device initialization */
	dev_relay->parent.type = RT_Device_Class_Char;

	/* device interface */
	dev_relay->parent.init 	    = rt_dev_relay_init;
	dev_relay->parent.open 	    = rt_dev_relay_open;
	dev_relay->parent.close     = rt_dev_relay_close;
	dev_relay->parent.read 	    = rt_dev_relay_read;
	dev_relay->parent.write     = rt_dev_relay_write;
	dev_relay->parent.control   = rt_dev_relay_control;
	dev_relay->parent.user_data = RT_NULL;
	
	rt_device_register(&dev_relay->parent, "relay", RT_DEVICE_FLAG_WRONLY);
}

