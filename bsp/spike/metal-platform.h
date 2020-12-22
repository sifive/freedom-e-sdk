/* Copyright 2019 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */
/* ----------------------------------- */
/* ----------------------------------- */

#ifndef METAL_PLATFORM_H
#define METAL_PLATFORM_H

/* From clint@2000000 */
#define METAL_RISCV_CLINT0_2000000_BASE_ADDRESS 33554432UL
#define METAL_RISCV_CLINT0_0_BASE_ADDRESS 33554432UL
#define METAL_RISCV_CLINT0_2000000_SIZE 786432UL
#define METAL_RISCV_CLINT0_0_SIZE 786432UL

#define METAL_RISCV_CLINT0
#define METAL_RISCV_CLINT0_MSIP_BASE 0UL
#define METAL_RISCV_CLINT0_MTIMECMP_BASE 16384UL
#define METAL_RISCV_CLINT0_MTIME 49144UL

/* From htif */

#define METAL_UCB_HTIF0

#endif /* METAL_PLATFORM_H*/
