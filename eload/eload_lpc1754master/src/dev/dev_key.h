#ifndef _DEV_KEY_H_
#define _DEV_KEY_H_

/* key cmd */
#define CMD_KEY_GET_VAL               1

typedef struct 
{
	rt_uint32_t   key;
	
	rt_bool_t     on;
} key_struct;

extern void dev_key_init(void);

#endif
