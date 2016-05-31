#include <rthw.h>
#include <rtthread.h>

#include <stdint.h>

#include "PinDefine.h"

#include "dev_key.h"
#include "key_define.h"

#define KEY_QUEUE_LEN     8

#define KEY_NUM     6

/* key status */
typedef enum
{
	KEY_STATUS_IDLE = 0,
	KEY_STATUS_BOUND = 1,
	KEY_STATUS_PRESS = 2,
	KEY_STATUS_LONG  = 3,
	KEY_STATUS_CONTINUE = 4,
	
	KEY_STATUS_LAST
} KEY_STATUS;

#define KEY_TIMER_INTERVAL    10

/* key count */
#define KEY_PRESS_CHECK_COUNT    (20 / KEY_TIMER_INTERVAL)
#define KEY_LONG_CHECK_COUNT     (500 / KEY_TIMER_INTERVAL)
#define KEY_CONTINUE_CHECK_COUNT (300 / KEY_TIMER_INTERVAL)
#define KEY_CONTINUE_DELTA_COUNT (100 / KEY_TIMER_INTERVAL)
#define KEY_CONTINUE_BASE_COUNT  (100 / KEY_TIMER_INTERVAL)

typedef struct _KEY_CHECK
{
	KEY_STATUS keyStatus;
	
	int16_t  count;
	
	int16_t  longCount;
	
	int16_t  continueCount;
	
	int16_t  continueBaseCount;
	
	uint8_t  targetKey;
	rt_bool_t (*CheckFun)(void);	
} KEY_CHECK;

struct dev_key
{
	struct rt_device parent;
	
	/* buffer for reception */
	rt_uint8_t read_index, save_index;
	key_t      key_buffer[KEY_QUEUE_LEN];
};

static struct dev_key s_dev_key;


static rt_bool_t CheckKey1(void)
{
	return !GET_GPIO_BIT(PIN_SW1);
}

static rt_bool_t CheckKey2(void)
{
	return !GET_GPIO_BIT(PIN_SW2);
}

static rt_bool_t CheckKey3(void)
{
	return !GET_GPIO_BIT(PIN_SW3);
}

static rt_bool_t CheckKey4(void)
{
	return !GET_GPIO_BIT(PIN_SW4);
}

static rt_bool_t CheckKey5(void)
{
	return !GET_GPIO_BIT(PIN_SW5);
}

static rt_bool_t CheckKey6(void)
{
	return !GET_GPIO_BIT(PIN_SW6);
}


static KEY_CHECK s_keyCheck[KEY_NUM] = 
{
	[0] = 
	{
		.keyStatus = KEY_STATUS_IDLE,
		.count     = 0,
		.longCount = KEY_LONG_CHECK_COUNT,
		.continueCount = KEY_CONTINUE_CHECK_COUNT,
		.continueBaseCount = KEY_CONTINUE_BASE_COUNT,
		.targetKey = KEY_RIGHT,
		.CheckFun  = CheckKey1
	},
	
	[1] = 
	{
		.keyStatus = KEY_STATUS_IDLE,
		.count     = 0,
		.longCount = KEY_LONG_CHECK_COUNT,
		.continueCount = KEY_CONTINUE_CHECK_COUNT,
		.continueBaseCount = KEY_CONTINUE_BASE_COUNT,
		.targetKey = KEY_DOWN,
		.CheckFun  = CheckKey2
	},
	
	[2] = 
	{
		.keyStatus = KEY_STATUS_IDLE,
		.count     = 0,
		.longCount = KEY_LONG_CHECK_COUNT,
		.continueCount = KEY_CONTINUE_CHECK_COUNT,
		.continueBaseCount = KEY_CONTINUE_BASE_COUNT,
		.targetKey = KEY_LEFT,
		.CheckFun  = CheckKey3
	},
	
	[3] = 
	{
		.keyStatus = KEY_STATUS_IDLE,
		.count     = 0,
		.longCount = KEY_LONG_CHECK_COUNT,
		.continueCount = KEY_CONTINUE_CHECK_COUNT,
		.continueBaseCount = KEY_CONTINUE_BASE_COUNT,
		.targetKey = KEY_CANCEL,
		.CheckFun  = CheckKey4
	},
	
	[4] = 
	{
		.keyStatus = KEY_STATUS_IDLE,
		.count     = 0,
		.longCount = KEY_LONG_CHECK_COUNT,
		.continueCount = KEY_CONTINUE_CHECK_COUNT,
		.continueBaseCount = KEY_CONTINUE_BASE_COUNT,
		.targetKey = KEY_UP,
		.CheckFun  = CheckKey5
	},
	
	[5] = 
	{
		.keyStatus = KEY_STATUS_IDLE,
		.count     = 0,
		.longCount = KEY_LONG_CHECK_COUNT,
		.continueCount = KEY_CONTINUE_CHECK_COUNT,
		.continueBaseCount = KEY_CONTINUE_BASE_COUNT,
		.targetKey = KEY_OK,
		.CheckFun  = CheckKey6
	}
};

