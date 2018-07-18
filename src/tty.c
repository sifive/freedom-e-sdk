/* Copyright 2018 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#include <mee/uart.h>

#if defined(__MEE_DT_STDOUT_UART_HANDLE)
/* This implementation serves as a small shim that interfaces with the first
 * UART on a system. */
int mee_tty_putc(unsigned char c)
{
    if (c == '\n') {
        int out = mee_uart_putc(__MEE_DT_STDOUT_UART_HANDLE, '\r');
        if (out != 0)
            return out;
    }
    return mee_uart_putc(__MEE_DT_STDOUT_UART_HANDLE, c);
}

#ifndef __MEE_DT_STDOUT_UART_BAUD
#define __MEE_DT_STDOUT_UART_BAUD 115200
#endif

static void mee_tty_init(void) __attribute__((constructor));
static void mee_tty_init(void)
{
    mee_uart_init(__MEE_DT_STDOUT_UART_HANDLE, __MEE_DT_STDOUT_UART_BAUD);
}
#else
/* This implementation of putc doesn't actually do anything, it's just there to
 * provide a shim that eats all the characters so we can ensure that everything
 * can link to mee_tty_putc. */
int nop_putc(unsigned char c) __attribute__((section(".text.mee.nop.putc")));
int nop_putc(unsigned char c) { return -1; }
int mee_tty_putc(unsigned char c) __attribute__((weak, alias("nop_putc")));
#warning "There is no default output device, mee_tty_putc() will throw away all input."
#endif
