
#include <stdint.h>
#include "type.h"
#include "key_define.h"

#include "menu_op.h"
#include "menu.h"

#include "lcd.h"
#include "draw.h"

#include "beeper.h"

static bool  s_editing = false;

static PASSWORD s_password;

/* edit fun */
static void edit_password(uint8_t key)
{
	if (key == KEY_UP)
	{
		increase_edit_password_setting_password_digit();
	}
	else if (key == KEY_DOWN)
	{
		decrease_edit_password_setting_password_digit();
	}
	else if (key == KEY_LEFT)
	{
		move_prev_edit_password_setting_password_digit();
	}
	else if (key == KEY_RIGHT)
	{
		move_next_edit_password_setting_password_digit();
	}
}

/* confirm edit fun */
static void confirm_edit_password(void)
{
	get_edit_password_setting_password(&s_password);

	draw_focus_password_setting_password(&s_password);
}

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
	
	if (key == KEY_UP || key == KEY_DOWN || key == KEY_LEFT || key == KEY_RIGHT)
	{
		if (s_editing)
		{
			edit_password(key);

			lcd_validate_cmd();
		}
	}
	else if (key == KEY_OK)
	{
		if (s_editing)
		{
			confirm_edit_password();

			s_editing = false;

			save_parameter(STRUCT_OFFSET(PARAMETER, password), &s_password, sizeof(s_password));
		}
		else
		{
			enter_edit_password_setting_password(&s_password);

			s_editing = true;
		}

		lcd_validate_cmd();
	}
	else if (key == KEY_CANCEL)
	{
		if (s_editing)
		{
			draw_focus_password_setting_password(&s_password);

			s_editing = false;
			
			lcd_validate_cmd();
		}
		else
		{
			switch_to_menu(MENU_ID_FACTORY_MODE);
		}
	}
}

static void init_callback(void *msg)
{
	load_parameter(STRUCT_OFFSET(PARAMETER, password), &s_password, sizeof(s_password));
	
	draw_password_setting_menu();

	draw_focus_password_setting_password(&s_password);

	lcd_validate_cmd();
}

static void destroy_callback(void *msg)
{
	lcd_clear(SCREEN_BACK_COLOR);
}

BEGIN_MENU_HANDLER(MENU_ID_PASSWORD_SETTING)

IMPLEMENT_MSG_HANDLER(MSG_ID_KEY, key_handler)
IMPLEMENT_MSG_HANDLER(MSG_ID_INIT, init_callback)
IMPLEMENT_MSG_HANDLER(MSG_ID_DESTROY, destroy_callback)

END_MENU_HANDLER()

