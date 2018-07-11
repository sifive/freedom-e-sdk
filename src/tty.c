/* Copyright 2018 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#include <mee/uart.h>

#ifdef __MEE_DT_UART_0_HANDLE
/* This implementation serves as a small shim that interfaces with the first
 * UART on a system. */
int mee_tty_putc(unsigned char c)
{
    if (c == '\n') {
        int out = mee_uart_putc(__MEE_DT_UART_0_HANDLE, '\r');
        if (out != 0)
            return out;
    }
    return mee_uart_putc(__MEE_DT_UART_0_HANDLE, c);
}
#else
/* This implementation of putc doesn't actually do anything, it's just there to
 * provide a shim that eats all the characters so we can ensure that everything
 * can link to mee_tty_putc. */
int nop_putc(unsigned char c) __attribute__((section(".text.mee.nop.putc")));
int nop_putc(unsigned char c) { return -1; }
int mee_tty_putc(unsigned char c) __attribute__((weak, alias("nop_putc")));
#endif
