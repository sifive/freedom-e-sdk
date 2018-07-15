/* Copyright 2018 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#ifndef MEE__COMPILER_H
#define MEE__COMPILER_H

#define MEE_DECLARE_VTABLE(type)                        \
    asm(".weak " #type);                                \
    const struct type type                              \

#endif
