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
	EMPTY_LOAD_SETTING_TIME,
	
	EMPTY_LOAD_SETTING_AC,
	
	EMPTY_LOAD_SETTING_VOLTAGE_FROM,
	
	EMPTY_LOAD_SETTING_VOLTAGE_TO,

	EMPTY_LOAD_SETTING_DP_DN_MODE,

	EMPTY_LOAD_SETTING_DP_DN_ON_OFF,

	EMPTY_LOAD_SETTING_DP_DN_SETTING,
	
	EMPTY_LOAD_SETTING_NONE,
	
	EMPTY_LOAD_SETTING_COUNT = EMPTY_LOAD_SETTING_NONE
} empty_load_setting_item;

static empty_load_setting_item s_focus_item = EMPTY_LOAD_SETTING_NONE;

static empty_load_setting_item s_edit_item = EMPTY_LOAD_SETTING_NONE;

static EMPTY_LOAD_TEST_SETTING s_empty_load_test_setting;

/* max test duration */
static const uint32_t MAX_TEST_DURATION = 10000ul;

static const uint32_t BIG_TEST_DURATION_STEP = 1000ul;

static const uint32_t SMALL_TEST_DURATION_STEP = 100ul;

/* max ac */
static const uint32_t MAX_AC = 999000ul;

static const uint32_t BIG_AC_STEP = 10000ul;

static const uint32_t SMALL_AC_STEP = 1000ul;

/* max voltage */
static const uint32_t MAX_VOLTAGE = 30000ul;

static const uint32_t BIG_VOLTAGE_STEP = 1000ul;

static const uint32_t SMALL_VOLTAGE_STEP = 10ul;

static uint32_t s_cur_duration;
static uint32_t s_cur_ac;
static uint32_t s_cur_voltage_from;
static uint32_t s_cur_voltage_to;

static USB_DP_DN_MODE s_cur_dp_dn_mode = VOLTAGE_DIVIDE_MODE;

static OPTION_ON_OFF  s_cur_option_on_off = OPTION_ON;

extern void get_test_empty_load_setting(EMPTY_LOAD_TEST_SETTING *empty_load_test_setting);
extern void set_test_empty_load_setting(const EMPTY_LOAD_TEST_SETTING *empty_load_test_setting);

/* unfocus function */
static void unfocus_time(void)
{
	draw_normal_empty_load_setting_time(s_empty_load_test_setting.duration);
}

static void unfocus_ac(void)
{
	draw_normal_empty_load_setting_ac(s_empty_load_test_setting.ac_limit);
}

static void unfocus_voltage_from(void)
{
	draw_normal_empty_load_setting_voltage_from(s_empty_load_test_setting.voltage_from);
}

static void unfocus_voltage_to(void)
{
	draw_normal_empty_load_setting_voltage_to(s_empty_load_test_setting.voltage_to);
}

static void unfocus_dp_dn_mode(void)
{
	draw_normal_empty_load_dp_dn_mode(s_empty_load_test_setting.dp_dn_setting.mode);
}

static void unfocus_dp_dn_option_on_off(void)
{
	draw_normal_empty_load_dp_dn_on_off(s_empty_load_test_setting.dp_dn_setting.on_off);
}

static void unfocus_dp_dn_setting(void)
{
	draw_normal_empty_load_dp_dn_setting();
}

static void (*const s_unfocus_fun_arr[])(void) = 
{
	[EMPTY_LOAD_SETTING_TIME]         = unfocus_time,
	
	[EMPTY_LOAD_SETTING_AC]           = unfocus_ac,
	
	[EMPTY_LOAD_SETTING_VOLTAGE_FROM] = unfocus_voltage_from,
	
	[EMPTY_LOAD_SETTING_VOLTAGE_TO]   = unfocus_voltage_to,

	[EMPTY_LOAD_SETTING_DP_DN_MODE]   = unfocus_dp_dn_mode,

	[EMPTY_LOAD_SETTING_DP_DN_ON_OFF] = unfocus_dp_dn_option_on_off,

	[EMPTY_LOAD_SETTING_DP_DN_SETTING] = unfocus_dp_dn_setting
};

/* focus function */
static void focus_time(void)
{
	draw_focus_empty_load_setting_time(s_empty_load_test_setting.duration);
}

