/* Copyright 2018 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#include <mee/uart.h>

extern inline void mee_uart_init(struct mee_uart *uart, int baud_rate);
extern inline int mee_uart_putc(struct mee_uart *uart, unsigned char c);
extern inline int mee_uart_getc(struct mee_uart *uart, unsigned char *c);
extern inline int mee_uart_get_baud_rate(struct mee_uart *uart);
extern inline int mee_uart_set_baud_rate(struct mee_uart *uart, int baud_rate);
