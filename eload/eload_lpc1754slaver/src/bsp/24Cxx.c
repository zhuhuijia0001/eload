#include "type.h"
#include "lpc17xx_i2c.h"
#include "I2C.h"
#include "24Cxx.h"

#define LPC_I2C      LPC_I2C2
#if I2C_TYPE == I2C_HARDWARE
void Init24Cxx(void)
{
	InitI2CMaster(LPC_I2C, 400000ul);
}
#elif I2C_TYPE == I2C_SOFTWARE
void Init24Cxx(void)
{
	InitI2CMaster();
}

#else
#error "Invalid i2c type"
#endif

#if I2C_TYPE == I2C_HARDWARE
static bool Write24CxxByteInternal(uchar devAddr, ushort addr, uchar addrLen, uchar dat)
{
	uchar shift;
	ushort timeout = 0xffff;
	
	ulong codeStatus;
	
	codeStatus = I2C_Start(LPC_I2C);
	
	if ((codeStatus != I2C_I2STAT_M_TX_START)
		&& (codeStatus != I2C_I2STAT_M_TX_RESTART))
	{
		I2C_Stop(LPC_I2C);
		
		return false;
	}
	
	codeStatus = I2C_SendByte(LPC_I2C, devAddr);
	if (codeStatus != I2C_I2STAT_M_TX_SLAW_ACK)
	{
		I2C_Stop(LPC_I2C);
		
		return false;
	}
	
	shift = (addrLen - 1) * 8;
	while (addrLen--)
	{
		codeStatus = I2C_SendByte(LPC_I2C, addr >> shift);
		if (codeStatus != I2C_I2STAT_M_TX_DAT_ACK)
		{
			I2C_Stop(LPC_I2C);
			
			return false;
		}
		
		shift -= 8;;
	}
	
	codeStatus = I2C_SendByte(LPC_I2C, dat);
	if (codeStatus != I2C_I2STAT_M_TX_DAT_ACK)
	{
		I2C_Stop(LPC_I2C);
			
		return false;
	}
	
	I2C_Stop(LPC_I2C);
	
	//polling
	while (true)
	{
		codeStatus = I2C_Start(LPC_I2C);
		if ((codeStatus != I2C_I2STAT_M_TX_START)
			&& (codeStatus != I2C_I2STAT_M_TX_RESTART))
		{
			I2C_Stop(LPC_I2C);
		
			return false;
		}
		codeStatus = I2C_SendByte(LPC_I2C, devAddr);
		if (codeStatus == I2C_I2STAT_M_TX_SLAW_ACK)
		{
			break;
		}
		
		timeout--;
		if (timeout == 0)
		{
			I2C_Stop(LPC_I2C);
		
			return false;
		}
	}

	return true;	
}

#elif I2C_TYPE == I2C_SOFTWARE
static bool Write24CxxByteInternal(uchar devAddr, ushort addr, uchar addrLen, uchar dat)
{
	uchar shift;
	uchar timeout = 0xff;
	
	I2CStart();
	
	WriteI2CByte(devAddr);
	if (!CheckI2CAck())
	{
		I2CStop();
		return false;
	}
	
	shift = (addrLen - 1) * 8;
	while (addrLen--)
	{
		WriteI2CByte(addr >> shift);
		if (!CheckI2CAck())
		{
			I2CStop();
			return false;
		}
		
		shift -= 8;;
	}
	
	WriteI2CByte(dat);
	if (!CheckI2CAck())
	{
		I2CStop();
		return false;
	}
	
	I2CStop();

	//Polling
	while (true)
	{
		I2CStart();
		WriteI2CByte(devAddr);
		if (CheckI2CAck())
		{
			break;
		}
		
		timeout--;
		if (timeout == 0)
		{
			return false;
		}
	}
	
	return true;	
}

#else
#error "Invalid i2c type"
#endif

