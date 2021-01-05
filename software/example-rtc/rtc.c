/* Copyright 2019 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#include <metal/cpu.h>
#include <metal/interrupt.h>
#include <metal/rtc.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define RTC_TIMEOUT_SECONDS 1

bool caught_rtc_int = false;

void rtc_handler(int id, void *data) {
	struct metal_rtc *rtc = (struct metal_rtc *) data;

	/* Stop the rtc */
	metal_rtc_run(rtc, METAL_RTC_STOP);

	/* Disable RTC interrupt */
	struct metal_interrupt *rtc_intr = metal_rtc_get_interrupt(rtc);
	int rtc_id = metal_rtc_get_interrupt_id(rtc);
	metal_interrupt_disable(rtc_intr, rtc_id);

	/* Clear the pending interrupt by setting the compare to a value
	 * larger than the current count */
	metal_rtc_set_compare(rtc, metal_rtc_get_count(rtc) + 1);

	puts("Caught RTC interrupt\n");

	caught_rtc_int = true;	
}

int main() {
	int rc;

	/* Get CPU and RTC device handles */
	struct metal_cpu *cpu = metal_cpu_get(metal_cpu_get_current_hartid());
	if (!cpu) {
		exit(1);
	}

	struct metal_rtc *rtc = metal_rtc_get_device(0);
	if (!rtc) {
		exit(2);
	}

	/* Initialize CPU and RTC interrupts */
	struct metal_interrupt *cpu_intr = metal_cpu_interrupt_controller(cpu);
	if (!cpu_intr) {
		exit(3);
	}
	metal_interrupt_init(cpu_intr);

	struct metal_interrupt *rtc_intr = metal_rtc_get_interrupt(rtc);
	if (!rtc_intr) {
		exit(4);
	}
	metal_interrupt_init(rtc_intr);
	int rtc_id = metal_rtc_get_interrupt_id(rtc);

	/* Register an interrupt handler for the rtc */
	rc = metal_interrupt_register_handler(rtc_intr, rtc_id, rtc_handler, rtc);
	if (rc != 0) {
		exit(rc * -1);
	}

	const uint64_t rate = metal_rtc_get_rate(rtc);

	/* Set RTC to 0 */
	metal_rtc_set_count(rtc, 0);

	/* Timeout after RTC_TIMEOUT_SECONDS seconds */
	metal_rtc_set_compare(rtc, RTC_TIMEOUT_SECONDS * rate);

	/* Enable interrupts */
	rc = metal_interrupt_enable(rtc_intr, rtc_id);
	if (rc != 0) {
		exit(5);
	}
	rc = metal_interrupt_enable(cpu_intr, 0);
	if (rc != 0) {
		exit(6);
	}

	puts("Starting RTC\n");

	/* Start the rtc */
	metal_rtc_run(rtc, METAL_RTC_RUN);

	/* If the rtc doesn't fire after twice the requested timeout, fail */
	time_t timeout = time(NULL) + (2 * RTC_TIMEOUT_SECONDS);
	
	while (!caught_rtc_int) {
		if (time(NULL) > timeout) {
			/* Stop the rtc */
			metal_rtc_run(rtc, METAL_RTC_STOP);

			puts("RTC interrupt never triggered\n");

			exit(7);
		}
	}

	return 0;
}


