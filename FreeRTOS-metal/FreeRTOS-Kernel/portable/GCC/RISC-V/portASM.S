/*
 * FreeRTOS Kernel V10.2.1
 * Copyright (C) 2019 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 4 spaces!
 */

/*
 * The FreeRTOS kernel's RISC-V port is split between the the code that is
 * common across all currently supported RISC-V chips (implementations of the
 * RISC-V ISA), and code which tailors the port to a specific RISC-V chip:
 *
 * + The code that is common to all RISC-V chips is implemented in
 *   FreeRTOS\Source\portable\GCC\RISC-V-RV32\portASM.S.  There is only one
 *   portASM.S file because the same file is used no matter which RISC-V chip is
 *   in use.
 *
 * + The code that tailors the kernel's RISC-V port to a specific RISC-V
 *   chip is implemented in freertos_risc_v_chip_specific_extensions.h.  There
 *   is one freertos_risc_v_chip_specific_extensions.h that can be used with any
 *   RISC-V chip that both includes a standard CLINT and does not add to the
 *   base set of RISC-V registers.  There are additional
 *   freertos_risc_v_chip_specific_extensions.h files for RISC-V implementations
 *   that do not include a standard CLINT or do add to the base set of RISC-V
 *   registers.
 *
 * CARE MUST BE TAKEN TO INCLDUE THE CORRECT
 * freertos_risc_v_chip_specific_extensions.h HEADER FILE FOR THE CHIP
 * IN USE.  To include the correct freertos_risc_v_chip_specific_extensions.h
 * header file ensure the path to the correct header file is in the assembler's
 * include path.
 *
 * This freertos_risc_v_chip_specific_extensions.h is for use on RISC-V chips
 * that include a standard CLINT and do not add to the base set of RISC-V
 * registers.
 *
 */
#include "portISR_CONTEXT.h"

#include "freertos_risc_v_chip_specific_extensions.h"

/* Check the freertos_risc_v_chip_specific_extensions.h and/or command line
definitions. */
#ifndef portasmHAS_CLINT
	#error portasmHAS_CLINT must be defined in freertos_risc_v_chip_specific_extensions.h.
#endif

#ifndef portHANDLE_INTERRUPT
	#error portHANDLE_INTERRUPT must be defined to the function to be called to handle external/peripheral interrupts.
#endif

#ifndef portHANDLE_EXCEPTION
	#error portHANDLE_EXCEPTION must be defined to the function to be called to handle execption.
#endif

.global xPortStartFirstTask
.global freertos_risc_v_trap_handler
.global pxPortInitialiseStack
.extern pxCurrentTCB
.extern vTaskSwitchContext
.extern pullMachineTimerCompareRegister
.extern pullNextTime
.extern uxTimerIncrementsForOneTick /* size_t type so 32-bit on 32-bit core and 64-bits on 64-bit core. */
.extern xISRStackTop

#if( configUSE_SEGGER_SYSTEMVIEW == 1 )
# ifndef SYSVIEW_RECORD_ENTER_ISR
	#error SYSVIEW_RECORD_ENTER_ISR must be defined to the function to be called when you enter into ISR. In basic usage it is define to SEGGER_SYSVIEW_RecordEnterISR 
# endif
# ifndef SYSVIEW_RECORD_EXIT_ISR
	#error SYSVIEW_RECORD_EXIT_ISR must be defined to the function to be called when you enter into ISR. In basic usage it is define to SEGGER_SYSVIEW_RecordExitISR 
# endif
# ifndef SYSVIEW_RECORD_EXIT_ISR_TO_SCHEDULER
	#error SYSVIEW_RECORD_EXIT_ISR_TO_SCHEDULER must be defined to the function to be called when you enter into ISR. In basic usage it is define to SEGGER_SYSVIEW_RecordExitISRToScheduler 
# endif
#endif

