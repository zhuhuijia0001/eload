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
	SHORT_SETTING_TIME,
	
	SHORT_SETTING_AC,
	
	SHORT_SETTING_SHORT_VAL,
	
	SHORT_SETTING_NONE,
	
	SHORT_SETTING_COUNT = SHORT_SETTING_NONE
} short_setting_item;

static short_setting_item s_focus_item = SHORT_SETTING_TIME;

static short_setting_item s_edit_item = SHORT_SETTING_NONE;

/* short test setting */
static SHORT_TEST_SETTING s_short_test_setting;

/* max test duration */
static const uint32_t MAX_TEST_DURATION = 10000ul;

static const uint32_t BIG_TEST_DURATION_STEP = 1000ul;

static const uint32_t SMALL_TEST_DURATION_STEP = 100ul;

/* max ac */
static const uint32_t MAX_AC = 999000ul;

static const uint32_t BIG_AC_STEP = 10000ul;

static const uint32_t SMALL_AC_STEP = 1000ul;

/* max current */
static const uint32_t MAX_CURRENT = 6000ul;

static const uint32_t BIG_CURRENT_STEP = 1000ul;

static const uint32_t SMALL_CURRENT_STEP = 10ul;

static uint32_t s_cur_duration;
static uint32_t s_cur_ac;
static uint32_t s_cur_current;

extern int get_cur_test_setting_step(void);

extern TEST_CATEGORY get_cur_test_category(void);

extern QC_20_TEST_TYPE get_cur_qc_20_test_type(int step);

extern bool get_test_short_setting(int step, SHORT_TEST_SETTING *short_test_setting);
extern bool set_test_short_setting(int step, const SHORT_TEST_SETTING *short_test_setting);

/* unfocus function */
static void unfocus_time(void)
{
	draw_normal_short_setting_time(s_short_test_setting.duration);
}

static void unfocus_ac(void)
{
	draw_normal_short_setting_ac(s_short_test_setting.ac_limit);
}

static void unfocus_short_val(void)
{
	draw_normal_short_setting_short(s_short_test_setting.short_limit);
}

static void (*const s_unfocus_fun_arr[])(void) = 
{
	[SHORT_SETTING_TIME]         = unfocus_time,
	
	[SHORT_SETTING_AC]           = unfocus_ac,
	
	[SHORT_SETTING_SHORT_VAL]    = unfocus_short_val
};

/* focus function */
static void focus_time(void)
{
	draw_focus_short_setting_time(s_short_test_setting.duration);
}

static void focus_ac(void)
{
	draw_focus_short_setting_ac(s_short_test_setting.ac_limit);
}

static void focus_short_val(void)
{
	draw_focus_short_setting_short(s_short_test_setting.short_limit);
}

static void (*const s_focus_fun_arr[])(void) = 
{
	[SHORT_SETTING_TIME]         = focus_time,
	
	[SHORT_SETTING_AC]           = focus_ac,
	
	[SHORT_SETTING_SHORT_VAL]    = focus_short_val
};

/* enter edit function */
static void enter_edit_time(void)
{
	s_cur_duration = s_short_test_setting.duration;
	draw_edit_short_setting_time(s_cur_duration);
	
	s_edit_item = SHORT_SETTING_TIME;
}

static void enter_edit_ac(void)
{
	s_cur_ac = s_short_test_setting.ac_limit;
	draw_edit_short_setting_ac(s_cur_ac);
	
	s_edit_item = SHORT_SETTING_AC;
}

static void enter_edit_short_val(void)
{
	s_cur_current = s_short_test_setting.short_limit;
	draw_edit_short_setting_short(s_cur_current);
	
	s_edit_item = SHORT_SETTING_SHORT_VAL;
}

static void (*const s_enter_edit_fun_arr[])(void) = 
{
	[SHORT_SETTING_TIME]         = enter_edit_time,
	
	[SHORT_SETTING_AC]           = enter_edit_ac,
	
	[SHORT_SETTING_SHORT_VAL]    = enter_edit_short_val
};

