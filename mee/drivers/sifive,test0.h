/* Copyright 2018 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#ifndef MEE__DRIVERS__SIFIVE_TEST0_H
#define MEE__DRIVERS__SIFIVE_TEST0_H

#include <mee/compiler.h>
#include <mee/shutdown.h>

struct __mee_driver_vtable_sifive_test0 {
    const struct mee_shutdown_vtable shutdown;
};

struct __mee_driver_sifive_test0;

void __mee_driver_sifive_test0_exit(const struct mee_shutdown *test, int code) __attribute__((noreturn));

MEE_DECLARE_VTABLE(__mee_driver_vtable_sifive_test0) = {
    .shutdown.exit       = &__mee_driver_sifive_test0_exit,
};

struct __mee_driver_sifive_test0 {
    struct mee_shutdown shutdown;
    const struct __mee_driver_vtable_sifive_test0 *vtable;
    const unsigned long base;
    const unsigned long size;
};


#endif