/*------------------------------------------------------------------*/
/*
 * Register		ABI Name	Description						Saver
 * x0			zero		Hard-wired zero					-
 * x1			ra			Return address					Caller
 * x2			sp			Stack pointer					Callee
 * x3			gp			Global pointer					-
 * x4			tp			Thread pointer					-
 * x5-7			t0-2		Temporaries						Caller
 * x8			s0/fp		Saved register/Frame pointer	Callee
 * x9			s1			Saved register					Callee
 * x10-11		a0-1		Function arguments/return values Caller
 * x12-17		a2-7		Function arguments				Caller
 * x18-27		s2-11		Saved registers					Callee
 * x28-31		t3-6		Temporaries						Caller
 */

/*-----------------------------------------------------------------*/

/*************************************************************/
.macro portSAVE_Tx_REG
	/* x5-7			t0-2		Temporaries */
	store_x  x5,  PORT_CONTEXT_xOFFSET(5)(sp)
	store_x  x6,  PORT_CONTEXT_xOFFSET(6)(sp)
	store_x  x7,  PORT_CONTEXT_xOFFSET(7)(sp)
	/* x28-31		t3-6		Temporaries */
	store_x  x28, PORT_CONTEXT_xOFFSET(28)(sp)
	store_x  x29, PORT_CONTEXT_xOFFSET(29)(sp)
	store_x  x30, PORT_CONTEXT_xOFFSET(30)(sp)
	store_x  x31, PORT_CONTEXT_xOFFSET(31)(sp)
	.endm

.macro portSAVE_Ax_REG
	/* x10-11		a0-7		Function arguments */
	store_x  x10, PORT_CONTEXT_xOFFSET(10)(sp)
	store_x  x11, PORT_CONTEXT_xOFFSET(11)(sp)
	store_x  x12, PORT_CONTEXT_xOFFSET(12)(sp)
	store_x  x13, PORT_CONTEXT_xOFFSET(13)(sp)
	store_x  x14, PORT_CONTEXT_xOFFSET(14)(sp)
	store_x  x15, PORT_CONTEXT_xOFFSET(15)(sp)
	store_x  x16, PORT_CONTEXT_xOFFSET(16)(sp)
	store_x  x17, PORT_CONTEXT_xOFFSET(17)(sp)
	.endm

.macro portSAVE_S1_S11_REG
	/* x9			s1			Saved register */
	store_x  x9,  PORT_CONTEXT_xOFFSET(9)(sp)
	/* x18-27		s2-11		Saved registers */
	store_x  x18, PORT_CONTEXT_xOFFSET(18)(sp)
	store_x  x19, PORT_CONTEXT_xOFFSET(19)(sp)
	store_x  x20, PORT_CONTEXT_xOFFSET(20)(sp)
	store_x  x21, PORT_CONTEXT_xOFFSET(21)(sp)
	store_x  x22, PORT_CONTEXT_xOFFSET(22)(sp)
	store_x  x23, PORT_CONTEXT_xOFFSET(23)(sp)
	store_x  x24, PORT_CONTEXT_xOFFSET(24)(sp)
	store_x  x25, PORT_CONTEXT_xOFFSET(25)(sp)
	store_x  x26, PORT_CONTEXT_xOFFSET(26)(sp)
	store_x  x27, PORT_CONTEXT_xOFFSET(27)(sp)
	.endm

.macro portSAVE_MAIN_REG
	/* x1 to x31 need to be saved */
	store_x  x1,  PORT_CONTEXT_xOFFSET(1)(sp)
	/* x2 Should be save after this macro */
	/* x3			gp			Global pointer */
	store_x  x3,  PORT_CONTEXT_xOFFSET(3)(sp)
	/* x4			tp			Thread pointer */
	store_x  x4,  PORT_CONTEXT_xOFFSET(4)(sp)
	/* x8			s0/fp		Saved register/Frame pointer */
	store_x  x8,  PORT_CONTEXT_xOFFSET(8)(sp)

	portasmSAVE_ADDITIONAL_REGISTERS	/* Defined in freertos_risc_v_chip_specific_extensions.h to save any registers unique to the RISC-V implementation. */
	.endm

