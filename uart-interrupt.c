/* Copyright 2019 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#include <stdio.h>
#include <metal/cpu.h>
#include <metal/led.h>
#include <metal/uart.h>
#include <metal/machine.h>

#define RTC_FREQ	32768

struct metal_cpu *cpu0;
struct metal_interrupt *cpu_intr, *tmr_intr;
struct metal_interrupt *uart0_ic;
int tmr_id, uart0_irq;

void display_instruction (void) {
    printf("\n");
    printf("SIFIVE, INC.\n!!\n");
    printf("\n");
    printf("Coreplex IP Eval Kit 'uart-interrupt' Example.\n\n");
    printf("A 1s debounce timer is used between these interupts.\n");
    printf("\n");
}

void timer_isr (int id, void *data) {
    // Disable Timer interrupt
    metal_interrupt_disable(tmr_intr, tmr_id);
    printf("Awaken\n");

    // Enable local IRQs
    //metal_interrupt_enable(but0_ic, but0_irq);
}

void debounce (void) {
    // Disable local IRQs
    //metal_interrupt_disable(but0_ic, but0_irq);

    printf("Sleep for 10s more secs\n");
    metal_cpu_set_mtimecmp(cpu0, metal_cpu_get_mtime(cpu0) + RTC_FREQ);

    // Enable Timer interrupt
    metal_interrupt_enable(tmr_intr, tmr_id);
}

void uart0_isr (int id, void *data) {
    printf("Got Uart 0 interrupt. Toggle Red LED.\n");
    //metal_led_toggle((struct metal_led *)data);
    debounce();  
}

int main (void)
{
    int rc;
    struct metal_led *led0_red, *led0_green, *led0_blue;
    struct metal_uart *uart0;
    size_t txcnt;


    // Lets get start with getting LEDs and turn only RED ON
    led0_red = metal_led_get_rgb("LD0", "red");
    led0_green = metal_led_get_rgb("LD0", "green");
    led0_blue = metal_led_get_rgb("LD0", "blue");
    if ((led0_red == NULL) || (led0_green == NULL) || (led0_blue == NULL)) {
        printf("At least one of LEDs is null.\n");
        return 1;
    }
    metal_led_enable(led0_red);
    metal_led_enable(led0_green);
    metal_led_enable(led0_blue);
    metal_led_on(led0_red);
    metal_led_off(led0_green);
    metal_led_off(led0_blue);
 
    // Lets get the CPU and and its interrupt
    cpu0 = metal_cpu_get(0);
    if (cpu0 == NULL) {
        printf("CPU null.\n");
        return 2;
    }
    cpu_intr = metal_cpu_interrupt_controller(cpu0);
    if (cpu_intr == NULL) {
        printf("CPU interrupt controller is null.\n");
        return 3;
    }
    metal_interrupt_init(cpu_intr);

    // Setup Timer and its interrupt
    tmr_intr = metal_cpu_timer_interrupt_controller(cpu0);
    if (tmr_intr == NULL) {
        printf("TIMER interrupt controller is  null.\n");
        return 4;
    }
    metal_interrupt_init(tmr_intr);
    tmr_id = metal_cpu_timer_get_interrupt_id(cpu0);
    rc = metal_interrupt_register_handler(tmr_intr, tmr_id, timer_isr, cpu0);
    if (rc < 0) {
        printf("TIMER interrupt handler registration failed\n");
        return (rc * -1);
    }

    // Setup Buttons 0-3 and its interrupt
    uart0 = (struct metal_uart *)__METAL_DT_SERIAL_20000000_HANDLE;
    uart0_ic = metal_uart_interrupt_controller(uart0);
    if (uart0_ic == NULL) {
        printf("UART0 interrupt controller is null.\n");
        return 4;
    }
    metal_interrupt_init(uart0_ic);
    uart0_irq = metal_uart_get_interrupt_id(uart0);
    rc = metal_interrupt_register_handler(uart0_ic, uart0_irq, uart0_isr, led0_red);
    if (rc < 0) {
        printf("Uart0 interrupt handler registration failed\n");
        return (rc * -1);
    }

    // Lets enable the Uart interrupt
    txcnt =  metal_uart_get_transmit_watermark(uart0);
    metal_uart_set_transmit_watermark(uart0, 1);
    metal_uart_transmit_interrupt_enable(uart0);
    display_instruction();
    if (metal_interrupt_enable(uart0_ic, uart0_irq) == -1) {
        printf("Uart0 interrupt enable failed\n");
        return 5;
    }
    // Lastly CPU interrupt
    if (metal_interrupt_enable(cpu_intr, 0) == -1) {
        printf("CPU interrupt enable failed\n");
        return 6;
    }

    metal_uart_set_transmit_watermark(uart0, txcnt);
    metal_uart_transmit_interrupt_enable(uart0);
    //display_instruction();

    while (1) {
        asm volatile ("wfi");
    }

    return 0;
}
