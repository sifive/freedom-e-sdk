// See LICENSE file for license details

#ifndef UART_DRIVER_H
#define UART_DRIVER_H

/* Standard includes */
#include <unistd.h>

/* HiFive/FE310 includes*/
#include "platform.h"

/* Top-level functions */
void UART_init(unsigned long baud, int stop_bits);
void UART_deinit();
int UART_write(char * msg, int blocking);
int UART_read_n(char * buffer, int max_chars, char terminator, int blocking);

/* Worker functions */
int UART_get_char(char * ch, int blocking);
int UART_put_char(char ch, int blocking);
void UART_set_baud(unsigned long baud);
void UART_set_stop_bits(int bits);

#endif /* UART_DRIVER_H */
