#include <stdint.h>
#include "type.h"
#include "key_define.h"

#include "menu_op.h"
#include "menu.h"

#include "lcd.h"
#include "draw.h"

#include "packet.h"

#include "beeper.h"

#include "com_thread.h"

#include "trace.h"

/* item */
typedef enum
{
	DEVICE_ADJUST_CHANNEL = 0,
	
	DEVICE_ADJUST_ACTUAL_VOLTAGE,
	
	DEVICE_ADJUST_ACTUAL_CURRENT,
	
	DEVICE_ADJUST_NONE,
	
	DEVICE_ADJUST_COUNT = DEVICE_ADJUST_NONE
} device_adjust_item;

/* focus item */
static device_adjust_item s_focus_item = DEVICE_ADJUST_NONE;

/* edit item */
static device_adjust_item s_edit_item = DEVICE_ADJUST_NONE;

/* adjust setting */
static ADJUST_SETTING s_adjust_setting;

static slave_com_port s_cur_channel = SLAVE_PORT_0;

/* adjust current val */
static const uint32_t ADJUST_CURRENT_VAL = 2000ul;

/* max voltage */
static const uint32_t MAX_VOLTAGE = 30000ul;

static const uint32_t BIG_VOLTAGE_STEP = 1000ul;

static const uint32_t SMALL_VOLTAGE_STEP = 10ul;

/* max current */
static const uint32_t MAX_CURRENT = 6000ul;

static const uint32_t BIG_CURRENT_STEP = 1000ul;

static const uint32_t SMALL_CURRENT_STEP = 10ul;

static uint32_t s_cur_current;
static uint32_t s_cur_voltage;

/* unfocus fun */
static void unfocus_channel(void)
{
	draw_normal_device_adjust_channel(s_cur_channel + 1);
}

static void unfocus_actual_voltage(void)
{
	draw_normal_device_adjust_actual_voltage(s_adjust_setting.actual_voltage);
}

static void unfocus_actual_current(void)
{
	draw_normal_device_adjust_actual_current(s_adjust_setting.actual_current);
}

static void (*const s_unfocus_fun_arr[])(void) = 
{
	[DEVICE_ADJUST_CHANNEL]        = unfocus_channel,
	
	[DEVICE_ADJUST_ACTUAL_VOLTAGE] = unfocus_actual_voltage,
	
	[DEVICE_ADJUST_ACTUAL_CURRENT] = unfocus_actual_current
};

/* focus fun */
static void focus_channel(void)
{
	draw_focus_device_adjust_channel(s_cur_channel + 1);
}

static void focus_actual_voltage(void)
{
	draw_focus_device_adjust_actual_voltage(s_adjust_setting.actual_voltage);
}

static void focus_actual_current(void)
{
	draw_focus_device_adjust_actual_current(s_adjust_setting.actual_current);
}

static void (*const s_focus_fun_arr[])(void) = 
{
	[DEVICE_ADJUST_CHANNEL]        = focus_channel,
	
	[DEVICE_ADJUST_ACTUAL_VOLTAGE] = focus_actual_voltage,
	
	[DEVICE_ADJUST_ACTUAL_CURRENT] = focus_actual_current
};

/* enter edit fun */
static void enter_edit_channel(void)
{
	draw_edit_device_adjust_channel(s_cur_channel + 1);
	
	s_edit_item = DEVICE_ADJUST_CHANNEL;
}

static void enter_edit_actual_voltage(void)
{
	s_cur_voltage = s_adjust_setting.actual_voltage;
	draw_edit_device_adjust_actual_voltage(s_cur_voltage);
	
	s_edit_item = DEVICE_ADJUST_ACTUAL_VOLTAGE;
}

static void enter_edit_actual_current(void)
{
	TEST_CMD test_cmd;
	
	s_cur_current = s_adjust_setting.actual_current;
	draw_edit_device_adjust_actual_current(s_cur_current);
	
	s_edit_item = DEVICE_ADJUST_ACTUAL_CURRENT;		
					
	/* notify to let the current to be specified value */
	test_cmd.channel   = (slave_com_port)s_cur_channel;
	test_cmd.test_type = TEST_TYPE_CC_MODE;
	test_cmd.test_config.cc_mode_config.current_val = ADJUST_CURRENT_VAL;
	test_cmd_notify(&test_cmd);

	TRACE("start adjusting current\n");
}

