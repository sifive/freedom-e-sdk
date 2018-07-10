/* Copyright 2018 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#ifndef MEE__SHUTDOWN_H
#define MEE__SHUTDOWN_H

/* The public MEE shutdown interface, which allows us to turn off the machine
 * when posible. */
void mee_shutdown(int code) __attribute__((noreturn));

#endif
