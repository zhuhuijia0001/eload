#include "rtthread.h"

#include <stdint.h>

#include "type.h"

#include "dev_key.h"
#include "key.h"

static rt_device_t s_dev_key = RT_NULL;

static rt_sem_t s_sem = RT_NULL;

static rt_err_t key_receive_indicate(rt_device_t dev, rt_size_t size)
{
	RT_ASSERT(s_sem != RT_NULL);
	
	rt_sem_release(s_sem);
	
	return RT_EOK;
}

void key_init(void)
{
	dev_key_init();
	
	s_sem = rt_sem_create("key", 0, RT_IPC_FLAG_FIFO);
	RT_ASSERT(s_sem != RT_NULL);
	
	s_dev_key = rt_device_find("key");
	RT_ASSERT(s_dev_key != RT_NULL);
	
	rt_device_set_rx_indicate(s_dev_key, key_receive_indicate);
}

void key_open(void)
{
	RT_ASSERT(s_dev_key != RT_NULL);
	
	rt_device_open(s_dev_key, RT_DEVICE_OFLAG_RDONLY);	
}

bool key_is_pressed(uint8_t key)
{
	key_struct ks;
	
	ks.key = key;
	
	RT_ASSERT(s_dev_key != RT_NULL);
	rt_device_control(s_dev_key, CMD_KEY_GET_VAL, &ks);
	
	return ks.on;
}

key_t key_get(void)
{
	key_t key;
	
	RT_ASSERT(s_dev_key != RT_NULL);
	
	rt_sem_take(s_sem, RT_WAITING_FOREVER);
	
	rt_device_read(s_dev_key, 0, &key, sizeof(key));

	return key;
}

