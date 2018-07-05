/* Copyright 2018 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#ifndef MEE__TTY_H
#define MEE__TTY_H

/* Writes a character to to default output device, which is probably the serial
 * port.  This returns 0 on success, or -1 on failure. */
int mee_tty_putc(unsigned char c);

#endif