static key_t key_check(rt_uint8_t keyNo)
{
	KEY_CHECK *pKeyCheck = &s_keyCheck[keyNo];
	
	rt_uint16_t key = (rt_uint16_t)KEY_NONE;
	
	if (pKeyCheck->CheckFun())
	{
		switch (pKeyCheck->keyStatus)
		{
		case KEY_STATUS_IDLE:
			pKeyCheck->keyStatus = KEY_STATUS_BOUND;
				
			pKeyCheck->count = KEY_PRESS_CHECK_COUNT;
			
			break;
			
		case KEY_STATUS_BOUND:
			pKeyCheck->count--;
			if (pKeyCheck->count == 0)
			{
				key = pKeyCheck->targetKey | MASK_KEY_PRESS;
						
				pKeyCheck->keyStatus = KEY_STATUS_PRESS;
					
				pKeyCheck->count = pKeyCheck->longCount;
			}

			break;
				
		case KEY_STATUS_PRESS:
			pKeyCheck->count--;
			if (pKeyCheck->count == 0)
			{
				key = pKeyCheck->targetKey | MASK_KEY_LONG;

				pKeyCheck->keyStatus = KEY_STATUS_LONG;
					
				pKeyCheck->count = pKeyCheck->continueCount;
			}
				
			break;
				
		case KEY_STATUS_LONG:
			pKeyCheck->count--;
			if (pKeyCheck->count == 0)
			{
				key = pKeyCheck->targetKey | MASK_KEY_CONTINUE;
					
				pKeyCheck->keyStatus = KEY_STATUS_CONTINUE;
					
				pKeyCheck->continueCount -= KEY_CONTINUE_DELTA_COUNT;
				pKeyCheck->count = pKeyCheck->continueCount;
			}
				
			break;
				
		case KEY_STATUS_CONTINUE:
			pKeyCheck->count--;
			if (pKeyCheck->count == 0)
			{
				key = pKeyCheck->targetKey | MASK_KEY_CONTINUE;
				
				pKeyCheck->continueCount -= KEY_CONTINUE_DELTA_COUNT;				
				if (pKeyCheck->continueCount < pKeyCheck->continueBaseCount)
				{
					pKeyCheck->continueCount = pKeyCheck->continueBaseCount;
				}
					
				pKeyCheck->count = pKeyCheck->continueCount;
			}
				
			break;
			
		default:
			break;
		}
	}
	else
	{
		if (pKeyCheck->keyStatus != KEY_STATUS_IDLE && pKeyCheck->keyStatus != KEY_STATUS_BOUND)
		{
			key = pKeyCheck->targetKey | MASK_KEY_RELEASE;
		}
			
		pKeyCheck->count = 0;
		pKeyCheck->continueCount = KEY_CONTINUE_CHECK_COUNT;
		pKeyCheck->keyStatus = KEY_STATUS_IDLE;
	}

	return key;
}

static void timer_callback(void *parameter)
{
	int i;
	key_t key;

	rt_ubase_t level;
	
	struct dev_key *dev_key = (struct dev_key *)parameter;
	
	for (i = 0; i < KEY_NUM; i++)
	{
		key = key_check(i);
		if (KEY_VALUE(key) != KEY_NONE)
		{
			dev_key->key_buffer[dev_key->save_index] = key;

			level = rt_hw_interrupt_disable();
			dev_key->save_index++;
			if (dev_key->save_index >= KEY_QUEUE_LEN)
				dev_key->save_index = 0;
			rt_hw_interrupt_enable(level);

			/* invoke callback */
			if(dev_key->parent.rx_indicate != RT_NULL)
			{
				rt_size_t length;
				if (dev_key->read_index > dev_key->save_index)
					length = KEY_QUEUE_LEN - dev_key->read_index + dev_key->save_index;
				else
					length = dev_key->save_index - dev_key->read_index;

				dev_key->parent.rx_indicate(&dev_key->parent, length);
			}
		}
	}
}

