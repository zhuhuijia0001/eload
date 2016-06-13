#include <stdint.h>
#include "type.h"
#include "key_define.h"

#include "menu_op.h"
#include "menu.h"

#include "lcd.h"
#include "draw.h"

#include "beeper.h"

/* item */
typedef enum 
{
	OC_SETTING_TIME,
	
	OC_SETTING_AC,
	
	OC_SETTING_OC_VAL,
	
	OC_SETTING_NONE,
	
	OC_SETTING_COUNT = OC_SETTING_NONE
} oc_setting_item;

static oc_setting_item s_focus_item = OC_SETTING_NONE;

static oc_setting_item s_edit_item = OC_SETTING_NONE;

static OVER_CURRENT_TEST_SETTING s_over_current_test_setting;

/* max test interval */
static const uint32_t MAX_TEST_INTERVAL = 500ul;

static const uint32_t BIG_TEST_INTERVAL_STEP = 1000ul;

static const uint32_t SMALL_TEST_INTERVAL_STEP = 100ul;

/* max ac */
static const uint32_t MAX_AC = 999000ul;

static const uint32_t BIG_AC_STEP = 10000ul;

static const uint32_t SMALL_AC_STEP = 1000ul;

/* max current */
static const uint32_t MAX_CURRENT = 6000ul;

static const uint32_t BIG_CURRENT_STEP = 1000ul;

static const uint32_t SMALL_CURRENT_STEP = 10ul;

static uint32_t s_cur_interval;
static uint32_t s_cur_ac;
static uint32_t s_cur_current;

extern int get_cur_test_setting_step(void);

extern TEST_CATEGORY get_cur_test_category(void);

extern QC_20_TEST_TYPE get_cur_qc_20_test_type(int step);

extern bool get_test_oc_setting(int step, OVER_CURRENT_TEST_SETTING *oc_test_setting);
extern bool set_test_oc_setting(int step, const OVER_CURRENT_TEST_SETTING *oc_test_setting);

/* unfocus function */
static void unfocus_time(void)
{
	draw_normal_oc_setting_time(s_over_current_test_setting.interval);
}

static void unfocus_ac(void)
{
	draw_normal_oc_setting_ac(s_over_current_test_setting.ac_limit);
}

static void unfocus_oc_val(void)
{
	draw_normal_oc_setting_oc(s_over_current_test_setting.current_limit);
}

static void (*const s_unfocus_fun_arr[])(void) = 
{
	[OC_SETTING_TIME]         = unfocus_time,
	
	[OC_SETTING_AC]           = unfocus_ac,
	
	[OC_SETTING_OC_VAL]       = unfocus_oc_val
};

/* focus function */
static void focus_time(void)
{
	draw_focus_oc_setting_time(s_over_current_test_setting.interval);
}

static void focus_ac(void)
{
	draw_focus_oc_setting_ac(s_over_current_test_setting.ac_limit);
}

static void focus_oc_val(void)
{
	draw_focus_oc_setting_oc(s_over_current_test_setting.current_limit);
}

static void (*const s_focus_fun_arr[])(void) = 
{
	[OC_SETTING_TIME]         = focus_time,
	
	[OC_SETTING_AC]           = focus_ac,
	
	[OC_SETTING_OC_VAL]       = focus_oc_val
};

/* enter edit function */
static void enter_edit_time(void)
{
	s_cur_interval = s_over_current_test_setting.interval;
	draw_edit_oc_setting_time(s_cur_interval);
	
	s_edit_item = OC_SETTING_TIME;
}

static void enter_edit_ac(void)
{
	s_cur_ac = s_over_current_test_setting.ac_limit;
	draw_edit_oc_setting_ac(s_cur_ac);
	
	s_edit_item = OC_SETTING_AC;
}

static void enter_edit_oc_val(void)
{
	s_cur_current = s_over_current_test_setting.current_limit;
	draw_edit_oc_setting_oc(s_cur_current);
	
	s_edit_item = OC_SETTING_OC_VAL;
}

static void (*const s_enter_edit_fun_arr[])(void) = 
{
	[OC_SETTING_TIME]         = enter_edit_time,
	
	[OC_SETTING_AC]           = enter_edit_ac,
	
	[OC_SETTING_OC_VAL]       = enter_edit_oc_val
};

/* confirm edit function */
static void confirm_edit_time(void)
{
	s_over_current_test_setting.interval = s_cur_interval;
	draw_focus_oc_setting_time(s_over_current_test_setting.interval);
}

