/* Copyright 2019 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#include <stdio.h>
#include <inttypes.h>

#include <metal/atomic.h>
#include <metal/cpu.h>

/* Declare the variable used for atomic operations with this macro to ensure
 * that it's allocated in a memory region that supports atomic operations */
METAL_ATOMIC_DECLARE(my_counter);

/* secondary_main() runs on all harts */
int secondary_main(void) {
	/* Atomically add from all harts */
	metal_atomic_add(&my_counter, 1);

	/* Loop forever if we're not hart 0 */
	int hartid = metal_cpu_get_current_hartid();
	while (hartid != 0) {
		__asm__ ("wfi");
	}

	/* Wait until the counter has finished incrementing */
	int num_harts = metal_cpu_get_num_harts();
	while (my_counter != num_harts) ;

	printf("Atomic API incremented %" PRId32 " times\n", my_counter);

	/* Return success */
	return 0;
}

/* We don't used main, but the linker wants one to be defined */
int main(void) {
	return 0;
}
