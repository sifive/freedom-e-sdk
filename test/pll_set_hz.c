/* Copyright 2018 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#include <stdio.h>
#include <mee/clock.h>

#define PLL_MIN_OUT 16000000
#define PLL_MAX_OUT 320000000

void main() {
    struct mee_clock * pll = __ME_DT_SIFIVE_FE310_G000_PLL_HANDLE;

    /* Set PLL to start running off PLL clock */
    mee_clock_set_rate_hz(pll, 16000000);

    printf("Test harness for FE310-G000 PLL Set Frequency\n\n");

    for(long requested = PLL_MIN_OUT; requested <= PLL_MAX_OUT; requested += 16000000)
    {
        /* fflush before we change clock rates */
        fflush(stdout);

        long actual = mee_clock_set_rate_hz(pll, requested);

        printf("Requested %9ld Hz, Actual %9ld Hz\n", requested, actual);
    }

    printf("--- Complete ---\n");
}
