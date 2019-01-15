#ifndef ASSEMBLY

#ifndef SIFIVE_HIFIVE1__MEE_H
#define SIFIVE_HIFIVE1__MEE_H

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
#include <mee/drivers/sifive,fe310-g000,pll.h>
#include <mee/drivers/sifive,fe310-g000,prci.h>
#include <mee/drivers/sifive,fe310-g000,hfxosc.h>
#include <mee/drivers/sifive,fe310-g000,hfrosc.h>
#include <mee/drivers/sifive,gpio0.h>
#include <mee/drivers/sifive,uart0.h>
#include <mee/drivers/sifive,local-external-interrupts0.h>
#include <mee/drivers/sifive,spi0.h>
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

/* From clock@2 */
asm (".weak __mee_dt_clock_2");
struct __mee_driver_fixed_clock __mee_dt_clock_2;

/* From clock@5 */
asm (".weak __mee_dt_clock_5");
struct __mee_driver_fixed_clock __mee_dt_clock_5;

/* From local_external_interrupts_0 */
asm (".weak __mee_dt_local_external_interrupts_0");
struct __mee_driver_sifive_local_external_interrupts0 __mee_dt_local_external_interrupts_0;

/* From clock@4 */
asm (".weak __mee_dt_clock_4");
struct __mee_driver_sifive_fe310_g000_pll __mee_dt_clock_4;

/* From prci@10008000 */
asm (".weak __mee_dt_prci_10008000");
struct __mee_driver_sifive_fe310_g000_prci __mee_dt_prci_10008000;

/* From clock@1 */
asm (".weak __mee_dt_clock_1");
struct __mee_driver_sifive_fe310_g000_hfxosc __mee_dt_clock_1;

/* From clock@3 */
asm (".weak __mee_dt_clock_3");
struct __mee_driver_sifive_fe310_g000_hfrosc __mee_dt_clock_3;

/* From gpio@10012000 */
asm (".weak __mee_dt_gpio_10012000");
struct __mee_driver_sifive_gpio0 __mee_dt_gpio_10012000;

/* From serial@10013000 */
asm (".weak __mee_dt_serial_10013000");
struct __mee_driver_sifive_uart0 __mee_dt_serial_10013000;

/* From spi@10014000 */
asm (".weak __mee_dt_spi_10014000");
struct __mee_driver_sifive_spi0 __mee_dt_spi_10014000;

/* From spi@10024000 */
asm (".weak __mee_dt_spi_10024000");
struct __mee_driver_sifive_spi0 __mee_dt_spi_10024000;

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
    .rate = 16000000UL,
};

/* From clock@2 */
struct __mee_driver_fixed_clock __mee_dt_clock_2 = {
    .vtable = &__mee_driver_vtable_fixed_clock,
    .clock.vtable = &__mee_driver_vtable_fixed_clock.clock,
    .rate = 72000000UL,
};

/* From clock@5 */
struct __mee_driver_fixed_clock __mee_dt_clock_5 = {
    .vtable = &__mee_driver_vtable_fixed_clock,
    .clock.vtable = &__mee_driver_vtable_fixed_clock.clock,
    .rate = 32000000UL,
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
    .controller.vtable = &__mee_driver_vtable_riscv_clint0.clint_vtable,
    .control_base = 33554432UL,
    .control_size = 65536UL,
    .init_done = 0,
    .num_interrupts = MEE_MAX_CLINT_INTERRUPTS,
    .interrupt_parent = &__mee_dt_interrupt_controller.controller,
    .interrupt_lines[0] = 3,
    .interrupt_lines[1] = 7,
};

/* From clint@2000000 */
#define __MEE_DT_RISCV_CLINT0_HANDLE (&__mee_dt_clint_2000000.controller)

#define __MEE_DT_CLINT_2000000_HANDLE (&__mee_dt_clint_2000000.controller)

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
    .controller.vtable = &__mee_driver_vtable_riscv_plic0.plic_vtable,
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
#define __MEE_DT_RISCV_PLIC0_HANDLE (&__mee_dt_interrupt_controller_c000000.controller)

#define __MEE_DT_INTERRUPT_CONTROLLER_C000000_HANDLE (&__mee_dt_interrupt_controller_c000000.controller)

