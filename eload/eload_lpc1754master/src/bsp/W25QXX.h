#ifndef _W25QXX_H_
#define _W25QXX_H_

void W25QXXInit(void);
UINT16 W25QXXReadID(void);
void W25QXXReadSector(UINT32 sector, UINT8* pBuffer); 
void W25QXXWriteSector(UINT32 sector, const UINT8* pBuffer);
void W25QXXEraseChip(void);  
void W25QXXEraseSector(UINT32 sector);

#endif
