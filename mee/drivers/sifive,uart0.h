/* Copyright 2018 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#ifndef MEE__DRIVERS__SIFIVE_UART0_H
#define MEE__DRIVERS__SIFIVE_UART0_H

#include <mee/clock.h>
#include <mee/compiler.h>
#include <mee/io.h>
#include <mee/uart.h>

struct __mee_driver_vtable_sifive_uart0 {
    const struct mee_uart_vtable uart;
};

struct __mee_driver_sifive_uart0;

void __mee_driver_sifive_uart0_init(struct __mee_driver_sifive_uart0 *uart);
int __mee_driver_sifive_uart0_putc(struct mee_uart *uart, unsigned char c);
int __mee_driver_sifive_uart0_getc(struct mee_uart *uart, unsigned char *c);
int __mee_driver_sifive_uart0_get_baud_rate(struct mee_uart *guart);
int __mee_driver_sifive_uart0_set_baud_rate(struct mee_uart *guart, int baud_rate);

MEE_DECLARE_VTABLE(__mee_driver_vtable_sifive_uart0) = {
    .uart.putc          = __mee_driver_sifive_uart0_putc,
    .uart.getc          = __mee_driver_sifive_uart0_getc,
    .uart.get_baud_rate = __mee_driver_sifive_uart0_get_baud_rate,
    .uart.set_baud_rate = __mee_driver_sifive_uart0_set_baud_rate,
};

struct __mee_driver_sifive_uart0 {
    struct mee_uart uart;
    const struct __mee_driver_vtable_sifive_uart0 *vtable;
    struct mee_clock *clock;
    const unsigned long control_base;
    const unsigned long control_size;
    unsigned long baud_rate;
};


#endif
