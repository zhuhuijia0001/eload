#include <rthw.h>
#include <rtthread.h>
#include "lpc17xx_pinsel.h"

#include "lpc17xx_adc.h"
#include "dev_adc.h"

/* channel define */
#define AD_CHANNEL_VSEN      ADC_CHANNEL_7
#define AD_CHANNEL_VSEN_INT  ADC_ADINTEN7

#define AD_CHANNEL_ISEN      ADC_CHANNEL_6
#define AD_CHANNEL_ISEN_INT  ADC_ADINTEN6

#define AD_CHANNEL_IAC_SEN   ADC_CHANNEL_3
#define AD_CHANNEL_IAC_SEN_INT   ADC_ADINTEN3

#define AD_CHANNEL_VDP_SEN   ADC_CHANNEL_5
#define AD_CHANNEL_VDP_SEN_INT  ADC_ADINTEN5

#define AD_CHANNEL_VDN_SEN   ADC_CHANNEL_2
#define AD_CHANNEL_VDN_SEN_INT  ADC_ADINTEN2

struct dev_adc
{
	struct rt_device parent;
};

static struct dev_adc s_dev_adc;

static void adc_init(void)
{
	PINSEL_CFG_Type PinSelCfgType;
	
	/* pin config */
	/* ad0_7, vsen */
	PinSelCfgType.Portnum = PINSEL_PORT_0;
	PinSelCfgType.Pinnum  = PINSEL_PIN_2;
	PinSelCfgType.Funcnum = PINSEL_FUNC_2;
	PinSelCfgType.Pinmode = PINSEL_PINMODE_PULLUP;
	PinSelCfgType.OpenDrain = PINSEL_PINMODE_NORMAL;
	PINSEL_ConfigPin(&PinSelCfgType);
	
	/* ad0_7, isen */
	PinSelCfgType.Portnum = PINSEL_PORT_0;
	PinSelCfgType.Pinnum  = PINSEL_PIN_3;
	PinSelCfgType.Funcnum = PINSEL_FUNC_2;
	PinSelCfgType.Pinmode = PINSEL_PINMODE_PULLUP;
	PinSelCfgType.OpenDrain = PINSEL_PINMODE_NORMAL;
	PINSEL_ConfigPin(&PinSelCfgType);

	/* ad0_3, iac_sen */
	PinSelCfgType.Portnum = PINSEL_PORT_0;
	PinSelCfgType.Pinnum  = PINSEL_PIN_26;
	PinSelCfgType.Funcnum = PINSEL_FUNC_1;
	PinSelCfgType.Pinmode = PINSEL_PINMODE_PULLUP;
	PinSelCfgType.OpenDrain = PINSEL_PINMODE_NORMAL;
	PINSEL_ConfigPin(&PinSelCfgType);

	/* ad0_5, vsen d+ */
	PinSelCfgType.Portnum = PINSEL_PORT_1;
	PinSelCfgType.Pinnum  = PINSEL_PIN_31;
	PinSelCfgType.Funcnum = PINSEL_FUNC_2;
	PinSelCfgType.Pinmode = PINSEL_PINMODE_PULLUP;
	PinSelCfgType.OpenDrain = PINSEL_PINMODE_NORMAL;
	PINSEL_ConfigPin(&PinSelCfgType);
	
	/* ad0_2, vsen d- */
	PinSelCfgType.Portnum = PINSEL_PORT_0;
	PinSelCfgType.Pinnum  = PINSEL_PIN_25;
	PinSelCfgType.Funcnum = PINSEL_FUNC_1;
	PinSelCfgType.Pinmode = PINSEL_PINMODE_PULLUP;
	PinSelCfgType.OpenDrain = PINSEL_PINMODE_NORMAL;
	PINSEL_ConfigPin(&PinSelCfgType);
	
	ADC_Init(LPC_ADC, 200000);
	
	ADC_IntConfig(LPC_ADC, AD_CHANNEL_VSEN_INT, DISABLE);
	ADC_ChannelCmd(LPC_ADC, AD_CHANNEL_VSEN, ENABLE);

	ADC_IntConfig(LPC_ADC, AD_CHANNEL_ISEN_INT, DISABLE);
	ADC_ChannelCmd(LPC_ADC, AD_CHANNEL_ISEN, ENABLE);

	ADC_IntConfig(LPC_ADC, AD_CHANNEL_IAC_SEN_INT, DISABLE);
	ADC_ChannelCmd(LPC_ADC, AD_CHANNEL_IAC_SEN, ENABLE);

	ADC_IntConfig(LPC_ADC, AD_CHANNEL_VDP_SEN_INT, DISABLE);
	ADC_ChannelCmd(LPC_ADC, AD_CHANNEL_VDP_SEN, ENABLE);
	
	ADC_IntConfig(LPC_ADC, AD_CHANNEL_VDN_SEN_INT, DISABLE);
	ADC_ChannelCmd(LPC_ADC, AD_CHANNEL_VDN_SEN, ENABLE);
	
	ADC_BurstCmd(LPC_ADC, ENABLE);
}

static rt_err_t rt_dev_adc_init (rt_device_t dev)
{
	adc_init();
	
	return RT_EOK;
}

static rt_err_t rt_dev_adc_open(rt_device_t dev, rt_uint16_t oflag)
{
	return RT_EOK;
}

static rt_err_t rt_dev_adc_close(rt_device_t dev)
{
	return RT_EOK;
}

static rt_size_t rt_dev_adc_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{	
	return 0;
}

