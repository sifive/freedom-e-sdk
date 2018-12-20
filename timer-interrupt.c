#include <stdio.h>
#include <mee/cpu.h>

int intr_count;

void timer_handler (int id, void *data) {
    intr_count++;
    mee_cpu_set_mtime((struct mee_cpu *)data, 0xffff);
}

int main (void)
{
    unsigned long long i, timeval, timebase;
    struct mee_cpu *cpu0;
    struct mee_interrupt *cpu_intr;
    struct mee_interrupt *tmr_intr;
    int rc, tmr_id;

    cpu0 = mee_cpu_get(0);
    if (cpu0 == NULL) {
        return 1;
    }

    timeval = 0;
    timebase = 0;
    mee_cpu_get_timer(cpu0, 0, &timeval);
    mee_cpu_get_timebase(cpu0, &timebase);
    if ((timeval == 0) || (timebase == 0)) {
       return 2;
    }

    cpu_intr = mee_cpu_interrupt_controller(cpu0);
    if (cpu_intr == NULL) {
        return 3;
    }
    mee_interrupt_init(cpu_intr);

    tmr_intr = mee_cpu_timer_interrupt_controller(cpu0);
    if (tmr_intr == NULL) {
        return 4;
    }
    mee_interrupt_init(tmr_intr);
    tmr_id = mee_cpu_timer_get_interrupt_id(cpu0);
    rc = mee_interrupt_register_handler(tmr_intr, tmr_id, timer_handler, cpu0);
    if (rc < 0) {
        return (rc * -1);
    }

    intr_count = 0;
    mee_cpu_set_mtime(cpu0, 0);
    if (mee_interrupt_enable(tmr_intr, tmr_id) == -1) {
        return 5;
    }   
    
    if (mee_interrupt_enable(cpu_intr, 0) == -1) {
        return 6;
    }   
    
    if (intr_count != 1) {
        return 99; 
    }   
    return 0;
}