/****************************************************************
Description:  Write a byte at a specified address
Input:
addr :        Address to write at 
dat  : 		  Byte to write

Output:       true :success
			  false:failure
****************************************************************/
bool Write24CxxByte(ushort addr, uchar dat)
{
	uchar devAddr = 0xa0;
	uchar addrLen;
	
#if EEPROM_TYPE == EEPROM_TYPE_24C01 || EEPROM_TYPE == EEPROM_TYPE_24C02
	devAddr |= ((EEPROM_PIN_A2 << 3)
				|(EEPROM_PIN_A1 << 2)
				|(EEPROM_PIN_A0 << 1));
	
	addrLen = 1;
	
#elif EEPROM_TYPE == EEPROM_TYPE_24C04
	devAddr |= ((EEPROM_PIN_A2 << 3)
				|(EEPROM_PIN_A1 << 2));
	
	devAddr |= (((addr >> 8) & 0x01) << 1);
	
	addrLen = 1;
	
#elif EEPROM_TYPE == EEPROM_TYPE_24C08
	devAddr |= (EEPROM_PIN_A2 << 3);
	
	devAddr |= (((addr >> 8) & 0x03) << 1);
	
	addrLen = 1;
	
#elif EEPROM_TYPE == EEPROM_TYPE_24C16
	devAddr |= (((addr >> 8) & 0x07) << 1);
	
	addrLen = 1;
	
#elif EEPROM_TYPE == EEPROM_TYPE_24C32 || EEPROM_TYPE == EEPROM_TYPE_24C64
	devAddr |= ((EEPROM_PIN_A2 << 3)
				|(EEPROM_PIN_A1 << 2)
				|(EEPROM_PIN_A0 << 1));
	
	addrLen = 2;
	
#endif
	
	return Write24CxxByteInternal(devAddr, addr, addrLen, dat);	
}

#if I2C_TYPE == I2C_HARDWARE
static bool Read24CxxByteInternal(uchar devAddr, ushort addr, uchar addrLen, uchar *pData)
{
	uchar shift;
	
	ulong codeStatus;
	
	codeStatus = I2C_Start(LPC_I2C);
	
	if ((codeStatus != I2C_I2STAT_M_TX_START)
		&& (codeStatus != I2C_I2STAT_M_TX_RESTART))
	{
		I2C_Stop(LPC_I2C);
		
		return false;
	}
	
	codeStatus = I2C_SendByte(LPC_I2C, devAddr);
	if (codeStatus != I2C_I2STAT_M_TX_SLAW_ACK)
	{
		I2C_Stop(LPC_I2C);
		
		return false;
	}
	
	shift = (addrLen - 1) * 8;
	while (addrLen--)
	{
		codeStatus = I2C_SendByte(LPC_I2C, addr >> shift);
		if (codeStatus != I2C_I2STAT_M_TX_DAT_ACK)
		{
			I2C_Stop(LPC_I2C);
			
			return false;
		}
		
		shift -= 8;;
	}
	
	codeStatus = I2C_Start(LPC_I2C);
	if (codeStatus != I2C_I2STAT_M_RX_START
		&& codeStatus != I2C_I2STAT_M_RX_RESTART)
	{
		I2C_Stop(LPC_I2C);
			
		return false;
	}
	
	codeStatus = I2C_SendByte(LPC_I2C, devAddr | 0x01);
	if (codeStatus != I2C_I2STAT_M_RX_SLAR_ACK)
	{
		I2C_Stop(LPC_I2C);
			
		return false;
	}
	
	codeStatus = I2C_GetByte(LPC_I2C, pData, true);
	if (codeStatus != I2C_I2STAT_M_RX_DAT_ACK)
	{
		I2C_Stop(LPC_I2C);
			
		return false;
	}
	
	I2C_Stop(LPC_I2C);
	
	return true;	
}

#elif I2C_TYPE == I2C_SOFTWARE
static bool Read24CxxByteInternal(uchar devAddr, ushort addr, uchar addrLen, uchar *pData)
{
	uchar shift;
		
	I2CStart();
	
	WriteI2CByte(devAddr);
	if (!CheckI2CAck())
	{
		I2CStop();
		return false;
	}
	
	shift = (addrLen - 1) * 8;
	while (addrLen--)
	{
		WriteI2CByte(addr >> shift);
		if (!CheckI2CAck())
		{
			I2CStop();
			return false;
		}
		
		shift -= 8;;
	}
	
	I2CStart();
	
	WriteI2CByte(devAddr | 0x01);
	if (!CheckI2CAck())
	{
		I2CStop();
		return false;
	}
	
	*pData = ReceiveI2CByte();

	SendI2CAck(true);
	
	I2CStop();
	
	return true;	
}

#else
#error "Invalid i2c type"
#endif

