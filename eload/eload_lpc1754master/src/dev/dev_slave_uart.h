#ifndef _DEV_SLAVE_UART_H_
#define _DEV_SLAVE_UART_H_

/* slave uart cmd */
#define CMD_SLAVE_UART_RESET_FIFO     1

#define CMD_SLAVE_UART_SWITCH_CHANNEL 2

extern void dev_slave_uart_init(void);

#endif
