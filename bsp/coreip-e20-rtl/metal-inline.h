/* Copyright 2019 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */
/* ----------------------------------- */
/* [XXXXX] 21-05-2019 10-54-34        */
/* ----------------------------------- */

#ifndef ASSEMBLY

#ifndef COREIP_E20_RTL__METAL_INLINE_H
#define COREIP_E20_RTL__METAL_INLINE_H

#include <metal/machine.h>


/* --------------------- fixed_clock ------------ */


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


/* --------------------- sifive_gpio0 ------------ */


/* --------------------- sifive_gpio_button ------------ */


/* --------------------- sifive_gpio_led ------------ */


/* --------------------- sifive_gpio_switch ------------ */


/* --------------------- sifive_spi0 ------------ */


/* --------------------- sifive_test0 ------------ */
extern inline unsigned long __metal_driver_sifive_test0_base( );
extern inline unsigned long __metal_driver_sifive_test0_size( );


/* --------------------- sifive_uart0 ------------ */


/* --------------------- sifive_fe310_g000_hfrosc ------------ */


/* --------------------- sifive_fe310_g000_hfxosc ------------ */


/* --------------------- sifive_fe310_g000_pll ------------ */


/* --------------------- fe310_g000_prci ------------ */


/* --------------------- sifive_fu540_c000_l2 ------------ */


struct metal_memory __metal_dt_mem_testram_20000000 = {
    ._base_address = 536870912UL,
    ._size = 134217728UL,
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

/* From teststatus@4000 */
struct __metal_driver_sifive_test0 __metal_dt_teststatus_4000 = {
    .shutdown.vtable = &__metal_driver_vtable_sifive_test0.shutdown,
};


#endif /* COREIP_E20_RTL__METAL_INLINE_H*/
#endif /* ! ASSEMBLY */
