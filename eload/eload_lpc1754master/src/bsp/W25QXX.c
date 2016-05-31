#include <stdint.h>

#include "type.h"
#include "PinDefine.h"
#include "spi.h"
#include "W25QXX.h"

//指令表
#define W25Q_WriteEnable		0x06 
#define W25Q_WriteDisable		0x04 
#define W25Q_ReadStatusReg		0x05 
#define W25Q_WriteStatusReg		0x01 
#define W25Q_ReadData			0x03 
#define W25Q_FastReadData		0x0B 
#define W25Q_FastReadDual		0x3B 
#define W25Q_PageProgram		0x02 
#define W25Q_BlockErase			0xD8 
#define W25Q_SectorErase		0x20 
#define W25Q_ChipErase			0xC7 
#define W25Q_PowerDown			0xB9 
#define W25Q_ReleasePowerDown	0xAB 
#define W25Q_DeviceID			0xAB 
#define W25Q_ManufactDeviceID	0x90 
#define W25Q_JedecDeviceID		0x9F

#define PAGE_SIZE    256

#define SECTOR_SIZE  4096

#define SELECT_CHIP()        CLR_GPIO_BIT(PIN_FLASH_CS)            
#define DESELECT_CHIP()      SET_GPIO_BIT(PIN_FLASH_CS) 

void W25QXXInit(void)
{
	SPIInit();
}

UINT16 W25QXXReadID(void)
{
	UINT16 id = 0;
	
	SELECT_CHIP();
	
	SPIReadWriteByte(W25Q_ManufactDeviceID);
	SPIReadWriteByte(0x00);
	SPIReadWriteByte(0x00);
	SPIReadWriteByte(0x00);
	
	id |= SPIReadWriteByte(0xff);
	id <<= 8;
	id |= SPIReadWriteByte(0xff);
	
	DESELECT_CHIP();
	
	return id;
}

static UINT8 W25QXXReadSR(void)
{
	UINT8 dat;
	
	SELECT_CHIP();
	
	SPIReadWriteByte(W25Q_ReadStatusReg);
	dat = SPIReadWriteByte(0xff);
	
	DESELECT_CHIP();
	
	return dat;
}

static void W25QXXWaitBusy(void)
{
	UINT16 timeout = 0xffff;

	UINT8 sr;
	do
	{
		sr = W25QXXReadSR();
	} while ((sr & 0x01) && --timeout); 
}


static void W25QXXWriteEnable(void)
{
	SELECT_CHIP();
	
	SPIReadWriteByte(W25Q_WriteEnable);
	
	DESELECT_CHIP();
}

#if 0
static void W25QXXWriteDisable(void)
{
	SELECT_CHIP();
	
	SPIReadWriteByte(W25Q_WriteDisable);
	
	DESELECT_CHIP();	
}
#endif

void W25QXXReadSector(UINT32 sector, UINT8* pBuffer)
{
	UINT16 i;

	sector *= SECTOR_SIZE;
	
	SELECT_CHIP();
	
	SPIReadWriteByte(W25Q_ReadData);
	
	SPIReadWriteByte((UINT8)(sector >> 16));
	SPIReadWriteByte((UINT8)(sector >> 8));
	SPIReadWriteByte((UINT8)sector);
	
	for (i = 0; i < SECTOR_SIZE; i++)
	{
		pBuffer[i] =  SPIReadWriteByte(0xff);
	}
	
	DESELECT_CHIP();
}

void W25QXXWriteSector(UINT32 sector, const UINT8* pBuffer)
{
 	UINT16 i, j; 

 	sector *= SECTOR_SIZE;

 	for (i = 0; i < SECTOR_SIZE / PAGE_SIZE; i++)
 	{
    	W25QXXWriteEnable(); 
	
		SELECT_CHIP(); 
	
    	SPIReadWriteByte(W25Q_PageProgram);
    	SPIReadWriteByte((UINT8)((sector)>>16));  
    	SPIReadWriteByte((UINT8)((sector)>>8));   
    	SPIReadWriteByte((UINT8)sector);
	
    	for (j = 0; j < PAGE_SIZE; j++)
		{
			SPIReadWriteByte(pBuffer[j]);
		}

		sector += PAGE_SIZE;
		pBuffer += PAGE_SIZE;
	
		DESELECT_CHIP();
	
		W25QXXWaitBusy();
	}
}

void W25QXXEraseChip(void)
{
    W25QXXWriteEnable();                  //SET WEL 
    W25QXXWaitBusy();   
  	SELECT_CHIP();                          //使能器件   
    SPIReadWriteByte(W25Q_ChipErase);        //发送片擦除命令  
	DESELECT_CHIP();                            //取消片选     	      
	W25QXXWaitBusy();   		
}

void W25QXXEraseSector(UINT32 sector)
{
	sector *= SECTOR_SIZE;
    W25QXXWriteEnable();                  //SET WEL 
    W25QXXWaitBusy();  
  	
	SELECT_CHIP();                            //使能器件   
    SPIReadWriteByte(W25Q_SectorErase);      //发送扇区擦除指令 
    SPIReadWriteByte((UINT8)((sector)>>16));  //发送24bit地址    
    SPIReadWriteByte((UINT8)((sector)>>8));   
    SPIReadWriteByte((UINT8)sector);  
	DESELECT_CHIP();                            //取消片选     	      
    W25QXXWaitBusy();   				   //等待擦除完成	
}

