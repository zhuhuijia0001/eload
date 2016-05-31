#include "rtthread.h"

#include <stdint.h>

#include "dev_pwm.h"
#include "control.h"

static rt_device_t s_dev_pwm = RT_NULL;

void control_init(void)
{
	dev_pwm_init();
	
	s_dev_pwm = rt_device_find("pwm");
	RT_ASSERT(s_dev_pwm != RT_NULL);
	
	rt_device_open(s_dev_pwm, RT_DEVICE_OFLAG_WRONLY);
}

void control_set_voltage_duty(int32_t duty)
{
	RT_ASSERT(s_dev_pwm != RT_NULL);
	
	rt_device_control(s_dev_pwm, CMD_PWM_VOLTAGE_DUTY_SET, &duty);
}

void control_set_current_duty(int32_t duty)
{
	RT_ASSERT(s_dev_pwm != RT_NULL);
	
	rt_device_control(s_dev_pwm, CMD_PWM_CURRENT_DUTY_SET, &duty);
}

void control_set_dp_drive_duty(int32_t duty)
{
	RT_ASSERT(s_dev_pwm != RT_NULL);

	rt_device_control(s_dev_pwm, CMD_PWM_DP_DRIVE_SET, &duty);
}

void control_set_dn_drive_duty(int32_t duty)
{
	RT_ASSERT(s_dev_pwm != RT_NULL);

	rt_device_control(s_dev_pwm, CMD_PWM_DN_DRIVE_SET, &duty);
}

int32_t control_get_max_duty(void)
{
	int32_t val;
	
	RT_ASSERT(s_dev_pwm != RT_NULL);
	
	rt_device_control(s_dev_pwm, CMD_PWM_MAX_DUTY_GET, &val);
	
	return val;
}
