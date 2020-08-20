/* Copyright 2019 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */
/* ----------------------------------- */
/* ----------------------------------- */

#ifndef ASSEMBLY

#ifndef METAL_INLINE_H
#define METAL_INLINE_H

#include <metal/machine.h>


/* --------------------- fixed_clock ------------ */
extern __inline__ unsigned long __metal_driver_fixed_clock_rate(const struct metal_clock *clock);


/* --------------------- fixed_factor_clock ------------ */
extern __inline__ struct metal_clock * __metal_driver_fixed_factor_clock_parent(const struct metal_clock *clock);
extern __inline__ unsigned long __metal_driver_fixed_factor_clock_mult(const struct metal_clock *clock);
extern __inline__ unsigned long __metal_driver_fixed_factor_clock_div(const struct metal_clock *clock);


/* --------------------- sifive_clint0 ------------ */
extern __inline__ unsigned long __metal_driver_sifive_clint0_control_base(struct metal_interrupt *controller);
extern __inline__ unsigned long __metal_driver_sifive_clint0_control_size(struct metal_interrupt *controller);
extern __inline__ int __metal_driver_sifive_clint0_num_interrupts(struct metal_interrupt *controller);
extern __inline__ struct metal_interrupt * __metal_driver_sifive_clint0_interrupt_parents(struct metal_interrupt *controller, int idx);
extern __inline__ int __metal_driver_sifive_clint0_interrupt_lines(struct metal_interrupt *controller, int idx);


/* --------------------- cpu ------------ */
extern __inline__ int __metal_driver_cpu_hartid(struct metal_cpu *cpu);
extern __inline__ int __metal_driver_cpu_timebase(struct metal_cpu *cpu);
extern __inline__ struct metal_interrupt * __metal_driver_cpu_interrupt_controller(struct metal_cpu *cpu);
extern __inline__ int __metal_driver_cpu_num_pmp_regions(struct metal_cpu *cpu);
extern __inline__ struct metal_buserror * __metal_driver_cpu_buserror(struct metal_cpu *cpu);


/* --------------------- sifive_plic0 ------------ */
extern __inline__ unsigned long __metal_driver_sifive_plic0_control_base(struct metal_interrupt *controller);
extern __inline__ unsigned long __metal_driver_sifive_plic0_control_size(struct metal_interrupt *controller);
extern __inline__ int __metal_driver_sifive_plic0_num_interrupts(struct metal_interrupt *controller);
extern __inline__ int __metal_driver_sifive_plic0_max_priority(struct metal_interrupt *controller);
extern __inline__ struct metal_interrupt * __metal_driver_sifive_plic0_interrupt_parents(struct metal_interrupt *controller, int idx);
extern __inline__ int __metal_driver_sifive_plic0_interrupt_lines(struct metal_interrupt *controller, int idx);
extern __inline__ int __metal_driver_sifive_plic0_context_ids(int hartid);


/* --------------------- sifive_buserror0 ------------ */


/* --------------------- sifive_clic0 ------------ */


/* --------------------- sifive_local_external_interrupts0 ------------ */


/* --------------------- sifive_global_external_interrupts0 ------------ */


/* --------------------- sifive_gpio0 ------------ */
extern __inline__ unsigned long __metal_driver_sifive_gpio0_base(struct metal_gpio *gpio);
extern __inline__ unsigned long __metal_driver_sifive_gpio0_size(struct metal_gpio *gpio);
extern __inline__ int __metal_driver_sifive_gpio0_num_interrupts(struct metal_gpio *gpio);
extern __inline__ struct metal_interrupt * __metal_driver_sifive_gpio0_interrupt_parent(struct metal_gpio *gpio);
extern __inline__ int __metal_driver_sifive_gpio0_interrupt_lines(struct metal_gpio *gpio, int idx);


/* --------------------- sifive_gpio_button ------------ */


/* --------------------- sifive_gpio_led ------------ */


/* --------------------- sifive_gpio_switch ------------ */


