/* Copyright 2018 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#ifndef MEE__DRIVERS__SIFIVE_FE310_G000_HFROSC_H
#define MEE__DRIVERS__SIFIVE_FE310_G000_HFROSC_H

#include <mee/drivers/sifive,fe310-g000,prci.h>
#include <mee/compiler.h>
#include <mee/clock.h>
#include <mee/io.h>

long __mee_driver_sifive_fe310_g000_hfrosc_get_rate_hz(const struct mee_clock *clock);
long __mee_driver_sifive_fe310_g000_hfrosc_set_rate_hz(struct mee_clock *clock, long rate);

struct __mee_driver_vtable_sifive_fe310_g000_hfrosc {
    struct __mee_clock_vtable clock;
};

MEE_DECLARE_VTABLE(__mee_driver_vtable_sifive_fe310_g000_hfrosc) = {
    .clock.get_rate_hz = &__mee_driver_sifive_fe310_g000_hfrosc_get_rate_hz,
    .clock.set_rate_hz = &__mee_driver_sifive_fe310_g000_hfrosc_set_rate_hz,
};

struct __mee_driver_sifive_fe310_g000_hfrosc {
    struct mee_clock clock;
    const struct __mee_driver_vtable_sifive_fe310_g000_hfrosc *vtable;
    const struct mee_clock *ref;
    const struct __mee_driver_sifive_fe310_g000_prci *config_base;
    const long config_offset;
};

#endif
