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
extern __inline__ uintptr_t __metal_driver_sifive_buserror0_control_base(const struct metal_buserror *beu);
extern __inline__ struct metal_interrupt * __metal_driver_sifive_buserror0_interrupt_parent(const struct metal_buserror *beu);
extern __inline__ int __metal_driver_sifive_buserror0_interrupt_id(const struct metal_buserror *beu);


/* --------------------- sifive_clic0 ------------ */


/* --------------------- sifive_local_external_interrupts0 ------------ */
extern __inline__ struct metal_interrupt * __metal_driver_sifive_local_external_interrupts0_interrupt_parent(struct metal_interrupt *controller);
extern __inline__ int __metal_driver_sifive_local_external_interrupts0_num_interrupts(struct metal_interrupt *controller);
extern __inline__ int __metal_driver_sifive_local_external_interrupts0_interrupt_lines(struct metal_interrupt *controller, int idx);


/* --------------------- sifive_global_external_interrupts0 ------------ */
extern __inline__ int __metal_driver_sifive_global_external_interrupts0_init_done( );
extern __inline__ struct metal_interrupt * __metal_driver_sifive_global_external_interrupts0_interrupt_parent(struct metal_interrupt *controller);
extern __inline__ int __metal_driver_sifive_global_external_interrupts0_num_interrupts(struct metal_interrupt *controller);
extern __inline__ int __metal_driver_sifive_global_external_interrupts0_interrupt_lines(struct metal_interrupt *controller, int idx);


/* --------------------- sifive_gpio0 ------------ */


/* --------------------- sifive_gpio_button ------------ */


/* --------------------- sifive_gpio_led ------------ */


/* --------------------- sifive_gpio_switch ------------ */


/* --------------------- sifive_i2c0 ------------ */


/* --------------------- sifive_pwm0 ------------ */


/* --------------------- sifive_rtc0 ------------ */


/* --------------------- sifive_spi0 ------------ */


/* --------------------- sifive_test0 ------------ */
extern __inline__ unsigned long __metal_driver_sifive_test0_base(const struct __metal_shutdown *sd);
extern __inline__ unsigned long __metal_driver_sifive_test0_size(const struct __metal_shutdown *sd);


/* --------------------- sifive_trace ------------ */
extern __inline__ unsigned long __metal_driver_sifive_trace_base(const struct metal_uart *uart);
extern __inline__ unsigned long __metal_driver_sifive_trace_size(const struct metal_uart *uart);

/* --------------------- sifive_nb2emmc ------------ */
extern __inline__ unsigned long long __metal_driver_sifive_nb2emmc_base(struct metal_emmc *emmc);
extern __inline__ unsigned long long __metal_driver_sifive_nb2emmc_size(struct metal_emmc *emmc);
extern __inline__ int __metal_driver_sifive_nb2emmc_num_interrupts(struct metal_emmc *emmc);
extern __inline__ struct metal_interrupt * __metal_driver_sifive_nb2emmc_interrupt_parent(struct metal_emmc *emmc);
extern __inline__ int __metal_driver_sifive_nb2emmc_interrupt_lines(struct metal_emmc *emmc, int idx);


/* --------------------- sifive_nb2qspi0 ------------ */
extern __inline__ unsigned long long __metal_driver_sifive_nb2qspi0_control_base(struct metal_qspi *qspi);
extern __inline__ unsigned long long __metal_driver_sifive_nb2qspi0_control_size(struct metal_qspi *qspi);
extern __inline__ struct __metal_driver_sifive_nb2gpio0 * __metal_driver_sifive_nb2qspi0_pinmux(struct metal_qspi *qspi);
extern __inline__ unsigned long __metal_driver_sifive_nb2qspi0_pinmux_output_selector(struct metal_qspi *qspi);
extern __inline__ unsigned long __metal_driver_sifive_nb2qspi0_pinmux_source_selector(struct metal_qspi *qspi);