/****************************************************************
Description:  Read a byte from a specified address
Input:
addr :        Address to read from 
pData: 		  Byte to read

Output:       true :success
			  false:failure
****************************************************************/
bool Read24CxxByte(ushort addr, uchar *pData)
{
	uchar devAddr = 0xa0;
	uchar addrLen;
	
#if EEPROM_TYPE == EEPROM_TYPE_24C01 || EEPROM_TYPE == EEPROM_TYPE_24C02
	devAddr |= ((EEPROM_PIN_A2 << 3)
				|(EEPROM_PIN_A1 << 2)
				|(EEPROM_PIN_A0 << 1));
	
	addrLen = 1;
	
#elif EEPROM_TYPE == EEPROM_TYPE_24C04
	devAddr |= ((EEPROM_PIN_A2 << 3)
				|(EEPROM_PIN_A1 << 2));
	
	devAddr |= (((addr >> 8) & 0x01) << 1);
	
	addrLen = 1;
	
#elif EEPROM_TYPE == EEPROM_TYPE_24C08
	devAddr |= (EEPROM_PIN_A2 << 3);
	
	devAddr |= (((addr >> 8) & 0x03) << 1);
	
	addrLen = 1;
	
#elif EEPROM_TYPE == EEPROM_TYPE_24C16
	devAddr |= (((addr >> 8) & 0x07) << 1);
	
	addrLen = 1;
	
#elif EEPROM_TYPE == EEPROM_TYPE_24C32 || EEPROM_TYPE == EEPROM_TYPE_24C64
	devAddr |= ((EEPROM_PIN_A2 << 3)
				|(EEPROM_PIN_A1 << 2)
				|(EEPROM_PIN_A0 << 1));
	
	addrLen = 2;
	
#endif
	
	return Read24CxxByteInternal(devAddr, addr, addrLen, pData);	
}

#if I2C_TYPE == I2C_HARDWARE
static bool Write24CxxDataPageInternal(uchar devAddr, ushort addr, uchar addrLen, const uchar *pData, uchar size)
{
	uchar shift;
	ushort timeout = 0xffff;
	
	ulong codeStatus;
	
	codeStatus = I2C_Start(LPC_I2C);
	
	if ((codeStatus != I2C_I2STAT_M_TX_START)
		&& (codeStatus != I2C_I2STAT_M_TX_RESTART))
	{
		I2C_Stop(LPC_I2C);
		
		return false;
	}
	
	codeStatus = I2C_SendByte(LPC_I2C, devAddr);
	if (codeStatus != I2C_I2STAT_M_TX_SLAW_ACK)
	{
		I2C_Stop(LPC_I2C);
		
		return false;
	}
	
	shift = (addrLen - 1) * 8;
	while (addrLen--)
	{
		codeStatus = I2C_SendByte(LPC_I2C, addr >> shift);
		if (codeStatus != I2C_I2STAT_M_TX_DAT_ACK)
		{
			I2C_Stop(LPC_I2C);
			
			return false;
		}
		
		shift -= 8;;
	}
	
	while (size--)
	{
		codeStatus = I2C_SendByte(LPC_I2C, *pData++);
		if (codeStatus != I2C_I2STAT_M_TX_DAT_ACK)
		{
			I2C_Stop(LPC_I2C);
			
			return false;
		}
	}
	
	I2C_Stop(LPC_I2C);
	
	//polling
	while (true)
	{
		codeStatus = I2C_Start(LPC_I2C);
		if ((codeStatus != I2C_I2STAT_M_TX_START)
			&& (codeStatus != I2C_I2STAT_M_TX_RESTART))
		{
			I2C_Stop(LPC_I2C);
		
			return false;
		}
		codeStatus = I2C_SendByte(LPC_I2C, devAddr);
		if (codeStatus == I2C_I2STAT_M_TX_SLAW_ACK)
		{
			break;
		}
		
		timeout--;
		if (timeout == 0)
		{
			I2C_Stop(LPC_I2C);
		
			return false;
		}
	}
	
	return true;	
}

#elif I2C_TYPE == I2C_SOFTWARE
static bool Write24CxxDataPageInternal(uchar devAddr, ushort addr, uchar addrLen, const uchar *pData, uchar size)
{
	uchar shift;
	uchar timeout = 0xff;
	
	I2CStart();
	
	WriteI2CByte(devAddr);
	if (!CheckI2CAck())
	{
		I2CStop();
		return false;
	}
	
	shift = (addrLen - 1) * 8;
	while (addrLen--)
	{
		WriteI2CByte(addr >> shift);
		if (!CheckI2CAck())
		{
			I2CStop();
			return false;
		}
		
		shift -= 8;;
	}
	
	while (size--)
	{
		WriteI2CByte(*pData++);
		if (!CheckI2CAck())
		{
			I2CStop();
			return false;
		}
	}
	
	I2CStop();

	//Polling
	while (true)
	{
		I2CStart();
		WriteI2CByte(devAddr);
		if (CheckI2CAck())
		{
			break;
		}
		
		timeout--;
		if (timeout == 0)
		{
			return false;
		}
	}
	
	return true;	
}

