/* Copyright 2019 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#include <stdio.h>
#include <stdlib.h>

#include <metal/ringbuf.h>

#define ITEM_SIZE_BYTES sizeof(char)
#define RINGBUF_SIZE 16	

METAL_RINGBUF_DECLARE(my_ringbuf, RINGBUF_SIZE, ITEM_SIZE_BYTES);

int main() {
	int rc = 0;
	size_t size = 0;
	char c = 0;
	int failed = 0;

	puts("TEST 1: fill ring buffer");
	size = 0;
	for (c = 'A'; c < ('A' + RINGBUF_SIZE); c++) {
		rc = metal_ringbuf_put(&my_ringbuf, (void *)&c);
		if (rc != 0) {
			printf("ring buffer accepted %d characters, expected %d\n",
			       size, RINGBUF_SIZE);
			failed += 1;
		}
		size += 1;

		if (metal_ringbuf_num_items(&my_ringbuf) != size) {
			printf("ring buffer reported size %d, but we've added %d characters\n",
		               size, metal_ringbuf_num_items(&my_ringbuf));
			failed += 1;
		}
	}
	if (size != RINGBUF_SIZE) {
		failed += 1;
	}

	puts("TEST 2: add to full ring buffer");
	c = 'Z';
	if (metal_ringbuf_put(&my_ringbuf, (void *)&c) == 0) {
		puts("ring buffer should be full, but accepted a new value anyway");
		failed += 1;
	}

	puts("TEST 3: empty ring buffer");
	size = 0;
	while (metal_ringbuf_get(&my_ringbuf, (void *)&c) == 0) {
		if (c != ('A' + size)) {
			printf("ring buffer returned incorrect character, expected %c but got %c\n",
			       'A' + size, c);
			failed += 1;
		}
		size += 1;
	}
	if (size != RINGBUF_SIZE) {
		printf("ring buffer returned %d characters, expected %d\n", size, RINGBUF_SIZE);
		failed += 1;
	}

	puts("TEST 4: get from empty ring buffer");
	if (metal_ringbuf_get(&my_ringbuf, (void *)&c) == 0) {
		printf("ring buffer should be empty, but returned a value %c anyway", c);
		failed += 1;
	}

	if (failed == 0) {
		puts("PASS");
	} else {
		puts("FAIL");
	}

	return failed;
}
