/* Copyright 2019 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */
/* ----------------------------------- */
/* [XXXXX] 21-05-2019 10-54-35        */
/* ----------------------------------- */

#ifndef ASSEMBLY

#ifndef COREIP_U54MC_RTL__METAL_INLINE_H
#define COREIP_U54MC_RTL__METAL_INLINE_H

#include <metal/machine.h>


/* --------------------- fixed_clock ------------ */


/* --------------------- fixed_factor_clock ------------ */


/* --------------------- sifive_clint0 ------------ */
extern inline unsigned long __metal_driver_sifive_clint0_control_base(struct metal_interrupt *controller);
extern inline unsigned long __metal_driver_sifive_clint0_control_size(struct metal_interrupt *controller);
extern inline int __metal_driver_sifive_clint0_num_interrupts(struct metal_interrupt *controller);
extern inline struct metal_interrupt * __metal_driver_sifive_clint0_interrupt_parents(struct metal_interrupt *controller, int idx);
extern inline int __metal_driver_sifive_clint0_interrupt_lines(struct metal_interrupt *controller, int idx);


/* --------------------- cpu ------------ */
extern inline int __metal_driver_cpu_timebase(struct metal_cpu *cpu);
extern inline struct metal_interrupt * __metal_driver_cpu_interrupt_controller(struct metal_cpu *cpu);
extern inline int __metal_driver_cpu_num_pmp_regions(struct metal_cpu *cpu);


/* --------------------- sifive_plic0 ------------ */
extern inline unsigned long __metal_driver_sifive_plic0_control_base(struct metal_interrupt *controller);
extern inline unsigned long __metal_driver_sifive_plic0_control_size(struct metal_interrupt *controller);
extern inline int __metal_driver_sifive_plic0_num_interrupts(struct metal_interrupt *controller);
extern inline int __metal_driver_sifive_plic0_max_priority(struct metal_interrupt *controller);
extern inline struct metal_interrupt * __metal_driver_sifive_plic0_interrupt_parents(struct metal_interrupt *controller, int idx);
extern inline int __metal_driver_sifive_plic0_interrupt_lines(struct metal_interrupt *controller, int idx);


/* --------------------- sifive_clic0 ------------ */


/* --------------------- sifive_local_external_interrupts0 ------------ */


/* --------------------- sifive_global_external_interrupts0 ------------ */
extern inline int __metal_driver_sifive_global_external_interrupts0_init_done( );
extern inline struct metal_interrupt * __metal_driver_sifive_global_external_interrupts0_interrupt_parent(struct metal_interrupt *controller);
extern inline int __metal_driver_sifive_global_external_interrupts0_num_interrupts(struct metal_interrupt *controller);
extern inline int __metal_driver_sifive_global_external_interrupts0_interrupt_lines(struct metal_interrupt *controller, int idx);


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
};

/* From cpu@1 */
struct __metal_driver_cpu __metal_dt_cpu_1 = {
    .cpu.vtable = &__metal_driver_vtable_cpu.cpu_vtable,
};

/* From cpu@2 */
struct __metal_driver_cpu __metal_dt_cpu_2 = {
    .cpu.vtable = &__metal_driver_vtable_cpu.cpu_vtable,
};

/* From cpu@3 */
struct __metal_driver_cpu __metal_dt_cpu_3 = {
    .cpu.vtable = &__metal_driver_vtable_cpu.cpu_vtable,
};

/* From cpu@4 */
struct __metal_driver_cpu __metal_dt_cpu_4 = {
    .cpu.vtable = &__metal_driver_vtable_cpu.cpu_vtable,
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

/* From global_external_interrupts */
struct __metal_driver_sifive_global_external_interrupts0 __metal_dt_global_external_interrupts = {
    .irc.vtable = &__metal_driver_vtable_sifive_global_external_interrupts0.global0_vtable,
    .init_done = 0,
};

/* From teststatus@4000 */
struct __metal_driver_sifive_test0 __metal_dt_teststatus_4000 = {
    .shutdown.vtable = &__metal_driver_vtable_sifive_test0.shutdown,
};

/* From cache_controller@2010000 */
struct __metal_driver_sifive_fu540_c000_l2 __metal_dt_cache_controller_2010000 = {
    .cache.vtable = &__metal_driver_vtable_sifive_fu540_c000_l2.cache,
};


#endif /* COREIP_U54MC_RTL__METAL_INLINE_H*/
#endif /* ! ASSEMBLY */