#else
#error "Invalid i2c type"
#endif

static bool Write24CxxDataPage(ushort addr, const uchar *pData, uchar size)
{
	uchar devAddr = 0xa0;
	uchar addrLen;
	
#if EEPROM_TYPE == EEPROM_TYPE_24C01 || EEPROM_TYPE == EEPROM_TYPE_24C02
	devAddr |= ((EEPROM_PIN_A2 << 3)
				|(EEPROM_PIN_A1 << 2)
				|(EEPROM_PIN_A0 << 1));
	
	addrLen = 1;
	
#elif EEPROM_TYPE == EEPROM_TYPE_24C04
	devAddr |= ((EEPROM_PIN_A2 << 3)
				|(EEPROM_PIN_A1 << 2));
	
	devAddr |= (((addr >> 8) & 0x01) << 1);
	
	addrLen = 1;
	
#elif EEPROM_TYPE == EEPROM_TYPE_24C08
	devAddr |= (EEPROM_PIN_A2 << 3);
	
	devAddr |= (((addr >> 8) & 0x03) << 1);
	
	addrLen = 1;
	
#elif EEPROM_TYPE == EEPROM_TYPE_24C16
	devAddr |= (((addr >> 8) & 0x07) << 1);
	
	addrLen = 1;
	
#elif EEPROM_TYPE == EEPROM_TYPE_24C32 || EEPROM_TYPE == EEPROM_TYPE_24C64
	devAddr |= ((EEPROM_PIN_A2 << 3)
				|(EEPROM_PIN_A1 << 2)
				|(EEPROM_PIN_A0 << 1));
	
	addrLen = 2;
	
#endif
	
	return Write24CxxDataPageInternal(devAddr, addr, addrLen, pData, size);
}

/****************************************************************
Description:  Write data from a specified address
Input:
addr :        Address to write from
pData:        Data to write
size : 		  Count of data in byte

Output:       true :success
			  false:failure
****************************************************************/
bool Write24CxxData(ushort addr, const uchar *pData, ushort size)
{
	ushort left = size;
	
	ushort pageOffset = addr % EEPROM_PAGE_SIZE;

	ushort pageRemain = EEPROM_PAGE_SIZE - pageOffset;
	
	if (pageRemain > left)
	{
		pageRemain = left;
	}

	if (pageRemain < EEPROM_PAGE_SIZE)
	{
		if (!Write24CxxDataPage(addr, pData, pageRemain))
		{
			return false;
		}
		
		left -= pageRemain;
		pData += pageRemain;
		addr += pageRemain;
	}
	
	while (left >= EEPROM_PAGE_SIZE)
	{
		if (!Write24CxxDataPage(addr, pData, EEPROM_PAGE_SIZE))
		{
			return false;
		}
			
		pData += EEPROM_PAGE_SIZE;
		addr += EEPROM_PAGE_SIZE;
		
		left -= EEPROM_PAGE_SIZE;
	}
	
	if (left > 0)
	{
		if (!Write24CxxDataPage(addr, pData, left))
		{
			return false;
		}
	}
	
	return true;	
}

