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
	DIVIDE_MODE_DP_VOLTAGE_FROM,
	
	DIVIDE_MODE_DP_VOLTAGE_TO,
	
	DIVIDE_MODE_DN_VOLTAGE_FROM,
	
	DIVIDE_MODE_DN_VOLTAGE_TO,

	DIVIDE_MODE_NONE,
	
	DIVIDE_MODE_COUNT = DIVIDE_MODE_NONE
} divide_mode_setting_item;

static divide_mode_setting_item s_focus_item = DIVIDE_MODE_DP_VOLTAGE_FROM;

static divide_mode_setting_item s_edit_item = DIVIDE_MODE_NONE;

static DIVIDE_MODE_SETTING s_divide_mode_setting;


/* max voltage */
static const uint32_t MAX_VOLTAGE = 30000ul;

static const uint32_t BIG_VOLTAGE_STEP = 1000ul;

static const uint32_t SMALL_VOLTAGE_STEP = 10ul;

static uint32_t s_cur_dp_voltage_from;
static uint32_t s_cur_dp_voltage_to;
static uint32_t s_cur_dn_voltage_from;
static uint32_t s_cur_dn_voltage_to;

extern void load_dp_dn_divide_mode_setting(DIVIDE_MODE_SETTING *divide_mode_setting);

extern void set_dp_dn_divide_mode_setting(const DIVIDE_MODE_SETTING *divide_mode_setting);

/* unfocus function */
static void unfocus_dp_voltage_from(void)
{
	draw_normal_divide_mode_dp_voltage_from(s_divide_mode_setting.dp_voltage_from);
}

static void unfocus_dp_voltage_to(void)
{
	draw_normal_divide_mode_dp_voltage_to(s_divide_mode_setting.dp_voltage_to);
}

static void unfocus_dn_voltage_from(void)
{
	draw_normal_divide_mode_dn_voltage_from(s_divide_mode_setting.dn_voltage_from);
}

static void unfocus_dn_voltage_to(void)
{
	draw_normal_divide_mode_dn_voltage_to(s_divide_mode_setting.dn_voltage_to);
}

static void (*const s_unfocus_fun_arr[])(void) = 
{
	[DIVIDE_MODE_DP_VOLTAGE_FROM] = unfocus_dp_voltage_from,
	
	[DIVIDE_MODE_DP_VOLTAGE_TO]   = unfocus_dp_voltage_to,
	
	[DIVIDE_MODE_DN_VOLTAGE_FROM] = unfocus_dn_voltage_from,
	
	[DIVIDE_MODE_DN_VOLTAGE_TO]   = unfocus_dn_voltage_to
};

/* focus function */
static void focus_dp_voltage_from(void)
{
	draw_focus_divide_mode_dp_voltage_from(s_divide_mode_setting.dp_voltage_from);
}

static void focus_dp_voltage_to(void)
{
	draw_focus_divide_mode_dp_voltage_to(s_divide_mode_setting.dp_voltage_to);
}

static void focus_dn_voltage_from(void)
{
	draw_focus_divide_mode_dn_voltage_from(s_divide_mode_setting.dn_voltage_from);
}

static void focus_dn_voltage_to(void)
{
	draw_focus_divide_mode_dn_voltage_to(s_divide_mode_setting.dn_voltage_to);
}

static void (*const s_focus_fun_arr[])(void) = 
{
	[DIVIDE_MODE_DP_VOLTAGE_FROM] = focus_dp_voltage_from,
	
	[DIVIDE_MODE_DP_VOLTAGE_TO]   = focus_dp_voltage_to,
	
	[DIVIDE_MODE_DN_VOLTAGE_FROM] = focus_dn_voltage_from,
	
	[DIVIDE_MODE_DN_VOLTAGE_TO]   = focus_dn_voltage_to
};

/* enter edit function */
static void enter_edit_dp_voltage_from(void)
{
	s_cur_dp_voltage_from = s_divide_mode_setting.dp_voltage_from;
	draw_edit_divide_mode_dp_voltage_from(s_cur_dp_voltage_from);
	
	s_edit_item = DIVIDE_MODE_DP_VOLTAGE_FROM;
}

