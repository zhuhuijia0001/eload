
#include <rthw.h>
#include <rtthread.h>

#include "type.h"
#include "dev_eeprom.h"
#include "W25QXX.h"

struct dev_eeprom
{
	struct rt_device parent;
};

static struct dev_eeprom s_dev_eeprom;

#define  FLASH_SECTOR_SIZE      RT_DFS_ELM_MAX_SECTOR_SIZE
#define  FLASH_SECTOR_COUNT     (2 * 1024 * 1024 / FLASH_SECTOR_SIZE)

static rt_err_t rt_eeprom_init (rt_device_t dev)
{
	W25QXXInit();
	
	rt_uint16_t id = W25QXXReadID();

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
	int i;

	rt_uint8_t *dst = (rt_uint8_t *)buffer;
	
	for (i = 0; i < size; i++)
	{
		W25QXXReadSector((rt_uint32_t)pos, dst);

		pos++;

		dst += FLASH_SECTOR_SIZE;
	}
	
	return size;
}

static rt_size_t rt_eeprom_write(rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{	
	int i;

	const rt_uint8_t *src = (const rt_uint8_t *)buffer;

	for (i = 0; i < size; i++)
	{
		W25QXXEraseSector((rt_uint32_t)pos);
		
		W25QXXWriteSector((rt_uint32_t)pos, src);

		pos++;

		src += FLASH_SECTOR_SIZE;
	}
	
	return size;
}

static rt_err_t rt_eeprom_control(rt_device_t dev, rt_uint8_t cmd, void *args)
{
	rt_err_t err = RT_EOK;

	if (cmd == RT_DEVICE_CTRL_BLK_GETGEOME)
    {
        struct rt_device_blk_geometry *geometry;

        geometry = (struct rt_device_blk_geometry *)args;
        if (geometry == RT_NULL) return -RT_ERROR;

        geometry->bytes_per_sector = FLASH_SECTOR_SIZE;
        geometry->block_size = 1;
        geometry->sector_count = FLASH_SECTOR_COUNT;
    }
    else if (cmd == RT_DEVICE_CTRL_BLK_ERASE)
    {
		rt_uint32_t from = *((rt_uint32_t*)args);

		rt_uint32_t to = *(((rt_uint32_t*)args) + 1);

		rt_uint32_t i;
		for (i = from; i <= to; i++)
		{
			W25QXXEraseSector(i);
		}
    }
    
	return err;
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
	eeprom->parent.control    = rt_eeprom_control;
	eeprom->parent.user_data  = RT_NULL;
	
	rt_device_register(&eeprom->parent, "eeprom", RT_DEVICE_FLAG_WRONLY);
}
