.section .text.metal.rvoffload.enter
.global _prologue
_prologue:
.option push
.option norelax
  la gp, __global_pointer$
.option pop
#if __riscv_xlen == 64
  addi sp, sp, -8
  sd ra, (sp)
  call main
  ld ra, (sp)
  addi sp, sp, 8
#else
  addi sp, sp, -4
  sw ra, (sp)
  call main
  lw ra, (sp)
  addi sp, sp, 4
#endif
  ret
