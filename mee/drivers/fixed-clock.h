/* Copyright 2018 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#ifndef MEE__DRIVERS__FIXED_CLOCK_H
#define MEE__DRIVERS__FIXED_CLOCK_H

struct __mee_driver_fixed_clock;

#include <mee/compiler.h>
#include <mee/clock.h>

struct __mee_driver_vtable_fixed_clock {
    struct __mee_clock_vtable clock;
};

inline long __mee_driver_fixed_clock_get_rate_hz(const struct mee_clock *gclk);
inline long __mee_driver_fixed_clock_set_rate_hz(struct mee_clock *gclk, long target_hz);

MEE_DECLARE_VTABLE(__mee_driver_vtable_fixed_clock) = {
    .clock.get_rate_hz = __mee_driver_fixed_clock_get_rate_hz,
    .clock.set_rate_hz = __mee_driver_fixed_clock_set_rate_hz,
};

struct __mee_driver_fixed_clock {
    const struct __mee_driver_vtable_fixed_clock *vtable;
    struct mee_clock clock;
    long rate;
};


inline long __mee_driver_fixed_clock_get_rate_hz(const struct mee_clock *gclk)
{
    const struct __mee_driver_fixed_clock *clk = (void *)gclk;
    return clk->rate;
}

inline long __mee_driver_fixed_clock_set_rate_hz(struct mee_clock *gclk, long target_hz)
{
    const struct __mee_driver_fixed_clock *clk = (void *)gclk;
    return clk->rate;
}


#endif
