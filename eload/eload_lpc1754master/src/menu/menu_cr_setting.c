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
	CR_SETTING_TIME,
	
	CR_SETTING_AC,
	
	CR_SETTING_CR_VAL,
	
	CR_SETTING_CURRENT_FROM,
	
	CR_SETTING_CURRENT_TO,
	
	CR_SETTING_VOLTAGE_FROM,
	
	CR_SETTING_VOLTAGE_TO,
	
	CR_SETTING_NONE,
	
	CR_SETTING_FOCUS_COUNT = CR_SETTING_NONE
} cr_setting_item;

static cr_setting_item s_focus_item = CR_SETTING_TIME;

static cr_setting_item s_edit_item = CR_SETTING_NONE;

/* cr test setting */
static CR_TEST_SETTING s_cr_test_setting;

/* max test duration */
static const uint32_t MAX_TEST_DURATION = 10000ul;

static const uint32_t BIG_TEST_DURATION_STEP = 1000ul;

static const uint32_t SMALL_TEST_DURATION_STEP = 100ul;

/* max ac */
static const uint32_t MAX_AC = 999000ul;

static const uint32_t BIG_AC_STEP = 10000ul;

static const uint32_t SMALL_AC_STEP = 1000ul;

/* max resist */
static const uint32_t MAX_RESIST = 999900ul;

static const uint32_t BIG_RESIST_STEP = 1000ul;

static const uint32_t SMALL_RESIST_STEP = 100ul;


/* max voltage */
static const uint32_t MAX_VOLTAGE = 30000ul;

static const uint32_t BIG_VOLTAGE_STEP = 1000ul;

static const uint32_t SMALL_VOLTAGE_STEP = 10ul;

/* max current */
static const uint32_t MAX_CURRENT = 6000ul;

static const uint32_t BIG_CURRENT_STEP = 1000ul;

static const uint32_t SMALL_CURRENT_STEP = 10ul;

static uint32_t s_cur_duration;
static uint32_t s_cur_ac;
static uint32_t s_cur_resist;
static uint32_t s_cur_current_from;
static uint32_t s_cur_current_to;
static uint32_t s_cur_voltage_from;
static uint32_t s_cur_voltage_to;

extern int get_cur_test_setting_step(void);

extern TEST_CATEGORY get_cur_test_category(void);

extern QC_20_TEST_TYPE get_cur_qc_20_test_type(int step);

extern bool get_test_cr_setting(int step, CR_TEST_SETTING *cc_test_setting);

extern bool set_test_cr_setting(int step, const CR_TEST_SETTING *cc_test_setting);

/* unfocus function */
static void unfocus_time(void)
{
	draw_normal_cr_setting_time(s_cr_test_setting.duration);
}

static void unfocus_ac(void)
{
	draw_normal_cr_setting_ac(s_cr_test_setting.ac_limit);
}

static void unfocus_cr_val(void)
{
	draw_normal_cr_setting_cr(s_cr_test_setting.cr_val);
}

static void unfocus_current_from(void)
{
	draw_normal_cr_setting_current_from(s_cr_test_setting.current_from);
}

static void unfocus_current_to(void)
{
	draw_normal_cr_setting_current_to(s_cr_test_setting.current_to);
}

static void unfocus_voltage_from(void)
{
	draw_normal_cr_setting_voltage_from(s_cr_test_setting.voltage_from);
}

static void unfocus_voltage_to(void)
{
	draw_normal_cr_setting_voltage_to(s_cr_test_setting.voltage_to);
}

static void (*const s_unfocus_fun_arr[])(void) = 
{
	[CR_SETTING_TIME]         = unfocus_time,
	
	[CR_SETTING_AC]           = unfocus_ac,
	
	[CR_SETTING_CR_VAL]       = unfocus_cr_val,
	
	[CR_SETTING_CURRENT_FROM] = unfocus_current_from,
	
	[CR_SETTING_CURRENT_TO]   = unfocus_current_to,
	
	[CR_SETTING_VOLTAGE_FROM] = unfocus_voltage_from,
	
	[CR_SETTING_VOLTAGE_TO]   = unfocus_voltage_to
};


/* focus function */
static void focus_time(void)
{
	draw_focus_cr_setting_time(s_cr_test_setting.duration);
}

static void focus_ac(void)
{
	draw_focus_cr_setting_ac(s_cr_test_setting.ac_limit);
}

static void focus_cr_val(void)
{
	draw_focus_cr_setting_cr(s_cr_test_setting.cr_val);
}

