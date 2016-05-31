#ifndef _EEPROM_H_
#define _EEPROM_H_

extern void eeprom_init(void);

extern int32_t eeprom_write(int pos, const void* buffer, int32_t size);

extern int32_t eeprom_read(int pos, void* buffer, int32_t size);

#endif
