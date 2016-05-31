#ifndef _DEV_PWM_H_
#define _DEV_PWM_H_

/* pwm cmd */
#define CMD_PWM_VOLTAGE_DUTY_SET   0x01

#define CMD_PWM_CURRENT_DUTY_SET   0x02

#define CMD_PWM_DP_DRIVE_SET       0x03

#define CMD_PWM_DN_DRIVE_SET       0x04

#define CMD_PWM_MAX_DUTY_GET       0x05

extern void dev_pwm_init(void);

#endif