static void enter_edit_dp_voltage_to(void)
{
	s_cur_dp_voltage_to = s_divide_mode_setting.dp_voltage_to;
	draw_edit_divide_mode_dp_voltage_to(s_cur_dp_voltage_to);
	
	s_edit_item = DIVIDE_MODE_DP_VOLTAGE_TO;
}

static void enter_edit_dn_voltage_from(void)
{
	s_cur_dn_voltage_from = s_divide_mode_setting.dn_voltage_from;
	draw_edit_divide_mode_dn_voltage_from(s_cur_dn_voltage_from);
	
	s_edit_item = DIVIDE_MODE_DN_VOLTAGE_FROM;
}

static void enter_edit_dn_voltage_to(void)
{
	s_cur_dn_voltage_to = s_divide_mode_setting.dn_voltage_to;
	draw_edit_divide_mode_dn_voltage_to(s_cur_dn_voltage_to);
	
	s_edit_item = DIVIDE_MODE_DN_VOLTAGE_TO;
}

static void (*const s_enter_edit_fun_arr[])(void) = 
{
	[DIVIDE_MODE_DP_VOLTAGE_FROM] = enter_edit_dp_voltage_from,
	
	[DIVIDE_MODE_DP_VOLTAGE_TO]   = enter_edit_dp_voltage_to,
	
	[DIVIDE_MODE_DN_VOLTAGE_FROM] = enter_edit_dn_voltage_from,
	
	[DIVIDE_MODE_DN_VOLTAGE_TO]   = enter_edit_dn_voltage_to
};

/* confirm edit function */
static void confirm_edit_dp_voltage_from(void)
{
	s_divide_mode_setting.dp_voltage_from = s_cur_dp_voltage_from;
	draw_focus_divide_mode_dp_voltage_from(s_divide_mode_setting.dp_voltage_from);
}

static void confirm_edit_dp_voltage_to(void)
{
	s_divide_mode_setting.dp_voltage_to = s_cur_dp_voltage_to;
	draw_focus_divide_mode_dp_voltage_to(s_divide_mode_setting.dp_voltage_to);
}

static void confirm_edit_dn_voltage_from(void)
{
	s_divide_mode_setting.dn_voltage_from = s_cur_dn_voltage_from;
	draw_focus_divide_mode_dn_voltage_from(s_divide_mode_setting.dn_voltage_from);
}

static void confirm_edit_dn_voltage_to(void)
{
	s_divide_mode_setting.dn_voltage_to = s_cur_dn_voltage_to;
	draw_focus_divide_mode_dn_voltage_to(s_divide_mode_setting.dn_voltage_to);
}

static void (*const s_confirm_edit_fun_arr[])(void) = 
{
	[DIVIDE_MODE_DP_VOLTAGE_FROM] = confirm_edit_dp_voltage_from,
	
	[DIVIDE_MODE_DP_VOLTAGE_TO]   = confirm_edit_dp_voltage_to,
	
	[DIVIDE_MODE_DN_VOLTAGE_FROM] = confirm_edit_dn_voltage_from,
	
	[DIVIDE_MODE_DN_VOLTAGE_TO]   = confirm_edit_dn_voltage_to
};

/* edit function */
static void edit_dp_voltage_from(uint8_t key)
{
	if (key == KEY_UP)
	{
		s_cur_dp_voltage_from += BIG_VOLTAGE_STEP;
		if (s_cur_dp_voltage_from > MAX_VOLTAGE)
		{
			s_cur_dp_voltage_from = MAX_VOLTAGE;
		}
		draw_edit_divide_mode_dp_voltage_from(s_cur_dp_voltage_from);
	}
	else if (key == KEY_DOWN)
	{
		if (s_cur_dp_voltage_from > BIG_VOLTAGE_STEP)
		{
			s_cur_dp_voltage_from -= BIG_VOLTAGE_STEP;
		}
		else
		{
			s_cur_dp_voltage_from = SMALL_VOLTAGE_STEP;
		}
		draw_edit_divide_mode_dp_voltage_from(s_cur_dp_voltage_from);
	}
	else if (key == KEY_RIGHT)
	{
		s_cur_dp_voltage_from += SMALL_VOLTAGE_STEP;
		if (s_cur_dp_voltage_from > MAX_VOLTAGE)
		{
			s_cur_dp_voltage_from = MAX_VOLTAGE;
		}
		draw_edit_divide_mode_dp_voltage_from(s_cur_dp_voltage_from);
	}
	else if (key == KEY_LEFT)
	{
		if (s_cur_dp_voltage_from > SMALL_VOLTAGE_STEP)
		{
			s_cur_dp_voltage_from -= SMALL_VOLTAGE_STEP;
		}
		draw_edit_divide_mode_dp_voltage_from(s_cur_dp_voltage_from);
	}
}

