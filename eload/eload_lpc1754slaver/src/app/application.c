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

#ifdef RT_USING_FINSH
#include <shell.h>
#include <finsh.h>
#endif

#include <stdint.h>

#include "type.h"

#include "meter.h"

#include "relay.h"

#include "switch.h"

#include "control.h"

#include "eeprom.h"

#include "parameter.h"
#include "app_cfg.h"
#include "global.h"

#include "work_thread.h"
#include "com_thread.h"

#if 0
static void quick_charge_test(void)
{
	//first give d+ 0.6V
	int32_t max_duty = control_get_max_duty();

	/* 9V */
	int32_t duty = (int32_t)(0.6 / 3.3 * max_duty);
	control_set_dp_drive_duty(duty);
	control_set_dn_drive_duty(0);

	//delay 1.5s
	rt_thread_delay(rt_tick_from_millisecond(2000));

	//give d+ 0.6V, d- 0.6V
	control_set_dp_drive_duty(max_duty);
	control_set_dn_drive_duty(duty);
	
	rt_thread_delay(rt_tick_from_millisecond(3000));

	/* 12 V */
	//delay 1.5s
	rt_thread_delay(rt_tick_from_millisecond(2000));

	//give d+ 0.6V, d- 0.6V
	control_set_dp_drive_duty(duty);
	control_set_dn_drive_duty(duty);

	rt_thread_delay(rt_tick_from_millisecond(3000));

	/* 5 V */
	//give d+ 0V, d- 0V
	control_set_dp_drive_duty(0);
	control_set_dn_drive_duty(0);

	rt_thread_delay(rt_tick_from_millisecond(1000));
}
#else
static void quick_charge_test(void)
{
#if 0
	int32_t max_duty = control_get_max_duty();

	/* 9V */
	int32_t duty = (int32_t)(0.6 / 3.3 * max_duty);
	control_set_dp_drive_duty(duty);
	control_set_dn_drive_duty(0);

	//delay 1.5s
	rt_thread_delay(rt_tick_from_millisecond(1500));

	//give d+ 0.6V, d- 0.6V
	control_set_dp_drive_duty(max_duty);
	control_set_dn_drive_duty(duty);

	rt_thread_delay(rt_tick_from_millisecond(100));
#endif
}

#endif

#if 0

static uint32_t s_max_duty = 0;

static void try_set_current(uint32_t mA)
{
	s_max_duty = control_get_max_duty();
	
	RT_ASSERT(s_max_duty > 0);
	
	uint32_t duty = mA * s_max_duty * 50ul * 10ul / 1000ul / 3300ul;
			
	control_set_current_duty(duty);
}

static void mtk_increase_step(void)
{
	try_set_current(0);
	rt_thread_delay(rt_tick_from_millisecond(100));
	
	//start
	try_set_current(300);
	rt_thread_delay(rt_tick_from_millisecond(100));

	try_set_current(0);
	rt_thread_delay(rt_tick_from_millisecond(100));

	try_set_current(300);
	rt_thread_delay(rt_tick_from_millisecond(100));

	try_set_current(0);
	rt_thread_delay(rt_tick_from_millisecond(100));

	try_set_current(300);
	rt_thread_delay(rt_tick_from_millisecond(300));

	try_set_current(0);
	rt_thread_delay(rt_tick_from_millisecond(100));

	try_set_current(300);
	rt_thread_delay(rt_tick_from_millisecond(300));

	try_set_current(0);
	rt_thread_delay(rt_tick_from_millisecond(100));

	try_set_current(300);
	rt_thread_delay(rt_tick_from_millisecond(300));

	try_set_current(0);
	rt_thread_delay(rt_tick_from_millisecond(100));

	try_set_current(300);
	rt_thread_delay(rt_tick_from_millisecond(500));

	try_set_current(0);
	rt_thread_delay(rt_tick_from_millisecond(100));

	try_set_current(300);
	rt_thread_delay(rt_tick_from_millisecond(100));
}

static void mtk_decrease_step(void)
{
	try_set_current(0);
	rt_thread_delay(rt_tick_from_millisecond(100));
	
	//start
	try_set_current(300);
	rt_thread_delay(rt_tick_from_millisecond(300));

	try_set_current(0);
	rt_thread_delay(rt_tick_from_millisecond(100));

	try_set_current(300);
	rt_thread_delay(rt_tick_from_millisecond(300));

	try_set_current(0);
	rt_thread_delay(rt_tick_from_millisecond(100));

	try_set_current(300);
	rt_thread_delay(rt_tick_from_millisecond(300));

	try_set_current(0);
	rt_thread_delay(rt_tick_from_millisecond(100));

	try_set_current(300);
	rt_thread_delay(rt_tick_from_millisecond(100));

	try_set_current(0);
	rt_thread_delay(rt_tick_from_millisecond(100));

	try_set_current(300);
	rt_thread_delay(rt_tick_from_millisecond(100));

	try_set_current(0);
	rt_thread_delay(rt_tick_from_millisecond(100));

	try_set_current(300);
	rt_thread_delay(rt_tick_from_millisecond(500));

	try_set_current(0);
	rt_thread_delay(rt_tick_from_millisecond(100));

	try_set_current(300);
	rt_thread_delay(rt_tick_from_millisecond(100));
}

static void mtk_default(void)
{
	try_set_current(0);
	rt_thread_delay(rt_tick_from_millisecond(300));
}

static void mtk_test(void)
{
	switch_disable();
	switch_to_channel(CC_CTRL_CHANNEL);
					
	control_set_voltage_duty(0);

	relay_load_on();
	relay_empty_on();

	rt_thread_delay(rt_tick_from_millisecond(500));

	switch_enable();

	mtk_increase_step();
	mtk_increase_step();
	mtk_increase_step();
	while (RT_TRUE)
	{
		rt_thread_delay(rt_tick_from_millisecond(2000));

		mtk_default();
	}
}
#else
static void mtk_test(void)
{

}
#endif

/* thread phase init */
void rt_init_thread_entry(void *parameter)
{
	/* initialize platform */
	platform_init();

#ifdef RT_USING_FINSH
	/* initialize finsh */
	finsh_system_init();
	finsh_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

	control_init();
	
	eeprom_init();

	/* load parameters */
	if (!load_parameter())
	{
		save_default_parameter();
	}
	
	relay_init();
	
	switch_init();
	switch_to_channel(EMPTY_CTRL_CHANNEL);

	meter_init();

	quick_charge_test();

	mtk_test();
	
	global_variable_init();
	
	start_com_thread();
	
	start_work_thread();
}

int rt_application_init(void)
{
    rt_thread_t tid;

    tid = rt_thread_create("init", rt_init_thread_entry, RT_NULL,
							2048, INIT_THREAD_PRIORITY, 20);

    RT_ASSERT(tid != RT_NULL);
	rt_thread_startup(tid);
	
	return 0;
}

