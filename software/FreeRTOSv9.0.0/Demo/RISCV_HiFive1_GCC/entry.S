// See LICENSE for license details

#ifndef ENTRY_S
#define ENTRY_S

#include "encoding.h"
#include "sifive/bits.h"

  .section      .text.entry	
  .align 2
  .global trap_entry

/* Macro for saving task context */
.macro pushREGFILE
	addi sp, sp, -32*REGBYTES

	STORE x1, 1*REGBYTES(sp)
	STORE x2, 2*REGBYTES(sp)
	STORE x3, 3*REGBYTES(sp)
	STORE x4, 4*REGBYTES(sp)
	STORE x5, 5*REGBYTES(sp)
	STORE x6, 6*REGBYTES(sp)
	STORE x7, 7*REGBYTES(sp)
	STORE x8, 8*REGBYTES(sp)
	STORE x9, 9*REGBYTES(sp)
	STORE x10, 10*REGBYTES(sp)
	STORE x11, 11*REGBYTES(sp)
	STORE x12, 12*REGBYTES(sp)
	STORE x13, 13*REGBYTES(sp)
	STORE x14, 14*REGBYTES(sp)
	STORE x15, 15*REGBYTES(sp)
	STORE x16, 16*REGBYTES(sp)
	STORE x17, 17*REGBYTES(sp)
	STORE x18, 18*REGBYTES(sp)
	STORE x19, 19*REGBYTES(sp)
	STORE x20, 20*REGBYTES(sp)
	STORE x21, 21*REGBYTES(sp)
	STORE x22, 22*REGBYTES(sp)
	STORE x23, 23*REGBYTES(sp)
	STORE x24, 24*REGBYTES(sp)
	STORE x25, 25*REGBYTES(sp)
	STORE x26, 26*REGBYTES(sp)
	STORE x27, 27*REGBYTES(sp)
	STORE x28, 28*REGBYTES(sp)
	STORE x29, 29*REGBYTES(sp)
	STORE x30, 30*REGBYTES(sp)
	STORE x31, 31*REGBYTES(sp)

	csrr a0, mcause
	csrr a1, mepc
	mv a2, sp
.endm

/* Macro for saving task context */
.macro popREGFILE
csrw mepc, a0

  # Remain in M-mode after mret
  li t0, MSTATUS_MPP
  csrs mstatus, t0

  LOAD x1, 1*REGBYTES(sp)
  LOAD x2, 2*REGBYTES(sp)
  LOAD x3, 3*REGBYTES(sp)
  LOAD x4, 4*REGBYTES(sp)
  LOAD x5, 5*REGBYTES(sp)
  LOAD x6, 6*REGBYTES(sp)
  LOAD x7, 7*REGBYTES(sp)
  LOAD x8, 8*REGBYTES(sp)
  LOAD x9, 9*REGBYTES(sp)
  LOAD x10, 10*REGBYTES(sp)
  LOAD x11, 11*REGBYTES(sp)
  LOAD x12, 12*REGBYTES(sp)
  LOAD x13, 13*REGBYTES(sp)
  LOAD x14, 14*REGBYTES(sp)
  LOAD x15, 15*REGBYTES(sp)
  LOAD x16, 16*REGBYTES(sp)
  LOAD x17, 17*REGBYTES(sp)
  LOAD x18, 18*REGBYTES(sp)
  LOAD x19, 19*REGBYTES(sp)
  LOAD x20, 20*REGBYTES(sp)
  LOAD x21, 21*REGBYTES(sp)
  LOAD x22, 22*REGBYTES(sp)
  LOAD x23, 23*REGBYTES(sp)
  LOAD x24, 24*REGBYTES(sp)
  LOAD x25, 25*REGBYTES(sp)
  LOAD x26, 26*REGBYTES(sp)
  LOAD x27, 27*REGBYTES(sp)
  LOAD x28, 28*REGBYTES(sp)
  LOAD x29, 29*REGBYTES(sp)
  LOAD x30, 30*REGBYTES(sp)
  LOAD x31, 31*REGBYTES(sp)

  addi sp, sp, 32*REGBYTES
  mret
.endm

#define INT_MASK 0x7FFFFFFF

/* When trap is an interrupt, this function is called */
interrupt:
	STORE   t1,1*REGBYTES(sp)

	li      t1,INT_MASK
	and     t0,t0,t1
	li      t1, 0x7
	bne     t0,t1, NON_TIMER_IRQ

	LOAD    t0, 0x0(sp)
	LOAD    t1, 1*REGBYTES(sp)
	addi	sp, sp, 3*REGBYTES

	/* Interupt is timer interrupt */
	j		TIMER_CMP_INT
	mret

	/* Interupt is not m-time  */
NON_TIMER_IRQ:
	LOAD    t0, 0x0(sp)
	LOAD    t1, 1*REGBYTES(sp)
	addi	sp, sp, 3*REGBYTES
	nop
	pushREGFILE
	jal handle_interrupt
	popREGFILE //j portRESTORE_CONTEXT


/* For when a trap is fired */
trap_entry:
	/* Check for interrupt */
	addi	sp, sp, -REGBYTES*3
	STORE	t0, 0x0(sp)
	csrr	t0, mcause
	blt	t0,x0,interrupt
	LOAD	t0, 0x0(sp)
	addi	sp, sp, 3*REGBYTES

	/* synchronous trap*/
	pushREGFILE
	jal ulSyscallTrap
	popREGFILE


.weak handle_interrupt
handle_interrupt:
1:
  j 1b
	
#endif