.macro portSAVE_MACHINE_SATE
	portSAVE_S1_S11_REG
    csrr s2, mcause
	csrr s3, mepc
	csrr s4, mstatus		/* Required for MPIE bit. */

	store_x s2, PORT_CONTEXT_mcauseOFFSET(sp)
	store_x s3, PORT_CONTEXT_mepcOFFSET(sp)
	store_x s4, PORT_CONTEXT_mstatusOFFSET(sp)
	.endm

/*************************************************************/
.macro portRESTORE_Tx_REG
	/* x5-7			t0-2		Temporaries */
	load_x  x5,  PORT_CONTEXT_xOFFSET(5)(sp)
	load_x  x6,  PORT_CONTEXT_xOFFSET(6)(sp)
	load_x  x7,  PORT_CONTEXT_xOFFSET(7)(sp)
	/* x28-31		t3-6		Temporaries */
	load_x  x28, PORT_CONTEXT_xOFFSET(28)(sp)
	load_x  x29, PORT_CONTEXT_xOFFSET(29)(sp)
	load_x  x30, PORT_CONTEXT_xOFFSET(30)(sp)
	load_x  x31, PORT_CONTEXT_xOFFSET(31)(sp)
	.endm

.macro portRESTORE_Ax_REG
	/* x10-11		a0-7		Function arguments */
	load_x  x10, PORT_CONTEXT_xOFFSET(10)(sp)
	load_x  x11, PORT_CONTEXT_xOFFSET(11)(sp)
	load_x  x12, PORT_CONTEXT_xOFFSET(12)(sp)
	load_x  x13, PORT_CONTEXT_xOFFSET(13)(sp)
	load_x  x14, PORT_CONTEXT_xOFFSET(14)(sp)
	load_x  x15, PORT_CONTEXT_xOFFSET(15)(sp)
	load_x  x16, PORT_CONTEXT_xOFFSET(16)(sp)
	load_x  x17, PORT_CONTEXT_xOFFSET(17)(sp)
	.endm

.macro portRESTORE_S1_S11_REG
	/* x9			s1			Saved register */
	load_x  x9,  PORT_CONTEXT_xOFFSET(9)(sp)
	/* x18-26		s2-10		Saved registers */
	load_x  x18, PORT_CONTEXT_xOFFSET(18)(sp)
	load_x  x19, PORT_CONTEXT_xOFFSET(19)(sp)
	load_x  x20, PORT_CONTEXT_xOFFSET(20)(sp)
	load_x  x21, PORT_CONTEXT_xOFFSET(21)(sp)
	load_x  x22, PORT_CONTEXT_xOFFSET(22)(sp)
	load_x  x23, PORT_CONTEXT_xOFFSET(23)(sp)
	load_x  x24, PORT_CONTEXT_xOFFSET(24)(sp)
	load_x  x25, PORT_CONTEXT_xOFFSET(25)(sp)
	load_x  x26, PORT_CONTEXT_xOFFSET(26)(sp)
	load_x  x27, PORT_CONTEXT_xOFFSET(27)(sp)
	.endm

.macro portRESTORE_MAIN_REG
	portasmRESTORE_ADDITIONAL_REGISTERS	/* Defined in freertos_risc_v_chip_specific_extensions.h to restore any registers unique to the RISC-V implementation. */

	/* x1 to x31 need to be saved */
	load_x  x1,  PORT_CONTEXT_xOFFSET(1)(sp)
	/* x3			gp			Global pointer */
	load_x  x3,  PORT_CONTEXT_xOFFSET(3)(sp)
	/* x4			tp			Thread pointer */
	load_x  x4,  PORT_CONTEXT_xOFFSET(4)(sp)
	/* x8			s0/fp		Saved register/Frame pointer */
	load_x  x8,  PORT_CONTEXT_xOFFSET(8)(sp)
	.endm

