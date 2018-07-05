/* Copyright 2018 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

/* This implementation of putc doesn't actually do anything, it's just there to
 * provide a shim that eats all the characters so we can ensure that everything
 * can link to mee_tty_putc. */
int nop_putc(unsigned char c) __attribute__((section(".text.mee.nop.putc")));
int nop_putc(unsigned char c) { return -1; }
int mee_tty_putc(unsigned char c) __attribute__((weak, alias("nop_putc")));
