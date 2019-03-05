#ifndef ASSEMBLY

#ifndef COREIP_S54_ARTY__METAL_H
#define COREIP_S54_ARTY__METAL_H

#ifdef __METAL_MACHINE_MACROS

#ifndef __METAL_CLIC_SUBINTERRUPTS
#define __METAL_CLIC_SUBINTERRUPTS 0
#endif

#else /* ! __METAL_MACHINE_MACROS */

#define __METAL_CLINT_2000000_INTERRUPTS 2

#define METAL_MAX_CLINT_INTERRUPTS 2

#define __METAL_INTERRUPT_CONTROLLER_C000000_INTERRUPTS 1

#define METAL_MAX_PLIC_INTERRUPTS 1

#define METAL_MAX_CLIC_INTERRUPTS 0

#define __METAL_LOCAL_EXTERNAL_INTERRUPTS_0_INTERRUPTS 16

#define METAL_MAX_LOCAL_EXT_INTERRUPTS 16

#define __METAL_GLOBAL_EXTERNAL_INTERRUPTS_INTERRUPTS 4

#define METAL_MAX_GLOBAL_EXT_INTERRUPTS 4

#define __METAL_GPIO_20002000_INTERRUPTS 16

#define METAL_MAX_GPIO_INTERRUPTS 16

#define __METAL_SERIAL_20000000_INTERRUPTS 1

#define METAL_MAX_UART_INTERRUPTS 1


#include <metal/drivers/fixed-clock.h>
#include <metal/drivers/riscv,clint0.h>
#include <metal/drivers/riscv,cpu.h>
#include <metal/drivers/riscv,plic0.h>
#include <metal/pmp.h>
#include <metal/drivers/sifive,local-external-interrupts0.h>
#include <metal/drivers/sifive,global-external-interrupts0.h>
#include <metal/drivers/sifive,gpio0.h>
#include <metal/drivers/sifive,gpio-buttons.h>
#include <metal/drivers/sifive,gpio-leds.h>
#include <metal/drivers/sifive,gpio-switches.h>
#include <metal/drivers/sifive,spi0.h>
#include <metal/drivers/sifive,test0.h>
#include <metal/drivers/sifive,uart0.h>

/* From clock@0 */
asm (".weak __metal_dt_clock_0");
struct __metal_driver_fixed_clock __metal_dt_clock_0;

/* From clint@2000000 */
asm (".weak __metal_dt_clint_2000000");
struct __metal_driver_riscv_clint0 __metal_dt_clint_2000000;

/* From cpu@0 */
asm (".weak __metal_dt_cpu_0");
struct __metal_driver_cpu __metal_dt_cpu_0;

/* From interrupt_controller */
asm (".weak __metal_dt_interrupt_controller");
struct __metal_driver_riscv_cpu_intc __metal_dt_interrupt_controller;

/* From interrupt_controller@c000000 */
asm (".weak __metal_dt_interrupt_controller_c000000");
struct __metal_driver_riscv_plic0 __metal_dt_interrupt_controller_c000000;

asm (".weak __metal_dt_pmp_0");
struct metal_pmp __metal_dt_pmp_0;

/* From local_external_interrupts_0 */
asm (".weak __metal_dt_local_external_interrupts_0");
struct __metal_driver_sifive_local_external_interrupts0 __metal_dt_local_external_interrupts_0;

/* From global_external_interrupts */
asm (".weak __metal_dt_global_external_interrupts");
struct __metal_driver_sifive_global_external_interrupts0 __metal_dt_global_external_interrupts;

/* From gpio@20002000 */
asm (".weak __metal_dt_gpio_20002000");
struct __metal_driver_sifive_gpio0 __metal_dt_gpio_20002000;

/* From button@0 */
asm (".weak __metal_dt_button_0");
struct __metal_driver_sifive_gpio_button __metal_dt_button_0;

/* From button@1 */
asm (".weak __metal_dt_button_1");
struct __metal_driver_sifive_gpio_button __metal_dt_button_1;

/* From button@2 */
asm (".weak __metal_dt_button_2");
struct __metal_driver_sifive_gpio_button __metal_dt_button_2;

/* From button@3 */
asm (".weak __metal_dt_button_3");
struct __metal_driver_sifive_gpio_button __metal_dt_button_3;

