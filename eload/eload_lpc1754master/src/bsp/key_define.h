#ifndef _KEY_DEFINE_H_
#define _KEY_DEFINE_H_

#define KEY_NONE     0xFF
#define KEY_UP       0x00
#define KEY_DOWN     0x01
#define KEY_LEFT     0x02
#define KEY_RIGHT    0x03
#define KEY_OK       0x04
#define KEY_CANCEL   0x05

#define KEY_COUNT    0x06

/* key mask */
#define MASK_KEY_PRESS    0x0100
#define MASK_KEY_LONG     0x0200
#define MASK_KEY_CONTINUE 0x0400
#define MASK_KEY_RELEASE  0x0800

#define KEY_TYPE(key)    (key & 0xff00)

#define KEY_VALUE(key)   (uint8_t)(key & 0x00ff)

typedef uint16_t   key_t;

#endif
