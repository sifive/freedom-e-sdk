/* Copyright 2019 SiFive, Inc */
#include <inttypes.h> /* for PRIxPTR  */
#include <metal/cache.h>
#include <metal/cpu.h>
#include <stdint.h> /* for uinptr_t */
#include <stdio.h>
#include <stdlib.h>

#include "latency_test.h"

size_t test_size[] = {4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192};
extern size_t metal_segment_heap_target_start;
extern size_t metal_segment_heap_target_end;

#define ONE p = (char **)*p;
#define FIVE ONE ONE ONE ONE ONE
#define TEN FIVE FIVE
#define FIFITY TEN TEN TEN TEN TEN
#define HUNDRED FIFITY FIFITY
#define FHUNDRED HUNDRED HUNDRED HUNDRED HUNDRED HUNDRED
#define THOUSAND FHUNDRED FHUNDRED

#define K_TO_BYTE(x) x * 1024

void benchmark_latency(void *test_setting, size_t min_loop) {
    struct test_info *setting = (struct test_info *)test_setting;
    register char **p = (char **)setting->p;
    register size_t i;
    register size_t loop = min_loop;

    asm volatile("sltu zero, x1, x2");  // For RTLsim log marker
    for (i = 0; i < loop; ++i) {
        THOUSAND;
    }
    asm volatile("sltu zero, x1, x2");  // For RTLsim log marker

    setting->p = (char *)p;
}

int main() {
    size_t heap_size = (size_t)&metal_segment_heap_target_end -
                       (size_t)&metal_segment_heap_target_start;
    struct test_info setting = {};
    unsigned int test_count = 0;
    unsigned int cycle_count = 0;
    unsigned int i = 0, loop = 10, warmup_loop = 100;
    unsigned int all_test = sizeof(test_size) / sizeof(test_size[0]);
    unsigned int hartid = metal_cpu_get_current_hartid();

    setting.line = 128;

    printf("heap size: %" PRIdPTR "K\n", (size_t)heap_size / 1024);
    printf("stride: %" PRIdPTR "\n", setting.line);

    while (K_TO_BYTE(test_size[test_count]) < heap_size &&
           test_count < all_test)
        test_count++;

    setting.max_range = K_TO_BYTE(test_size[test_count - 1]);

    // iterate through all test_size
    for (i = 0; i < test_count; i++) {
        uint64_t start, end;

        // init all data structure
        setting.cur_range = K_TO_BYTE(test_size[i]);
        rnd_init(&setting);

        // warm-up run
        benchmark_latency(&setting, warmup_loop);

        // benchmark
        start = get_cycle();
        benchmark_latency(&setting, loop);
        end = get_cycle();

        cycle_count = end - start;
        printf("%6" PRIdPTR " K : %3" PRIdPTR " cycle\n", test_size[i],
               cycle_count / (loop * 1000));
    }
    printf("---test end---\n");
    exit(0);
}
