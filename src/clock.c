/* Copyright 2018 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#include <mee/clock.h>

extern inline long mee_clock_get_rate_hz(const struct mee_clock *clk);
extern inline long mee_clock_set_rate_hz(struct mee_clock *clk, long hz);
extern inline void mee_clock_register_rate_change_callback(struct mee_clock *clk, mee_clock_rate_change_callback cb, void *priv);
