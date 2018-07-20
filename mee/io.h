/* Copyright 2018 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#ifndef MEE__IO_H
#define MEE__IO_H

/* This macro enforces that the compiler will not elide the given access. */
#define __MEE_ACCESS_ONCE(x) (*(typeof(*x) volatile *)(x))

/* Allows users to specify arbitrary fences. */
#define __MEE_IO_FENCE(pred, succ) __asm__ volatile ("fence " #pred "," #succ ::: "memory");

/* Types that explicitly describe an address as being used for memory-mapped
 * IO.  These should only be accessed via __MEE_ACCESS_ONCE. */
typedef unsigned char  mee_io_u8;
typedef unsigned short mee_io_u16;
typedef unsigned int   mee_io_u32;
#if __riscv_xlen >= 64
typedef unsigned long  mee_io_u64;
#endif

#endif
