/* Copyright 2020 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#include <stdio.h>
#include <stdlib.h>
#include <metal/cpu.h>
#include <metal/csr.h>
#include <metal/pmp.h>
#include <metal/privilege.h>
#include <metal/drivers/riscv_cpu.h>

#define SATP_MODE	0x80000000UL

/* Create a stack for user-mode execution */
uint8_t s_stack[768] __attribute__((aligned(16)));

/* Create the register file for user mode execution */
struct metal_register_file s_regfile = {
	.sp = (uintptr_t) (s_stack + sizeof(s_stack)),
};

static void supervisor_mode_trap_handler(struct metal_cpu *cpu, int cause)
{
	uintptr_t epc = metal_cpu_get_exception_pc(cpu);
	int inst_len = metal_cpu_get_instruction_length(cpu, epc);
	uintptr_t value;

	if (cause == METAL_II_EXCEPTION_CODE) {
		printf("Caught illegal exception\n");
		metal_cpu_set_exception_pc(cpu, epc + inst_len);
		exit(0);
	} else {
		exit(7);
	}
}

static void supervisor_mode_entry_point(void)
{
	uintptr_t value;

	/* Write to satp CSR should be ignored in base-S mode */
	METAL_CPU_GET_CSR(satp, value);
	printf("satp: 0x%lx\n", value);

	METAL_CPU_SET_CSR(satp, SATP_MODE);

	METAL_CPU_GET_CSR(satp, value);
	printf("satp: 0x%lx\n", value);

	/* Perform a syscall in supervisor mode */
	__asm__ __volatile__("sfence.vma");

	exit(6);
}

int main(void)
{
	int ret;
	struct metal_cpu *cpu;
	struct metal_interrupt *cpu_intr;
#ifdef __METAL_DT_PMP_HANDLE
	struct metal_pmp *pmp;
#endif

	/* Initialize interrupt handling */
	cpu = metal_cpu_get(metal_cpu_get_current_hartid());
	if (!cpu) {
		printf("Unable to get CPU handle\n");
		return 1;
	}

	cpu_intr = metal_cpu_interrupt_controller(cpu);
	if (!cpu_intr) {
		printf("Unable to get CPU Interrupt handle\n");
		return 2;
	}

	metal_interrupt_init(cpu_intr);

	/* Register our own handler for traps */
	ret = metal_cpu_exception_register(cpu,
					   METAL_II_EXCEPTION_CODE,
					   supervisor_mode_trap_handler);
	if (ret < 0) {
		printf("Failed to register S-Mode exception handler\n");
		return 3;
	}

#ifdef __METAL_DT_PMP_HANDLE
	/* Initialize PMPs */
	pmp = metal_pmp_get_device();
	if (!pmp) {
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
	ret = metal_pmp_set_region(pmp, 0, config, -1);
	if (ret != 0) {
		return 5;
	}
#endif

	printf("=== Transfer privilege to supervisor mode ===\n");

	/* Use API of freedom-metal to switch mode */
	metal_privilege_drop_to_mode(METAL_PRIVILEGE_SUPERVISOR,
				     s_regfile,
				     supervisor_mode_entry_point);

	return 0;
}
