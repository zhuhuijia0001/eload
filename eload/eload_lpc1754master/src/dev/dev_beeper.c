#include <rthw.h>
#include <rtthread.h>

#include <stdint.h>

#include "dev_beeper.h"

#include "lpc17xx_pinsel.h"
#include "lpc17xx_clkpwr.h"
#include "lpc17xx_pwm.h"

#define BEEPER_FREQ      3000

#define BEEP_QUEUE_LEN   4

struct dev_beeper
{
	struct rt_device parent;
	
	rt_mq_t message_queue;
};

static struct dev_beeper s_dev_beeper;

static void PWM_init(rt_uint32_t freq)
{
	PINSEL_CFG_Type PinSelCfgType;
	PWM_TIMERCFG_Type PWMTimerCfg;
	PWM_MATCHCFG_Type PWMMatchCfg;

	uint32_t sys_freq;

	//pin config
	PinSelCfgType.Portnum = PINSEL_PORT_2;
	PinSelCfgType.Pinnum  = PINSEL_PIN_2;
	PinSelCfgType.Funcnum = PINSEL_FUNC_1;
	PinSelCfgType.Pinmode = PINSEL_PINMODE_PULLUP;
	PinSelCfgType.OpenDrain = PINSEL_PINMODE_NORMAL;
	PINSEL_ConfigPin(&PinSelCfgType);

	CLKPWR_SetPCLKDiv(CLKPWR_PCLKSEL_PWM1, CLKPWR_PCLKSEL_CCLK_DIV_4);
	sys_freq = CLKPWR_GetPCLK(CLKPWR_PCLKSEL_PWM1);
	
	//init
	PWMTimerCfg.PrescaleOption = PWM_TIMER_PRESCALE_TICKVAL;
	PWMTimerCfg.PrescaleValue  = 1;
	PWM_Init(LPC_PWM1, PWM_MODE_TIMER, &PWMTimerCfg);

	//match
	PWMMatchCfg.MatchChannel = 0;
	PWMMatchCfg.IntOnMatch   = DISABLE;
	PWMMatchCfg.StopOnMatch  = DISABLE;
	PWMMatchCfg.ResetOnMatch = ENABLE;
	PWM_ConfigMatch(LPC_PWM1, &PWMMatchCfg);
	
	PWM_MatchUpdate(LPC_PWM1, 0, sys_freq / freq, PWM_MATCH_UPDATE_NOW);

	PWM_ChannelConfig(LPC_PWM1, 3, PWM_CHANNEL_SINGLE_EDGE);
	
	PWMMatchCfg.MatchChannel = 3;
	PWMMatchCfg.IntOnMatch   = DISABLE;
	PWMMatchCfg.StopOnMatch  = DISABLE;
	PWMMatchCfg.ResetOnMatch = DISABLE;
	PWM_ConfigMatch(LPC_PWM1, &PWMMatchCfg);

	PWM_MatchUpdate(LPC_PWM1, 3, 0, PWM_MATCH_UPDATE_NOW);

	PWM_ChannelCmd(LPC_PWM1, 3, ENABLE);

	PWM_Cmd(LPC_PWM1, ENABLE);
	
	PWM_ResetCounter(LPC_PWM1);
	
	PWM_CounterCmd(LPC_PWM1, ENABLE);
}

