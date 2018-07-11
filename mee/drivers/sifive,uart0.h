/* Copyright 2018 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#ifndef MEE__DRIVERS__SIFIVE_UART0_H
#define MEE__DRIVERS__SIFIVE_UART0_H

#include <mee/uart.h>
#include <mee/clock.h>

/* A driver for the SiFive UART. */
struct __mee_driver_sifive_uart0 {
    struct mee_uart uart;
    struct mee_clock *clock;
    unsigned long base;
    unsigned long baud_rate;
};

/* Initializes a SiFive UART.  This must be called before any  */
void __mee_driver_sifive_uart0_init(struct __mee_driver_sifive_uart0 *uart);

/* Static paramaterization of the UART driver. */
#ifdef __MEE_DT_SIFIVE_UART0_0_HANDLE
extern struct __mee_driver_sifive_uart0 __mee_driver_sifive_uart0_0;
#endif

#ifdef __MEE_DT_SIFIVE_UART0_1_HANDLE
# error "Only one sifive,uart0 is supported"
#endif

#endif
