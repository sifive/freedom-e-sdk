/* Copyright 2018 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#include <mee/drivers/sifive,fe310-g000,hfxosc.h>

#define CONFIG_ENABLE  0x40000000UL
#define CONFIG_READY   0x80000000UL

long __mee_driver_sifive_fe310_g000_hfxosc_get_rate_hz(const struct mee_clock *clock)
{
    struct __mee_driver_sifive_fe310_g000_hfxosc *clk = (void *)clock;
    long cfg = clk->config_base->vtable->get_reg(clk->config_base, clk->config_offset);
    if (cfg & CONFIG_ENABLE == 0)
        return -1;
    if (cfg & CONFIG_READY == 0)
        return -1;
    return mee_clock_get_rate_hz(clk->ref);
}

long __mee_driver_sifive_fe310_g000_hfxosc_set_rate_hz(struct mee_clock *clock, long rate)
{
    return __mee_driver_sifive_fe310_g000_hfxosc_get_rate_hz(clock);
}