static void focus_current_from(void)
{
	draw_focus_cr_setting_current_from(s_cr_test_setting.current_from);
}

static void focus_current_to(void)
{
	draw_focus_cr_setting_current_to(s_cr_test_setting.current_to);
}

static void focus_voltage_from(void)
{
	draw_focus_cr_setting_voltage_from(s_cr_test_setting.voltage_from);
}

static void focus_voltage_to(void)
{
	draw_focus_cr_setting_voltage_to(s_cr_test_setting.voltage_to);
}

static void (*const s_focus_fun_arr[])(void) = 
{
	[CR_SETTING_TIME]         = focus_time,
	
	[CR_SETTING_AC]           = focus_ac,
	
	[CR_SETTING_CR_VAL]       = focus_cr_val,
	
	[CR_SETTING_CURRENT_FROM] = focus_current_from,
	
	[CR_SETTING_CURRENT_TO]   = focus_current_to,
	
	[CR_SETTING_VOLTAGE_FROM] = focus_voltage_from,
	
	[CR_SETTING_VOLTAGE_TO]   = focus_voltage_to
};


/* enter edit function */
static void enter_edit_time(void)
{
	s_cur_duration = s_cr_test_setting.duration;
	draw_edit_cr_setting_time(s_cur_duration);
	
	s_edit_item = CR_SETTING_TIME;
}

static void enter_edit_ac(void)
{
	s_cur_ac = s_cr_test_setting.ac_limit;
	draw_edit_cr_setting_ac(s_cur_ac);
	
	s_edit_item = CR_SETTING_AC;
}

static void enter_edit_cr_val(void)
{
	s_cur_resist = s_cr_test_setting.cr_val;
	draw_edit_cr_setting_cr(s_cur_resist);
	
	s_edit_item = CR_SETTING_CR_VAL;
}

static void enter_edit_current_from(void)
{
	s_cur_current_from = s_cr_test_setting.current_from;
	draw_edit_cr_setting_current_from(s_cur_current_from);
	
	s_edit_item = CR_SETTING_CURRENT_FROM;
}

static void enter_edit_current_to(void)
{
	s_cur_current_to = s_cr_test_setting.current_to;
	draw_edit_cr_setting_current_to(s_cur_current_to);
	
	s_edit_item = CR_SETTING_CURRENT_TO;
}

static void enter_edit_voltage_from(void)
{
	s_cur_voltage_from = s_cr_test_setting.voltage_from;
	draw_edit_cr_setting_voltage_from(s_cur_voltage_from);
	
	s_edit_item = CR_SETTING_VOLTAGE_FROM;
}

static void enter_edit_voltage_to(void)
{
	s_cur_voltage_to = s_cr_test_setting.voltage_to;
	draw_edit_cr_setting_voltage_to(s_cur_voltage_to);
	
	s_edit_item = CR_SETTING_VOLTAGE_TO;	
}

static void (*const s_enter_edit_fun_arr[])(void) = 
{
	[CR_SETTING_TIME]         = enter_edit_time,
	
	[CR_SETTING_AC]           = enter_edit_ac,
	
	[CR_SETTING_CR_VAL]       = enter_edit_cr_val,
	
	[CR_SETTING_CURRENT_FROM] = enter_edit_current_from,
	
	[CR_SETTING_CURRENT_TO]   = enter_edit_current_to,
	
	[CR_SETTING_VOLTAGE_FROM] = enter_edit_voltage_from,
	
	[CR_SETTING_VOLTAGE_TO]   = enter_edit_voltage_to
};


/* confirm edit function */
static void confirm_edit_time(void)
{
	s_cr_test_setting.duration = s_cur_duration;
	draw_focus_cr_setting_time(s_cr_test_setting.duration);
}

static void confirm_edit_ac(void)
{
	s_cr_test_setting.ac_limit = s_cur_ac;
	draw_focus_cr_setting_ac(s_cr_test_setting.ac_limit);
}

static void confirm_edit_cr_val(void)
{
	s_cr_test_setting.cr_val = s_cur_resist;
	draw_focus_cr_setting_cr(s_cr_test_setting.cr_val);
}

static void confirm_edit_current_from(void)
{
	s_cr_test_setting.current_from = s_cur_current_from;
	draw_focus_cr_setting_current_from(s_cr_test_setting.current_from);
}

static void confirm_edit_current_to(void)
{
	s_cr_test_setting.current_to = s_cur_current_to;
	draw_focus_cr_setting_current_to(s_cr_test_setting.current_to);
}

