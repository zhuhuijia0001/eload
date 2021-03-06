#ifndef _DEV_ADC_H_
#define _DEV_ADC_H_

/* cmd */
#define ENABLE_ADC_CHANNEL_VSEN        0x01
#define ENABLE_ADC_CHANNEL_ISEN        0x02
#define ENABLE_ADC_CHANNEL_IAC_SEN     0x03
#define ENABLE_ADC_CHANNEL_VDP_SEN     0x04
#define ENABLE_ADC_CHANNEL_VDN_SEN     0x05

#define DISABLE_ADC_CHANNEL_VSEN       0x06
#define DISABLE_ADC_CHANNEL_ISEN       0x07
#define DISABLE_ADC_CHANNEL_IAC_SEN    0x08
#define DISABLE_ADC_CHANNEL_VDP_SEN    0x09
#define DISABLE_ADC_CHANNEL_VDN_SEN    0x0A
#define DISABLE_ALL_ADC_CHANNEL        0x0B

#define GET_ADC_CHANNEL_VSEN_VAL       0x0C
#define GET_ADC_CHANNEL_ISEN_VAL       0x0D
#define GET_ADC_CHANNEL_IAC_SEN_VAL    0x0E
#define GET_ADC_CHANNEL_VDP_SEN_VAL    0x0F
#define GET_ADC_CHANNEL_VDN_SEN_VAL    0x10

extern void dev_adc_init(void);

#endif
