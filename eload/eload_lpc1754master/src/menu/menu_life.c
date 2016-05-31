#include <stdint.h>
#include "type.h"
#include "key_define.h"

#include "menu_op.h"
#include "menu.h"

#include "parameter.h"

#include "lcd.h"
#include "draw.h"

#include "beeper.h"

typedef enum
{
	LIFE_FOCUS_MODE = 0,
	
	LIFE_EDIT_MODE = 1
} life_mode;

static life_mode s_life_mode = LIFE_FOCUS_MODE;

static LIFE_LIMIT s_life_limit;

/* acc key */
static const int  ACC_KEY_COUNT =  4;

static uint8_t s_acc_keys[ACC_KEY_COUNT];
static uint8_t s_key_index = 0;

static bool check_acc_keys(void)
{
	if (s_acc_keys[0] == KEY_LEFT
		&& s_acc_keys[1] == KEY_RIGHT
		&& s_acc_keys[2] == KEY_LEFT
		&& s_acc_keys[3] == KEY_RIGHT)
	{
		return true;
	}

	return false;
}

static void key_handler(void *msg)
{
	key_t key_msg = (key_t)(uint32_t)msg;
	uint8_t key = KEY_VALUE(key_msg);
	
	if (KEY_TYPE(key_msg) == MASK_KEY_RELEASE)
	{
		return;
	}

	beeper_beep(BEEPER_VOL_LOW, 50, 50, 1);
	
	if (key == KEY_UP)
	{
		if (s_life_mode == LIFE_EDIT_MODE)
		{
			increase_edit_life_count_setting_digit();
		
			lcd_validate_cmd();
		}
	}
	else if (key == KEY_DOWN)
	{
		if (s_life_mode == LIFE_EDIT_MODE)
		{
			decrease_edit_life_count_setting_digit();
		
			lcd_validate_cmd();
		}		
	}
	else if (key == KEY_LEFT || key == KEY_RIGHT)
	{
		if (s_life_mode == LIFE_EDIT_MODE)
		{
			if (key == KEY_LEFT)
			{
				move_prev_edit_life_count_setting_digit();
			}
			else
			{
				move_next_edit_life_count_setting_digit();
			}
		
			lcd_validate_cmd();
		}
		else
		{
			s_acc_keys[s_key_index++] = key;

			if (s_key_index == ACC_KEY_COUNT)
			{	
				if (check_acc_keys())
				{
					s_life_limit.power_on_count = 0;
					save_parameter(STRUCT_OFFSET(PARAMETER, life_limit), &s_life_limit, sizeof(s_life_limit));

					draw_normal_life_actual_count_item(s_life_limit.power_on_count);

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
	}
	else if (key == KEY_OK)
	{
		if (s_life_mode == LIFE_FOCUS_MODE)
		{
			enter_edit_life_count_setting_item(s_life_limit.power_on_limit);
		
			lcd_validate_cmd();
		
			s_life_mode = LIFE_EDIT_MODE;
		}
		else
		{
			s_life_limit.power_on_limit = get_edit_life_count_setting_item();
			
			draw_focus_life_count_setting_item(s_life_limit.power_on_limit);
			
			lcd_validate_cmd();
			
			s_life_mode = LIFE_FOCUS_MODE;

			save_parameter(STRUCT_OFFSET(PARAMETER, life_limit), &s_life_limit, sizeof(s_life_limit));
		}
	}
	else if (key == KEY_CANCEL)
	{
		if (s_life_mode == LIFE_FOCUS_MODE)
		{
			switch_to_menu(MENU_ID_FACTORY_MODE);
		}
		else
		{	
			draw_focus_life_count_setting_item(s_life_limit.power_on_limit);
			
			lcd_validate_cmd();
			
			s_life_mode = LIFE_FOCUS_MODE;				
		}
	}
}

static void init_callback(void *msg)
{
	load_parameter(STRUCT_OFFSET(PARAMETER, life_limit), &s_life_limit, sizeof(s_life_limit));

	draw_life_limit_menu();
	
	draw_focus_life_count_setting_item(s_life_limit.power_on_limit);
	
	draw_normal_life_actual_count_item(s_life_limit.power_on_count);
	
	lcd_validate_cmd();
	
	s_life_mode = LIFE_FOCUS_MODE;

	s_key_index = 0;
}

static void destroy_callback(void *msg)
{
	lcd_clear(SCREEN_BACK_COLOR);		
}

BEGIN_MENU_HANDLER(MENU_ID_LIFE)

IMPLEMENT_MSG_HANDLER(MSG_ID_KEY, key_handler)
IMPLEMENT_MSG_HANDLER(MSG_ID_INIT, init_callback)
IMPLEMENT_MSG_HANDLER(MSG_ID_DESTROY, destroy_callback)

END_MENU_HANDLER()