static void confirm_edit_voltage_from(void)
{
	s_cr_test_setting.voltage_from = s_cur_voltage_from;
	draw_focus_cr_setting_voltage_from(s_cr_test_setting.voltage_from);
}

static void confirm_edit_voltage_to(void)
{
	s_cr_test_setting.voltage_to = s_cur_voltage_to;
	draw_focus_cr_setting_voltage_to(s_cr_test_setting.voltage_to);
}

static void (*const s_confirm_edit_fun_arr[])(void) = 
{
	[CR_SETTING_TIME]         = confirm_edit_time,
	
	[CR_SETTING_AC]           = confirm_edit_ac,
	
	[CR_SETTING_CR_VAL]       = confirm_edit_cr_val,
	
	[CR_SETTING_CURRENT_FROM] = confirm_edit_current_from,
	
	[CR_SETTING_CURRENT_TO]   = confirm_edit_current_to,
	
	[CR_SETTING_VOLTAGE_FROM] = confirm_edit_voltage_from,
	
	[CR_SETTING_VOLTAGE_TO]   = confirm_edit_voltage_to
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
		draw_edit_cr_setting_time(s_cur_duration);
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
		draw_edit_cr_setting_time(s_cur_duration);
	}
	else if (key == KEY_RIGHT)
	{
		s_cur_duration += SMALL_TEST_DURATION_STEP;
		if (s_cur_duration > MAX_TEST_DURATION)
		{
			s_cur_duration = MAX_TEST_DURATION;
		}
		draw_edit_cr_setting_time(s_cur_duration);
	}
	else if (key == KEY_LEFT)
	{
		if (s_cur_duration > SMALL_TEST_DURATION_STEP)
		{
			s_cur_duration -= SMALL_TEST_DURATION_STEP;
		}
		draw_edit_cr_setting_time(s_cur_duration);
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
		draw_edit_cr_setting_ac(s_cur_ac);
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
		draw_edit_cr_setting_ac(s_cur_ac);
	}
	else if (key == KEY_RIGHT)
	{
		s_cur_ac += SMALL_AC_STEP;
		if (s_cur_ac > MAX_AC)
		{
			s_cur_ac = MAX_AC;
		}
		draw_edit_cr_setting_ac(s_cur_ac);
	}
	else if (key == KEY_LEFT)
	{
		if (s_cur_ac > SMALL_AC_STEP)
		{
			s_cur_ac -= SMALL_AC_STEP;
		}
		draw_edit_cr_setting_ac(s_cur_ac);
	}
}

static void edit_cr_val(uint8_t key)
{
	if (key == KEY_UP)
	{
		s_cur_resist += BIG_RESIST_STEP;
		if (s_cur_resist > MAX_RESIST)
		{
			s_cur_resist = MAX_RESIST;
		}
		draw_edit_cr_setting_cr(s_cur_resist);
	}
	else if (key == KEY_DOWN)
	{
		if (s_cur_resist > BIG_RESIST_STEP)
		{
			s_cur_resist -= BIG_RESIST_STEP;
		}
		else
		{
			s_cur_resist = SMALL_RESIST_STEP;
		}
		draw_edit_cr_setting_cr(s_cur_resist);
	}
	else if (key == KEY_RIGHT)
	{
		s_cur_resist += SMALL_RESIST_STEP;
		if (s_cur_resist > MAX_RESIST)
		{
			s_cur_resist = MAX_RESIST;
		}
		draw_edit_cr_setting_cr(s_cur_resist);
	}
	else if (key == KEY_LEFT)
	{
		if (s_cur_resist > SMALL_RESIST_STEP)
		{
			s_cur_resist -= SMALL_RESIST_STEP;
		}
		draw_edit_cr_setting_cr(s_cur_resist);
	}
}

static void edit_current_from(uint8_t key)
{
	if (key == KEY_UP)
	{
		s_cur_current_from += BIG_CURRENT_STEP;
		if (s_cur_current_from > MAX_CURRENT)
		{
			s_cur_current_from = MAX_CURRENT;
		}
		draw_edit_cr_setting_current_from(s_cur_current_from);
	}
	else if (key == KEY_DOWN)
	{
		if (s_cur_current_from > BIG_CURRENT_STEP)
		{
			s_cur_current_from -= BIG_CURRENT_STEP;
		}
		else
		{
			s_cur_current_from = SMALL_CURRENT_STEP;
		}
		draw_edit_cr_setting_current_from(s_cur_current_from);
	}
	else if (key == KEY_RIGHT)
	{
		s_cur_current_from += SMALL_CURRENT_STEP;
		if (s_cur_current_from > MAX_CURRENT)
		{
			s_cur_current_from = MAX_CURRENT;
		}
		draw_edit_cr_setting_current_from(s_cur_current_from);
	}
	else if (key == KEY_LEFT)
	{
		if (s_cur_current_from > SMALL_CURRENT_STEP)
		{
			s_cur_current_from -= SMALL_CURRENT_STEP;
		}
		draw_edit_cr_setting_current_from(s_cur_current_from);
	}
}

