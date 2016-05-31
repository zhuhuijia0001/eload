#ifndef _COM_PORT_H_
#define _COM_PORT_H_

extern void com_port_init(void);

extern int com_port_write(const uint8_t *data, int size);

extern void com_port_set_read_callback(void (*fn)(uint8_t *payload, uint16_t payload_size));

#endif
