/* Copyright 2019 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <metal/machine.h>
#include <metal/cpu.h>
#include <metal/uart.h>
#include <metal/interrupt.h>

volatile int counter = 0;

#define MSG_MAX_LEN 100
char msg[MSG_MAX_LEN];

void send_callback(struct metal_uart *uart, metal_uart_callback_cause cause) {
    if (cause != METAL_UART_TX_DONE) {
        exit(1);
    }

    puts("Done transmitting\n");
}

int main() {
    struct metal_cpu *cpu = metal_cpu_get(metal_cpu_get_current_hartid());
    struct metal_interrupt *cpu_intr = metal_cpu_interrupt_controller(cpu);
    metal_interrupt_init(cpu_intr);

    struct metal_uart *uart = (struct metal_uart *)__METAL_DT_SERIAL_10013000_HANDLE;
    struct metal_interrupt *uart_intr = metal_uart_interrupt_controller(uart);
    metal_interrupt_init(uart_intr);

    int uart_id = metal_uart_get_interrupt_id(uart);
    metal_uart_set_transmit_watermark(uart, 1);

    metal_interrupt_enable(uart_intr, uart_id);
    metal_interrupt_enable(cpu_intr, 0);
    
    while(1) {
        if (counter % 1000 == 0) {
            snprintf(msg, MSG_MAX_LEN, "Counter: %d\r\n", counter);
            metal_uart_send(uart, msg, strnlen(msg, MSG_MAX_LEN), send_callback);
        }
        counter += 1;
    }

    return 0;
}