/* From led@0red */
asm (".weak __metal_dt_led_0red");
struct __metal_driver_sifive_gpio_led __metal_dt_led_0red;

/* From led@0green */
asm (".weak __metal_dt_led_0green");
struct __metal_driver_sifive_gpio_led __metal_dt_led_0green;

/* From led@0blue */
asm (".weak __metal_dt_led_0blue");
struct __metal_driver_sifive_gpio_led __metal_dt_led_0blue;

/* From switch@0 */
asm (".weak __metal_dt_switch_0");
struct __metal_driver_sifive_gpio_switch __metal_dt_switch_0;

/* From switch@1 */
asm (".weak __metal_dt_switch_1");
struct __metal_driver_sifive_gpio_switch __metal_dt_switch_1;

/* From switch@2 */
asm (".weak __metal_dt_switch_2");
struct __metal_driver_sifive_gpio_switch __metal_dt_switch_2;

/* From switch@3 */
asm (".weak __metal_dt_switch_3");
struct __metal_driver_sifive_gpio_switch __metal_dt_switch_3;

/* From spi@20004000 */
asm (".weak __metal_dt_spi_20004000");
struct __metal_driver_sifive_spi0 __metal_dt_spi_20004000;

/* From teststatus@4000 */
asm (".weak __metal_dt_teststatus_4000");
struct __metal_driver_sifive_test0 __metal_dt_teststatus_4000;

/* From serial@20000000 */
asm (".weak __metal_dt_serial_20000000");
struct __metal_driver_sifive_uart0 __metal_dt_serial_20000000;


/* From clock@0 */
struct __metal_driver_fixed_clock __metal_dt_clock_0 = {
    .vtable = &__metal_driver_vtable_fixed_clock,
    .clock.vtable = &__metal_driver_vtable_fixed_clock.clock,
    .rate = 32500000UL,
};

/* From clint@2000000 */
struct __metal_driver_riscv_clint0 __metal_dt_clint_2000000 = {
    .vtable = &__metal_driver_vtable_riscv_clint0,
    .controller.vtable = &__metal_driver_vtable_riscv_clint0.clint_vtable,
    .control_base = 33554432UL,
    .control_size = 65536UL,
    .init_done = 0,
    .num_interrupts = METAL_MAX_CLINT_INTERRUPTS,
    .interrupt_parent = &__metal_dt_interrupt_controller.controller,
    .interrupt_lines[0] = 3,
    .interrupt_lines[1] = 7,
};

/* From cpu@0 */
struct __metal_driver_cpu __metal_dt_cpu_0 = {
    .vtable = &__metal_driver_vtable_cpu,
    .cpu.vtable = &__metal_driver_vtable_cpu.cpu_vtable,
    .timebase = 1000000UL,
    .interrupt_controller = &__metal_dt_interrupt_controller.controller,
};

/* From interrupt_controller */
struct __metal_driver_riscv_cpu_intc __metal_dt_interrupt_controller = {
    .vtable = &__metal_driver_vtable_riscv_cpu_intc,
    .controller.vtable = &__metal_driver_vtable_riscv_cpu_intc.controller_vtable,
    .init_done = 0,
    .interrupt_controller = 1,
};

/* From interrupt_controller@c000000 */
struct __metal_driver_riscv_plic0 __metal_dt_interrupt_controller_c000000 = {
    .vtable = &__metal_driver_vtable_riscv_plic0,
    .controller.vtable = &__metal_driver_vtable_riscv_plic0.plic_vtable,
    .init_done = 0,
/* From interrupt_controller */
    .interrupt_parent = &__metal_dt_interrupt_controller.controller,
    .interrupt_line = 11UL,
    .control_base = 201326592UL,
    .control_size = 67108864UL,
    .max_priority = 7UL,
    .num_interrupts = 26UL,
    .interrupt_controller = 1,
};

/* From pmp@0 */
struct metal_pmp __metal_dt_pmp_0 = {
    .num_regions = 8UL,
};

