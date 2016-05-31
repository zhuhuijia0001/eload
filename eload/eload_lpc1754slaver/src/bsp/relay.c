#include "rtthread.h"

#include "dev_relay.h"
#include "relay.h"

static rt_device_t s_dev_relay = RT_NULL;

void relay_init(void)
{
	dev_relay_init();
	
	s_dev_relay = rt_device_find("relay");
	RT_ASSERT(s_dev_relay != RT_NULL);
	
	rt_device_open(s_dev_relay, RT_DEVICE_OFLAG_WRONLY);
}

void relay_load_on(void)
{
	RT_ASSERT(s_dev_relay != RT_NULL);
	
	rt_device_control(s_dev_relay, CMD_RELAY_LOAD_ON, RT_NULL);
}

void relay_load_off(void)
{
	RT_ASSERT(s_dev_relay != RT_NULL);
	
	rt_device_control(s_dev_relay, CMD_RELAY_LOAD_OFF, RT_NULL);	
}

void relay_empty_on(void)
{
	RT_ASSERT(s_dev_relay != RT_NULL);
	
	rt_device_control(s_dev_relay, CMD_RELAY_EMPTY_ON, RT_NULL);
}

void relay_empty_off(void)
{
	RT_ASSERT(s_dev_relay != RT_NULL);
	
	rt_device_control(s_dev_relay, CMD_RELAY_EMPTY_OFF, RT_NULL);
}

void relay_ac_on(void)
{
	RT_ASSERT(s_dev_relay != RT_NULL);
	
	rt_device_control(s_dev_relay, CMD_RELAY_AC_ON, RT_NULL);
}

void relay_ac_off(void)
{
	RT_ASSERT(s_dev_relay != RT_NULL);
	
	rt_device_control(s_dev_relay, CMD_RELAY_AC_OFF, RT_NULL);
}