static void (*const s_enter_edit_fun_arr[])(void) = 
{
	[DEVICE_ADJUST_CHANNEL]        = enter_edit_channel,
	
	[DEVICE_ADJUST_ACTUAL_VOLTAGE] = enter_edit_actual_voltage,
	
	[DEVICE_ADJUST_ACTUAL_CURRENT] = enter_edit_actual_current
};

/* confirm edit fun */
static void confirm_edit_channel(void)
{
	draw_focus_device_adjust_channel(s_cur_channel + 1);
}

static void confirm_edit_actual_voltage(void)
{
	s_adjust_setting.actual_voltage = s_cur_voltage;
	draw_focus_device_adjust_actual_voltage(s_adjust_setting.actual_voltage);

	save_parameter(STRUCT_OFFSET(PARAMETER, adjust_setting[s_cur_channel]), &s_adjust_setting, sizeof(s_adjust_setting));
}

static void confirm_edit_actual_current(void)
{
	TEST_CMD test_cmd;
		
	s_adjust_setting.actual_current = s_cur_current;
	draw_focus_device_adjust_actual_current(s_adjust_setting.actual_current);

	save_parameter(STRUCT_OFFSET(PARAMETER, adjust_setting[s_cur_channel]), &s_adjust_setting, sizeof(s_adjust_setting));

	/* notify to stop test */
	test_cmd.channel   = (slave_com_port)s_cur_channel;
	test_cmd.test_type = TEST_TYPE_NONE;
	test_cmd_notify(&test_cmd);
	
	TRACE("stop adjusting current\n");
}

static void (*const s_confirm_edit_fun_arr[])(void) = 
{
	[DEVICE_ADJUST_CHANNEL]        = confirm_edit_channel,
	
	[DEVICE_ADJUST_ACTUAL_VOLTAGE] = confirm_edit_actual_voltage,
	
	[DEVICE_ADJUST_ACTUAL_CURRENT] = confirm_edit_actual_current
};

/* edit fun */
static void edit_channel(uint8_t key)
{
	if (key == KEY_UP || key == KEY_RIGHT)
	{
		s_cur_channel++;
		s_cur_channel %= SLAVE_PORT_COUNT;

		load_parameter(STRUCT_OFFSET(PARAMETER, adjust_setting[s_cur_channel]), &s_adjust_setting, sizeof(s_adjust_setting));
	
		draw_edit_device_adjust_channel(s_cur_channel + 1);
	
		draw_normal_device_adjust_actual_voltage(s_adjust_setting.actual_voltage);
	
		draw_normal_device_adjust_actual_current(s_adjust_setting.actual_current);		
	}
	else if (key == KEY_DOWN || key == KEY_LEFT)
	{
		s_cur_channel += SLAVE_PORT_COUNT - 1;
		s_cur_channel %= SLAVE_PORT_COUNT;
		
		load_parameter(STRUCT_OFFSET(PARAMETER, adjust_setting[s_cur_channel]), &s_adjust_setting, sizeof(s_adjust_setting));
	
		draw_edit_device_adjust_channel(s_cur_channel + 1);
	
		draw_normal_device_adjust_actual_voltage(s_adjust_setting.actual_voltage);
	
		draw_normal_device_adjust_actual_current(s_adjust_setting.actual_current);	
	}
}

static void edit_actual_voltage(uint8_t key)
{
	if (key == KEY_UP)
	{
		s_cur_voltage += BIG_VOLTAGE_STEP;
		if (s_cur_voltage > MAX_VOLTAGE)
		{
			s_cur_voltage = MAX_VOLTAGE;
		}
		draw_edit_device_adjust_actual_voltage(s_cur_voltage);
	}
	else if (key == KEY_DOWN)
	{
		if (s_cur_voltage > BIG_VOLTAGE_STEP)
		{
			s_cur_voltage -= BIG_VOLTAGE_STEP;
		}
		else
		{
			s_cur_voltage = SMALL_VOLTAGE_STEP;
		}
		draw_edit_device_adjust_actual_voltage(s_cur_voltage);
	}
	else if (key == KEY_RIGHT)
	{
		s_cur_voltage += SMALL_VOLTAGE_STEP;
		if (s_cur_voltage > MAX_VOLTAGE)
		{
			s_cur_voltage = MAX_VOLTAGE;
		}
		draw_edit_device_adjust_actual_voltage(s_cur_voltage);
	}
	else if (key == KEY_LEFT)
	{
		if (s_cur_voltage > SMALL_VOLTAGE_STEP)
		{
			s_cur_voltage -= SMALL_VOLTAGE_STEP;
		}
		draw_edit_device_adjust_actual_voltage(s_cur_voltage);
	}
}

