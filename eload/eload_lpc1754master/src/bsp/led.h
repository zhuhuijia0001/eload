#ifndef _LED_H_
#define _LED_H_

#include "led_define.h"

extern void led_init(void);

extern void pass_led_on(ch_led ch);

extern void pass_led_off(ch_led ch);

extern void all_pass_led_on(void);

extern void all_pass_led_off(void);

extern void fail_led_on(ch_led ch);

extern void fail_led_off(ch_led ch);

extern void all_fail_led_on(void);

extern void all_fail_led_off(void);

#endif
