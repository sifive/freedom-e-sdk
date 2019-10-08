/* Copyright 2019 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */
#include <stdio.h>
#include <inttypes.h>   /* for PRIxPTR  */
#include <stdint.h>     /* for uinptr_t */
#include <metal/csr.h>

int main() {
    uintptr_t ms1, ms2;

    /*
     * Using METAL_CPU_GET_CSR() to read csr register using register name,
     * with return value store in ms1. A variable of type uintptr_t is require
     */
    METAL_CPU_GET_CSR(marchid, ms1)

    ms2 = 0xdeadbeef;
    /*
     * Using METAL_CPU_SET_CSR() to write to csr register using register name,
     * with value to write in ms2. A variable of type uintptr_t is require
     */
    METAL_CPU_SET_CSR(mscratch, ms2);

    /* Reading mscratch csr register with return value store in ms2 */
    METAL_CPU_GET_CSR(mscratch, ms2); 

    /* Print out what was read back. */
    /* Note due uinptr_t can be int or long macro PRIxPTR needed for printf */
    printf("read 0x%" PRIxPTR ", write 0x%x, read 0x%" PRIxPTR "\n", ms1, 0xdeadbeef, ms2);

    ms1 = 0xdeafabba;
    /*
     * Using METAL_CPU_SET_CSR() to write to csr register using register oftset,
     * with value to write in ms1. A variable of type uintptr_t is require
     */
    METAL_CPU_SET_CSR(0x340, ms1);

    /*
     * Using METAL_CPU_GET_CSR() to read csr register using register offset,
     * with return value store in ms2. A variable of type uintptr_t is require
     */
    METAL_CPU_GET_CSR(0x340, ms2); 

    /* Print out what was written and read back. */
    printf("read write 0x%" PRIxPTR ", read 0x%" PRIxPTR "\n", ms1, ms2);
    return 0;
}

