#include <stdint.h>
#include "type.h"
#include "key_define.h"

#include "menu_op.h"
#include "menu.h"

#include "lcd.h"
#include "draw.h"

#include "beeper.h"

typedef enum
{
	FACTORY_ITEM_ADJUST = 0,

	FACTORY_ITEM_PRIVILEGE,

	FACTORY_ITEM_LIFE,

	FACTORY_ITEM_PHONE,

	FACTORY_ITEM_COUNT
} factory_item;

static factory_item s_cur_factory_item = FACTORY_ITEM_ADJUST;

static MENU_ID const s_factory_id_arr[] = 
{
	[FACTORY_ITEM_ADJUST] = MENU_ID_ADJUST,
	
	[FACTORY_ITEM_PRIVILEGE] = MENU_ID_PRIVILEGE,
	
	[FACTORY_ITEM_LIFE] = MENU_ID_LIFE,
	
	[FACTORY_ITEM_PHONE] = MENU_ID_PHONE_SETTING
};

static void (*const s_focus_factory_item[])(void) = 
{
	[FACTORY_ITEM_ADJUST]    = draw_focus_factory_item_adjust,
	
	[FACTORY_ITEM_PRIVILEGE] = draw_focus_factory_item_privilege,
	
	[FACTORY_ITEM_LIFE]      = draw_focus_factory_item_life,
	
	[FACTORY_ITEM_PHONE]     = draw_focus_factory_item_phone
};

static void (*const s_unfocus_factory_item[])(void) = 
{
	[FACTORY_ITEM_ADJUST]    = draw_normal_factory_item_adjust,
	
	[FACTORY_ITEM_PRIVILEGE] = draw_normal_factory_item_privilege,
	
	[FACTORY_ITEM_LIFE]      = draw_normal_factory_item_life,
	
	[FACTORY_ITEM_PHONE]     = draw_normal_factory_item_phone
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
	
	if (key == KEY_UP)
	{
		s_unfocus_factory_item[s_cur_factory_item]();
		
		s_cur_factory_item += FACTORY_ITEM_COUNT - 1;
		s_cur_factory_item %= FACTORY_ITEM_COUNT;
		
		s_focus_factory_item[s_cur_factory_item]();
		
		lcd_validate_cmd();
	}
	else if (key == KEY_DOWN)
	{
		s_unfocus_factory_item[s_cur_factory_item]();
		
		s_cur_factory_item++;
		s_cur_factory_item %= FACTORY_ITEM_COUNT;
		
		s_focus_factory_item[s_cur_factory_item]();
		
		lcd_validate_cmd();
	}
	else if (key == KEY_OK)
	{
		switch_to_menu(s_factory_id_arr[s_cur_factory_item]);
	}
	else if (key == KEY_CANCEL)
	{
		switch_to_menu(MENU_ID_MAIN);
	}
}

static void init_callback(void *msg)
{
	draw_factory_menu();
	
	s_focus_factory_item[s_cur_factory_item]();
	
	lcd_validate_cmd();
}

static void destroy_callback(void *msg)
{
	lcd_clear(SCREEN_BACK_COLOR);
}

BEGIN_MENU_HANDLER(MENU_ID_FACTORY_MODE)

IMPLEMENT_MSG_HANDLER(MSG_ID_KEY, key_handler)
IMPLEMENT_MSG_HANDLER(MSG_ID_INIT, init_callback)
IMPLEMENT_MSG_HANDLER(MSG_ID_DESTROY, destroy_callback)

END_MENU_HANDLER()

