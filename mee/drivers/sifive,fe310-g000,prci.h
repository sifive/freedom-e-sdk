/* Copyright 2018 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#ifndef MEE__DRIVERS__SIFIVE_FE310_G000_PRCI_H
#define MEE__DRIVERS__SIFIVE_FE310_G000_PRCI_H

#include <mee/compiler.h>
#include <mee/io.h>

struct __mee_driver_sifive_fe310_g000_prci;

long __mee_driver_sifive_fe310_g000_prci_get_reg(const struct __mee_driver_sifive_fe310_g000_prci *, long offset);
long __mee_driver_sifive_fe310_g000_prci_set_reg(const struct __mee_driver_sifive_fe310_g000_prci *, long offset, long value);

struct __mee_driver_vtable_sifive_fe310_g000_prci {
    long (*get_reg)(const struct __mee_driver_sifive_fe310_g000_prci *, long offset);
    long (*set_reg)(const struct __mee_driver_sifive_fe310_g000_prci *, long offset, long value);
};

MEE_DECLARE_VTABLE(__mee_driver_vtable_sifive_fe310_g000_prci) = {
    .get_reg = __mee_driver_sifive_fe310_g000_prci_get_reg,
    .set_reg = __mee_driver_sifive_fe310_g000_prci_set_reg,
};

struct __mee_driver_sifive_fe310_g000_prci {
    const struct __mee_driver_vtable_sifive_fe310_g000_prci *vtable;
    const mee_io_u32 *base;
    const long size;
};

#endif