static void focus_ac(void)
{
	draw_focus_empty_load_setting_ac(s_empty_load_test_setting.ac_limit);
}

static void focus_voltage_from(void)
{
	draw_focus_empty_load_setting_voltage_from(s_empty_load_test_setting.voltage_from);
}

static void focus_voltage_to(void)
{
	draw_focus_empty_load_setting_voltage_to(s_empty_load_test_setting.voltage_to);
}

static void focus_dp_dn_mode(void)
{
	draw_focus_empty_load_dp_dn_mode(s_empty_load_test_setting.dp_dn_setting.mode);
}

static void focus_dp_dn_option_on_off(void)
{
	draw_focus_empty_load_dp_dn_on_off(s_empty_load_test_setting.dp_dn_setting.on_off);
}

static void focus_dp_dn_setting(void)
{
	draw_focus_empty_load_dp_dn_setting();
}


static void (*const s_focus_fun_arr[])(void) = 
{
	[EMPTY_LOAD_SETTING_TIME]         = focus_time,
	
	[EMPTY_LOAD_SETTING_AC]           = focus_ac,
	
	[EMPTY_LOAD_SETTING_VOLTAGE_FROM] = focus_voltage_from,
	
	[EMPTY_LOAD_SETTING_VOLTAGE_TO]   = focus_voltage_to,

	[EMPTY_LOAD_SETTING_DP_DN_MODE]   = focus_dp_dn_mode,

	[EMPTY_LOAD_SETTING_DP_DN_ON_OFF] = focus_dp_dn_option_on_off,

	[EMPTY_LOAD_SETTING_DP_DN_SETTING] = focus_dp_dn_setting
};

/* enter edit function */
static void enter_edit_time(void)
{
	s_cur_duration = s_empty_load_test_setting.duration;
	draw_edit_empty_load_setting_time(s_cur_duration);
	
	s_edit_item = EMPTY_LOAD_SETTING_TIME;
}

static void enter_edit_ac(void)
{
	s_cur_ac = s_empty_load_test_setting.ac_limit;
	draw_edit_empty_load_setting_ac(s_cur_ac);
	
	s_edit_item = EMPTY_LOAD_SETTING_AC;
}

static void enter_edit_voltage_from(void)
{
	s_cur_voltage_from = s_empty_load_test_setting.voltage_from;
	draw_edit_empty_load_setting_voltage_from(s_cur_voltage_from);
	
	s_edit_item = EMPTY_LOAD_SETTING_VOLTAGE_FROM;
}

static void enter_edit_voltage_to(void)
{
	s_cur_voltage_to = s_empty_load_test_setting.voltage_to;
	draw_edit_empty_load_setting_voltage_to(s_cur_voltage_to);
	
	s_edit_item = EMPTY_LOAD_SETTING_VOLTAGE_TO;
}

static void enter_edit_dp_dn_mode(void)
{
	s_cur_dp_dn_mode = s_empty_load_test_setting.dp_dn_setting.mode;
	draw_edit_empty_load_dp_dn_mode(s_cur_dp_dn_mode);

	s_edit_item = EMPTY_LOAD_SETTING_DP_DN_MODE;
}

static void enter_edit_dp_dn_option_on_off(void)
{
	s_cur_option_on_off = s_empty_load_test_setting.dp_dn_setting.on_off;
	draw_edit_empty_load_dp_dn_on_off(s_cur_option_on_off);

	s_edit_item = EMPTY_LOAD_SETTING_DP_DN_ON_OFF;
}

static const MENU_ID s_MENU_ID[] = 
{
	[VOLTAGE_DIVIDE_MODE] = MENU_ID_USB_DP_DN_DIVIDE_MODE_SETTING,

	[SHORT_MODE] = MENU_ID_USB_DP_DN_SHORT_MODE_SETTING,

	[SHORT_RESIST_MODE] = MENU_ID_USB_DP_DN_RESIST_MODE_SETTING
};

static void enter_edit_dp_dn_setting(void)
{
	switch_to_menu(s_MENU_ID[s_cur_dp_dn_mode]);
}

