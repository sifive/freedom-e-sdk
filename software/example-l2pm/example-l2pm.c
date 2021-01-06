/* Copyright 2020 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

/*
 *  Example code to demonstrate usage of SiFive L2 performance monitor counters
 *  to capture L2 cache event logs.
 */
#include <metal/cache.h>
#include <metal/drivers/sifive_ccache0.h>
#include <metal/drivers/sifive_l2pf0.h>
#include <metal/machine.h>
#include <stdio.h>

/* Check for presence of SiFive L2 cache controller and PM counters */
#if defined(METAL_SIFIVE_CCACHE0) && METAL_SIFIVE_CCACHE0_PERFMON_COUNTERS > 5

/* Macros to set event selector values */
/* Capture L1 miss events.
 * Event Set 1
 * innerAcquireBlockNtoB
 * innerAcquireBlockNtoT
 * innerAcquireBlockBtoT
 * innerAcquirePermNtoT
 * innerAcquirePermB2T
 */
#define L1MISS_EVENTS                                                          \
  ((0x01) | (((1 << 6) | (1 << 7) | (1 << 8) | (1 << 9) | (1 << 10)) << 8))

/* Capture L1 miss hit L2 events.
 * Event Set 2
 * innerAcquireBlock_Hit
 * innerAcquirePerm_Hit
 */
#define L1MISS_L2HIT_EVENTS ((0x02) | (((1 << 6) | (1 << 5)) << 8))

/* Capture prefetch events.
 * Event Set 1
 * innerPrefetchRead
 * innerPrefetchWrite
 */
#define PREFETCH_EVENTS ((0x01) | (((1 << 4) | (1 << 5)) << 8))

/* Capture prefetch hits L2 events.
 * Event Set 2
 * innerPrefetch_Hit
 */
#define PREFETCH_HITS_L2 ((0x02) | (((1 << 4)) << 8))

/* Capture L1 request misses L2 events.
 * Event Set3
 * outerAcquireBlockNtoB
 * outerAcquireBlockNtoT
 * outerAcquireBlockBtoT
 * outerAcquirePermNtoT
 * outerAcquirePermBtoT
 */
#define L1_REQ_MISSES_L2                                                       \
  ((0x03) | (((1 << 0) | (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4)) << 8))

/* L2PM counter IDs.
 * We assume at least 5 counters to be available.
 */
#define L2PM_COUNTER0 0
#define L2PM_COUNTER1 1
#define L2PM_COUNTER2 2
#define L2PM_COUNTER3 3
#define L2PM_COUNTER4 4

/* Enable / Disable print statements */
#if 0
#define PRINT(...) printf(__VA_ARGS__)
#else
#define PRINT(...)
#endif

/* Boot hart ID exported from linker */
extern char __metal_boot_hart;

extern char metal_segment_heap_target_start;
extern char metal_segment_heap_target_end;

/* Function to run memory operations */
static void mem_test() {
  volatile int *addr, *end;
  volatile int readvalue;

  /* Flush out entire cache */
  metal_dcache_l1_flush((uintptr_t)&__metal_boot_hart, 0);

  /* Set end memory address */
  end = (int *)(&metal_segment_heap_target_end - 16);

  for (int i = 0; i < 4; i++) {
    addr = (int *)&metal_segment_heap_target_start;

    /* Read some memory locations */
    while (addr < end) {
      readvalue = *addr;
      readvalue = *addr;
      /* Access memory in multiples of cache block size */
      addr += 16;
    }
  }
  /* Avoids '-Werror=unused-but-set-variable' error */
  readvalue += 1;
}

