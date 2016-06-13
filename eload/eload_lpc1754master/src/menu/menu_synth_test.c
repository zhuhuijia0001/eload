#include <stdint.h>
#include <rtthread.h>

#include "type.h"
#include "key_define.h"

#include "app_cfg.h"

#include "menu_op.h"
#include "menu.h"

#include "lcd.h"
#include "draw.h"

#include "beeper.h"

#include "led.h"

#include "trace.h"

#include "global.h"

#include "packet.h"

#include "msg_thread.h"
#include "com_thread.h"

#define  QUERY_CONTENT_INTERVAL      20

#define  QUERY_DEVICE_ON_INTERVAL      500

#define  EMPTY_LOAD_VOLTAGE_THREASHOULD   500

static const SYNTH_TEST_SETTING *s_synth_test_setting = NULL;

static const QC_20_TEST_SETTING *s_qc_20_test_setting = NULL;

//static const MTK_TEST_SETTING *s_mtk_test_setting = NULL;

extern const SYNTH_TEST_SETTING *get_synth_test_setting(void);

extern const QC_20_TEST_SETTING *get_qc_20_test_setting(void);

extern int get_test_group(void);

extern TEST_CATEGORY get_cur_test_category(void);


/* thread to run test */
static rt_thread_t s_test_thread = RT_NULL;

static TEST_RESULT s_test_result;

static PHONE_NUMBER_SETTING s_phone_number_setting;

static OPTION_ON_OFF s_channel_set[CHANNEL_COUNT];

static TEST_CATEGORY s_cur_test_category;

static void key_handler(void *msg)
{
	key_t key_msg = (key_t)(uint32_t)msg;
	uint8_t key = KEY_VALUE(key_msg);
	
	if (KEY_TYPE(key_msg) == MASK_KEY_RELEASE)
	{
		return;
	}

	if (KEY_TYPE(key_msg) != MASK_KEY_PRESS && (key == KEY_OK || key == KEY_CANCEL))
	{
		return;
	}
	
	beeper_beep(BEEPER_VOL_LOW, 50, 50, 1);

	if (key == KEY_CANCEL)
	{	
		RT_ASSERT(s_test_thread != RT_NULL);
		rt_thread_delete(s_test_thread);
		s_test_thread = RT_NULL;

		rt_thread_delay(rt_tick_from_millisecond(QUERY_CONTENT_INTERVAL));

		/* turn off led to avoid interrupt */
		all_pass_led_off();
		all_fail_led_off();
		
		TEST_CMD test_cmd;
		/* notify to stop test */
		test_cmd.channel   = SLAVE_PORT_ALL;
		test_cmd.test_type = TEST_TYPE_NONE;
		
		test_cmd_notify(&test_cmd);	
		
		switch_to_menu(MENU_ID_SYNTH_TEST_SETTING);
	}
}

static void draw_synth_test_step_empty_load_result(const TEST_RESULT *synth_test_result)
{
	draw_synth_test_step_1_ac(synth_test_result->test_content.ac_current);
		
	draw_synth_test_step_1_voltage(measure_to_actual_voltage((int)synth_test_result->test_content.channel, synth_test_result->test_content.voltage));

	if (synth_test_result->test_content.test_status == TEST_STATUS_NORMAL)
	{
		draw_synth_test_step_1_OK();
	}
	else if (synth_test_result->test_content.test_status == TEST_STATUS_ABNORMAL)
	{
		draw_synth_test_step_1_fail();
	}
}

static void draw_synth_test_step_2_result(const TEST_RESULT *synth_test_result)
{
	if (synth_test_result->test_content.test_type == TEST_TYPE_CV_TEST
		|| synth_test_result->test_content.test_type == TEST_TYPE_CC_TEST
		|| synth_test_result->test_content.test_type == TEST_TYPE_CR_TEST)
	{
		draw_synth_test_step_2_ac(synth_test_result->test_content.ac_current);
		
		draw_synth_test_step_2_voltage(measure_to_actual_voltage((int)synth_test_result->test_content.channel, synth_test_result->test_content.voltage));
		
		draw_synth_test_step_2_current(measure_to_actual_current((int)synth_test_result->test_content.channel, synth_test_result->test_content.current));
	}
	else if (synth_test_result->test_content.test_type == TEST_TYPE_OVER_CURRENT_TEST)
	{
		draw_synth_test_step_2_ac(synth_test_result->test_content.ac_current);

		draw_synth_test_step_2_oc(measure_to_actual_current((int)synth_test_result->test_content.channel, synth_test_result->test_content.current));
	}
	else if (synth_test_result->test_content.test_type == TEST_TYPE_SHORT_TEST)
	{
		draw_synth_test_step_2_ac(synth_test_result->test_content.ac_current);

		draw_synth_test_step_2_short(measure_to_actual_current((int)synth_test_result->test_content.channel, synth_test_result->test_content.current));
	}


	if (synth_test_result->test_content.test_status == TEST_STATUS_NORMAL)
	{
		draw_synth_test_step_2_OK();
	}
	else if (synth_test_result->test_content.test_status == TEST_STATUS_ABNORMAL)
	{
		draw_synth_test_step_2_fail();
	}
}

static void draw_synth_test_step_3_result(const TEST_RESULT *synth_test_result)
{
	if (synth_test_result->test_content.test_type == TEST_TYPE_CV_TEST
		|| synth_test_result->test_content.test_type == TEST_TYPE_CC_TEST
		|| synth_test_result->test_content.test_type == TEST_TYPE_CR_TEST)
	{
		draw_synth_test_step_3_ac(synth_test_result->test_content.ac_current);
		
		draw_synth_test_step_3_voltage(measure_to_actual_voltage((int)synth_test_result->test_content.channel, synth_test_result->test_content.voltage));
		
		draw_synth_test_step_3_current(measure_to_actual_current((int)synth_test_result->test_content.channel, synth_test_result->test_content.current));
	}
	else if (synth_test_result->test_content.test_type == TEST_TYPE_OVER_CURRENT_TEST)
	{
		draw_synth_test_step_3_ac(synth_test_result->test_content.ac_current);

		draw_synth_test_step_3_oc(measure_to_actual_current((int)synth_test_result->test_content.channel, synth_test_result->test_content.current));
	}
	else if (synth_test_result->test_content.test_type == TEST_TYPE_SHORT_TEST)
	{
		draw_synth_test_step_3_ac(synth_test_result->test_content.ac_current);

		draw_synth_test_step_3_short(measure_to_actual_current((int)synth_test_result->test_content.channel, synth_test_result->test_content.current));
	}

	if (synth_test_result->test_content.test_status == TEST_STATUS_NORMAL)
	{
		draw_synth_test_step_3_OK();
	}
	else if (synth_test_result->test_content.test_status == TEST_STATUS_ABNORMAL)
	{
		draw_synth_test_step_3_fail();
	}
}

static void draw_synth_test_step_4_result(const TEST_RESULT *synth_test_result)
{
	if (synth_test_result->test_content.test_type == TEST_TYPE_CV_TEST
		|| synth_test_result->test_content.test_type == TEST_TYPE_CC_TEST
		|| synth_test_result->test_content.test_type == TEST_TYPE_CR_TEST)
	{
		draw_synth_test_step_4_ac(synth_test_result->test_content.ac_current);
		
		draw_synth_test_step_4_voltage(measure_to_actual_voltage((int)synth_test_result->test_content.channel, synth_test_result->test_content.voltage));
		
		draw_synth_test_step_4_current(measure_to_actual_current((int)synth_test_result->test_content.channel, synth_test_result->test_content.current));
	}
	else if (synth_test_result->test_content.test_type == TEST_TYPE_OVER_CURRENT_TEST)
	{
		draw_synth_test_step_4_ac(synth_test_result->test_content.ac_current);

		draw_synth_test_step_4_oc(measure_to_actual_current((int)synth_test_result->test_content.channel, synth_test_result->test_content.current));
	}
	else if (synth_test_result->test_content.test_type == TEST_TYPE_SHORT_TEST)
	{
		draw_synth_test_step_4_ac(synth_test_result->test_content.ac_current);

		draw_synth_test_step_4_short(measure_to_actual_current((int)synth_test_result->test_content.channel, synth_test_result->test_content.current));
	}

	if (synth_test_result->test_content.test_status == TEST_STATUS_NORMAL)
	{
		draw_synth_test_step_4_OK();
	}
	else if (synth_test_result->test_content.test_status == TEST_STATUS_ABNORMAL)
	{
		draw_synth_test_step_4_fail();
	}
}

static void draw_synth_test_step_5_result(const TEST_RESULT *synth_test_result)
{
	if (synth_test_result->test_content.test_type == TEST_TYPE_CV_TEST
		|| synth_test_result->test_content.test_type == TEST_TYPE_CC_TEST
		|| synth_test_result->test_content.test_type == TEST_TYPE_CR_TEST)
	{
		draw_synth_test_step_5_ac(synth_test_result->test_content.ac_current);
		
		draw_synth_test_step_5_voltage(measure_to_actual_voltage((int)synth_test_result->test_content.channel, synth_test_result->test_content.voltage));
		
		draw_synth_test_step_5_current(measure_to_actual_current((int)synth_test_result->test_content.channel, synth_test_result->test_content.current));
	}
	else if (synth_test_result->test_content.test_type == TEST_TYPE_OVER_CURRENT_TEST)
	{
		draw_synth_test_step_5_ac(synth_test_result->test_content.ac_current);

		draw_synth_test_step_5_oc(measure_to_actual_current((int)synth_test_result->test_content.channel, synth_test_result->test_content.current));
	}
	else if (synth_test_result->test_content.test_type == TEST_TYPE_SHORT_TEST)
	{
		draw_synth_test_step_5_ac(synth_test_result->test_content.ac_current);

		draw_synth_test_step_5_short(measure_to_actual_current((int)synth_test_result->test_content.channel, synth_test_result->test_content.current));
	}

	if (synth_test_result->test_content.test_status == TEST_STATUS_NORMAL)
	{
		draw_synth_test_step_5_OK();
	}
	else if (synth_test_result->test_content.test_status == TEST_STATUS_ABNORMAL)
	{
		draw_synth_test_step_5_fail();
	}
}

