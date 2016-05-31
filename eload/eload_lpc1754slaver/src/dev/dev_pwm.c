#include <rthw.h>
#include <rtthread.h>

#include <stdint.h>

#include "lpc17xx_pinsel.h"
#include "lpc17xx_clkpwr.h"
#include "lpc17xx_pwm.h"

#include "dev_pwm.h"

/* 100kHz */
#define PWM_FREQ        100000ul

struct dev_pwm
{
	struct rt_device parent;
};

static struct dev_pwm s_dev_pwm;

static void pwm_init(rt_uint32_t freq)
{
	PINSEL_CFG_Type PinSelCfgType;
	PWM_TIMERCFG_Type PWMTimerCfg;
	PWM_MATCHCFG_Type PWMMatchCfg;

	uint32_t sys_freq;

	//pin config
	//pwm cc
	PinSelCfgType.Portnum = PINSEL_PORT_2;
	PinSelCfgType.Pinnum  = PINSEL_PIN_2;
	PinSelCfgType.Funcnum = PINSEL_FUNC_1;
	PinSelCfgType.Pinmode = PINSEL_PINMODE_PULLUP;
	PinSelCfgType.OpenDrain = PINSEL_PINMODE_NORMAL;
	PINSEL_ConfigPin(&PinSelCfgType);

	//pwm cv
	PinSelCfgType.Portnum = PINSEL_PORT_2;
	PinSelCfgType.Pinnum  = PINSEL_PIN_3;
	PinSelCfgType.Funcnum = PINSEL_FUNC_1;
	PinSelCfgType.Pinmode = PINSEL_PINMODE_PULLUP;
	PinSelCfgType.OpenDrain = PINSEL_PINMODE_NORMAL;
	PINSEL_ConfigPin(&PinSelCfgType);

	//pwm usb dp drive
	PinSelCfgType.Portnum = PINSEL_PORT_2;
	PinSelCfgType.Pinnum  = PINSEL_PIN_4;
	PinSelCfgType.Funcnum = PINSEL_FUNC_1;
	PinSelCfgType.Pinmode = PINSEL_PINMODE_PULLUP;
	PinSelCfgType.OpenDrain = PINSEL_PINMODE_NORMAL;
	PINSEL_ConfigPin(&PinSelCfgType);

	//pwm usb dn drive
	PinSelCfgType.Portnum = PINSEL_PORT_2;
	PinSelCfgType.Pinnum  = PINSEL_PIN_5;
	PinSelCfgType.Funcnum = PINSEL_FUNC_1;
	PinSelCfgType.Pinmode = PINSEL_PINMODE_PULLUP;
	PinSelCfgType.OpenDrain = PINSEL_PINMODE_NORMAL;
	PINSEL_ConfigPin(&PinSelCfgType);
	
	CLKPWR_ConfigPPWR (CLKPWR_PCONP_PCPWM1, ENABLE);
	CLKPWR_SetPCLKDiv (CLKPWR_PCLKSEL_PWM1, CLKPWR_PCLKSEL_CCLK_DIV_1);
	
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
	
	sys_freq = CLKPWR_GetPCLK(CLKPWR_PCLKSEL_PWM1);
	
	PWM_MatchUpdate(LPC_PWM1, 0, sys_freq / freq, PWM_MATCH_UPDATE_NOW);

	//pwm cc
	PWM_ChannelConfig(LPC_PWM1, 3, PWM_CHANNEL_SINGLE_EDGE);
	
	PWMMatchCfg.MatchChannel = 3;
	PWMMatchCfg.IntOnMatch   = DISABLE;
	PWMMatchCfg.StopOnMatch  = DISABLE;
	PWMMatchCfg.ResetOnMatch = DISABLE;
	PWM_ConfigMatch(LPC_PWM1, &PWMMatchCfg);

	PWM_MatchUpdate(LPC_PWM1, 3, 0, PWM_MATCH_UPDATE_NOW);

	PWM_ChannelCmd(LPC_PWM1, 3, ENABLE);

	//cv pwm
	PWM_ChannelConfig(LPC_PWM1, 4, PWM_CHANNEL_SINGLE_EDGE);
	
	PWMMatchCfg.MatchChannel = 4;
	PWMMatchCfg.IntOnMatch   = DISABLE;
	PWMMatchCfg.StopOnMatch  = DISABLE;
	PWMMatchCfg.ResetOnMatch = DISABLE;
	PWM_ConfigMatch(LPC_PWM1, &PWMMatchCfg);

	PWM_MatchUpdate(LPC_PWM1, 4, 0 , PWM_MATCH_UPDATE_NOW);

	PWM_ChannelCmd(LPC_PWM1, 4, ENABLE);

	//pwm usb dp drive
	PWM_ChannelConfig(LPC_PWM1, 5, PWM_CHANNEL_SINGLE_EDGE);
	
	PWMMatchCfg.MatchChannel = 5;
	PWMMatchCfg.IntOnMatch   = DISABLE;
	PWMMatchCfg.StopOnMatch  = DISABLE;
	PWMMatchCfg.ResetOnMatch = DISABLE;
	PWM_ConfigMatch(LPC_PWM1, &PWMMatchCfg);

	PWM_MatchUpdate(LPC_PWM1, 5, 0 , PWM_MATCH_UPDATE_NOW);

	PWM_ChannelCmd(LPC_PWM1, 5, ENABLE);

	//pwm usb dn drive
	PWM_ChannelConfig(LPC_PWM1, 6, PWM_CHANNEL_SINGLE_EDGE);
	
	PWMMatchCfg.MatchChannel = 6;
	PWMMatchCfg.IntOnMatch   = DISABLE;
	PWMMatchCfg.StopOnMatch  = DISABLE;
	PWMMatchCfg.ResetOnMatch = DISABLE;
	PWM_ConfigMatch(LPC_PWM1, &PWMMatchCfg);

	PWM_MatchUpdate(LPC_PWM1, 6, 0 , PWM_MATCH_UPDATE_NOW);

	PWM_ChannelCmd(LPC_PWM1, 6, ENABLE);
	
	PWM_Cmd(LPC_PWM1, ENABLE);
	
	PWM_ResetCounter(LPC_PWM1);
	
	PWM_CounterCmd(LPC_PWM1, ENABLE);	
}