int main() {

  uint64_t count;

  PRINT("***L2 cache performance monitor counter demo***\n");

  /* Initialize SiFive L2 cache controller */
  if (sifive_ccache0_init() != 0)
    return 1;

  sifive_ccache0_clr_pmevent_counter(L2PM_COUNTER0);
  /* Configure counter 0 to capture L1 miss events */
  sifive_ccache0_set_pmevent_selector(L2PM_COUNTER0, L1MISS_EVENTS);
  /* Check if values were set */
  if (sifive_ccache0_get_pmevent_selector(L2PM_COUNTER0) != L1MISS_EVENTS)
    return 2;

  sifive_ccache0_clr_pmevent_counter(L2PM_COUNTER1);
  /* Configure counter 1 to capture L1 miss hit L2 */
  sifive_ccache0_set_pmevent_selector(L2PM_COUNTER1, L1MISS_L2HIT_EVENTS);
  /* Check if values were set */
  if (sifive_ccache0_get_pmevent_selector(L2PM_COUNTER1) != L1MISS_L2HIT_EVENTS)
    return 3;

  sifive_ccache0_clr_pmevent_counter(L2PM_COUNTER2);
  /* Configure counter 2 to capture prefetch events */
  sifive_ccache0_set_pmevent_selector(L2PM_COUNTER2, PREFETCH_EVENTS);
  /* Check if values were set */
  if (sifive_ccache0_get_pmevent_selector(L2PM_COUNTER2) != PREFETCH_EVENTS)
    return 4;

  sifive_ccache0_clr_pmevent_counter(L2PM_COUNTER3);
  /* Configure counter 3 to capture prefetch hits L2 events */
  sifive_ccache0_set_pmevent_selector(L2PM_COUNTER3, PREFETCH_HITS_L2);
  /* Check if values were set */
  if (sifive_ccache0_get_pmevent_selector(L2PM_COUNTER3) != PREFETCH_HITS_L2)
    return 5;

  sifive_ccache0_clr_pmevent_counter(L2PM_COUNTER4);
  /* Configure counter 4 to capture L1 request misses L2 events */
  sifive_ccache0_set_pmevent_selector(L2PM_COUNTER4, L1_REQ_MISSES_L2);
  /* Check if values were set */
  if (sifive_ccache0_get_pmevent_selector(L2PM_COUNTER4) != L1_REQ_MISSES_L2)
    return 6;

  /* Counters start incrementing from the moment event selectors are set.
   * Event selectors are configured for the set of L2 events to be captured.*/

  /* Run some memory operations */
  mem_test();

  /* Report error, if read counter values are zero. */
  count = sifive_ccache0_get_pmevent_counter(L2PM_COUNTER0);
  if (count == 0)
    return 7;
  PRINT("L1 miss event count: %lu\n", count);

  count = sifive_ccache0_get_pmevent_counter(L2PM_COUNTER1);
  if (count == 0)
    return 8;
  PRINT("L1 miss hit L2 event count: %lu\n", count);

#ifdef METAL_SIFIVE_L2PF0
  /* Run some memory operations */
  mem_test();

  count = sifive_ccache0_get_pmevent_counter(L2PM_COUNTER2);
  if (count == 0)
    return 9;
  PRINT("Prefetch event count: %lu\n", count);

  count = sifive_ccache0_get_pmevent_counter(L2PM_COUNTER3);
  if (count == 0)
    return 10;
  PRINT("Prefetch hits L2 event count: %lu\n", count);

  count = sifive_ccache0_get_pmevent_counter(L2PM_COUNTER4);
  if (count == 0)
    return 11;
  PRINT("L1 request misses L2 event count: %lu\n", count);
#endif

  /* Clear off event selectors, to stop counters. */
  sifive_ccache0_set_pmevent_selector(L2PM_COUNTER0, 0);
  sifive_ccache0_set_pmevent_selector(L2PM_COUNTER1, 0);
  sifive_ccache0_set_pmevent_selector(L2PM_COUNTER2, 0);
  sifive_ccache0_set_pmevent_selector(L2PM_COUNTER3, 0);
  sifive_ccache0_set_pmevent_selector(L2PM_COUNTER4, 0);

  return 0;
}

/* secondary_main() runs on all HARTs */
int secondary_main() {
#ifdef METAL_SIFIVE_L2PF0
  /* Enable L2 prefetcher for each hart */
  sifive_l2pf0_enable();
#endif
  uintptr_t hart_id = metal_cpu_get_current_hartid();

  if (hart_id == (uintptr_t)&__metal_boot_hart) {
    /* Boot hart runs main() */
    return main();
  } else {
    while (1) {
      __asm__ __volatile__("wfi");
    }
  }
}

#else

int main() { return 0; }

#endif