static void (*const s_enter_edit_fun_arr[])(void) = 
{
	[EMPTY_LOAD_SETTING_TIME]         = enter_edit_time,
	
	[EMPTY_LOAD_SETTING_AC]           = enter_edit_ac,
	
	[EMPTY_LOAD_SETTING_VOLTAGE_FROM] = enter_edit_voltage_from,
	
	[EMPTY_LOAD_SETTING_VOLTAGE_TO]   = enter_edit_voltage_to,

	[EMPTY_LOAD_SETTING_DP_DN_MODE]   = enter_edit_dp_dn_mode,

	[EMPTY_LOAD_SETTING_DP_DN_ON_OFF] = enter_edit_dp_dn_option_on_off,

	[EMPTY_LOAD_SETTING_DP_DN_SETTING] = enter_edit_dp_dn_setting
};

/* confirm edit function */
static void confirm_edit_time(void)
{
	s_empty_load_test_setting.duration = s_cur_duration;
	draw_focus_empty_load_setting_time(s_empty_load_test_setting.duration);
}

static void confirm_edit_ac(void)
{
	s_empty_load_test_setting.ac_limit = s_cur_ac;
	draw_focus_empty_load_setting_ac(s_empty_load_test_setting.ac_limit);
}

static void confirm_edit_voltage_from(void)
{
	s_empty_load_test_setting.voltage_from = s_cur_voltage_from;
	draw_focus_empty_load_setting_voltage_from(s_empty_load_test_setting.voltage_from);
}

static void confirm_edit_voltage_to(void)
{
	s_empty_load_test_setting.voltage_to = s_cur_voltage_to;
	draw_focus_empty_load_setting_voltage_to(s_empty_load_test_setting.voltage_to);
}

static void confirm_edit_dp_dn_mode(void)
{
	s_empty_load_test_setting.dp_dn_setting.mode = s_cur_dp_dn_mode;
	draw_focus_empty_load_dp_dn_mode(s_empty_load_test_setting.dp_dn_setting.mode);
}

static void confirm_edit_dp_dn_option_on_off(void)
{
	s_empty_load_test_setting.dp_dn_setting.on_off = s_cur_option_on_off;
	draw_focus_empty_load_dp_dn_on_off(s_empty_load_test_setting.dp_dn_setting.on_off);
}

static void confirm_edit_dp_dn_setting(void)
{

}

static void (*const s_confirm_edit_fun_arr[])(void) = 
{
	[EMPTY_LOAD_SETTING_TIME]         = confirm_edit_time,
	
	[EMPTY_LOAD_SETTING_AC]           = confirm_edit_ac,
	
	[EMPTY_LOAD_SETTING_VOLTAGE_FROM] = confirm_edit_voltage_from,
	
	[EMPTY_LOAD_SETTING_VOLTAGE_TO]   = confirm_edit_voltage_to,

	[EMPTY_LOAD_SETTING_DP_DN_MODE]   = confirm_edit_dp_dn_mode,

	[EMPTY_LOAD_SETTING_DP_DN_ON_OFF] = confirm_edit_dp_dn_option_on_off,

	[EMPTY_LOAD_SETTING_DP_DN_SETTING] = confirm_edit_dp_dn_setting
};

