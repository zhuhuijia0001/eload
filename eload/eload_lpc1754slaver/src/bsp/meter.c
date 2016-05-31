#include "rtthread.h"
#include <stdint.h>

#include "dev_adc.h"
#include "meter.h"

static rt_device_t s_dev_adc = RT_NULL;

void meter_init(void)
{	
	dev_adc_init();
	
	s_dev_adc = rt_device_find("adc");
	RT_ASSERT(s_dev_adc != RT_NULL);
	
	rt_device_open(s_dev_adc, RT_DEVICE_OFLAG_RDONLY);
}

uint32_t meter_get_voltage_chn_val(void)
{
	uint32_t val;
	
	RT_ASSERT(s_dev_adc != RT_NULL);
	rt_device_control(s_dev_adc, GET_ADC_CHANNEL_VSEN_VAL, &val);
	
	return val;
}

uint32_t meter_get_current_chn_val(void)
{
	uint32_t val;
	
	RT_ASSERT(s_dev_adc != RT_NULL);
	rt_device_control(s_dev_adc, GET_ADC_CHANNEL_ISEN_VAL, &val);
	
	return val;	
}

uint32_t meter_get_ac_chn_val(void)
{
	uint32_t val;
	
	RT_ASSERT(s_dev_adc != RT_NULL);
	rt_device_control(s_dev_adc, GET_ADC_CHANNEL_IAC_SEN_VAL, &val);
	
	return val;		
}

uint32_t meter_get_voltage_posotive_chn_val(void)
{
	uint32_t val;
	
	RT_ASSERT(s_dev_adc != RT_NULL);
	rt_device_control(s_dev_adc, GET_ADC_CHANNEL_VDP_SEN_VAL, &val);
	
	return val;	
}

uint32_t meter_get_voltage_neg_chn_val(void)
{
	uint32_t val;
	
	RT_ASSERT(s_dev_adc != RT_NULL);
	rt_device_control(s_dev_adc, GET_ADC_CHANNEL_VDN_SEN_VAL, &val);
	
	return val;		
}

