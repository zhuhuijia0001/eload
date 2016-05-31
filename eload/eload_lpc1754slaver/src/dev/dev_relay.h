#ifndef _DEV_RELAY_H_
#define _DEV_RELAY_H_

/* relay cmd */
#define CMD_RELAY_LOAD_ON   0x01

#define CMD_RELAY_LOAD_OFF  0x02

#define CMD_RELAY_EMPTY_ON  0x03

#define CMD_RELAY_EMPTY_OFF 0x04

#define CMD_RELAY_AC_ON     0x05

#define CMD_RELAY_AC_OFF    0x06

extern void dev_relay_init(void);

#endif
