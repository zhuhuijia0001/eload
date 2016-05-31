#ifndef _BEEPER_H_
#define _BEEPER_H_

#include "beeper_define.h"

extern void beeper_init(void);

extern void beeper_beep(beeper_vol vol, uint16_t on_interval, uint16_t off_interval, uint16_t beep_count);

#endif