.macro portRESTORE_MACHINE_SATE
	load_x  s3, PORT_CONTEXT_mepcOFFSET(sp)
	load_x  s4, PORT_CONTEXT_mstatusOFFSET(sp)
	csrw	mepc, s3
	csrw	mstatus, s4

	portRESTORE_S1_S11_REG
	.endm

/*************************************************************/
.align 8
.func
freertos_risc_v_trap_handler:
	/* We do not know if this is an ASYNC or SYNC
	 * If ASYNC, it is a normal interrupt
	 *  and the stack pointer is assumed good.
	 * else (SYNC)
	 *  We could be here due to a bus fault.
	 */
    csrw	mscratch, t0
    csrr	t0, mcause
    blt  	t0, x0, handle_interrupt

handle_exception:
	/* mscratch = old t0
	 * t0 = mcause
	 * mcause = small number 0..16
	 *  0 Instruction address misaligned
	 *  1 Instruction access fault
	 *  2 Illegal instruction
	 *  3 Breakpoint
	 *  4 Load address misaligned
	 *  5 Load access fault
	 *  6 Store/AMO address misaligned
	 *  7 Store/AMO access fault
	 *  8 Environment call from U-mode
	 *  9 Environment call from S-mode
	 *  10 Reserved
	 *  11 Environment call from M-mode
	 *  12 Instruction page fault
	 *  13 Load page fault
	 *  14 Reserved
	 *  15 Store/AMO page fault
	 *  ≥16 Reserved
	 *
	 * if( mcause between 8 and 11  ) we are good - ecall
	 * else: problem
	 */

	addi	t0, t0, -8
	blt		t0, x0, is_exception /* sp < 8, must be fault */
	addi	t0, t0, -4
	blt		t0, x0, environment_call

is_exception:
	/* restore t0 and save sp in mscratch. */
	csrr	t0, mscratch
    csrw	mscratch, sp
	/* Switch to ISR stack before function call. */
	load_x	sp, xISRStackTop			
	addi	sp, sp, -PORT_CONTEXT_SIZEOF
	portSAVE_MAIN_REG
	portSAVE_Ax_REG
	portSAVE_Tx_REG
	/* portSAVE_S1_S11_REG is called into portSAVE_MACHINE_SATE macro */
	portSAVE_MACHINE_SATE
	/* recover faulting SP from mscratch */
	csrrw	t0, mscratch, t0
	/* SP = X2, so save it */
	store_x	t0, PORT_CONTEXT_xOFFSET(2)(sp)
	/* Execption is treated by freedom metal functions */
	jal portHANDLE_EXCEPTION
infinite_loop:
	ebreak
	j	infinite_loop

environment_call:
	addi	sp, sp, -PORT_CONTEXT_SIZEOF
	portSAVE_MAIN_REG
	portSAVE_Ax_REG
	/* restore t0 */
	csrr	t0, mscratch
	portSAVE_Tx_REG
	/* portSAVE_S1_S11_REG is called into portSAVE_MACHINE_SATE macro */
	portSAVE_MACHINE_SATE
	/* s2 = mcause
	 * s3 = mepc
	 * s4 = mstatus
	 * s9 will be use for pxCurrentTCB
	 * s10 will be use for if we call vTaskSwitchContext
	 * s11 will be use to save sp
	 */
	addi	t0, s3, 4						/* Synchronous so updated exception return address to the instruction after the instruction that generated the exeption. */
	store_x	t0, PORT_CONTEXT_mepcOFFSET(sp) 
	/* Store the value of sp when the interrupt occur */
	addi 	t0, sp, PORT_CONTEXT_SIZEOF
	store_x t0, PORT_CONTEXT_xOFFSET(2)(sp)
	
	/* Load pxCurrentTCB and update first TCB member(pxTopOfStack) with sp. */
	load_x  s9, pxCurrentTCB
	store_x  sp, 0( s9 )

	/* Save sp into s11 */
	mv 		s11, sp

	load_x sp, xISRStackTop			/* Switch to ISR stack before function call. */

	li 		s10, 1
	j	exit_trap_handler