/* confirm edit function */
static void confirm_edit_time(void)
{
	s_short_test_setting.duration = s_cur_duration;
	draw_focus_short_setting_time(s_short_test_setting.duration);
}

static void confirm_edit_ac(void)
{
	s_short_test_setting.ac_limit = s_cur_ac;
	draw_focus_short_setting_ac(s_short_test_setting.ac_limit);
}

static void confirm_edit_short_val(void)
{
	s_short_test_setting.short_limit = s_cur_current;
	draw_focus_short_setting_short(s_short_test_setting.short_limit);
}

static void (*const s_confirm_edit_fun_arr[])(void) = 
{
	[SHORT_SETTING_TIME]         = confirm_edit_time,
	
	[SHORT_SETTING_AC]           = confirm_edit_ac,
	
	[SHORT_SETTING_SHORT_VAL]    = confirm_edit_short_val
};

/* edit function */
static void edit_time(uint8_t key)
{
	if (key == KEY_UP)
	{
		s_cur_duration += BIG_TEST_DURATION_STEP;
		if (s_cur_duration > MAX_TEST_DURATION)
		{
			s_cur_duration = MAX_TEST_DURATION;
		}
		draw_edit_short_setting_time(s_cur_duration);
	}
	else if (key == KEY_DOWN)
	{
		if (s_cur_duration > BIG_TEST_DURATION_STEP)
		{
			s_cur_duration -= BIG_TEST_DURATION_STEP;
		}
		else
		{
			s_cur_duration = SMALL_TEST_DURATION_STEP;
		}
		draw_edit_short_setting_time(s_cur_duration);
	}
	else if (key == KEY_RIGHT)
	{
		s_cur_duration += SMALL_TEST_DURATION_STEP;
		if (s_cur_duration > MAX_TEST_DURATION)
		{
			s_cur_duration = MAX_TEST_DURATION;
		}
		draw_edit_short_setting_time(s_cur_duration);
	}
	else if (key == KEY_LEFT)
	{
		if (s_cur_duration > SMALL_TEST_DURATION_STEP)
		{
			s_cur_duration -= SMALL_TEST_DURATION_STEP;
		}
		draw_edit_short_setting_time(s_cur_duration);
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
		draw_edit_short_setting_ac(s_cur_ac);
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
		draw_edit_short_setting_ac(s_cur_ac);
	}
	else if (key == KEY_RIGHT)
	{
		s_cur_ac += SMALL_AC_STEP;
		if (s_cur_ac > MAX_AC)
		{
			s_cur_ac = MAX_AC;
		}
		draw_edit_short_setting_ac(s_cur_ac);
	}
	else if (key == KEY_LEFT)
	{
		if (s_cur_ac > SMALL_AC_STEP)
		{
			s_cur_ac -= SMALL_AC_STEP;
		}
		draw_edit_short_setting_ac(s_cur_ac);
	}
}

static void edit_short_val(uint8_t key)
{
	if (key == KEY_UP)
	{
		s_cur_current += BIG_CURRENT_STEP;
		if (s_cur_current > MAX_CURRENT)
		{
			s_cur_current = MAX_CURRENT;
		}
		draw_edit_short_setting_short(s_cur_current);
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
		draw_edit_short_setting_short(s_cur_current);
	}
	else if (key == KEY_RIGHT)
	{
		s_cur_current += SMALL_CURRENT_STEP;
		if (s_cur_current > MAX_CURRENT)
		{
			s_cur_current = MAX_CURRENT;
		}
		draw_edit_short_setting_short(s_cur_current);
	}
	else if (key == KEY_LEFT)
	{
		if (s_cur_current > SMALL_CURRENT_STEP)
		{
			s_cur_current -= SMALL_CURRENT_STEP;
		}
		draw_edit_short_setting_short(s_cur_current);
	}
}

