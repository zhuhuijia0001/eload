#ifndef _DEV_LED_H_
#define _DEV_LED_H_

/* led cmd */
#define CMD_LED_PASS_ON     1

#define CMD_LED_PASS_OFF    2

#define CMD_LED_FAIL_ON     3

#define CMD_LED_FAIL_OFF    4

#define CMD_ALL_PASS_ON     5

#define CMD_ALL_PASS_OFF    6

#define CMD_ALL_FAIL_ON     7

#define CMD_ALL_FAIL_OFF    8

extern void dev_led_init(void);

#endif
