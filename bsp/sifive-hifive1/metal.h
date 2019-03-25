#ifndef ASSEMBLY

#ifndef SIFIVE_HIFIVE1__METAL_H
#define SIFIVE_HIFIVE1__METAL_H

#ifdef __METAL_MACHINE_MACROS

#define __METAL_PLIC_SUBINTERRUPTS 27

#ifndef __METAL_PLIC_SUBINTERRUPTS
#define __METAL_PLIC_SUBINTERRUPTS 0
#endif
#ifndef __METAL_CLIC_SUBINTERRUPTS
#define __METAL_CLIC_SUBINTERRUPTS 0
#endif

#else /* ! __METAL_MACHINE_MACROS */

#define __METAL_CLINT_2000000_INTERRUPTS 2

#define METAL_MAX_CLINT_INTERRUPTS 2

#define __METAL_INTERRUPT_CONTROLLER_C000000_INTERRUPTS 1

#define __METAL_PLIC_SUBINTERRUPTS 27

#define METAL_MAX_PLIC_INTERRUPTS 1

#define __METAL_CLIC_SUBINTERRUPTS 0
#define METAL_MAX_CLIC_INTERRUPTS 0

#define __METAL_LOCAL_EXTERNAL_INTERRUPTS_0_INTERRUPTS 16

#define METAL_MAX_LOCAL_EXT_INTERRUPTS 16

#define METAL_MAX_GLOBAL_EXT_INTERRUPTS 0

#define __METAL_GPIO_10012000_INTERRUPTS 16

#define METAL_MAX_GPIO_INTERRUPTS 16

#define __METAL_SERIAL_10013000_INTERRUPTS 1

#define METAL_MAX_UART_INTERRUPTS 1


#include <metal/drivers/fixed-clock.h>
#include <metal/drivers/riscv,clint0.h>
#include <metal/drivers/riscv,cpu.h>
#include <metal/drivers/riscv,plic0.h>
#include <metal/pmp.h>
#include <metal/drivers/sifive,local-external-interrupts0.h>
#include <metal/drivers/sifive,gpio0.h>
#include <metal/drivers/sifive,spi0.h>
#include <metal/drivers/sifive,uart0.h>
#include <metal/drivers/sifive,fe310-g000,hfrosc.h>
#include <metal/drivers/sifive,fe310-g000,hfxosc.h>
#include <metal/drivers/sifive,fe310-g000,pll.h>
#include <metal/drivers/sifive,fe310-g000,prci.h>

/* From clock@0 */
asm (".weak __metal_dt_clock_0");
struct __metal_driver_fixed_clock __metal_dt_clock_0;

/* From clock@2 */
asm (".weak __metal_dt_clock_2");
struct __metal_driver_fixed_clock __metal_dt_clock_2;

/* From clock@5 */
asm (".weak __metal_dt_clock_5");
struct __metal_driver_fixed_clock __metal_dt_clock_5;

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

/* From local_external_interrupts_0 */
asm (".weak __metal_dt_local_external_interrupts_0");
struct __metal_driver_sifive_local_external_interrupts0 __metal_dt_local_external_interrupts_0;

/* From gpio@10012000 */
asm (".weak __metal_dt_gpio_10012000");
struct __metal_driver_sifive_gpio0 __metal_dt_gpio_10012000;

/* From spi@10014000 */
asm (".weak __metal_dt_spi_10014000");
struct __metal_driver_sifive_spi0 __metal_dt_spi_10014000;

/* From serial@10013000 */
asm (".weak __metal_dt_serial_10013000");
struct __metal_driver_sifive_uart0 __metal_dt_serial_10013000;

/* From clock@3 */
asm (".weak __metal_dt_clock_3");
struct __metal_driver_sifive_fe310_g000_hfrosc __metal_dt_clock_3;

/* From clock@1 */
asm (".weak __metal_dt_clock_1");
struct __metal_driver_sifive_fe310_g000_hfxosc __metal_dt_clock_1;

/* From clock@4 */
asm (".weak __metal_dt_clock_4");
struct __metal_driver_sifive_fe310_g000_pll __metal_dt_clock_4;

/* From prci@10008000 */
asm (".weak __metal_dt_prci_10008000");
struct __metal_driver_sifive_fe310_g000_prci __metal_dt_prci_10008000;


/* From clock@0 */
struct __metal_driver_fixed_clock __metal_dt_clock_0 = {
    .vtable = &__metal_driver_vtable_fixed_clock,
    .clock.vtable = &__metal_driver_vtable_fixed_clock.clock,
    .rate = 16000000UL,
};

/* From clock@2 */
struct __metal_driver_fixed_clock __metal_dt_clock_2 = {
    .vtable = &__metal_driver_vtable_fixed_clock,
    .clock.vtable = &__metal_driver_vtable_fixed_clock.clock,
    .rate = 72000000UL,
};

