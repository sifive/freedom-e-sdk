/* Copyright 2018 SiFive, Inc. */
/* SPDX-License-Identifier: Apache-2.0 */

#include <mee/drivers/fixed-clock.h>
#include <stddef.h>

static long get_rate_hz(const struct mee_clock *gclk)
{
    const struct __mee_driver_fixed_clock *clk = (void *)gclk;
    return clk->rate;
}

static long set_rate_hz(struct mee_clock *gclk, long hz)
{
    const struct __mee_driver_fixed_clock *clk = (void *)gclk;
    return clk->rate;
}

#ifdef __MEE_DT_FIXED_CLOCK_0_HANDLE
struct __mee_driver_fixed_clock __mee_driver_fixed_clock_0 = {
    .clock.get_rate_hz               = &get_rate_hz,
    .clock.set_rate_hz               = &set_rate_hz,
    .clock.rate_change_callback      = NULL,
    .clock.rate_change_callback_priv = NULL,
    .rate                            = __MEE_DT_FIXED_CLOCK_0_RATE,
};
#endif
