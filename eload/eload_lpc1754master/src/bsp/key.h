#ifndef _KEY_H_
#define _KEY_H_

#include "type.h"
#include "key_define.h"

extern void key_init(void);

extern void key_open(void);

extern bool key_is_pressed(uint8_t key);

extern key_t key_get(void);

#endif