static void edit_dp_voltage_to(uint8_t key)
{
	if (key == KEY_UP)
	{
		s_cur_dp_voltage_to += BIG_VOLTAGE_STEP;
		if (s_cur_dp_voltage_to > MAX_VOLTAGE)
		{
			s_cur_dp_voltage_to = MAX_VOLTAGE;
		}
		draw_edit_divide_mode_dp_voltage_to(s_cur_dp_voltage_to);
	}
	else if (key == KEY_DOWN)
	{
		if (s_cur_dp_voltage_to > BIG_VOLTAGE_STEP)
		{
			s_cur_dp_voltage_to -= BIG_VOLTAGE_STEP;
		}
		else
		{
			s_cur_dp_voltage_to = SMALL_VOLTAGE_STEP;
		}
		draw_edit_divide_mode_dp_voltage_to(s_cur_dp_voltage_to);
	}
	else if (key == KEY_RIGHT)
	{
		s_cur_dp_voltage_to += SMALL_VOLTAGE_STEP;
		if (s_cur_dp_voltage_to > MAX_VOLTAGE)
		{
			s_cur_dp_voltage_to = MAX_VOLTAGE;
		}
		draw_edit_divide_mode_dp_voltage_to(s_cur_dp_voltage_to);
	}
	else if (key == KEY_LEFT)
	{
		if (s_cur_dp_voltage_to > SMALL_VOLTAGE_STEP)
		{
			s_cur_dp_voltage_to -= SMALL_VOLTAGE_STEP;
		}
		draw_edit_divide_mode_dp_voltage_to(s_cur_dp_voltage_to);
	}
}

static void edit_dn_voltage_from(uint8_t key)
{
	if (key == KEY_UP)
	{
		s_cur_dn_voltage_from += BIG_VOLTAGE_STEP;
		if (s_cur_dn_voltage_from > MAX_VOLTAGE)
		{
			s_cur_dn_voltage_from = MAX_VOLTAGE;
		}
		draw_edit_divide_mode_dn_voltage_from(s_cur_dn_voltage_from);
	}
	else if (key == KEY_DOWN)
	{
		if (s_cur_dn_voltage_from > BIG_VOLTAGE_STEP)
		{
			s_cur_dn_voltage_from -= BIG_VOLTAGE_STEP;
		}
		else
		{
			s_cur_dn_voltage_from = SMALL_VOLTAGE_STEP;
		}
		draw_edit_divide_mode_dn_voltage_from(s_cur_dn_voltage_from);
	}
	else if (key == KEY_RIGHT)
	{
		s_cur_dn_voltage_from += SMALL_VOLTAGE_STEP;
		if (s_cur_dn_voltage_from > MAX_VOLTAGE)
		{
			s_cur_dn_voltage_from = MAX_VOLTAGE;
		}
		draw_edit_divide_mode_dn_voltage_from(s_cur_dn_voltage_from);
	}
	else if (key == KEY_LEFT)
	{
		if (s_cur_dn_voltage_from > SMALL_VOLTAGE_STEP)
		{
			s_cur_dn_voltage_from -= SMALL_VOLTAGE_STEP;
		}
		draw_edit_divide_mode_dn_voltage_from(s_cur_dn_voltage_from);
	}
}

