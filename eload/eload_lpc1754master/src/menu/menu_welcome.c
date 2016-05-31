
#include <stdint.h>
#include "type.h"

#include "key_define.h"

#include "menu_op.h"
#include "menu.h"

#include "lcd.h"
#include "draw.h"

#include "beeper.h"

/* acc key */
static const int  ACC_KEY_COUNT =  4;

static uint8_t s_acc_keys[ACC_KEY_COUNT];
static uint8_t s_key_index = 0;

static bool is_factory_mode_activated(void)
{
	return s_acc_keys[0] == KEY_UP
			 && s_acc_keys[1] == KEY_DOWN
			 && s_acc_keys[2] == KEY_LEFT
			 && s_acc_keys[3] == KEY_RIGHT;
}

static void key_handler(void *msg)
{
	key_t key_msg = (key_t)(uint32_t)msg;
	
	if (KEY_TYPE(key_msg) != MASK_KEY_PRESS)
	{
		return;
	}
	
	beeper_beep(BEEPER_VOL_LOW, 50, 50, 1);
	
	s_acc_keys[s_key_index++] = KEY_VALUE(key_msg);
	if (s_key_index == ACC_KEY_COUNT)
	{
		/* verify */
		if (is_factory_mode_activated())
		{
			switch_to_menu(MENU_ID_FACTORY_MODE);
		}
		else
		{
			beeper_beep(BEEPER_VOL_MEDIUM, 50, 50, 2);
		}
		
		s_key_index = 0;
	}	
}

static void init_callback(void *msg)
{
	draw_welcome_menu();
		
	lcd_validate_cmd();		
}

static void destroy_callback(void *msg)
{
	lcd_clear(SCREEN_BACK_COLOR);	
}

BEGIN_MENU_HANDLER(MENU_ID_WELCOME)

IMPLEMENT_MSG_HANDLER(MSG_ID_KEY, key_handler)
IMPLEMENT_MSG_HANDLER(MSG_ID_INIT, init_callback)
IMPLEMENT_MSG_HANDLER(MSG_ID_DESTROY, destroy_callback)

END_MENU_HANDLER()


