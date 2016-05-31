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
	DISCHARGE_SETTING_DISCHARGE_CURRENT,
	
	DISCHARGE_SETTING_DISCHARGE_TIME,
	
	DISCHARGE_SETTING_INDICATE_DELAY_TIME,
	
	DISCHARGE_SETTING_NONE,
	
	DISCHARGE_SETTING_COUNT = DISCHARGE_SETTING_NONE
} discharge_setting_item;

static discharge_setting_item s_focus_item = DISCHARGE_SETTING_DISCHARGE_CURRENT;

static discharge_setting_item s_edit_item = DISCHARGE_SETTING_NONE;

/* discharge test setting */
static DISCHARGE_TEST_SETTING s_discharge_test_setting;

/* max current */
static const uint32_t MAX_CURRENT = 6000ul;

static const uint32_t BIG_CURRENT_STEP = 1000ul;

static const uint32_t SMALL_CURRENT_STEP = 10ul;

/* max duration */
static const uint32_t MAX_TEST_DURATION = 10000ul;

static const uint32_t BIG_TEST_DURATION_STEP = 1000ul;

static const uint32_t SMALL_TEST_DURATION_STEP = 100ul;

static uint32_t s_cur_current;
static uint32_t s_cur_discharge_duration;
static uint32_t s_cur_indicate_delay;

extern void get_test_discharge_setting(DISCHARGE_TEST_SETTING *discharge_test_setting);
extern void set_test_discharge_setting(const DISCHARGE_TEST_SETTING *discharge_test_setting);

/* unfocus function */
static void unfocus_discharge_current(void)
{
	draw_normal_discharge_setting_discharge_current(s_discharge_test_setting.discharge_current);
}


static void unfocus_discharge_time(void)
{
	draw_normal_discharge_setting_discharge_time(s_discharge_test_setting.discharge_duration);
}

static void unfocus_indicate_delay_time(void)
{
	draw_normal_discharge_setting_indicate_delay_time(s_discharge_test_setting.indicate_delay);
}

static void (*const s_unfocus_fun_arr[])(void) = 
{
	[DISCHARGE_SETTING_DISCHARGE_CURRENT]   = unfocus_discharge_current,
	
	[DISCHARGE_SETTING_DISCHARGE_TIME]      = unfocus_discharge_time,
	
	[DISCHARGE_SETTING_INDICATE_DELAY_TIME] = unfocus_indicate_delay_time
};

/* focus function */
static void focus_discharge_current(void)
{
	draw_focus_discharge_setting_discharge_current(s_discharge_test_setting.discharge_current);
}

static void focus_discharge_time(void)
{
	draw_focus_discharge_setting_discharge_time(s_discharge_test_setting.discharge_duration);
}

static void focus_indicate_delay_time(void)
{
	draw_focus_discharge_setting_indicate_delay_time(s_discharge_test_setting.indicate_delay);
}

static void (*const s_focus_fun_arr[])(void) = 
{
	[DISCHARGE_SETTING_DISCHARGE_CURRENT]   = focus_discharge_current,
	
	[DISCHARGE_SETTING_DISCHARGE_TIME]      = focus_discharge_time,
	
	[DISCHARGE_SETTING_INDICATE_DELAY_TIME] = focus_indicate_delay_time
};

/* enter edit function */
static void enter_edit_discharge_current(void)
{
	s_cur_current = s_discharge_test_setting.discharge_current;
	draw_edit_discharge_setting_discharge_current(s_cur_current);
	
	s_edit_item = DISCHARGE_SETTING_DISCHARGE_CURRENT;
}

static void enter_edit_discharge_time(void)
{
	s_cur_discharge_duration = s_discharge_test_setting.discharge_duration;
	draw_edit_discharge_setting_discharge_time(s_cur_discharge_duration);
	
	s_edit_item = DISCHARGE_SETTING_DISCHARGE_TIME;
}

static void enter_edit_indicate_delay_time(void)
{
	s_cur_indicate_delay = s_discharge_test_setting.indicate_delay;
	draw_edit_discharge_setting_indicate_delay_time(s_cur_indicate_delay);
	
	s_edit_item = DISCHARGE_SETTING_INDICATE_DELAY_TIME;
}

