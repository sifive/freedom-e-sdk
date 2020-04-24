.text

.globl getcycles
.align 2
getcycles:
#if __riscv_xlen == 64
    csrr a0, mcycle
#elif __riscv_xlen == 32
    csrr a1, mcycleh
    csrr a0, mcycle
    csrr a2, mcycleh
    bne a1, a2, getcycles
#endif
    ret
.size getcycles,.-getcycles
