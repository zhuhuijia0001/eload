#ifndef _SWITCH_H_
#define _SWITCH_H_

/* control channels */
#define CC_CTRL_CHANNEL     0

#define CV_CTRL_CHANNEL     1

#define SHORT_CTRL_CHANNEL  2

#define EMPTY_CTRL_CHANNEL  3

extern void switch_init(void);

extern void switch_enable(void);

extern void switch_disable(void);

extern void switch_to_channel(uint32_t ch);

#endif