static void draw_synth_test_step_6_result(const TEST_RESULT *synth_test_result)
{
	if (synth_test_result->test_content.test_type == TEST_TYPE_CV_TEST
		|| synth_test_result->test_content.test_type == TEST_TYPE_CC_TEST
		|| synth_test_result->test_content.test_type == TEST_TYPE_CR_TEST)
	{
		draw_synth_test_step_6_ac(synth_test_result->test_content.ac_current);
		
		draw_synth_test_step_6_voltage(measure_to_actual_voltage((int)synth_test_result->test_content.channel, synth_test_result->test_content.voltage));
		
		draw_synth_test_step_6_current(measure_to_actual_current((int)synth_test_result->test_content.channel, synth_test_result->test_content.current));
	}
	else if (synth_test_result->test_content.test_type == TEST_TYPE_OVER_CURRENT_TEST)
	{
		draw_synth_test_step_6_ac(synth_test_result->test_content.ac_current);

		draw_synth_test_step_6_oc(measure_to_actual_current((int)synth_test_result->test_content.channel, synth_test_result->test_content.current));
	}
	else if (synth_test_result->test_content.test_type == TEST_TYPE_SHORT_TEST)
	{
		draw_synth_test_step_6_ac(synth_test_result->test_content.ac_current);

		draw_synth_test_step_6_short(measure_to_actual_current((int)synth_test_result->test_content.channel, synth_test_result->test_content.current));
	}

	if (synth_test_result->test_content.test_status == TEST_STATUS_NORMAL)
	{
		draw_synth_test_step_6_OK();
	}
	else if (synth_test_result->test_content.test_status == TEST_STATUS_ABNORMAL)
	{
		draw_synth_test_step_6_fail();
	}
}

static void draw_synth_test_step_7_result(const TEST_RESULT *synth_test_result)
{
	if (synth_test_result->test_content.test_type == TEST_TYPE_CV_TEST
		|| synth_test_result->test_content.test_type == TEST_TYPE_CC_TEST
		|| synth_test_result->test_content.test_type == TEST_TYPE_CR_TEST)
	{
		draw_synth_test_step_7_ac(synth_test_result->test_content.ac_current);
		
		draw_synth_test_step_7_voltage(measure_to_actual_voltage((int)synth_test_result->test_content.channel, synth_test_result->test_content.voltage));
		
		draw_synth_test_step_7_current(measure_to_actual_current((int)synth_test_result->test_content.channel, synth_test_result->test_content.current));
	}
	else if (synth_test_result->test_content.test_type == TEST_TYPE_OVER_CURRENT_TEST)
	{
		draw_synth_test_step_7_ac(synth_test_result->test_content.ac_current);

		draw_synth_test_step_7_oc(measure_to_actual_current((int)synth_test_result->test_content.channel, synth_test_result->test_content.current));
	}
	else if (synth_test_result->test_content.test_type == TEST_TYPE_SHORT_TEST)
	{
		draw_synth_test_step_7_ac(synth_test_result->test_content.ac_current);

		draw_synth_test_step_7_short(measure_to_actual_current((int)synth_test_result->test_content.channel, synth_test_result->test_content.current));
	}

	if (synth_test_result->test_content.test_status == TEST_STATUS_NORMAL)
	{
		draw_synth_test_step_7_OK();
	}
	else if (synth_test_result->test_content.test_status == TEST_STATUS_ABNORMAL)
	{
		draw_synth_test_step_7_fail();
	}
}

static void draw_synth_test_step_discharge_result(const TEST_RESULT *synth_test_result)
{
	if (synth_test_result->test_content.test_status == TEST_STATUS_NORMAL)
	{
		draw_synth_test_step_8_OK();
	}
}

static void clear_synth_test_step_2_val(void)
{
	clear_synth_test_step_2_ac();
	
	clear_synth_test_step_2_voltage();
	
	clear_synth_test_step_2_current();	

	clear_synth_test_step_2_result();	
}

static void clear_synth_test_step_2_cv_val(void)
{
	clear_synth_test_step_2_val();
}

static void clear_synth_test_step_2_cc_val(void)
{
	clear_synth_test_step_2_val();
}

static void clear_synth_test_step_2_cr_val(void)
{
	clear_synth_test_step_2_val();
}

static void clear_synth_test_step_2_oc_val(void)
{
	clear_synth_test_step_2_ac();

	clear_synth_test_step_2_oc();

	clear_synth_test_step_2_result();
}

static void clear_synth_test_step_2_short_val(void)
{
	clear_synth_test_step_2_ac();

	clear_synth_test_step_2_short();

	clear_synth_test_step_2_result();
}

static void (* const s_clear_synth_test_step_2_val_func[])(void) = 
{
	[SYNTH_TEST_CV] = clear_synth_test_step_2_cv_val,

	[SYNTH_TEST_CC] = clear_synth_test_step_2_cc_val,

	[SYNTH_TEST_CR] = clear_synth_test_step_2_cr_val,

	[SYNTH_TEST_OVER_CURRENT] = clear_synth_test_step_2_oc_val,

	[SYNTH_TEST_SHORT] = clear_synth_test_step_2_short_val
};

static void (* const s_clear_qc_20_test_step_2_val_func[])(void) = 
{
	[QC_20_5V_TEST_CV] = clear_synth_test_step_2_cv_val,

	[QC_20_5V_TEST_CC] = clear_synth_test_step_2_cc_val,

	[QC_20_5V_TEST_CR] = clear_synth_test_step_2_cr_val,

	[QC_20_5V_TEST_OVER_CURRENT] = clear_synth_test_step_2_oc_val,

	[QC_20_5V_TEST_SHORT] = clear_synth_test_step_2_short_val,

	[QC_20_9V_TEST_CV] = clear_synth_test_step_2_cv_val,

	[QC_20_9V_TEST_CC] = clear_synth_test_step_2_cc_val,

	[QC_20_9V_TEST_CR] = clear_synth_test_step_2_cr_val,

	[QC_20_9V_TEST_OVER_CURRENT] = clear_synth_test_step_2_oc_val,

	[QC_20_9V_TEST_SHORT] = clear_synth_test_step_2_short_val,

	[QC_20_12V_TEST_CV] = clear_synth_test_step_2_cv_val,

	[QC_20_12V_TEST_CC] = clear_synth_test_step_2_cc_val,

	[QC_20_12V_TEST_CR] = clear_synth_test_step_2_cr_val,

	[QC_20_12V_TEST_OVER_CURRENT] = clear_synth_test_step_2_oc_val,

	[QC_20_12V_TEST_SHORT] = clear_synth_test_step_2_short_val,

	[QC_20_20V_TEST_CV] = clear_synth_test_step_2_cv_val,

	[QC_20_20V_TEST_CC] = clear_synth_test_step_2_cc_val,

	[QC_20_20V_TEST_CR] = clear_synth_test_step_2_cr_val,

	[QC_20_20V_TEST_OVER_CURRENT] = clear_synth_test_step_2_oc_val,

	[QC_20_20V_TEST_SHORT] = clear_synth_test_step_2_short_val,
};

static void clear_synth_test_step_3_val(void)
{
	clear_synth_test_step_3_ac();
	
	clear_synth_test_step_3_voltage();
	
	clear_synth_test_step_3_current();	

	clear_synth_test_step_3_result();	
}

static void clear_synth_test_step_3_cv_val(void)
{
	clear_synth_test_step_3_val();
}

static void clear_synth_test_step_3_cc_val(void)
{
	clear_synth_test_step_3_val();
}

static void clear_synth_test_step_3_cr_val(void)
{
	clear_synth_test_step_3_val();
}

static void clear_synth_test_step_3_oc_val(void)
{
	clear_synth_test_step_3_ac();

	clear_synth_test_step_3_oc();

	clear_synth_test_step_3_result();
}

static void clear_synth_test_step_3_short_val(void)
{
	clear_synth_test_step_3_ac();

	clear_synth_test_step_3_short();

	clear_synth_test_step_3_result();
}

static void (* const s_clear_synth_test_step_3_val_func[])(void) = 
{
	[SYNTH_TEST_CV] = clear_synth_test_step_3_cv_val,

	[SYNTH_TEST_CC] = clear_synth_test_step_3_cc_val,

	[SYNTH_TEST_CR] = clear_synth_test_step_3_cr_val,

	[SYNTH_TEST_OVER_CURRENT] = clear_synth_test_step_3_oc_val,

	[SYNTH_TEST_SHORT] = clear_synth_test_step_3_short_val
};

static void (* const s_clear_qc_20_test_step_3_val_func[])(void) = 
{
	[QC_20_5V_TEST_CV] = clear_synth_test_step_3_cv_val,

	[QC_20_5V_TEST_CC] = clear_synth_test_step_3_cc_val,

	[QC_20_5V_TEST_CR] = clear_synth_test_step_3_cr_val,

	[QC_20_5V_TEST_OVER_CURRENT] = clear_synth_test_step_3_oc_val,

	[QC_20_5V_TEST_SHORT] = clear_synth_test_step_3_short_val,

	[QC_20_9V_TEST_CV] = clear_synth_test_step_3_cv_val,

	[QC_20_9V_TEST_CC] = clear_synth_test_step_3_cc_val,

	[QC_20_9V_TEST_CR] = clear_synth_test_step_3_cr_val,

	[QC_20_9V_TEST_OVER_CURRENT] = clear_synth_test_step_3_oc_val,

	[QC_20_9V_TEST_SHORT] = clear_synth_test_step_3_short_val,

	[QC_20_12V_TEST_CV] = clear_synth_test_step_3_cv_val,

	[QC_20_12V_TEST_CC] = clear_synth_test_step_3_cc_val,

	[QC_20_12V_TEST_CR] = clear_synth_test_step_3_cr_val,

	[QC_20_12V_TEST_OVER_CURRENT] = clear_synth_test_step_3_oc_val,

	[QC_20_12V_TEST_SHORT] = clear_synth_test_step_3_short_val,

	[QC_20_20V_TEST_CV] = clear_synth_test_step_3_cv_val,

	[QC_20_20V_TEST_CC] = clear_synth_test_step_3_cc_val,

	[QC_20_20V_TEST_CR] = clear_synth_test_step_3_cr_val,

	[QC_20_20V_TEST_OVER_CURRENT] = clear_synth_test_step_3_oc_val,

	[QC_20_20V_TEST_SHORT] = clear_synth_test_step_3_short_val,
};

