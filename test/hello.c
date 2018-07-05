/* Copyright 2018 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#include <mee/tty.h>

unsigned char stack[512];

/* The tests need to run without a C library so we set up an extremely minimal
 * C runtime -- in this case it's so minimal that we actually don't rely on
 * anything but the stack pointer! */
asm(
".global _start\n"
"_start:\n"
"    la sp, stack + 512\n"
"    andi sp, sp, -16\n"
"    call main\n"
);

void main() {
    mee_tty_putc('H');
    mee_tty_putc('e');
    mee_tty_putc('l');
    mee_tty_putc('l');
    mee_tty_putc('o');
    mee_tty_putc(' ');
    mee_tty_putc('W');
    mee_tty_putc('o');
    mee_tty_putc('r');
    mee_tty_putc('l');
    mee_tty_putc('d');
    mee_tty_putc('!');
    mee_tty_putc('\n');
}
