#include "rtthread.h"

#include <stdint.h>

#include "dev_beeper.h"
#include "beeper.h"

static rt_device_t s_dev_beeper = RT_NULL;

void beeper_init(void)
{	
	dev_beeper_init();
	
	s_dev_beeper = rt_device_find("beeper");
	RT_ASSERT(s_dev_beeper != RT_NULL);
	
	rt_device_open(s_dev_beeper, RT_DEVICE_OFLAG_WRONLY);
}

void beeper_beep(beeper_vol vol, uint16_t on_interval, uint16_t off_interval, uint16_t beep_count)
{
	struct beep_property property;
	property.vol          = vol;
	property.on_interval  = on_interval;
	property.off_interval = off_interval;
	property.beep_count   = beep_count;
	
	rt_device_control(s_dev_beeper, CMD_BEEP_SET, &property);
}
