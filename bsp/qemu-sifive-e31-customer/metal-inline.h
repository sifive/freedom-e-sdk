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


/* --------------------- sifive_gpio0 ------------ */
extern __inline__ unsigned long __metal_driver_sifive_gpio0_base(struct metal_gpio *gpio);
extern __inline__ unsigned long __metal_driver_sifive_gpio0_size(struct metal_gpio *gpio);
extern __inline__ int __metal_driver_sifive_gpio0_num_interrupts(struct metal_gpio *gpio);
extern __inline__ struct metal_interrupt * __metal_driver_sifive_gpio0_interrupt_parent(struct metal_gpio *gpio);
extern __inline__ int __metal_driver_sifive_gpio0_interrupt_lines(struct metal_gpio *gpio, int idx);


/* --------------------- sifive_gpio_button ------------ */


/* --------------------- sifive_gpio_led ------------ */
extern __inline__ struct metal_gpio * __metal_driver_sifive_gpio_led_gpio(struct metal_led *led);
extern __inline__ int __metal_driver_sifive_gpio_led_pin(struct metal_led *led);
extern __inline__ char * __metal_driver_sifive_gpio_led_label(struct metal_led *led);


/* --------------------- sifive_gpio_switch ------------ */


/* --------------------- sifive_i2c0 ------------ */


/* --------------------- sifive_prci0 ------------ */


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


/* --------------------- sifive_remapper2 ------------ */
extern __inline__ unsigned long __metal_driver_sifive_remapper2_base(const struct metal_remapper *remapper);
extern __inline__ unsigned long __metal_driver_sifive_remapper2_size(const struct metal_remapper *remapper);
extern __inline__ unsigned long long __metal_driver_sifive_remapper2_from_region_base(const struct metal_remapper *remapper);
extern __inline__ unsigned long long __metal_driver_sifive_remapper2_from_region_size(const struct metal_remapper *remapper);
extern __inline__ unsigned long long __metal_driver_sifive_remapper2_to_region_base(const struct metal_remapper *remapper);
extern __inline__ unsigned long long __metal_driver_sifive_remapper2_to_region_size(const struct metal_remapper *remapper);
extern __inline__ unsigned int __metal_driver_sifive_remapper2_max_from_entry_addr_width(const struct metal_remapper *remapper);


/* --------------------- sifive_rtc0 ------------ */
extern __inline__ unsigned long __metal_driver_sifive_rtc0_control_base(const struct metal_rtc *const rtc);
extern __inline__ unsigned long __metal_driver_sifive_rtc0_control_size(const struct metal_rtc *const rtc);
extern __inline__ struct metal_interrupt * __metal_driver_sifive_rtc0_interrupt_parent(const struct metal_rtc *const rtc);
extern __inline__ int __metal_driver_sifive_rtc0_interrupt_line(const struct metal_rtc *const rtc);
extern __inline__ struct metal_clock * __metal_driver_sifive_rtc0_clock(const struct metal_rtc *const rtc);


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
extern __inline__ unsigned long __metal_driver_sifive_wdog0_control_base(const struct metal_watchdog *const watchdog);
extern __inline__ unsigned long __metal_driver_sifive_wdog0_control_size(const struct metal_watchdog *const watchdog);
extern __inline__ struct metal_interrupt * __metal_driver_sifive_wdog0_interrupt_parent(const struct metal_watchdog *const watchdog);
extern __inline__ int __metal_driver_sifive_wdog0_interrupt_line(const struct metal_watchdog *const watchdog);
extern __inline__ struct metal_clock * __metal_driver_sifive_wdog0_clock(const struct metal_watchdog *const watchdog);


/* --------------------- sifive_fe310_g000_hfrosc ------------ */
extern __inline__ struct metal_clock * __metal_driver_sifive_fe310_g000_hfrosc_ref(const struct metal_clock *clock);
extern __inline__ struct __metal_driver_sifive_fe310_g000_prci * __metal_driver_sifive_fe310_g000_hfrosc_config_base(const struct metal_clock *clock);
extern __inline__ const struct __metal_driver_vtable_sifive_fe310_g000_prci * __metal_driver_sifive_fe310_g000_hfrosc_config_vtable(struct metal_clock *clock);
extern __inline__ long __metal_driver_sifive_fe310_g000_hfrosc_config_offset(const struct metal_clock *clock);