static void (*const s_enter_edit_fun_arr[])(void) = 
{
	[DISCHARGE_SETTING_DISCHARGE_CURRENT]   = enter_edit_discharge_current,
	
	[DISCHARGE_SETTING_DISCHARGE_TIME]      = enter_edit_discharge_time,
	
	[DISCHARGE_SETTING_INDICATE_DELAY_TIME] = enter_edit_indicate_delay_time
};


/* confirm edit function */
static void confirm_edit_discharge_current(void)
{
	s_discharge_test_setting.discharge_current = s_cur_current;
	draw_focus_discharge_setting_discharge_current(s_discharge_test_setting.discharge_current);
}

static void confirm_edit_discharge_time(void)
{
	s_discharge_test_setting.discharge_duration = s_cur_discharge_duration;
	draw_focus_discharge_setting_discharge_time(s_discharge_test_setting.discharge_duration);
}

static void confirm_edit_indicate_delay_time(void)
{
	s_discharge_test_setting.indicate_delay = s_cur_indicate_delay;
	draw_focus_discharge_setting_indicate_delay_time(s_discharge_test_setting.indicate_delay);
}

static void (*const s_confirm_edit_fun_arr[])(void) = 
{
	[DISCHARGE_SETTING_DISCHARGE_CURRENT]   = confirm_edit_discharge_current,
	
	[DISCHARGE_SETTING_DISCHARGE_TIME]      = confirm_edit_discharge_time,
	
	[DISCHARGE_SETTING_INDICATE_DELAY_TIME] = confirm_edit_indicate_delay_time
};

/* edit function */
static void edit_discharge_current(uint8_t key)
{
	if (key == KEY_UP)
	{
		s_cur_current += BIG_CURRENT_STEP;
		if (s_cur_current > MAX_CURRENT)
		{
			s_cur_current = MAX_CURRENT;
		}
		draw_edit_discharge_setting_discharge_current(s_cur_current);
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
		draw_edit_discharge_setting_discharge_current(s_cur_current);
	}
	else if (key == KEY_RIGHT)
	{
		s_cur_current += SMALL_CURRENT_STEP;
		if (s_cur_current > MAX_CURRENT)
		{
			s_cur_current = MAX_CURRENT;
		}
		draw_edit_discharge_setting_discharge_current(s_cur_current);
	}
	else if (key == KEY_LEFT)
	{
		if (s_cur_current > SMALL_CURRENT_STEP)
		{
			s_cur_current -= SMALL_CURRENT_STEP;
		}
		draw_edit_discharge_setting_discharge_current(s_cur_current);
	}
}

static void edit_discharge_time(uint8_t key)
{
	if (key == KEY_UP)
	{
		s_cur_discharge_duration += BIG_TEST_DURATION_STEP;
		if (s_cur_discharge_duration > MAX_TEST_DURATION)
		{
			s_cur_discharge_duration = MAX_TEST_DURATION;
		}
		draw_edit_discharge_setting_discharge_time(s_cur_discharge_duration);
	}
	else if (key == KEY_DOWN)
	{
		if (s_cur_discharge_duration > BIG_TEST_DURATION_STEP)
		{
			s_cur_discharge_duration -= BIG_TEST_DURATION_STEP;
		}
		else
		{
			s_cur_discharge_duration = SMALL_TEST_DURATION_STEP;
		}
		draw_edit_discharge_setting_discharge_time(s_cur_discharge_duration);
	}
	else if (key == KEY_RIGHT)
	{
		s_cur_discharge_duration += SMALL_TEST_DURATION_STEP;
		if (s_cur_discharge_duration > MAX_TEST_DURATION)
		{
			s_cur_discharge_duration = MAX_TEST_DURATION;
		}
		draw_edit_discharge_setting_discharge_time(s_cur_discharge_duration);
	}
	else if (key == KEY_LEFT)
	{
		if (s_cur_discharge_duration > SMALL_TEST_DURATION_STEP)
		{
			s_cur_discharge_duration -= SMALL_TEST_DURATION_STEP;
		}
		draw_edit_discharge_setting_discharge_time(s_cur_discharge_duration);
	}
}

