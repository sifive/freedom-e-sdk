#ifndef ASSEMBLY

#ifndef FREEDOM_E310_ARTY__MEE_H
#define FREEDOM_E310_ARTY__MEE_H

#define __MEE_CLINT_2000000_INTERRUPTS 		2
#define MEE_MAX_CLINT_INTERRUPTS	 __MEE_CLINT_2000000_INTERRUPTS

#define __MEE_INTERRUPT_CONTROLLER_C000000_INTERRUPTS 		1
#define MEE_MAX_PLIC_INTERRUPTS	 __MEE_INTERRUPT_CONTROLLER_C000000_INTERRUPTS

#define __MEE_LOCAL_EXTERNAL_INTERRUPTS_0_INTERRUPTS 		16
#define MEE_MAX_LOCAL_EXT_INTERRUPTS	 __MEE_LOCAL_EXTERNAL_INTERRUPTS_0_INTERRUPTS

#define __MEE_GPIO_10012000_INTERRUPTS 		16
#define MEE_MAX_GPIO_INTERRUPTS	 __MEE_GPIO_10012000_INTERRUPTS

#define __MEE_SERIAL_10013000_INTERRUPTS 		1
#define MEE_MAX_UART_INTERRUPTS	 __MEE_SERIAL_10013000_INTERRUPTS

#include <mee/drivers/riscv,cpu.h>
#include <mee/drivers/riscv,clint0.h>
#include <mee/drivers/riscv,plic0.h>
#include <mee/drivers/fixed-clock.h>
#include <mee/drivers/sifive,gpio0.h>
#include <mee/drivers/sifive,uart0.h>
#include <mee/drivers/sifive,local-external-interrupts0.h>
/* From cpu@0 */
asm (".weak __mee_dt_cpu_0");
struct __mee_driver_cpu __mee_dt_cpu_0;

/* From clint@2000000 */
asm (".weak __mee_dt_clint_2000000");
struct __mee_driver_riscv_clint0 __mee_dt_clint_2000000;

/* From interrupt_controller@c000000 */
asm (".weak __mee_dt_interrupt_controller_c000000");
struct __mee_driver_riscv_plic0 __mee_dt_interrupt_controller_c000000;

/* From interrupt_controller */
asm (".weak __mee_dt_interrupt_controller");
struct __mee_driver_riscv_cpu_intc __mee_dt_interrupt_controller;

/* From clock@0 */
asm (".weak __mee_dt_clock_0");
struct __mee_driver_fixed_clock __mee_dt_clock_0;

/* From local_external_interrupts_0 */
asm (".weak __mee_dt_local_external_interrupts_0");
struct __mee_driver_sifive_local_external_interrupts0 __mee_dt_local_external_interrupts_0;

/* From gpio@10012000 */
asm (".weak __mee_dt_gpio_10012000");
struct __mee_driver_sifive_gpio0 __mee_dt_gpio_10012000;

/* From serial@10013000 */
asm (".weak __mee_dt_serial_10013000");
struct __mee_driver_sifive_uart0 __mee_dt_serial_10013000;

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

/* From clock@0 */
struct __mee_driver_fixed_clock __mee_dt_clock_0 = {
    .vtable = &__mee_driver_vtable_fixed_clock,
    .clock.vtable = &__mee_driver_vtable_fixed_clock.clock,
    .rate = 65000000UL,
};

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

/* From clint@2000000 */
struct __mee_driver_riscv_clint0 __mee_dt_clint_2000000 = {
    .vtable = &__mee_driver_vtable_riscv_clint0,
    .clint.vtable = &__mee_driver_vtable_riscv_clint0.clint_vtable,
    .control_base = 33554432UL,
    .control_size = 65536UL,
    .init_done = 0,
    .num_interrupts = MEE_MAX_CLINT_INTERRUPTS,
    .interrupt_parent = &__mee_dt_interrupt_controller.controller,
    .interrupt_lines[0] = 3,
    .interrupt_lines[1] = 7,
};

/* From clint@2000000 */
#define __MEE_DT_RISCV_CLINT0_HANDLE (&__mee_dt_clint_2000000.clint)

#define __MEE_DT_CLINT_2000000_HANDLE (&__mee_dt_clint_2000000.clint)

