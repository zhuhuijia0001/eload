#include "rtthread.h"

#include "dev_led.h"
#include "led.h"

static rt_device_t s_dev_led = RT_NULL;

void led_init(void)
{
	dev_led_init();
	
	s_dev_led = rt_device_find("led");
	RT_ASSERT(s_dev_led != RT_NULL);
	
	rt_device_open(s_dev_led, RT_DEVICE_OFLAG_WRONLY);
}

void pass_led_on(ch_led ch)
{
	RT_ASSERT(s_dev_led != RT_NULL);
	
	rt_device_control(s_dev_led, CMD_LED_PASS_ON, &ch);
}

void pass_led_off(ch_led ch)
{
	RT_ASSERT(s_dev_led != RT_NULL);
	
	rt_device_control(s_dev_led, CMD_LED_PASS_OFF, &ch);	
}

void all_pass_led_on(void)
{
	RT_ASSERT(s_dev_led != RT_NULL);
	
	rt_device_control(s_dev_led, CMD_ALL_PASS_ON, RT_NULL);	
}

void all_pass_led_off(void)
{
	RT_ASSERT(s_dev_led != RT_NULL);
	
	rt_device_control(s_dev_led, CMD_ALL_PASS_OFF, RT_NULL);	
}

void fail_led_on(ch_led ch)
{
	RT_ASSERT(s_dev_led != RT_NULL);
	
	rt_device_control(s_dev_led, CMD_LED_FAIL_ON, &ch);	
}

void fail_led_off(ch_led ch)
{
	RT_ASSERT(s_dev_led != RT_NULL);
	
	rt_device_control(s_dev_led, CMD_LED_FAIL_OFF, &ch);	
}

void all_fail_led_on(void)
{
	RT_ASSERT(s_dev_led != RT_NULL);
	
	rt_device_control(s_dev_led, CMD_ALL_FAIL_ON, RT_NULL);	
}

void all_fail_led_off(void)
{
	RT_ASSERT(s_dev_led != RT_NULL);
	
	rt_device_control(s_dev_led, CMD_ALL_FAIL_OFF, RT_NULL);	
}