static void edit_dn_voltage_to(uint8_t key)
{
	if (key == KEY_UP)
	{
		s_cur_dn_voltage_to += BIG_VOLTAGE_STEP;
		if (s_cur_dn_voltage_to > MAX_VOLTAGE)
		{
			s_cur_dn_voltage_to = MAX_VOLTAGE;
		}
		draw_edit_divide_mode_dn_voltage_to(s_cur_dn_voltage_to);
	}
	else if (key == KEY_DOWN)
	{
		if (s_cur_dn_voltage_to > BIG_VOLTAGE_STEP)
		{
			s_cur_dn_voltage_to -= BIG_VOLTAGE_STEP;
		}
		else
		{
			s_cur_dn_voltage_to = SMALL_VOLTAGE_STEP;
		}
		draw_edit_divide_mode_dn_voltage_to(s_cur_dn_voltage_to);
	}
	else if (key == KEY_RIGHT)
	{
		s_cur_dn_voltage_to += SMALL_VOLTAGE_STEP;
		if (s_cur_dn_voltage_to > MAX_VOLTAGE)
		{
			s_cur_dn_voltage_to = MAX_VOLTAGE;
		}
		draw_edit_divide_mode_dn_voltage_to(s_cur_dn_voltage_to);
	}
	else if (key == KEY_LEFT)
	{
		if (s_cur_dn_voltage_to > SMALL_VOLTAGE_STEP)
		{
			s_cur_dn_voltage_to -= SMALL_VOLTAGE_STEP;
		}
		draw_edit_divide_mode_dn_voltage_to(s_cur_dn_voltage_to);
	}
}

static void (*const s_edit_fun_arr[])(uint8_t key) = 
{
	[DIVIDE_MODE_DP_VOLTAGE_FROM] = edit_dp_voltage_from,
	
	[DIVIDE_MODE_DP_VOLTAGE_TO]   = edit_dp_voltage_to,
	
	[DIVIDE_MODE_DN_VOLTAGE_FROM] = edit_dn_voltage_from,
	
	[DIVIDE_MODE_DN_VOLTAGE_TO]   = edit_dn_voltage_to
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
		if (s_edit_item == DIVIDE_MODE_NONE)
		{
			s_unfocus_fun_arr[s_focus_item]();
			
			s_focus_item += DIVIDE_MODE_COUNT - 1;
			s_focus_item %= DIVIDE_MODE_COUNT;
			
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
		if (s_edit_item == DIVIDE_MODE_NONE)
		{
			s_unfocus_fun_arr[s_focus_item]();
			
			s_focus_item++;
			s_focus_item %= DIVIDE_MODE_COUNT;
			
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
		if (s_edit_item == DIVIDE_MODE_NONE)
		{
			s_enter_edit_fun_arr[s_focus_item]();
		}
		else
		{
			s_confirm_edit_fun_arr[s_focus_item]();
			
			s_edit_item = DIVIDE_MODE_NONE;
		}
		
		lcd_validate_cmd();
	}
	else if (key == KEY_CANCEL)
	{
		if (s_edit_item == DIVIDE_MODE_NONE)
		{
			/* save */
			set_dp_dn_divide_mode_setting(&s_divide_mode_setting);
			
			switch_to_menu(MENU_ID_EMPTY_LOAD_SETTING);
		}
		else
		{
			s_focus_fun_arr[s_focus_item]();
			
			lcd_validate_cmd();
			
			s_edit_item = DIVIDE_MODE_NONE;
		}
	}
}

static void init_callback(void *msg)
{
	load_dp_dn_divide_mode_setting(&s_divide_mode_setting);
	
	draw_dp_dn_divide_mode_menu();

	s_edit_item = DIVIDE_MODE_NONE;
	
	s_focus_item = DIVIDE_MODE_DP_VOLTAGE_FROM;
	
	s_focus_fun_arr[s_focus_item]();

	draw_normal_divide_mode_dp_voltage_to(s_divide_mode_setting.dp_voltage_to);

	draw_normal_divide_mode_dn_voltage_from(s_divide_mode_setting.dn_voltage_from);

	draw_normal_divide_mode_dn_voltage_to(s_divide_mode_setting.dn_voltage_to);
}

static void destroy_callback(void *msg)
{
	lcd_clear(SCREEN_BACK_COLOR);
}

BEGIN_MENU_HANDLER(MENU_ID_USB_DP_DN_DIVIDE_MODE_SETTING)

IMPLEMENT_MSG_HANDLER(MSG_ID_KEY, key_handler)
IMPLEMENT_MSG_HANDLER(MSG_ID_INIT, init_callback)
IMPLEMENT_MSG_HANDLER(MSG_ID_DESTROY, destroy_callback)

END_MENU_HANDLER()