static void clear_synth_test_step_4_val(void)
{
	clear_synth_test_step_4_ac();
	
	clear_synth_test_step_4_voltage();
	
	clear_synth_test_step_4_current();	

	clear_synth_test_step_4_result();	
}

static void clear_synth_test_step_4_cv_val(void)
{
	clear_synth_test_step_4_val();
}

static void clear_synth_test_step_4_cc_val(void)
{
	clear_synth_test_step_4_val();
}

static void clear_synth_test_step_4_cr_val(void)
{
	clear_synth_test_step_4_val();
}

static void clear_synth_test_step_4_oc_val(void)
{
	clear_synth_test_step_4_ac();

	clear_synth_test_step_4_oc();

	clear_synth_test_step_4_result();
}

static void clear_synth_test_step_4_short_val(void)
{
	clear_synth_test_step_4_ac();

	clear_synth_test_step_4_short();

	clear_synth_test_step_4_result();
}

static void (* const s_clear_synth_test_step_4_val_func[])(void) = 
{
	[SYNTH_TEST_CV] = clear_synth_test_step_4_cv_val,

	[SYNTH_TEST_CC] = clear_synth_test_step_4_cc_val,

	[SYNTH_TEST_CR] = clear_synth_test_step_4_cr_val,

	[SYNTH_TEST_OVER_CURRENT] = clear_synth_test_step_4_oc_val,

	[SYNTH_TEST_SHORT] = clear_synth_test_step_4_short_val
};

static void (* const s_clear_qc_20_test_step_4_val_func[])(void) = 
{
	[QC_20_5V_TEST_CV] = clear_synth_test_step_4_cv_val,

	[QC_20_5V_TEST_CC] = clear_synth_test_step_4_cc_val,

	[QC_20_5V_TEST_CR] = clear_synth_test_step_4_cr_val,

	[QC_20_5V_TEST_OVER_CURRENT] = clear_synth_test_step_4_oc_val,

	[QC_20_5V_TEST_SHORT] = clear_synth_test_step_4_short_val,

	[QC_20_9V_TEST_CV] = clear_synth_test_step_4_cv_val,

	[QC_20_9V_TEST_CC] = clear_synth_test_step_4_cc_val,

	[QC_20_9V_TEST_CR] = clear_synth_test_step_4_cr_val,

	[QC_20_9V_TEST_OVER_CURRENT] = clear_synth_test_step_4_oc_val,

	[QC_20_9V_TEST_SHORT] = clear_synth_test_step_4_short_val,

	[QC_20_12V_TEST_CV] = clear_synth_test_step_4_cv_val,

	[QC_20_12V_TEST_CC] = clear_synth_test_step_4_cc_val,

	[QC_20_12V_TEST_CR] = clear_synth_test_step_4_cr_val,

	[QC_20_12V_TEST_OVER_CURRENT] = clear_synth_test_step_4_oc_val,

	[QC_20_12V_TEST_SHORT] = clear_synth_test_step_4_short_val,

	[QC_20_20V_TEST_CV] = clear_synth_test_step_4_cv_val,

	[QC_20_20V_TEST_CC] = clear_synth_test_step_4_cc_val,

	[QC_20_20V_TEST_CR] = clear_synth_test_step_4_cr_val,

	[QC_20_20V_TEST_OVER_CURRENT] = clear_synth_test_step_4_oc_val,

	[QC_20_20V_TEST_SHORT] = clear_synth_test_step_4_short_val,
};
static void clear_synth_test_step_5_val(void)
{
	clear_synth_test_step_5_ac();
	
	clear_synth_test_step_5_voltage();
	
	clear_synth_test_step_5_current();	

	clear_synth_test_step_5_result();	
}

static void clear_synth_test_step_5_cv_val(void)
{
	clear_synth_test_step_5_val();
}

static void clear_synth_test_step_5_cc_val(void)
{
	clear_synth_test_step_5_val();
}

static void clear_synth_test_step_5_cr_val(void)
{
	clear_synth_test_step_5_val();
}

static void clear_synth_test_step_5_oc_val(void)
{
	clear_synth_test_step_5_ac();

	clear_synth_test_step_5_oc();

	clear_synth_test_step_5_result();
}

static void clear_synth_test_step_5_short_val(void)
{
	clear_synth_test_step_5_ac();

	clear_synth_test_step_5_short();

	clear_synth_test_step_5_result();
}

static void (* const s_clear_synth_test_step_5_val_func[])(void) = 
{
	[SYNTH_TEST_CV] = clear_synth_test_step_5_cv_val,

	[SYNTH_TEST_CC] = clear_synth_test_step_5_cc_val,

	[SYNTH_TEST_CR] = clear_synth_test_step_5_cr_val,

	[SYNTH_TEST_OVER_CURRENT] = clear_synth_test_step_5_oc_val,

	[SYNTH_TEST_SHORT] = clear_synth_test_step_5_short_val
};

static void (* const s_clear_qc_20_test_step_5_val_func[])(void) = 
{
	[QC_20_5V_TEST_CV] = clear_synth_test_step_5_cv_val,

	[QC_20_5V_TEST_CC] = clear_synth_test_step_5_cc_val,

	[QC_20_5V_TEST_CR] = clear_synth_test_step_5_cr_val,

	[QC_20_5V_TEST_OVER_CURRENT] = clear_synth_test_step_5_oc_val,

	[QC_20_5V_TEST_SHORT] = clear_synth_test_step_5_short_val,

	[QC_20_9V_TEST_CV] = clear_synth_test_step_5_cv_val,

	[QC_20_9V_TEST_CC] = clear_synth_test_step_5_cc_val,

	[QC_20_9V_TEST_CR] = clear_synth_test_step_5_cr_val,

	[QC_20_9V_TEST_OVER_CURRENT] = clear_synth_test_step_5_oc_val,

	[QC_20_9V_TEST_SHORT] = clear_synth_test_step_5_short_val,

	[QC_20_12V_TEST_CV] = clear_synth_test_step_5_cv_val,

	[QC_20_12V_TEST_CC] = clear_synth_test_step_5_cc_val,

	[QC_20_12V_TEST_CR] = clear_synth_test_step_5_cr_val,

	[QC_20_12V_TEST_OVER_CURRENT] = clear_synth_test_step_5_oc_val,

	[QC_20_12V_TEST_SHORT] = clear_synth_test_step_5_short_val,

	[QC_20_20V_TEST_CV] = clear_synth_test_step_5_cv_val,

	[QC_20_20V_TEST_CC] = clear_synth_test_step_5_cc_val,

	[QC_20_20V_TEST_CR] = clear_synth_test_step_5_cr_val,

	[QC_20_20V_TEST_OVER_CURRENT] = clear_synth_test_step_5_oc_val,

	[QC_20_20V_TEST_SHORT] = clear_synth_test_step_5_short_val,
};

static void clear_synth_test_step_6_val(void)
{
	clear_synth_test_step_6_ac();
	
	clear_synth_test_step_6_voltage();
	
	clear_synth_test_step_6_current();	

	clear_synth_test_step_6_result();	
}

static void clear_synth_test_step_6_cv_val(void)
{
	clear_synth_test_step_6_val();
}

static void clear_synth_test_step_6_cc_val(void)
{
	clear_synth_test_step_6_val();
}

static void clear_synth_test_step_6_cr_val(void)
{
	clear_synth_test_step_6_val();
}

static void clear_synth_test_step_6_oc_val(void)
{
	clear_synth_test_step_6_ac();

	clear_synth_test_step_6_oc();

	clear_synth_test_step_6_result();
}

static void clear_synth_test_step_6_short_val(void)
{
	clear_synth_test_step_6_ac();

	clear_synth_test_step_6_short();

	clear_synth_test_step_6_result();
}

static void (* const s_clear_synth_test_step_6_val_func[])(void) = 
{
	[SYNTH_TEST_CV] = clear_synth_test_step_6_cv_val,

	[SYNTH_TEST_CC] = clear_synth_test_step_6_cc_val,

	[SYNTH_TEST_CR] = clear_synth_test_step_6_cr_val,

	[SYNTH_TEST_OVER_CURRENT] = clear_synth_test_step_6_oc_val,

	[SYNTH_TEST_SHORT] = clear_synth_test_step_6_short_val
};

static void (* const s_clear_qc_20_test_step_6_val_func[])(void) = 
{
	[QC_20_5V_TEST_CV] = clear_synth_test_step_6_cv_val,

	[QC_20_5V_TEST_CC] = clear_synth_test_step_6_cc_val,

	[QC_20_5V_TEST_CR] = clear_synth_test_step_6_cr_val,

	[QC_20_5V_TEST_OVER_CURRENT] = clear_synth_test_step_6_oc_val,

	[QC_20_5V_TEST_SHORT] = clear_synth_test_step_6_short_val,

	[QC_20_9V_TEST_CV] = clear_synth_test_step_6_cv_val,

	[QC_20_9V_TEST_CC] = clear_synth_test_step_6_cc_val,

	[QC_20_9V_TEST_CR] = clear_synth_test_step_6_cr_val,

	[QC_20_9V_TEST_OVER_CURRENT] = clear_synth_test_step_6_oc_val,

	[QC_20_9V_TEST_SHORT] = clear_synth_test_step_6_short_val,

	[QC_20_12V_TEST_CV] = clear_synth_test_step_6_cv_val,

	[QC_20_12V_TEST_CC] = clear_synth_test_step_6_cc_val,

	[QC_20_12V_TEST_CR] = clear_synth_test_step_6_cr_val,

	[QC_20_12V_TEST_OVER_CURRENT] = clear_synth_test_step_6_oc_val,

	[QC_20_12V_TEST_SHORT] = clear_synth_test_step_6_short_val,

	[QC_20_20V_TEST_CV] = clear_synth_test_step_6_cv_val,

	[QC_20_20V_TEST_CC] = clear_synth_test_step_6_cc_val,

	[QC_20_20V_TEST_CR] = clear_synth_test_step_6_cr_val,

	[QC_20_20V_TEST_OVER_CURRENT] = clear_synth_test_step_6_oc_val,

	[QC_20_20V_TEST_SHORT] = clear_synth_test_step_6_short_val,
};

