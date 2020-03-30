/* Copyright 2020 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#include <stdio.h>
#include <metal/cpu.h>
#include <metal/drivers/sifive_buserror0.h>

#define BADADDR 0x1000

struct metal_cpu *cpu;
struct metal_interrupt *cpu_intr;

int accrued = 0;
int local_int_handled = 0;

void beu_local_handler(int id, void *data) {
	struct metal_buserror *beu = (struct metal_buserror *)data;

	metal_buserror_event_t event = metal_buserror_get_cause(beu);

	if (event == METAL_BUSERROR_EVENT_LOAD_STORE_ERROR) {
		printf("Handled TileLink load or store bus error\n");
		local_int_handled = 1;
		metal_buserror_clear_event_accrued(beu, METAL_BUSERROR_EVENT_LOAD_STORE_ERROR);
	}

	metal_buserror_clear_cause(beu);
}

int main() {
	cpu = metal_cpu_get(metal_cpu_get_current_hartid());
	if (cpu == NULL) {
		return 1;
	}
	cpu_intr = metal_cpu_interrupt_controller(cpu);
	if (cpu_intr == NULL) {
		return 2;
	}
	metal_interrupt_init(cpu_intr);

	struct metal_buserror *beu = metal_cpu_get_buserror(cpu);
	if (beu == NULL) {
		return 3;
	}

	int rc = metal_interrupt_register_handler(cpu_intr, METAL_BUSERROR_LOCAL_INTERRUPT_ID, beu_local_handler, beu);
	if (rc != 0) {
		return -1 * rc;
	}

	/* Clear any accrued events and the cause register */
	metal_buserror_clear_event_accrued(beu, METAL_BUSERROR_EVENT_ALL);
	metal_buserror_clear_cause(beu);

	/* Enable the TileLink bus load/store error event */
	metal_buserror_set_event_enabled(beu, METAL_BUSERROR_EVENT_LOAD_STORE_ERROR, true);

	/* Trigger a load/store error event */
	uint8_t bad = *((uint8_t *)BADADDR);

	/* Check if the event is accrued and clear it*/
	if (metal_buserror_is_event_accrued(beu, METAL_BUSERROR_EVENT_LOAD_STORE_ERROR)) {
		printf("Detected accrued load or store bus error\n");
		accrued = 1;
		metal_buserror_clear_event_accrued(beu, METAL_BUSERROR_EVENT_LOAD_STORE_ERROR);
	}
	if (!metal_buserror_is_event_accrued(beu, METAL_BUSERROR_EVENT_LOAD_STORE_ERROR)) {
		printf("Cleared accrued load or store bus error\n");
	}

	/* Clear any accrued events and the cause register */
	metal_buserror_clear_event_accrued(beu, METAL_BUSERROR_EVENT_ALL);
	metal_buserror_clear_cause(beu);

	/* Enable the hart-local interrupt */
	metal_buserror_set_local_interrupt(beu, METAL_BUSERROR_EVENT_LOAD_STORE_ERROR, true);

	/* Trigger a load/store error event */
	bad = *((uint8_t *)BADADDR);

	return accrued && local_int_handled;
}
