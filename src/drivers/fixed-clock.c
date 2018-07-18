/* Copyright 2018 SiFive, Inc. */
/* SPDX-License-Identifier: Apache-2.0 */

#include <mee/drivers/fixed-clock.h>
#include <stddef.h>

long __mee_driver_fixed_clock_get_rate_hz(const struct mee_clock *gclk)
{
    const struct __mee_driver_fixed_clock *clk = (void *)gclk;
    return clk->rate;
}

long __mee_driver_fixed_clock_set_rate_hz(struct mee_clock *gclk, long target_hz)
{
    return __mee_driver_fixed_clock_get_rate_hz(gclk);
}