/* --------------------- sifive_nb2uart0 ------------ */
extern __inline__ unsigned long long __metal_driver_sifive_nb2uart0_control_base(struct metal_uart *uart);
extern __inline__ unsigned long long __metal_driver_sifive_nb2uart0_control_size(struct metal_uart *uart);
extern __inline__ int __metal_driver_sifive_nb2uart0_num_interrupts(struct metal_uart *uart);
extern __inline__ struct metal_interrupt * __metal_driver_sifive_nb2uart0_interrupt_parent(struct metal_uart *uart);
extern __inline__ int __metal_driver_sifive_nb2uart0_interrupt_line(struct metal_uart *uart);
extern __inline__ struct metal_clock * __metal_driver_sifive_nb2uart0_clock(struct metal_uart *uart);
extern __inline__ struct __metal_driver_sifive_nb2gpio0 * __metal_driver_sifive_nb2uart0_pinmux(struct metal_uart *uart);
extern __inline__ unsigned long __metal_driver_sifive_nb2uart0_pinmux_output_selector(struct metal_uart *uart);
extern __inline__ unsigned long __metal_driver_sifive_nb2uart0_pinmux_source_selector(struct metal_uart *uart);


/* --------------------- sifive_nb2wdt ------------ */
extern __inline__ unsigned long long __metal_driver_sifive_nb2wdt_control_base(const struct metal_watchdog *const watchdog);
extern __inline__ unsigned long long __metal_driver_sifive_nb2wdt_control_size(const struct metal_watchdog *const watchdog);
extern __inline__ struct metal_interrupt * __metal_driver_sifive_nb2wdt_interrupt_parent(const struct metal_watchdog *const watchdog);
extern __inline__ int __metal_driver_sifive_nb2wdt_interrupt_line(const struct metal_watchdog *const watchdog);
extern __inline__ struct metal_clock * __metal_driver_sifive_nb2wdt_clock(const struct metal_watchdog *const watchdog);


/* --------------------- sifive_fe310_g000_hfrosc ------------ */


/* --------------------- sifive_fe310_g000_hfxosc ------------ */


/* --------------------- sifive_fe310_g000_lfrosc ------------ */


/* --------------------- sifive_fe310_g000_pll ------------ */


/* --------------------- fe310_g000_prci ------------ */


/* From subsystem_pbus_clock */
struct __metal_driver_fixed_clock __metal_dt_subsystem_pbus_clock = {
    .clock.vtable = &__metal_driver_vtable_fixed_clock.clock,
};

/* From qspi_clock */
struct __metal_driver_fixed_clock __metal_dt_qspi_clock = {
    .clock.vtable = &__metal_driver_vtable_fixed_clock.clock,
};

/* From emmc_clock */
struct __metal_driver_fixed_clock __metal_dt_emmc_clock = {
    .clock.vtable = &__metal_driver_vtable_fixed_clock.clock,
};

struct metal_memory __metal_dt_mem_testram_100000000 = {
    ._base_address = 4294967296UL,
    ._size = 536870911UL,
    ._attrs = {
        .R = 1,
        .W = 1,
        .X = 1,
        .C = 1,
        .A = 1},
};

struct metal_memory __metal_dt_mem_testram_c00000000 = {
    ._base_address = 51539607552UL,
    ._size = 536870911UL,
    ._attrs = {
        .R = 1,
        .W = 1,
        .X = 1,
        .C = 1,
        .A = 1},
};

