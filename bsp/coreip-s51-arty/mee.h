#ifndef ASSEMBLY

#ifndef COREIP_S51_ARTY__MEE_H
#define COREIP_S51_ARTY__MEE_H

#define __MEE_CLINT_2000000_INTERRUPTS 		2
#define MEE_MAX_CLINT_INTERRUPTS	 __MEE_CLINT_2000000_INTERRUPTS

#define __MEE_INTERRUPT_CONTROLLER_C000000_INTERRUPTS 		1
#define MEE_MAX_PLIC_INTERRUPTS	 __MEE_INTERRUPT_CONTROLLER_C000000_INTERRUPTS

#define __MEE_LOCAL_EXTERNAL_INTERRUPTS_0_INTERRUPTS 		16
#define MEE_MAX_LOCAL_EXT_INTERRUPTS	 __MEE_LOCAL_EXTERNAL_INTERRUPTS_0_INTERRUPTS

#define __MEE_GLOBAL_EXTERNAL_INTERRUPTS_INTERRUPTS 		4
#define MEE_MAX_GLOBAL_EXT_INTERRUPTS	 __MEE_GLOBAL_EXTERNAL_INTERRUPTS_INTERRUPTS

#define __MEE_GPIO_20002000_INTERRUPTS 		16
#define MEE_MAX_GPIO_INTERRUPTS	 __MEE_GPIO_20002000_INTERRUPTS

#define __MEE_SERIAL_20000000_INTERRUPTS 		1
#define MEE_MAX_UART_INTERRUPTS	 __MEE_SERIAL_20000000_INTERRUPTS

#include <mee/drivers/riscv,cpu.h>
#include <mee/drivers/riscv,clint0.h>
#include <mee/drivers/riscv,plic0.h>
#include <mee/drivers/fixed-clock.h>
#include <mee/drivers/sifive,gpio0.h>
#include <mee/drivers/sifive,uart0.h>
#include <mee/drivers/sifive,local-external-interrupts0.h>
#include <mee/drivers/sifive,global-external-interrupts0.h>
#include <mee/drivers/sifive,gpio-leds.h>
#include <mee/drivers/sifive,gpio-buttons.h>
#include <mee/drivers/sifive,gpio-switches.h>
#include <mee/drivers/sifive,test0.h>
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

/* From global_external_interrupts */
asm (".weak __mee_dt_global_external_interrupts");
struct __mee_driver_sifive_global_external_interrupts0 __mee_dt_global_external_interrupts;

/* From gpio@20002000 */
asm (".weak __mee_dt_gpio_20002000");
struct __mee_driver_sifive_gpio0 __mee_dt_gpio_20002000;

/* From serial@20000000 */
asm (".weak __mee_dt_serial_20000000");
struct __mee_driver_sifive_uart0 __mee_dt_serial_20000000;

/* From led@0red */
asm (".weak __mee_dt_led_0red");
struct __mee_driver_sifive_gpio_led __mee_dt_led_0red;

/* From led@0green */
asm (".weak __mee_dt_led_0green");
struct __mee_driver_sifive_gpio_led __mee_dt_led_0green;

/* From led@0blue */
asm (".weak __mee_dt_led_0blue");
struct __mee_driver_sifive_gpio_led __mee_dt_led_0blue;

/* From button@0 */
asm (".weak __mee_dt_button_0");
struct __mee_driver_sifive_gpio_button __mee_dt_button_0;

/* From button@1 */
asm (".weak __mee_dt_button_1");
struct __mee_driver_sifive_gpio_button __mee_dt_button_1;

/* From button@2 */
asm (".weak __mee_dt_button_2");
struct __mee_driver_sifive_gpio_button __mee_dt_button_2;

/* From button@3 */
asm (".weak __mee_dt_button_3");
struct __mee_driver_sifive_gpio_button __mee_dt_button_3;

/* From switch@0 */
asm (".weak __mee_dt_switch_0");
struct __mee_driver_sifive_gpio_switch __mee_dt_switch_0;

/* From switch@1 */
asm (".weak __mee_dt_switch_1");
struct __mee_driver_sifive_gpio_switch __mee_dt_switch_1;

/* From switch@2 */
asm (".weak __mee_dt_switch_2");
struct __mee_driver_sifive_gpio_switch __mee_dt_switch_2;

/* From switch@3 */
asm (".weak __mee_dt_switch_3");
struct __mee_driver_sifive_gpio_switch __mee_dt_switch_3;

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

