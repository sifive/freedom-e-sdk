/* Copyright 2019 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#include <stdlib.h>
#include <stdio.h>

#include <metal/cpu.h>
#include <metal/pmp.h>
#include <metal/privilege.h>

#define ECODE_ILLEGAL_INSTRUCTION	2

/* Create a stack for user-mode execution */
uint8_t my_stack[768] __attribute__((aligned(16)));

/* Create the register file for user mode execution */
struct metal_register_file my_regfile = {
	.sp = (uintptr_t) (my_stack + sizeof(my_stack)),
};

void illegal_instruction_fault_handler(struct metal_cpu *cpu, int ecode)
{
	if(ecode == ECODE_ILLEGAL_INSTRUCTION) {
		printf("Caught illegal instruction in User mode\n");
		exit(0);
	} else {
		exit(7);
	}
}

void user_mode_entry_point()
{
	/* Attempt to read from a machine-mode CSR */
	int misa;
	__asm__ volatile("csrr %0, misa" : "=r" (misa));

	/* If we didn't trap, fail the test */
	exit(8);
}

int main()
{
	int rc;
	struct metal_cpu *cpu;
	struct metal_interrupt *cpu_intr;
	struct metal_pmp *pmp;

	/* Initialize interrupt handling on CPU 0 */
	cpu = metal_cpu_get(metal_cpu_get_current_hartid());
	if(!cpu) {
		printf("Unable to get CPU 0 handle\n");
		return 1;
	}
	cpu_intr = metal_cpu_interrupt_controller(cpu);
	if(!cpu_intr) {
		printf("Unable to get CPU 0 Interrupt handle\n");
		return 2;
	}
	metal_interrupt_init(cpu_intr);

	/* Register a handler for the store access fault exception */
	rc = metal_cpu_exception_register(cpu, ECODE_ILLEGAL_INSTRUCTION, illegal_instruction_fault_handler);
	if(rc < 0) {
		printf("Failed to register exception handler\n");
		return 3;
	}

	/* Initialize PMPs */
	pmp = metal_pmp_get_device();
	if(!pmp) {
		printf("Unable to get PMP Device\n");
		return 4;
	}
	metal_pmp_init(pmp);

	/* Configure PMP 0 to allow access to all memory */
	struct metal_pmp_config config = {
		.L = METAL_PMP_UNLOCKED,
		.A = METAL_PMP_TOR,
		.X = 1,
		.W = 1,
		.R = 1,
	};
	rc = metal_pmp_set_region(pmp, 0, config, -1);
	if(rc != 0) {
		return 5;
	}

	printf("Dropping privilege to User mode");

	/* Drop to user mode */
	metal_privilege_drop_to_mode(METAL_PRIVILEGE_USER, my_regfile, user_mode_entry_point);

	/* Execution should never return here */
	return 6;
}

