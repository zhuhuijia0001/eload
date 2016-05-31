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
	MAIN_ITEM_SYNTH_TEST = 0,
	
	MAIN_ITEM_CV_MODE,

	MAIN_ITEM_CC_MODE,

	MAIN_ITEM_CR_MODE,

	MAIN_ITEM_CHANNEL_SET,

	MAIN_ITEM_COUNT
} main_item;

static main_item s_cur_focus_item = MAIN_ITEM_SYNTH_TEST;

static MENU_ID const s_main_id_arr[] = 
{
	[MAIN_ITEM_SYNTH_TEST] = MENU_ID_SYNTH_TEST_SETTING,
	
	[MAIN_ITEM_CV_MODE] = MENU_ID_CV_MODE,
	
	[MAIN_ITEM_CC_MODE] = MENU_ID_CC_MODE,
	
	[MAIN_ITEM_CR_MODE] = MENU_ID_CR_MODE,

	[MAIN_ITEM_CHANNEL_SET] = MENU_ID_CHANNEL_SETTING
};

static void (*const s_focus_fun_arr[])(void) = 
{
	[MAIN_ITEM_SYNTH_TEST] = draw_focus_main_item_synth_test,
	
	[MAIN_ITEM_CV_MODE] = draw_focus_main_item_cv_mode,

	[MAIN_ITEM_CC_MODE] = draw_focus_main_item_cc_mode,
	
	[MAIN_ITEM_CR_MODE] = draw_focus_main_item_cr_mode,

	[MAIN_ITEM_CHANNEL_SET] = draw_focus_main_item_channel_set
};

static void (*const s_unfocus_fun_arr[])(void) = 
{
	[MAIN_ITEM_SYNTH_TEST] = draw_normal_main_item_synth_test,
	
	[MAIN_ITEM_CV_MODE] = draw_normal_main_item_cv_mode,

	[MAIN_ITEM_CC_MODE] = draw_normal_main_item_cc_mode,
	
	[MAIN_ITEM_CR_MODE] = draw_normal_main_item_cr_mode,

	[MAIN_ITEM_CHANNEL_SET] = draw_normal_main_item_channel_set
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
		s_unfocus_fun_arr[s_cur_focus_item]();
		
		s_cur_focus_item += MAIN_ITEM_COUNT - 1;
		s_cur_focus_item %= MAIN_ITEM_COUNT;
		
		s_focus_fun_arr[s_cur_focus_item]();
		
		lcd_validate_cmd();
	}
	else if (key == KEY_DOWN)
	{
		s_unfocus_fun_arr[s_cur_focus_item]();
		
		s_cur_focus_item++;
		s_cur_focus_item %= MAIN_ITEM_COUNT;
		
		s_focus_fun_arr[s_cur_focus_item]();
		
		lcd_validate_cmd();	
	}
	else if (key == KEY_OK)
	{
		switch_to_menu(s_main_id_arr[s_cur_focus_item]);
	}
}

static void init_callback(void *msg)
{
	draw_main_items();
	
	s_focus_fun_arr[s_cur_focus_item]();
	
	lcd_validate_cmd();
}

static void destroy_callback(void *msg)
{
	lcd_clear(SCREEN_BACK_COLOR);
}

BEGIN_MENU_HANDLER(MENU_ID_MAIN)

IMPLEMENT_MSG_HANDLER(MSG_ID_KEY, key_handler)
IMPLEMENT_MSG_HANDLER(MSG_ID_INIT, init_callback)
IMPLEMENT_MSG_HANDLER(MSG_ID_DESTROY, destroy_callback)

END_MENU_HANDLER()

