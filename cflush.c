/* Copyright 2019 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#include <stdio.h>
#include <metal/timer.h>

int data = 0xABBACADA;

static inline void cache_flush()
{
    __asm__ __volatile__ (".word 0xfc000073" : : : "memory"); // CFLUSH.D.L1
    __asm__ __volatile__ ("fence w ,r" ::: "memory");         // FENCE
}

int main (void)
{
    int i, test, dummy;
    unsigned long long mc_count0, mc_count1;
    unsigned long long mc[2];

    // This example demo how to use cflush (Data) L1 and use FENCE to ensure flush complete
    test = data;
    for (i = 0; i < 2; i++) {
        metal_timer_get_cyclecount(0, &mc_count0);
        test = data;
        dummy = test++; // Ensure load actually complete
        metal_timer_get_cyclecount(0, &mc_count1);
        cache_flush();
        mc[i] = mc_count1 - mc_count0;
    }

    if (mc[1] <= mc[0]) {
        printf("CFLUSH failed, pre-mc %d post-mc %d\n", mc[0], mc[1]);
        return 1;
    }

    // return
    return 0;
}

