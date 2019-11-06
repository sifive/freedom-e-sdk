/* Copyright 2019 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#include "latency_test.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t *ptr_init_with_random(size_t max, int scale) {
    size_t *ptrs = (size_t *)malloc(max * sizeof(size_t));

    if (!ptrs) return NULL;
    memset(ptrs, 0, max * sizeof(size_t));

    size_t i;
    for (i = 0; i < max; ++i) {
        ptrs[i] = i * scale;
    }
    size_t v, o;
    for (i = 0; i < max; i++) {
        o = rand() % max;
        v = ptrs[o];
        ptrs[o] = ptrs[i];
        ptrs[i] = v;
    }

    return ptrs;
}
void rnd_init(void *test_setting) {
    struct test_info *setting = (struct test_info *)test_setting;

    setting->nptrs = setting->cur_range / setting->line;
    setting->ptrs = ptr_init_with_random(setting->nptrs - 1, setting->line);

    if (setting->addr) {
        free(setting->addr);
        setting->addr = NULL;
    }

    register char *addr = setting->addr = (char *)malloc(setting->max_range);

    if (!setting->ptrs || !addr) {
        printf("malloc fail\n");
        exit(0xdead);
    }

    size_t stride = setting->line;
    register size_t i, cur = 0, next = 0;

    for (i = 0; i < setting->nptrs - 1; i++) {
        next = setting->ptrs[i] + stride;
        *(char **)&addr[cur] = (char *)&addr[next];
        cur = next;
    }

    // completes circulation
    *(char **)&addr[cur] = (char *)&addr[0];

    setting->p = addr;
    if (setting->ptrs) {
        free(setting->ptrs);
        setting->ptrs = NULL;
    }
}
