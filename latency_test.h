#ifndef LATENCY_TEST_H
#define LATENCY_TEST_H
#include <stdint.h> /* for uinptr_t */
#include <stdio.h>
#include <stdlib.h>

#define PAGESIZE 4096
#define LOOPCOUNT 1

#ifdef DEBUG
#define DEBUG_PRINT(format, args...) printf(format, ##args)
#else
#define DEBUG_PRINT(format, args...)
#endif

unsigned long long get_cycle();

struct test_info {
    size_t cur_range;  // The address range for current run, e.g., 8 KB
    size_t max_range;  // The maximum address range set by user, e.g., 8 MB
    size_t line;       // Stride;

    char *addr;  // Raw pointer to char array of sizeof(maxlen)

    size_t *ptrs;  // ptr array for random pattern
    size_t nptrs;  // total number of ptr

    // Traversal pointer
    char *p;
};

void rnd_init(void *test_setting);

#endif  // LATENCY_TEST_H