static void clear_synth_test_step_7_val(void)
{
	clear_synth_test_step_7_ac();
	
	clear_synth_test_step_7_voltage();
	
	clear_synth_test_step_7_current();	

	clear_synth_test_step_7_result();	
}

static void clear_synth_test_step_7_cv_val(void)
{
	clear_synth_test_step_7_val();
}

static void clear_synth_test_step_7_cc_val(void)
{
	clear_synth_test_step_7_val();
}

static void clear_synth_test_step_7_cr_val(void)
{
	clear_synth_test_step_7_val();
}

static void clear_synth_test_step_7_oc_val(void)
{
	clear_synth_test_step_7_ac();

	clear_synth_test_step_7_oc();

	clear_synth_test_step_7_result();
}

static void clear_synth_test_step_7_short_val(void)
{
	clear_synth_test_step_7_ac();

	clear_synth_test_step_7_short();

	clear_synth_test_step_7_result();
}

static void (* const s_clear_synth_test_step_7_val_func[])(void) = 
{
	[SYNTH_TEST_CV] = clear_synth_test_step_7_cv_val,

	[SYNTH_TEST_CC] = clear_synth_test_step_7_cc_val,

	[SYNTH_TEST_CR] = clear_synth_test_step_7_cr_val,

	[SYNTH_TEST_OVER_CURRENT] = clear_synth_test_step_7_oc_val,

	[SYNTH_TEST_SHORT] = clear_synth_test_step_7_short_val
};

static void (* const s_clear_qc_20_test_step_7_val_func[])(void) = 
{
	[QC_20_5V_TEST_CV] = clear_synth_test_step_7_cv_val,

	[QC_20_5V_TEST_CC] = clear_synth_test_step_7_cc_val,

	[QC_20_5V_TEST_CR] = clear_synth_test_step_7_cr_val,

	[QC_20_5V_TEST_OVER_CURRENT] = clear_synth_test_step_7_oc_val,

	[QC_20_5V_TEST_SHORT] = clear_synth_test_step_7_short_val,

	[QC_20_9V_TEST_CV] = clear_synth_test_step_7_cv_val,

	[QC_20_9V_TEST_CC] = clear_synth_test_step_7_cc_val,

	[QC_20_9V_TEST_CR] = clear_synth_test_step_7_cr_val,

	[QC_20_9V_TEST_OVER_CURRENT] = clear_synth_test_step_7_oc_val,

	[QC_20_9V_TEST_SHORT] = clear_synth_test_step_7_short_val,

	[QC_20_12V_TEST_CV] = clear_synth_test_step_7_cv_val,

	[QC_20_12V_TEST_CC] = clear_synth_test_step_7_cc_val,

	[QC_20_12V_TEST_CR] = clear_synth_test_step_7_cr_val,

	[QC_20_12V_TEST_OVER_CURRENT] = clear_synth_test_step_7_oc_val,

	[QC_20_12V_TEST_SHORT] = clear_synth_test_step_7_short_val,

	[QC_20_20V_TEST_CV] = clear_synth_test_step_7_cv_val,

	[QC_20_20V_TEST_CC] = clear_synth_test_step_7_cc_val,

	[QC_20_20V_TEST_CR] = clear_synth_test_step_7_cr_val,

	[QC_20_20V_TEST_OVER_CURRENT] = clear_synth_test_step_7_oc_val,

	[QC_20_20V_TEST_SHORT] = clear_synth_test_step_7_short_val,
};

static void draw_synth_test_step_none(const TEST_RESULT *synth_test_result)
{
	SYNTH_TEST_TYPE  synth_test_type;
	QC_20_TEST_TYPE  qc_20_test_type;
	
	OPTION_ON_OFF    on_off;
	
	/* clear empty load test result */
	clear_synth_test_step_1_ac();

	clear_synth_test_step_1_voltage();

	clear_synth_test_step_1_result();

	/* clear step 2 result */
	if (s_cur_test_category == TEST_CATEGORY_SYNTH_TEST)
	{
		synth_test_type = s_synth_test_setting->synth_normal_test_setting[0].test_type;
		on_off = s_synth_test_setting->synth_normal_test_setting[0].on_off;

		if (on_off == OPTION_ON)
		{
			s_clear_synth_test_step_2_val_func[synth_test_type]();
		}
	}
	else if (s_cur_test_category == TEST_CATEGORY_QC_20_TEST)
	{
		qc_20_test_type = s_qc_20_test_setting->qc_20_normal_test_setting[0].test_type;
		on_off = s_qc_20_test_setting->qc_20_normal_test_setting[0].on_off;

		if (on_off == OPTION_ON)
		{
			s_clear_qc_20_test_step_2_val_func[qc_20_test_type]();
		}
	}

	/* clear step 3 result */
	if (s_cur_test_category == TEST_CATEGORY_SYNTH_TEST)
	{
		synth_test_type = s_synth_test_setting->synth_normal_test_setting[1].test_type;
		on_off = s_synth_test_setting->synth_normal_test_setting[1].on_off;

		if (on_off == OPTION_ON)
		{
			s_clear_synth_test_step_3_val_func[synth_test_type]();
		}
	}
	else if (s_cur_test_category == TEST_CATEGORY_QC_20_TEST)
	{
		qc_20_test_type = s_qc_20_test_setting->qc_20_normal_test_setting[1].test_type;
		on_off = s_qc_20_test_setting->qc_20_normal_test_setting[1].on_off;

		if (on_off == OPTION_ON)
		{
			s_clear_qc_20_test_step_3_val_func[qc_20_test_type]();
		}
	}

	/* clear step 4 result */
	if (s_cur_test_category == TEST_CATEGORY_SYNTH_TEST)
	{
		synth_test_type = s_synth_test_setting->synth_normal_test_setting[2].test_type;
		on_off = s_synth_test_setting->synth_normal_test_setting[2].on_off;

		if (on_off == OPTION_ON)
		{
			s_clear_synth_test_step_4_val_func[synth_test_type]();
		}
	}
	else if (s_cur_test_category == TEST_CATEGORY_QC_20_TEST)
	{
		qc_20_test_type = s_qc_20_test_setting->qc_20_normal_test_setting[2].test_type;
		on_off = s_qc_20_test_setting->qc_20_normal_test_setting[2].on_off;

		if (on_off == OPTION_ON)
		{
			s_clear_qc_20_test_step_4_val_func[qc_20_test_type]();
		}
	}

	lcd_validate_cmd();
	
	/* clear step 5 result */
	if (s_cur_test_category == TEST_CATEGORY_SYNTH_TEST)
	{
		synth_test_type = s_synth_test_setting->synth_normal_test_setting[3].test_type;
		on_off = s_synth_test_setting->synth_normal_test_setting[3].on_off;

		if (on_off == OPTION_ON)
		{
			s_clear_synth_test_step_5_val_func[synth_test_type]();
		}
	}
	else if (s_cur_test_category == TEST_CATEGORY_QC_20_TEST)
	{
		qc_20_test_type = s_qc_20_test_setting->qc_20_normal_test_setting[3].test_type;
		on_off = s_qc_20_test_setting->qc_20_normal_test_setting[3].on_off;

		if (on_off == OPTION_ON)
		{
			s_clear_qc_20_test_step_5_val_func[qc_20_test_type]();
		}
	}
	
	/* clear step 6 result */
	if (s_cur_test_category == TEST_CATEGORY_SYNTH_TEST)
	{
		synth_test_type = s_synth_test_setting->synth_normal_test_setting[4].test_type;
		on_off = s_synth_test_setting->synth_normal_test_setting[4].on_off;

		if (on_off == OPTION_ON)
		{
			s_clear_synth_test_step_6_val_func[synth_test_type]();
		}
	}
	else if (s_cur_test_category == TEST_CATEGORY_QC_20_TEST)
	{
		qc_20_test_type = s_qc_20_test_setting->qc_20_normal_test_setting[4].test_type;
		on_off = s_qc_20_test_setting->qc_20_normal_test_setting[4].on_off;

		if (on_off == OPTION_ON)
		{
			s_clear_qc_20_test_step_6_val_func[qc_20_test_type]();
		}
	}

	/* clear step 7 result */
	if (s_cur_test_category == TEST_CATEGORY_SYNTH_TEST)
	{
		synth_test_type = s_synth_test_setting->synth_normal_test_setting[5].test_type;
		on_off = s_synth_test_setting->synth_normal_test_setting[5].on_off;

		if (on_off == OPTION_ON)
		{
			s_clear_synth_test_step_7_val_func[synth_test_type]();
		}
	}
	else if (s_cur_test_category == TEST_CATEGORY_QC_20_TEST)
	{
		qc_20_test_type = s_qc_20_test_setting->qc_20_normal_test_setting[5].test_type;
		on_off = s_qc_20_test_setting->qc_20_normal_test_setting[5].on_off;

		if (on_off == OPTION_ON)
		{
			s_clear_qc_20_test_step_7_val_func[qc_20_test_type]();
		}
	}

	/* clear discharge test result */
	clear_synth_test_step_8_result();
}

static void (*const s_draw_synth_test_result_func[])(const TEST_RESULT *synth_test_result) = 
{
	[TEST_STEP_EMPTY_LOAD] = draw_synth_test_step_empty_load_result,
	
	[TEST_STEP_2] = draw_synth_test_step_2_result, 

	[TEST_STEP_3] = draw_synth_test_step_3_result, 

	[TEST_STEP_4] = draw_synth_test_step_4_result,

	[TEST_STEP_5] = draw_synth_test_step_5_result, 

	[TEST_STEP_6] = draw_synth_test_step_6_result,

	[TEST_STEP_7] = draw_synth_test_step_7_result,

	[TEST_STEP_DISCHARGE] = draw_synth_test_step_discharge_result,

	[TEST_STEP_NONE] = draw_synth_test_step_none
};