/* From clock@5 */
struct __metal_driver_fixed_clock __metal_dt_clock_5 = {
    .vtable = &__metal_driver_vtable_fixed_clock,
    .clock.vtable = &__metal_driver_vtable_fixed_clock.clock,
    .rate = 32000000UL,
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
    .num_interrupts = 27UL,
    .interrupt_controller = 1,
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

/* From gpio@10012000 */
struct __metal_driver_sifive_gpio0 __metal_dt_gpio_10012000 = {
    .vtable = &__metal_driver_vtable_sifive_gpio0,
    .gpio.vtable = &__metal_driver_vtable_sifive_gpio0.gpio,
    .base = 268509184UL,
    .size = 4096UL,
/* From interrupt_controller@c000000 */
    .interrupt_parent = &__metal_dt_interrupt_controller_c000000.controller,
    .num_interrupts = METAL_MAX_GPIO_INTERRUPTS,
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

/* From spi@10014000 */
struct __metal_driver_sifive_spi0 __metal_dt_spi_10014000 = {
    .vtable = &__metal_driver_vtable_sifive_spi0,
    .spi.vtable = &__metal_driver_vtable_sifive_spi0.spi,
    .control_base = 268517376UL,
    .control_size = 4096UL,
/* From clock@4 */
    .clock = &__metal_dt_clock_4.clock,
/* From gpio@10012000 */
    .pinmux = &__metal_dt_gpio_10012000,
    .pinmux_output_selector = 60UL,
    .pinmux_source_selector = 60UL,
};

/* From serial@10013000 */
struct __metal_driver_sifive_uart0 __metal_dt_serial_10013000 = {
    .vtable = &__metal_driver_vtable_sifive_uart0,
    .uart.vtable = &__metal_driver_vtable_sifive_uart0.uart,
    .control_base = 268513280UL,
    .control_size = 4096UL,
/* From clock@4 */
    .clock = &__metal_dt_clock_4.clock,
/* From gpio@10012000 */
    .pinmux = &__metal_dt_gpio_10012000,
    .pinmux_output_selector = 196608UL,
    .pinmux_source_selector = 196608UL,
/* From interrupt_controller@c000000 */
    .interrupt_parent = &__metal_dt_interrupt_controller_c000000.controller,
    .num_interrupts = METAL_MAX_UART_INTERRUPTS,
    .interrupt_line = 5UL,
};

/* From clock@3 */
struct __metal_driver_sifive_fe310_g000_hfrosc __metal_dt_clock_3 = {
    .vtable = &__metal_driver_vtable_sifive_fe310_g000_hfrosc,
    .clock.vtable = &__metal_driver_vtable_sifive_fe310_g000_hfrosc.clock,
/* From clock@2 */
    .ref = &__metal_dt_clock_2.clock,
/* From prci@10008000 */
    .config_base = &__metal_dt_prci_10008000,
    .config_offset = 0UL,
};

/* From clock@1 */
struct __metal_driver_sifive_fe310_g000_hfxosc __metal_dt_clock_1 = {
    .vtable = &__metal_driver_vtable_sifive_fe310_g000_hfxosc,
    .clock.vtable = &__metal_driver_vtable_sifive_fe310_g000_hfxosc.clock,
/* From clock@0 */
    .ref = &__metal_dt_clock_0.clock,
/* From prci@10008000 */
    .config_base = &__metal_dt_prci_10008000,
    .config_offset = 4UL,
};

/* From clock@4 */
struct __metal_driver_sifive_fe310_g000_pll __metal_dt_clock_4 = {
    .vtable = &__metal_driver_vtable_sifive_fe310_g000_pll,
    .clock.vtable = &__metal_driver_vtable_sifive_fe310_g000_pll.clock,
/* From clock@3 */
    .pllsel0 = &__metal_dt_clock_3.clock,
/* From clock@1 */
    .pllref = &__metal_dt_clock_1.clock,
/* From prci@10008000 */
    .divider_base = &__metal_dt_prci_10008000,
    .divider_offset = 12UL,
/* From prci@10008000 */
    .config_base = &__metal_dt_prci_10008000,
    .config_offset = 8UL,
    .init_rate = 16000000UL,
};

/* From prci@10008000 */
struct __metal_driver_sifive_fe310_g000_prci __metal_dt_prci_10008000 = {
    .vtable = &__metal_driver_vtable_sifive_fe310_g000_prci,
    .base = 268468224UL,
    .size = 32768UL,
};


/* From serial@10013000 */
#define __METAL_DT_STDOUT_UART_HANDLE (&__metal_dt_serial_10013000.uart)

#define __METAL_DT_SERIAL_10013000_HANDLE (&__metal_dt_serial_10013000.uart)

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

/* From local_external_interrupts_0 */
#define __METAL_DT_SIFIVE_LOCAL_EXINTR0_HANDLE (&__metal_dt_local_external_interrupts_0.irc)

#define __METAL_DT_LOCAL_EXTERNAL_INTERRUPTS_0_HANDLE (&__metal_dt_local_external_interrupts_0.irc)

#define __MEE_DT_MAX_GPIOS 1

asm (".weak __metal_gpio_table");
struct __metal_driver_sifive_gpio0 *__metal_gpio_table[] = {
					&__metal_dt_gpio_10012000};

#define __METAL_DT_MAX_BUTTONS 0

asm (".weak __metal_button_table");
struct __metal_driver_sifive_gpio_button *__metal_button_table[] = {
					NULL };
#define __METAL_DT_MAX_LEDS 0

asm (".weak __metal_led_table");
struct __metal_driver_sifive_gpio_led *__metal_led_table[] = {
					NULL };
#define __METAL_DT_MAX_SWITCHES 0

asm (".weak __metal_switch_table");
struct __metal_driver_sifive_gpio_switch *__metal_switch_table[] = {
					NULL };
#define __METAL_DT_MAX_SPIS 1

asm (".weak __metal_spi_table");
struct __metal_driver_sifive_spi0 *__metal_spi_table[] = {
					&__metal_dt_spi_10014000};

/* From clock@4 */
#define __METAL_DT_SIFIVE_FE310_G000_PLL_HANDLE (&__metal_dt_clock_4)

#define __METAL_DT_CLOCK_4_HANDLE (&__metal_dt_clock_4)


#endif /* ! __METAL_MACHINE_MACROS */
#endif /* SIFIVE_HIFIVE1__METAL_H*/
#endif /* ! ASSEMBLY */
