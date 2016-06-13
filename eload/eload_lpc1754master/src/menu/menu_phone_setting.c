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
	PHONE_SETTING_DEFAULT_NUMBER = 0,
	
	PHONE_SETTING_CUSTOMER_NUMBER,
	
	PHONE_SETTING_CUSTOMER_POWER_ON_LIMIT,
	
	PHONE_SETTING_NONE,
	
	PHONE_SETTING_COUNT = PHONE_SETTING_NONE
} phone_setting_item;

/* focus item */
static phone_setting_item s_focus_item = PHONE_SETTING_NONE;

/* edit item */
static phone_setting_item s_edit_item = PHONE_SETTING_NONE;

static PHONE_NUMBER_SETTING s_phone_number_setting;

/* acc key */
static const int  ACC_KEY_COUNT =  4;

static uint8_t s_acc_keys[ACC_KEY_COUNT];
static uint8_t s_key_index = 0;

static bool check_acc_keys(void)
{
	if (s_acc_keys[0] == KEY_LEFT
		&& s_acc_keys[1] == KEY_LEFT
		&& s_acc_keys[2] == KEY_RIGHT
		&& s_acc_keys[3] == KEY_RIGHT)
	{
		return true;
	}

	return false;
}

/* unfocus fun */
static void unfocus_default_phone_number(void)
{
	draw_normal_phone_setting_default_number(&s_phone_number_setting.default_phone_number);
}

static void unfocus_customer_phone_number(void)
{
	draw_normal_phone_setting_customer_number(&s_phone_number_setting.customer_phone_number);
}

static void unfocus_customer_power_on_limit(void)
{
	draw_normal_phone_setting_customer_power_on_limit(s_phone_number_setting.customer_phone_number_power_on_limit);
}

static void (*const s_unfocus_fun_arr[])(void) = 
{
	[PHONE_SETTING_DEFAULT_NUMBER]          = unfocus_default_phone_number,
	
	[PHONE_SETTING_CUSTOMER_NUMBER]         = unfocus_customer_phone_number,
	
	[PHONE_SETTING_CUSTOMER_POWER_ON_LIMIT] = unfocus_customer_power_on_limit
};

/* focus fun */
static void focus_default_phone_number(void)
{
	draw_focus_phone_setting_default_number(&s_phone_number_setting.default_phone_number);
}

static void focus_customer_phone_number(void)
{
	draw_focus_phone_setting_customer_number(&s_phone_number_setting.customer_phone_number);
}

static void focus_customer_power_on_limit(void)
{
	draw_focus_phone_setting_customer_power_on_limit(s_phone_number_setting.customer_phone_number_power_on_limit);
}

static void (*const s_focus_fun_arr[])(void) = 
{
	[PHONE_SETTING_DEFAULT_NUMBER]          = focus_default_phone_number,
	
	[PHONE_SETTING_CUSTOMER_NUMBER]         = focus_customer_phone_number,
	
	[PHONE_SETTING_CUSTOMER_POWER_ON_LIMIT] = focus_customer_power_on_limit
};

/* enter edit fun */
static void enter_edit_default_phone_number(void)
{
	enter_edit_phone_setting_default_number(&s_phone_number_setting.default_phone_number);
	
	s_edit_item = PHONE_SETTING_DEFAULT_NUMBER;
}

static void enter_edit_customer_phone_number(void)
{
	enter_edit_phone_setting_customer_number(&s_phone_number_setting.customer_phone_number);
	
	s_edit_item = PHONE_SETTING_CUSTOMER_NUMBER;
}

static void enter_edit_customer_power_on_limit(void)
{
	enter_edit_phone_setting_customer_power_on_limit(s_phone_number_setting.customer_phone_number_power_on_limit);
	
	s_edit_item = PHONE_SETTING_CUSTOMER_POWER_ON_LIMIT;
}

