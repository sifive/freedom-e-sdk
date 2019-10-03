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
char response[MSG_MAX_LEN];

void uart_async_cb(struct metal_uart *uart, metal_uart_callback_cause cause) {
    if (cause == METAL_UART_RX_DONE) {
        snprintf(response, MSG_MAX_LEN, "You entered: %s after a count of %d\r\n", msg, counter);
        metal_uart_send_async(uart, response, strlen(response), uart_async_cb);
    } else if (cause == METAL_UART_TX_DONE) {
        puts("Done\n");
        exit(0);
    } else {
        exit(1);
    }
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

    puts("Please enter a 10-character message: ");

    metal_uart_recv_async(uart, msg, 10, uart_async_cb);

    while(1) {
        counter += 1;
    }

    return 0;
}