static void rt_beeper_entry(void *parameter)
{
	rt_bool_t is_beep_on = RT_FALSE;
	
	struct beep_property property;
	
	rt_uint16_t beep_count;
	
	rt_uint16_t on_delay;
	
	rt_uint16_t off_delay;
	
	rt_int32_t timeout;
	
	struct dev_beeper *dev_beeper = (struct dev_beeper *)parameter;
	RT_ASSERT(dev_beeper->message_queue != RT_NULL);
	
	while (RT_TRUE)
	{
		rt_err_t ret;
		
		if (is_beep_on)
		{
			timeout = RT_WAITING_NO;
		}
		else
		{
			timeout = RT_WAITING_FOREVER;
		}

		ret = rt_mq_recv(dev_beeper->message_queue, &property, sizeof(property), timeout);
		if (ret == RT_EOK)
		{
			RT_ASSERT(property.vol <= BEEPER_VOL_HIGH);

			if (property.vol == BEEPER_VOL_MUTE)
			{
				/* mute means stop */
				PWM_MatchUpdate(LPC_PWM1, 3, 0, PWM_MATCH_UPDATE_NOW);
			
				is_beep_on = RT_FALSE;
			}
			else
			{
				is_beep_on = RT_TRUE;
			}
			
			if (is_beep_on)
			{
				/* got a beep property */
				beep_count = property.beep_count;
				
				on_delay = property.on_interval;				
				off_delay = property.off_interval;
			}
		}
		
		if (is_beep_on)
		{
			uint32_t sys_freq;
			sys_freq = CLKPWR_GetPCLK(CLKPWR_PCLKSEL_PWM1);
			
			/* set new match value */
			switch (property.vol)
			{
			case BEEPER_VOL_LOW:
				PWM_MatchUpdate(LPC_PWM1, 3, sys_freq / BEEPER_FREQ / 20, PWM_MATCH_UPDATE_NOW);
			
				break;
			
			case BEEPER_VOL_MEDIUM:
				PWM_MatchUpdate(LPC_PWM1, 3, sys_freq / BEEPER_FREQ / 5, PWM_MATCH_UPDATE_NOW);
			
				break;
			
			case BEEPER_VOL_HIGH:
				PWM_MatchUpdate(LPC_PWM1, 3, sys_freq / BEEPER_FREQ, PWM_MATCH_UPDATE_NOW);
			
				break;
			
			default:
			
				break;
			}
			
			rt_thread_delay(rt_tick_from_millisecond(on_delay));
			
			/* stop */
			PWM_MatchUpdate(LPC_PWM1, 3, 0, PWM_MATCH_UPDATE_NOW);
			
			rt_thread_delay(rt_tick_from_millisecond(off_delay));
			
			beep_count--;
			if (beep_count == 0)
			{	
				on_delay = 0;
				
				off_delay = 0;
				
				is_beep_on = RT_FALSE;
			}
		}
	}
}

static rt_err_t rt_beeper_init (rt_device_t dev)
{
	rt_thread_t tid;
	
	PWM_init(BEEPER_FREQ);
	
	tid = rt_thread_create("beeper", rt_beeper_entry, &s_dev_beeper, 
							256, 17, 10);
	RT_ASSERT(tid != RT_NULL);
	rt_thread_startup(tid);
	
	return RT_EOK;
}

static rt_err_t rt_beeper_open(rt_device_t dev, rt_uint16_t oflag)
{
	return RT_EOK;
}

static rt_err_t rt_beeper_close(rt_device_t dev)
{
	return RT_EOK;
}

static rt_size_t rt_beeper_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
	return 0;
}

static rt_size_t rt_beeper_write(rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{	
	return 0;
}

static rt_err_t rt_beeper_control(rt_device_t dev, rt_uint8_t cmd, void *args)
{
	struct dev_beeper *dev_beeper = (struct dev_beeper *)dev;
	RT_ASSERT(dev_beeper->message_queue != RT_NULL);
	
	switch (cmd)
	{
	case CMD_BEEP_SET:
		{
			struct beep_property *property = (struct beep_property *)args;
			RT_ASSERT(property != RT_NULL 
						&& property->on_interval > 0
						&& property->beep_count > 0);
			
			rt_mq_send(dev_beeper->message_queue, property, sizeof(*property));
		}
		
		break;
		
	default:
		goto ERROR;
	}
	
	return RT_EOK;
	
ERROR:
	return RT_ERROR;
}

void dev_beeper_init(void)
{
	struct dev_beeper *dev_beeper;
	dev_beeper = &s_dev_beeper;
	
	dev_beeper->message_queue = rt_mq_create("beepermsg", sizeof(struct beep_property), BEEP_QUEUE_LEN, RT_IPC_FLAG_FIFO);
	RT_ASSERT(dev_beeper->message_queue != RT_NULL);
	
	/* device initialization */
	dev_beeper->parent.type = RT_Device_Class_Char;

	/* device interface */
	dev_beeper->parent.init 	 = rt_beeper_init;
	dev_beeper->parent.open 	 = rt_beeper_open;
	dev_beeper->parent.close     = rt_beeper_close;
	dev_beeper->parent.read 	 = rt_beeper_read;
	dev_beeper->parent.write     = rt_beeper_write;
	dev_beeper->parent.control   = rt_beeper_control;
	dev_beeper->parent.user_data = RT_NULL;
	
	rt_device_register(&dev_beeper->parent, "beeper", RT_DEVICE_FLAG_WRONLY);
}