static void edit_current_to(uint8_t key)
{
	if (key == KEY_UP)
	{
		s_cur_current_to += BIG_CURRENT_STEP;
		if (s_cur_current_to > MAX_CURRENT)
		{
			s_cur_current_to = MAX_CURRENT;
		}
		draw_edit_cr_setting_current_to(s_cur_current_to);
	}
	else if (key == KEY_DOWN)
	{
		if (s_cur_current_to > BIG_CURRENT_STEP)
		{
			s_cur_current_to -= BIG_CURRENT_STEP;
		}
		else
		{
			s_cur_current_to = SMALL_CURRENT_STEP;
		}
		draw_edit_cr_setting_current_to(s_cur_current_to);
	}
	else if (key == KEY_RIGHT)
	{
		s_cur_current_to += SMALL_CURRENT_STEP;
		if (s_cur_current_to > MAX_CURRENT)
		{
			s_cur_current_to = MAX_CURRENT;
		}
		draw_edit_cr_setting_current_to(s_cur_current_to);
	}
	else if (key == KEY_LEFT)
	{
		if (s_cur_current_to > SMALL_CURRENT_STEP)
		{
			s_cur_current_to -= SMALL_CURRENT_STEP;
		}
		draw_edit_cr_setting_current_to(s_cur_current_to);
	}
}

static void edit_voltage_from(uint8_t key)
{
	if (key == KEY_UP)
	{
		s_cur_voltage_from += BIG_VOLTAGE_STEP;
		if (s_cur_voltage_from > MAX_VOLTAGE)
		{
			s_cur_voltage_from = MAX_VOLTAGE;
		}
		draw_edit_cr_setting_voltage_from(s_cur_voltage_from);
	}
	else if (key == KEY_DOWN)
	{
		if (s_cur_voltage_from > BIG_VOLTAGE_STEP)
		{
			s_cur_voltage_from -= BIG_VOLTAGE_STEP;
		}
		else
		{
			s_cur_voltage_from = SMALL_VOLTAGE_STEP;
		}
		draw_edit_cr_setting_voltage_from(s_cur_voltage_from);
	}
	else if (key == KEY_RIGHT)
	{
		s_cur_voltage_from += SMALL_VOLTAGE_STEP;
		if (s_cur_voltage_from > MAX_VOLTAGE)
		{
			s_cur_voltage_from = MAX_VOLTAGE;
		}
		draw_edit_cr_setting_voltage_from(s_cur_voltage_from);
	}
	else if (key == KEY_LEFT)
	{
		if (s_cur_voltage_from > SMALL_VOLTAGE_STEP)
		{
			s_cur_voltage_from -= SMALL_VOLTAGE_STEP;
		}
		draw_edit_cr_setting_voltage_from(s_cur_voltage_from);
	}
}

static void edit_voltage_to(uint8_t key)
{
	if (key == KEY_UP)
	{
		s_cur_voltage_to += BIG_VOLTAGE_STEP;
		if (s_cur_voltage_to > MAX_VOLTAGE)
		{
			s_cur_voltage_to = MAX_VOLTAGE;
		}
		draw_edit_cr_setting_voltage_to(s_cur_voltage_to);
	}
	else if (key == KEY_DOWN)
	{
		if (s_cur_voltage_to > BIG_VOLTAGE_STEP)
		{
			s_cur_voltage_to -= BIG_VOLTAGE_STEP;
		}
		else
		{
			s_cur_voltage_to = SMALL_VOLTAGE_STEP;
		}
		draw_edit_cr_setting_voltage_to(s_cur_voltage_to);
	}
	else if (key == KEY_RIGHT)
	{
		s_cur_voltage_to += SMALL_VOLTAGE_STEP;
		if (s_cur_voltage_to > MAX_VOLTAGE)
		{
			s_cur_voltage_to = MAX_VOLTAGE;
		}
		draw_edit_cr_setting_voltage_to(s_cur_voltage_to);
	}
	else if (key == KEY_LEFT)
	{
		if (s_cur_voltage_to > SMALL_VOLTAGE_STEP)
		{
			s_cur_voltage_to -= SMALL_VOLTAGE_STEP;
		}
		draw_edit_cr_setting_voltage_to(s_cur_voltage_to);
	}
}

