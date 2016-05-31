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
	CR_FOCUS_MODE = 0,
	
	CR_EDIT_MODE = 1
} cr_mode;

static cr_mode s_cr_mode = CR_FOCUS_MODE;

/* max resist */
static const uint32_t MAX_RESIST = 999900ul;

static const uint32_t BIG_RESIST_STEP = 1000ul;

static const uint32_t SMALL_RESIST_STEP = 100ul;

static uint32_t s_cr_mode_resist_set;

static uint32_t s_cur_resist;

static void key_handler(void *msg)
{
	key_t key_msg = (key_t)(uint32_t)msg;
	uint8_t key = KEY_VALUE(key_msg);
	
	if (KEY_TYPE(key_msg) != MASK_KEY_RELEASE)
	{
		beeper_beep(BEEPER_VOL_LOW, 50, 50, 1);
		
		if (key == KEY_UP)
		{
			if (s_cr_mode == CR_EDIT_MODE)
			{
				s_cur_resist += BIG_RESIST_STEP;
				if (s_cur_resist > MAX_RESIST)
				{
					s_cur_resist = MAX_RESIST;
				}	
				draw_edit_resist_val(s_cur_resist);
			
				lcd_validate_cmd();
			}
		}
		else if (key == KEY_DOWN)
		{
			if (s_cr_mode == CR_EDIT_MODE)
			{
				if (s_cur_resist > BIG_RESIST_STEP)
				{
					s_cur_resist -= BIG_RESIST_STEP;
				}
				else
				{
					s_cur_resist = SMALL_RESIST_STEP;
				}
				draw_edit_resist_val(s_cur_resist);
			
				lcd_validate_cmd();
			}
		}
		else if (key == KEY_LEFT)
		{
			if (s_cr_mode == CR_EDIT_MODE)
			{
				if (s_cur_resist > SMALL_RESIST_STEP)
				{
					s_cur_resist -= SMALL_RESIST_STEP;
				}
				draw_edit_resist_val(s_cur_resist);
			
				lcd_validate_cmd();
			}
		}
		else if (key == KEY_RIGHT)
		{
			if (s_cr_mode == CR_EDIT_MODE)
			{	
				s_cur_resist += SMALL_RESIST_STEP;
				if (s_cur_resist > MAX_RESIST)
				{
					s_cur_resist = MAX_RESIST;
				}
				draw_edit_resist_val(s_cur_resist);
			
				lcd_validate_cmd();
			}
		}
		else if (key == KEY_OK)
		{
			if (KEY_TYPE(key_msg) == MASK_KEY_PRESS)
			{
				TEST_CMD test_cmd;
				
				if (s_cr_mode == CR_FOCUS_MODE)
				{	
					s_cur_resist = s_cr_mode_resist_set;
					draw_edit_resist_val(s_cur_resist);
				
					lcd_validate_cmd();
				
					s_cr_mode = CR_EDIT_MODE;		
					
					/* notify to start test */
					test_cmd.channel   = SLAVE_PORT_0;
					test_cmd.test_type = TEST_TYPE_CR_MODE;
					test_cmd.test_config.cr_mode_config.resist_val = s_cur_resist;
					test_cmd_notify(&test_cmd);

					TRACE("start testing\n");

					all_pass_led_on();
				}
				else
				{
					s_cr_mode_resist_set = s_cur_resist;
					draw_focus_resist_val(s_cr_mode_resist_set);
				
					lcd_validate_cmd();

					save_parameter(STRUCT_OFFSET(PARAMETER, cr_mode_resist_set), &s_cr_mode_resist_set, sizeof(s_cr_mode_resist_set));
					
					s_cr_mode = CR_FOCUS_MODE;
					
					/* notify to stop test */
					test_cmd.channel   = SLAVE_PORT_0;
					test_cmd.test_type = TEST_TYPE_NONE;
					test_cmd_notify(&test_cmd);		

					TRACE("stop testing\n");

					all_pass_led_off();
				}
			}
		}
		else if (key == KEY_CANCEL)
		{
			if (s_cr_mode == CR_FOCUS_MODE)
			{
				switch_to_menu(MENU_ID_MAIN);
			}
			else
			{
				TEST_CMD test_cmd;
				
				draw_focus_resist_val(s_cr_mode_resist_set);
				
				lcd_validate_cmd();
				
				s_cr_mode = CR_FOCUS_MODE;

				/* notify to stop test */
				test_cmd.channel   = SLAVE_PORT_0;
				test_cmd.test_type = TEST_TYPE_NONE;
				test_cmd_notify(&test_cmd);	

				TRACE("stop testing\n");

				all_pass_led_off();	
			}
		}
	}
	else
	{
		/* release */
		if (key == KEY_UP || key == KEY_DOWN
			|| key == KEY_LEFT || key == KEY_RIGHT)
		{
			if (s_cr_mode == CR_EDIT_MODE)
			{
				TEST_CMD test_cmd;
					
				/* notify */
				test_cmd.channel   = SLAVE_PORT_0;
				test_cmd.test_type = TEST_TYPE_CR_MODE;
				test_cmd.test_config.cr_mode_config.resist_val = s_cur_resist;
				test_cmd_notify(&test_cmd);

				TRACE("start testing\n");
			}
		}
	}
}

static void refresh_handler(void *msg)
{
	TEST_CONTENT *test_content = (TEST_CONTENT *)msg;
	
	draw_ac_val(test_content->ac_current);
		
	draw_voltage_val(measure_to_actual_voltage((int)test_content->channel, test_content->voltage));
		
	draw_current_val(measure_to_actual_current((int)test_content->channel, test_content->current));
	
	lcd_validate_cmd();	
}

static void init_callback(void *msg)
{
	load_parameter(STRUCT_OFFSET(PARAMETER, cr_mode_resist_set), &s_cr_mode_resist_set, sizeof(s_cr_mode_resist_set));
	
	draw_cr_mode_menu();

	s_cur_resist = s_cr_mode_resist_set;
	draw_focus_resist_val(s_cur_resist);
	
	draw_ac_val(0);
	
	draw_voltage_val(0);
	
	draw_current_val(0);
	
	lcd_validate_cmd();
	
	s_cr_mode = CR_FOCUS_MODE;
}

static void destroy_callback(void *msg)
{
	lcd_clear(SCREEN_BACK_COLOR);
}

BEGIN_MENU_HANDLER(MENU_ID_CR_MODE)

IMPLEMENT_MSG_HANDLER(MSG_ID_KEY, key_handler)
IMPLEMENT_MSG_HANDLER(MSG_ID_REFRESH, refresh_handler)
IMPLEMENT_MSG_HANDLER(MSG_ID_INIT, init_callback)
IMPLEMENT_MSG_HANDLER(MSG_ID_DESTROY, destroy_callback)

END_MENU_HANDLER()

