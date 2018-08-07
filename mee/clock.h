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

typedef void (*mee_clock_pre_rate_change_callback)(void *priv);
typedef void (*mee_clock_post_rate_change_callback)(void *priv);

struct mee_clock {
    const struct __mee_clock_vtable *vtable;

    /* Pre-rate change callback */
    mee_clock_pre_rate_change_callback pre_rate_change_callback;
    void *pre_rate_change_callback_priv;

    /* Post-rate change callback */
    mee_clock_post_rate_change_callback post_rate_change_callback;
    void *post_rate_change_callback_priv;
};

/* Returns the current rate of the given clock. */
inline long mee_clock_get_rate_hz(const struct mee_clock *clk) { return clk->vtable->get_rate_hz(clk); }

/* Attempts to set the current rate of the given clock to as close as possible
 * to the given rate.  Returns the actual value that's been selected, which
 * could be anything! */
inline long mee_clock_set_rate_hz(struct mee_clock *clk, long hz)
{
    if(clk->pre_rate_change_callback != NULL)
        clk->pre_rate_change_callback(clk->pre_rate_change_callback_priv);

    long out = clk->vtable->set_rate_hz(clk, hz);

    if (clk->post_rate_change_callback != NULL)
        clk->post_rate_change_callback(clk->post_rate_change_callback_priv);

    return out;
}

/* Registers a callback that must be called before a rate change */
inline void mee_clock_register_pre_rate_change_callback(struct mee_clock *clk, mee_clock_pre_rate_change_callback cb, void *priv)
{
    clk->pre_rate_change_callback = cb;
    clk->pre_rate_change_callback_priv = priv;
}

/* Registers a callback that must be called after a rate change */
inline void mee_clock_register_post_rate_change_callback(struct mee_clock *clk, mee_clock_post_rate_change_callback cb, void *priv)
{
    clk->post_rate_change_callback = cb;
    clk->post_rate_change_callback_priv = priv;
}

#endif
