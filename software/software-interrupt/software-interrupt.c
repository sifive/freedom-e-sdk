/* Copyright 2019 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#include <stdio.h>
#include <metal/cpu.h>
#include <metal/timer.h>

int sw_status = 99;

void software_handler (int id, void *data) {
    metal_cpu_software_clear_ipi((struct metal_cpu *)data, metal_cpu_get_current_hartid());
    sw_status = 0;
}

int main (void)
{
    int rc, sw_id;
    struct metal_cpu *cpu;
    struct metal_interrupt *cpu_intr;
    struct metal_interrupt *sw_intr;

    cpu = metal_cpu_get(metal_cpu_get_current_hartid());
    if (cpu == NULL) {
        return 1;
    }
    cpu_intr = metal_cpu_interrupt_controller(cpu);
    if (cpu_intr == NULL) {
        return 2;
    }
    metal_interrupt_init(cpu_intr);

    sw_intr = metal_cpu_software_interrupt_controller(cpu);
    if (sw_intr == NULL) {
        return 3;
    }
    metal_interrupt_init(sw_intr);
    sw_id = metal_cpu_software_get_interrupt_id(cpu);
    rc = metal_interrupt_register_handler(sw_intr, sw_id, software_handler, cpu);
    if (rc < 0) {
        return (rc * -1);
    }

    if (metal_interrupt_enable(sw_intr, sw_id) == -1) {
        return 5;
    }
    if (metal_interrupt_enable(cpu_intr, 0) == -1) {
        return 6;
    }

    metal_cpu_software_set_ipi(cpu, metal_cpu_get_current_hartid());

    unsigned long long start;
    unsigned long long count;
    metal_timer_get_cyclecount(metal_cpu_get_current_hartid(), &start);
    do {
        metal_timer_get_cyclecount(metal_cpu_get_current_hartid(), &count);
    } while (count < (start + METAL_WAIT_CYCLE));

    return sw_status;
}