handle_interrupt:
	addi	sp, sp, -PORT_CONTEXT_SIZEOF
	portSAVE_MAIN_REG
	portSAVE_Ax_REG
	csrr	t0, mscratch
	portSAVE_Tx_REG
	/* portSAVE_S1_S11_REG is called into portSAVE_MACHINE_SATE macro */
	portSAVE_MACHINE_SATE
	/* s2 = mcause
	 * s3 = mepc
	 * s4 = mstatus
	 * s9 will be use for pxCurrentTCB
	 * s10 will be use for if we want to call vTaskSwitchContext
	 * s11 will be use to save sp
	 */

	/* Store the value of sp when the interrupt occur */
	addi t0, sp, PORT_CONTEXT_SIZEOF
	store_x  t0, PORT_CONTEXT_xOFFSET(2)(sp)

	/* By default we assume not making a switch context */
	li	s10, 0

	/* Load pxCurrentTCB and update first TCB member(pxTopOfStack) with sp. */
	load_x  s9, pxCurrentTCB
	store_x  sp, 0( s9 )

	/* Save sp into s11 */
	mv  s11, sp
	load_x sp, xISRStackTop			/* Switch to ISR stack before function call. */

#if( configUSE_SEGGER_SYSTEMVIEW == 1 )
	jal SYSVIEW_RECORD_ENTER_ISR
#endif

#if( portasmHAS_CLINT != 0 )
	addi t0, x0, 1

	slli t0, t0, __riscv_xlen - 1   /* LSB is already set, shift into MSB.  Shift 31 on 32-bit or 63 on 64-bit cores. */
	addi t1, t0, 7					/* 0x8000[]0007 == machine timer interrupt. */
	bne s2, t1, test_if_external_interrupt

	load_x t0, pullMachineTimerCompareRegister  /* Load address of compare register into t0. */
	load_x t1, pullNextTime  		/* Load the address of ullNextTime into t1. */

# if( __riscv_xlen == 32 )
	/* Update the 64-bit mtimer compare match value in two 32-bit writes. */
	lw 	t2, 0(t1)				/* Load the low word of ullNextTime into t2. */
	lw 	t3, 4(t1)				/* Load the high word of ullNextTime into t3. */
	sw 	t2, 0(t0)				/* Store low word of ullNextTime into compare register. */
	sw 	t3, 4(t0)				/* Store high word of ullNextTime into compare register. */
	lw 	t0, uxTimerIncrementsForOneTick	/* Load the value of ullTimerIncrementForOneTick into t0 (could this be optimized by storing in an array next to pullNextTime?). */
	add t4, t0, t2				/* Add the low word of ullNextTime to the timer increments for one tick (assumes timer increment for one tick fits in 32-bits). */
	sltu t5, t4, t2				/* See if the sum of low words overflowed (what about the zero case?). */
	add t6, t3, t5				/* Add overflow to high word of ullNextTime. */
	sw 	t4, 0(t1)				/* Store new low word of ullNextTime. */
	sw 	t6, 4(t1)				/* Store new high word of ullNextTime. */
# elif( __riscv_xlen == 64 )
	/* Update the 64-bit mtimer compare match value. */
	ld 	t2, 0(t1)			 	/* Load ullNextTime into t2. */
	sd 	t2, 0(t0)				/* Store ullNextTime into compare register. */
	ld 	t0, uxTimerIncrementsForOneTick  /* Load the value of ullTimerIncrementForOneTick into t0 (could this be optimized by storing in an array next to pullNextTime?). */
	add 	t4, t0, t2				/* Add ullNextTime to the timer increments for one tick. */
	sd 	t4, 0(t1)				/* Store ullNextTime. */
