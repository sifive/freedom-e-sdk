/* Copyright 2018 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#ifndef MEE__UART_H
#define MEE__UART_H

struct mee_uart;

struct mee_uart_vtable {
    void (*init)(struct mee_uart *uart, int baud_rate);
    int (*putc)(struct mee_uart *uart, unsigned char c);
    int (*getc)(struct mee_uart *uart, unsigned char *c);
    int (*get_baud_rate)(struct mee_uart *uart);
    int (*set_baud_rate)(struct mee_uart *uart, int baud_rate);
};

struct mee_uart {
    const struct mee_uart_vtable *vtable;
};

/* Initializes a UART. */
inline void mee_uart_init(struct mee_uart *uart, int baud_rate) { return uart->vtable->init(uart, baud_rate); }

/* Reads from or writes to a UART.  These return 0 on success. */
inline int mee_uart_putc(struct mee_uart *uart, unsigned char c) { return uart->vtable->putc(uart, c); }
inline int mee_uart_getc(struct mee_uart *uart, unsigned char *c) { return uart->vtable->getc(uart, c); }

/* Modifies (or allows probing of) the UART's current baud rate. */
inline int mee_uart_get_baud_rate(struct mee_uart *uart) { return uart->vtable->get_baud_rate(uart); }
inline int mee_uart_set_baud_rate(struct mee_uart *uart, int baud_rate) { return uart->vtable->set_baud_rate(uart, baud_rate); }

#endif