struct metal_memory __metal_dt_mem_memory_800000000 = {
    ._base_address = 34359738368UL,
    ._size = 8589934592UL,
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

/* From interrupt_controller@c000000 */
struct __metal_driver_riscv_plic0 __metal_dt_interrupt_controller_c000000 = {
    .controller.vtable = &__metal_driver_vtable_riscv_plic0.plic_vtable,
    .init_done = 0,
};

struct metal_pmp __metal_dt_pmp;

/* From bus_error_unit@1700000 */
struct metal_buserror __metal_dt_bus_error_unit_1700000 = {
};

/* From bus_error_unit@1701000 */
struct metal_buserror __metal_dt_bus_error_unit_1701000 = {
};

/* From bus_error_unit@1702000 */
struct metal_buserror __metal_dt_bus_error_unit_1702000 = {
};

/* From bus_error_unit@1703000 */
struct metal_buserror __metal_dt_bus_error_unit_1703000 = {
};

/* From local_external_interrupts_0 */
struct __metal_driver_sifive_local_external_interrupts0 __metal_dt_local_external_interrupts_0 = {
    .irc.vtable = &__metal_driver_vtable_sifive_local_external_interrupts0.local0_vtable,
    .init_done = 0,
};

/* From local_external_interrupts_1 */
struct __metal_driver_sifive_local_external_interrupts0 __metal_dt_local_external_interrupts_1 = {
    .irc.vtable = &__metal_driver_vtable_sifive_local_external_interrupts0.local0_vtable,
    .init_done = 0,
};

/* From local_external_interrupts_2 */
struct __metal_driver_sifive_local_external_interrupts0 __metal_dt_local_external_interrupts_2 = {
    .irc.vtable = &__metal_driver_vtable_sifive_local_external_interrupts0.local0_vtable,
    .init_done = 0,
};

/* From local_external_interrupts_3 */
struct __metal_driver_sifive_local_external_interrupts0 __metal_dt_local_external_interrupts_3 = {
    .irc.vtable = &__metal_driver_vtable_sifive_local_external_interrupts0.local0_vtable,
    .init_done = 0,
};

/* From global_external_interrupts */
struct __metal_driver_sifive_global_external_interrupts0 __metal_dt_global_external_interrupts = {
    .irc.vtable = &__metal_driver_vtable_sifive_global_external_interrupts0.global0_vtable,
    .init_done = 0,
};

/* From teststatus@4000 */
struct __metal_driver_sifive_test0 __metal_dt_teststatus_4000 = {
    .shutdown.vtable = &__metal_driver_vtable_sifive_test0.shutdown,
};

/* From trace_encoder_0@10000000 */
struct __metal_driver_sifive_trace __metal_dt_trace_encoder_0_10000000 = {
    .uart.vtable = &__metal_driver_vtable_sifive_trace.uart,
};

/* From trace_encoder_1@10001000 */
struct __metal_driver_sifive_trace __metal_dt_trace_encoder_1_10001000 = {
    .uart.vtable = &__metal_driver_vtable_sifive_trace.uart,
};

/* From trace_encoder_2@10002000 */
struct __metal_driver_sifive_trace __metal_dt_trace_encoder_2_10002000 = {
    .uart.vtable = &__metal_driver_vtable_sifive_trace.uart,
};

/* From trace_encoder_3@10003000 */
struct __metal_driver_sifive_trace __metal_dt_trace_encoder_3_10003000 = {
    .uart.vtable = &__metal_driver_vtable_sifive_trace.uart,
};

/* From trace_funnel@10008000 */
struct __metal_driver_sifive_trace __metal_dt_trace_funnel_10008000 = {
    .uart.vtable = &__metal_driver_vtable_sifive_trace.uart,
};

/* From nb2emmc@301007000 */
struct __metal_driver_sifive_nb2emmc __metal_dt_nb2emmc_301007000 = {
    .emmc.vtable = &__metal_driver_vtable_sifive_nb2emmc.emmc,
};

/* From flash */
struct __metal_driver_sifive_flash __metal_dt_flash = {
    .flash.vtable = &__metal_driver_vtable_sifive_flash.flash,
};

/* From nb2qspi0@261010000 */
struct __metal_driver_sifive_nb2qspi0 __metal_dt_nb2qspi0_261010000 = {
    .qspi.vtable = &__metal_driver_vtable_sifive_nb2qspi0.qspi,
};

/* From nb2uart0@302011000 */
struct __metal_driver_sifive_nb2uart0 __metal_dt_nb2uart0_302011000 = {
    .uart.vtable = &__metal_driver_vtable_sifive_nb2uart0.uart,
};

/* From nb2uart0@302012000 */
struct __metal_driver_sifive_nb2uart0 __metal_dt_nb2uart0_302012000 = {
    .uart.vtable = &__metal_driver_vtable_sifive_nb2uart0.uart,
};

/* From nb2wdt@302058000 */
struct __metal_driver_sifive_nb2wdt __metal_dt_nb2wdt_302058000 = {
    .watchdog.vtable = &__metal_driver_vtable_sifive_nb2wdt.watchdog,
};


#endif /* METAL_INLINE_H*/
#endif /* ! ASSEMBLY */
