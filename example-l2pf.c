/* Copyright 2020 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

/*
 *  Example code for usage and measuring effectiveness of SiFive L2 Prefetcher.
 */

#include <metal/cpu.h>
#include <metal/drivers/sifive_ccache0.h>
#include <metal/drivers/sifive_l2pf0.h>
#include <metal/machine.h>
#include <stdio.h>

/* Check for presence of SiFive L2 Prefetcher */
#ifdef METAL_SIFIVE_L2PF0

/* Macros to set L2 performance counter event selector values */
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

/* L2PM counter IDs.
 * We assume at least 2 counters to be available.
 */
#define L2PM_COUNTER0 0
#define L2PM_COUNTER1 1

/* Enable / Disable print statements */
#if 0
#define PRINT(...) printf(__VA_ARGS__)
#else
#define PRINT(...)
#endif

/* Raw access to heap segment */
extern char metal_segment_heap_target_start;

/* Function to run memory operations */
static void mem_test() {
  volatile int *addr;
  volatile int readvalue;

  for (int i = 1; i < 64; i++) {
    addr = (int *)&metal_segment_heap_target_start;
    addr = addr + (i << 14);
    addr = addr + 32;
    for (int j = 0; j < i; j++) {
      addr = addr + 16;
      readvalue = *addr;
    }

    addr = (int *)&metal_segment_heap_target_start;
    addr = addr + (i << 14);
    readvalue = *addr;
    addr = addr + 16;
    readvalue = *addr;
    addr = addr + 16;
    readvalue = *addr;
  }
  /* Avoids '-Werror=unused-but-set-variable' error */
  readvalue += 1;
}

int main() {

  struct metal_cpu *cpu;
  uint64_t t1, t2;

  PRINT("***L2 cache hardware prefetcher demo***\n");

  /* Initialize SiFive L2 cache controller */
  if (sifive_ccache0_init() != 0)
    return 1;

#if METAL_SIFIVE_CCACHE0_PERFMON_COUNTERS > 0
  sifive_ccache0_clr_pmevent_counter(L2PM_COUNTER0);
  /* Configure counter 0 to capture prefetch events */
  sifive_ccache0_set_pmevent_selector(L2PM_COUNTER0, PREFETCH_EVENTS);
  /* Check if values were set */
  if (sifive_ccache0_get_pmevent_selector(L2PM_COUNTER0) != PREFETCH_EVENTS)
    return 2;

  sifive_ccache0_clr_pmevent_counter(L2PM_COUNTER1);
  /* Configure counter 1 to capture prefetch hits L2 events */
  sifive_ccache0_set_pmevent_selector(L2PM_COUNTER1, PREFETCH_HITS_L2);
  /* Check if values were set */
  if (sifive_ccache0_get_pmevent_selector(L2PM_COUNTER1) != PREFETCH_HITS_L2)
    return 3;
#endif

  /* Keep L2 prefetcher disabled */
  sifive_l2pf0_disable();

  /* Calculate t1 cycles to run mem_test() with L2 prefetcher disabled */
  cpu = metal_cpu_get(metal_cpu_get_current_hartid());

  t1 = metal_cpu_get_timer(cpu);

  mem_test();

  t1 = metal_cpu_get_timer(cpu) - t1;

#if METAL_SIFIVE_CCACHE0_PERFMON_COUNTERS > 0
  uint64_t count;
  /* Counter should not register any prefetcher events */
  count = sifive_ccache0_get_pmevent_counter(L2PM_COUNTER0);
  if (count != 0)
    return 4;

  count = sifive_ccache0_get_pmevent_counter(L2PM_COUNTER1);
  if (count != 0)
    return 5;
#endif

  /* Enable L2 prefetcher */
  sifive_l2pf0_enable();

  /* Calculate t2 cycles to run mem_test() with L2 prefetcher enabled */
  t2 = metal_cpu_get_timer(cpu);

  mem_test();

  t2 = metal_cpu_get_timer(cpu) - t2;

#if METAL_SIFIVE_CCACHE0_PERFMON_COUNTERS > 0
  /* Report error if prefetcher events are not detected */
  count = sifive_ccache0_get_pmevent_counter(L2PM_COUNTER0);
  if (count == 0)
    return 6;
  PRINT("Prefetch event count: %lu\n", count);

  count = sifive_ccache0_get_pmevent_counter(L2PM_COUNTER1);

  if (count == 0)
    return 7;
  PRINT("Prefetch hits L2 event count: %lu\n", count);

  /* Clear off event selectors, to stop counters. */
  sifive_ccache0_set_pmevent_selector(L2PM_COUNTER0, 0);
  sifive_ccache0_set_pmevent_selector(L2PM_COUNTER1, 0);
#endif

  PRINT("Test run count with L2 prefetcher disabled: %lu\n", t1);
  PRINT("Test run count with L2 prefetcher enabled: %lu\n", t2);

  /* If t2 cycle count is higher than t1, something is not right ! */
  if ((t2 > t1) || (t1 == 0) || (t2 == 0))
    return 8;

  return 0;
}

#else

int main() { return 0; }

#endif