static void edit_actual_current(uint8_t key)
{
	if (key == KEY_UP)
	{
		s_cur_current += BIG_CURRENT_STEP;
		if (s_cur_current > MAX_CURRENT)
		{
			s_cur_current = MAX_CURRENT;
		}
		draw_edit_device_adjust_actual_current(s_cur_current);
	}
	else if (key == KEY_DOWN)
	{
		if (s_cur_current > BIG_CURRENT_STEP)
		{
			s_cur_current -= BIG_CURRENT_STEP;
		}
		else
		{
			s_cur_current = SMALL_CURRENT_STEP;
		}
		draw_edit_device_adjust_actual_current(s_cur_current);
	}
	else if (key == KEY_RIGHT)
	{
		s_cur_current += SMALL_CURRENT_STEP;
		if (s_cur_current > MAX_CURRENT)
		{
			s_cur_current = MAX_CURRENT;
		}
		draw_edit_device_adjust_actual_current(s_cur_current);
	}
	else if (key == KEY_LEFT)
	{
		if (s_cur_current > SMALL_CURRENT_STEP)
		{
			s_cur_current -= SMALL_CURRENT_STEP;
		}
		draw_edit_device_adjust_actual_current(s_cur_current);
	}
}

static void (*const s_edit_fun_arr[])(uint8_t key) = 
{
	[DEVICE_ADJUST_CHANNEL]        = edit_channel,
	
	[DEVICE_ADJUST_ACTUAL_VOLTAGE] = edit_actual_voltage,
	
	[DEVICE_ADJUST_ACTUAL_CURRENT] = edit_actual_current
};

static void edit_channel_released(uint8_t key)
{
}

static void edit_actual_voltage_released(uint8_t key)
{
	if (key == KEY_LEFT || key == KEY_RIGHT 
		|| key == KEY_UP || key == KEY_DOWN)
	{
		g_channel_adjust_value[s_cur_channel].measure_voltage = get_cur_voltage(s_cur_channel);
		g_channel_adjust_value[s_cur_channel].actual_voltage  = s_cur_voltage;	
	}
}

static void edit_actual_current_released(uint8_t key)
{
	if (key == KEY_LEFT || key == KEY_RIGHT 
		|| key == KEY_UP || key == KEY_DOWN)
	{
		g_channel_adjust_value[s_cur_channel].measure_current = get_cur_current(s_cur_channel);
		g_channel_adjust_value[s_cur_channel].actual_current  = s_cur_current;
	}
}

static void (*const s_edit_released_fun_arr[])(uint8_t key) = 
{
	[DEVICE_ADJUST_CHANNEL]        = edit_channel_released,
	
	[DEVICE_ADJUST_ACTUAL_VOLTAGE] = edit_actual_voltage_released,
	
	[DEVICE_ADJUST_ACTUAL_CURRENT] = edit_actual_current_released
};

