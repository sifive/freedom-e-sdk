#include <stdio.h>
#include <metal/cpu.h>

int intr_count;

void timer_handler (int id, void *data) {
    intr_count++;
    metal_cpu_set_mtimecmp((struct metal_cpu *)data, 0xffff);
}

int main (void)
{
    unsigned long long i, timeval, timebase;
    struct metal_cpu *cpu0;
    struct metal_interrupt *cpu_intr;
    struct metal_interrupt *tmr_intr;
    int rc, tmr_id;

    cpu0 = metal_cpu_get(0);
    if (cpu0 == NULL) {
        return 1;
    }

    timeval = 0;
    timebase = 0;
    timeval = metal_cpu_get_timer(cpu0);
    timebase = metal_cpu_get_timebase(cpu0);
    if ((timeval == 0) || (timebase == 0)) {
       return 2;
    }

    cpu_intr = metal_cpu_interrupt_controller(cpu0);
    if (cpu_intr == NULL) {
        return 3;
    }
    metal_interrupt_init(cpu_intr);

    tmr_intr = metal_cpu_timer_interrupt_controller(cpu0);
    if (tmr_intr == NULL) {
        return 4;
    }
    metal_interrupt_init(tmr_intr);
    tmr_id = metal_cpu_timer_get_interrupt_id(cpu0);
    rc = metal_interrupt_register_handler(tmr_intr, tmr_id, timer_handler, cpu0);
    if (rc < 0) {
        return (rc * -1);
    }

    intr_count = 0;
    metal_cpu_set_mtimecmp(cpu0, 0);
    if (metal_interrupt_enable(tmr_intr, tmr_id) == -1) {
        return 5;
    }   
    
    if (metal_interrupt_enable(cpu_intr, 0) == -1) {
        return 6;
    }   
    
    if (intr_count != 1) {
        return 99; 
    }   
    return 0;
}

