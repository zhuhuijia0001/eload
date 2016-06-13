
#include <rtthread.h>
#include <stdint.h>

#include "switch.h"
#include "control.h"
#include "relay.h"
#include "meter.h"
#include "trace.h"

#include "protocol.h"
#include "app_cfg.h"
#include "global.h"

#include "work_thread.h"

/* ref voltage for adc */
#define ADC_REF_VAL          3000ul

/* 12bit ADC */
#define ADC_RESOLUTION       (1u << 12)

#define VOLTAGE_AMPLITUDE    10ul

#define CURRENT_AMPLITUDE    50ul

/* value of resist sampling */
#define SAMPLE_RESIST_VAL    10ul

/* ac amplitude */
#define AC_AMPLITUDE         (2000ul / 4)

/* value of ac sample resist */
#define AC_SAMPLE_RESIST_VAL  1000ul

/* sample interval */
#define SAMPLE_INTERVAL      20

/* sample count */
#define SAMPLE_COUNT         10

/* delay interval before relay on */
#define RELAY_ON_DELAY       50

/* VDD reference */
#define VDD_REF              3300ul

/* over current step */
#define OVER_CURRENT_STEP    100ul

#define  TEST_FLAG_FAIL      0x00
#define  TEST_FLAG_OK        0x01

/* automatic test time limit */
#define  AUTOMATIC_TEST_LIMIT   2000

typedef struct 
{
	uint8_t test_type;
	
	uint8_t test_status;

	uint8_t test_flag;

	TEST_CONFIG  test_config;
} TEST_STATUS;

static TEST_STATUS  s_test_status;

/* convert */
uint32_t adc_to_voltage_val(uint32_t adc_val)
{
	uint64_t val = adc_val;
	val *= ADC_REF_VAL;
	val *= VOLTAGE_AMPLITUDE;
	val /= ADC_RESOLUTION;

	return (uint32_t)val;
}

uint32_t adc_to_current_val(uint32_t adc_val)
{
	uint64_t val = adc_val;
	val *= ADC_REF_VAL;
	val *= 1000ul;
	val /= CURRENT_AMPLITUDE;
	val /= SAMPLE_RESIST_VAL;
	val /= ADC_RESOLUTION;

	return (uint32_t)val;
}

uint32_t adc_to_ac_val(uint32_t adc_val)
{
	uint64_t val = adc_val;
	val *= ADC_REF_VAL;
	val *= AC_AMPLITUDE;
	val /= ADC_RESOLUTION;
	val *= 1000;
	val /= AC_SAMPLE_RESIST_VAL;

	return (uint32_t)val;
}

/* PWM duty */
static int32_t s_duty = 0;

/* max PWM duty */
static int32_t s_max_duty = 0;

static void try_set_voltage(uint32_t mV)
{
	RT_ASSERT(s_max_duty > 0);
	
	s_duty = mV * s_max_duty / VOLTAGE_AMPLITUDE / VDD_REF;
			
	control_set_voltage_duty(s_duty);
}

static void try_set_current(uint32_t mA)
{
	RT_ASSERT(s_max_duty > 0);
	
	s_duty = mA * s_max_duty * CURRENT_AMPLITUDE * SAMPLE_RESIST_VAL / 1000ul / VDD_REF;
			
	control_set_current_duty(s_duty);
}

static void try_set_resist(uint32_t mV, uint32_t uO)
{
	uint32_t init_current;

	RT_ASSERT(s_max_duty > 0);

	RT_ASSERT(uO > 0);

	init_current = mV * 1000ul / uO;
	s_duty = init_current * s_max_duty * CURRENT_AMPLITUDE * SAMPLE_RESIST_VAL / 1000ul / VDD_REF;
			
	control_set_current_duty(s_duty);
}

static void adjust_voltage_current(uint32_t mV, uint32_t mA)
{

	uint32_t target_val;
	
	if (s_test_status.test_type == TEST_TYPE_CV_MODE || s_test_status.test_type == TEST_TYPE_CV_TEST)
	{
		if (s_test_status.test_type == TEST_TYPE_CV_MODE)
		{
			target_val = s_test_status.test_config.cv_mode_config.voltage_val;
		}
		else
		{
			target_val = s_test_status.test_config.cv_test_config.voltage_val;
		}

		/*
		if (mV < target_val)
		{
			s_duty++;
			if (s_duty > s_max_duty)
			{
				s_duty = s_max_duty;
			}
				
			control_set_voltage_duty(s_duty);
			
			TRACE("voltage duty:%d\n", s_duty);
		}
		else if (mV > target_val)
		{
			s_duty--;
			if (s_duty < 0)
			{
				s_duty = 0;
			}

			control_set_voltage_duty(s_duty);
			
			TRACE("voltage duty:%d\n", s_duty);
		}
		*/
	}
	else if (s_test_status.test_type == TEST_TYPE_CC_MODE || s_test_status.test_type == TEST_TYPE_CC_TEST)
	{
		if (s_test_status.test_type == TEST_TYPE_CC_MODE)
		{
			target_val = s_test_status.test_config.cc_mode_config.current_val;
		}
		else
		{
			target_val = s_test_status.test_config.cc_test_config.current_val;
		}
		
		if (mA < target_val)
		{
			s_duty++;
			if (s_duty > s_max_duty)
			{
				s_duty = s_max_duty;
			}
				
			control_set_current_duty(s_duty);
		}
		else if (mA > target_val)
		{
			s_duty--;
			if (s_duty < 0)
			{
				s_duty = 0;
			}
				
			control_set_current_duty(s_duty);
		}
	}
	else if (s_test_status.test_type == TEST_TYPE_CR_MODE || s_test_status.test_type == TEST_TYPE_CR_TEST)
	{
		uint32_t resist;
		
		if (s_test_status.test_type == TEST_TYPE_CR_MODE)
		{
			target_val = s_test_status.test_config.cr_mode_config.resist_val;
		}
		else
		{
			target_val = s_test_status.test_config.cr_test_config.resist_val;
		}
		
		resist = mV * 1000ul / mA;
		if (resist < target_val)
		{
			/* resist is too low, must decrease current */
			s_duty--;
			if (s_duty < 0)
			{
				s_duty = 0;
			}
				
			control_set_current_duty(s_duty);
		}
		else if (resist > target_val)
		{
			/* resist is too high, must increase current */
			s_duty++;
			if (s_duty > s_max_duty)
			{
				s_duty = s_max_duty;
			}
			
			control_set_current_duty(s_duty);
		}
	}

	//TRACE("max duty:%d\n", control_get_max_duty());
	//TRACE("duty:%d\n", s_duty);
}

//qc 2.0 switch
static void switch_to_qc_20_5v_level(void)
{
	control_set_dp_drive_duty(0);
	
	control_set_dn_drive_duty(0);
}

static void switch_to_qc_20_9v_level(void)
{
	int32_t duty = 700 * s_max_duty / VDD_REF;

	control_set_dp_drive_duty(duty);
	//control_set_dn_drive_duty(0);

	//delay 1.5s
	rt_thread_delay(rt_tick_from_millisecond(1500));
	
	//give d+ 3.3V, d- 0.6V
	control_set_dp_drive_duty(s_max_duty);
	control_set_dn_drive_duty(duty);

	rt_thread_delay(rt_tick_from_millisecond(100));
}

static void switch_to_qc_20_12v_level(void)
{
	int32_t duty = 700 * s_max_duty / VDD_REF;

	control_set_dp_drive_duty(duty);
	//control_set_dn_drive_duty(0);

	//delay 1.5s
	rt_thread_delay(rt_tick_from_millisecond(1500));

	//give d+ 0.6V, d- 0.6V
	control_set_dp_drive_duty(duty);
	control_set_dn_drive_duty(duty);

	rt_thread_delay(rt_tick_from_millisecond(100));
}

static void switch_to_qc_20_20v_level(void)
{
	int32_t duty = 700 * s_max_duty / VDD_REF;

	control_set_dp_drive_duty(duty);
	//control_set_dn_drive_duty(0);

	//delay 1.5s
	rt_thread_delay(rt_tick_from_millisecond(1500));

	//give d+ 3.3V, d- 3.3V
	control_set_dp_drive_duty(s_max_duty);
	control_set_dn_drive_duty(s_max_duty);

	rt_thread_delay(rt_tick_from_millisecond(100));
}

static void switch_to_qc_20_voltage_level(uint8_t voltage_level)
{
	switch (voltage_level)
	{
	case TEST_VOLTAGE_LEVEL_5V:
		switch_to_qc_20_5v_level();

		break;

	case TEST_VOLTAGE_LEVEL_9V:
		switch_to_qc_20_9v_level();

		break;

	case TEST_VOLTAGE_LEVEL_12V:
		switch_to_qc_20_12v_level();

		break;

	case TEST_VOLTAGE_LEVEL_20V:
		switch_to_qc_20_20v_level();

		break;

	default:
		RT_ASSERT(RT_FALSE);
		
		break;
	}
}

