/* Copyright 2019 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#include <stdio.h>

#include <metal/itim.h>

__attribute__ ((noinline))
METAL_PLACE_IN_ITIM
int run_in_itim(int x)
{
	return x * x;
}

int main(void)
{
	int x = 2;
	int y = run_in_itim(x);

	if(y != 4) {
		puts("ITIM test failed\n");
		return 1;
	}

	puts("ITIM test passed\n");

	return 0;
}
