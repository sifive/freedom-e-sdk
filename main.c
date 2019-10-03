/* Copyright 2019 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */
#include <stdio.h>
#include <stdint.h>
#include <metal/csr.h>

int main() {
uintptr_t ms1, ms2;
    METAL_CPU_GET_CSR(marchid, ms1)
    ms2 = 0xdeadbeef;
    METAL_CPU_SET_CSR(mscratch, ms2);
    METAL_CPU_GET_CSR(mscratch, ms2); 
    printf("read 0x%x, write 0x%x, read 0x%x\n", ms1, 0xdeadbeef, ms2);
    ms1 = 0xdeafabba;
    METAL_CPU_SET_CSR(0x340, ms1);
    METAL_CPU_GET_CSR(0x340, ms2); 
    printf("read write 0x%x, read 0x%x\n", ms1, ms2);
    return 0;
}