static void (*const s_enter_edit_fun_arr[])(void) = 
{
	[PHONE_SETTING_DEFAULT_NUMBER]          = enter_edit_default_phone_number,
	
	[PHONE_SETTING_CUSTOMER_NUMBER]         = enter_edit_customer_phone_number,
	
	[PHONE_SETTING_CUSTOMER_POWER_ON_LIMIT] = enter_edit_customer_power_on_limit
};

/* edit fun */
static void edit_default_phone_number(uint8_t key)
{
	if (key == KEY_UP)
	{
		increase_edit_phone_setting_default_number_digit();
	}
	else if (key == KEY_DOWN)
	{
		decrease_edit_phone_setting_default_number_digit();
	}
	else if (key == KEY_LEFT)
	{
		move_prev_edit_phone_setting_default_number_digit();
	}
	else if (key == KEY_RIGHT)
	{
		move_next_edit_phone_setting_default_number_digit();
	}
}

static void edit_customer_phone_number(uint8_t key)
{
	if (key == KEY_UP)
	{
		increase_edit_phone_setting_customer_number_digit();
	}
	else if (key == KEY_DOWN)
	{
		decrease_edit_phone_setting_customer_number_digit();
	}
	else if (key == KEY_LEFT)
	{
		move_prev_edit_phone_setting_customer_number_digit();
	}
	else if (key == KEY_RIGHT)
	{
		move_next_edit_phone_setting_customer_number_digit();
	}
}

static void edit_customer_power_on_limit(uint8_t key)
{
	if (key == KEY_UP)
	{
		increase_edit_phone_setting_customer_power_on_limit_digit();
	}
	else if (key == KEY_DOWN)
	{
		decrease_edit_phone_setting_customer_power_on_limit_digit();
	}
	else if (key == KEY_LEFT)
	{
		move_prev_edit_phone_setting_customer_power_on_limit_digit();
	}
	else if (key == KEY_RIGHT)
	{
		move_next_edit_phone_setting_customer_power_on_limit_digit();
	}
}

static void (*const s_edit_fun_arr[])(uint8_t key) = 
{
	[PHONE_SETTING_DEFAULT_NUMBER]          = edit_default_phone_number,
	
	[PHONE_SETTING_CUSTOMER_NUMBER]         = edit_customer_phone_number,
	
	[PHONE_SETTING_CUSTOMER_POWER_ON_LIMIT] = edit_customer_power_on_limit
};

/* confirm edit fun */
static void confirm_edit_default_phone_number(void)
{
	get_edit_phone_setting_default_number(&s_phone_number_setting.default_phone_number);

	draw_focus_phone_setting_default_number(&s_phone_number_setting.default_phone_number);
}

static void confirm_edit_customer_phone_number(void)
{
	get_edit_phone_setting_default_number(&s_phone_number_setting.customer_phone_number);

	draw_focus_phone_setting_customer_number(&s_phone_number_setting.customer_phone_number);
}

static void confirm_edit_customer_power_on_limit(void)
{
	s_phone_number_setting.customer_phone_number_power_on_limit = get_edit_phone_setting_customer_power_on_limit();

	draw_focus_phone_setting_customer_power_on_limit(s_phone_number_setting.customer_phone_number_power_on_limit);
}

