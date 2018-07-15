/* Copyright 2018 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#ifndef MEE__CLOCK_H
#define MEE__CLOCK_H

struct mee_clock;

#include <stddef.h>

/* The generic interface to all clocks. */
struct __mee_clock_vtable {
    long (*get_rate_hz)(const struct mee_clock *clk);
    long (*set_rate_hz)(struct mee_clock *clk, long hz);
};

typedef void (*mee_clock_rate_change_callback)(void *priv);

struct mee_clock {
    const struct __mee_clock_vtable *vtable;
    mee_clock_rate_change_callback rate_change_callback;
    void *rate_change_callback_priv;
};

/* Returns the current rate of the given clock. */
inline long mee_clock_get_rate_hz(const struct mee_clock *clk) { return clk->vtable->get_rate_hz(clk); }

/* Attempts to set the current rate of the given clock to as close as possible
 * to the given rate.  Returns the actual value that's been selected, which
 * could be anything! */
inline long mee_clock_set_rate_hz(struct mee_clock *clk, long hz)
{
    long out = clk->vtable->set_rate_hz(clk, hz);
    if (clk->rate_change_callback != NULL)
        clk->rate_change_callback(clk->rate_change_callback_priv);
    return out;
}

/* Registers a callback that must be called whenever. */
inline void mee_clock_register_rate_change_callback(struct mee_clock *clk, mee_clock_rate_change_callback cb, void *priv)
{
    clk->rate_change_callback = cb;
    clk->rate_change_callback_priv = priv;
}

#endif