/* refresh synth test result */
static void synth_test_handler(void *msg)
{
	TEST_RESULT *synth_test_result = (TEST_RESULT *)msg;
	RT_ASSERT(synth_test_result != RT_NULL);

	s_draw_synth_test_result_func[synth_test_result->test_step](synth_test_result);

	lcd_validate_cmd();
}

static uint8_t s_synth_test_type[] = 
{
	[SYNTH_TEST_CV] = TEST_TYPE_CV_TEST,

	[SYNTH_TEST_CC] = TEST_TYPE_CC_TEST,

	[SYNTH_TEST_CR] = TEST_TYPE_CR_TEST,

	[SYNTH_TEST_OVER_CURRENT] = TEST_TYPE_OVER_CURRENT_TEST,

	[SYNTH_TEST_SHORT] = TEST_TYPE_SHORT_TEST
};

static uint8_t s_qc_20_test_type[] = 
{
	[QC_20_5V_TEST_CV] = TEST_TYPE_CV_TEST,

	[QC_20_5V_TEST_CC] = TEST_TYPE_CC_TEST,

	[QC_20_5V_TEST_CR] = TEST_TYPE_CR_TEST,

	[QC_20_5V_TEST_OVER_CURRENT] = TEST_TYPE_OVER_CURRENT_TEST,

	[QC_20_5V_TEST_SHORT] = TEST_TYPE_SHORT_TEST,
	

	[QC_20_9V_TEST_CV] = TEST_TYPE_CV_TEST,

	[QC_20_9V_TEST_CC] = TEST_TYPE_CC_TEST,

	[QC_20_9V_TEST_CR] = TEST_TYPE_CR_TEST,

	[QC_20_9V_TEST_OVER_CURRENT] = TEST_TYPE_OVER_CURRENT_TEST,

	[QC_20_9V_TEST_SHORT] = TEST_TYPE_SHORT_TEST,


	[QC_20_12V_TEST_CV] = TEST_TYPE_CV_TEST,

	[QC_20_12V_TEST_CC] = TEST_TYPE_CC_TEST,

	[QC_20_12V_TEST_CR] = TEST_TYPE_CR_TEST,

	[QC_20_12V_TEST_OVER_CURRENT] = TEST_TYPE_OVER_CURRENT_TEST,

	[QC_20_12V_TEST_SHORT] = TEST_TYPE_SHORT_TEST,


	[QC_20_20V_TEST_CV] = TEST_TYPE_CV_TEST,

	[QC_20_20V_TEST_CC] = TEST_TYPE_CC_TEST,

	[QC_20_20V_TEST_CR] = TEST_TYPE_CR_TEST,

	[QC_20_20V_TEST_OVER_CURRENT] = TEST_TYPE_OVER_CURRENT_TEST,

	[QC_20_20V_TEST_SHORT] = TEST_TYPE_SHORT_TEST,
};

void form_synth_test_config(int port, TEST_CONFIG *test_config, const SYNTH_NORMAL_TEST_SETTING *synth_normal_test_setting)
{
	uint8_t test_type = s_synth_test_type[synth_normal_test_setting->test_type];

	test_config->cv_test_config.test_category = TEST_CATEGORY_SYNTH;
	
	switch (test_type)
	{
	case TEST_TYPE_CV_TEST:
		test_config->cv_test_config.duration      = synth_normal_test_setting->cv_setting.duration;
		test_config->cv_test_config.voltage_val   = actual_to_measure_voltage(port, synth_normal_test_setting->cv_setting.cv_val);
		test_config->cv_test_config.ac_upper      = synth_normal_test_setting->cv_setting.ac_limit;
		test_config->cv_test_config.current_lower = actual_to_measure_current(port, synth_normal_test_setting->cv_setting.current_from);
		test_config->cv_test_config.current_upper = actual_to_measure_current(port, synth_normal_test_setting->cv_setting.current_to);

		test_config->cv_test_config.voltage_level = TEST_VOLTAGE_LEVEL_DEFAULT;

		break;

	case TEST_TYPE_CC_TEST:
		test_config->cc_test_config.duration      = synth_normal_test_setting->cc_setting.duration;
		test_config->cc_test_config.current_val   = actual_to_measure_current(port, synth_normal_test_setting->cc_setting.cc_val);
		test_config->cc_test_config.ac_upper      = synth_normal_test_setting->cc_setting.ac_limit;
		test_config->cc_test_config.voltage_lower = actual_to_measure_voltage(port, synth_normal_test_setting->cc_setting.voltage_from);
		test_config->cc_test_config.voltage_upper = actual_to_measure_voltage(port, synth_normal_test_setting->cc_setting.voltage_to);

		test_config->cc_test_config.voltage_level = TEST_VOLTAGE_LEVEL_DEFAULT;
		
		break;
		
	case TEST_TYPE_CR_TEST:
		test_config->cr_test_config.duration      = synth_normal_test_setting->cr_setting.duration;
		test_config->cr_test_config.resist_val    = synth_normal_test_setting->cr_setting.cr_val;
		test_config->cr_test_config.ac_upper      = synth_normal_test_setting->cr_setting.ac_limit;
		test_config->cr_test_config.current_lower = actual_to_measure_current(port, synth_normal_test_setting->cr_setting.current_from);
		test_config->cr_test_config.current_upper = actual_to_measure_current(port, synth_normal_test_setting->cr_setting.current_to);
		test_config->cr_test_config.voltage_lower = actual_to_measure_voltage(port, synth_normal_test_setting->cr_setting.voltage_from);
		test_config->cr_test_config.voltage_upper = actual_to_measure_voltage(port, synth_normal_test_setting->cr_setting.voltage_to);

		test_config->cr_test_config.voltage_level = TEST_VOLTAGE_LEVEL_DEFAULT;
		
		break;

	case TEST_TYPE_OVER_CURRENT_TEST:
		test_config->over_current_test_config.interval = synth_normal_test_setting->over_current_test_setting.interval;
		test_config->over_current_test_config.ac_upper = synth_normal_test_setting->over_current_test_setting.ac_limit;
		test_config->over_current_test_config.current_upper = actual_to_measure_current(port, synth_normal_test_setting->over_current_test_setting.current_limit);
		
		test_config->over_current_test_config.voltage_level = TEST_VOLTAGE_LEVEL_DEFAULT;
		
		break;

	case TEST_TYPE_SHORT_TEST:
		test_config->short_test_config.duration = synth_normal_test_setting->short_test_setting.duration;
		test_config->short_test_config.ac_upper = synth_normal_test_setting->short_test_setting.ac_limit;
		test_config->short_test_config.current_upper = actual_to_measure_current(port, synth_normal_test_setting->short_test_setting.short_limit);

		test_config->short_test_config.voltage_level = TEST_VOLTAGE_LEVEL_DEFAULT;
		
		break;

	default:
		break;
	}
}