static void (*const s_confirm_edit_fun_arr[])(void) = 
{
	[PHONE_SETTING_DEFAULT_NUMBER]          = confirm_edit_default_phone_number,
	
	[PHONE_SETTING_CUSTOMER_NUMBER]         = confirm_edit_customer_phone_number,
	
	[PHONE_SETTING_CUSTOMER_POWER_ON_LIMIT] = confirm_edit_customer_power_on_limit
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
	
	if (key == KEY_UP)
	{
		if (s_edit_item == PHONE_SETTING_NONE)
		{
			s_unfocus_fun_arr[s_focus_item]();
			
			s_focus_item += PHONE_SETTING_COUNT - 1;
			s_focus_item %= PHONE_SETTING_COUNT;
			
			s_focus_fun_arr[s_focus_item]();
		}
		else
		{
			s_edit_fun_arr[s_edit_item](key);
		}
		
		lcd_validate_cmd();
	}
	else if (key == KEY_DOWN)
	{
		if (s_edit_item == PHONE_SETTING_NONE)
		{
			s_unfocus_fun_arr[s_focus_item]();
			
			s_focus_item++;
			s_focus_item %= PHONE_SETTING_COUNT;
			
			s_focus_fun_arr[s_focus_item]();
		}
		else
		{
			s_edit_fun_arr[s_edit_item](key);
		}

		lcd_validate_cmd();
	}
	else if (key == KEY_LEFT || key == KEY_RIGHT)
	{
		if (s_edit_item == PHONE_SETTING_NONE)
		{
			s_acc_keys[s_key_index++] = key;

			if (s_key_index == ACC_KEY_COUNT)
			{	
				if (check_acc_keys())
				{
					s_phone_number_setting.customer_phone_number_power_on_count = 0;
					save_parameter(STRUCT_OFFSET(PARAMETER, phone_number_setting), &s_phone_number_setting, sizeof(s_phone_number_setting));

					draw_normal_phone_setting_actual_customer_power_on_count(s_phone_number_setting.customer_phone_number_power_on_count);

					lcd_validate_cmd();
					
					beeper_beep(BEEPER_VOL_MEDIUM, 50, 50, 1);
				}
				else
				{
					beeper_beep(BEEPER_VOL_MEDIUM, 50, 50, 2);
				}

				s_key_index = 0;
			}
		}
		else
		{
			s_edit_fun_arr[s_edit_item](key);

			lcd_validate_cmd();
		}
	}
	else if (key == KEY_OK)
	{
		if (s_edit_item == PHONE_SETTING_NONE)
		{
			s_enter_edit_fun_arr[s_focus_item]();

			lcd_validate_cmd();
		}
		else
		{
			s_confirm_edit_fun_arr[s_focus_item]();

			lcd_validate_cmd();
			
			save_parameter(STRUCT_OFFSET(PARAMETER, phone_number_setting), &s_phone_number_setting, sizeof(s_phone_number_setting));

			s_edit_item = PHONE_SETTING_NONE;

			s_key_index = 0;
		}
	}
	else if (key == KEY_CANCEL)
	{
		if (s_edit_item == PHONE_SETTING_NONE)
		{
			switch_to_menu(MENU_ID_FACTORY_MODE);
		}
		else
		{
			s_focus_fun_arr[s_focus_item]();
			
			lcd_validate_cmd();
			
			s_edit_item = PHONE_SETTING_NONE;

			s_key_index = 0;
		}
	}	
}

static void init_callback(void *msg)
{
	load_parameter(STRUCT_OFFSET(PARAMETER, phone_number_setting), &s_phone_number_setting, sizeof(s_phone_number_setting));
	
	draw_phone_setting_menu();
	
	draw_focus_phone_setting_default_number(&s_phone_number_setting.default_phone_number);
	
	draw_normal_phone_setting_customer_number(&s_phone_number_setting.customer_phone_number);
	
	draw_normal_phone_setting_customer_power_on_limit(s_phone_number_setting.customer_phone_number_power_on_limit);
	
	draw_normal_phone_setting_actual_customer_power_on_count(s_phone_number_setting.customer_phone_number_power_on_count);
	
	s_focus_item = PHONE_SETTING_DEFAULT_NUMBER;
	
	s_edit_item = PHONE_SETTING_NONE;
	
	s_key_index = 0;

	lcd_validate_cmd();
}

static void destroy_callback(void *msg)
{
	lcd_clear(SCREEN_BACK_COLOR);
}

BEGIN_MENU_HANDLER(MENU_ID_PHONE_SETTING)

IMPLEMENT_MSG_HANDLER(MSG_ID_KEY, key_handler)
IMPLEMENT_MSG_HANDLER(MSG_ID_INIT, init_callback)
IMPLEMENT_MSG_HANDLER(MSG_ID_DESTROY, destroy_callback)

END_MENU_HANDLER()

