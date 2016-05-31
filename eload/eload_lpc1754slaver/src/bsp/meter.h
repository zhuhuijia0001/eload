#ifndef _METER_H_
#define _METER_H_

extern void meter_init(void);

extern uint32_t meter_get_voltage_chn_val(void);

extern uint32_t meter_get_current_chn_val(void);

extern uint32_t meter_get_ac_chn_val(void);

extern uint32_t meter_get_voltage_posotive_chn_val(void);

extern uint32_t meter_get_voltage_neg_chn_val(void);

#endif
