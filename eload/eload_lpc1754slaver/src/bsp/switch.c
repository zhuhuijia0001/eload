#include "rtthread.h"

#include <stdint.h>

#include "dev_switch.h"
#include "switch.h"

static rt_device_t s_dev_switch = RT_NULL;

void switch_init(void)
{
	dev_switch_init();
	
	s_dev_switch = rt_device_find("switch");
	RT_ASSERT(s_dev_switch != RT_NULL);
	
	rt_device_open(s_dev_switch, RT_DEVICE_OFLAG_WRONLY);
}

void switch_enable(void)
{
	RT_ASSERT(s_dev_switch != RT_NULL);
	
	rt_device_control(s_dev_switch, CMD_ENABLE_SWITCH, RT_NULL);
}

void switch_disable(void)
{
	RT_ASSERT(s_dev_switch != RT_NULL);
	
	rt_device_control(s_dev_switch, CMD_DISABLE_SWITCH, RT_NULL);	
}

void switch_to_channel(uint32_t ch)
{
	RT_ASSERT(s_dev_switch != RT_NULL);
	
	rt_device_control(s_dev_switch, CMD_SWITCH, &ch);	
}
