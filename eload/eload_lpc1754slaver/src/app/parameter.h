
#ifndef _PARAMETER_H_
#define _PARAMETER_H_

#define PARAMETER_HEADER    0xDEADBEEF

typedef struct
{
	uint32_t  measure_voltage;

	uint32_t  actual_voltage;

	uint32_t  measure_current;

	uint32_t  actual_current;
} __attribute__ ((packed)) PARAMETER;

typedef struct
{
	uint32_t  header;
	uint32_t  size;

	PARAMETER parameter;
} __attribute__ ((packed)) PARAMETER_STRUCT;

extern PARAMETER_STRUCT  g_parameter_struct;

#define  ADJUST_PARAMETER   g_parameter_struct.parameter

extern bool load_parameter(void);

extern void save_default_parameter(void);

extern bool save_parameter(void);

#endif

