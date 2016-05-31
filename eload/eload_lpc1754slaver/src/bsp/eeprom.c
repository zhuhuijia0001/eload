
#include <rthw.h>
#include <rtthread.h>

#include <stdint.h>

#include "dev_eeprom.h"
#include "eeprom.h"

static rt_device_t s_dev_eeprom = RT_NULL;

void eeprom_init(void)
{
	dev_eeprom_init();
	
	s_dev_eeprom = rt_device_find("eeprom");
	
	RT_ASSERT(s_dev_eeprom != RT_NULL);
	
	rt_device_open(s_dev_eeprom, RT_DEVICE_OFLAG_RDWR);
}

int32_t eeprom_write(int pos, const void* buffer, int32_t size)
{
	RT_ASSERT(s_dev_eeprom != RT_NULL);
	
	return rt_device_write(s_dev_eeprom, pos, buffer, size);
}

int32_t eeprom_read(int pos, void* buffer, int32_t size)
{
	RT_ASSERT(s_dev_eeprom != RT_NULL);
	
	return rt_device_read(s_dev_eeprom, pos, buffer, size);
}
