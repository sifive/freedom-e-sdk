/* Copyright 2018 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#include <mee/drivers/sifive,fe310-g000,pll.h>
#include <mee/compiler.h>

#define PLL_R        0x00000003UL
#define PLL_F        0x000001F0UL
#define PLL_Q        0x00000600UL
#define PLL_SEL      0x00010000UL
#define PLL_REFSEL   0x00020000UL
#define PLL_BYPASS   0x00040000UL
#define PLL_LOCK     0x80000000UL

#define DIV_DIV      0x0000003FUL
#define DIV_1        0x00000100UL

long __mee_driver_sifive_fe310_g000_pll_get_rate_hz(const struct mee_clock *clock)
{
    struct __mee_driver_sifive_fe310_g000_pll *clk = (void *)clock;
    long cfg = clk->config_base->vtable->get_reg(clk->config_base, clk->config_offset);
    long div = clk->config_base->vtable->get_reg(clk->divider_base, clk->divider_offset);

    /* At the end of the PLL there's one big mux: it either selects the HFROSC
     * (bypassing the PLL entirely) or uses the PLL. */
    if (MEE_GET_FIELD(cfg, PLL_SEL) == 0)
        return mee_clock_get_rate_hz(clk->pllsel0);

    /* There's a clock mux before the PLL that selects between the HFROSC adn
     * the HFXOSC as the PLL's input clock. */
    long ref_hz = mee_clock_get_rate_hz(MEE_GET_FIELD(cfg, PLL_REFSEL) ? clk->pllsel0 : clk->pllref);

    /* It's possible to bypass the PLL, which is an internal bpyass.  This
     * still obays the PLL's input clock mu. */
    if (MEE_GET_FIELD(cfg, PLL_BYPASS))
        return ref_hz;

    /* Logically the PLL is a three stage div-mul-div. */
    long div_r = MEE_GET_FIELD(cfg, PLL_R) + 1;
    long mul_f = 1 << MEE_GET_FIELD(cfg, PLL_F);
    if (MEE_GET_FIELD(cfg, PLL_Q) == 0)
        return -1;
    long div_q = 1 << MEE_GET_FIELD(cfg, PLL_Q);

    /* In addition to the dividers inherent in the PLL, there's an additional
     * clock divider that lives after the PLL and lets us pick a more
     * interesting range of frequencies. */
    long pllout = (((ref_hz / div_r) * mul_f) / div_q);
    if (MEE_GET_FIELD(div, DIV_1))
        return pllout;

    return pllout / (2 << MEE_GET_FIELD(div, DIV_DIV));
}

long __mee_driver_sifive_fe310_g000_pll_set_rate_hz(struct mee_clock *clock, long rate)
{
    return __mee_driver_sifive_fe310_g000_pll_get_rate_hz(clock);
}