/* edit function */
static void edit_time(uint8_t key)
{
	if (key == KEY_UP)
	{
		if (s_cur_duration == AUTOMATIC_TIME)
		{
			s_cur_duration = BIG_TEST_DURATION_STEP;
		}
		else
		{
			s_cur_duration += BIG_TEST_DURATION_STEP;
			if (s_cur_duration > MAX_TEST_DURATION)
			{
				s_cur_duration = AUTOMATIC_TIME;
			}
		}
		
		draw_edit_empty_load_setting_time(s_cur_duration);
	}
	else if (key == KEY_DOWN)
	{
		if (s_cur_duration == AUTOMATIC_TIME)
		{
			s_cur_duration = MAX_TEST_DURATION;
		}
		else
		{
			if (s_cur_duration > BIG_TEST_DURATION_STEP)
			{
				s_cur_duration -= BIG_TEST_DURATION_STEP;
			}
			else
			{
				s_cur_duration = AUTOMATIC_TIME;
			}
		}
		
		draw_edit_empty_load_setting_time(s_cur_duration);
	}
	else if (key == KEY_RIGHT)
	{
		if (s_cur_duration == AUTOMATIC_TIME)
		{
			s_cur_duration = SMALL_TEST_DURATION_STEP;
		}
		else
		{
			s_cur_duration += SMALL_TEST_DURATION_STEP;
			if (s_cur_duration > MAX_TEST_DURATION)
			{
				s_cur_duration = AUTOMATIC_TIME;
			}
		}
		
		draw_edit_empty_load_setting_time(s_cur_duration);
	}
	else if (key == KEY_LEFT)
	{
		if (s_cur_duration == AUTOMATIC_TIME)
		{
			s_cur_duration = MAX_TEST_DURATION;
		}
		else
		{
			if (s_cur_duration > SMALL_TEST_DURATION_STEP)
			{
				s_cur_duration -= SMALL_TEST_DURATION_STEP;
			}
			else
			{
				s_cur_duration = AUTOMATIC_TIME;
			}
		}	
		
		draw_edit_empty_load_setting_time(s_cur_duration);
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
		draw_edit_empty_load_setting_ac(s_cur_ac);
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
		draw_edit_empty_load_setting_ac(s_cur_ac);
	}
	else if (key == KEY_RIGHT)
	{
		s_cur_ac += SMALL_AC_STEP;
		if (s_cur_ac > MAX_AC)
		{
			s_cur_ac = MAX_AC;
		}
		draw_edit_empty_load_setting_ac(s_cur_ac);
	}
	else if (key == KEY_LEFT)
	{
		if (s_cur_ac > SMALL_AC_STEP)
		{
			s_cur_ac -= SMALL_AC_STEP;
		}
		draw_edit_empty_load_setting_ac(s_cur_ac);
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
		draw_edit_empty_load_setting_voltage_from(s_cur_voltage_from);
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
		draw_edit_empty_load_setting_voltage_from(s_cur_voltage_from);
	}
	else if (key == KEY_RIGHT)
	{
		s_cur_voltage_from += SMALL_VOLTAGE_STEP;
		if (s_cur_voltage_from > MAX_VOLTAGE)
		{
			s_cur_voltage_from = MAX_VOLTAGE;
		}
		draw_edit_empty_load_setting_voltage_from(s_cur_voltage_from);
	}
	else if (key == KEY_LEFT)
	{
		if (s_cur_voltage_from > SMALL_VOLTAGE_STEP)
		{
			s_cur_voltage_from -= SMALL_VOLTAGE_STEP;
		}
		draw_edit_empty_load_setting_voltage_from(s_cur_voltage_from);
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
		draw_edit_empty_load_setting_voltage_to(s_cur_voltage_to);
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
		draw_edit_empty_load_setting_voltage_to(s_cur_voltage_to);
	}
	else if (key == KEY_RIGHT)
	{
		s_cur_voltage_to += SMALL_VOLTAGE_STEP;
		if (s_cur_voltage_to > MAX_VOLTAGE)
		{
			s_cur_voltage_to = MAX_VOLTAGE;
		}
		draw_edit_empty_load_setting_voltage_to(s_cur_voltage_to);
	}
	else if (key == KEY_LEFT)
	{
		if (s_cur_voltage_to > SMALL_VOLTAGE_STEP)
		{
			s_cur_voltage_to -= SMALL_VOLTAGE_STEP;
		}
		draw_edit_empty_load_setting_voltage_to(s_cur_voltage_to);
	}
}

static void edit_dp_dn_mode(uint8_t key)
{
	if (key == KEY_UP || key == KEY_RIGHT)
	{
		s_cur_dp_dn_mode++;
		s_cur_dp_dn_mode %= DP_DN_MODE_COUNT;
		draw_edit_empty_load_dp_dn_mode(s_cur_dp_dn_mode);
	}
	else if (key == KEY_DOWN || key == KEY_LEFT)
	{
		s_cur_dp_dn_mode += DP_DN_MODE_COUNT - 1;
		s_cur_dp_dn_mode %= DP_DN_MODE_COUNT;
		draw_edit_empty_load_dp_dn_mode(s_cur_dp_dn_mode);
	}
}

static void edit_dp_dn_option_on_off(uint8_t key)
{
	if (key == KEY_UP || key == KEY_RIGHT)
	{
		s_cur_option_on_off++;
		s_cur_option_on_off %= OPTION_ON_OFF_COUNT;
		draw_edit_empty_load_dp_dn_on_off(s_cur_option_on_off);
	}
	else if (key == KEY_DOWN || key == KEY_LEFT)
	{
		s_cur_option_on_off += OPTION_ON_OFF_COUNT - 1;
		s_cur_option_on_off %= OPTION_ON_OFF_COUNT;
		draw_edit_empty_load_dp_dn_on_off(s_cur_option_on_off);
	}
}