static void mtk_voltage_increase_step(void)
{
	try_set_current(0);
	rt_thread_delay(rt_tick_from_millisecond(100));
	
	//start
	try_set_current(300);
	rt_thread_delay(rt_tick_from_millisecond(100));

	try_set_current(0);
	rt_thread_delay(rt_tick_from_millisecond(100));

	try_set_current(300);
	rt_thread_delay(rt_tick_from_millisecond(100));

	try_set_current(0);
	rt_thread_delay(rt_tick_from_millisecond(100));

	try_set_current(300);
	rt_thread_delay(rt_tick_from_millisecond(300));

	try_set_current(0);
	rt_thread_delay(rt_tick_from_millisecond(100));

	try_set_current(300);
	rt_thread_delay(rt_tick_from_millisecond(300));

	try_set_current(0);
	rt_thread_delay(rt_tick_from_millisecond(100));

	try_set_current(300);
	rt_thread_delay(rt_tick_from_millisecond(300));

	try_set_current(0);
	rt_thread_delay(rt_tick_from_millisecond(100));

	try_set_current(300);
	rt_thread_delay(rt_tick_from_millisecond(500));

	try_set_current(0);
	rt_thread_delay(rt_tick_from_millisecond(100));

	try_set_current(300);
	rt_thread_delay(rt_tick_from_millisecond(100));
}

static void mtk_voltage_decrease_step(void)
{
	try_set_current(0);
	rt_thread_delay(rt_tick_from_millisecond(100));
	
	//start
	try_set_current(300);
	rt_thread_delay(rt_tick_from_millisecond(300));

	try_set_current(0);
	rt_thread_delay(rt_tick_from_millisecond(100));

	try_set_current(300);
	rt_thread_delay(rt_tick_from_millisecond(300));

	try_set_current(0);
	rt_thread_delay(rt_tick_from_millisecond(100));

	try_set_current(300);
	rt_thread_delay(rt_tick_from_millisecond(300));

	try_set_current(0);
	rt_thread_delay(rt_tick_from_millisecond(100));

	try_set_current(300);
	rt_thread_delay(rt_tick_from_millisecond(100));

	try_set_current(0);
	rt_thread_delay(rt_tick_from_millisecond(100));

	try_set_current(300);
	rt_thread_delay(rt_tick_from_millisecond(100));

	try_set_current(0);
	rt_thread_delay(rt_tick_from_millisecond(100));

	try_set_current(300);
	rt_thread_delay(rt_tick_from_millisecond(500));

	try_set_current(0);
	rt_thread_delay(rt_tick_from_millisecond(100));

	try_set_current(300);
	rt_thread_delay(rt_tick_from_millisecond(100));
}

static void mtk_switch_to_default(void)
{
	try_set_current(0);
	rt_thread_delay(rt_tick_from_millisecond(300));
}

//mtk switch
static void switch_to_mtk_5v_level(void)
{

}

static void switch_to_mtk_9v_level(void)
{

}

static void switch_to_mtk_12v_level(void)
{

}

static void switch_to_mtk_20v_level(void)
{

}

static void switch_to_mtk_voltage_level(uint8_t voltage_level)
{
	switch (voltage_level)
	{
	case TEST_VOLTAGE_LEVEL_5V:
		switch_to_mtk_5v_level();

		break;

	case TEST_VOLTAGE_LEVEL_9V:
		switch_to_mtk_9v_level();

		break;

	case TEST_VOLTAGE_LEVEL_12V:
		switch_to_mtk_12v_level();

		break;

	case TEST_VOLTAGE_LEVEL_20V:
		switch_to_mtk_20v_level();

		break;

	default:
		RT_ASSERT(RT_FALSE);
		
		break;
	}
}

