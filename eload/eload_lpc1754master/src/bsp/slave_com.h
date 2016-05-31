#ifndef _SLAVE_COM_H_
#define _SLAVE_COM_H_

#include "slave_port_define.h"

extern void salve_com_init(void);

extern uint16_t slave_com_write(slave_com_port port, const uint8_t *buffer, uint16_t size);

extern void slave_com_set_read_callback(void (*fn)(uint8_t *payload, uint16_t payload_size));

#endif