static rt_err_t rt_dev_pwm_init(rt_device_t dev)
{
	pwm_init(PWM_FREQ);
	
	return RT_EOK;
}

static rt_err_t rt_dev_pwm_open(rt_device_t dev, rt_uint16_t oflag)
{
	return RT_EOK;
}

static rt_err_t rt_dev_pwm_close(rt_device_t dev)
{
	return RT_EOK;
}

static rt_size_t rt_dev_pwm_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
	return 0;
}

static rt_size_t rt_dev_pwm_write(rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{	
	return 0;
}

static rt_err_t rt_dev_pwm_control(rt_device_t dev, rt_uint8_t cmd, void *args)
{
	rt_uint32_t sys_freq;
	
	rt_uint32_t val;
	
	switch (cmd)
	{
	case CMD_PWM_VOLTAGE_DUTY_SET:
		sys_freq = CLKPWR_GetPCLK(CLKPWR_PCLKSEL_PWM1);
		
		val = *(rt_int32_t *)args;
		if (val > sys_freq / PWM_FREQ)
		{
			val = sys_freq / PWM_FREQ;
		}
		
		PWM_MatchUpdate(LPC_PWM1, 4, val, PWM_MATCH_UPDATE_NOW);
	
		break;
	
	case CMD_PWM_CURRENT_DUTY_SET:
		sys_freq = CLKPWR_GetPCLK(CLKPWR_PCLKSEL_PWM1);
		
		val = *(rt_int32_t *)args;
		if (val > sys_freq / PWM_FREQ)
		{
			val = sys_freq / PWM_FREQ;
		}
		
		PWM_MatchUpdate(LPC_PWM1, 3, val, PWM_MATCH_UPDATE_NOW);
			
		break;

	case CMD_PWM_DP_DRIVE_SET:
		sys_freq = CLKPWR_GetPCLK(CLKPWR_PCLKSEL_PWM1);
		
		val = *(rt_int32_t *)args;
		if (val > sys_freq / PWM_FREQ)
		{
			val = sys_freq / PWM_FREQ;
		}
		
		PWM_MatchUpdate(LPC_PWM1, 5, val, PWM_MATCH_UPDATE_NOW);
		
		break;

	case CMD_PWM_DN_DRIVE_SET:
		sys_freq = CLKPWR_GetPCLK(CLKPWR_PCLKSEL_PWM1);
		
		val = *(rt_int32_t *)args;
		if (val > sys_freq / PWM_FREQ)
		{
			val = sys_freq / PWM_FREQ;
		}
		
		PWM_MatchUpdate(LPC_PWM1, 6, val, PWM_MATCH_UPDATE_NOW);
		
		break;
		
	case CMD_PWM_MAX_DUTY_GET:
		sys_freq = CLKPWR_GetPCLK(CLKPWR_PCLKSEL_PWM1);
		val = sys_freq / PWM_FREQ;
		
		*(rt_int32_t *)args = val;
	
		break;
	
	default:
		goto ERROR;
	}
	
	return RT_EOK;
	
ERROR:
	return RT_ERROR;
}

void dev_pwm_init(void)
{
	struct dev_pwm *dev_pwm;
	dev_pwm = &s_dev_pwm;
	
	/* device initialization */
	dev_pwm->parent.type = RT_Device_Class_Char;

	/* device interface */
	dev_pwm->parent.init 	  = rt_dev_pwm_init;
	dev_pwm->parent.open      = rt_dev_pwm_open;
	dev_pwm->parent.close     = rt_dev_pwm_close;
	dev_pwm->parent.read 	  = rt_dev_pwm_read;
	dev_pwm->parent.write     = rt_dev_pwm_write;
	dev_pwm->parent.control   = rt_dev_pwm_control;
	dev_pwm->parent.user_data = RT_NULL;
	
	rt_device_register(&dev_pwm->parent, "pwm", RT_DEVICE_FLAG_WRONLY);
}
