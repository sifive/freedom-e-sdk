/* Copyright 2018 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#include <mee/drivers/sifive,fe310-g000,pll.h>

#define __MEE_DRIVER_SIFIVE_FE310_G000_PLL_R        0x00000003UL
#define __MEE_DRIVER_SIFIVE_FE310_G000_PLL_F        0x000001F0UL
#define __MEE_DRIVER_SIFIVE_FE310_G000_PLL_Q        0x00000600UL
#define __MEE_DRIVER_SIFIVE_FE310_G000_PLL_SEL      0x00010000UL

long __mee_driver_sifive_fe310_g000_pll_get_rate_hz(const struct mee_clock *clock)
{
    return -1;
}

long __mee_driver_sifive_fe310_g000_pll_set_rate_hz(struct mee_clock *clock, long rate)
{
    return -1;
}