/* --------------------- sifive_i2c0 ------------ */
extern __inline__ unsigned long __metal_driver_sifive_i2c0_control_base(struct metal_i2c *i2c);
extern __inline__ unsigned long __metal_driver_sifive_i2c0_control_size(struct metal_i2c *i2c);
extern __inline__ int __metal_driver_sifive_i2c0_num_interrupts(struct metal_i2c *i2c);
extern __inline__ struct metal_interrupt * __metal_driver_sifive_i2c0_interrupt_parent(struct metal_i2c *i2c);
extern __inline__ int __metal_driver_sifive_i2c0_interrupt_line(struct metal_i2c *i2c);
extern __inline__ struct metal_clock * __metal_driver_sifive_i2c0_clock(struct metal_i2c *i2c);
extern __inline__ struct __metal_driver_sifive_gpio0 * __metal_driver_sifive_i2c0_pinmux(struct metal_i2c *i2c);
extern __inline__ unsigned long __metal_driver_sifive_i2c0_pinmux_output_selector(struct metal_i2c *i2c);
extern __inline__ unsigned long __metal_driver_sifive_i2c0_pinmux_source_selector(struct metal_i2c *i2c);


/* --------------------- sifive_pwm0 ------------ */
extern __inline__ unsigned long __metal_driver_sifive_pwm0_control_base(struct metal_pwm *pwm);
extern __inline__ unsigned long __metal_driver_sifive_pwm0_control_size(struct metal_pwm *pwm);
extern __inline__ int __metal_driver_sifive_pwm0_num_interrupts(struct metal_pwm *pwm);
extern __inline__ struct metal_interrupt * __metal_driver_sifive_pwm0_interrupt_parent(struct metal_pwm *pwm);
extern __inline__ int __metal_driver_sifive_pwm0_interrupt_lines(struct metal_pwm *pwm, int idx);
extern __inline__ struct metal_clock * __metal_driver_sifive_pwm0_clock(struct metal_pwm *pwm);
extern __inline__ struct __metal_driver_sifive_gpio0 * __metal_driver_sifive_pwm0_pinmux(struct metal_pwm *pwm);
extern __inline__ unsigned long __metal_driver_sifive_pwm0_pinmux_output_selector(struct metal_pwm *pwm);
extern __inline__ unsigned long __metal_driver_sifive_pwm0_pinmux_source_selector(struct metal_pwm *pwm);
extern __inline__ int __metal_driver_sifive_pwm0_compare_width(struct metal_pwm *pwm);
extern __inline__ int __metal_driver_sifive_pwm0_comparator_count(struct metal_pwm *pwm);


/* --------------------- sifive_rtc0 ------------ */


/* --------------------- sifive_spi0 ------------ */
extern __inline__ unsigned long __metal_driver_sifive_spi0_control_base(struct metal_spi *spi);
extern __inline__ unsigned long __metal_driver_sifive_spi0_control_size(struct metal_spi *spi);
extern __inline__ struct __metal_driver_sifive_gpio0 * __metal_driver_sifive_spi0_pinmux(struct metal_spi *spi);
extern __inline__ unsigned long __metal_driver_sifive_spi0_pinmux_output_selector(struct metal_spi *spi);
extern __inline__ unsigned long __metal_driver_sifive_spi0_pinmux_source_selector(struct metal_spi *spi);


/* --------------------- sifive_test0 ------------ */
extern __inline__ unsigned long __metal_driver_sifive_test0_base(const struct __metal_shutdown *sd);
extern __inline__ unsigned long __metal_driver_sifive_test0_size(const struct __metal_shutdown *sd);


/* --------------------- sifive_trace ------------ */

/* --------------------- sifive_uart0 ------------ */
extern __inline__ unsigned long __metal_driver_sifive_uart0_control_base(struct metal_uart *uart);
extern __inline__ unsigned long __metal_driver_sifive_uart0_control_size(struct metal_uart *uart);
extern __inline__ int __metal_driver_sifive_uart0_num_interrupts(struct metal_uart *uart);
extern __inline__ struct metal_interrupt * __metal_driver_sifive_uart0_interrupt_parent(struct metal_uart *uart);
extern __inline__ int __metal_driver_sifive_uart0_interrupt_line(struct metal_uart *uart);
extern __inline__ struct metal_clock * __metal_driver_sifive_uart0_clock(struct metal_uart *uart);
extern __inline__ struct __metal_driver_sifive_gpio0 * __metal_driver_sifive_uart0_pinmux(struct metal_uart *uart);
extern __inline__ unsigned long __metal_driver_sifive_uart0_pinmux_output_selector(struct metal_uart *uart);
extern __inline__ unsigned long __metal_driver_sifive_uart0_pinmux_source_selector(struct metal_uart *uart);