static void (*const s_edit_fun_arr[])(uint8_t key) = 
{
	[EMPTY_LOAD_SETTING_TIME]         = edit_time,
	
	[EMPTY_LOAD_SETTING_AC]           = edit_ac,
	
	[EMPTY_LOAD_SETTING_VOLTAGE_FROM] = edit_voltage_from,
	
	[EMPTY_LOAD_SETTING_VOLTAGE_TO]   = edit_voltage_to,

	[EMPTY_LOAD_SETTING_DP_DN_MODE]   = edit_dp_dn_mode,

	[EMPTY_LOAD_SETTING_DP_DN_ON_OFF] = edit_dp_dn_option_on_off
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
		if (s_edit_item == EMPTY_LOAD_SETTING_NONE)
		{
			s_unfocus_fun_arr[s_focus_item]();
			
			s_focus_item += EMPTY_LOAD_SETTING_COUNT - 1;
			s_focus_item %= EMPTY_LOAD_SETTING_COUNT;
			
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
		if (s_edit_item == EMPTY_LOAD_SETTING_NONE)
		{
			s_unfocus_fun_arr[s_focus_item]();
			
			s_focus_item++;
			s_focus_item %= EMPTY_LOAD_SETTING_COUNT;
			
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
		if (s_edit_item == EMPTY_LOAD_SETTING_NONE)
		{
			s_enter_edit_fun_arr[s_focus_item]();
		}
		else
		{
			s_confirm_edit_fun_arr[s_focus_item]();
			
			s_edit_item = EMPTY_LOAD_SETTING_NONE;
		}
		
		lcd_validate_cmd();
	}
	else if (key == KEY_CANCEL)
	{
		if (s_edit_item == EMPTY_LOAD_SETTING_NONE)
		{
			/* save */
			set_test_empty_load_setting(&s_empty_load_test_setting);
			
			switch_to_menu(MENU_ID_SYNTH_TEST_SETTING);
		}
		else
		{
			s_focus_fun_arr[s_focus_item]();
			
			lcd_validate_cmd();
			
			s_edit_item = EMPTY_LOAD_SETTING_NONE;
		}
	}	
}

static void init_callback(void *msg)
{
	get_test_empty_load_setting(&s_empty_load_test_setting);
	
	draw_empty_load_setting_menu();

	draw_focus_empty_load_setting_time(s_empty_load_test_setting.duration);
	
	draw_normal_empty_load_setting_ac(s_empty_load_test_setting.ac_limit);
	
	draw_normal_empty_load_setting_voltage_from(s_empty_load_test_setting.voltage_from);
	
	draw_normal_empty_load_setting_voltage_to(s_empty_load_test_setting.voltage_to);

	draw_normal_empty_load_dp_dn_mode(s_empty_load_test_setting.dp_dn_setting.mode);

	draw_normal_empty_load_dp_dn_on_off(s_empty_load_test_setting.dp_dn_setting.on_off);
	
	lcd_validate_cmd();
	
	s_focus_item = EMPTY_LOAD_SETTING_TIME;
	
	s_edit_item = EMPTY_LOAD_SETTING_NONE;
}

static void destroy_callback(void *msg)
{
	lcd_clear(SCREEN_BACK_COLOR);		
}

BEGIN_MENU_HANDLER(MENU_ID_EMPTY_LOAD_SETTING)

IMPLEMENT_MSG_HANDLER(MSG_ID_KEY, key_handler)
IMPLEMENT_MSG_HANDLER(MSG_ID_INIT, init_callback)
IMPLEMENT_MSG_HANDLER(MSG_ID_DESTROY, destroy_callback)

END_MENU_HANDLER()


void load_dp_dn_divide_mode_setting(DIVIDE_MODE_SETTING *divide_mode_setting)
{
	*divide_mode_setting = s_empty_load_test_setting.dp_dn_setting.divide_mode_setting;
}

void set_dp_dn_divide_mode_setting(const DIVIDE_MODE_SETTING *divide_mode_setting)
{
	s_empty_load_test_setting.dp_dn_setting.divide_mode_setting = *divide_mode_setting;
}
