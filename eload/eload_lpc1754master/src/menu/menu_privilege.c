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
	PRIV_QC20,
	
	PRIV_MTK,
	
	PRIV_NONE,
	
	PRIV_COUNT = PRIV_NONE
} priv_item;

static priv_item s_focus_item = PRIV_QC20;

static priv_item s_edit_item = PRIV_NONE;

static OPTION_ON_OFF s_privilege_option_on_off = OPTION_ON;

static DEVICE_PRIVILEGE  s_device_privilege;

/* unfocus fun */
static void unfocus_qc_20_item(void)
{
	draw_normal_QC20_item(s_device_privilege.QC_20_test_on_off);
}

static void unfocus_MTK_item(void)
{
	draw_normal_MTK_item(s_device_privilege.MTK_test_on_off);
}

static void (*const s_unfocus_fun[])(void) = 
{
	[PRIV_QC20] = unfocus_qc_20_item,
	
	[PRIV_MTK]  = unfocus_MTK_item
};

/* focus fun */
static void focus_qc_20_item(void)
{
	draw_focus_QC20_item(s_device_privilege.QC_20_test_on_off);
}

static void focus_MTK_item(void)
{
	draw_focus_MTK_item(s_device_privilege.MTK_test_on_off);
}

static void (*const s_focus_fun[])(void) = 
{
	[PRIV_QC20] = focus_qc_20_item,
	
	[PRIV_MTK]  = focus_MTK_item
};

/* enter edit fun */
static void enter_edit_qc_20_item(void)
{
	s_privilege_option_on_off = s_device_privilege.QC_20_test_on_off;
	
	draw_edit_QC20_item(s_privilege_option_on_off);
}

static void enter_edit_MTK_item(void)
{
	s_privilege_option_on_off = s_device_privilege.MTK_test_on_off;
	
	draw_edit_MTK_item(s_privilege_option_on_off);
}

static void (*const s_enter_edit_fun[])(void) = 
{
	[PRIV_QC20] = enter_edit_qc_20_item,
	
	[PRIV_MTK]  = enter_edit_MTK_item
};

/* edit fun */
static void edit_qc_20_item(uint8_t key)
{
	if (key == KEY_LEFT || key == KEY_DOWN)
	{
		s_privilege_option_on_off += PRIV_COUNT - 1;
		s_privilege_option_on_off %= PRIV_COUNT;

		draw_edit_QC20_item(s_privilege_option_on_off);
	}
	else if (key == KEY_RIGHT || key == KEY_UP)
	{
		s_privilege_option_on_off++;
		s_privilege_option_on_off %= PRIV_COUNT;

		draw_edit_QC20_item(s_privilege_option_on_off);
	}
}

static void edit_MTK_item(uint8_t key)
{
	if (key == KEY_LEFT || key == KEY_DOWN)
	{
		s_privilege_option_on_off += PRIV_COUNT - 1;
		s_privilege_option_on_off %= PRIV_COUNT;

		draw_edit_MTK_item(s_privilege_option_on_off);
	}
	else if (key == KEY_RIGHT || key == KEY_UP)
	{
		s_privilege_option_on_off++;
		s_privilege_option_on_off %= PRIV_COUNT;

		draw_edit_MTK_item(s_privilege_option_on_off);
	}
}

static void (*const s_edit_fun[])(uint8_t key) = 
{
	[PRIV_QC20] = edit_qc_20_item,
	
	[PRIV_MTK]  = edit_MTK_item
};

/* confirm edit fun */
static void confirm_edit_qc_20_item(void)
{
	s_device_privilege.QC_20_test_on_off = s_privilege_option_on_off;
	draw_focus_QC20_item(s_device_privilege.QC_20_test_on_off);

	save_parameter(STRUCT_OFFSET(PARAMETER, device_privilege), &s_device_privilege, sizeof(s_device_privilege));
}

static void confirm_edit_MTK_item(void)
{
	s_device_privilege.MTK_test_on_off = s_privilege_option_on_off;
	draw_focus_MTK_item(s_device_privilege.MTK_test_on_off);

	save_parameter(STRUCT_OFFSET(PARAMETER, device_privilege), &s_device_privilege, sizeof(s_device_privilege));
}

static void (*const s_confirm_edit_fun[])(void) = 
{
	[PRIV_QC20] = confirm_edit_qc_20_item,
	
	[PRIV_MTK]  = confirm_edit_MTK_item
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
	
	if (key == KEY_RIGHT || key == KEY_UP)
	{
		if (s_edit_item == PRIV_NONE)
		{
			s_unfocus_fun[s_focus_item]();
			
			s_focus_item += PRIV_COUNT - 1;
			s_focus_item %= PRIV_COUNT;
			
			s_focus_fun[s_focus_item]();
		}
		else
		{
			s_edit_fun[s_edit_item](key);
		}

		lcd_validate_cmd();
	}	
	else if (key == KEY_LEFT || key == KEY_DOWN)
	{
		if (s_edit_item == PRIV_NONE)
		{
			s_unfocus_fun[s_focus_item]();
			
			s_focus_item++;
			s_focus_item %= PRIV_COUNT;
			
			s_focus_fun[s_focus_item]();
		}
		else
		{
			s_edit_fun[s_edit_item](key);
		}

		lcd_validate_cmd();
	}
	else if (key == KEY_OK)
	{
		if (s_edit_item == PRIV_NONE)
		{
			s_enter_edit_fun[s_focus_item]();
			
			s_edit_item = s_focus_item;	

			lcd_validate_cmd();
		}
		else
		{
			s_confirm_edit_fun[s_edit_item]();
			
			s_edit_item = PRIV_NONE;
			
			lcd_validate_cmd();
		}
	}
	else if (key == KEY_CANCEL)
	{
		if (s_edit_item == PRIV_NONE)
		{
			switch_to_menu(MENU_ID_FACTORY_MODE);			
		}
		else
		{
			s_focus_fun[s_edit_item]();
			
			s_edit_item = PRIV_NONE;
			
			lcd_validate_cmd();
		}		
	}
}

static void init_callback(void *msg)
{
	load_parameter(STRUCT_OFFSET(PARAMETER, device_privilege), &s_device_privilege, sizeof(s_device_privilege));
	
	draw_device_privilege_menu();
	
	s_focus_item = PRIV_QC20;
	s_edit_item = PRIV_NONE;
	
	s_focus_fun[s_focus_item]();
	
	draw_normal_MTK_item(s_device_privilege.MTK_test_on_off);
	
	lcd_validate_cmd();
}

static void destroy_callback(void *msg)
{
	lcd_clear(SCREEN_BACK_COLOR);	
}

BEGIN_MENU_HANDLER(MENU_ID_PRIVILEGE)

IMPLEMENT_MSG_HANDLER(MSG_ID_KEY, key_handler)
IMPLEMENT_MSG_HANDLER(MSG_ID_INIT, init_callback)
IMPLEMENT_MSG_HANDLER(MSG_ID_DESTROY, destroy_callback)

END_MENU_HANDLER()