/* From local_external_interrupts_0 */
struct __mee_driver_sifive_local_external_interrupts0 __mee_dt_local_external_interrupts_0 = {
    .vtable = &__mee_driver_vtable_sifive_local_external_interrupts0,
    .irc.vtable = &__mee_driver_vtable_sifive_local_external_interrupts0.local0_vtable,
/* From interrupt_controller */
    .interrupt_parent = &__mee_dt_interrupt_controller.controller,
    .num_interrupts = MEE_MAX_LOCAL_EXT_INTERRUPTS,
    .interrupt_lines[0] = 16,
    .interrupt_lines[1] = 17,
    .interrupt_lines[2] = 18,
    .interrupt_lines[3] = 19,
    .interrupt_lines[4] = 20,
    .interrupt_lines[5] = 21,
    .interrupt_lines[6] = 22,
    .interrupt_lines[7] = 23,
    .interrupt_lines[8] = 24,
    .interrupt_lines[9] = 25,
    .interrupt_lines[10] = 26,
    .interrupt_lines[11] = 27,
    .interrupt_lines[12] = 28,
    .interrupt_lines[13] = 29,
    .interrupt_lines[14] = 30,
    .interrupt_lines[15] = 31,
};

/* From local_external_interrupts_0 */
#define __MEE_DT_SIFIVE_LOCAL_EXINTR0_HANDLE (&__mee_dt_local_external_interrupts_0.irc)

#define __MEE_DT_LOCAL_EXTERNAL_INTERRUPTS_0_HANDLE (&__mee_dt_local_external_interrupts_0.irc)

/* From interrupt_controller@c000000 */
struct __mee_driver_riscv_plic0 __mee_dt_interrupt_controller_c000000 = {
    .vtable = &__mee_driver_vtable_riscv_plic0,
    .plic0.vtable = &__mee_driver_vtable_riscv_plic0.controller_vtable,
    .init_done = 0,
/* From interrupt_controller */
    .interrupt_parent = &__mee_dt_interrupt_controller.controller,
    .interrupt_line = 11UL,
    .control_base = 201326592UL,
    .control_size = 67108864UL,
    .max_priority = 7UL,
    .num_interrupts = 26UL,
    .interrupt_controller = 1,
};

/* From interrupt_controller@c000000 */
#define __MEE_DT_RISCV_PLIC0_HANDLE (&__mee_dt_interrupt_controller_c000000.plic0)

#define __MEE_DT_INTERRUPT_CONTROLLER_C000000_HANDLE (&__mee_dt_interrupt_controller_c000000.plic0)

/* From gpio@10012000 */
struct __mee_driver_sifive_gpio0 __mee_dt_gpio_10012000 = {
    .vtable = &__mee_driver_vtable_sifive_gpio0,
    .base = 268509184UL,
    .size = 4096UL,
/* From interrupt_controller@c000000 */
    .interrupt_parent = &__mee_dt_interrupt_controller_c000000.plic0,
    .num_interrupts = MEE_MAX_GPIO_INTERRUPTS,
    .interrupt_lines[0] = 7,
    .interrupt_lines[1] = 8,
    .interrupt_lines[2] = 9,
    .interrupt_lines[3] = 10,
    .interrupt_lines[4] = 11,
    .interrupt_lines[5] = 12,
    .interrupt_lines[6] = 13,
    .interrupt_lines[7] = 14,
    .interrupt_lines[8] = 15,
    .interrupt_lines[9] = 16,
    .interrupt_lines[10] = 17,
    .interrupt_lines[11] = 18,
    .interrupt_lines[12] = 19,
    .interrupt_lines[13] = 20,
    .interrupt_lines[14] = 21,
    .interrupt_lines[15] = 22,
};

/* From serial@10013000 */
struct __mee_driver_sifive_uart0 __mee_dt_serial_10013000 = {
    .vtable = &__mee_driver_vtable_sifive_uart0,
    .uart.vtable = &__mee_driver_vtable_sifive_uart0.uart,
    .control_base = 268513280UL,
    .control_size = 4096UL,
/* From clock@0 */
    .clock = &__mee_dt_clock_0.clock,
/* From gpio@10012000 */
    .pinmux = &__mee_dt_gpio_10012000,
    .pinmux_output_selector = 196608UL,
    .pinmux_source_selector = 196608UL,
/* From interrupt_controller@c000000 */
    .interrupt_parent = &__mee_dt_interrupt_controller_c000000.plic0,
    .num_interrupts = MEE_MAX_UART_INTERRUPTS,
    .interrupt_line = 5UL,
};

/* From serial@10013000 */
#define __MEE_DT_STDOUT_UART_HANDLE (&__mee_dt_serial_10013000.uart)

#define __MEE_DT_SERIAL_10013000_HANDLE (&__mee_dt_serial_10013000.uart)

#define __MEE_DT_STDOUT_UART_BAUD 115200

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
#endif /*MEE__MACHINE__FREEDOM_E310_ARTY__MEE_H*/

#endif/*ASSEMBLY*/