static void key_gpio_init(void)
{	
	SET_GPIO_INPUT(PIN_SW1);
	
	SET_GPIO_INPUT(PIN_SW2);
	
	SET_GPIO_INPUT(PIN_SW3);
	
	SET_GPIO_INPUT(PIN_SW4);
	
	SET_GPIO_INPUT(PIN_SW5);
	
	SET_GPIO_INPUT(PIN_SW6);
}

static rt_err_t rt_key_init (rt_device_t dev)
{
	key_gpio_init();
	
	return RT_EOK;
}

static rt_err_t rt_key_open(rt_device_t dev, rt_uint16_t oflag)
{
	rt_timer_t timer;
	
	timer = rt_timer_create("timer", timer_callback, &s_dev_key, rt_tick_from_millisecond(KEY_TIMER_INTERVAL), RT_TIMER_FLAG_PERIODIC/* | RT_TIMER_FLAG_SOFT_TIMER */);
	RT_ASSERT(timer != RT_NULL);
	rt_timer_start(timer);
	
	return RT_EOK;
}

static rt_err_t rt_key_close(rt_device_t dev)
{
	return RT_EOK;
}

static rt_size_t rt_key_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
	struct dev_key *dev_key = (struct dev_key *)dev;
	
	key_t *key = (key_t *)buffer;
	int32_t count = size / sizeof(key_t);
	
	while (count)
	{
		rt_base_t level;

		/* disable interrupt */
		level = rt_hw_interrupt_disable();
		if (dev_key->read_index != dev_key->save_index)
		{
			*key = dev_key->key_buffer[dev_key->read_index];

			dev_key->read_index ++;
			if (dev_key->read_index >= KEY_QUEUE_LEN)
				dev_key->read_index = 0;
		}
		else
		{
			/* no data */

			/* enable interrupt */
			rt_hw_interrupt_enable(level);
			break;
		}

		/* enable interrupt */
		rt_hw_interrupt_enable(level);

		key++;
		count--;
	}

	return (rt_uint32_t)key - (rt_uint32_t)buffer;
}

static rt_size_t rt_key_write(rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{	
	return 0;
}

static rt_bool_t rt_key_1_val(void)
{
	return !GET_GPIO_BIT(PIN_SW1) ? RT_TRUE : RT_FALSE;
}

static rt_bool_t rt_key_2_val(void)
{
	return !GET_GPIO_BIT(PIN_SW2) ? RT_TRUE : RT_FALSE;
}

static rt_bool_t rt_key_3_val(void)
{
	return !GET_GPIO_BIT(PIN_SW3) ? RT_TRUE : RT_FALSE;
}

static rt_bool_t rt_key_4_val(void)
{
	return !GET_GPIO_BIT(PIN_SW4) ? RT_TRUE : RT_FALSE;
}

static rt_bool_t rt_key_5_val(void)
{
	return !GET_GPIO_BIT(PIN_SW5) ? RT_TRUE : RT_FALSE;
}

static rt_bool_t rt_key_6_val(void)
{
	return !GET_GPIO_BIT(PIN_SW6) ? RT_TRUE : RT_FALSE;
}

static rt_bool_t (* const key_val_fun[])(void) = 
{
	[KEY_RIGHT]  = rt_key_1_val,
	
	[KEY_DOWN]   = rt_key_2_val,
	
	[KEY_LEFT]   = rt_key_3_val,
	
	[KEY_CANCEL] = rt_key_4_val,
	
	[KEY_UP]     = rt_key_5_val,
	
	[KEY_OK]     = rt_key_6_val
};

static rt_err_t rt_key_control(rt_device_t dev, rt_uint8_t cmd, void *args)
{
	switch (cmd)
	{
	case CMD_KEY_GET_VAL:
		{
			key_struct *key = (key_struct *)args;
			if (key->key >= KEY_COUNT)
			{
				goto ERROR;
			}
			
			key->on = key_val_fun[key->key]();
		}
		
		break;
		
	default:
		goto ERROR;
	}
	
	return RT_EOK;

ERROR:	
	return RT_ERROR;
}

void dev_key_init(void)
{
	struct dev_key* key;

	key = &s_dev_key;
	
	/* device initialization */
	key->parent.type = RT_Device_Class_Char;

	/* device interface */
	key->parent.init 	  = rt_key_init;
	key->parent.open 	  = rt_key_open;
	key->parent.close     = rt_key_close;
	key->parent.read 	  = rt_key_read;
	key->parent.write     = rt_key_write;
	key->parent.control   = rt_key_control;
	key->parent.user_data = RT_NULL;
	
	rt_device_register(&key->parent, "key", RT_DEVICE_FLAG_RDONLY);	
}
