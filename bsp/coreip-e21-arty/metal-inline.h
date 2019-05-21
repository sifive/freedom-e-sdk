/* Copyright 2019 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */
/* ----------------------------------- */
/* [XXXXX] 21-05-2019 10-54-34        */
/* ----------------------------------- */

#ifndef ASSEMBLY

#ifndef COREIP_E21_ARTY__METAL_INLINE_H
#define COREIP_E21_ARTY__METAL_INLINE_H

#include <metal/machine.h>


/* --------------------- fixed_clock ------------ */
extern inline unsigned long __metal_driver_fixed_clock_rate(struct metal_clock *clock);


/* --------------------- fixed_factor_clock ------------ */


/* --------------------- sifive_clint0 ------------ */


/* --------------------- cpu ------------ */
extern inline int __metal_driver_cpu_timebase(struct metal_cpu *cpu);
extern inline struct metal_interrupt * __metal_driver_cpu_interrupt_controller(struct metal_cpu *cpu);
extern inline int __metal_driver_cpu_num_pmp_regions(struct metal_cpu *cpu);


/* --------------------- sifive_plic0 ------------ */


/* --------------------- sifive_clic0 ------------ */
extern inline unsigned long __metal_driver_sifive_clic0_control_base(struct metal_interrupt *controller);
extern inline unsigned long __metal_driver_sifive_clic0_control_size(struct metal_interrupt *controller);
extern inline struct metal_interrupt * __metal_driver_sifive_clic0_interrupt_parent(struct metal_interrupt *controller);
extern inline int __metal_driver_sifive_clic0_num_interrupts(struct metal_interrupt *controller);
extern inline int __metal_driver_sifive_clic0_interrupt_lines(struct metal_interrupt *controller, int idx);
extern inline int __metal_driver_sifive_clic0_max_levels(struct metal_interrupt *controller);
extern inline int __metal_driver_sifive_clic0_num_subinterrupts(struct metal_interrupt *controller);
extern inline int __metal_driver_sifive_clic0_num_intbits(struct metal_interrupt *controller);


/* --------------------- sifive_local_external_interrupts0 ------------ */
extern inline struct metal_interrupt * __metal_driver_sifive_local_external_interrupts0_interrupt_parent(struct metal_interrupt *controller);
extern inline int __metal_driver_sifive_local_external_interrupts0_num_interrupts(struct metal_interrupt *controller);
extern inline int __metal_driver_sifive_local_external_interrupts0_interrupt_lines(struct metal_interrupt *controller, int idx);


/* --------------------- sifive_global_external_interrupts0 ------------ */
extern inline int __metal_driver_sifive_global_external_interrupts0_init_done( );
extern inline struct metal_interrupt * __metal_driver_sifive_global_external_interrupts0_interrupt_parent(struct metal_interrupt *controller);
extern inline int __metal_driver_sifive_global_external_interrupts0_num_interrupts(struct metal_interrupt *controller);
extern inline int __metal_driver_sifive_global_external_interrupts0_interrupt_lines(struct metal_interrupt *controller, int idx);


/* --------------------- sifive_gpio0 ------------ */
extern inline unsigned long __metal_driver_sifive_gpio0_base(struct metal_gpio *gpio);
extern inline unsigned long __metal_driver_sifive_gpio0_size(struct metal_gpio *gpio);
extern inline int __metal_driver_sifive_gpio0_num_interrupts(struct metal_gpio *gpio);
extern inline struct metal_interrupt * __metal_driver_sifive_gpio0_interrupt_parent(struct metal_gpio *gpio);
extern inline int __metal_driver_sifive_gpio0_interrupt_lines(struct metal_gpio *gpio, int idx);


/* --------------------- sifive_gpio_button ------------ */
extern inline struct metal_gpio * __metal_driver_sifive_gpio_button_gpio(struct metal_button *button);
extern inline int __metal_driver_sifive_gpio_button_pin(struct metal_button *button);
extern inline struct metal_interrupt * __metal_driver_sifive_gpio_button_interrupt_controller(struct metal_button *button);
extern inline int __metal_driver_sifive_gpio_button_interrupt_line(struct metal_button *button);
extern inline char * __metal_driver_sifive_gpio_button_label(struct metal_button *button);