static rt_size_t rt_dev_adc_write(rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{
	return 0;
}

static rt_err_t rt_dev_adc_control(rt_device_t dev, rt_uint8_t cmd, void *args)
{	
	switch (cmd)
	{
	case ENABLE_ADC_CHANNEL_VSEN:
		ADC_ChannelCmd(LPC_ADC, AD_CHANNEL_VSEN, ENABLE);
		
		break;
		
	case ENABLE_ADC_CHANNEL_ISEN:
		ADC_ChannelCmd(LPC_ADC, AD_CHANNEL_ISEN, ENABLE);
	
		break;
	
	case ENABLE_ADC_CHANNEL_IAC_SEN:
		ADC_ChannelCmd(LPC_ADC, AD_CHANNEL_IAC_SEN, ENABLE);
	
		break;

	case ENABLE_ADC_CHANNEL_VDP_SEN:
		ADC_ChannelCmd(LPC_ADC, AD_CHANNEL_VDP_SEN, ENABLE);
	
		break;
		
	case ENABLE_ADC_CHANNEL_VDN_SEN:
		ADC_ChannelCmd(LPC_ADC, AD_CHANNEL_VDN_SEN, ENABLE);
	
		break;

	case DISABLE_ADC_CHANNEL_VSEN:
		ADC_ChannelCmd(LPC_ADC, AD_CHANNEL_VSEN, DISABLE);
		
		break;
		
	case DISABLE_ADC_CHANNEL_ISEN:
		ADC_ChannelCmd(LPC_ADC, AD_CHANNEL_ISEN, DISABLE);
	
		break;
	
	case DISABLE_ADC_CHANNEL_IAC_SEN:
		ADC_ChannelCmd(LPC_ADC, AD_CHANNEL_IAC_SEN, DISABLE);
	
		break;

	case DISABLE_ADC_CHANNEL_VDP_SEN:
		ADC_ChannelCmd(LPC_ADC, AD_CHANNEL_VDP_SEN, DISABLE);
	
		break;
		
	case DISABLE_ADC_CHANNEL_VDN_SEN:
		ADC_ChannelCmd(LPC_ADC, AD_CHANNEL_VDN_SEN, DISABLE);
	
		break;
	
	case DISABLE_ALL_ADC_CHANNEL:
		ADC_ChannelCmd(LPC_ADC, AD_CHANNEL_VSEN, DISABLE);
		ADC_ChannelCmd(LPC_ADC, AD_CHANNEL_ISEN, DISABLE);
		ADC_ChannelCmd(LPC_ADC, AD_CHANNEL_IAC_SEN, DISABLE);
		ADC_ChannelCmd(LPC_ADC, AD_CHANNEL_VDN_SEN, DISABLE);
	
		break;
	
	case GET_ADC_CHANNEL_VSEN_VAL:
		//ADC_StartCmd(LPC_ADC, ADC_START_NOW);
		//Wait conversion complete
		//while (!(ADC_ChannelGetStatus(LPC_ADC, AD_CHANNEL_VSEN, ADC_DATA_DONE)));
		*(rt_uint32_t *)args = ADC_ChannelGetData(LPC_ADC, AD_CHANNEL_VSEN);
	
		break;

	case GET_ADC_CHANNEL_ISEN_VAL:
		//ADC_StartCmd(LPC_ADC, ADC_START_NOW);
		//Wait conversion complete
		//while (!(ADC_ChannelGetStatus(LPC_ADC, AD_CHANNEL_ISEN, ADC_DATA_DONE)));
		*(rt_uint32_t *)args = ADC_ChannelGetData(LPC_ADC, AD_CHANNEL_ISEN);
	
		break;

	case GET_ADC_CHANNEL_IAC_SEN_VAL:
		//ADC_StartCmd(LPC_ADC, ADC_START_NOW);
		//Wait conversion complete
		//while (!(ADC_ChannelGetStatus(LPC_ADC, AD_CHANNEL_IAC_SEN, ADC_DATA_DONE)));
		*(rt_uint32_t *)args = ADC_ChannelGetData(LPC_ADC, AD_CHANNEL_IAC_SEN);
	
		break;

	case GET_ADC_CHANNEL_VDP_SEN_VAL:
		*(rt_uint32_t *)args = ADC_ChannelGetData(LPC_ADC, AD_CHANNEL_VDP_SEN);
	
		break;
		
	case GET_ADC_CHANNEL_VDN_SEN_VAL:
		//ADC_StartCmd(LPC_ADC, ADC_START_NOW);
		//Wait conversion complete
		//while (!(ADC_ChannelGetStatus(LPC_ADC, AD_CHANNEL_VDN_SEN, ADC_DATA_DONE)));
		*(rt_uint32_t *)args = ADC_ChannelGetData(LPC_ADC, AD_CHANNEL_VDN_SEN);
	
		break;
	
	default:
		goto ERROR;
	}
	
	return RT_EOK;
	
ERROR:
	return RT_ERROR;
}

void dev_adc_init(void)
{
	struct dev_adc *adc;
	
	adc = &s_dev_adc;
	
	adc->parent.type = RT_Device_Class_Char;
	
	adc->parent.init = rt_dev_adc_init;
	adc->parent.open = rt_dev_adc_open;
	adc->parent.close = rt_dev_adc_close;
	adc->parent.read  = rt_dev_adc_read;
	adc->parent.write = rt_dev_adc_write;
	adc->parent.control = rt_dev_adc_control;
	
	rt_device_register(&adc->parent,
		"adc", RT_DEVICE_FLAG_RDONLY /*| RT_DEVICE_FLAG_STREAM | RT_DEVICE_FLAG_INT_RX*/);
}