/* --------------------- sifive_fe310_g000_hfxosc ------------ */
extern __inline__ struct metal_clock * __metal_driver_sifive_fe310_g000_hfxosc_ref(const struct metal_clock *clock);
extern __inline__ struct __metal_driver_sifive_fe310_g000_prci * __metal_driver_sifive_fe310_g000_hfxosc_config_base(const struct metal_clock *clock);
extern __inline__ long __metal_driver_sifive_fe310_g000_hfxosc_config_offset(const struct metal_clock *clock);


/* --------------------- sifive_fe310_g000_lfrosc ------------ */
extern __inline__ struct metal_clock * __metal_driver_sifive_fe310_g000_lfrosc_lfrosc(const struct metal_clock *clock);
extern __inline__ struct metal_clock * __metal_driver_sifive_fe310_g000_lfrosc_psdlfaltclk(const struct metal_clock *clock);
extern __inline__ unsigned long int __metal_driver_sifive_fe310_g000_lfrosc_config_reg(const struct metal_clock *clock);
extern __inline__ unsigned long int __metal_driver_sifive_fe310_g000_lfrosc_mux_reg(const struct metal_clock *clock);


/* --------------------- sifive_fe310_g000_pll ------------ */
extern __inline__ struct metal_clock * __metal_driver_sifive_fe310_g000_pll_pllsel0(const struct metal_clock *clock);
extern __inline__ struct metal_clock * __metal_driver_sifive_fe310_g000_pll_pllref(const struct metal_clock *clock);
extern __inline__ struct __metal_driver_sifive_fe310_g000_prci * __metal_driver_sifive_fe310_g000_pll_config_base( );
extern __inline__ long __metal_driver_sifive_fe310_g000_pll_config_offset( );
extern __inline__ struct __metal_driver_sifive_fe310_g000_prci * __metal_driver_sifive_fe310_g000_pll_divider_base(const struct metal_clock *clock);
extern __inline__ long __metal_driver_sifive_fe310_g000_pll_divider_offset(const struct metal_clock *clock);
extern __inline__ long __metal_driver_sifive_fe310_g000_pll_init_rate( );


/* --------------------- fe310_g000_prci ------------ */
extern __inline__ long __metal_driver_sifive_fe310_g000_prci_base( );
extern __inline__ long __metal_driver_sifive_fe310_g000_prci_size( );
extern __inline__ const struct __metal_driver_vtable_sifive_fe310_g000_prci * __metal_driver_sifive_fe310_g000_prci_vtable( );


/* From clock@0 */
struct __metal_driver_fixed_clock __metal_dt_clock_0 = {
    .clock.vtable = &__metal_driver_vtable_fixed_clock.clock,
};

/* From clock@2 */
struct __metal_driver_fixed_clock __metal_dt_clock_2 = {
    .clock.vtable = &__metal_driver_vtable_fixed_clock.clock,
};

/* From clock@5 */
struct __metal_driver_fixed_clock __metal_dt_clock_5 = {
    .clock.vtable = &__metal_driver_vtable_fixed_clock.clock,
};

struct metal_memory __metal_dt_mem_dtim_80000000 = {
    ._base_address = 2147483648UL,
    ._size = 4194304UL,
    ._attrs = {
        .R = 1,
        .W = 1,
        .X = 1,
        .C = 1,
        .A = 1},
};