/* --------------------- sifive_simuart0 ------------ */


/* --------------------- sifive_wdog0 ------------ */


/* --------------------- sifive_fe310_g000_hfrosc ------------ */


/* --------------------- sifive_fe310_g000_hfxosc ------------ */


/* --------------------- sifive_fe310_g000_lfrosc ------------ */


/* --------------------- sifive_fe310_g000_pll ------------ */


/* --------------------- fe310_g000_prci ------------ */


/* From refclk */
struct __metal_driver_fixed_clock __metal_dt_refclk = {
    .clock.vtable = &__metal_driver_vtable_fixed_clock.clock,
};

/* From tlclk */
struct __metal_driver_fixed_factor_clock __metal_dt_tlclk = {
    .clock.vtable = &__metal_driver_vtable_fixed_factor_clock.clock,
};

struct metal_memory __metal_dt_mem_dtim_1000000 = {
    ._base_address = 16777216UL,
    ._size = 8192UL,
    ._attrs = {
        .R = 1,
        .W = 1,
        .X = 1,
        .C = 1,
        .A = 1},
};

struct metal_memory __metal_dt_mem_itim_1800000 = {
    ._base_address = 25165824UL,
    ._size = 16384UL,
    ._attrs = {
        .R = 1,
        .W = 1,
        .X = 1,
        .C = 1,
        .A = 1},
};

struct metal_memory __metal_dt_mem_itim_1808000 = {
    ._base_address = 25198592UL,
    ._size = 32768UL,
    ._attrs = {
        .R = 1,
        .W = 1,
        .X = 1,
        .C = 1,
        .A = 1},
};

struct metal_memory __metal_dt_mem_itim_1810000 = {
    ._base_address = 25231360UL,
    ._size = 32768UL,
    ._attrs = {
        .R = 1,
        .W = 1,
        .X = 1,
        .C = 1,
        .A = 1},
};

struct metal_memory __metal_dt_mem_itim_1818000 = {
    ._base_address = 25264128UL,
    ._size = 32768UL,
    ._attrs = {
        .R = 1,
        .W = 1,
        .X = 1,
        .C = 1,
        .A = 1},
};

struct metal_memory __metal_dt_mem_itim_1820000 = {
    ._base_address = 25296896UL,
    ._size = 32768UL,
    ._attrs = {
        .R = 1,
        .W = 1,
        .X = 1,
        .C = 1,
        .A = 1},
};

struct metal_memory __metal_dt_mem_memory_80000000 = {
    ._base_address = 2147483648UL,
    ._size = 135291469824UL,
    ._attrs = {
        .R = 1,
        .W = 1,
        .X = 1,
        .C = 1,
        .A = 1},
};

struct metal_memory __metal_dt_mem_spi_10040000 = {
    ._base_address = 536870912UL,
    ._size = 268435456UL,
    ._attrs = {
        .R = 1,
        .W = 1,
        .X = 1,
        .C = 1,
        .A = 1},
};

struct metal_memory __metal_dt_mem_spi_10041000 = {
    ._base_address = 805306368UL,
    ._size = 268435456UL,
    ._attrs = {
        .R = 1,
        .W = 1,
        .X = 1,
        .C = 1,
        .A = 1},
};

struct metal_memory __metal_dt_mem_spi_10050000 = {
    ._attrs = {
        .R = 1,
        .W = 1,
        .X = 1,
        .C = 1,
        .A = 1},
};

/* From clint@2000000 */
struct __metal_driver_riscv_clint0 __metal_dt_clint_2000000 = {
    .controller.vtable = &__metal_driver_vtable_riscv_clint0.clint_vtable,
    .init_done = 0,
};

/* From cpu@0 */
struct __metal_driver_cpu __metal_dt_cpu_0 = {
    .cpu.vtable = &__metal_driver_vtable_cpu.cpu_vtable,
    .hpm_count = 0,
};

/* From cpu@1 */
struct __metal_driver_cpu __metal_dt_cpu_1 = {
    .cpu.vtable = &__metal_driver_vtable_cpu.cpu_vtable,
    .hpm_count = 0,
};

/* From cpu@2 */
struct __metal_driver_cpu __metal_dt_cpu_2 = {
    .cpu.vtable = &__metal_driver_vtable_cpu.cpu_vtable,
    .hpm_count = 0,
};