#if I2C_TYPE == I2C_HARDWARE
static bool Read24CxxDataInternal(uchar devAddr, ushort addr, uchar addrLen, uchar *pData, ushort size, ushort *pSizeRet)
{
	uchar shift;
	ushort count = 0;
	
	uchar tmp;
	
	ulong codeStatus;
	
	codeStatus = I2C_Start(LPC_I2C);
	
	if ((codeStatus != I2C_I2STAT_M_TX_START)
		&& (codeStatus != I2C_I2STAT_M_TX_RESTART))
	{
		I2C_Stop(LPC_I2C);
		
		return false;
	}
	
	codeStatus = I2C_SendByte(LPC_I2C, devAddr);
	if (codeStatus != I2C_I2STAT_M_TX_SLAW_ACK)
	{
		I2C_Stop(LPC_I2C);
		
		return false;
	}
	
	shift = (addrLen - 1) * 8;
	while (addrLen--)
	{
		codeStatus = I2C_SendByte(LPC_I2C, addr >> shift);
		if (codeStatus != I2C_I2STAT_M_TX_DAT_ACK)
		{
			I2C_Stop(LPC_I2C);
			
			return false;
		}
		
		shift -= 8;;
	}
	
	codeStatus = I2C_Start(LPC_I2C);
	if (codeStatus != I2C_I2STAT_M_RX_START
		&& codeStatus != I2C_I2STAT_M_RX_RESTART)
	{
		I2C_Stop(LPC_I2C);
			
		return false;
	}
	
	codeStatus = I2C_SendByte(LPC_I2C, devAddr | 0x01);
	if (codeStatus != I2C_I2STAT_M_RX_SLAR_ACK)
	{
		I2C_Stop(LPC_I2C);
			
		return false;
	}
	
	while (size--)
	{
		codeStatus = I2C_GetByte(LPC_I2C, &tmp, size > 0);
		*pData++ = tmp;
		if (size > 0)
		{
			if (codeStatus != I2C_I2STAT_M_RX_DAT_ACK)
			{
				I2C_Stop(LPC_I2C);
				
				return false;
			}
		}
		else
		{
			if (codeStatus != I2C_I2STAT_M_RX_DAT_NACK)
			{
				I2C_Stop(LPC_I2C);
				
				return false;
			}
		}
		
		count++;
	}
	
	I2C_Stop(LPC_I2C);
	
	if (pSizeRet != NULL)
	{
		*pSizeRet = count;
	}
	
	return true;	
}

#elif I2C_TYPE == I2C_SOFTWARE
static bool Read24CxxDataInternal(uchar devAddr, ushort addr, uchar addrLen, uchar *pData, ushort size, ushort *pSizeRet)
{
	uchar shift;
	
	ushort count = 0;
	
	I2CStart();
	
	WriteI2CByte(devAddr);
	if (!CheckI2CAck())
	{
		I2CStop();
		
		return false;
	}
	
	shift = (addrLen - 1) * 8;
	while (addrLen--)
	{
		WriteI2CByte(addr >> shift);
		if (!CheckI2CAck())
		{
			I2CStop();
			
			return false;
		}
		
		shift -= 8;;
	}
	
	I2CStart();
	WriteI2CByte(devAddr | 0x01);
	if (!CheckI2CAck())
	{
		I2CStop();
		
		return false;
	}
	
	while (size--)
	{
		*pData++ = ReceiveI2CByte();
		SendI2CAck(size == 0);
		
		count++;
	}
	
	I2CStop();
	
	if (pSizeRet != NULL)
	{
		*pSizeRet = count;
	}
	
	return true;	
}
#else
#error "Invalid i2c type"
#endif

/****************************************************************
Description:  Read data from a specified address
Input:
addr :        Address to read from
pData:        Buffer to read data
size : 		  Count of data in byte to read
pSizeRet:     Count of data that has read

Output:       true :success
			  false:failure
****************************************************************/
bool Read24CxxData(ushort addr, uchar *pData, ushort size, ushort *pSizeRet)
{
	uchar devAddr = 0xa0;
	uchar addrLen;
	
#if (EEPROM_TYPE == EEPROM_TYPE_24C01) || (EEPROM_TYPE == EEPROM_TYPE_24C02)
	devAddr |= ((EEPROM_PIN_A2 << 3)
				|(EEPROM_PIN_A1 << 2)
				|(EEPROM_PIN_A0 << 1));
	
	addrLen = 1;
	
#elif EEPROM_TYPE == EEPROM_TYPE_24C04
	devAddr |= ((EEPROM_PIN_A2 << 3)
				|(EEPROM_PIN_A1 << 2));
	
	devAddr |= (((addr >> 8) & 0x01) << 1);
	
	addrLen = 1;
	
#elif EEPROM_TYPE == EEPROM_TYPE_24C08
	devAddr |= (EEPROM_PIN_A2 << 3);
	
	devAddr |= (((addr >> 8) & 0x03) << 1);
	
	addrLen = 1;
	
#elif EEPROM_TYPE == EEPROM_TYPE_24C16
	devAddr |= (((addr >> 8) & 0x07) << 1);
	
	addrLen = 1;
	
#elif (EEPROM_TYPE == EEPROM_TYPE_24C32) || (EEPROM_TYPE == EEPROM_TYPE_24C64)
	devAddr |= ((EEPROM_PIN_A2 << 3)
				|(EEPROM_PIN_A1 << 2)
				|(EEPROM_PIN_A0 << 1));
	
	addrLen = 2;
	
#endif
	
	return 	Read24CxxDataInternal(devAddr, addr, addrLen, pData, size, pSizeRet);	
}
