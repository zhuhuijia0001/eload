#include <stdint.h>
#include "type.h"

#include "key_define.h"

#include "menu_op.h"
#include "menu.h"

#include "lcd.h"
#include "draw.h"

#include "beeper.h"

static PASSWORD s_password;

static PASSWORD s_password_edit = 
{
	.password = { '0', '0', '0', '0', '0', '0' },
};

static bool is_password_correct(void)
{
	int i;
	for (i = 0; i < PASSWORD_LEN; i++)
	{
		if (s_password_edit.password[i] != s_password.password[i])
		{
			return false;
		}
	}

	return true;
}

/* edit fun */
static void edit_password(uint8_t key)
{
	if (key == KEY_UP)
	{
		increase_edit_password_digit();
	}
	else if (key == KEY_DOWN)
	{
		decrease_edit_password_digit();
	}
	else if (key == KEY_LEFT)
	{
		move_prev_edit_password_digit();
	}
	else if (key == KEY_RIGHT)
	{
		move_next_edit_password_digit();
	}
}

static void key_handler(void *msg)
{
	key_t key_msg = (key_t)(uint32_t)msg;
	
	if (KEY_TYPE(key_msg) != MASK_KEY_PRESS)
	{
		return;
	}
	
	beeper_beep(BEEPER_VOL_LOW, 50, 50, 1);
	
	uint8_t key = KEY_VALUE(key_msg);
	if (key == KEY_UP || key == KEY_DOWN || key == KEY_LEFT || key == KEY_RIGHT)
	{
		edit_password(key);

		lcd_validate_cmd();	
	}	
	else if (key == KEY_OK)
	{
		get_edit_password(&s_password_edit);
		
		if (is_password_correct())
		{
			switch_to_menu(MENU_ID_FACTORY_MODE);
		}
		else
		{
			beeper_beep(BEEPER_VOL_MEDIUM, 50, 50, 2);
		}
	}
	else if (key == KEY_CANCEL)
	{
		switch_to_menu(MENU_ID_MAIN);
	}
}

static void init_callback(void *msg)
{
	load_parameter(STRUCT_OFFSET(PARAMETER, password), &s_password, sizeof(s_password));
	
	draw_password_menu();

	enter_edit_password(&s_password_edit);
	
	lcd_validate_cmd();		
}

static void destroy_callback(void *msg)
{
	lcd_clear(SCREEN_BACK_COLOR);	
}

BEGIN_MENU_HANDLER(MENU_ID_PASSWORD)

IMPLEMENT_MSG_HANDLER(MSG_ID_KEY, key_handler)
IMPLEMENT_MSG_HANDLER(MSG_ID_INIT, init_callback)
IMPLEMENT_MSG_HANDLER(MSG_ID_DESTROY, destroy_callback)

END_MENU_HANDLER()