struct metal_memory __metal_dt_mem_spi_10014000 = {
    ._base_address = 536870912UL,
    ._size = 536870912UL,
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

/* From interrupt_controller */
struct __metal_driver_riscv_cpu_intc __metal_dt_cpu_0_interrupt_controller = {
    .controller.vtable = &__metal_driver_vtable_riscv_cpu_intc.controller_vtable,
    .init_done = 0,
};

/* From interrupt_controller@c000000 */
struct __metal_driver_riscv_plic0 __metal_dt_interrupt_controller_c000000 = {
    .controller.vtable = &__metal_driver_vtable_riscv_plic0.plic_vtable,
    .init_done = 0,
};

/* From bus_error_unit@4000000 */
struct metal_buserror __metal_dt_bus_error_unit_4000000 = {
	.__no_empty_structs = 0,
};

/* From local_external_interrupts_0 */
struct __metal_driver_sifive_local_external_interrupts0 __metal_dt_local_external_interrupts_0 = {
    .irc.vtable = &__metal_driver_vtable_sifive_local_external_interrupts0.local0_vtable,
    .init_done = 0,
};

/* From gpio@10012000 */
struct __metal_driver_sifive_gpio0 __metal_dt_gpio_10012000 = {
    .gpio.vtable = &__metal_driver_vtable_sifive_gpio0.gpio,
};

/* From led@0 */
struct __metal_driver_sifive_gpio_led __metal_dt_led_0 = {
    .led.vtable = &__metal_driver_vtable_sifive_led.led_vtable,
};

/* From led@1 */
struct __metal_driver_sifive_gpio_led __metal_dt_led_1 = {
    .led.vtable = &__metal_driver_vtable_sifive_led.led_vtable,
};

/* From led@2 */
struct __metal_driver_sifive_gpio_led __metal_dt_led_2 = {
    .led.vtable = &__metal_driver_vtable_sifive_led.led_vtable,
};

/* From pwm@10015000 */
struct __metal_driver_sifive_pwm0 __metal_dt_pwm_10015000 = {
    .pwm.vtable = &__metal_driver_vtable_sifive_pwm0.pwm,
};

/* From remapper@3000000 */
struct __metal_driver_sifive_remapper2 __metal_dt_remapper_3000000 = {
    .remapper.vtable = &__metal_driver_vtable_sifive_remapper2.remapper,
};

/* From aon@10000000 */
struct __metal_driver_sifive_rtc0 __metal_dt_rtc_10000000 = {
    .rtc.vtable = &__metal_driver_vtable_sifive_rtc0.rtc,
};

/* From spi@10014000 */
struct __metal_driver_sifive_spi0 __metal_dt_spi_10014000 = {
    .spi.vtable = &__metal_driver_vtable_sifive_spi0.spi,
};

/* From test@100000 */
struct __metal_driver_sifive_test0 __metal_dt_test_100000 = {
    .shutdown.vtable = &__metal_driver_vtable_sifive_test0.shutdown,
};

/* From serial@10013000 */
struct __metal_driver_sifive_uart0 __metal_dt_serial_10013000 = {
    .uart.vtable = &__metal_driver_vtable_sifive_uart0.uart,
};

/* From aon@10000000 */
struct __metal_driver_sifive_wdog0 __metal_dt_aon_10000000 = {
    .watchdog.vtable = &__metal_driver_vtable_sifive_wdog0.watchdog,
};

/* From clock@3 */
struct __metal_driver_sifive_fe310_g000_hfrosc __metal_dt_clock_3 = {
    .clock.vtable = &__metal_driver_vtable_sifive_fe310_g000_hfrosc.clock,
};

/* From clock@1 */
struct __metal_driver_sifive_fe310_g000_hfxosc __metal_dt_clock_1 = {
    .clock.vtable = &__metal_driver_vtable_sifive_fe310_g000_hfxosc.clock,
};

/* From clock@6 */
struct __metal_driver_sifive_fe310_g000_lfrosc __metal_dt_clock_6 = {
    .clock.vtable = &__metal_driver_vtable_sifive_fe310_g000_lfrosc.clock,
};

/* From clock@4 */
struct __metal_driver_sifive_fe310_g000_pll __metal_dt_clock_4 = {
    .clock.vtable = &__metal_driver_vtable_sifive_fe310_g000_pll.clock,
};

/* From prci@10008000 */
struct __metal_driver_sifive_fe310_g000_prci __metal_dt_prci_10008000 = {
    .vtable = &__metal_driver_vtable_sifive_fe310_g000_prci,
};


#endif /* METAL_INLINE_H*/
#endif /* ! ASSEMBLY */
