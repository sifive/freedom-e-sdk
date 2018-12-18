
#include <stdio.h>
#include <mee/cpu.h>

int sw_status = 99;

void software_handler (int id, void *data) {
    mee_cpu_software_clear_ipi((struct mee_cpu *)data, 0);
    sw_status = 0;
}

int main (void)
{
    int rc, sw_id;
    struct mee_cpu *cpu0;
    struct mee_interrupt *cpu_intr;
    struct mee_interrupt *sw_intr;

    cpu0 = mee_cpu_get(0);
    if (cpu0 == NULL) {
        return 1;
    }
    cpu_intr = mee_cpu_interrupt_controller(cpu0);
    if (cpu_intr == NULL) {
        return 2;
    }
    mee_interrupt_init(cpu_intr);

    sw_intr = mee_cpu_software_interrupt_controller(cpu0);
    if (sw_intr == NULL) {
        return 3;
    }
    mee_interrupt_init(sw_intr);
    sw_id = mee_cpu_software_get_interrupt_id(cpu0);
    rc = mee_interrupt_register_handler(sw_intr, sw_id, software_handler, cpu0);
    if (rc < 0) {
        return (rc * -1);
    }

    if (mee_interrupt_enable(sw_intr, sw_id) == -1) {
        return 5;
    }
    if (mee_interrupt_enable(cpu_intr, 0) == -1) {
        return 6;
    }

    mee_cpu_software_set_ipi(cpu0, 0);

    return sw_status;
}
