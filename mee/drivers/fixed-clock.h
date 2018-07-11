/* Copyright 2018 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#ifndef MEE__DRIVERS__FIXED_CLOCK_H
#define MEE__DRIVERS__FIXED_CLOCK_H

#include <mee/clock.h>

struct __mee_driver_fixed_clock {
    struct mee_clock clock;
    long rate;
};

#ifdef __MEE_DT_FIXED_CLOCK_0_HANDLE
extern struct __mee_driver_fixed_clock __mee_driver_fixed_clock_0;
#endif

#endif
