
#include <stdint.h>

#include "PinDefine.h"

#include "spi.h"

void SPIInit(void)
{
	/* cs */
	SET_GPIO_BIT(PIN_FLASH_CS);
	SET_GPIO_OUTPUT(PIN_FLASH_CS);
	
	/* sck */
	CLR_GPIO_BIT(PIN_FLASH_SCK);
	SET_GPIO_OUTPUT(PIN_FLASH_SCK);
	
	/* mosi */
	CLR_GPIO_BIT(PIN_FLASH_MOSI);
	SET_GPIO_OUTPUT(PIN_FLASH_MOSI);
	
	/* miso */
	SET_GPIO_INPUT(PIN_FLASH_MISO);
}


uint8_t SPIReadWriteByte(uint8_t ch)
{
	int i;
	
	uint8_t ret = 0;
	
	for (i = 0; i < 8; i++)
	{
		CLR_GPIO_BIT(PIN_FLASH_SCK);
		
		if (ch & 0x80)
		{
			SET_GPIO_BIT(PIN_FLASH_MOSI);
		}
		else
		{
			CLR_GPIO_BIT(PIN_FLASH_MOSI);
		}
		
		SET_GPIO_BIT(PIN_FLASH_SCK);
		
		ret <<= 1;
		ret |= GET_GPIO_BIT(PIN_FLASH_MISO);
		
		ch <<= 1;
	}
	
	CLR_GPIO_BIT(PIN_FLASH_SCK);
	
	return ret;	
}