# endif /* __riscv_xlen == 64 */

	jal xTaskIncrementTick
	beqz a0, exit_trap_handler		/* Don't switch context if incrementing tick didn't unblock a task. */
	li 		s10, 1
	j exit_trap_handler

test_if_external_interrupt:			/* If there is a CLINT and the mtimer interrupt is not pending then check to see if an external interrupt is pending. */
	addi t1, t1, 4					/* 0x80000007 + 4 = 0x8000000b == Machine external interrupt. */
	bne s2, t1, as_yet_unhandled	/* Something as yet unhandled. */

#endif /* portasmHAS_CLINT */

	csrr 	a0, mhartid
	mv		a1, s2
	mv 		a2, s5
	jal portHANDLE_INTERRUPT			/* Jump to the interrupt handler if there is no CLINT or if there is a CLINT and it has been determined that an external interrupt is pending. */
	j exit_trap_handler

as_yet_unhandled:
	ebreak
	j as_yet_unhandled

exit_trap_handler:
	bne s10, x0, proceed_switch_context
#if( configUSE_SEGGER_SYSTEMVIEW == 1 )
	jal SYSVIEW_RECORD_EXIT_ISR
#endif
	mv  sp, s11
	j end_trap_handler

proceed_switch_context:
	jal	vTaskSwitchContext
#if( configUSE_SEGGER_SYSTEMVIEW == 1 )
	jal SYSVIEW_RECORD_EXIT_ISR_TO_SCHEDULER
#endif
	load_x s9, pxCurrentTCB			/* Load pxCurrentTCB. */
	load_x  sp, 0( s9 )				/* Read sp from first TCB member. */

end_trap_handler:	
	load_x  t1, PORT_CONTEXT_xOFFSET(2)(sp)
	store_x  t1, 0( s9 )				/* Write sp saved value to first TCB member. */

	/* portSAVE_S1_S11_REG is called into portSAVE_MACHINE_SATE macro */
	portRESTORE_MACHINE_SATE
	portRESTORE_Tx_REG
	portRESTORE_Ax_REG
	portRESTORE_MAIN_REG
	load_x  x2, PORT_CONTEXT_xOFFSET(2)(sp)

	mret
	.endfunc
/*-----------------------------------------------------------*/

.align 8
.func
xPortStartFirstTask:

	/* Interrupts should be branch directly to the FreeRTOS	trap handler.
	Otherwise the interrupt controller will need to be configured outside of
	this file. */
	la t0, freertos_risc_v_trap_handler
	csrw mtvec, t0

	load_x  t0, pxCurrentTCB			/* Load pxCurrentTCB. */
	load_x  sp, 0( t0 )				 	/* Read sp from first TCB member. */

	load_x  t1,  PORT_CONTEXT_xOFFSET(2)(sp)
	store_x  t1, 0( t0 )				/* Write sp saved value to first TCB member. */

	/* portSAVE_S1_S11_REG is called into portSAVE_MACHINE_SATE macro */
	portRESTORE_MACHINE_SATE
	portRESTORE_Ax_REG
	portRESTORE_MAIN_REG
	
	load_x t0, pullMachineTimerRegister  /* Load address of compare register into t0. */
	load_x t1, pullNextTime  		/* Load the address of ullNextTime into t1. */

# if( __riscv_xlen == 32 )
		/* Read the 64-bit mtimer match value in two 32-bit writes. */
		lw t3, 4(t0)				/* Load mtimer register high address. */
