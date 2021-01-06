/* Copyright 2019 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#include <metal/cpu.h>
#include <metal/interrupt.h>
#include <metal/watchdog.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define WDOG_DESIRED_RATE 1000000 /* 1 MHz */
#define WDOG_TIMEOUT_SECONDS 1

bool caught_wdog_int = false;

void wdog_handler(int id, void *data) {
	struct metal_watchdog *wdog = (struct metal_watchdog *) data;

	/* Stop the watchdog and clear the interrupt*/
	metal_watchdog_run(wdog, METAL_WATCHDOG_STOP);
	metal_watchdog_clear_interrupt(wdog);

	puts("Caught watchdog interrupt\n");

	caught_wdog_int = true;	
}

int main() {
	int rc;

	/* Get CPU and Watchdog device handles */
	struct metal_cpu *cpu = metal_cpu_get(metal_cpu_get_current_hartid());
	if (!cpu) {
		exit(1);
	}

	struct metal_watchdog *wdog = metal_watchdog_get_device(0);
	if (!wdog) {
		exit(3);
	}

	/* Initialize CPU and Watchdog interrupts */
	struct metal_interrupt *cpu_intr = metal_cpu_interrupt_controller(cpu);
	if (!cpu_intr) {
		exit(2);
	}
	metal_interrupt_init(cpu_intr);

	struct metal_interrupt *wdog_intr = metal_watchdog_get_interrupt(wdog);
	if (!wdog_intr) {
		exit(4);
	}
	metal_interrupt_init(wdog_intr);
	int wdog_id = metal_watchdog_get_interrupt_id(wdog);

	/* Register an interrupt handler for the watchdog */
	rc = metal_interrupt_register_handler(wdog_intr, wdog_id, wdog_handler, wdog);
	if (rc != 0) {
		exit(rc * -1);
	}

	/* Try to set the watchdog rate */
	const long int rate = metal_watchdog_set_rate(wdog, WDOG_DESIRED_RATE);

	/* Timeout after WDOG_TIMEOUT_SECONDS seconds */
	metal_watchdog_set_timeout(wdog, WDOG_TIMEOUT_SECONDS * rate);

	/* Configure the watchdog to trigger an interrupt */
	metal_watchdog_set_result(wdog, METAL_WATCHDOG_INTERRUPT);

	/* Enable interrupts */
	rc = metal_interrupt_enable(wdog_intr, wdog_id);
	if (rc != 0) {
		exit(5);
	}
	rc = metal_interrupt_enable(cpu_intr, 0);
	if (rc != 0) {
		exit(6);
	}

	puts("Starting watchdog\n");

	/* Start the watchdog */
	metal_watchdog_run(wdog, METAL_WATCHDOG_RUN_ALWAYS);

	/* If the watchdog doesn't fire after twice the requested timeout, fail */
	time_t timeout = time(NULL) + (2 * WDOG_TIMEOUT_SECONDS);
	
	while (!caught_wdog_int) {
		if (time(NULL) > timeout) {
			/* Stop the watchdog */
			metal_watchdog_run(wdog, METAL_WATCHDOG_STOP);

			puts("Watchdog interrupt never triggered\n");

			exit(7);
		}
	}

	return 0;
}

