
#include <stdio.h>
#include <metal/cpu.h>

int sw_status = 99;

void software_handler (int id, void *data) {
    metal_cpu_software_clear_ipi((struct metal_cpu *)data, 0);
    sw_status = 0;
}

int main (void)
{
    int rc, sw_id;
    struct metal_cpu *cpu0;
    struct metal_interrupt *cpu_intr;
    struct metal_interrupt *sw_intr;

    cpu0 = metal_cpu_get(0);
    if (cpu0 == NULL) {
        return 1;
    }
    cpu_intr = metal_cpu_interrupt_controller(cpu0);
    if (cpu_intr == NULL) {
        return 2;
    }
    metal_interrupt_init(cpu_intr);

    sw_intr = metal_cpu_software_interrupt_controller(cpu0);
    if (sw_intr == NULL) {
        return 3;
    }
    metal_interrupt_init(sw_intr);
    sw_id = metal_cpu_software_get_interrupt_id(cpu0);
    rc = metal_interrupt_register_handler(sw_intr, sw_id, software_handler, cpu0);
    if (rc < 0) {
        return (rc * -1);
    }

    if (metal_interrupt_enable(sw_intr, sw_id) == -1) {
        return 5;
    }
    if (metal_interrupt_enable(cpu_intr, 0) == -1) {
        return 6;
    }

    metal_cpu_software_set_ipi(cpu0, 0);

    return sw_status;
}