first_task_timer_loop:
		lw t2, 0(t0)				/* Load mtimer register low address. */
		mv t4, t3
		lw t3, 4(t0)				/* Load mtimer register high address. */
		bne t4, t3, first_task_timer_loop

		lw t0, uxTimerIncrementsForOneTick	/* Load the value of ullTimerIncrementForOneTick into t0 (could this be optimized by storing in an array next to pullNextTime?). */
		add t4, t0, t2				/* Add the low word of mtimer for one tick (assumes timer increment for one tick fits in 32-bits). */
		sltu t5, t4, t2				/* See if the sum of low words overflowed (what about the zero case?). */
		add t6, t3, t5				/* Add overflow to high word of mtimer. */
	
		load_x t2, pullMachineTimerCompareRegister  /* Load address of compare register into t0. */
		sw t4, 0(t2)				/* Store new low word of ullNextTime. */
		sw t6, 4(t2)				/* Store new high word of ullNextTime. */

		add t2, t0, t4				/* Add the low word of ullNextTime to the timer increments for one tick (assumes timer increment for one tick fits in 32-bits). */
		sltu t5, t2, t4				/* See if the sum of low words overflowed (what about the zero case?). */
		add t3, t6, t5				/* Add overflow to high word of ullNextTime. */
		sw t2, 0(t1)				/* Store new low word of ullNextTime. */
		sw t3, 4(t1)				/* Store new high word of ullNextTime. */

# elif( __riscv_xlen == 64 )
		/* Read the 64-bit mtimer */
		ld t2, 0(t0)			 	/* Load mtimer register into t2. */
		ld t3, uxTimerIncrementsForOneTick  /* Load the value of ullTimerIncrementForOneTick into t0 (could this be optimized by storing in an array next to pullNextTime?). */
		add t4, t3, t2				/* Add ullNextTime to the timer increments for one tick. */
		load_x t2, pullMachineTimerCompareRegister  /* Load address of compare register into t0. */
		sd t4, 0(t2)				/* Store ullNextTime into compare register. */
		/* Update the 64-bit mtimer compare match value. */
		add t4, t3, t4				/* Add ullNextTime to the timer increments for one tick. */
		sd t4, 0(t1)				/* Store ullNextTime. */
# endif /* __riscv_xlen == 64 */

	li t0, 0x880
	csrs mie, t0

	portRESTORE_Tx_REG
	load_x  ra, PORT_CONTEXT_mepcOFFSET(sp) /* Note for starting the scheduler the exception return address is used as the function return address. */
	load_x  x2, PORT_CONTEXT_xOFFSET(2)(sp)

	ret
	.endfunc
/*-----------------------------------------------------------*/

/*
 * Unlike other ports pxPortInitialiseStack() is written in assembly code as it
 * needs access to the portasmADDITIONAL_CONTEXT_SIZE constant.  The prototype
 * for the function is as per the other ports:
 * StackType_t *pxPortInitialiseStack( StackType_t *pxTopOfStack, TaskFunction_t pxCode, void *pvParameters );
 *
 * As per the standard RISC-V ABI pxTopcOfStack is passed in in a0, pxCode in
 * a1, and pvParameters in a2.  The new top of stack is passed out in a0.
 *
 * RISC-V maps registers to ABI names as follows (X1 to X31 integer registers
 * for the 'I' profile, X1 to X15 for the 'E' profile, currently I assumed).
 *
 * Register		ABI Name	Description						Saver
 * x0			zero		Hard-wired zero					-
 * x1			ra			Return address					Caller
 * x2			sp			Stack pointer					Callee
 * x3			gp			Global pointer					-
 * x4			tp			Thread pointer					-
 * x5-7			t0-2		Temporaries						Caller
 * x8			s0/fp		Saved register/Frame pointer	Callee
 * x9			s1			Saved register					Callee
 * x10-11		a0-1		Function Arguments/return values Caller
 * x12-17		a2-7		Function arguments				Caller
 * x18-27		s2-11		Saved registers					Callee
 * x28-31		t3-6		Temporaries						Caller
 *
 */

/*-----------------------------------------------------------*/