void form_qc_20_test_config(int port, TEST_CONFIG *test_config, const QC_20_NORMAL_TEST_SETTING *qc_20_normal_test_setting)
{
	test_config->cv_test_config.test_category = TEST_CATEGORY_QC_20;
	
	switch (qc_20_normal_test_setting->test_type)
	{
	case QC_20_5V_TEST_CV:
		test_config->cv_test_config.duration      = qc_20_normal_test_setting->_5v_cv_setting.duration;
		test_config->cv_test_config.voltage_val   = actual_to_measure_voltage(port, qc_20_normal_test_setting->_5v_cv_setting.cv_val);
		test_config->cv_test_config.ac_upper      = qc_20_normal_test_setting->_5v_cv_setting.ac_limit;
		test_config->cv_test_config.current_lower = actual_to_measure_current(port, qc_20_normal_test_setting->_5v_cv_setting.current_from);
		test_config->cv_test_config.current_upper = actual_to_measure_current(port, qc_20_normal_test_setting->_5v_cv_setting.current_to);

		test_config->cv_test_config.voltage_level = TEST_VOLTAGE_LEVEL_5V;
		
		break;

	case QC_20_5V_TEST_CC:
		test_config->cc_test_config.duration      = qc_20_normal_test_setting->_5v_cc_setting.duration;
		test_config->cc_test_config.current_val   = actual_to_measure_current(port, qc_20_normal_test_setting->_5v_cc_setting.cc_val);
		test_config->cc_test_config.ac_upper      = qc_20_normal_test_setting->_5v_cc_setting.ac_limit;
		test_config->cc_test_config.voltage_lower = actual_to_measure_voltage(port, qc_20_normal_test_setting->_5v_cc_setting.voltage_from);
		test_config->cc_test_config.voltage_upper = actual_to_measure_voltage(port, qc_20_normal_test_setting->_5v_cc_setting.voltage_to);

		test_config->cc_test_config.voltage_level = TEST_VOLTAGE_LEVEL_5V;
		
		break;
		
	case QC_20_5V_TEST_CR:
		test_config->cr_test_config.duration      = qc_20_normal_test_setting->_5v_cr_setting.duration;
		test_config->cr_test_config.resist_val    = qc_20_normal_test_setting->_5v_cr_setting.cr_val;
		test_config->cr_test_config.ac_upper      = qc_20_normal_test_setting->_5v_cr_setting.ac_limit;
		test_config->cr_test_config.current_lower = actual_to_measure_current(port, qc_20_normal_test_setting->_5v_cr_setting.current_from);
		test_config->cr_test_config.current_upper = actual_to_measure_current(port, qc_20_normal_test_setting->_5v_cr_setting.current_to);
		test_config->cr_test_config.voltage_lower = actual_to_measure_voltage(port, qc_20_normal_test_setting->_5v_cr_setting.voltage_from);
		test_config->cr_test_config.voltage_upper = actual_to_measure_voltage(port, qc_20_normal_test_setting->_5v_cr_setting.voltage_to);

		test_config->cr_test_config.voltage_level = TEST_VOLTAGE_LEVEL_5V;
		
		break;

	case QC_20_5V_TEST_OVER_CURRENT:
		test_config->over_current_test_config.interval = qc_20_normal_test_setting->_5v_over_current_test_setting.interval;
		test_config->over_current_test_config.ac_upper = qc_20_normal_test_setting->_5v_over_current_test_setting.ac_limit;
		test_config->over_current_test_config.current_upper = actual_to_measure_current(port, qc_20_normal_test_setting->_5v_over_current_test_setting.current_limit);

		test_config->over_current_test_config.voltage_level = TEST_VOLTAGE_LEVEL_5V;
		
		break;

	case QC_20_5V_TEST_SHORT:
		test_config->short_test_config.duration = qc_20_normal_test_setting->_5v_short_test_setting.duration;
		test_config->short_test_config.ac_upper = qc_20_normal_test_setting->_5v_short_test_setting.ac_limit;
		test_config->short_test_config.current_upper = actual_to_measure_current(port, qc_20_normal_test_setting->_5v_short_test_setting.short_limit);

		test_config->short_test_config.voltage_level = TEST_VOLTAGE_LEVEL_5V;
		
		break;

	case QC_20_9V_TEST_CV:
		test_config->cv_test_config.duration      = qc_20_normal_test_setting->_9v_cv_setting.duration;
		test_config->cv_test_config.voltage_val   = actual_to_measure_voltage(port, qc_20_normal_test_setting->_9v_cv_setting.cv_val);
		test_config->cv_test_config.ac_upper      = qc_20_normal_test_setting->_9v_cv_setting.ac_limit;
		test_config->cv_test_config.current_lower = actual_to_measure_current(port, qc_20_normal_test_setting->_9v_cv_setting.current_from);
		test_config->cv_test_config.current_upper = actual_to_measure_current(port, qc_20_normal_test_setting->_9v_cv_setting.current_to);

		test_config->cv_test_config.voltage_level = TEST_VOLTAGE_LEVEL_9V;
		
		break;

	case QC_20_9V_TEST_CC:
		test_config->cc_test_config.duration      = qc_20_normal_test_setting->_9v_cc_setting.duration;
		test_config->cc_test_config.current_val   = actual_to_measure_current(port, qc_20_normal_test_setting->_9v_cc_setting.cc_val);
		test_config->cc_test_config.ac_upper      = qc_20_normal_test_setting->_9v_cc_setting.ac_limit;
		test_config->cc_test_config.voltage_lower = actual_to_measure_voltage(port, qc_20_normal_test_setting->_9v_cc_setting.voltage_from);
		test_config->cc_test_config.voltage_upper = actual_to_measure_voltage(port, qc_20_normal_test_setting->_9v_cc_setting.voltage_to);

		test_config->cc_test_config.voltage_level = TEST_VOLTAGE_LEVEL_9V;
		
		break;
		
	case QC_20_9V_TEST_CR:
		test_config->cr_test_config.duration      = qc_20_normal_test_setting->_9v_cr_setting.duration;
		test_config->cr_test_config.resist_val    = qc_20_normal_test_setting->_9v_cr_setting.cr_val;
		test_config->cr_test_config.ac_upper      = qc_20_normal_test_setting->_9v_cr_setting.ac_limit;
		test_config->cr_test_config.current_lower = actual_to_measure_current(port, qc_20_normal_test_setting->_9v_cr_setting.current_from);
		test_config->cr_test_config.current_upper = actual_to_measure_current(port, qc_20_normal_test_setting->_9v_cr_setting.current_to);
		test_config->cr_test_config.voltage_lower = actual_to_measure_voltage(port, qc_20_normal_test_setting->_9v_cr_setting.voltage_from);
		test_config->cr_test_config.voltage_upper = actual_to_measure_voltage(port, qc_20_normal_test_setting->_9v_cr_setting.voltage_to);

		test_config->cr_test_config.voltage_level = TEST_VOLTAGE_LEVEL_9V;
		
		break;

	case QC_20_9V_TEST_OVER_CURRENT:
		test_config->over_current_test_config.interval = qc_20_normal_test_setting->_9v_over_current_test_setting.interval;
		test_config->over_current_test_config.ac_upper = qc_20_normal_test_setting->_9v_over_current_test_setting.ac_limit;
		test_config->over_current_test_config.current_upper = actual_to_measure_current(port, qc_20_normal_test_setting->_9v_over_current_test_setting.current_limit);

		test_config->over_current_test_config.voltage_level = TEST_VOLTAGE_LEVEL_9V;
		
		break;

	case QC_20_9V_TEST_SHORT:
		test_config->short_test_config.duration = qc_20_normal_test_setting->_9v_short_test_setting.duration;
		test_config->short_test_config.ac_upper = qc_20_normal_test_setting->_9v_short_test_setting.ac_limit;
		test_config->short_test_config.current_upper = actual_to_measure_current(port, qc_20_normal_test_setting->_9v_short_test_setting.short_limit);

		test_config->short_test_config.voltage_level = TEST_VOLTAGE_LEVEL_9V;
		
		break;

	case QC_20_12V_TEST_CV:
		test_config->cv_test_config.duration      = qc_20_normal_test_setting->_12v_cv_setting.duration;
		test_config->cv_test_config.voltage_val   = actual_to_measure_voltage(port, qc_20_normal_test_setting->_12v_cv_setting.cv_val);
		test_config->cv_test_config.ac_upper      = qc_20_normal_test_setting->_12v_cv_setting.ac_limit;
		test_config->cv_test_config.current_lower = actual_to_measure_current(port, qc_20_normal_test_setting->_12v_cv_setting.current_from);
		test_config->cv_test_config.current_upper = actual_to_measure_current(port, qc_20_normal_test_setting->_12v_cv_setting.current_to);

		test_config->cv_test_config.voltage_level = TEST_VOLTAGE_LEVEL_12V;
		
		break;

	case QC_20_12V_TEST_CC:
		test_config->cc_test_config.duration      = qc_20_normal_test_setting->_12v_cc_setting.duration;
		test_config->cc_test_config.current_val   = actual_to_measure_current(port, qc_20_normal_test_setting->_12v_cc_setting.cc_val);
		test_config->cc_test_config.ac_upper      = qc_20_normal_test_setting->_12v_cc_setting.ac_limit;
		test_config->cc_test_config.voltage_lower = actual_to_measure_voltage(port, qc_20_normal_test_setting->_12v_cc_setting.voltage_from);
		test_config->cc_test_config.voltage_upper = actual_to_measure_voltage(port, qc_20_normal_test_setting->_12v_cc_setting.voltage_to);

		test_config->cc_test_config.voltage_level = TEST_VOLTAGE_LEVEL_12V;
		
		break;
		
	case QC_20_12V_TEST_CR:
		test_config->cr_test_config.duration      = qc_20_normal_test_setting->_12v_cr_setting.duration;
		test_config->cr_test_config.resist_val    = qc_20_normal_test_setting->_12v_cr_setting.cr_val;
		test_config->cr_test_config.ac_upper      = qc_20_normal_test_setting->_12v_cr_setting.ac_limit;
		test_config->cr_test_config.current_lower = actual_to_measure_current(port, qc_20_normal_test_setting->_12v_cr_setting.current_from);
		test_config->cr_test_config.current_upper = actual_to_measure_current(port, qc_20_normal_test_setting->_12v_cr_setting.current_to);
		test_config->cr_test_config.voltage_lower = actual_to_measure_voltage(port, qc_20_normal_test_setting->_12v_cr_setting.voltage_from);
		test_config->cr_test_config.voltage_upper = actual_to_measure_voltage(port, qc_20_normal_test_setting->_12v_cr_setting.voltage_to);

		test_config->cr_test_config.voltage_level = TEST_VOLTAGE_LEVEL_12V;
		
		break;

	case QC_20_12V_TEST_OVER_CURRENT:
		test_config->over_current_test_config.interval = qc_20_normal_test_setting->_12v_over_current_test_setting.interval;
		test_config->over_current_test_config.ac_upper = qc_20_normal_test_setting->_12v_over_current_test_setting.ac_limit;
		test_config->over_current_test_config.current_upper = actual_to_measure_current(port, qc_20_normal_test_setting->_12v_over_current_test_setting.current_limit);

		test_config->over_current_test_config.voltage_level = TEST_VOLTAGE_LEVEL_12V;
		
		break;

	case QC_20_12V_TEST_SHORT:
		test_config->short_test_config.duration = qc_20_normal_test_setting->_12v_short_test_setting.duration;
		test_config->short_test_config.ac_upper = qc_20_normal_test_setting->_12v_short_test_setting.ac_limit;
		test_config->short_test_config.current_upper = actual_to_measure_current(port, qc_20_normal_test_setting->_12v_short_test_setting.short_limit);

		test_config->short_test_config.voltage_level = TEST_VOLTAGE_LEVEL_12V;
		
		break;

	case QC_20_20V_TEST_CV:
		test_config->cv_test_config.duration      = qc_20_normal_test_setting->_20v_cv_setting.duration;
		test_config->cv_test_config.voltage_val   = actual_to_measure_voltage(port, qc_20_normal_test_setting->_20v_cv_setting.cv_val);
		test_config->cv_test_config.ac_upper      = qc_20_normal_test_setting->_20v_cv_setting.ac_limit;
		test_config->cv_test_config.current_lower = actual_to_measure_current(port, qc_20_normal_test_setting->_20v_cv_setting.current_from);
		test_config->cv_test_config.current_upper = actual_to_measure_current(port, qc_20_normal_test_setting->_20v_cv_setting.current_to);

		test_config->cv_test_config.voltage_level = TEST_VOLTAGE_LEVEL_20V;
		
		break;

	case QC_20_20V_TEST_CC:
		test_config->cc_test_config.duration      = qc_20_normal_test_setting->_20v_cc_setting.duration;
		test_config->cc_test_config.current_val   = actual_to_measure_current(port, qc_20_normal_test_setting->_20v_cc_setting.cc_val);
		test_config->cc_test_config.ac_upper      = qc_20_normal_test_setting->_20v_cc_setting.ac_limit;
		test_config->cc_test_config.voltage_lower = actual_to_measure_voltage(port, qc_20_normal_test_setting->_20v_cc_setting.voltage_from);
		test_config->cc_test_config.voltage_upper = actual_to_measure_voltage(port, qc_20_normal_test_setting->_20v_cc_setting.voltage_to);

		test_config->cc_test_config.voltage_level = TEST_VOLTAGE_LEVEL_20V;
		
		break;
		
	case QC_20_20V_TEST_CR:
		test_config->cr_test_config.duration      = qc_20_normal_test_setting->_20v_cr_setting.duration;
		test_config->cr_test_config.resist_val    = qc_20_normal_test_setting->_20v_cr_setting.cr_val;
		test_config->cr_test_config.ac_upper      = qc_20_normal_test_setting->_20v_cr_setting.ac_limit;
		test_config->cr_test_config.current_lower = actual_to_measure_current(port, qc_20_normal_test_setting->_20v_cr_setting.current_from);
		test_config->cr_test_config.current_upper = actual_to_measure_current(port, qc_20_normal_test_setting->_20v_cr_setting.current_to);
		test_config->cr_test_config.voltage_lower = actual_to_measure_voltage(port, qc_20_normal_test_setting->_20v_cr_setting.voltage_from);
		test_config->cr_test_config.voltage_upper = actual_to_measure_voltage(port, qc_20_normal_test_setting->_20v_cr_setting.voltage_to);

		test_config->cr_test_config.voltage_level = TEST_VOLTAGE_LEVEL_20V;
		
		break;

	case QC_20_20V_TEST_OVER_CURRENT:
		test_config->over_current_test_config.interval = qc_20_normal_test_setting->_20v_over_current_test_setting.interval;
		test_config->over_current_test_config.ac_upper = qc_20_normal_test_setting->_20v_over_current_test_setting.ac_limit;
		test_config->over_current_test_config.current_upper = actual_to_measure_current(port, qc_20_normal_test_setting->_20v_over_current_test_setting.current_limit);

		test_config->over_current_test_config.voltage_level = TEST_VOLTAGE_LEVEL_20V;
		
		break;

	case QC_20_20V_TEST_SHORT:
		test_config->short_test_config.duration = qc_20_normal_test_setting->_20v_short_test_setting.duration;
		test_config->short_test_config.ac_upper = qc_20_normal_test_setting->_20v_short_test_setting.ac_limit;
		test_config->short_test_config.current_upper = actual_to_measure_current(port, qc_20_normal_test_setting->_20v_short_test_setting.short_limit);

		test_config->short_test_config.voltage_level = TEST_VOLTAGE_LEVEL_20V;
		
		break;
		
	default:
		break;
	}
}