/* From clock@4 */
struct __mee_driver_sifive_fe310_g000_pll __mee_dt_clock_4 = {
    .vtable = &__mee_driver_vtable_sifive_fe310_g000_pll,
    .clock.vtable = &__mee_driver_vtable_sifive_fe310_g000_pll.clock,
/* From clock@3 */
    .pllsel0 = &__mee_dt_clock_3.clock,
/* From clock@1 */
    .pllref = &__mee_dt_clock_1.clock,
/* From prci@10008000 */
    .divider_base = &__mee_dt_prci_10008000,
    .divider_offset = 12UL,
/* From prci@10008000 */
    .config_base = &__mee_dt_prci_10008000,
    .config_offset = 8UL,
    .init_rate = 16000000UL,
};

/* From clock@4 */
#define __MEE_DT_SIFIVE_FE310_G000_PLL_HANDLE (&__mee_dt_clock_4)

#define __MEE_DT_CLOCK_4_HANDLE (&__mee_dt_clock_4)

/* From prci@10008000 */
struct __mee_driver_sifive_fe310_g000_prci __mee_dt_prci_10008000 = {
    .vtable = &__mee_driver_vtable_sifive_fe310_g000_prci,
    .base = 268468224UL,
    .size = 32768UL,
};

/* From clock@1 */
struct __mee_driver_sifive_fe310_g000_hfxosc __mee_dt_clock_1 = {
    .vtable = &__mee_driver_vtable_sifive_fe310_g000_hfxosc,
    .clock.vtable = &__mee_driver_vtable_sifive_fe310_g000_hfxosc.clock,
/* From clock@0 */
    .ref = &__mee_dt_clock_0.clock,
/* From prci@10008000 */
    .config_base = &__mee_dt_prci_10008000,
    .config_offset = 4UL,
};

/* From clock@3 */
struct __mee_driver_sifive_fe310_g000_hfrosc __mee_dt_clock_3 = {
    .vtable = &__mee_driver_vtable_sifive_fe310_g000_hfrosc,
    .clock.vtable = &__mee_driver_vtable_sifive_fe310_g000_hfrosc.clock,
/* From clock@2 */
    .ref = &__mee_dt_clock_2.clock,
/* From prci@10008000 */
    .config_base = &__mee_dt_prci_10008000,
    .config_offset = 0UL,
};

/* From gpio@10012000 */
struct __mee_driver_sifive_gpio0 __mee_dt_gpio_10012000 = {
    .vtable = &__mee_driver_vtable_sifive_gpio0,
    .base = 268509184UL,
    .size = 4096UL,
/* From interrupt_controller@c000000 */
    .interrupt_parent = &__mee_dt_interrupt_controller_c000000.controller,
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
/* From clock@4 */
    .clock = &__mee_dt_clock_4.clock,
/* From gpio@10012000 */
    .pinmux = &__mee_dt_gpio_10012000,
    .pinmux_output_selector = 196608UL,
    .pinmux_source_selector = 196608UL,
/* From interrupt_controller@c000000 */
    .interrupt_parent = &__mee_dt_interrupt_controller_c000000.controller,
    .num_interrupts = MEE_MAX_UART_INTERRUPTS,
    .interrupt_line = 5UL,
};

/* From spi@10014000 */
struct __mee_driver_sifive_spi0 __mee_dt_spi_10014000 = {
    .vtable = &__mee_driver_vtable_sifive_spi0,
    .spi.vtable = &__mee_driver_vtable_sifive_spi0.spi,
    .control_base = 268517376UL,
    .control_size = 4096UL,
/* From clock@4 */
    .clock = &__mee_dt_clock_4.clock,
/* From gpio@10012000 */
    .pinmux = &__mee_dt_gpio_10012000,
    .pinmux_output_selector = 0UL,
    .pinmux_source_selector = 0UL,
};

/* From spi@10024000 */
struct __mee_driver_sifive_spi0 __mee_dt_spi_10024000 = {
    .vtable = &__mee_driver_vtable_sifive_spi0,
    .spi.vtable = &__mee_driver_vtable_sifive_spi0.spi,
    .control_base = 268582912UL,
    .control_size = 4096UL,
/* From clock@4 */
    .clock = &__mee_dt_clock_4.clock,
/* From gpio@10012000 */
    .pinmux = &__mee_dt_gpio_10012000,
    .pinmux_output_selector = 60UL,
    .pinmux_source_selector = 60UL,
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
#define __MEE_DT_MAX_SPIS 2

asm (".weak __mee_spi_table");
struct __mee_driver_sifive_spi0 *__mee_spi_table[] = {
					&__mee_dt_spi_10014000,
					&__mee_dt_spi_10024000,
};
#endif /*MEE__MACHINE__SIFIVE_HIFIVE1__MEE_H*/

#endif/*ASSEMBLY*/
