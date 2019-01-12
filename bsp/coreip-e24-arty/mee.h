#ifndef ASSEMBLY

#ifndef COREIP_E24_ARTY__MEE_H
#define COREIP_E24_ARTY__MEE_H

#define __MEE_GPIO_20002000_INTERRUPTS 		16
#define MEE_MAX_GPIO_INTERRUPTS	 __MEE_GPIO_20002000_INTERRUPTS

#define __MEE_SERIAL_20000000_INTERRUPTS 		1
#define MEE_MAX_UART_INTERRUPTS	 __MEE_SERIAL_20000000_INTERRUPTS

#include <mee/drivers/riscv,cpu.h>
#include <mee/drivers/sifive,gpio0.h>
#include <mee/drivers/sifive,uart0.h>
#include <mee/drivers/sifive,test0.h>
/* From cpu@0 */
asm (".weak __mee_dt_cpu_0");
struct __mee_driver_cpu __mee_dt_cpu_0;

/* From interrupt_controller */
asm (".weak __mee_dt_interrupt_controller");
struct __mee_driver_riscv_cpu_intc __mee_dt_interrupt_controller;

/* From gpio@20002000 */
asm (".weak __mee_dt_gpio_20002000");
struct __mee_driver_sifive_gpio0 __mee_dt_gpio_20002000;

/* From serial@20000000 */
asm (".weak __mee_dt_serial_20000000");
struct __mee_driver_sifive_uart0 __mee_dt_serial_20000000;

/* From teststatus@4000 */
asm (".weak __mee_dt_teststatus_4000");
struct __mee_driver_sifive_test0 __mee_dt_teststatus_4000;

/* From cpu@0 */
struct __mee_driver_cpu __mee_dt_cpu_0 = {
    .vtable = &__mee_driver_vtable_cpu,
    .cpu.vtable = &__mee_driver_vtable_cpu.cpu_vtable,
    .timebase = 1000000UL,
    .interrupt_controller = &__mee_dt_interrupt_controller.controller,
};

/* From cpu@0 */
#define __MEE_DT_RISCV_CPU_HANDLE (&__mee_dt_cpu_0.cpu)

#define __MEE_DT_CPU_0_HANDLE (&__mee_dt_cpu_0.cpu)

/* From interrupt_controller */
struct __mee_driver_riscv_cpu_intc __mee_dt_interrupt_controller = {
    .vtable = &__mee_driver_vtable_riscv_cpu_intc,
    .controller.vtable = &__mee_driver_vtable_riscv_cpu_intc.controller_vtable,
    .init_done = 0,
    .interrupt_controller = 1,
};

/* From interrupt_controller */
#define __MEE_DT_RISCV_CPU_INTC_HANDLE (&__mee_dt_interrupt_controller.controller)

#define __MEE_DT_INTERRUPT_CONTROLLER_HANDLE (&__mee_dt_interrupt_controller.controller)

/* From gpio@20002000 */
struct __mee_driver_sifive_gpio0 __mee_dt_gpio_20002000 = {
    .vtable = &__mee_driver_vtable_sifive_gpio0,
    .base = 536879104UL,
    .size = 4096UL,
/* From interrupt_controller@2000000 */
    .interrupt_parent = &__mee_dt_interrupt_controller_2000000.plic0,
    .num_interrupts = MEE_MAX_GPIO_INTERRUPTS,
    .interrupt_lines[0] = 6,
    .interrupt_lines[1] = 7,
    .interrupt_lines[2] = 8,
    .interrupt_lines[3] = 9,
    .interrupt_lines[4] = 10,
    .interrupt_lines[5] = 11,
    .interrupt_lines[6] = 12,
    .interrupt_lines[7] = 13,
    .interrupt_lines[8] = 14,
    .interrupt_lines[9] = 15,
    .interrupt_lines[10] = 16,
    .interrupt_lines[11] = 17,
    .interrupt_lines[12] = 18,
    .interrupt_lines[13] = 19,
    .interrupt_lines[14] = 20,
    .interrupt_lines[15] = 21,
};

/* From serial@20000000 */
struct __mee_driver_sifive_uart0 __mee_dt_serial_20000000 = {
    .vtable = &__mee_driver_vtable_sifive_uart0,
    .uart.vtable = &__mee_driver_vtable_sifive_uart0.uart,
    .control_base = 536870912UL,
    .control_size = 4096UL,
    .clock = NULL,
    .pinmux = NULL,
/* From interrupt_controller@2000000 */
    .interrupt_parent = &__mee_dt_interrupt_controller_2000000.plic0,
    .num_interrupts = MEE_MAX_UART_INTERRUPTS,
    .interrupt_line = 4UL,
};

/* From teststatus@4000 */
struct __mee_driver_sifive_test0 __mee_dt_teststatus_4000 = {
    .vtable = &__mee_driver_vtable_sifive_test0,
    .shutdown.vtable = &__mee_driver_vtable_sifive_test0.shutdown,
    .base = 16384UL,
    .size = 4096UL,
};

/* From teststatus@4000 */
#define __MEE_DT_SHUTDOWN_HANDLE (&__mee_dt_teststatus_4000.shutdown)

#define __MEE_DT_TESTSTATUS_4000_HANDLE (&__mee_dt_teststatus_4000.shutdown)

#define __MEE_DT_MAX_HARTS 1

asm (".weak __mee_cpu_table");
struct __mee_driver_cpu *__mee_cpu_table[] = {
					&__mee_dt_cpu_0};

#define __MEE_DT_MAX_LEDS 0

asm (".weak __mee_led_table");
struct __mee_driver_sifive_gpio_led *__mee_led_table[] = {
					NULL };
#define __MEE_DT_MAX_BUTTONS 0

asm (".weak __mee_button_table");
struct __mee_driver_sifive_gpio_button *__mee_button_table[] = {
					NULL };
#define __MEE_DT_MAX_SWITCHES 0

asm (".weak __mee_switch_table");
struct __mee_driver_sifive_gpio_switch *__mee_switch_table[] = {
					NULL };
#endif /*MEE__MACHINE__COREIP_E24_ARTY__MEE_H*/

#endif/*ASSEMBLY*/
