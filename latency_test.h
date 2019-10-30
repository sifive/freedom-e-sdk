/* Copyright 2019 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */
#ifndef LATENCY_TEST_H
#define LATENCY_TEST_H
#include <stddef.h>
#include <stdint.h>

struct test_info {
    size_t cur_range;  // The address range for current run, e.g., 8 KB
    size_t max_range;  // The maximum address range set by user, e.g., 8 MB
    size_t line;       // Stride;

    char *addr;  // Raw pointer to char array of sizeof(maxlen)

    size_t *ptrs;  // ptr array for random pattern
    size_t nptrs;  // total number of ptr

    char *p;  // Traversal pointer
};

uint64_t get_cycle();
void rnd_init(void *test_setting);

#endif  // LATENCY_TEST_H
