#ifndef _CONTROL_H_
#define _CONTROL_H_

extern void control_init(void);

extern void control_set_voltage_duty(int32_t duty);

extern void control_set_current_duty(int32_t duty);

extern void control_set_dp_drive_duty(int32_t duty);

extern void control_set_dn_drive_duty(int32_t duty);

extern int32_t control_get_max_duty(void);

#endif