static void confirm_edit_ac(void)
{
	s_over_current_test_setting.ac_limit = s_cur_ac;
	draw_focus_oc_setting_ac(s_over_current_test_setting.ac_limit);
}

static void confirm_edit_oc_val(void)
{
	s_over_current_test_setting.current_limit = s_cur_current;
	draw_focus_oc_setting_oc(s_over_current_test_setting.current_limit);
}

static void (*const s_confirm_edit_fun_arr[])(void) = 
{
	[OC_SETTING_TIME]         = confirm_edit_time,
	
	[OC_SETTING_AC]           = confirm_edit_ac,
	
	[OC_SETTING_OC_VAL]       = confirm_edit_oc_val
};

/* edit function */
static void edit_time(uint8_t key)
{
	if (key == KEY_UP)
	{
		s_cur_interval += BIG_TEST_INTERVAL_STEP;
		if (s_cur_interval > MAX_TEST_INTERVAL)
		{
			s_cur_interval = MAX_TEST_INTERVAL;
		}
		draw_edit_oc_setting_time(s_cur_interval);
	}
	else if (key == KEY_DOWN)
	{
		if (s_cur_interval > BIG_TEST_INTERVAL_STEP)
		{
			s_cur_interval -= BIG_TEST_INTERVAL_STEP;
		}
		else
		{
			s_cur_interval = SMALL_TEST_INTERVAL_STEP;
		}
		draw_edit_oc_setting_time(s_cur_interval);
	}
	else if (key == KEY_RIGHT)
	{
		s_cur_interval += SMALL_TEST_INTERVAL_STEP;
		if (s_cur_interval > MAX_TEST_INTERVAL)
		{
			s_cur_interval = MAX_TEST_INTERVAL;
		}
		draw_edit_oc_setting_time(s_cur_interval);
	}
	else if (key == KEY_LEFT)
	{
		if (s_cur_interval > SMALL_TEST_INTERVAL_STEP)
		{
			s_cur_interval -= SMALL_TEST_INTERVAL_STEP;
		}
		draw_edit_oc_setting_time(s_cur_interval);
	}
}

static void edit_ac(uint8_t key)
{
	if (key == KEY_UP)
	{
		s_cur_ac += BIG_AC_STEP;
		if (s_cur_ac > MAX_AC)
		{
			s_cur_ac = MAX_AC;
		}
		draw_edit_oc_setting_ac(s_cur_ac);
	}
	else if (key == KEY_DOWN)
	{
		if (s_cur_ac > BIG_AC_STEP)
		{
			s_cur_ac -= BIG_AC_STEP;
		}
		else
		{
			s_cur_ac = SMALL_AC_STEP;
		}
		draw_edit_oc_setting_ac(s_cur_ac);
	}
	else if (key == KEY_RIGHT)
	{
		s_cur_ac += SMALL_AC_STEP;
		if (s_cur_ac > MAX_AC)
		{
			s_cur_ac = MAX_AC;
		}
		draw_edit_oc_setting_ac(s_cur_ac);
	}
	else if (key == KEY_LEFT)
	{
		if (s_cur_ac > SMALL_AC_STEP)
		{
			s_cur_ac -= SMALL_AC_STEP;
		}
		draw_edit_oc_setting_ac(s_cur_ac);
	}
}

static void edit_oc_val(uint8_t key)
{
	if (key == KEY_UP)
	{
		s_cur_current += BIG_CURRENT_STEP;
		if (s_cur_current > MAX_CURRENT)
		{
			s_cur_current = MAX_CURRENT;
		}
		draw_edit_oc_setting_oc(s_cur_current);
	}
	else if (key == KEY_DOWN)
	{
		if (s_cur_current > BIG_CURRENT_STEP)
		{
			s_cur_current -= BIG_CURRENT_STEP;
		}
		else
		{
			s_cur_current = SMALL_CURRENT_STEP;
		}
		draw_edit_oc_setting_oc(s_cur_current);
	}
	else if (key == KEY_RIGHT)
	{
		s_cur_current += SMALL_CURRENT_STEP;
		if (s_cur_current > MAX_CURRENT)
		{
			s_cur_current = MAX_CURRENT;
		}
		draw_edit_oc_setting_oc(s_cur_current);
	}
	else if (key == KEY_LEFT)
	{
		if (s_cur_current > SMALL_CURRENT_STEP)
		{
			s_cur_current -= SMALL_CURRENT_STEP;
		}
		draw_edit_oc_setting_oc(s_cur_current);
	}
}