static void work_thread_entry(void *parameter)
{	
	uint32_t adc_val;
	uint32_t voltage_min, voltage_max;
	uint32_t current_min, current_max;
	uint32_t ac_min, ac_max;
	
	uint32_t voltage, current, ac;

	uint32_t last_voltage;

	uint32_t cur_over_current;
	
	uint32_t sample_count;
	
	rt_err_t ret;
	TEST_CMD  test_cmd;
	
	rt_tick_t next_tick;

	uint8_t last_test_category;
	
	uint8_t last_voltage_level;
	
	/* init channel */
	switch_disable();
	switch_to_channel(CV_CTRL_CHANNEL);
	
	s_max_duty = control_get_max_duty();
	
	control_set_voltage_duty(0);
	
	relay_load_off();

	relay_empty_off();
	
	relay_ac_off();
	
	sample_count = 0;

	s_test_status.test_type   = TEST_TYPE_NONE;
	s_test_status.test_status = TEST_STATUS_IDLE;
	s_test_status.test_flag   = TEST_FLAG_FAIL;

	last_voltage = 0;

	last_test_category = TEST_CATEGORY_SYNTH;
	
	last_voltage_level = TEST_VOLTAGE_LEVEL_5V;
	
	while (RT_TRUE)
	{	
		RT_ASSERT(g_test_cmd_queue != RT_NULL);
	
		/* get cmd */
		ret = rt_mq_recv(g_test_cmd_queue, &test_cmd, sizeof(test_cmd), RT_WAITING_NO);
		if (ret == RT_EOK)
		{
			switch (test_cmd.test_type)
			{
			case TEST_TYPE_CV_MODE:
				if (s_test_status.test_type == TEST_TYPE_CV_MODE)
				{
					TRACE("cv mode continue\n");

					/* still cv mode */
					s_test_status.test_config.cv_mode_config = test_cmd.test_config.cv_mode_config;

					s_test_status.test_status = TEST_STATUS_ON;
					try_set_voltage(s_test_status.test_config.cv_mode_config.voltage_val);
				
					/* update content */
					rt_sem_take(g_sem_test_content, RT_WAITING_FOREVER);
					g_test_content.test_type   = TEST_TYPE_CV_MODE;
					g_test_content.test_status = TEST_STATUS_ON;
					rt_sem_release(g_sem_test_content);
				}
				else
				{
					/* just start testing */
					switch_disable();
					switch_to_channel(CV_CTRL_CHANNEL);
				
					control_set_current_duty(0);

					s_test_status.test_config.cv_mode_config = test_cmd.test_config.cv_mode_config;

					try_set_voltage(s_test_status.test_config.cv_mode_config.voltage_val);
	
					switch_enable();

					if (s_test_status.test_type == TEST_TYPE_NONE
						|| s_test_status.test_type == TEST_TYPE_EMPTY_LOAD_TEST)
					{
						/* init status is no testing */
						TRACE("first cv mode\n");

						relay_load_on();

						relay_empty_on();
						
						rt_thread_delay(rt_tick_from_millisecond(RELAY_ON_DELAY));
					}

					/* update content */
					rt_sem_take(g_sem_test_content, RT_WAITING_FOREVER);
					g_test_content.test_type   = TEST_TYPE_CV_MODE;
					g_test_content.test_status = TEST_STATUS_ON;
					rt_sem_release(g_sem_test_content);
					
					s_test_status.test_type     = TEST_TYPE_CV_MODE;
					s_test_status.test_status   = TEST_STATUS_ON;
				}
				
				sample_count = 0;
				
				break;
			
			case TEST_TYPE_CC_MODE:
				if (s_test_status.test_type == TEST_TYPE_CC_MODE)
				{
					TRACE("cc mode continue\n");
					
					/* still cc mode */
					s_test_status.test_config.cc_mode_config = test_cmd.test_config.cc_mode_config;

					s_test_status.test_status   = TEST_STATUS_ON;
					
					try_set_current(s_test_status.test_config.cc_mode_config.current_val);

					/* update content */
					rt_sem_take(g_sem_test_content, RT_WAITING_FOREVER);
					g_test_content.test_type   = TEST_TYPE_CC_MODE;
					g_test_content.test_status = TEST_STATUS_ON;
					rt_sem_release(g_sem_test_content);
				}
				else
				{
					/* just start testing */
					switch_disable();
					switch_to_channel(CC_CTRL_CHANNEL);
					
					control_set_voltage_duty(0);
					
					if (s_test_status.test_type == TEST_TYPE_NONE
						|| s_test_status.test_type == TEST_TYPE_EMPTY_LOAD_TEST)
					{
						/* init status is no testing */
						TRACE("first cc mode\n");

						relay_load_on();

						relay_empty_on();
						
						rt_thread_delay(rt_tick_from_millisecond(RELAY_ON_DELAY));
					}

					s_test_status.test_config.cc_mode_config = test_cmd.test_config.cc_mode_config;

					s_test_status.test_type     = TEST_TYPE_CC_MODE;
					s_test_status.test_status   = TEST_STATUS_ON;
					
					try_set_current(s_test_status.test_config.cc_mode_config.current_val);

					/* update content */
					rt_sem_take(g_sem_test_content, RT_WAITING_FOREVER);
					g_test_content.test_type   = TEST_TYPE_CC_MODE;
					g_test_content.test_status = TEST_STATUS_ON;
					rt_sem_release(g_sem_test_content);
	
					switch_enable();
				}
				
				sample_count = 0;
						
				break;
			
			case TEST_TYPE_CR_MODE:
				if (s_test_status.test_type == TEST_TYPE_CR_MODE)
				{
					TRACE("cr mode continue\n");
					
					/* still cr mode */
					s_test_status.test_config.cr_mode_config = test_cmd.test_config.cr_mode_config;

					s_test_status.test_status   = TEST_STATUS_ON;	
					
					try_set_resist(last_voltage, s_test_status.test_config.cr_mode_config.resist_val);

					/* update content */
					rt_sem_take(g_sem_test_content, RT_WAITING_FOREVER);
					g_test_content.test_type   = TEST_TYPE_CR_MODE;
					g_test_content.test_status = TEST_STATUS_ON;
					rt_sem_release(g_sem_test_content);
				}
				else
				{
					/* just start testing */
					switch_disable();
					switch_to_channel(CC_CTRL_CHANNEL);
					
					control_set_voltage_duty(0);
					
					if (s_test_status.test_type == TEST_TYPE_NONE
						|| s_test_status.test_type == TEST_TYPE_EMPTY_LOAD_TEST)
					{
						/* init status is no testing */
						TRACE("first cr mode\n");

						relay_load_on();

						relay_empty_on();
						
						rt_thread_delay(rt_tick_from_millisecond(RELAY_ON_DELAY));
					}

					s_test_status.test_config.cr_mode_config = test_cmd.test_config.cr_mode_config;

					s_test_status.test_type     = TEST_TYPE_CR_MODE;
					s_test_status.test_status   = TEST_STATUS_ON;
					
					try_set_resist(last_voltage, s_test_status.test_config.cr_mode_config.resist_val);

					/* update content */
					rt_sem_take(g_sem_test_content, RT_WAITING_FOREVER);
					g_test_content.test_type   = TEST_TYPE_CR_MODE;
					g_test_content.test_status = TEST_STATUS_ON;
					rt_sem_release(g_sem_test_content);
					
					switch_enable();
				}
				
				sample_count = 0;
				
				break;

			case TEST_TYPE_CV_TEST:
				if (s_test_status.test_type != TEST_TYPE_NONE
						&& s_test_status.test_type != TEST_TYPE_EMPTY_LOAD_TEST)
				{
					TRACE("still relay on\n");

					s_test_status.test_config.cv_test_config = test_cmd.test_config.cv_test_config;
					
					/* still relay on */
					switch_disable();
					switch_to_channel(CV_CTRL_CHANNEL);

					if (s_test_status.test_config.cv_test_config.test_category != TEST_CATEGORY_SYNTH)
					{
						relay_load_off();
						
						rt_thread_delay(rt_tick_from_millisecond(RELAY_ON_DELAY));
					}	

					s_test_status.test_status  = TEST_STATUS_ON;

					/* update content */
					rt_sem_take(g_sem_test_content, RT_WAITING_FOREVER);
					g_test_content.test_type   = TEST_TYPE_CV_TEST;
					g_test_content.test_status = TEST_STATUS_ON;
					rt_sem_release(g_sem_test_content);
					
					if (s_test_status.test_config.cv_test_config.test_category == TEST_CATEGORY_QC_20)
					{
						last_test_category = TEST_CATEGORY_QC_20;
						
						if (s_test_status.test_config.cv_test_config.voltage_level != last_voltage_level)
						{
							switch_to_qc_20_voltage_level(s_test_status.test_config.cv_test_config.voltage_level);
							
							last_voltage_level = s_test_status.test_config.cv_test_config.voltage_level;
						}
					}
					else if (s_test_status.test_config.cv_test_config.test_category == TEST_CATEGORY_MTK)
					{
						last_test_category = TEST_CATEGORY_MTK;
						
						if (s_test_status.test_config.cv_test_config.voltage_level != last_voltage_level)
						{
							switch_to_mtk_voltage_level(s_test_status.test_config.cv_test_config.voltage_level);

							last_voltage_level = s_test_status.test_config.cv_test_config.voltage_level;
						}
					}
					
					try_set_voltage(s_test_status.test_config.cv_test_config.voltage_val);

					switch_enable();

					if (s_test_status.test_config.cv_test_config.test_category != TEST_CATEGORY_SYNTH)
					{
						relay_load_on();
							
						rt_thread_delay(rt_tick_from_millisecond(RELAY_ON_DELAY));
					}
				}
				else
				{
					/* load relay is off */
					switch_disable();
					switch_to_channel(CV_CTRL_CHANNEL);
					
					control_set_current_duty(0);
					
					s_test_status.test_config.cv_test_config = test_cmd.test_config.cv_test_config;

					s_test_status.test_type     = TEST_TYPE_CV_TEST;
					s_test_status.test_status   = TEST_STATUS_ON;

					/* update content */
					rt_sem_take(g_sem_test_content, RT_WAITING_FOREVER);
					g_test_content.test_type   = TEST_TYPE_CV_TEST;
					g_test_content.test_status = TEST_STATUS_ON;
					rt_sem_release(g_sem_test_content);
					
					if (s_test_status.test_config.cv_test_config.test_category == TEST_CATEGORY_QC_20)
					{
						last_test_category = TEST_CATEGORY_QC_20;
						
						if (s_test_status.test_config.cv_test_config.voltage_level != last_voltage_level)
						{
							switch_to_qc_20_voltage_level(s_test_status.test_config.cv_test_config.voltage_level);

							last_voltage_level = s_test_status.test_config.cv_test_config.voltage_level;
						}
					}
					else if (s_test_status.test_config.cv_test_config.test_category == TEST_CATEGORY_MTK)
					{
						last_test_category = TEST_CATEGORY_MTK;
						
						if (s_test_status.test_config.cv_test_config.voltage_level != last_voltage_level)
						{
							switch_to_mtk_voltage_level(s_test_status.test_config.cv_test_config.voltage_level);

							last_voltage_level = s_test_status.test_config.cv_test_config.voltage_level;
						}
					}
					
					try_set_voltage(s_test_status.test_config.cv_test_config.voltage_val);

					/* assume relay is on */
					switch_enable();

					/* init status is no testing */
					TRACE("first cv test\n");

					relay_load_on();
						
					rt_thread_delay(rt_tick_from_millisecond(RELAY_ON_DELAY));
				}

				s_test_status.test_flag = TEST_FLAG_FAIL;

				if (s_test_status.test_config.cv_test_config.duration == AUTOMATIC_TIME)
				{
					next_tick = rt_tick_get() + rt_tick_from_millisecond(AUTOMATIC_TEST_LIMIT);
				}
				else
				{
					next_tick = rt_tick_get() + rt_tick_from_millisecond(s_test_status.test_config.cv_test_config.duration);
				}
				
				sample_count = 0;
				
				break;

			case TEST_TYPE_CC_TEST:
				if (s_test_status.test_type == TEST_TYPE_CC_TEST)
				{
					TRACE("cc test continue\n");
					
					/* still cc test */
					switch_disable();
					switch_to_channel(CC_CTRL_CHANNEL);
					
					s_test_status.test_config.cc_test_config = test_cmd.test_config.cc_test_config;

					s_test_status.test_status   = TEST_STATUS_ON;

					/* update content */
					rt_sem_take(g_sem_test_content, RT_WAITING_FOREVER);
					g_test_content.test_type   = TEST_TYPE_CC_TEST;
					g_test_content.test_status = TEST_STATUS_ON;
					rt_sem_release(g_sem_test_content);

					if (s_test_status.test_config.cc_test_config.test_category == TEST_CATEGORY_QC_20)
					{
						last_test_category = TEST_CATEGORY_QC_20;
						
						if (s_test_status.test_config.cc_test_config.voltage_level != last_voltage_level)
						{
							switch_to_qc_20_voltage_level(s_test_status.test_config.cc_test_config.voltage_level);

							last_voltage_level = s_test_status.test_config.cc_test_config.voltage_level;
						}
					}
					else if (s_test_status.test_config.cc_test_config.test_category == TEST_CATEGORY_MTK)
					{
						last_test_category = TEST_CATEGORY_MTK;
						
						if (s_test_status.test_config.cc_test_config.voltage_level != last_voltage_level)
						{
							switch_to_mtk_voltage_level(s_test_status.test_config.cc_test_config.voltage_level);

							last_voltage_level = s_test_status.test_config.cc_test_config.voltage_level;
						}
					}

					try_set_current(s_test_status.test_config.cc_test_config.current_val);

					switch_enable();
				}
				else
				{
					/* just start testing */
					switch_disable();
					switch_to_channel(CC_CTRL_CHANNEL);
					
					control_set_voltage_duty(0);

					if (s_test_status.test_type == TEST_TYPE_NONE
						|| s_test_status.test_type == TEST_TYPE_EMPTY_LOAD_TEST)
					{
						/* init status is no testing */
						TRACE("first cc test\n");

						relay_load_on();

						relay_empty_on();
						
						rt_thread_delay(rt_tick_from_millisecond(RELAY_ON_DELAY));
					}

					s_test_status.test_config.cc_test_config = test_cmd.test_config.cc_test_config;

					s_test_status.test_type     = TEST_TYPE_CC_TEST;
					s_test_status.test_status   = TEST_STATUS_ON;

					/* update content */
					rt_sem_take(g_sem_test_content, RT_WAITING_FOREVER);
					g_test_content.test_type   = TEST_TYPE_CC_TEST;
					g_test_content.test_status = TEST_STATUS_ON;
					rt_sem_release(g_sem_test_content);
					
					if (s_test_status.test_config.cc_test_config.test_category == TEST_CATEGORY_QC_20)
					{
						last_test_category = TEST_CATEGORY_QC_20;
						
						if (s_test_status.test_config.cc_test_config.voltage_level != last_voltage_level)
						{
							switch_to_qc_20_voltage_level(s_test_status.test_config.cc_test_config.voltage_level);

							last_voltage_level = s_test_status.test_config.cc_test_config.voltage_level;
						}
					}
					else if (s_test_status.test_config.cc_test_config.test_category == TEST_CATEGORY_MTK)
					{
						last_test_category = TEST_CATEGORY_MTK;
						
						if (s_test_status.test_config.cc_test_config.voltage_level != last_voltage_level)
						{
							switch_to_mtk_voltage_level(s_test_status.test_config.cc_test_config.voltage_level);

							last_voltage_level = s_test_status.test_config.cc_test_config.voltage_level;
						}
					}
					
					try_set_current(s_test_status.test_config.cc_test_config.current_val);
					
					/* assume relay is on */
					switch_enable();
				}

				s_test_status.test_flag = TEST_FLAG_FAIL;

				if (s_test_status.test_config.cc_test_config.duration == AUTOMATIC_TIME)
				{
					next_tick = rt_tick_get() + rt_tick_from_millisecond(AUTOMATIC_TEST_LIMIT);
				}
				else
				{
					next_tick = rt_tick_get() + rt_tick_from_millisecond(s_test_status.test_config.cc_test_config.duration);
				}
				
				sample_count = 0;
				
				break;

			case TEST_TYPE_CR_TEST:
				if (s_test_status.test_type == TEST_TYPE_CR_TEST)
				{
					TRACE("cr test continue\n");
					
					/* still cr test */
					switch_disable();
					switch_to_channel(CC_CTRL_CHANNEL);
					
					s_test_status.test_config.cr_test_config = test_cmd.test_config.cr_test_config;

					s_test_status.test_status = TEST_STATUS_ON;

					/* update content */
					rt_sem_take(g_sem_test_content, RT_WAITING_FOREVER);
					g_test_content.test_type   = TEST_TYPE_CR_TEST;
					g_test_content.test_status = TEST_STATUS_ON;
					rt_sem_release(g_sem_test_content);
				
					if (s_test_status.test_config.cr_test_config.test_category == TEST_CATEGORY_QC_20)
					{
						last_test_category = TEST_CATEGORY_QC_20;
						
						if (s_test_status.test_config.cr_test_config.voltage_level != last_voltage_level)
						{
							switch_to_qc_20_voltage_level(s_test_status.test_config.cr_test_config.voltage_level);

							last_voltage_level = s_test_status.test_config.cr_test_config.voltage_level;
						}
					}
					else if (s_test_status.test_config.cr_test_config.test_category == TEST_CATEGORY_MTK)
					{
						last_test_category = TEST_CATEGORY_MTK;
						
						if (s_test_status.test_config.cr_test_config.voltage_level != last_voltage_level)
						{
							switch_to_mtk_voltage_level(s_test_status.test_config.cr_test_config.voltage_level);

							last_voltage_level = s_test_status.test_config.cr_test_config.voltage_level;
						}
					}
					
					try_set_resist(last_voltage, s_test_status.test_config.cr_test_config.resist_val);

					switch_enable();
				}
				else
				{
					/* just start testing */
					switch_disable();
					switch_to_channel(CC_CTRL_CHANNEL);
					
					control_set_voltage_duty(0);

					if (s_test_status.test_type == TEST_TYPE_NONE
						|| s_test_status.test_type == TEST_TYPE_EMPTY_LOAD_TEST)
					{
						/* init status is no testing */
						TRACE("first cr test\n");

						relay_load_on();

						relay_empty_on();
						
						rt_thread_delay(rt_tick_from_millisecond(RELAY_ON_DELAY));
					}

					s_test_status.test_config.cr_test_config = test_cmd.test_config.cr_test_config;

					s_test_status.test_type     = TEST_TYPE_CR_TEST;
					s_test_status.test_status   = TEST_STATUS_ON;

					/* update content */
					rt_sem_take(g_sem_test_content, RT_WAITING_FOREVER);
					g_test_content.test_type   = TEST_TYPE_CR_TEST;
					g_test_content.test_status = TEST_STATUS_ON;
					rt_sem_release(g_sem_test_content);
					
					if (s_test_status.test_config.cr_test_config.test_category == TEST_CATEGORY_QC_20)
					{
						last_test_category = TEST_CATEGORY_QC_20;
						
						if (s_test_status.test_config.cr_test_config.voltage_level != last_voltage_level)
						{
							switch_to_qc_20_voltage_level(s_test_status.test_config.cr_test_config.voltage_level);

							last_voltage_level = s_test_status.test_config.cr_test_config.voltage_level;
						}
					}
					else if (s_test_status.test_config.cr_test_config.test_category == TEST_CATEGORY_MTK)
					{
						last_test_category = TEST_CATEGORY_MTK;
						
						if (s_test_status.test_config.cr_test_config.voltage_level != last_voltage_level)
						{
							switch_to_mtk_voltage_level(s_test_status.test_config.cr_test_config.voltage_level);

							last_voltage_level = s_test_status.test_config.cr_test_config.voltage_level;
						}
					}
					
					try_set_resist(last_voltage, s_test_status.test_config.cr_test_config.resist_val);
					
					/* assume relay is on */
					switch_enable();
				}

				s_test_status.test_flag = TEST_FLAG_FAIL;

				if (s_test_status.test_config.cr_test_config.duration == AUTOMATIC_TIME)
				{
					next_tick = rt_tick_get() + rt_tick_from_millisecond(AUTOMATIC_TEST_LIMIT);
				}
				else
				{
					next_tick = rt_tick_get() + rt_tick_from_millisecond(s_test_status.test_config.cr_test_config.duration);
				}
				
				sample_count = 0;
				
				break;

			case TEST_TYPE_EMPTY_LOAD_TEST:
				/* turn off empty relay to enable ac short detect */
				relay_empty_off();
				
				if (s_test_status.test_type == TEST_TYPE_EMPTY_LOAD_TEST)
				{
					TRACE("empty load test continue\n");
					
					/* still empty load test */
					s_test_status.test_config.empty_load_test_config = test_cmd.test_config.empty_load_test_config;
					
					s_test_status.test_status = TEST_STATUS_ON;

					/* update content */
					rt_sem_take(g_sem_test_content, RT_WAITING_FOREVER);
					g_test_content.test_type   = TEST_TYPE_EMPTY_LOAD_TEST;
					g_test_content.test_status = TEST_STATUS_ON;
					rt_sem_release(g_sem_test_content);
				}
				else
				{
					/* just start testing */
					switch_disable();
					switch_to_channel(EMPTY_CTRL_CHANNEL);

					control_set_voltage_duty(0);

					relay_load_off();

					TRACE("first start empty load test\n");

					s_test_status.test_config.empty_load_test_config = test_cmd.test_config.empty_load_test_config;
					
					s_test_status.test_type   = TEST_TYPE_EMPTY_LOAD_TEST;
					s_test_status.test_status = TEST_STATUS_ON;

					/* update content */
					rt_sem_take(g_sem_test_content, RT_WAITING_FOREVER);
					g_test_content.test_type   = TEST_TYPE_EMPTY_LOAD_TEST;
					g_test_content.test_status = TEST_STATUS_ON;
					rt_sem_release(g_sem_test_content);

					switch_enable();
				}

				if (s_test_status.test_config.empty_load_test_config.duration == AUTOMATIC_TIME)
				{
					next_tick = rt_tick_get() + rt_tick_from_millisecond(AUTOMATIC_TEST_LIMIT);
				}
				else
				{
					next_tick = rt_tick_get() + rt_tick_from_millisecond(s_test_status.test_config.empty_load_test_config.duration);
				}
			
				sample_count = 0;
				
				break;

			case TEST_TYPE_OVER_CURRENT_TEST:
				if (s_test_status.test_type == TEST_TYPE_OVER_CURRENT_TEST)
				{
					TRACE("over current test continue\n");
					
					/* still over current test */
					switch_disable();
					switch_to_channel(CC_CTRL_CHANNEL);
					
					cur_over_current = OVER_CURRENT_STEP;

					s_test_status.test_config.over_current_test_config = test_cmd.test_config.over_current_test_config;

					s_test_status.test_status   = TEST_STATUS_ON;
					
					/* update content */
					rt_sem_take(g_sem_test_content, RT_WAITING_FOREVER);
					g_test_content.test_type   = TEST_TYPE_OVER_CURRENT_TEST;
					g_test_content.test_status = TEST_STATUS_ON;
					rt_sem_release(g_sem_test_content);

					if (s_test_status.test_config.over_current_test_config.voltage_level == TEST_CATEGORY_QC_20)
					{
						last_test_category = TEST_CATEGORY_QC_20;
						
						if (s_test_status.test_config.over_current_test_config.voltage_level != last_voltage_level)
						{
							switch_to_qc_20_voltage_level(s_test_status.test_config.over_current_test_config.voltage_level);

							last_voltage_level = s_test_status.test_config.over_current_test_config.voltage_level;
						}
					}
					else if (s_test_status.test_config.over_current_test_config.voltage_level == TEST_CATEGORY_MTK)
					{
						last_test_category = TEST_CATEGORY_MTK;
						
						if (s_test_status.test_config.over_current_test_config.voltage_level != last_voltage_level)
						{
							switch_to_mtk_voltage_level(s_test_status.test_config.over_current_test_config.voltage_level);

							last_voltage_level = s_test_status.test_config.over_current_test_config.voltage_level;
						}
					}
					
					try_set_current(cur_over_current);

					switch_enable();
				}
				else
				{
					/* just start testing */
					switch_disable();
					switch_to_channel(CC_CTRL_CHANNEL);
					
					control_set_voltage_duty(0);

					if (s_test_status.test_type == TEST_TYPE_NONE
						|| s_test_status.test_type == TEST_TYPE_EMPTY_LOAD_TEST)
					{
						/* init status is no testing */
						TRACE("first over current test\n");

						relay_load_on();

						relay_empty_on();
						
						rt_thread_delay(rt_tick_from_millisecond(RELAY_ON_DELAY));
					}

					cur_over_current = OVER_CURRENT_STEP;

					s_test_status.test_config.over_current_test_config = test_cmd.test_config.over_current_test_config;

					s_test_status.test_type     = TEST_TYPE_OVER_CURRENT_TEST;
					s_test_status.test_status   = TEST_STATUS_ON;
					
					/* update content */
					rt_sem_take(g_sem_test_content, RT_WAITING_FOREVER);
					g_test_content.test_type   = TEST_TYPE_OVER_CURRENT_TEST;
					g_test_content.test_status = TEST_STATUS_ON;
					rt_sem_release(g_sem_test_content);
					
					if (s_test_status.test_config.over_current_test_config.voltage_level == TEST_CATEGORY_QC_20)
					{
						last_test_category = TEST_CATEGORY_QC_20;
						
						if (s_test_status.test_config.over_current_test_config.voltage_level != last_voltage_level)
						{
							switch_to_qc_20_voltage_level(s_test_status.test_config.over_current_test_config.voltage_level);

							last_voltage_level = s_test_status.test_config.over_current_test_config.voltage_level;
						}
					}
					else if (s_test_status.test_config.over_current_test_config.voltage_level == TEST_CATEGORY_MTK)
					{
						last_test_category = TEST_CATEGORY_MTK;
						
						if (s_test_status.test_config.over_current_test_config.voltage_level != last_voltage_level)
						{
							switch_to_mtk_voltage_level(s_test_status.test_config.over_current_test_config.voltage_level);

							last_voltage_level = s_test_status.test_config.over_current_test_config.voltage_level;
						}
					}
					
					try_set_current(cur_over_current);

					switch_enable();
				}
				
				next_tick = rt_tick_get() + rt_tick_from_millisecond(s_test_status.test_config.over_current_test_config.interval);
				
				sample_count = 0;
				
				break;

			case TEST_TYPE_SHORT_TEST:
				if (s_test_status.test_type == TEST_TYPE_SHORT_TEST)
				{
					TRACE("short test continue\n");
					
					/* still short test */
					switch_disable();
					switch_to_channel(SHORT_CTRL_CHANNEL);
					
					s_test_status.test_config.short_test_config = test_cmd.test_config.short_test_config;

					s_test_status.test_status = TEST_STATUS_ON;
					
					/* update content */
					rt_sem_take(g_sem_test_content, RT_WAITING_FOREVER);
					g_test_content.test_type   = TEST_TYPE_SHORT_TEST;
					g_test_content.test_status = TEST_STATUS_ON;
					rt_sem_release(g_sem_test_content);

					if (s_test_status.test_config.short_test_config.voltage_level == TEST_CATEGORY_QC_20)
					{
						last_test_category = TEST_CATEGORY_QC_20;
						
						if (s_test_status.test_config.short_test_config.voltage_level != last_voltage_level)
						{
							switch_to_qc_20_voltage_level(s_test_status.test_config.short_test_config.voltage_level);

							last_voltage_level = s_test_status.test_config.short_test_config.voltage_level;
						}
					}
					else if (s_test_status.test_config.short_test_config.voltage_level == TEST_CATEGORY_MTK)
					{
						last_test_category = TEST_CATEGORY_MTK;
						
						if (s_test_status.test_config.short_test_config.voltage_level != last_voltage_level)
						{
							switch_to_mtk_voltage_level(s_test_status.test_config.short_test_config.voltage_level);

							last_voltage_level = s_test_status.test_config.short_test_config.voltage_level;
						}
					}
					
					switch_enable();
				}
				else
				{
					/* just start testing */
					switch_disable();
					switch_to_channel(SHORT_CTRL_CHANNEL);
					
					control_set_voltage_duty(0);

					if (s_test_status.test_type == TEST_TYPE_NONE
						|| s_test_status.test_type == TEST_TYPE_EMPTY_LOAD_TEST)
					{
						/* init status is no testing */
						TRACE("first short test\n");

						relay_load_on();

						relay_empty_on();
						
						rt_thread_delay(rt_tick_from_millisecond(RELAY_ON_DELAY));
					}

					s_test_status.test_config.short_test_config = test_cmd.test_config.short_test_config;

					s_test_status.test_type   = TEST_TYPE_SHORT_TEST;
					s_test_status.test_status = TEST_STATUS_ON;
					
					/* update content */
					rt_sem_take(g_sem_test_content, RT_WAITING_FOREVER);
					g_test_content.test_type   = TEST_TYPE_SHORT_TEST;
					g_test_content.test_status = TEST_STATUS_ON;
					rt_sem_release(g_sem_test_content);
					
					if (s_test_status.test_config.short_test_config.voltage_level == TEST_CATEGORY_QC_20)
					{
						last_test_category = TEST_CATEGORY_QC_20;
						
						if (s_test_status.test_config.short_test_config.voltage_level != last_voltage_level)
						{
							switch_to_qc_20_voltage_level(s_test_status.test_config.short_test_config.voltage_level);

							last_voltage_level = s_test_status.test_config.short_test_config.voltage_level;
						}
					}
					else if (s_test_status.test_config.short_test_config.voltage_level == TEST_CATEGORY_MTK)
					{
						last_test_category = TEST_CATEGORY_MTK;
						
						if (s_test_status.test_config.short_test_config.voltage_level != last_voltage_level)
						{
							switch_to_mtk_voltage_level(s_test_status.test_config.short_test_config.voltage_level);

							last_voltage_level = s_test_status.test_config.short_test_config.voltage_level;
						}
					}

					switch_enable();
				}

				s_test_status.test_flag = TEST_FLAG_FAIL;

				if (s_test_status.test_config.short_test_config.duration == AUTOMATIC_TIME)
				{
					next_tick = rt_tick_get() + rt_tick_from_millisecond(AUTOMATIC_TEST_LIMIT);
				}
				else
				{
					next_tick = rt_tick_get() + rt_tick_from_millisecond(s_test_status.test_config.short_test_config.duration);
				}
				
				sample_count = 0;
				
				break;

			case TEST_TYPE_DISCHARGE_TEST:
				relay_ac_off();
				TRACE("turn off ac relay\n");
			
				if (s_test_status.test_type == TEST_TYPE_DISCHARGE_TEST)
				{
					TRACE("discharge test continue\n");
					
					/* still discharge test */
					s_test_status.test_config.discharge_test_config = test_cmd.test_config.discharge_test_config;
					
					try_set_current(s_test_status.test_config.discharge_test_config.current_val);
					
					s_test_status.test_status = TEST_STATUS_ON;
				}
				else
				{
					/* just start testing */
					switch_disable();
					switch_to_channel(CC_CTRL_CHANNEL);
					
					control_set_voltage_duty(0);

					if (s_test_status.test_type == TEST_TYPE_NONE
						|| s_test_status.test_type == TEST_TYPE_EMPTY_LOAD_TEST)
					{
						/* init status is no testing */
						TRACE("first discharge test\n");

						relay_load_on();

						relay_empty_on();
						
						rt_thread_delay(rt_tick_from_millisecond(RELAY_ON_DELAY));
					}

					s_test_status.test_config.discharge_test_config = test_cmd.test_config.discharge_test_config;

					s_test_status.test_type   = TEST_TYPE_DISCHARGE_TEST;
					s_test_status.test_status = TEST_STATUS_ON;
					
					/* update content */
					rt_sem_take(g_sem_test_content, RT_WAITING_FOREVER);
					g_test_content.test_type   = TEST_TYPE_DISCHARGE_TEST;
					g_test_content.test_status = TEST_STATUS_ON;
					rt_sem_release(g_sem_test_content);
					
					try_set_current(s_test_status.test_config.discharge_test_config.current_val);
					
					switch_enable();

					TRACE("duration:%d, current:%d\n", s_test_status.test_config.discharge_test_config.duration,
							s_test_status.test_config.discharge_test_config.current_val);
				}
				
				next_tick = rt_tick_get() + rt_tick_from_millisecond(s_test_status.test_config.discharge_test_config.duration);
				
				sample_count = 0;
				
				break;
				
			case TEST_TYPE_NONE:
				if (s_test_status.test_type != TEST_TYPE_NONE)
				{
					TRACE("testing, now stop\n");
					
					/* just stop testing */
					switch_disable();
					switch_to_channel(EMPTY_CTRL_CHANNEL);
					switch_enable();
					
					s_duty = 0;
					control_set_current_duty(s_duty);
					control_set_voltage_duty(s_duty);
					
					relay_load_off();
				}

				if (last_test_category == TEST_CATEGORY_QC_20)
				{
					/* restore to default voltage level */
					switch_to_qc_20_5v_level();

					last_voltage_level = TEST_VOLTAGE_LEVEL_5V;
				}
				else
				{

				}
				
				s_test_status.test_type  = TEST_TYPE_NONE;
				s_test_status.test_status  = TEST_STATUS_IDLE;
				
				sample_count = 0;
				
				/* update content */
				rt_sem_take(g_sem_test_content, RT_WAITING_FOREVER);
				g_test_content.test_type = TEST_TYPE_NONE;
				g_test_content.test_status = TEST_STATUS_IDLE;
				rt_sem_release(g_sem_test_content);

				relay_empty_off();
				
				relay_ac_on();
				TRACE("turn on ac relay\n");
				
				break;
			
			default:
				
				break;
			}
		}
		
		rt_thread_delay(rt_tick_from_millisecond(SAMPLE_INTERVAL));
		
		/* first sample voltage */	
		adc_val = meter_get_voltage_chn_val();
		
		if (sample_count == 0)
		{
			voltage_min = adc_val;
			voltage_max = adc_val;
			
			voltage = adc_val;
		}
		else
		{
			if (voltage_min > adc_val)
			{
				voltage_min = adc_val;
			}
			
			if (voltage_max < adc_val)
			{
				voltage_max = adc_val;
			}
			
			voltage += adc_val;
		}

		/* second sample current */
		adc_val = meter_get_current_chn_val();
		if (sample_count == 0)
		{
			current_min = adc_val;
			current_max = adc_val;
			
			current = adc_val;
		}
		else
		{
			if (current_min > adc_val)
			{
				current_min = adc_val;
			}
			
			if (current_max < adc_val)
			{
				current_max = adc_val;
			}
			
			current += adc_val;
		}

		/* sample ac */
		adc_val = meter_get_ac_chn_val();
		if (sample_count == 0)
		{
			ac_min = adc_val;
			ac_max = adc_val;

			ac = adc_val;
		}
		else
		{
			if (ac_min > adc_val)
			{
				ac_min = adc_val;
			}

			if (ac_max < adc_val)
			{
				ac_max = adc_val;
			}

			ac += adc_val;
		}
		
		sample_count++;
		
		if (sample_count == SAMPLE_COUNT)
		{
			sample_count = 0;
			
			/* get voltage value */
			voltage -= (voltage_min + voltage_max);	
			voltage /= (SAMPLE_COUNT - 2);
			
			voltage = adc_to_voltage_val(voltage);

			last_voltage = voltage;
	
			/* get current value */
			current -= (current_min + current_max);
			current /= (SAMPLE_COUNT - 2);

			current = adc_to_current_val(current);
			
			/* get ac value */
			ac -= (ac_min + ac_max);
			ac /= (SAMPLE_COUNT - 2);

			/* uA */
			ac = adc_to_ac_val(ac);
			
			/* update content */
			RT_ASSERT(g_sem_test_content != RT_NULL);
	
			rt_sem_take(g_sem_test_content, RT_WAITING_FOREVER);
			g_test_content.voltage = voltage;
			g_test_content.current = current;
			g_test_content.ac_current = ac;
			rt_sem_release(g_sem_test_content);

			TRACE("type:%d, voltage:%d, current:%d, ac:%d, status:%d\n", g_test_content.test_type,
						g_test_content.voltage, g_test_content.current, 
						g_test_content.ac_current, g_test_content.test_status);
						
			adjust_voltage_current(voltage, current);

			/* adjust tick */
			switch (g_test_content.test_type)
			{
			case TEST_TYPE_CV_TEST:
				if (g_test_content.test_status == TEST_STATUS_ON)
				{
					if (s_test_status.test_config.cv_test_config.duration == AUTOMATIC_TIME)
					{
						if ((rt_tick_get() - next_tick) < RT_TICK_MAX / 2)
						{
							/* time is up */
							control_set_voltage_duty(0);
							
							switch_disable();
							switch_to_channel(EMPTY_CTRL_CHANNEL);
							switch_enable();

							rt_sem_take(g_sem_test_content, RT_WAITING_FOREVER);
							g_test_content.test_status = TEST_STATUS_ABNORMAL;
							rt_sem_release(g_sem_test_content);

							TRACE("cv test failed\n");
							TRACE("current lower:%d, current upper:%d, ac upper:%d\n", s_test_status.test_config.cv_test_config.current_lower,
										s_test_status.test_config.cv_test_config.current_upper, s_test_status.test_config.cv_test_config.ac_upper);
						}
						else
						{
							if (g_test_content.ac_current <= s_test_status.test_config.cv_test_config.ac_upper
								&& g_test_content.current <= s_test_status.test_config.cv_test_config.current_upper
								&& g_test_content.current >= s_test_status.test_config.cv_test_config.current_lower)
							{
								control_set_voltage_duty(0);
							
								switch_disable();
								switch_to_channel(EMPTY_CTRL_CHANNEL);
								switch_enable();

								rt_sem_take(g_sem_test_content, RT_WAITING_FOREVER);
								g_test_content.test_status = TEST_STATUS_NORMAL;
								rt_sem_release(g_sem_test_content);
								
								TRACE("cv test OK, stopped\n");
							}
						}
					}
					else
					{
						if ((rt_tick_get() - next_tick) < RT_TICK_MAX / 2)
						{
							/* time is up, stop test */
							if (s_test_status.test_flag == TEST_FLAG_OK)
							{
								control_set_voltage_duty(0);
								
								switch_disable();
								switch_to_channel(EMPTY_CTRL_CHANNEL);
								switch_enable();

								rt_sem_take(g_sem_test_content, RT_WAITING_FOREVER);
								g_test_content.test_status = TEST_STATUS_NORMAL;
								rt_sem_release(g_sem_test_content);
								
								TRACE("cv test OK, stopped\n");
							}
							else
							{
								control_set_voltage_duty(0);
								
								switch_disable();
								switch_to_channel(EMPTY_CTRL_CHANNEL);
								switch_enable();

								rt_sem_take(g_sem_test_content, RT_WAITING_FOREVER);
								g_test_content.test_status = TEST_STATUS_ABNORMAL;
								rt_sem_release(g_sem_test_content);

								TRACE("cv test failed\n");
								TRACE("current lower:%d, current upper:%d, ac upper:%d\n", s_test_status.test_config.cv_test_config.current_lower,
											s_test_status.test_config.cv_test_config.current_upper, s_test_status.test_config.cv_test_config.ac_upper);
							}
						}
						else
						{
							if (g_test_content.ac_current <= s_test_status.test_config.cv_test_config.ac_upper
								&& g_test_content.current <= s_test_status.test_config.cv_test_config.current_upper
								&& g_test_content.current >= s_test_status.test_config.cv_test_config.current_lower)
							{
								s_test_status.test_flag = TEST_FLAG_OK;
							}
						}
					}	
				}

				break;

			case TEST_TYPE_CC_TEST:
				if (g_test_content.test_status == TEST_STATUS_ON)
				{
					if (s_test_status.test_config.cc_test_config.duration == AUTOMATIC_TIME)
					{
						if ((rt_tick_get() - next_tick) < RT_TICK_MAX / 2)
						{
							/* time is up */
							control_set_current_duty(0);
							
							switch_disable();
							switch_to_channel(EMPTY_CTRL_CHANNEL);
							switch_enable();

							rt_sem_take(g_sem_test_content, RT_WAITING_FOREVER);
							g_test_content.test_status = TEST_STATUS_ABNORMAL;
							rt_sem_release(g_sem_test_content);

							TRACE("cc test failed\n");
							TRACE("voltage lower:%d, voltage upper:%d, ac upper:%d\n", s_test_status.test_config.cc_test_config.voltage_lower,
										s_test_status.test_config.cc_test_config.voltage_upper, s_test_status.test_config.cc_test_config.ac_upper);
						}
						else
						{
							if (g_test_content.ac_current <= s_test_status.test_config.cc_test_config.ac_upper
							&& g_test_content.voltage <= s_test_status.test_config.cc_test_config.voltage_upper
							&& g_test_content.voltage >= s_test_status.test_config.cc_test_config.voltage_lower)
							{
								control_set_current_duty(0);
							
								switch_disable();
								switch_to_channel(EMPTY_CTRL_CHANNEL);
								switch_enable();

								rt_sem_take(g_sem_test_content, RT_WAITING_FOREVER);
								g_test_content.test_status = TEST_STATUS_NORMAL;
								rt_sem_release(g_sem_test_content);

								TRACE("cc test OK, stopped\n");		
							}
						}
					}
					else
					{		
						if ((rt_tick_get() - next_tick) < RT_TICK_MAX / 2)
						{
							/* time is up, stop test */
							if (s_test_status.test_flag == TEST_FLAG_OK)
							{
								control_set_current_duty(0);
								
								switch_disable();
								switch_to_channel(EMPTY_CTRL_CHANNEL);
								switch_enable();

								rt_sem_take(g_sem_test_content, RT_WAITING_FOREVER);
								g_test_content.test_status = TEST_STATUS_NORMAL;
								rt_sem_release(g_sem_test_content);

								TRACE("cc test OK, stopped\n");
							}
							else
							{
								control_set_current_duty(0);
								
								switch_disable();
								switch_to_channel(EMPTY_CTRL_CHANNEL);
								switch_enable();

								rt_sem_take(g_sem_test_content, RT_WAITING_FOREVER);
								g_test_content.test_status = TEST_STATUS_ABNORMAL;
								rt_sem_release(g_sem_test_content);

								TRACE("cc test failed\n");
								TRACE("voltage lower:%d, voltage upper:%d, ac upper:%d\n", s_test_status.test_config.cc_test_config.voltage_lower,
											s_test_status.test_config.cc_test_config.voltage_upper, s_test_status.test_config.cc_test_config.ac_upper);
							}
						}
						else
						{
							if (g_test_content.ac_current <= s_test_status.test_config.cc_test_config.ac_upper
								&& g_test_content.voltage <= s_test_status.test_config.cc_test_config.voltage_upper
								&& g_test_content.voltage >= s_test_status.test_config.cc_test_config.voltage_lower)
							{
								s_test_status.test_flag = TEST_FLAG_OK;			
							}
						}
					}
				}

				break;
				
			case TEST_TYPE_CR_TEST:
				if (g_test_content.test_status == TEST_STATUS_ON)
				{
					if (s_test_status.test_config.cr_test_config.duration == AUTOMATIC_TIME)
					{
						if ((rt_tick_get() - next_tick) < RT_TICK_MAX / 2)
						{
							/* time is up, stop test */
							control_set_current_duty(0);
								
							switch_disable();
							switch_to_channel(EMPTY_CTRL_CHANNEL);
							switch_enable();

							rt_sem_take(g_sem_test_content, RT_WAITING_FOREVER);
							g_test_content.test_status = TEST_STATUS_ABNORMAL;
							rt_sem_release(g_sem_test_content);

							TRACE("cr test failed\n");
							TRACE("voltage lower:%d, voltage upper:%d, current lower:%d, current upper:%d, ac upper:%d\n", 
									s_test_status.test_config.cr_test_config.voltage_lower, s_test_status.test_config.cr_test_config.voltage_upper, 
									s_test_status.test_config.cr_test_config.current_lower, s_test_status.test_config.cr_test_config.current_upper,
									s_test_status.test_config.cr_test_config.ac_upper);
						}
						else
						{
							if (g_test_content.ac_current <= s_test_status.test_config.cr_test_config.ac_upper
								&& g_test_content.voltage <= s_test_status.test_config.cr_test_config.voltage_upper
								&& g_test_content.voltage >= s_test_status.test_config.cr_test_config.voltage_lower
								&& g_test_content.current <= s_test_status.test_config.cr_test_config.current_upper
								&& g_test_content.current >= s_test_status.test_config.cr_test_config.current_lower)
							{
								control_set_current_duty(0);
								
								switch_disable();
								switch_to_channel(EMPTY_CTRL_CHANNEL);
								switch_enable();

								rt_sem_take(g_sem_test_content, RT_WAITING_FOREVER);
								g_test_content.test_status = TEST_STATUS_NORMAL;
								rt_sem_release(g_sem_test_content);

								TRACE("cr test OK, stopped\n");
							}
						}
					}
					else
					{
						if ((rt_tick_get() - next_tick) < RT_TICK_MAX / 2)
						{
							/* time is up, stop test */
							if (s_test_status.test_flag == TEST_FLAG_OK)
							{
								control_set_current_duty(0);
									
								switch_disable();
								switch_to_channel(EMPTY_CTRL_CHANNEL);
								switch_enable();

								rt_sem_take(g_sem_test_content, RT_WAITING_FOREVER);
								g_test_content.test_status = TEST_STATUS_NORMAL;
								rt_sem_release(g_sem_test_content);

								TRACE("cr test OK, stopped\n");
							}
							else
							{
								control_set_current_duty(0);
									
								switch_disable();
								switch_to_channel(EMPTY_CTRL_CHANNEL);
								switch_enable();

								rt_sem_take(g_sem_test_content, RT_WAITING_FOREVER);
								g_test_content.test_status = TEST_STATUS_ABNORMAL;
								rt_sem_release(g_sem_test_content);

								TRACE("cr test failed\n");
								TRACE("voltage lower:%d, voltage upper:%d, current lower:%d, current upper:%d, ac upper:%d\n", 
										s_test_status.test_config.cr_test_config.voltage_lower, s_test_status.test_config.cr_test_config.voltage_upper, 
										s_test_status.test_config.cr_test_config.current_lower, s_test_status.test_config.cr_test_config.current_upper,
										s_test_status.test_config.cr_test_config.ac_upper);
							}
						}
						else
						{
							if (g_test_content.ac_current <= s_test_status.test_config.cr_test_config.ac_upper
								&& g_test_content.voltage <= s_test_status.test_config.cr_test_config.voltage_upper
								&& g_test_content.voltage >= s_test_status.test_config.cr_test_config.voltage_lower
								&& g_test_content.current <= s_test_status.test_config.cr_test_config.current_upper
								&& g_test_content.current >= s_test_status.test_config.cr_test_config.current_lower)
							{
								s_test_status.test_flag = TEST_FLAG_OK;
							}
						}
					}
				}
				
				break;
				
			case TEST_TYPE_EMPTY_LOAD_TEST:
				if (g_test_content.test_status == TEST_STATUS_ON)
				{
					if (s_test_status.test_config.empty_load_test_config.duration == AUTOMATIC_TIME)
					{
						if ((rt_tick_get() - next_tick) < RT_TICK_MAX / 2)
						{
							/* time is up, stop test */
							rt_sem_take(g_sem_test_content, RT_WAITING_FOREVER);
							g_test_content.test_status = TEST_STATUS_ABNORMAL;
							rt_sem_release(g_sem_test_content);
							
							TRACE("empty load test failed\n");
							TRACE("voltage lower:%d, voltage upper:%d, ac upper:%d\n", s_test_status.test_config.empty_load_test_config.voltage_lower,
										s_test_status.test_config.empty_load_test_config.voltage_upper, s_test_status.test_config.empty_load_test_config.ac_upper);
						}
						else 
						{
							if (g_test_content.ac_current <= s_test_status.test_config.empty_load_test_config.ac_upper
								&& g_test_content.voltage <= s_test_status.test_config.empty_load_test_config.voltage_upper
								&& g_test_content.voltage >= s_test_status.test_config.empty_load_test_config.voltage_lower)
							{
								rt_sem_take(g_sem_test_content, RT_WAITING_FOREVER);
								g_test_content.test_status = TEST_STATUS_NORMAL;
								rt_sem_release(g_sem_test_content);
								
								TRACE("empty load test OK, stopped\n");
							}
						}
					}
					else
					{
						if ((rt_tick_get() - next_tick) < RT_TICK_MAX / 2)
						{
							/* time is up, stop test */
							if (s_test_status.test_flag == TEST_FLAG_OK)
							{
								rt_sem_take(g_sem_test_content, RT_WAITING_FOREVER);
								g_test_content.test_status = TEST_STATUS_NORMAL;
								rt_sem_release(g_sem_test_content);
								
								TRACE("empty load test OK, stopped\n");
							}
							else
							{
								rt_sem_take(g_sem_test_content, RT_WAITING_FOREVER);
								g_test_content.test_status = TEST_STATUS_ABNORMAL;
								rt_sem_release(g_sem_test_content);
								
								TRACE("empty load test failed\n");
								TRACE("voltage lower:%d, voltage upper:%d, ac upper:%d\n", s_test_status.test_config.empty_load_test_config.voltage_lower,
											s_test_status.test_config.empty_load_test_config.voltage_upper, s_test_status.test_config.empty_load_test_config.ac_upper);
							}	
						}
						else
						{
							if (g_test_content.ac_current <= s_test_status.test_config.empty_load_test_config.ac_upper
									&& g_test_content.voltage <= s_test_status.test_config.empty_load_test_config.voltage_upper
									&& g_test_content.voltage >= s_test_status.test_config.empty_load_test_config.voltage_lower)
							{
								s_test_status.test_flag = TEST_FLAG_OK;
							}
						}
					}
				}

				break;
				
			case TEST_TYPE_OVER_CURRENT_TEST:
				if (g_test_content.test_status == TEST_STATUS_ON)
				{
					if ((rt_tick_get() - next_tick) < RT_TICK_MAX / 2)
					{
						/* interval is up, increase current by step */
						if (cur_over_current + OVER_CURRENT_STEP > s_test_status.test_config.over_current_test_config.current_upper)
						{
							control_set_current_duty(0);
							
							switch_disable();
							switch_to_channel(EMPTY_CTRL_CHANNEL);
							switch_enable();

							rt_sem_take(g_sem_test_content, RT_WAITING_FOREVER);
							g_test_content.test_status = TEST_STATUS_ABNORMAL;
							rt_sem_release(g_sem_test_content);						

							TRACE("over current test exceeds upper current, current set:%d, upper current:%d\n",
									cur_over_current,
									s_test_status.test_config.over_current_test_config.current_upper);
						}
						else
						{
							if (g_test_content.ac_current < s_test_status.test_config.over_current_test_config.ac_upper)
							{
								uint32_t current1, current2;

								current1 = g_test_content.current;
								current2 = cur_over_current;
								
								if (current1 > current2)
								{
									current1 = cur_over_current;
									current2 = g_test_content.current;
								}

								if ((current2 - current1) * 100 >= current2 * 70)
								{
									/* actual current is enough smaller than set */
									control_set_current_duty(0);
									
									switch_disable();
									switch_to_channel(EMPTY_CTRL_CHANNEL);
									switch_enable();

									rt_sem_take(g_sem_test_content, RT_WAITING_FOREVER);
									g_test_content.test_status = TEST_STATUS_NORMAL;
									rt_sem_release(g_sem_test_content);

									TRACE("over current test ok, current:%d, upper current:%d\n",
											g_test_content.current, s_test_status.test_config.over_current_test_config.current_upper);
								}
								else
								{
									g_over_current_test_result.over_current_test_current = g_test_content.current;
									g_over_current_test_result.over_current_test_voltage = g_test_content.voltage;
									g_over_current_test_result.over_current_test_ac      = g_test_content.ac_current;

									TRACE("g_over_current_test_result.over_current_test_current:%d\n", g_over_current_test_result.over_current_test_current);
									
									cur_over_current += OVER_CURRENT_STEP;
									try_set_current(cur_over_current);

									TRACE("set current:%d\n", cur_over_current);
								}
							}
							else
							{
								control_set_current_duty(0);
								
								switch_disable();
								switch_to_channel(EMPTY_CTRL_CHANNEL);
								switch_enable();

								rt_sem_take(g_sem_test_content, RT_WAITING_FOREVER);
								g_test_content.test_status = TEST_STATUS_ABNORMAL;
								rt_sem_release(g_sem_test_content);
								
								TRACE("over current test failed. ac:%d, upper ac:%d\n", g_test_content.ac_current,
										s_test_status.test_config.over_current_test_config.ac_upper);
							}
						}
					}
					else
					{
						if (g_test_content.ac_current < s_test_status.test_config.over_current_test_config.ac_upper)
						{
							uint32_t current1, current2;

							current1 = g_test_content.current;
							current2 = cur_over_current;
								
							if (current1 > current2)
							{
								current1 = cur_over_current;
								current2 = g_test_content.current;
							}

							if ((current2 - current1) * 100 / current2 >= 70)
							{
								/* actual current is smalled enough than set */
								control_set_current_duty(0);
									
								switch_disable();
								switch_to_channel(EMPTY_CTRL_CHANNEL);
								switch_enable();

								rt_sem_take(g_sem_test_content, RT_WAITING_FOREVER);
								g_test_content.test_status = TEST_STATUS_NORMAL;
								rt_sem_release(g_sem_test_content);
								

								TRACE("over current test ok, current:%d, upper current:%d\n",
											g_test_content.current, s_test_status.test_config.over_current_test_config.current_upper);
							}
							else
							{
								g_over_current_test_result.over_current_test_current = g_test_content.current;
								g_over_current_test_result.over_current_test_voltage = g_test_content.voltage;
								g_over_current_test_result.over_current_test_ac      = g_test_content.ac_current;

								TRACE("g_over_current_test_result.over_current_test_current:%d\n", g_over_current_test_result.over_current_test_current);
							}
						}
						else
						{
							control_set_current_duty(0);
								
							switch_disable();
							switch_to_channel(EMPTY_CTRL_CHANNEL);
							switch_enable();

							rt_sem_take(g_sem_test_content, RT_WAITING_FOREVER);
							g_test_content.test_status = TEST_STATUS_ABNORMAL;
							rt_sem_release(g_sem_test_content);
	
							TRACE("over current test failed. ac:%d, upper ac:%d\n", g_test_content.ac_current,
										s_test_status.test_config.over_current_test_config.ac_upper);
						}
					}
				}

				break;
				
			case TEST_TYPE_SHORT_TEST:
				if (g_test_content.test_status == TEST_STATUS_ON)
				{
					if (s_test_status.test_config.short_test_config.duration == AUTOMATIC_TIME)
					{
						if ((rt_tick_get() - next_tick) < RT_TICK_MAX / 2)
						{
							/* time is up, stop test */
							control_set_current_duty(0);
							
							switch_disable();
							switch_to_channel(EMPTY_CTRL_CHANNEL);
							switch_enable();

							rt_sem_take(g_sem_test_content, RT_WAITING_FOREVER);
							g_test_content.test_status = TEST_STATUS_ABNORMAL;
							rt_sem_release(g_sem_test_content);

							TRACE("short test failed. ac:%d, upper ac:%d, current:%d, upper current:%d\n", 
									g_test_content.ac_current, s_test_status.test_config.over_current_test_config.ac_upper,
									g_test_content.current, s_test_status.test_config.short_test_config.current_upper);			
						}
						else
						{
							if (g_test_content.ac_current <= s_test_status.test_config.short_test_config.ac_upper
								&& g_test_content.current <= s_test_status.test_config.short_test_config.current_upper)
							{
								control_set_current_duty(0);
							
								switch_disable();
								switch_to_channel(EMPTY_CTRL_CHANNEL);
								switch_enable();

								rt_sem_take(g_sem_test_content, RT_WAITING_FOREVER);
								g_test_content.test_status = TEST_STATUS_NORMAL;
								rt_sem_release(g_sem_test_content);

								TRACE("short test OK, stopped\n");			
							}
						}
					}
					else
					{
						if ((rt_tick_get() - next_tick) < RT_TICK_MAX / 2)
						{
							/* time is up, stop test */
							if (s_test_status.test_flag == TEST_FLAG_OK)
							{
								control_set_current_duty(0);
								
								switch_disable();
								switch_to_channel(EMPTY_CTRL_CHANNEL);
								switch_enable();

								rt_sem_take(g_sem_test_content, RT_WAITING_FOREVER);
								g_test_content.test_status = TEST_STATUS_NORMAL;
								rt_sem_release(g_sem_test_content);

								TRACE("short test OK, stopped\n");
							}
							else
							{
								control_set_current_duty(0);
								
								switch_disable();
								switch_to_channel(EMPTY_CTRL_CHANNEL);
								switch_enable();

								rt_sem_take(g_sem_test_content, RT_WAITING_FOREVER);
								g_test_content.test_status = TEST_STATUS_ABNORMAL;
								rt_sem_release(g_sem_test_content);

								TRACE("short test failed. ac:%d, upper ac:%d, current:%d, upper current:%d\n", 
										g_test_content.ac_current, s_test_status.test_config.over_current_test_config.ac_upper,
										g_test_content.current, s_test_status.test_config.short_test_config.current_upper);
							}
						}
						else
						{
							if (g_test_content.ac_current <= s_test_status.test_config.short_test_config.ac_upper
								&& g_test_content.current <= s_test_status.test_config.short_test_config.current_upper)
							{
								s_test_status.test_flag = TEST_FLAG_OK;			
							}
						}
					}	
				}

				break;
				
			case TEST_TYPE_DISCHARGE_TEST:
				if (g_test_content.test_status == TEST_STATUS_ON)
				{
					if ((rt_tick_get() - next_tick) < RT_TICK_MAX / 2)
					{
						/* time is up, stop test */
						control_set_current_duty(0);
						
						switch_disable();
						switch_to_channel(EMPTY_CTRL_CHANNEL);
						switch_enable();

						relay_load_off();

						relay_empty_off();

						rt_sem_take(g_sem_test_content, RT_WAITING_FOREVER);
						g_test_content.test_status = TEST_STATUS_NORMAL;
						rt_sem_release(g_sem_test_content);
							
						TRACE("discharge test stopped\n");
					}
				}
				
				break;
			}
		}
	}
}

void start_work_thread(void)
{
	rt_thread_t tid;
	
	tid = rt_thread_create("work", work_thread_entry, RT_NULL, 512, WORK_THREAD_PRIORITY, 10);

	RT_ASSERT(tid != RT_NULL);
	rt_thread_startup(tid);
}

