#include <stdint.h>

#include "type.h"
#include "parameter.h"
#include "eeprom.h"

PARAMETER_STRUCT  g_parameter_struct;

const PARAMETER s_default_parameter = 
{
	.measure_voltage = 1,

	.actual_voltage  = 1,

	.measure_current = 1,

	.actual_current  = 1
};

#define EEPROM_START_ADDR    0

bool load_parameter(void)
{
	if (eeprom_read(EEPROM_START_ADDR, &g_parameter_struct, sizeof(g_parameter_struct)) != sizeof(g_parameter_struct))
	{
		return false;
	}

	if (g_parameter_struct.header != PARAMETER_HEADER)
	{
		return false;
	}

	if (g_parameter_struct.size != sizeof(PARAMETER))
	{
		return false;
	}

	return true;
}

void save_default_parameter(void)
{
	g_parameter_struct.header = PARAMETER_HEADER;
	g_parameter_struct.size   = sizeof(PARAMETER);
	g_parameter_struct.parameter = s_default_parameter;

	eeprom_write(EEPROM_START_ADDR, &g_parameter_struct, sizeof(g_parameter_struct));
}

bool save_parameter(void)
{
	if (eeprom_write(EEPROM_START_ADDR, &g_parameter_struct, sizeof(g_parameter_struct))
		!= sizeof(g_parameter_struct))
	{
		return false;
	}

	return true;
}