static void (*const s_edit_fun_arr[])(uint8_t key) = 
{
	[OC_SETTING_TIME]         = edit_time,
	
	[OC_SETTING_AC]           = edit_ac,
	
	[OC_SETTING_OC_VAL]       = edit_oc_val,
};

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
	
	if (key == KEY_LEFT || key == KEY_UP)
	{
		if (s_edit_item == OC_SETTING_NONE)
		{
			s_unfocus_fun_arr[s_focus_item]();
			
			s_focus_item += OC_SETTING_COUNT - 1;
			s_focus_item %= OC_SETTING_COUNT;
			
			s_focus_fun_arr[s_focus_item]();
		}
		else
		{
			s_edit_fun_arr[s_edit_item](key);
		}
		
		lcd_validate_cmd();
	}
	else if (key == KEY_RIGHT || key == KEY_DOWN)
	{
		if (s_edit_item == OC_SETTING_NONE)
		{
			s_unfocus_fun_arr[s_focus_item]();
			
			s_focus_item++;
			s_focus_item %= OC_SETTING_COUNT;
			
			s_focus_fun_arr[s_focus_item]();
		}
		else
		{
			s_edit_fun_arr[s_edit_item](key);
		}

		lcd_validate_cmd();
	}
	else if (key == KEY_OK)
	{
		if (s_edit_item == OC_SETTING_NONE)
		{
			s_enter_edit_fun_arr[s_focus_item]();
		}
		else
		{
			s_confirm_edit_fun_arr[s_focus_item]();
			
			s_edit_item = OC_SETTING_NONE;
		}
		
		lcd_validate_cmd();
	}
	else if (key == KEY_CANCEL)
	{
		if (s_edit_item == OC_SETTING_NONE)
		{
			/* save */
			int step = get_cur_test_setting_step();
			set_test_oc_setting(step, &s_over_current_test_setting);
			
			switch_to_menu(MENU_ID_SYNTH_TEST_SETTING);
		}
		else
		{
			s_focus_fun_arr[s_focus_item]();
			
			lcd_validate_cmd();
			
			s_edit_item = OC_SETTING_NONE;
		}
	}	
}

static void init_callback(void *msg)
{
	int step = get_cur_test_setting_step();

	TEST_CATEGORY test_category = get_cur_test_category();
	if (test_category == TEST_CATEGORY_SYNTH_TEST)
	{
		draw_synth_oc_setting_caption();
	}
	else if (test_category == TEST_CATEGORY_QC_20_TEST)
	{
		QC_20_TEST_TYPE qc_20_test_type = get_cur_qc_20_test_type(step);
		if (qc_20_test_type == QC_20_5V_TEST_OVER_CURRENT)
		{
			draw_qc_20_5v_oc_setting_caption();
		}
		else if (qc_20_test_type == QC_20_9V_TEST_OVER_CURRENT)
		{
			draw_qc_20_9v_oc_setting_caption();
		}
		else if (qc_20_test_type == QC_20_12V_TEST_OVER_CURRENT)
		{
			draw_qc_20_12v_oc_setting_caption();
		}
		else if (qc_20_test_type == QC_20_20V_TEST_OVER_CURRENT)
		{
			draw_qc_20_20v_oc_setting_caption();
		}
	}

	get_test_oc_setting(step, &s_over_current_test_setting);
	
	draw_oc_setting_menu();
	
	draw_focus_oc_setting_time(s_over_current_test_setting.interval);
	
	draw_normal_oc_setting_ac(s_over_current_test_setting.ac_limit);
	
	draw_normal_oc_setting_oc(s_over_current_test_setting.current_limit);
	
	lcd_validate_cmd();
	
	s_focus_item = OC_SETTING_TIME;

	s_edit_item = OC_SETTING_NONE;
}

static void destroy_callback(void *msg)
{
	lcd_clear(SCREEN_BACK_COLOR);
}

BEGIN_MENU_HANDLER(MENU_ID_OVER_CURRENT_SETTING)

IMPLEMENT_MSG_HANDLER(MSG_ID_KEY, key_handler)
IMPLEMENT_MSG_HANDLER(MSG_ID_INIT, init_callback)
IMPLEMENT_MSG_HANDLER(MSG_ID_DESTROY, destroy_callback)

END_MENU_HANDLER()

