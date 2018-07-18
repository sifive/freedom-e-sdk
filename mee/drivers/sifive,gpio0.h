/* Copyright 2018 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#ifndef MEE__DRIVERS__SIFIVE_GPIO0_H
#define MEE__DRIVERS__SIFIVE_GPIO0_H

struct __mee_driver_sifive_gpio0;

long __mee_driver_sifive_gpio0_enable_io(const struct __mee_driver_sifive_gpio0 *, long source, long dest);

struct __mee_driver_vtable_sifive_gpio0 {
    long (*enable_io)(const struct __mee_driver_sifive_gpio0 *, long source, long dest);
};

MEE_DECLARE_VTABLE(__mee_driver_vtable_sifive_gpio0) = {
    .enable_io = __mee_driver_sifive_gpio0_enable_io,
};

struct __mee_driver_sifive_gpio0 {
    const struct __mee_driver_vtable_sifive_gpio0 *vtable;
    const long base;
    const long size;
};

#endif
