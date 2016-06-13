#include <stdint.h>
#include "type.h"
#include "key_define.h"

#include "menu_op.h"
#include "menu.h"

#include "lcd.h"
#include "draw.h"

#include "led.h"
#include "beeper.h"

#include "packet.h"
#include "global.h"

#include "trace.h"

typedef enum
{
	CHANNEL_1_SETTING = 0,

	CHANNEL_2_SETTING,

	CHANNEL_3_SETTING,

	CHANNEL_4_SETTING,

	CHANNEL_5_SETTING,

	CHANNEL_6_SETTING,

	CHANNEL_7_SETTING,

	CHANNEL_8_SETTING,

	CHANNEL_SETTING_NONE,

	CHANNEL_SETTING_COUNT = CHANNEL_SETTING_NONE
} channel_setting_item;

static channel_setting_item s_focus_item = CHANNEL_1_SETTING;

static channel_setting_item s_edit_item = CHANNEL_SETTING_NONE;

static OPTION_ON_OFF s_channel_set[CHANNEL_COUNT];

static OPTION_ON_OFF s_option_on_off;

/* unfocus function */
static void unfocus_channel_option(channel_setting_item item, OPTION_ON_OFF on_off)
{
	draw_normal_channel_option(item, on_off);
}

/* focus function */
static void focus_channel_option(channel_setting_item item, OPTION_ON_OFF on_off)
{
	draw_focus_channel_option(item, on_off);
}

/* edit function */
static void edit_channel_option(channel_setting_item item, OPTION_ON_OFF on_off)
{
	draw_edit_channel_option(item, on_off);
}

static channel_setting_item get_next_horz_item(channel_setting_item item)
{
	channel_setting_item item_save = item;
	
	do
	{
		item++;
		item %= CHANNEL_SETTING_COUNT;
	} while (g_channel_status[item] == CHANNEL_OFFLINE && item_save != item);
	
	return item;
}

static channel_setting_item get_prev_horz_item(channel_setting_item item)
{
	channel_setting_item item_save = item;

	do
	{
		item += CHANNEL_SETTING_COUNT - 1;
		item %= CHANNEL_SETTING_COUNT;
	} while (g_channel_status[item] == CHANNEL_OFFLINE && item_save != item);
	
	return item;
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
	
	if (key == KEY_LEFT || key == KEY_UP)
	{
		if (s_edit_item == CHANNEL_SETTING_NONE)
		{
			if (g_channel_status[s_focus_item] != CHANNEL_OFFLINE)
			{
				unfocus_channel_option(s_focus_item, s_channel_set[s_focus_item]);
			}
			
			s_focus_item = get_prev_horz_item(s_focus_item);
			if (g_channel_status[s_focus_item] != CHANNEL_OFFLINE)
			{
				focus_channel_option(s_focus_item, s_channel_set[s_focus_item]);
			}

			lcd_validate_cmd();
		}
		else
		{
			s_option_on_off += OPTION_ON_OFF_COUNT - 1;
			s_option_on_off %= OPTION_ON_OFF_COUNT;

			edit_channel_option(s_edit_item, s_option_on_off);

			lcd_validate_cmd();
		}
	}
	else if (key == KEY_RIGHT || key == KEY_DOWN)
	{
		if (s_edit_item == CHANNEL_SETTING_NONE)
		{
			if (g_channel_status[s_focus_item] != CHANNEL_OFFLINE)
			{
				unfocus_channel_option(s_focus_item, s_channel_set[s_focus_item]);
			}
			
			s_focus_item = get_next_horz_item(s_focus_item);
			if (g_channel_status[s_focus_item] != CHANNEL_OFFLINE)
			{
				focus_channel_option(s_focus_item, s_channel_set[s_focus_item]);
			}

			lcd_validate_cmd();
		}
		else
		{
			s_option_on_off++;
			s_option_on_off %= OPTION_ON_OFF_COUNT;

			edit_channel_option(s_edit_item, s_option_on_off);

			lcd_validate_cmd();
		}
	}
	else if (key == KEY_OK)
	{
		if (s_edit_item == CHANNEL_SETTING_NONE)
		{
			if (g_channel_status[s_focus_item] != CHANNEL_OFFLINE)
			{
				s_edit_item = s_focus_item;

				s_option_on_off = s_channel_set[s_edit_item];
				edit_channel_option(s_edit_item, s_option_on_off);

				lcd_validate_cmd();
			}
		}
		else
		{
			s_channel_set[s_edit_item] = s_option_on_off;

			s_edit_item = CHANNEL_SETTING_NONE;

			focus_channel_option(s_focus_item, s_channel_set[s_focus_item]);

			lcd_validate_cmd();

			save_parameter(STRUCT_OFFSET(PARAMETER, channel_set[s_focus_item]), &s_channel_set[s_focus_item], 
								sizeof(s_channel_set[s_focus_item]));
		}
	}
	else if (key == KEY_CANCEL)
	{
		if (s_edit_item != CHANNEL_SETTING_NONE)
		{
			s_edit_item = CHANNEL_SETTING_NONE;
			
			if (g_channel_status[s_focus_item] != CHANNEL_OFFLINE)
			{
				focus_channel_option(s_focus_item, s_channel_set[s_focus_item]);

				lcd_validate_cmd();
			}
		}
		else
		{
			switch_to_menu(MENU_ID_MAIN);
		}
	}
}

static void init_callback(void *msg)
{
	load_parameter(STRUCT_OFFSET(PARAMETER, channel_set), s_channel_set, sizeof(s_channel_set));
	
	draw_channel_setting_menu();

	draw_channel_setting_option(s_channel_set, g_channel_status);

	if (g_channel_status[s_focus_item] == CHANNEL_OFFLINE)
	{
		s_focus_item = get_next_horz_item(s_focus_item);
	}
	
	if (g_channel_status[s_focus_item] != CHANNEL_OFFLINE)
	{
		focus_channel_option(s_focus_item, s_channel_set[s_focus_item]);
	}
	
	lcd_validate_cmd();
}

static void destroy_callback(void *msg)
{
	lcd_clear(SCREEN_BACK_COLOR);
}

BEGIN_MENU_HANDLER(MENU_ID_CHANNEL_SETTING)

IMPLEMENT_MSG_HANDLER(MSG_ID_KEY, key_handler)
IMPLEMENT_MSG_HANDLER(MSG_ID_INIT, init_callback)
IMPLEMENT_MSG_HANDLER(MSG_ID_DESTROY, destroy_callback)

END_MENU_HANDLER()

