#ifndef _DEV_BEEPER_H_
#define _DEV_BEEPER_H_

#include "beeper_define.h"

/* beeper cmd */
#define CMD_BEEP_SET    1

struct beep_property
{
	beeper_vol   vol;
	
	rt_uint16_t  on_interval;
	
	rt_uint16_t  off_interval;
	
	rt_uint16_t  beep_count;
};

extern void dev_beeper_init(void);


#endif