/* From clock@0 */
struct __mee_driver_fixed_clock __mee_dt_clock_0 = {
    .vtable = &__mee_driver_vtable_fixed_clock,
    .clock.vtable = &__mee_driver_vtable_fixed_clock.clock,
    .rate = 32500000UL,
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
    .init_done = 0,
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

/* From global_external_interrupts */
struct __mee_driver_sifive_global_external_interrupts0 __mee_dt_global_external_interrupts = {
    .vtable = &__mee_driver_vtable_sifive_global_external_interrupts0,
    .irc.vtable = &__mee_driver_vtable_sifive_global_external_interrupts0.global0_vtable,
    .init_done = 0,
/* From interrupt_controller@c000000 */
    .interrupt_parent = &__mee_dt_interrupt_controller_c000000.plic0,
    .num_interrupts = MEE_MAX_GLOBAL_EXT_INTERRUPTS,
    .interrupt_lines[0] = 1,
    .interrupt_lines[1] = 2,
    .interrupt_lines[2] = 3,
    .interrupt_lines[3] = 4,
};

/* From global_external_interrupts */
#define __MEE_DT_SIFIVE_GLOBAL_EXINTR0_HANDLE (&__mee_dt_global_external_interrupts.irc)

#define __MEE_DT_GLOBAL_EXTERNAL_INTERRUPTS_HANDLE (&__mee_dt_global_external_interrupts.irc)

/* From gpio@20002000 */
struct __mee_driver_sifive_gpio0 __mee_dt_gpio_20002000 = {
    .vtable = &__mee_driver_vtable_sifive_gpio0,
    .base = 536879104UL,
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

/* From serial@20000000 */
struct __mee_driver_sifive_uart0 __mee_dt_serial_20000000 = {
    .vtable = &__mee_driver_vtable_sifive_uart0,
    .uart.vtable = &__mee_driver_vtable_sifive_uart0.uart,
    .control_base = 536870912UL,
    .control_size = 4096UL,
/* From clock@0 */
    .clock = &__mee_dt_clock_0.clock,
    .pinmux = NULL,
/* From interrupt_controller@c000000 */
    .interrupt_parent = &__mee_dt_interrupt_controller_c000000.plic0,
    .num_interrupts = MEE_MAX_UART_INTERRUPTS,
    .interrupt_line = 5UL,
};

/* From led@0red */
struct __mee_driver_sifive_gpio_led __mee_dt_led_0red = {
    .vtable = &__mee_driver_vtable_sifive_led,
    .led.vtable = &__mee_driver_vtable_sifive_led.led_vtable,
/* From gpio@20002000 */
    .gpio = &__mee_dt_gpio_20002000,
    .pin = 0UL,
    .label = "LD0red",
};

/* From led@0green */
struct __mee_driver_sifive_gpio_led __mee_dt_led_0green = {
    .vtable = &__mee_driver_vtable_sifive_led,
    .led.vtable = &__mee_driver_vtable_sifive_led.led_vtable,
/* From gpio@20002000 */
    .gpio = &__mee_dt_gpio_20002000,
    .pin = 1UL,
    .label = "LD0green",
};

/* From led@0blue */
struct __mee_driver_sifive_gpio_led __mee_dt_led_0blue = {
    .vtable = &__mee_driver_vtable_sifive_led,
    .led.vtable = &__mee_driver_vtable_sifive_led.led_vtable,
/* From gpio@20002000 */
    .gpio = &__mee_dt_gpio_20002000,
    .pin = 2UL,
    .label = "LD0blue",
};

/* From button@0 */
struct __mee_driver_sifive_gpio_button __mee_dt_button_0 = {
    .vtable = &__mee_driver_vtable_sifive_button,
    .button.vtable = &__mee_driver_vtable_sifive_button.button_vtable,
/* From gpio@20002000 */
    .gpio = &__mee_dt_gpio_20002000,
    .pin = 4UL,
/* From local_external_interrupts_0 */
    .interrupt_parent = &__mee_dt_local_external_interrupts_0.irc,
    .interrupt_line = 4UL,
    .label = "BTN0",
};

/* From button@1 */
struct __mee_driver_sifive_gpio_button __mee_dt_button_1 = {
    .vtable = &__mee_driver_vtable_sifive_button,
    .button.vtable = &__mee_driver_vtable_sifive_button.button_vtable,
/* From gpio@20002000 */
    .gpio = &__mee_dt_gpio_20002000,
    .pin = 5UL,
/* From local_external_interrupts_0 */
    .interrupt_parent = &__mee_dt_local_external_interrupts_0.irc,
    .interrupt_line = 5UL,
    .label = "BTN1",
};

/* From button@2 */
struct __mee_driver_sifive_gpio_button __mee_dt_button_2 = {
    .vtable = &__mee_driver_vtable_sifive_button,
    .button.vtable = &__mee_driver_vtable_sifive_button.button_vtable,
/* From gpio@20002000 */
    .gpio = &__mee_dt_gpio_20002000,
    .pin = 6UL,
/* From local_external_interrupts_0 */
    .interrupt_parent = &__mee_dt_local_external_interrupts_0.irc,
    .interrupt_line = 6UL,
    .label = "BTN2",
};

/* From button@3 */
struct __mee_driver_sifive_gpio_button __mee_dt_button_3 = {
    .vtable = &__mee_driver_vtable_sifive_button,
    .button.vtable = &__mee_driver_vtable_sifive_button.button_vtable,
/* From gpio@20002000 */
    .gpio = &__mee_dt_gpio_20002000,
    .pin = 7UL,
/* From local_external_interrupts_0 */
    .interrupt_parent = &__mee_dt_local_external_interrupts_0.irc,
    .interrupt_line = 7UL,
    .label = "BTN3",
};

/* From switch@0 */
struct __mee_driver_sifive_gpio_switch __mee_dt_switch_0 = {
    .vtable = &__mee_driver_vtable_sifive_switch,
    .flip.vtable = &__mee_driver_vtable_sifive_switch.switch_vtable,
/* From global_external_interrupts */
    .interrupt_parent = &__mee_dt_global_external_interrupts.irc,
    .interrupt_line = 0UL,
    .label = "SW0",
};

/* From switch@1 */
struct __mee_driver_sifive_gpio_switch __mee_dt_switch_1 = {
    .vtable = &__mee_driver_vtable_sifive_switch,
    .flip.vtable = &__mee_driver_vtable_sifive_switch.switch_vtable,
/* From global_external_interrupts */
    .interrupt_parent = &__mee_dt_global_external_interrupts.irc,
    .interrupt_line = 1UL,
    .label = "SW1",
};

/* From switch@2 */
struct __mee_driver_sifive_gpio_switch __mee_dt_switch_2 = {
    .vtable = &__mee_driver_vtable_sifive_switch,
    .flip.vtable = &__mee_driver_vtable_sifive_switch.switch_vtable,
/* From global_external_interrupts */
    .interrupt_parent = &__mee_dt_global_external_interrupts.irc,
    .interrupt_line = 2UL,
    .label = "SW2",
};

/* From switch@3 */
struct __mee_driver_sifive_gpio_switch __mee_dt_switch_3 = {
    .vtable = &__mee_driver_vtable_sifive_switch,
    .flip.vtable = &__mee_driver_vtable_sifive_switch.switch_vtable,
/* From local_external_interrupts_0 */
    .interrupt_parent = &__mee_dt_local_external_interrupts_0.irc,
    .interrupt_line = 3UL,
    .label = "SW3",
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

/* From serial@20000000 */
#define __MEE_DT_STDOUT_UART_HANDLE (&__mee_dt_serial_20000000.uart)

#define __MEE_DT_SERIAL_20000000_HANDLE (&__mee_dt_serial_20000000.uart)

#define __MEE_DT_STDOUT_UART_BAUD 115200

#define __MEE_DT_MAX_HARTS 1

asm (".weak __mee_cpu_table");
struct __mee_driver_cpu *__mee_cpu_table[] = {
					&__mee_dt_cpu_0};

#define __MEE_DT_MAX_LEDS 3

asm (".weak __mee_led_table");
struct __mee_driver_sifive_gpio_led *__mee_led_table[] = {
					&__mee_dt_led_0red,
					&__mee_dt_led_0green,
					&__mee_dt_led_0blue};

#define __MEE_DT_MAX_BUTTONS 4

asm (".weak __mee_button_table");
struct __mee_driver_sifive_gpio_button *__mee_button_table[] = {
					&__mee_dt_button_0,
					&__mee_dt_button_1,
					&__mee_dt_button_2,
					&__mee_dt_button_3};

#define __MEE_DT_MAX_SWITCHES 4

asm (".weak __mee_switch_table");
struct __mee_driver_sifive_gpio_switch *__mee_switch_table[] = {
					&__mee_dt_switch_0,
					&__mee_dt_switch_1,
					&__mee_dt_switch_2,
					&__mee_dt_switch_3};

#endif /*MEE__MACHINE__COREIP_S51_ARTY__MEE_H*/

#endif/*ASSEMBLY*/