static int s_refresh_count = 0;

/* thread to run synth test */
static void test_thread_entry(void *parameter)
{
	TEST_CMD test_cmd;
	
	TEST_CONTENT channel_test_content;

	TEST_STEP test_step[SLAVE_PORT_COUNT];

	int i;

	/* channel to test */
	uint8_t test_channel = 0x00;
	uint8_t complete;
	uint8_t channel_test_result;

	int ret;

	rt_bool_t  discharge_enable = RT_TRUE;
	
	for (i = 0; i < SLAVE_PORT_COUNT; i++)
	{
		test_step[i] = TEST_STEP_NONE;
	}

	if (s_cur_test_category == TEST_CATEGORY_SYNTH_TEST)
	{
		RT_ASSERT(s_synth_test_setting != NULL);
		
		if (s_synth_test_setting->discharge_test_setting.on_off == OPTION_OFF)
		{
			discharge_enable = RT_FALSE;
		}
	}
	else if (s_cur_test_category == TEST_CATEGORY_QC_20_TEST)
	{	
		RT_ASSERT(s_qc_20_test_setting != NULL);
		
		if (s_qc_20_test_setting->discharge_test_setting.on_off == OPTION_OFF)
		{
			discharge_enable = RT_FALSE;
		}
	}
	else
	{
		RT_ASSERT(s_mtk_test_setting != NULL);
	}

	/* get channel to test */
	for (i = 0; i < CHANNEL_COUNT; i++)
	{
		if (s_channel_set[i] == OPTION_ON && g_channel_status[i] == CHANNEL_ONLINE)
		{
			test_channel |= (1u << i);
		}
	}
	
	do
	{
		/* wait until idle */
		uint8_t idle_status = 0x00;
		
		do
		{				
			ret = test_content_query(&channel_test_content, rt_tick_from_millisecond(QUERY_CONTENT_INTERVAL));
			if (ret == RT_EOK)
			{
				if (channel_test_content.test_status == TEST_STATUS_IDLE)
				{
					idle_status |= (1u << channel_test_content.channel);

					if (idle_status == test_channel)
					{
						break;
					}
				}
			}
			
		} while (RT_TRUE);
			
		/* wait for device plugged in */
		rt_thread_delay(rt_tick_from_millisecond(QUERY_CONTENT_INTERVAL));

		if (get_cur_voltage(SLAVE_PORT_0) <= EMPTY_LOAD_VOLTAGE_THREASHOULD)
		{
			continue;
		}

		/* notify UI, clear result */
		s_test_result.test_step = TEST_STEP_NONE;

		s_test_result.test_content.channel = SLAVE_PORT_0;
		s_test_result.test_content.test_type = TEST_TYPE_NONE;
		s_test_result.test_content.test_status = TEST_STATUS_IDLE;
		s_test_result.test_content.ac_current = channel_test_content.ac_current;
		s_test_result.test_content.voltage = channel_test_content.voltage;
		s_test_result.test_content.current = channel_test_content.current;
					
		refresh_test_result(&s_test_result);
		
		complete = 0x00;
		channel_test_result = test_channel;
		
		/* empty load test */
		for (i = 0; i < CHANNEL_COUNT; i++)
		{
			if (test_channel & (1u << i))
			{
				test_cmd.channel   = (slave_com_port)i;
				test_cmd.test_type = TEST_TYPE_EMPTY_LOAD_TEST;

				if (s_cur_test_category == TEST_CATEGORY_SYNTH_TEST)
				{
					test_cmd.test_config.empty_load_test_config.duration = s_synth_test_setting->empty_load_test_setting.duration;
					test_cmd.test_config.empty_load_test_config.ac_upper = s_synth_test_setting->empty_load_test_setting.ac_limit;
					test_cmd.test_config.empty_load_test_config.voltage_lower = actual_to_measure_voltage(i, s_synth_test_setting->empty_load_test_setting.voltage_from);
					test_cmd.test_config.empty_load_test_config.voltage_upper = actual_to_measure_voltage(i, s_synth_test_setting->empty_load_test_setting.voltage_to);
				}
				else if (s_cur_test_category == TEST_CATEGORY_QC_20_TEST)
				{
					test_cmd.test_config.empty_load_test_config.duration = s_qc_20_test_setting->empty_load_test_setting.duration;
					test_cmd.test_config.empty_load_test_config.ac_upper = s_qc_20_test_setting->empty_load_test_setting.ac_limit;
					test_cmd.test_config.empty_load_test_config.voltage_lower = actual_to_measure_voltage(i, s_qc_20_test_setting->empty_load_test_setting.voltage_from);
					test_cmd.test_config.empty_load_test_config.voltage_upper = actual_to_measure_voltage(i, s_qc_20_test_setting->empty_load_test_setting.voltage_to);
				}
				else
				{

				}
				
				test_cmd_notify(&test_cmd);

				test_step[i] = TEST_STEP_EMPTY_LOAD;

				TRACE("start empty load test\n");

				/* delay some time */
				rt_thread_delay(rt_tick_from_millisecond(QUERY_CONTENT_INTERVAL));
			}
		}

		while (complete != test_channel)
		{
			/* not complete all yet */
			
			/* wait for reply */
			do
			{				
				ret = test_content_query(&channel_test_content, rt_tick_from_millisecond(QUERY_CONTENT_INTERVAL));			
			} while (ret != RT_EOK);

			if (channel_test_content.test_status == TEST_STATUS_ON)
			{
				if (channel_test_content.channel == SLAVE_PORT_0)
				{
					s_refresh_count++;
					if (s_refresh_count == 5)
					{
						/* notify UI */
						s_test_result.test_step = test_step[SLAVE_PORT_0];
						s_test_result.test_content = channel_test_content;
						
						refresh_test_result(&s_test_result);

						s_refresh_count = 0;
					}
				}
			}
			else if (channel_test_content.test_status == TEST_STATUS_ABNORMAL)
			{
				/* abnormal */
				if (channel_test_content.channel == SLAVE_PORT_0)
				{
					/* notify UI */
					s_test_result.test_step = test_step[SLAVE_PORT_0];
					s_test_result.test_content = channel_test_content;
					
					refresh_test_result(&s_test_result);
				}

				if (discharge_enable)
				{
					/* discharge test */
					test_cmd.channel   = channel_test_content.channel;
					test_cmd.test_type = TEST_TYPE_DISCHARGE_TEST;

					if (s_cur_test_category == TEST_CATEGORY_SYNTH_TEST)
					{
						test_cmd.test_config.discharge_test_config.duration = s_synth_test_setting->discharge_test_setting.discharge_duration;
						test_cmd.test_config.discharge_test_config.current_val = s_synth_test_setting->discharge_test_setting.discharge_current;
					}
					else if (s_cur_test_category == TEST_CATEGORY_QC_20_TEST)
					{
						test_cmd.test_config.discharge_test_config.duration = s_qc_20_test_setting->discharge_test_setting.discharge_duration;
						test_cmd.test_config.discharge_test_config.current_val = s_qc_20_test_setting->discharge_test_setting.discharge_current;
					}
					else
					{

					}
					
					test_cmd_notify(&test_cmd);

					test_step[channel_test_content.channel] = TEST_STEP_DISCHARGE;
				}
				else
				{
					/* test fail */
					fail_led_on((ch_led)(channel_test_content.channel));
						
					complete |= (1u << channel_test_content.channel);

					/* stop test */
					test_cmd.test_type = TEST_TYPE_NONE;
					test_cmd_notify(&test_cmd);	
					
					test_step[channel_test_content.channel] = TEST_STEP_NONE;
				}

				/* update result */
				channel_test_result &= ~(1u << channel_test_content.channel);
			}
			else if (channel_test_content.test_status == TEST_STATUS_NORMAL)
			{
				/* passed the test */
				test_cmd.channel = channel_test_content.channel;

				if (channel_test_content.channel == SLAVE_PORT_0)
				{
					/* notify UI */
					s_test_result.test_step = test_step[SLAVE_PORT_0];
					s_test_result.test_content = channel_test_content;
					
					refresh_test_result(&s_test_result);
				}
				
				switch (test_step[channel_test_content.channel])
				{
					/* empty test over */
				case TEST_STEP_EMPTY_LOAD:

					/* step 2 test over */
				case TEST_STEP_2:

					/* step 3 test over */
				case TEST_STEP_3:

					/* step 4 test over */
				case TEST_STEP_4:
		
					/* step 5 test over */
				case TEST_STEP_5:

					/* step 6 test over */
				case TEST_STEP_6:

					/* step 7 test over */
				case TEST_STEP_7:
					if (s_cur_test_category == TEST_CATEGORY_SYNTH_TEST)
					{
						for (i = test_step[channel_test_content.channel]; 
								i < sizeof(s_synth_test_setting->synth_normal_test_setting) / sizeof(s_synth_test_setting->synth_normal_test_setting[0]);
								i++)
						{
							if (s_synth_test_setting->synth_normal_test_setting[i].on_off == OPTION_ON)
							{
								break;
							}
						}

						if (i < sizeof(s_synth_test_setting->synth_normal_test_setting) / sizeof(s_synth_test_setting->synth_normal_test_setting[0]))
						{
							/* still has the rest test */
							test_cmd.test_type = s_synth_test_type[s_synth_test_setting->synth_normal_test_setting[i].test_type];
							form_synth_test_config((int)channel_test_content.channel, &test_cmd.test_config, &s_synth_test_setting->synth_normal_test_setting[i]);

							test_cmd_notify(&test_cmd);

							test_step[channel_test_content.channel] = (TEST_STEP)(TEST_STEP_2 + i);
						}
						else
						{
							/* all is passed */
							if (discharge_enable)
							{
								/* do discharge test */
								test_cmd.test_type = TEST_TYPE_DISCHARGE_TEST;
								test_cmd.test_config.discharge_test_config.duration = s_synth_test_setting->discharge_test_setting.discharge_duration;
								test_cmd.test_config.discharge_test_config.current_val = s_synth_test_setting->discharge_test_setting.discharge_current;
								
								test_cmd_notify(&test_cmd);

								test_step[channel_test_content.channel] = TEST_STEP_DISCHARGE;
							}
							else
							{
								/* test pass */
								pass_led_on((ch_led)(channel_test_content.channel));
								
								complete |= (1u << channel_test_content.channel);

								/* stop test */
								test_cmd.test_type = TEST_TYPE_NONE;
								test_cmd_notify(&test_cmd);	
					
								test_step[channel_test_content.channel] = TEST_STEP_NONE;
							}
							
						}
					}
					else if (s_cur_test_category == TEST_CATEGORY_QC_20_TEST)
					{
						for (i = test_step[channel_test_content.channel]; 
								i < sizeof(s_qc_20_test_setting->qc_20_normal_test_setting) / sizeof(s_qc_20_test_setting->qc_20_normal_test_setting[0]);
								i++)
						{
							if (s_qc_20_test_setting->qc_20_normal_test_setting[i].on_off == OPTION_ON)
							{
								break;
							}
						}

						if (i < sizeof(s_qc_20_test_setting->qc_20_normal_test_setting) / sizeof(s_qc_20_test_setting->qc_20_normal_test_setting[0]))
						{
							/* still has the rest test */
							test_cmd.test_type = s_qc_20_test_type[s_qc_20_test_setting->qc_20_normal_test_setting[i].test_type];
							form_qc_20_test_config((int)channel_test_content.channel, &test_cmd.test_config, &s_qc_20_test_setting->qc_20_normal_test_setting[i]);

							test_cmd_notify(&test_cmd);

							test_step[channel_test_content.channel] = (TEST_STEP)(TEST_STEP_2 + i);
						}
						else
						{
							/* all is passed */
							if (discharge_enable)
							{
								/* do discharge test */
								test_cmd.test_type = TEST_TYPE_DISCHARGE_TEST;
								test_cmd.test_config.discharge_test_config.duration = s_qc_20_test_setting->discharge_test_setting.discharge_duration;
								test_cmd.test_config.discharge_test_config.current_val = s_qc_20_test_setting->discharge_test_setting.discharge_current;

								test_cmd_notify(&test_cmd);

								test_step[channel_test_content.channel] = TEST_STEP_DISCHARGE;
							}
							else
							{
								/* test pass */
								pass_led_on((ch_led)(channel_test_content.channel));
								
								complete |= (1u << channel_test_content.channel);

								/* stop test */
								test_cmd.test_type = TEST_TYPE_NONE;
								test_cmd_notify(&test_cmd);	
					
								test_step[channel_test_content.channel] = TEST_STEP_NONE;
							}	
						}
					}
					else
					{
						/* MTK */
					}		

					break;

				case TEST_STEP_DISCHARGE:
					complete |= (1u << channel_test_content.channel);

					if (channel_test_result & (1u << channel_test_content.channel))
					{
						/* test pass */
						pass_led_on((ch_led)(channel_test_content.channel));
					}
					else
					{
						/* test fail */
						fail_led_on((ch_led)(channel_test_content.channel));
					}

#if 0
					/* stop test */
					test_cmd.test_type = TEST_TYPE_NONE;
					test_cmd_notify(&test_cmd);	
					
					test_step[channel_test_content.channel] = TEST_STEP_NONE;
#endif					
					break;
					
				default:
				
					break;
				}
			}
		}

		if (channel_test_result & (1u << 0))
		{
			/* passed */
			beeper_beep(BEEPER_VOL_HIGH, 50, 50, 2);
		}
		else
		{
			beeper_beep(BEEPER_VOL_HIGH, 500, 50, 1);
		}

		if (discharge_enable)
		{
			/* delay to indicate */
			if (s_cur_test_category == TEST_CATEGORY_SYNTH_TEST)
			{
				rt_thread_delay(rt_tick_from_millisecond(s_synth_test_setting->discharge_test_setting.indicate_delay));
			}
			else if (s_cur_test_category == TEST_CATEGORY_QC_20_TEST)
			{
				rt_thread_delay(rt_tick_from_millisecond(s_qc_20_test_setting->discharge_test_setting.indicate_delay));
			}
			else
			{

			}

#if 1
			/* notify to stop test */
			test_cmd.channel   = SLAVE_PORT_ALL;
			test_cmd.test_type = TEST_TYPE_NONE;
			
			test_cmd_notify(&test_cmd);	
			
			for (i = 0; i < CHANNEL_COUNT; i++)
			{
				test_step[i] = TEST_STEP_NONE;
			}

			rt_thread_delay(rt_tick_from_millisecond(200)); 
#endif
		}
		else
		{
			do
			{
				/* wait for device plugged in */
				rt_thread_delay(rt_tick_from_millisecond(200));
				
			} while (get_cur_voltage(SLAVE_PORT_0) >= EMPTY_LOAD_VOLTAGE_THREASHOULD);
		}
					
		/* turn off led */
		all_pass_led_off();
		all_fail_led_off();
	} while (RT_TRUE);
}