/* --------------------- sifive_gpio_led ------------ */
extern inline struct metal_gpio * __metal_driver_sifive_gpio_led_gpio(struct metal_led *led);
extern inline int __metal_driver_sifive_gpio_led_pin(struct metal_led *led);
extern inline char * __metal_driver_sifive_gpio_led_label(struct metal_led *led);


/* --------------------- sifive_gpio_switch ------------ */
extern inline struct metal_gpio * __metal_driver_sifive_gpio_switch_gpio(struct metal_switch *flip);
extern inline int __metal_driver_sifive_gpio_switch_pin(struct metal_switch *flip);
extern inline struct metal_interrupt * __metal_driver_sifive_gpio_switch_interrupt_controller(struct metal_switch *flip);
extern inline int __metal_driver_sifive_gpio_switch_interrupt_line(struct metal_switch *flip);
extern inline char * __metal_driver_sifive_gpio_switch_label(struct metal_switch *flip);


/* --------------------- sifive_spi0 ------------ */
extern inline unsigned long __metal_driver_sifive_spi0_control_base(struct metal_spi *spi);
extern inline unsigned long __metal_driver_sifive_spi0_control_size(struct metal_spi *spi);
extern inline struct __metal_driver_sifive_gpio0 * __metal_driver_sifive_spi0_pinmux(struct metal_spi *spi);
extern inline unsigned long __metal_driver_sifive_spi0_pinmux_output_selector(struct metal_spi *spi);
extern inline unsigned long __metal_driver_sifive_spi0_pinmux_source_selector(struct metal_spi *spi);


/* --------------------- sifive_test0 ------------ */
extern inline unsigned long __metal_driver_sifive_test0_base( );
extern inline unsigned long __metal_driver_sifive_test0_size( );


/* --------------------- sifive_uart0 ------------ */
extern inline unsigned long __metal_driver_sifive_uart0_control_base(struct metal_uart *uart);
extern inline unsigned long __metal_driver_sifive_uart0_control_size(struct metal_uart *uart);
extern inline int __metal_driver_sifive_uart0_num_interrupts(struct metal_uart *uart);
extern inline struct metal_interrupt * __metal_driver_sifive_uart0_interrupt_parent(struct metal_uart *uart);
extern inline int __metal_driver_sifive_uart0_interrupt_line(struct metal_uart *uart);
extern inline struct metal_clock * __metal_driver_sifive_uart0_clock(struct metal_uart *uart);
extern inline struct __metal_driver_sifive_gpio0 * __metal_driver_sifive_uart0_pinmux(struct metal_uart *uart);
extern inline unsigned long __metal_driver_sifive_uart0_pinmux_output_selector(struct metal_uart *uart);
extern inline unsigned long __metal_driver_sifive_uart0_pinmux_source_selector(struct metal_uart *uart);


/* --------------------- sifive_fe310_g000_hfrosc ------------ */


/* --------------------- sifive_fe310_g000_hfxosc ------------ */


/* --------------------- sifive_fe310_g000_pll ------------ */


/* --------------------- fe310_g000_prci ------------ */


/* --------------------- sifive_fu540_c000_l2 ------------ */


/* From clock@0 */
struct __metal_driver_fixed_clock __metal_dt_clock_0 = {
    .clock.vtable = &__metal_driver_vtable_fixed_clock.clock,
};

struct metal_memory __metal_dt_mem_sys_sram_0_80000000 = {
    ._base_address = 2147483648UL,
    ._size = 32768UL,
    ._attrs = {
        .R = 1,
        .W = 1,
        .X = 1,
        .C = 1,
        .A = 1},
};

struct metal_memory __metal_dt_mem_sys_sram_1_80008000 = {
    ._base_address = 2147516416UL,
    ._size = 32768UL,
    ._attrs = {
        .R = 1,
        .W = 1,
        .X = 1,
        .C = 1,
        .A = 1},
};

struct metal_memory __metal_dt_mem_spi_20004000 = {
    ._base_address = 1073741824UL,
    ._size = 536870912UL,
    ._attrs = {
        .R = 1,
        .W = 1,
        .X = 1,
        .C = 1,
        .A = 1},
};

/* From cpu@0 */
struct __metal_driver_cpu __metal_dt_cpu_0 = {
    .cpu.vtable = &__metal_driver_vtable_cpu.cpu_vtable,
};