/* From local_external_interrupts_0 */
struct __metal_driver_sifive_local_external_interrupts0 __metal_dt_local_external_interrupts_0 = {
    .vtable = &__metal_driver_vtable_sifive_local_external_interrupts0,
    .irc.vtable = &__metal_driver_vtable_sifive_local_external_interrupts0.local0_vtable,
    .init_done = 0,
/* From interrupt_controller */
    .interrupt_parent = &__metal_dt_interrupt_controller.controller,
    .num_interrupts = METAL_MAX_LOCAL_EXT_INTERRUPTS,
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

/* From global_external_interrupts */
struct __metal_driver_sifive_global_external_interrupts0 __metal_dt_global_external_interrupts = {
    .vtable = &__metal_driver_vtable_sifive_global_external_interrupts0,
    .irc.vtable = &__metal_driver_vtable_sifive_global_external_interrupts0.global0_vtable,
    .init_done = 0,
/* From interrupt_controller@c000000 */
    .interrupt_parent = &__metal_dt_interrupt_controller_c000000.controller,
    .num_interrupts = METAL_MAX_GLOBAL_EXT_INTERRUPTS,
    .interrupt_lines[0] = 23,
    .interrupt_lines[1] = 24,
    .interrupt_lines[2] = 25,
    .interrupt_lines[3] = 26,
};

/* From gpio@20002000 */
struct __metal_driver_sifive_gpio0 __metal_dt_gpio_20002000 = {
    .vtable = &__metal_driver_vtable_sifive_gpio0,
    .base = 536879104UL,
    .size = 4096UL,
/* From interrupt_controller@c000000 */
    .interrupt_parent = &__metal_dt_interrupt_controller_c000000.controller,
    .num_interrupts = METAL_MAX_GPIO_INTERRUPTS,
    .interrupt_lines[0] = 1,
    .interrupt_lines[1] = 2,
    .interrupt_lines[2] = 3,
    .interrupt_lines[3] = 4,
    .interrupt_lines[4] = 5,
    .interrupt_lines[5] = 6,
    .interrupt_lines[6] = 7,
    .interrupt_lines[7] = 8,
    .interrupt_lines[8] = 9,
    .interrupt_lines[9] = 10,
    .interrupt_lines[10] = 11,
    .interrupt_lines[11] = 12,
    .interrupt_lines[12] = 13,
    .interrupt_lines[13] = 14,
    .interrupt_lines[14] = 15,
    .interrupt_lines[15] = 16,
};

/* From button@0 */
struct __metal_driver_sifive_gpio_button __metal_dt_button_0 = {
    .vtable = &__metal_driver_vtable_sifive_button,
    .button.vtable = &__metal_driver_vtable_sifive_button.button_vtable,
/* From gpio@20002000 */
    .gpio = &__metal_dt_gpio_20002000,
    .pin = 4UL,
/* From local_external_interrupts_0 */
    .interrupt_parent = &__metal_dt_local_external_interrupts_0.irc,
    .interrupt_line = 4UL,
    .label = "BTN0",
};

/* From button@1 */
struct __metal_driver_sifive_gpio_button __metal_dt_button_1 = {
    .vtable = &__metal_driver_vtable_sifive_button,
    .button.vtable = &__metal_driver_vtable_sifive_button.button_vtable,
/* From gpio@20002000 */
    .gpio = &__metal_dt_gpio_20002000,
    .pin = 5UL,
/* From local_external_interrupts_0 */
    .interrupt_parent = &__metal_dt_local_external_interrupts_0.irc,
    .interrupt_line = 5UL,
    .label = "BTN1",
};

/* From button@2 */
struct __metal_driver_sifive_gpio_button __metal_dt_button_2 = {
    .vtable = &__metal_driver_vtable_sifive_button,
    .button.vtable = &__metal_driver_vtable_sifive_button.button_vtable,
/* From gpio@20002000 */
    .gpio = &__metal_dt_gpio_20002000,
    .pin = 6UL,
/* From local_external_interrupts_0 */
    .interrupt_parent = &__metal_dt_local_external_interrupts_0.irc,
    .interrupt_line = 6UL,
    .label = "BTN2",
};

/* From button@3 */
struct __metal_driver_sifive_gpio_button __metal_dt_button_3 = {
    .vtable = &__metal_driver_vtable_sifive_button,
    .button.vtable = &__metal_driver_vtable_sifive_button.button_vtable,
/* From gpio@20002000 */
    .gpio = &__metal_dt_gpio_20002000,
    .pin = 7UL,
/* From local_external_interrupts_0 */
    .interrupt_parent = &__metal_dt_local_external_interrupts_0.irc,
    .interrupt_line = 7UL,
    .label = "BTN3",
};

/* From led@0red */
struct __metal_driver_sifive_gpio_led __metal_dt_led_0red = {
    .vtable = &__metal_driver_vtable_sifive_led,
    .led.vtable = &__metal_driver_vtable_sifive_led.led_vtable,
/* From gpio@20002000 */
    .gpio = &__metal_dt_gpio_20002000,
    .pin = 0UL,
    .label = "LD0red",
};

/* From led@0green */
struct __metal_driver_sifive_gpio_led __metal_dt_led_0green = {
    .vtable = &__metal_driver_vtable_sifive_led,
    .led.vtable = &__metal_driver_vtable_sifive_led.led_vtable,
/* From gpio@20002000 */
    .gpio = &__metal_dt_gpio_20002000,
    .pin = 1UL,
    .label = "LD0green",
};

/* From led@0blue */
struct __metal_driver_sifive_gpio_led __metal_dt_led_0blue = {
    .vtable = &__metal_driver_vtable_sifive_led,
    .led.vtable = &__metal_driver_vtable_sifive_led.led_vtable,
/* From gpio@20002000 */
    .gpio = &__metal_dt_gpio_20002000,
    .pin = 2UL,
    .label = "LD0blue",
};

/* From switch@0 */
struct __metal_driver_sifive_gpio_switch __metal_dt_switch_0 = {
    .vtable = &__metal_driver_vtable_sifive_switch,
    .flip.vtable = &__metal_driver_vtable_sifive_switch.switch_vtable,
    .gpio = NULL,
    .pin = 0,
/* From global_external_interrupts */
    .interrupt_parent = &__metal_dt_global_external_interrupts.irc,
    .interrupt_line = 0UL,
    .label = "SW0",
};

/* From switch@1 */
struct __metal_driver_sifive_gpio_switch __metal_dt_switch_1 = {
    .vtable = &__metal_driver_vtable_sifive_switch,
    .flip.vtable = &__metal_driver_vtable_sifive_switch.switch_vtable,
    .gpio = NULL,
    .pin = 0,
/* From global_external_interrupts */
    .interrupt_parent = &__metal_dt_global_external_interrupts.irc,
    .interrupt_line = 1UL,
    .label = "SW1",
};

/* From switch@2 */
struct __metal_driver_sifive_gpio_switch __metal_dt_switch_2 = {
    .vtable = &__metal_driver_vtable_sifive_switch,
    .flip.vtable = &__metal_driver_vtable_sifive_switch.switch_vtable,
    .gpio = NULL,
    .pin = 0,
/* From global_external_interrupts */
    .interrupt_parent = &__metal_dt_global_external_interrupts.irc,
    .interrupt_line = 2UL,
    .label = "SW2",
};

/* From switch@3 */
struct __metal_driver_sifive_gpio_switch __metal_dt_switch_3 = {
    .vtable = &__metal_driver_vtable_sifive_switch,
    .flip.vtable = &__metal_driver_vtable_sifive_switch.switch_vtable,
    .gpio = NULL,
    .pin = 0,
/* From local_external_interrupts_0 */
    .interrupt_parent = &__metal_dt_local_external_interrupts_0.irc,
    .interrupt_line = 3UL,
    .label = "SW3",
};

/* From spi@20004000 */
struct __metal_driver_sifive_spi0 __metal_dt_spi_20004000 = {
    .vtable = &__metal_driver_vtable_sifive_spi0,
    .spi.vtable = &__metal_driver_vtable_sifive_spi0.spi,
    .control_base = 536887296UL,
    .control_size = 4096UL,
    .clock = NULL,
    .pinmux = NULL,
};

/* From teststatus@4000 */
struct __metal_driver_sifive_test0 __metal_dt_teststatus_4000 = {
    .vtable = &__metal_driver_vtable_sifive_test0,
    .shutdown.vtable = &__metal_driver_vtable_sifive_test0.shutdown,
    .base = 16384UL,
    .size = 4096UL,
};

/* From serial@20000000 */
struct __metal_driver_sifive_uart0 __metal_dt_serial_20000000 = {
    .vtable = &__metal_driver_vtable_sifive_uart0,
    .uart.vtable = &__metal_driver_vtable_sifive_uart0.uart,
    .control_base = 536870912UL,
    .control_size = 4096UL,
/* From clock@0 */
    .clock = &__metal_dt_clock_0.clock,
    .pinmux = NULL,
/* From interrupt_controller@c000000 */
    .interrupt_parent = &__metal_dt_interrupt_controller_c000000.controller,
    .num_interrupts = METAL_MAX_UART_INTERRUPTS,
    .interrupt_line = 17UL,
};


/* From serial@20000000 */
#define __METAL_DT_STDOUT_UART_HANDLE (&__metal_dt_serial_20000000.uart)

#define __METAL_DT_SERIAL_20000000_HANDLE (&__metal_dt_serial_20000000.uart)

#define __METAL_DT_STDOUT_UART_BAUD 115200

/* From clint@2000000 */
#define __METAL_DT_RISCV_CLINT0_HANDLE (&__metal_dt_clint_2000000.controller)

#define __METAL_DT_CLINT_2000000_HANDLE (&__metal_dt_clint_2000000.controller)

/* From cpu@0 */
#define __METAL_DT_RISCV_CPU_HANDLE (&__metal_dt_cpu_0.cpu)

#define __METAL_DT_CPU_0_HANDLE (&__metal_dt_cpu_0.cpu)

#define __METAL_DT_MAX_HARTS 1

asm (".weak __metal_cpu_table");
struct __metal_driver_cpu *__metal_cpu_table[] = {
					&__metal_dt_cpu_0};

/* From interrupt_controller */
#define __METAL_DT_RISCV_CPU_INTC_HANDLE (&__metal_dt_interrupt_controller.controller)

#define __METAL_DT_INTERRUPT_CONTROLLER_HANDLE (&__metal_dt_interrupt_controller.controller)

/* From interrupt_controller@c000000 */
#define __METAL_DT_RISCV_PLIC0_HANDLE (&__metal_dt_interrupt_controller_c000000.controller)

#define __METAL_DT_INTERRUPT_CONTROLLER_C000000_HANDLE (&__metal_dt_interrupt_controller_c000000.controller)

/* From pmp@0 */
#define __METAL_DT_PMP_HANDLE (&__metal_dt_pmp_0)

/* From local_external_interrupts_0 */
#define __METAL_DT_SIFIVE_LOCAL_EXINTR0_HANDLE (&__metal_dt_local_external_interrupts_0.irc)

#define __METAL_DT_LOCAL_EXTERNAL_INTERRUPTS_0_HANDLE (&__metal_dt_local_external_interrupts_0.irc)

/* From global_external_interrupts */
#define __METAL_DT_SIFIVE_GLOBAL_EXINTR0_HANDLE (&__metal_dt_global_external_interrupts.irc)

#define __METAL_DT_GLOBAL_EXTERNAL_INTERRUPTS_HANDLE (&__metal_dt_global_external_interrupts.irc)

#define __METAL_DT_MAX_BUTTONS 4

asm (".weak __metal_button_table");
struct __metal_driver_sifive_gpio_button *__metal_button_table[] = {
					&__metal_dt_button_0,
					&__metal_dt_button_1,
					&__metal_dt_button_2,
					&__metal_dt_button_3};

#define __METAL_DT_MAX_LEDS 3

asm (".weak __metal_led_table");
struct __metal_driver_sifive_gpio_led *__metal_led_table[] = {
					&__metal_dt_led_0red,
					&__metal_dt_led_0green,
					&__metal_dt_led_0blue};

#define __METAL_DT_MAX_SWITCHES 4

asm (".weak __metal_switch_table");
struct __metal_driver_sifive_gpio_switch *__metal_switch_table[] = {
					&__metal_dt_switch_0,
					&__metal_dt_switch_1,
					&__metal_dt_switch_2,
					&__metal_dt_switch_3};

#define __METAL_DT_MAX_SPIS 1

asm (".weak __metal_spi_table");
struct __metal_driver_sifive_spi0 *__metal_spi_table[] = {
					&__metal_dt_spi_20004000};

/* From teststatus@4000 */
#define __METAL_DT_SHUTDOWN_HANDLE (&__metal_dt_teststatus_4000.shutdown)

#define __METAL_DT_TESTSTATUS_4000_HANDLE (&__metal_dt_teststatus_4000.shutdown)


#endif /* ! __METAL_MACHINE_MACROS */
#endif /* COREIP_S54_ARTY__METAL_H*/
#endif /* ! ASSEMBLY */