static void (*const s_edit_fun_arr[])(uint8_t key) = 
{
	[SHORT_SETTING_TIME]         = edit_time,
	
	[SHORT_SETTING_AC]           = edit_ac,
	
	[SHORT_SETTING_SHORT_VAL]    = edit_short_val,
};

static void key_handler(void *msg)
{
	key_t key_msg = (key_t)(uint32_t)msg;
	uint8_t key = KEY_VALUE(key_msg);
	
	if (KEY_TYPE(key_msg) == MASK_KEY_RELEASE)
	{
		return;
	}

	beeper_beep(BEEPER_VOL_LOW, 50, 50, 1);
	
	if (key == KEY_LEFT || key == KEY_UP)
	{
		if (s_edit_item == SHORT_SETTING_NONE)
		{
			s_unfocus_fun_arr[s_focus_item]();
			
			s_focus_item += SHORT_SETTING_COUNT - 1;
			s_focus_item %= SHORT_SETTING_COUNT;
			
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
		if (s_edit_item == SHORT_SETTING_NONE)
		{
			s_unfocus_fun_arr[s_focus_item]();
			
			s_focus_item++;
			s_focus_item %= SHORT_SETTING_COUNT;
			
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
		if (s_edit_item == SHORT_SETTING_NONE)
		{
			s_enter_edit_fun_arr[s_focus_item]();
		}
		else
		{
			s_confirm_edit_fun_arr[s_focus_item]();
			
			s_edit_item = SHORT_SETTING_NONE;
		}
		
		lcd_validate_cmd();
	}
	else if (key == KEY_CANCEL)
	{
		if (s_edit_item == SHORT_SETTING_NONE)
		{
			/* save */
			int step = get_cur_test_setting_step();
			set_test_short_setting(step, &s_short_test_setting);
			
			switch_to_menu(MENU_ID_SYNTH_TEST_SETTING);
		}
		else
		{
			s_focus_fun_arr[s_focus_item]();
			
			lcd_validate_cmd();
			
			s_edit_item = SHORT_SETTING_NONE;
		}
	}	
}

static void init_callback(void *msg)
{
	int step = get_cur_test_setting_step();

	TEST_CATEGORY test_category = get_cur_test_category();
	if (test_category == TEST_CATEGORY_SYNTH_TEST)
	{
		draw_synth_short_setting_caption();
	}
	else if (test_category == TEST_CATEGORY_QC_20_TEST)
	{
		QC_20_TEST_TYPE qc_20_test_type = get_cur_qc_20_test_type(step);
		if (qc_20_test_type == QC_20_5V_TEST_SHORT)
		{
			draw_qc_20_5v_short_setting_caption();
		}
		else if (qc_20_test_type == QC_20_9V_TEST_SHORT)
		{
			draw_qc_20_9v_short_setting_caption();
		}
		else if (qc_20_test_type == QC_20_12V_TEST_SHORT)
		{
			draw_qc_20_12v_short_setting_caption();
		}
		else if (qc_20_test_type == QC_20_20V_TEST_SHORT)
		{
			draw_qc_20_20v_short_setting_caption();
		}
	}
	
	get_test_short_setting(step, &s_short_test_setting);
	
	draw_short_setting_menu();
	
	draw_focus_short_setting_time(s_short_test_setting.duration);
	
	draw_normal_short_setting_ac(s_short_test_setting.ac_limit);
	
	draw_normal_short_setting_short(s_short_test_setting.short_limit);
	
	lcd_validate_cmd();
	
	s_focus_item = SHORT_SETTING_TIME;

	s_edit_item = SHORT_SETTING_NONE;	
}

static void destroy_callback(void *msg)
{
	lcd_clear(SCREEN_BACK_COLOR);
}

BEGIN_MENU_HANDLER(MENU_ID_SHORT_SETTING)

IMPLEMENT_MSG_HANDLER(MSG_ID_KEY, key_handler)
IMPLEMENT_MSG_HANDLER(MSG_ID_INIT, init_callback)
IMPLEMENT_MSG_HANDLER(MSG_ID_DESTROY, destroy_callback)

END_MENU_HANDLER()

