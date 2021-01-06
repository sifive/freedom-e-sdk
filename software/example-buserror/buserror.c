/* Copyright 2020 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#include <stdio.h>
#include <metal/cpu.h>
#include <metal/drivers/sifive_buserror0.h>
#include <metal/machine.h>

/* The sifive,error0 device is used to trigger a TileLink bus error for
 * testing the sifive,buserror0 device. If one isn't present, this example
 * will fail to compile because we have no way to trigger a bus error. */
#ifndef METAL_SIFIVE_ERROR0
#error Example requires a sifive,error0 device to drive bus errors
#endif

#define BADADDR METAL_SIFIVE_ERROR0_0_BASE_ADDRESS

struct metal_cpu *cpu;
struct metal_interrupt *cpu_intr;

int accrued = 0;
volatile int local_int_handled = 0;

void beu_local_handler(int id, void *data) {
  struct metal_buserror *beu = (struct metal_buserror *)data;

  metal_buserror_event_t event = metal_buserror_get_cause(beu);

  if (event & METAL_BUSERROR_EVENT_ANY) {
    printf("Handled TileLink bus error\n");
    local_int_handled = 1;
    metal_buserror_clear_event_accrued(beu, METAL_BUSERROR_EVENT_ALL);
  }

  metal_buserror_clear_cause(beu);
}

int main() {
  cpu = metal_cpu_get(metal_cpu_get_current_hartid());
  if (cpu == NULL) {
    return 1;
  }
  cpu_intr = metal_cpu_interrupt_controller(cpu);
  if (cpu_intr == NULL) {
    return 2;
  }
  metal_interrupt_init(cpu_intr);

  struct metal_buserror *beu = metal_cpu_get_buserror(cpu);
  if (beu == NULL) {
    return 3;
  }
  int beu_int_id = metal_buserror_get_local_interrupt_id(beu);

  /* Register beu_local_handler for the bus error unit interrupt */
  int rc = metal_interrupt_register_handler(cpu_intr, beu_int_id, beu_local_handler, beu);
  if (rc != 0) {
    return -1 * rc;
  }

  /* Clear any accrued events and the cause register */
  metal_buserror_clear_event_accrued(beu, METAL_BUSERROR_EVENT_ALL);
  metal_buserror_clear_cause(beu);

  /* Enable all bus error events */
  metal_buserror_set_event_enabled(beu, METAL_BUSERROR_EVENT_ALL, true);

  /* Trigger an error event */
  uint8_t bad = *((volatile uint8_t *)BADADDR);

  /* Fence above error event before check below */
  __asm__ ("fence");

  /* Check if the event is accrued and clear it*/
  if (metal_buserror_is_event_accrued(beu, METAL_BUSERROR_EVENT_ANY)) {
    printf("Detected accrued bus error\n");
    accrued = 1;
    metal_buserror_clear_event_accrued(beu, METAL_BUSERROR_EVENT_ALL);
    metal_buserror_clear_cause(beu);
  }
  if (!metal_buserror_is_event_accrued(beu, METAL_BUSERROR_EVENT_ANY)) {
    printf("Cleared accrued bus error\n");
  }

  /* Enable hart-local interrupts for error events */
  metal_buserror_set_local_interrupt(beu, METAL_BUSERROR_EVENT_ALL, true);
  rc = metal_interrupt_enable(cpu_intr, 0);
  if (rc != 0) {
    return 4;
  }

  /* Fence above error clear before trigger below */
  /* Fence above interrupt enable before trigger below */
  __asm__ ("fence");

  /* Trigger an error event */
  bad = *((volatile uint8_t *)BADADDR);

  /* Fence above error event before interrupt check below */
  __asm__ ("fence");
  __asm__ ("fence.i");

  if (!accrued) {
    return 5;
  }
  if (!local_int_handled) {
    return 6;
  }
  return 0;
}
