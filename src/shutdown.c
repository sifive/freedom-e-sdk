/* Copyright 2018 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#include <mee/shutdown.h>

void mee_shutdown(int code)
{
    while (1) {
      __asm__ volatile ("nop");
    }
}
