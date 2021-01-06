/* Copyright 2019 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#include <stdio.h>
#include <stdlib.h>

#include <metal/cpu.h>
#include <metal/lock.h>

#define NUM_ITERATIONS 10

#ifdef __SEGGER_LIBC__
/* Segger libc doesn't have fflush, so define it away */
#define fflush(stdout);
#endif

METAL_LOCK_DECLARE(my_lock);

int main(void);
int other_main();

/* This flag tells the secondary harts when to start to make sure
 * that they wait until the lock is initialized */
volatile int _start_other = 0;

/* This is a count of the number of harts who have executed their main function */
volatile int checkin_count = 0;

/* The secondary_main() function can be redefined to start execution
 * on secondary harts. We redefine it here to cause harts with
 * hartid != 0 to execute other_main() */
int secondary_main(void) {
	int hartid = metal_cpu_get_current_hartid();

	if(hartid == 0) {
		int rc = metal_lock_init(&my_lock);
		if(rc != 0) {
			puts("Failed to initialize my_lock\n");
			exit(1);
		}

		/* Ensure that the lock is initialized before any readers of
		 * _start_other */
		__asm__ ("fence rw,w"); /* Release semantics */

		_start_other = 1;

		return main();
	} else {
		return other_main(hartid);
	}
}

int main(void) {
	int num_harts = metal_cpu_get_num_harts();

	metal_lock_take(&my_lock);

	puts("Hart 0\n");
	fflush(stdout);

	checkin_count += 1;

	metal_lock_give(&my_lock);

	while(checkin_count != num_harts) ;

	return 0;
}

int other_main(int hartid) {
	while(!_start_other) ;	

	metal_lock_take(&my_lock);

	puts("Other Hart\n");
	fflush(stdout);

	checkin_count += 1;

	metal_lock_give(&my_lock);

	while(1) {
		__asm__("wfi");
	}
}