/* From interrupt_controller */
struct __metal_driver_riscv_cpu_intc __metal_dt_cpu_0_interrupt_controller = {
    .controller.vtable = &__metal_driver_vtable_riscv_cpu_intc.controller_vtable,
    .init_done = 0,
};

/* From interrupt_controller@2000000 */
struct __metal_driver_sifive_clic0 __metal_dt_interrupt_controller_2000000 = {
    .controller.vtable = &__metal_driver_vtable_sifive_clic0.clic_vtable,
    .init_done = 0,
};

/* From local_external_interrupts_0 */
struct __metal_driver_sifive_local_external_interrupts0 __metal_dt_local_external_interrupts_0 = {
    .irc.vtable = &__metal_driver_vtable_sifive_local_external_interrupts0.local0_vtable,
    .init_done = 0,
};

/* From global_external_interrupts */
struct __metal_driver_sifive_global_external_interrupts0 __metal_dt_global_external_interrupts = {
    .irc.vtable = &__metal_driver_vtable_sifive_global_external_interrupts0.global0_vtable,
    .init_done = 0,
};

/* From gpio@20002000 */
struct __metal_driver_sifive_gpio0 __metal_dt_gpio_20002000 = {
    .gpio.vtable = &__metal_driver_vtable_sifive_gpio0.gpio,
};

/* From button@0 */
struct __metal_driver_sifive_gpio_button __metal_dt_button_0 = {
    .button.vtable = &__metal_driver_vtable_sifive_button.button_vtable,
};

/* From button@1 */
struct __metal_driver_sifive_gpio_button __metal_dt_button_1 = {
    .button.vtable = &__metal_driver_vtable_sifive_button.button_vtable,
};

/* From button@2 */
struct __metal_driver_sifive_gpio_button __metal_dt_button_2 = {
    .button.vtable = &__metal_driver_vtable_sifive_button.button_vtable,
};

/* From button@3 */
struct __metal_driver_sifive_gpio_button __metal_dt_button_3 = {
    .button.vtable = &__metal_driver_vtable_sifive_button.button_vtable,
};

/* From led@0red */
struct __metal_driver_sifive_gpio_led __metal_dt_led_0red = {
    .led.vtable = &__metal_driver_vtable_sifive_led.led_vtable,
};

/* From led@0green */
struct __metal_driver_sifive_gpio_led __metal_dt_led_0green = {
    .led.vtable = &__metal_driver_vtable_sifive_led.led_vtable,
};

/* From led@0blue */
struct __metal_driver_sifive_gpio_led __metal_dt_led_0blue = {
    .led.vtable = &__metal_driver_vtable_sifive_led.led_vtable,
};

/* From switch@0 */
struct __metal_driver_sifive_gpio_switch __metal_dt_switch_0 = {
    .flip.vtable = &__metal_driver_vtable_sifive_switch.switch_vtable,
};

/* From switch@1 */
struct __metal_driver_sifive_gpio_switch __metal_dt_switch_1 = {
    .flip.vtable = &__metal_driver_vtable_sifive_switch.switch_vtable,
};

/* From switch@2 */
struct __metal_driver_sifive_gpio_switch __metal_dt_switch_2 = {
    .flip.vtable = &__metal_driver_vtable_sifive_switch.switch_vtable,
};

/* From switch@3 */
struct __metal_driver_sifive_gpio_switch __metal_dt_switch_3 = {
    .flip.vtable = &__metal_driver_vtable_sifive_switch.switch_vtable,
};

/* From spi@20004000 */
struct __metal_driver_sifive_spi0 __metal_dt_spi_20004000 = {
    .spi.vtable = &__metal_driver_vtable_sifive_spi0.spi,
};

/* From teststatus@4000 */
struct __metal_driver_sifive_test0 __metal_dt_teststatus_4000 = {
    .shutdown.vtable = &__metal_driver_vtable_sifive_test0.shutdown,
};

/* From serial@20000000 */
struct __metal_driver_sifive_uart0 __metal_dt_serial_20000000 = {
    .uart.vtable = &__metal_driver_vtable_sifive_uart0.uart,
};


#endif /* COREIP_E21_ARTY__METAL_INLINE_H*/
#endif /* ! ASSEMBLY */
