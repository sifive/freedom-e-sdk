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
struct metal_interrupt *cpu_intr;
struct metal_interrupt *clic;
int tmr_id, csip_irq;
struct metal_led *led0_red, *led0_green;

void display_instruction (void) {
    printf("\n");
    printf("SIFIVE, INC.\n!!\n");
    printf("\n");
    printf("Coreplex IP Eval Kit 'clic-hadrware-vector-interrupts' example.\n\n");
    printf("IRQ 12 (CSIP) is enabled as external interrupt source.\n");
    printf("A 10s debounce timer is used to trigger and clear CSIP interrupt.\n");
    printf("\n");
}

void timer_isr (void) __attribute__((interrupt, aligned(64)));
void timer_isr (void) {
    printf("**** Lets trigger clic software interrupt ****\n");
    metal_interrupt_set(clic, csip_irq);
}

void csip_isr(void) __attribute__((interrupt, aligned(64)));
void csip_isr(void) {
    printf("Got the CSIP interrupt!\n");
    metal_interrupt_clear(clic, csip_irq);
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

    // Lets get a CLIC interrupt controller explicitly
    clic = metal_interrupt_get_controller(METAL_CLIC_CONTROLLER,
                                          metal_cpu_get_current_hartid());
    if (clic == NULL) {
        printf("Exit. This example need a clic interrupt controller.\n");
        return 0;
    }
    metal_interrupt_init(clic);

    // Lets set CLIC in Hardware Vector mode. Note this must be done AFTER init!!
    metal_interrupt_set_vector_mode(clic, METAL_HARDWARE_VECTOR_MODE);

    tmr_id = metal_cpu_timer_get_interrupt_id(cpu);
    rc = metal_interrupt_register_vector_handler(clic, tmr_id, timer_isr, cpu);
    if (rc < 0) {
        printf("Failed. TIMER interrupt handler registration failed\n");
        return (rc * -1);
    }

    csip_irq = 12;
    metal_interrupt_vector_enable(clic, csip_irq);
    rc = metal_interrupt_register_vector_handler(clic, csip_irq, csip_isr, NULL);
    if (rc < 0) {
        printf("SW1 interrupt handler registration failed\n");
        return (rc * -1);
    }
    if (metal_interrupt_enable(clic, csip_irq) == -1) {
        printf("SW1 interrupt enable failed\n");
        return 5;
    }
    // Set timeout of 10s, and enable timer interrupt
    metal_cpu_set_mtimecmp(cpu, metal_cpu_get_mtime(cpu) + 10*RTC_FREQ);
    metal_interrupt_enable(clic, tmr_id);

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
