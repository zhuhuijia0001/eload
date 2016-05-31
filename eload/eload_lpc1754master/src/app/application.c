/*
 * File      : application.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      the first version
 * 2010-03-04     Magicoe      for LPC1766 version
 * 2010-05-02     Aozima       add led function
 * 2010-05-24     Bernard      add filesystem initialization and move led function to led.c
 * 2012-04-15     Bernard      enable components_init.
 */

#include <rtthread.h>
#include "trace.h"
#include "platform.h"

#ifdef RT_USING_DFS
#include <dfs_fs.h>
#include <dfs_init.h>
#include <dfs_elm.h>

#endif

#ifdef RT_USING_FINSH
#include <shell.h>
#include <finsh.h>
#endif

#include <stdint.h>

#include "type.h"

#include "lcd.h"

#include "beeper.h"

#include "key.h"

#include "eeprom.h"

#include "led.h"

#include "slave_com.h"

#include "menu_op.h"
#include "menu.h"

#include "parameter.h"

#include "global.h"

#include "com_thread.h"
#include "msg_thread.h"

#include "packet.h"

/* determine whether it is allowed to enter factory mode */
static bool can_enter_main_menu(void)
{
	return !(key_is_pressed(KEY_UP)/* && key_is_pressed(KEY_DOWN)*/);
}

static void check_power_on_limit(void)
{
	LIFE_LIMIT life_limit;
	
	load_parameter(STRUCT_OFFSET(PARAMETER, life_limit), &life_limit, sizeof(life_limit));
	if (life_limit.power_on_count >= life_limit.power_on_limit)
	{
		beeper_beep(BEEPER_VOL_HIGH, 200, 100, 5);

		/* loop endless */
		while (RT_TRUE)
		{
			rt_thread_delay(RT_TICK_PER_SECOND);
		}
	}
	else
	{
		life_limit.power_on_count++;
		save_parameter(STRUCT_OFFSET(PARAMETER, life_limit), &life_limit, sizeof(life_limit));
	}
}

static void check_customer_phone_number_power_on_limit(void)
{
	PHONE_NUMBER_SETTING phone_number_setting;
	
	load_parameter(STRUCT_OFFSET(PARAMETER, phone_number_setting), &phone_number_setting, sizeof(phone_number_setting));
	if (phone_number_setting.customer_phone_number_power_on_count < phone_number_setting.customer_phone_number_power_on_limit)
	{
		phone_number_setting.customer_phone_number_power_on_count++;

		save_parameter(STRUCT_OFFSET(PARAMETER, phone_number_setting), &phone_number_setting, sizeof(phone_number_setting));
	}
}

/* operation thread */
static void rt_operation_entry(void *parameter)
{
	const int delay_time = 3000;
	
	switch_to_menu(MENU_ID_WELCOME);

	/* wait for several seconds */
	rt_thread_delay(rt_tick_from_millisecond(delay_time));
	
	beeper_beep(BEEPER_VOL_MEDIUM, 50, 50, 2);
	
	key_init();
	
	if (can_enter_main_menu())
	{
		check_power_on_limit();

		check_customer_phone_number_power_on_limit();
		
		switch_to_menu(MENU_ID_MAIN);
	}
	
	/* key just starts to work */
	rt_thread_delay(rt_tick_from_millisecond(1000));
	
	key_open();
	
	/* start menu session */
	start_menu_session();

	/* start com thread */
	start_com_thread();
	
	while (RT_TRUE)
	{
		MSG_ID id;
		void *msg;
		
		if (wait_for_menu_msg(&id, &msg) == 0)
		{
			process_cur_menu_msg(id, msg);
		}
	}
}

static void operation_start(void)
{
	rt_thread_t tid;
	tid = rt_thread_create("oper", rt_operation_entry, RT_NULL, 
							1024, 19, 10);
	RT_ASSERT(tid != RT_NULL);
	rt_thread_startup(tid);
}

/* thread phase init */
void rt_init_thread_entry(void *parameter)
{
	bool need_save_default_param = false;
	
	/* wait for some time */
	rt_thread_delay(rt_tick_from_millisecond(300));
	
	/* initialize platform */
	platform_init();

	/* Filesystem Initialization */
#ifdef RT_USING_DFS

	/* initialize the device file system */
	dfs_init();

#ifdef RT_USING_DFS_ELMFAT
	/* initialize the elm chan FatFS file system*/
	elm_init();
	
	eeprom_init();
#endif

    /* mount eeprom fat partition 1 as root directory */
    if (dfs_mount("eeprom", "/", "elm", 0, NULL) == 0)
	{
    	rt_kprintf("eeprom mount to /!\n");

    	if (!parameter_file_exist())
    	{
    		need_save_default_param = true;
    	}
	}
    else
	{
    	rt_kprintf("eeprom mount to / failed!\n");
		
		int ret = dfs_mkfs("elm", "eeprom");
		if (ret < 0)
		{
			rt_kprintf("mkfs OK\n");
		}
		else
		{
			rt_kprintf("mkfs failed\n");

			while (true);
		}

		need_save_default_param = true;
	}
	
#endif

	if (need_save_default_param)
	{
		save_default_parameters();
	}
	
#ifdef RT_USING_FINSH
	/* initialize finsh */
	finsh_system_init();
	finsh_set_device(RT_CONSOLE_DEVICE_NAME);
#endif
	
	global_variable_init();
	
	lcd_init();
	
	lcd_set_backlight(100);
	lcd_validate_cmd();
	
	beeper_init();
	
	led_init();

	/* start operation */
	operation_start();
}

int rt_application_init(void)
{
    rt_thread_t tid;

    tid = rt_thread_create("init", rt_init_thread_entry, RT_NULL,
							2048, RT_THREAD_PRIORITY_MAX / 3, 20);
    RT_ASSERT(tid != RT_NULL); 
	rt_thread_startup(tid);
	
	return 0;
}

