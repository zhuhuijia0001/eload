
#include <rthw.h>
#include <rtthread.h>

#include "type.h"
#include "dev_eeprom.h"
#include "24Cxx.h"

struct dev_eeprom
{
	struct rt_device parent;
};

static struct dev_eeprom s_dev_eeprom;

static rt_err_t rt_eeprom_init (rt_device_t dev)
{
	Init24Cxx();

	return RT_EOK;
}

static rt_err_t rt_eeprom_open(rt_device_t dev, rt_uint16_t oflag)
{
	return RT_EOK;
}

static rt_err_t rt_eeprom_close(rt_device_t dev)
{
	return RT_EOK;
}

static rt_size_t rt_eeprom_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
	ushort ret_size;
	
	bool res = Read24CxxData((ushort)pos, (uchar *)buffer, (ushort)size, &ret_size);
	if (!res)
	{
		return 0;
	}
	
	return (rt_size_t)ret_size;
}

static rt_size_t rt_eeprom_write(rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{	
	bool res = Write24CxxData((ushort)pos, (const uchar *)buffer, (ushort)size);
	if (!res)
	{
		return 0;
	}
	
	return size;
}

void dev_eeprom_init(void)
{
	struct dev_eeprom* eeprom;

	eeprom = &s_dev_eeprom;

	/* device initialization */
	eeprom->parent.type = RT_Device_Class_Char;

	/* device interface */
	eeprom->parent.init 	  = rt_eeprom_init;
	eeprom->parent.open 	  = rt_eeprom_open;
	eeprom->parent.close      = rt_eeprom_close;
	eeprom->parent.read 	  = rt_eeprom_read;
	eeprom->parent.write      = rt_eeprom_write;
	eeprom->parent.control    = RT_NULL;
	eeprom->parent.user_data  = RT_NULL;
	
	rt_device_register(&eeprom->parent, "eeprom", RT_DEVICE_FLAG_WRONLY);
}