static void init_test_thread(void)
{
	s_test_thread = rt_thread_create("test", test_thread_entry, RT_NULL, 1024, TEST_THREAD_PRIORITY, 10);
	RT_ASSERT(s_test_thread != RT_NULL);

	rt_thread_startup(s_test_thread);
}

static void init_callback(void *msg)
{
	s_cur_test_category = get_cur_test_category();
	
	load_parameter(STRUCT_OFFSET(PARAMETER, channel_set), s_channel_set, sizeof(s_channel_set));
	
	load_parameter(STRUCT_OFFSET(PARAMETER, phone_number_setting), &s_phone_number_setting, sizeof(s_phone_number_setting));

	if (s_cur_test_category == TEST_CATEGORY_SYNTH_TEST)
	{
		draw_synth_test_caption();
	}
	else if (s_cur_test_category == TEST_CATEGORY_QC_20_TEST)
	{
		draw_qc_20_test_caption();
	}
	else
	{

	}

	draw_test_menu_const();

	draw_test_group(get_test_group() + 1);
	
	lcd_validate_cmd();

	if (s_cur_test_category == TEST_CATEGORY_SYNTH_TEST)
	{
		s_synth_test_setting = get_synth_test_setting();
	
		draw_synth_test_menu(s_synth_test_setting);
	}
	else if (s_cur_test_category == TEST_CATEGORY_QC_20_TEST)
	{
		s_qc_20_test_setting = get_qc_20_test_setting();

		draw_qc_20_test_menu(s_qc_20_test_setting);
	}
	else
	{

	}

	if (s_phone_number_setting.customer_phone_number_power_on_count >= s_phone_number_setting.customer_phone_number_power_on_limit)
	{
		draw_synth_test_phone_number(&s_phone_number_setting.default_phone_number);
	}
	else
	{
		draw_synth_test_phone_number(&s_phone_number_setting.customer_phone_number);
	}

	lcd_validate_cmd();

	init_test_thread();
}

static void destroy_callback(void *msg)
{
	lcd_clear(SCREEN_BACK_COLOR);
}

BEGIN_MENU_HANDLER(MENU_ID_SYNTH_TEST)

IMPLEMENT_MSG_HANDLER(MSG_ID_KEY, key_handler)
IMPLEMENT_MSG_HANDLER(MSG_ID_SYNTH_TEST, synth_test_handler)
IMPLEMENT_MSG_HANDLER(MSG_ID_INIT, init_callback)
IMPLEMENT_MSG_HANDLER(MSG_ID_DESTROY, destroy_callback)

END_MENU_HANDLER()

