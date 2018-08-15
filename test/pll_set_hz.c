/* Copyright 2018 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#include <stdio.h>
#include <mee/clock.h>

#define PLL_MIN_OUT 16000000
#define PLL_MAX_OUT 320000000

void main() {
#ifdef __ME_DT_SIFIVE_FE310_G000_PLL_HANDLE
    struct mee_clock * pll = __ME_DT_SIFIVE_FE310_G000_PLL_HANDLE;

    printf("Test harness for FE310-G000 PLL Set Frequency\n\n");
    printf("Boot frequency is: %ld\n", mee_clock_get_rate_hz(pll));

    for(long requested = PLL_MIN_OUT; requested <= PLL_MAX_OUT; requested += 16000000)
    {
        /* fflush before we change clock rates */
        fflush(stdout);

        long actual = mee_clock_set_rate_hz(pll, requested);

        printf("Requested %9ld Hz, Actual %9ld Hz\n", requested, actual);
    }

    printf("--- Complete ---\n");
#else
    printf("Unable to run fe310-g000 PLL test case as there is no PLL\n");
#endif
}