/* From cpu@3 */
struct __metal_driver_cpu __metal_dt_cpu_3 = {
    .cpu.vtable = &__metal_driver_vtable_cpu.cpu_vtable,
    .hpm_count = 0,
};

/* From cpu@4 */
struct __metal_driver_cpu __metal_dt_cpu_4 = {
    .cpu.vtable = &__metal_driver_vtable_cpu.cpu_vtable,
    .hpm_count = 0,
};

/* From interrupt_controller */
struct __metal_driver_riscv_cpu_intc __metal_dt_cpu_0_interrupt_controller = {
    .controller.vtable = &__metal_driver_vtable_riscv_cpu_intc.controller_vtable,
    .init_done = 0,
};

/* From interrupt_controller */
struct __metal_driver_riscv_cpu_intc __metal_dt_cpu_1_interrupt_controller = {
    .controller.vtable = &__metal_driver_vtable_riscv_cpu_intc.controller_vtable,
    .init_done = 0,
};

/* From interrupt_controller */
struct __metal_driver_riscv_cpu_intc __metal_dt_cpu_2_interrupt_controller = {
    .controller.vtable = &__metal_driver_vtable_riscv_cpu_intc.controller_vtable,
    .init_done = 0,
};

/* From interrupt_controller */
struct __metal_driver_riscv_cpu_intc __metal_dt_cpu_3_interrupt_controller = {
    .controller.vtable = &__metal_driver_vtable_riscv_cpu_intc.controller_vtable,
    .init_done = 0,
};

/* From interrupt_controller */
struct __metal_driver_riscv_cpu_intc __metal_dt_cpu_4_interrupt_controller = {
    .controller.vtable = &__metal_driver_vtable_riscv_cpu_intc.controller_vtable,
    .init_done = 0,
};

/* From interrupt_controller@c000000 */
struct __metal_driver_riscv_plic0 __metal_dt_interrupt_controller_c000000 = {
    .controller.vtable = &__metal_driver_vtable_riscv_plic0.plic_vtable,
    .init_done = 0,
};

struct metal_pmp __metal_dt_pmp;

/* From gpio@10060000 */
struct __metal_driver_sifive_gpio0 __metal_dt_gpio_10060000 = {
    .gpio.vtable = &__metal_driver_vtable_sifive_gpio0.gpio,
};

/* From i2c@10030000 */
struct __metal_driver_sifive_i2c0 __metal_dt_i2c_10030000 = {
    .i2c.vtable = &__metal_driver_vtable_sifive_i2c0.i2c,
};

/* From pwm@10020000 */
struct __metal_driver_sifive_pwm0 __metal_dt_pwm_10020000 = {
    .pwm.vtable = &__metal_driver_vtable_sifive_pwm0.pwm,
};

/* From pwm@10021000 */
struct __metal_driver_sifive_pwm0 __metal_dt_pwm_10021000 = {
    .pwm.vtable = &__metal_driver_vtable_sifive_pwm0.pwm,
};

/* From spi@10040000 */
struct __metal_driver_sifive_spi0 __metal_dt_spi_10040000 = {
    .spi.vtable = &__metal_driver_vtable_sifive_spi0.spi,
};

/* From spi@10041000 */
struct __metal_driver_sifive_spi0 __metal_dt_spi_10041000 = {
    .spi.vtable = &__metal_driver_vtable_sifive_spi0.spi,
};

/* From spi@10050000 */
struct __metal_driver_sifive_spi0 __metal_dt_spi_10050000 = {
    .spi.vtable = &__metal_driver_vtable_sifive_spi0.spi,
};

/* From teststatus@4000 */
struct __metal_driver_sifive_test0 __metal_dt_teststatus_4000 = {
    .shutdown.vtable = &__metal_driver_vtable_sifive_test0.shutdown,
};

/* From serial@10010000 */
struct __metal_driver_sifive_uart0 __metal_dt_serial_10010000 = {
    .uart.vtable = &__metal_driver_vtable_sifive_uart0.uart,
};

/* From serial@10011000 */
struct __metal_driver_sifive_uart0 __metal_dt_serial_10011000 = {
    .uart.vtable = &__metal_driver_vtable_sifive_uart0.uart,
};


#endif /* METAL_INLINE_H*/
#endif /* ! ASSEMBLY */
