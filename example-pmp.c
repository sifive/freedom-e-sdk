/* Copyright 2019 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#include <stdlib.h>
#include <stdio.h>

#include <metal/cpu.h>
#include <metal/pmp.h>

#define ECODE_STORE_FAULT	7

#define NAPOT_SIZE 128
#define PROTECTED_ARRAY_LENGTH 32
volatile uint32_t protected_global[PROTECTED_ARRAY_LENGTH] __attribute__((aligned(NAPOT_SIZE)));

void store_access_fault_handler(struct metal_cpu *cpu, int ecode)
{
	/* Get faulting instruction and instruction length */
	unsigned long epc = metal_cpu_get_exception_pc(cpu);
	int inst_len = metal_cpu_get_instruction_length(cpu, epc);

	/* Advance the exception program counter by the length of the
	 * instruction to return execution after the faulting store */
	metal_cpu_set_exception_pc(cpu, epc + inst_len);

	if(ecode != ECODE_STORE_FAULT) {
		exit(7);
	}
}

int main()
{
	int rc;
	struct metal_cpu *cpu;
	struct metal_interrupt *cpu_intr;
	struct metal_pmp *pmp;

	/* PMP addresses are 4-byte aligned, drop the bottom two bits */
	size_t protected_addr = ((size_t) &protected_global) >> 2;
	
	/* Clear the bit corresponding with alignment */
	protected_addr &= ~(NAPOT_SIZE >> 3);

	/* Set the bits up to the alignment bit */
	protected_addr |= ((NAPOT_SIZE >> 3) - 1);

	printf("PMP Driver Example\n");

	/* Initialize interrupt handling on the current CPU */
	cpu = metal_cpu_get(metal_cpu_get_current_hartid());
	if(!cpu) {
		printf("Unable to get CPU handle\n");
		return 1;
	}
	cpu_intr = metal_cpu_interrupt_controller(cpu);
	if(!cpu_intr) {
		printf("Unable to get CPU Interrupt handle\n");
		return 2;
	}
	metal_interrupt_init(cpu_intr);

	/* Register a handler for the store access fault exception */
	rc = metal_cpu_exception_register(cpu, ECODE_STORE_FAULT, store_access_fault_handler);
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

	/* Perform a write to the memory we're about to protect access to */
	protected_global[0] = 0;

	/* Configure PMP 0 to only allow reads to protected_global. The
	 * PMP region is locked so that the configuration applies to M-mode
	 * accesses. */
	struct metal_pmp_config config = {
		.L = METAL_PMP_LOCKED,
		.A = METAL_PMP_NAPOT, /* Naturally-aligned power of two */
		.X = 0,
		.W = 0,
		.R = 1,
	};
	rc = metal_pmp_set_region(pmp, 0, config, protected_addr);
	if(rc != 0) {
		printf("Failed to configure PMP 0\n");
		return 5;
	}

	printf("Attempting to write to protected address\n");

	/* Attempt to write to protected_global. This should generate a store
	 * access fault exception. */
	protected_global[0] = 6;

	/* If execution returns to here, return the value of protected
	 * global to demonstrate that we can still read the value */

	/* If the write succeeds, the test fails */
	return protected_global[0];
}