static void key_handler(void *msg)
{
	key_t key_msg = (key_t)(uint32_t)msg;
	uint8_t key = KEY_VALUE(key_msg);

	if (KEY_TYPE(key_msg) != MASK_KEY_PRESS && (key == KEY_OK || key == KEY_CANCEL))
	{
		return;
	}
	
	if (KEY_TYPE(key_msg) != MASK_KEY_RELEASE)
	{
		beeper_beep(BEEPER_VOL_LOW, 50, 50, 1);
		
		if (key == KEY_LEFT || key == KEY_UP)
		{
			if (s_edit_item == DEVICE_ADJUST_NONE)
			{
				s_unfocus_fun_arr[s_focus_item]();
				
				s_focus_item += DEVICE_ADJUST_COUNT - 1;
				s_focus_item %= DEVICE_ADJUST_COUNT;
				
				s_focus_fun_arr[s_focus_item]();
			}
			else
			{
				s_edit_fun_arr[s_edit_item](key);
			}
			
			lcd_validate_cmd();
		}
		else if (key == KEY_RIGHT || key == KEY_DOWN)
		{
			if (s_edit_item == DEVICE_ADJUST_NONE)
			{
				s_unfocus_fun_arr[s_focus_item]();
				
				s_focus_item++;
				s_focus_item %= DEVICE_ADJUST_COUNT;
				
				s_focus_fun_arr[s_focus_item]();
			}
			else
			{
				s_edit_fun_arr[s_edit_item](key);
			}

			lcd_validate_cmd();
		}
		else if (key == KEY_OK)
		{
			if (s_edit_item == DEVICE_ADJUST_NONE)
			{
				s_enter_edit_fun_arr[s_focus_item]();
			}
			else
			{
				TEST_CMD test_cmd;
				
				s_confirm_edit_fun_arr[s_focus_item]();
				
				s_edit_item = DEVICE_ADJUST_NONE;
						
				/* notify adjust parameter */
				test_cmd.channel   = s_cur_channel;
				test_cmd.test_type = TEST_TYPE_SET_ADJUST_VALUE;

				test_cmd.test_config.adjust_value_config.measure_voltage = g_channel_adjust_value[s_cur_channel].measure_voltage;
				test_cmd.test_config.adjust_value_config.actual_voltage  = g_channel_adjust_value[s_cur_channel].actual_voltage;
				test_cmd.test_config.adjust_value_config.measure_current = g_channel_adjust_value[s_cur_channel].measure_current;
				test_cmd.test_config.adjust_value_config.actual_current  = g_channel_adjust_value[s_cur_channel].actual_current;
				
				test_cmd_notify(&test_cmd);
			}
			
			lcd_validate_cmd();
		}
		else if (key == KEY_CANCEL)
		{
			if (s_edit_item == DEVICE_ADJUST_NONE)
			{
				switch_to_menu(MENU_ID_FACTORY_MODE);
			}
			else
			{
				s_focus_fun_arr[s_focus_item]();
				
				lcd_validate_cmd();
				
				s_edit_item = DEVICE_ADJUST_NONE;
			}
		}
	}
	else
	{
		if (s_edit_item != DEVICE_ADJUST_NONE)
		{
			s_edit_released_fun_arr[s_edit_item](key);
		}
	}
}

static void refresh_handler(void *msg)
{
	TEST_CONTENT *test_content = (TEST_CONTENT *)msg;

	draw_device_adjust_measure_voltage(test_content->voltage);

	draw_device_adjusted_voltage(measure_to_actual_voltage((int)s_cur_channel, test_content->voltage));

	draw_device_adjust_measure_current(test_content->current);
	
	draw_device_adjusted_current(measure_to_actual_current((int)s_cur_channel, test_content->current));
	
	lcd_validate_cmd();
}

static void init_callback(void *msg)
{
	load_parameter(STRUCT_OFFSET(PARAMETER, adjust_setting[s_cur_channel]), &s_adjust_setting, sizeof(s_adjust_setting));
	
	draw_device_adjust_menu();
	
	draw_focus_device_adjust_channel(s_cur_channel + 1);
	
	draw_normal_device_adjust_actual_voltage(s_adjust_setting.actual_voltage);
	
	draw_normal_device_adjust_actual_current(s_adjust_setting.actual_current);
	
	s_focus_item = DEVICE_ADJUST_CHANNEL;
	
	s_edit_item = DEVICE_ADJUST_NONE;
	
	lcd_validate_cmd();
}

static void destroy_callback(void *msg)
{
	lcd_clear(SCREEN_BACK_COLOR);		
}

BEGIN_MENU_HANDLER(MENU_ID_ADJUST)

IMPLEMENT_MSG_HANDLER(MSG_ID_KEY, key_handler)
IMPLEMENT_MSG_HANDLER(MSG_ID_REFRESH, refresh_handler)
IMPLEMENT_MSG_HANDLER(MSG_ID_INIT, init_callback)
IMPLEMENT_MSG_HANDLER(MSG_ID_DESTROY, destroy_callback)

END_MENU_HANDLER()