static void (*const s_edit_fun_arr[])(uint8_t key) = 
{
	[CR_SETTING_TIME]         = edit_time,
	
	[CR_SETTING_AC]           = edit_ac,
	
	[CR_SETTING_CR_VAL]       = edit_cr_val,
	
	[CR_SETTING_CURRENT_FROM] = edit_current_from,
	
	[CR_SETTING_CURRENT_TO]   = edit_current_to,
	
	[CR_SETTING_VOLTAGE_FROM] = edit_voltage_from,
	
	[CR_SETTING_VOLTAGE_TO]   = edit_voltage_to
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
		if (s_edit_item == CR_SETTING_NONE)
		{
			s_unfocus_fun_arr[s_focus_item]();
			
			s_focus_item += CR_SETTING_FOCUS_COUNT - 1;
			s_focus_item %= CR_SETTING_FOCUS_COUNT;
			
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
		if (s_edit_item == CR_SETTING_NONE)
		{
			s_unfocus_fun_arr[s_focus_item]();
			
			s_focus_item++;
			s_focus_item %= CR_SETTING_FOCUS_COUNT;
			
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
		if (s_edit_item == CR_SETTING_NONE)
		{
			s_enter_edit_fun_arr[s_focus_item]();
		}
		else
		{
			s_confirm_edit_fun_arr[s_focus_item]();
			
			s_edit_item = CR_SETTING_NONE;
		}
		
		lcd_validate_cmd();
	}
	else if (key == KEY_CANCEL)
	{
		if (s_edit_item == CR_SETTING_NONE)
		{
			/* save */
			int step = get_cur_test_setting_step();
			set_test_cr_setting(step, &s_cr_test_setting);
			
			switch_to_menu(MENU_ID_SYNTH_TEST_SETTING);
		}
		else
		{
			s_focus_fun_arr[s_focus_item]();
			
			lcd_validate_cmd();
			
			s_edit_item = CR_SETTING_NONE;
		}
	}
}

static void init_callback(void *msg)
{
	int step = get_cur_test_setting_step();

	TEST_CATEGORY test_category = get_cur_test_category();
	if (test_category == TEST_CATEGORY_SYNTH_TEST)
	{
		draw_synth_cr_setting_caption();
	}
	else if (test_category == TEST_CATEGORY_QC_20_TEST)
	{
		QC_20_TEST_TYPE qc_20_test_type = get_cur_qc_20_test_type(step);
		if (qc_20_test_type == QC_20_5V_TEST_CR)
		{
			draw_qc_20_5v_cr_setting_caption();
		}
		else if (qc_20_test_type == QC_20_9V_TEST_CR)
		{
			draw_qc_20_9v_cr_setting_caption();
		}
		else if (qc_20_test_type == QC_20_12V_TEST_CR)
		{
			draw_qc_20_12v_cr_setting_caption();
		}
		else if (qc_20_test_type == QC_20_20V_TEST_CR)
		{
			draw_qc_20_20v_cr_setting_caption();
		}
	}
	
	get_test_cr_setting(step, &s_cr_test_setting);
	
	draw_cr_setting_menu();

	s_focus_item = CR_SETTING_TIME;

	s_edit_item = CR_SETTING_NONE;
	
	s_focus_fun_arr[s_focus_item]();
	
	draw_normal_cr_setting_ac(s_cr_test_setting.ac_limit);
	
	draw_normal_cr_setting_cr(s_cr_test_setting.cr_val);
	
	draw_normal_cr_setting_current_from(s_cr_test_setting.current_from);
	
	draw_normal_cr_setting_current_to(s_cr_test_setting.current_to);
	
	draw_normal_cr_setting_voltage_from(s_cr_test_setting.voltage_from);
	
	draw_normal_cr_setting_voltage_to(s_cr_test_setting.voltage_to);
	
	lcd_validate_cmd();
}

static void destroy_callback(void *msg)
{
	lcd_clear(SCREEN_BACK_COLOR);
}

BEGIN_MENU_HANDLER(MENU_ID_CR_SETTING)

IMPLEMENT_MSG_HANDLER(MSG_ID_KEY, key_handler)
IMPLEMENT_MSG_HANDLER(MSG_ID_INIT, init_callback)
IMPLEMENT_MSG_HANDLER(MSG_ID_DESTROY, destroy_callback)

END_MENU_HANDLER()