static void edit_indicate_delay_time(uint8_t key)
{
	if (key == KEY_UP)
	{
		s_cur_indicate_delay += BIG_TEST_DURATION_STEP;
		if (s_cur_indicate_delay > MAX_TEST_DURATION)
		{
			s_cur_indicate_delay = MAX_TEST_DURATION;
		}
		draw_edit_discharge_setting_indicate_delay_time(s_cur_indicate_delay);
	}
	else if (key == KEY_DOWN)
	{
		if (s_cur_indicate_delay > BIG_TEST_DURATION_STEP)
		{
			s_cur_indicate_delay -= BIG_TEST_DURATION_STEP;
		}
		else
		{
			s_cur_indicate_delay = SMALL_TEST_DURATION_STEP;
		}
		draw_edit_discharge_setting_indicate_delay_time(s_cur_indicate_delay);
	}
	else if (key == KEY_RIGHT)
	{
		s_cur_indicate_delay += SMALL_TEST_DURATION_STEP;
		if (s_cur_indicate_delay > MAX_TEST_DURATION)
		{
			s_cur_indicate_delay = MAX_TEST_DURATION;
		}
		draw_edit_discharge_setting_indicate_delay_time(s_cur_indicate_delay);
	}
	else if (key == KEY_LEFT)
	{
		if (s_cur_indicate_delay > SMALL_TEST_DURATION_STEP)
		{
			s_cur_indicate_delay -= SMALL_TEST_DURATION_STEP;
		}
		draw_edit_discharge_setting_indicate_delay_time(s_cur_indicate_delay);
	}
}

static void (*const s_edit_fun_arr[])(uint8_t key) = 
{
	[DISCHARGE_SETTING_DISCHARGE_CURRENT]   = edit_discharge_current,
	
	[DISCHARGE_SETTING_DISCHARGE_TIME]      = edit_discharge_time,
	
	[DISCHARGE_SETTING_INDICATE_DELAY_TIME] = edit_indicate_delay_time
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
		if (s_edit_item == DISCHARGE_SETTING_NONE)
		{
			s_unfocus_fun_arr[s_focus_item]();
			
			s_focus_item += DISCHARGE_SETTING_COUNT - 1;
			s_focus_item %= DISCHARGE_SETTING_COUNT;
			
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
		if (s_edit_item == DISCHARGE_SETTING_NONE)
		{
			s_unfocus_fun_arr[s_focus_item]();
			
			s_focus_item++;
			s_focus_item %= DISCHARGE_SETTING_COUNT;
			
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
		if (s_edit_item == DISCHARGE_SETTING_NONE)
		{
			s_enter_edit_fun_arr[s_focus_item]();
		}
		else
		{
			s_confirm_edit_fun_arr[s_focus_item]();
			
			s_edit_item = DISCHARGE_SETTING_NONE;
		}
		
		lcd_validate_cmd();
	}
	else if (key == KEY_CANCEL)
	{
		if (s_edit_item == DISCHARGE_SETTING_NONE)
		{
			/* save */
			set_test_discharge_setting(&s_discharge_test_setting);
			
			switch_to_menu(MENU_ID_SYNTH_TEST_SETTING);
		}
		else
		{
			s_focus_fun_arr[s_focus_item]();
			
			lcd_validate_cmd();
			
			s_edit_item = DISCHARGE_SETTING_NONE;
		}
	}	
}

static void init_callback(void *msg)
{
	get_test_discharge_setting(&s_discharge_test_setting);
	
	draw_discharge_setting_menu();
	
	draw_focus_discharge_setting_discharge_current(s_discharge_test_setting.discharge_current);
	
	draw_normal_discharge_setting_discharge_time(s_discharge_test_setting.discharge_duration);
	
	draw_normal_discharge_setting_indicate_delay_time(s_discharge_test_setting.indicate_delay);
	
	lcd_validate_cmd();
	
	s_focus_item = DISCHARGE_SETTING_DISCHARGE_CURRENT;

	s_edit_item = DISCHARGE_SETTING_NONE;	
}

static void destroy_callback(void *msg)
{
	lcd_clear(SCREEN_BACK_COLOR);
}

BEGIN_MENU_HANDLER(MENU_ID_DISCHARGE_SETTING)

IMPLEMENT_MSG_HANDLER(MSG_ID_KEY, key_handler)
IMPLEMENT_MSG_HANDLER(MSG_ID_INIT, init_callback)
IMPLEMENT_MSG_HANDLER(MSG_ID_DESTROY, destroy_callback)

END_MENU_HANDLER()

