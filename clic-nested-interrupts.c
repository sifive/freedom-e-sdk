/* Copyright 2020 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#include <stdio.h>
#include <string.h>
#include <metal/cpu.h>
#include <metal/csr.h>
#include <metal/led.h>
#include <metal/button.h>

#define RTC_FREQ	32768

struct metal_cpu *cpu;
struct metal_interrupt *cpu_intr;
struct metal_interrupt *clic;
int tmr_id, sip_irq, csip_irq;
struct metal_led *led0_red, *led0_green;

void display_instruction (void) {
    printf("\n");
    printf("SIFIVE, INC.\n!!\n");
    printf("\n");
    printf("Coreplex IP Eval Kit 'clic-nested-interrupts' example.\n\n");
    printf("A 5s debounce timer is used to trigger SIP and CSIP interrupts.\n");
    printf("Which preempted the timer ISR, with SIP has higher priority to CSIP interrupt.\n");
    printf("\n");
}

void timer_isr (void) __attribute__((interrupt, aligned(64)));
void timer_isr (void) {
    volatile uintptr_t saved_mcause;
    volatile uintptr_t saved_mepc;

    printf("**** In Timer handler, let trigger CSIP IRQ ****\n");

    // Trigger the SIP and CSIP interrupts
    metal_interrupt_set(clic, csip_irq);
    metal_interrupt_set(clic, sip_irq);

    /* Save originally interrupt context before re-enabling interrupts */
    METAL_CPU_GET_CSR(mepc, saved_mepc);
    METAL_CPU_GET_CSR(mcause, saved_mcause);

    /* Enable Preemptive Interrupts */
    __asm__ volatile ("csrrsi x0, mstatus, %0" : : "I"(0x8));

    /* Allow preemption to take place here */
    for (int i=0; i<10;i++)
        __asm__ volatile ("nop");

    /* Disable Preemptive Interrupts */
    __asm__ volatile ("csrrci x0, mstatus, %0" : : "I"(0x8));

    /* Restore originally interrupt context */
    METAL_CPU_SET_CSR(mepc, saved_mepc);
    METAL_CPU_SET_CSR(mcause, saved_mcause);

    metal_cpu_set_mtimecmp(cpu, metal_cpu_get_mtime(cpu) + 5*RTC_FREQ);
    printf("Clear and re-arm timer another 5 seconds.\n");
    printf("**** Exiting Timer handler ****\n");
}

void csip_isr(void) __attribute__((interrupt, aligned(64)));
void csip_isr(void) {
    printf("Got CSIP interrupt!\n");

    metal_led_toggle(led0_red);
    metal_interrupt_clear(clic, csip_irq);

    printf("Clear CSIP interrupt.\n");
}

void sip_isr(void) __attribute__((interrupt, aligned(64)));
void sip_isr(void) {
    printf("Got SIP interrupt!\n");

    metal_led_toggle(led0_green);
    metal_interrupt_clear(clic, sip_irq);

    printf("Clear SIP interrupt.\n");
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

    // Lets set CLIC in Selective Vector mode. Note this must be done AFTER init!!
    // This mode REQUIRE enabling/disabling specific interrupt BEFORE interrupt registration!!
    metal_interrupt_set_vector_mode(clic, METAL_SELECTIVE_VECTOR_MODE);

    // Also lets set 1 bit levels
    metal_interrupt_set_threshold(clic, 1);

    // Lets set up timer interrupt to be lower than SIP/CSIP so it can be preempted
    tmr_id = metal_cpu_timer_get_interrupt_id(cpu);
    metal_interrupt_set_preemptive_level(clic, tmr_id, 127);
    // Because we uses SELECTIVE HARDWARE VECTOR, need to enable each vector interrupt
    metal_interrupt_vector_enable(clic, tmr_id);
    rc = metal_interrupt_register_vector_handler(clic, tmr_id, timer_isr, cpu);
    if (rc < 0) {
        printf("Failed. TIMER interrupt handler registration failed\n");
        return (rc * -1);
    }

    // Similarly setup SIP and CSIP to a higher level then Timer
    // Also SIP (255) has higher priority than CSIP (223),
    // so SIP should get chosen before CSIP.
    sip_irq = 3;
    csip_irq = 12;
    metal_interrupt_set_preemptive_level(clic, sip_irq, 255);
    metal_interrupt_set_preemptive_level(clic, csip_irq, 223);
    metal_interrupt_vector_enable(clic, sip_irq);
    metal_interrupt_vector_enable(clic, csip_irq);
    rc = metal_interrupt_register_vector_handler(clic, sip_irq, sip_isr, NULL);
    rc = metal_interrupt_register_vector_handler(clic, csip_irq, csip_isr, NULL);
    if (rc < 0) {
        printf("SW interrupt handler registration failed\n");
        return (rc * -1);
    }

    // Enable SIP and CSIP interrupts
    if ((metal_interrupt_enable(clic, sip_irq) == -1) || 
        (metal_interrupt_enable(clic, csip_irq) == -1)) {
        printf("SW interrupt enabling failed\n");
        return 5;
    }

    // Set timeout of 5s, and enable timer interrupt
    metal_cpu_set_mtimecmp(cpu, metal_cpu_get_mtime(cpu) + 5*RTC_FREQ);
    metal_interrupt_enable(clic, tmr_id);

    display_instruction();

    // Lastly CPU interrupt
    if (metal_interrupt_enable(cpu_intr, 0) == -1) {
        printf("CPU interrupt enable failed\n");
        return 6;
    }

    // Wait For Interrupt
    while (1) {
        __asm__ volatile ("wfi");
    }

    return 0;
}
