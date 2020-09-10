/* Copyright 2019 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#include <stdio.h>
#include <string.h>
#include <metal/cpu.h>
#include <metal/led.h>
#include <metal/button.h>
#include <metal/switch.h>

#define RTC_FREQ	32768

struct metal_cpu *cpu;
struct metal_interrupt *cpu_intr, *tmr_intr;
struct metal_led *led0_red, *led0_green;
struct metal_interrupt *clint;
int tmr_id, sip_irq;

void display_instruction (void) {
    printf("\n");
    printf("SIFIVE, INC.\n!!\n");
    printf("\n");
    printf("Coreplex IP Eval Kit 'clint-vector-interrupts' Example.\n\n");
    printf("IRQ 3 (SIP) is enabled as external interrupt source.\n");
    printf("A 10s debounce timer is used to trigger and clear SIP interrupt.\n");
    printf("\n");
}

void timer_isr (int id, void *data) {
    printf("**** Lets trigger clint software interrupt ****\n");
    metal_interrupt_set(clint, sip_irq);
}

void sip_isr(int id, void *data) {
    printf("Got the SIP interrupt!\n");
    metal_interrupt_clear(clint, sip_irq);
    printf("Lets clear and re-arm timer another 10 seconds.\n");
    metal_led_toggle(led0_green);
    metal_led_toggle(led0_red);
    metal_cpu_set_mtimecmp(cpu, metal_cpu_get_mtime(cpu) + 10*RTC_FREQ);
}

int main (void)
{
    int rc;

    // Lets get start with getting LEDs and turn only RED ON
    led0_red = metal_led_get_rgb("LD0", "red");
    led0_green = metal_led_get_rgb("LD0", "green");
    if ((led0_red == NULL) || (led0_green == NULL)) {
        printf("Abort. At least one of LEDs is null.\n");
        return 1;
    }
    metal_led_enable(led0_red);
    metal_led_enable(led0_green);
    metal_led_on(led0_red);
    metal_led_off(led0_green);
 
    // Lets get the CPU and and its interrupt
    cpu = metal_cpu_get(metal_cpu_get_current_hartid());
    if (cpu == NULL) {
        printf("Abort. CPU is null.\n");
        return 2;
    }
    cpu_intr = metal_cpu_interrupt_controller(cpu);
    if (cpu_intr == NULL) {
        printf("Abort. CPU interrupt controller is null.\n");
        return 3;
    }
    metal_interrupt_init(cpu_intr);

    // Setup Timer interrupt
    tmr_intr = metal_cpu_timer_interrupt_controller(cpu);
    if (tmr_intr == NULL) {
        printf("Abort. TIMER interrupt controller is  null.\n");
        return 4;
    }
    metal_interrupt_init(tmr_intr);
    tmr_id = metal_cpu_timer_get_interrupt_id(cpu);
    rc = metal_interrupt_register_handler(tmr_intr, tmr_id, timer_isr, cpu);
    if (rc < 0) {
        printf("Failed. TIMER interrupt handler registration failed\n");
        return (rc * -1);
    }

    // Lets get a CLINT interrupt controller explicitly
    clint = metal_interrupt_get_controller(METAL_CLINT_CONTROLLER,
                                           metal_cpu_get_current_hartid());
    if (clint == NULL) {
        printf("Exit. This example need a clint interrupt controller.\n");
        return 0;
    }
    metal_interrupt_init(clint);

    // Lets set CLINT in Vector mode. Note this must be done AFTER init!!
    metal_interrupt_set_vector_mode(clint, METAL_VECTOR_MODE);

    sip_irq = 7;
    rc = metal_interrupt_register_handler(clint, sip_irq, sip_isr, NULL);
    if (rc < 0) {
        printf("SW interrupt handler registration failed\n");
        return (rc * -1);
    }

    // Lets enable Switches interrupts
    if (metal_interrupt_enable(clint, sip_irq) == -1) {
        printf("SW interrupt enable failed\n");
        return 5;
    }
    // Set timeout of 10s, and enable timer interrupt
    metal_cpu_set_mtimecmp(cpu, metal_cpu_get_mtime(cpu) + 10*RTC_FREQ);
    metal_interrupt_enable(tmr_intr, tmr_id);

    display_instruction();

    // Lastly CPU interrupt
    if (metal_interrupt_enable(cpu_intr, 0) == -1) {
        printf("CPU interrupt enable failed\n");
        return 6;
    }

    while (1) {
        __asm__ volatile ("wfi");
    }

    return 0;
}
