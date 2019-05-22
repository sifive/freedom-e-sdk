/* Copyright 2019 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */
/* ----------------------------------- */
/* [XXXXX] 21-05-2019 10-54-35        */
/* ----------------------------------- */

#ifndef ASSEMBLY

#include <metal/machine/platform.h>

#ifdef __METAL_MACHINE_MACROS

#ifndef MACROS_IF_COREIP_U54MC_RTL__METAL_H
#define MACROS_IF_COREIP_U54MC_RTL__METAL_H

#define __METAL_CLINT_NUM_PARENTS 10

#ifndef __METAL_CLINT_NUM_PARENTS
#define __METAL_CLINT_NUM_PARENTS 0
#endif
#define __METAL_PLIC_SUBINTERRUPTS 137

#define __METAL_PLIC_NUM_PARENTS 9

#ifndef __METAL_PLIC_SUBINTERRUPTS
#define __METAL_PLIC_SUBINTERRUPTS 0
#endif
#ifndef __METAL_PLIC_NUM_PARENTS
#define __METAL_PLIC_NUM_PARENTS 0
#endif
#ifndef __METAL_CLIC_SUBINTERRUPTS
#define __METAL_CLIC_SUBINTERRUPTS 0
#endif

#endif /* MACROS_IF_COREIP_U54MC_RTL__METAL_H*/

#else /* ! __METAL_MACHINE_MACROS */

#ifndef MACROS_ELSE_COREIP_U54MC_RTL__METAL_H
#define MACROS_ELSE_COREIP_U54MC_RTL__METAL_H

#define __METAL_CLINT_2000000_INTERRUPTS 10

#define METAL_MAX_CLINT_INTERRUPTS 10

#define __METAL_CLINT_NUM_PARENTS 10

#define __METAL_INTERRUPT_CONTROLLER_C000000_INTERRUPTS 9

#define __METAL_PLIC_SUBINTERRUPTS 137

#define METAL_MAX_PLIC_INTERRUPTS 9

#define __METAL_PLIC_NUM_PARENTS 9

#define __METAL_CLIC_SUBINTERRUPTS 0
#define METAL_MAX_CLIC_INTERRUPTS 0

#define METAL_MAX_LOCAL_EXT_INTERRUPTS 0

#define __METAL_GLOBAL_EXTERNAL_INTERRUPTS_INTERRUPTS 127

#define METAL_MAX_GLOBAL_EXT_INTERRUPTS 127

#define METAL_MAX_GPIO_INTERRUPTS 0

#define METAL_MAX_UART_INTERRUPTS 0


#include <metal/drivers/fixed-clock.h>
#include <metal/memory.h>
#include <metal/drivers/riscv,clint0.h>
#include <metal/drivers/riscv,cpu.h>
#include <metal/drivers/riscv,plic0.h>
#include <metal/pmp.h>
#include <metal/drivers/sifive,global-external-interrupts0.h>
#include <metal/drivers/sifive,test0.h>
#include <metal/drivers/sifive,fu540-c000,l2.h>

struct metal_memory __metal_dt_mem_dtim_1000000;

struct metal_memory __metal_dt_mem_itim_1800000;

struct metal_memory __metal_dt_mem_itim_1808000;

struct metal_memory __metal_dt_mem_itim_1810000;

struct metal_memory __metal_dt_mem_itim_1818000;

struct metal_memory __metal_dt_mem_itim_1820000;

struct metal_memory __metal_dt_mem_memory_80000000;

/* From clint@2000000 */
struct __metal_driver_riscv_clint0 __metal_dt_clint_2000000;

/* From cpu@0 */
struct __metal_driver_cpu __metal_dt_cpu_0;

/* From cpu@1 */
struct __metal_driver_cpu __metal_dt_cpu_1;

/* From cpu@2 */
struct __metal_driver_cpu __metal_dt_cpu_2;

/* From cpu@3 */
struct __metal_driver_cpu __metal_dt_cpu_3;

/* From cpu@4 */
struct __metal_driver_cpu __metal_dt_cpu_4;

struct __metal_driver_riscv_cpu_intc __metal_dt_cpu_0_interrupt_controller;

struct __metal_driver_riscv_cpu_intc __metal_dt_cpu_1_interrupt_controller;

struct __metal_driver_riscv_cpu_intc __metal_dt_cpu_2_interrupt_controller;

struct __metal_driver_riscv_cpu_intc __metal_dt_cpu_3_interrupt_controller;

struct __metal_driver_riscv_cpu_intc __metal_dt_cpu_4_interrupt_controller;

/* From interrupt_controller@c000000 */
struct __metal_driver_riscv_plic0 __metal_dt_interrupt_controller_c000000;

struct metal_pmp __metal_dt_pmp;

/* From global_external_interrupts */
struct __metal_driver_sifive_global_external_interrupts0 __metal_dt_global_external_interrupts;

/* From teststatus@4000 */
struct __metal_driver_sifive_test0 __metal_dt_teststatus_4000;

/* From cache_controller@2010000 */
struct __metal_driver_sifive_fu540_c000_l2 __metal_dt_cache_controller_2010000;



/* --------------------- fixed_clock ------------ */


/* --------------------- fixed_factor_clock ------------ */


/* --------------------- sifive_clint0 ------------ */
static inline unsigned long __metal_driver_sifive_clint0_control_base(struct metal_interrupt *controller)
{
	if ((uintptr_t)controller == (uintptr_t)&__metal_dt_clint_2000000) {
		return METAL_RISCV_CLINT0_2000000_BASE_ADDRESS;
	}
	else {
		return 0;
	}
}

static inline unsigned long __metal_driver_sifive_clint0_control_size(struct metal_interrupt *controller)
{
	if ((uintptr_t)controller == (uintptr_t)&__metal_dt_clint_2000000) {
		return METAL_RISCV_CLINT0_2000000_SIZE;
	}
	else {
		return 0;
	}
}

static inline int __metal_driver_sifive_clint0_num_interrupts(struct metal_interrupt *controller)
{
	if ((uintptr_t)controller == (uintptr_t)&__metal_dt_clint_2000000) {
		return METAL_MAX_CLINT_INTERRUPTS;
	}
	else {
		return 0;
	}
}

static inline struct metal_interrupt * __metal_driver_sifive_clint0_interrupt_parents(struct metal_interrupt *controller, int idx)
{
	if (idx == 0) {
		return (struct metal_interrupt *)&__metal_dt_cpu_0_interrupt_controller.controller;
	}
	else if (idx == 1) {
		return (struct metal_interrupt *)&__metal_dt_cpu_0_interrupt_controller.controller;
	}
	else if (idx == 2) {
		return (struct metal_interrupt *)&__metal_dt_cpu_1_interrupt_controller.controller;
	}
	else if (idx == 3) {
		return (struct metal_interrupt *)&__metal_dt_cpu_1_interrupt_controller.controller;
	}
	else if (idx == 4) {
		return (struct metal_interrupt *)&__metal_dt_cpu_2_interrupt_controller.controller;
	}
	else if (idx == 5) {
		return (struct metal_interrupt *)&__metal_dt_cpu_2_interrupt_controller.controller;
	}
	else if (idx == 6) {
		return (struct metal_interrupt *)&__metal_dt_cpu_3_interrupt_controller.controller;
	}
	else if (idx == 7) {
		return (struct metal_interrupt *)&__metal_dt_cpu_3_interrupt_controller.controller;
	}
	else if (idx == 8) {
		return (struct metal_interrupt *)&__metal_dt_cpu_4_interrupt_controller.controller;
	}
	else if (idx == 9) {
		return (struct metal_interrupt *)&__metal_dt_cpu_4_interrupt_controller.controller;
	}
	else {
		return NULL;
	}
}

static inline int __metal_driver_sifive_clint0_interrupt_lines(struct metal_interrupt *controller, int idx)
{
	if (idx == 0) {
		return 3;
	}
	else if (idx == 1) {
		return 7;
	}
	else if (idx == 2) {
		return 3;
	}
	else if (idx == 3) {
		return 7;
	}
	else if (idx == 4) {
		return 3;
	}
	else if (idx == 5) {
		return 7;
	}
	else if (idx == 6) {
		return 3;
	}
	else if (idx == 7) {
		return 7;
	}
	else if (idx == 8) {
		return 3;
	}
	else if (idx == 9) {
		return 7;
	}
	else {
		return 0;
	}
}



/* --------------------- cpu ------------ */
static inline int __metal_driver_cpu_timebase(struct metal_cpu *cpu)
{
	if ((uintptr_t)cpu == (uintptr_t)&__metal_dt_cpu_0) {
		return 1000000;
	}
	else if ((uintptr_t)cpu == (uintptr_t)&__metal_dt_cpu_0) {
		return 1000000;
	}
	else if ((uintptr_t)cpu == (uintptr_t)&__metal_dt_cpu_1) {
		return 1000000;
	}
	else if ((uintptr_t)cpu == (uintptr_t)&__metal_dt_cpu_2) {
		return 1000000;
	}
	else if ((uintptr_t)cpu == (uintptr_t)&__metal_dt_cpu_3) {
		return 1000000;
	}
	else {
		return 0;
	}
}

static inline struct metal_interrupt * __metal_driver_cpu_interrupt_controller(struct metal_cpu *cpu)
{
	if ((uintptr_t)cpu == (uintptr_t)&__metal_dt_cpu_0) {
		return &__metal_dt_cpu_0_interrupt_controller.controller;
	}
	else if ((uintptr_t)cpu == (uintptr_t)&__metal_dt_cpu_0) {
		return &__metal_dt_cpu_0_interrupt_controller.controller;
	}
	else if ((uintptr_t)cpu == (uintptr_t)&__metal_dt_cpu_1) {
		return &__metal_dt_cpu_1_interrupt_controller.controller;
	}
	else if ((uintptr_t)cpu == (uintptr_t)&__metal_dt_cpu_2) {
		return &__metal_dt_cpu_2_interrupt_controller.controller;
	}
	else if ((uintptr_t)cpu == (uintptr_t)&__metal_dt_cpu_3) {
		return &__metal_dt_cpu_3_interrupt_controller.controller;
	}
	else {
		return NULL;
	}
}

static inline int __metal_driver_cpu_num_pmp_regions(struct metal_cpu *cpu)
{
	if ((uintptr_t)cpu == (uintptr_t)&__metal_dt_cpu_0) {
		return 8;
	}
	else if ((uintptr_t)cpu == (uintptr_t)&__metal_dt_cpu_0) {
		return 8;
	}
	else if ((uintptr_t)cpu == (uintptr_t)&__metal_dt_cpu_1) {
		return 8;
	}
	else if ((uintptr_t)cpu == (uintptr_t)&__metal_dt_cpu_2) {
		return 8;
	}
	else if ((uintptr_t)cpu == (uintptr_t)&__metal_dt_cpu_3) {
		return 8;
	}
	else {
		return 0;
	}
}



/* --------------------- sifive_plic0 ------------ */
static inline unsigned long __metal_driver_sifive_plic0_control_base(struct metal_interrupt *controller)
{
	if ((uintptr_t)controller == (uintptr_t)&__metal_dt_interrupt_controller_c000000) {
		return METAL_RISCV_PLIC0_C000000_BASE_ADDRESS;
	}
	else {
		return 0;
	}
}

static inline unsigned long __metal_driver_sifive_plic0_control_size(struct metal_interrupt *controller)
{
	if ((uintptr_t)controller == (uintptr_t)&__metal_dt_interrupt_controller_c000000) {
		return METAL_RISCV_PLIC0_C000000_SIZE;
	}
	else {
		return 0;
	}
}

static inline int __metal_driver_sifive_plic0_num_interrupts(struct metal_interrupt *controller)
{
	if ((uintptr_t)controller == (uintptr_t)&__metal_dt_interrupt_controller_c000000) {
		return METAL_RISCV_PLIC0_C000000_RISCV_NDEV;
	}
	else {
		return 0;
	}
}

static inline int __metal_driver_sifive_plic0_max_priority(struct metal_interrupt *controller)
{
	if ((uintptr_t)controller == (uintptr_t)&__metal_dt_interrupt_controller_c000000) {
		return METAL_RISCV_PLIC0_C000000_RISCV_MAX_PRIORITY;
	}
	else {
		return 0;
	}
}

static inline struct metal_interrupt * __metal_driver_sifive_plic0_interrupt_parents(struct metal_interrupt *controller, int idx)
{
	if (idx == 0) {
		return (struct metal_interrupt *)&__metal_dt_cpu_0_interrupt_controller.controller;
	}
	else if (idx == 0) {
		return (struct metal_interrupt *)&__metal_dt_cpu_0_interrupt_controller.controller;
	}
	else if (idx == 1) {
		return (struct metal_interrupt *)&__metal_dt_cpu_1_interrupt_controller.controller;
	}
	else if (idx == 2) {
		return (struct metal_interrupt *)&__metal_dt_cpu_1_interrupt_controller.controller;
	}
	else if (idx == 3) {
		return (struct metal_interrupt *)&__metal_dt_cpu_2_interrupt_controller.controller;
	}
	else if (idx == 4) {
		return (struct metal_interrupt *)&__metal_dt_cpu_2_interrupt_controller.controller;
	}
	else if (idx == 5) {
		return (struct metal_interrupt *)&__metal_dt_cpu_3_interrupt_controller.controller;
	}
	else if (idx == 6) {
		return (struct metal_interrupt *)&__metal_dt_cpu_3_interrupt_controller.controller;
	}
	else if (idx == 7) {
		return (struct metal_interrupt *)&__metal_dt_cpu_4_interrupt_controller.controller;
	}
	else if (idx == 8) {
		return (struct metal_interrupt *)&__metal_dt_cpu_4_interrupt_controller.controller;
	}
	else {
		return NULL;
	}
}

static inline int __metal_driver_sifive_plic0_interrupt_lines(struct metal_interrupt *controller, int idx)
{
	if (idx == 0) {
		return 11;
	}
	else if (idx == 0) {
		return 11;
	}
	else if (idx == 1) {
		return 11;
	}
	else if (idx == 2) {
		return 9;
	}
	else if (idx == 3) {
		return 11;
	}
	else if (idx == 4) {
		return 9;
	}
	else if (idx == 5) {
		return 11;
	}
	else if (idx == 6) {
		return 9;
	}
	else if (idx == 7) {
		return 11;
	}
	else if (idx == 8) {
		return 9;
	}
	else {
		return 0;
	}
}



/* --------------------- sifive_clic0 ------------ */


/* --------------------- sifive_local_external_interrupts0 ------------ */


/* --------------------- sifive_global_external_interrupts0 ------------ */
static inline int __metal_driver_sifive_global_external_interrupts0_init_done()
{
		return 0;
}

static inline struct metal_interrupt * __metal_driver_sifive_global_external_interrupts0_interrupt_parent(struct metal_interrupt *controller)
{
	if ((uintptr_t)controller == (uintptr_t)&__metal_dt_global_external_interrupts) {
		return (struct metal_interrupt *)&__metal_dt_interrupt_controller_c000000.controller;
	}
	else {
		return NULL;
	}
}

static inline int __metal_driver_sifive_global_external_interrupts0_num_interrupts(struct metal_interrupt *controller)
{
	if ((uintptr_t)controller == (uintptr_t)&__metal_dt_global_external_interrupts) {
		return METAL_MAX_GLOBAL_EXT_INTERRUPTS;
	}
	else {
		return 0;
	}
}

static inline int __metal_driver_sifive_global_external_interrupts0_interrupt_lines(struct metal_interrupt *controller, int idx)
{
	if (idx == 0) {
		return 1;
	}
	else if (idx == 1) {
		return 2;
	}
	else if (idx == 2) {
		return 3;
	}
	else if (idx == 3) {
		return 4;
	}
	else if (idx == 4) {
		return 5;
	}
	else if (idx == 5) {
		return 6;
	}
	else if (idx == 6) {
		return 7;
	}
	else if (idx == 7) {
		return 8;
	}
	else if (idx == 8) {
		return 9;
	}
	else if (idx == 9) {
		return 10;
	}
	else if (idx == 10) {
		return 11;
	}
	else if (idx == 11) {
		return 12;
	}
	else if (idx == 12) {
		return 13;
	}
	else if (idx == 13) {
		return 14;
	}
	else if (idx == 14) {
		return 15;
	}
	else if (idx == 15) {
		return 16;
	}
	else if (idx == 16) {
		return 17;
	}
	else if (idx == 17) {
		return 18;
	}
	else if (idx == 18) {
		return 19;
	}
	else if (idx == 19) {
		return 20;
	}
	else if (idx == 20) {
		return 21;
	}
	else if (idx == 21) {
		return 22;
	}
	else if (idx == 22) {
		return 23;
	}
	else if (idx == 23) {
		return 24;
	}
	else if (idx == 24) {
		return 25;
	}
	else if (idx == 25) {
		return 26;
	}
	else if (idx == 26) {
		return 27;
	}
	else if (idx == 27) {
		return 28;
	}
	else if (idx == 28) {
		return 29;
	}
	else if (idx == 29) {
		return 30;
	}
	else if (idx == 30) {
		return 31;
	}
	else if (idx == 31) {
		return 32;
	}
	else if (idx == 32) {
		return 33;
	}
	else if (idx == 33) {
		return 34;
	}
	else if (idx == 34) {
		return 35;
	}
	else if (idx == 35) {
		return 36;
	}
	else if (idx == 36) {
		return 37;
	}
	else if (idx == 37) {
		return 38;
	}
	else if (idx == 38) {
		return 39;
	}
	else if (idx == 39) {
		return 40;
	}
	else if (idx == 40) {
		return 41;
	}
	else if (idx == 41) {
		return 42;
	}
	else if (idx == 42) {
		return 43;
	}
	else if (idx == 43) {
		return 44;
	}
	else if (idx == 44) {
		return 45;
	}
	else if (idx == 45) {
		return 46;
	}
	else if (idx == 46) {
		return 47;
	}
	else if (idx == 47) {
		return 48;
	}
	else if (idx == 48) {
		return 49;
	}
	else if (idx == 49) {
		return 50;
	}
	else if (idx == 50) {
		return 51;
	}
	else if (idx == 51) {
		return 52;
	}
	else if (idx == 52) {
		return 53;
	}
	else if (idx == 53) {
		return 54;
	}
	else if (idx == 54) {
		return 55;
	}
	else if (idx == 55) {
		return 56;
	}
	else if (idx == 56) {
		return 57;
	}
	else if (idx == 57) {
		return 58;
	}
	else if (idx == 58) {
		return 59;
	}
	else if (idx == 59) {
		return 60;
	}
	else if (idx == 60) {
		return 61;
	}
	else if (idx == 61) {
		return 62;
	}
	else if (idx == 62) {
		return 63;
	}
	else if (idx == 63) {
		return 64;
	}
	else if (idx == 64) {
		return 65;
	}
	else if (idx == 65) {
		return 66;
	}
	else if (idx == 66) {
		return 67;
	}
	else if (idx == 67) {
		return 68;
	}
	else if (idx == 68) {
		return 69;
	}
	else if (idx == 69) {
		return 70;
	}
	else if (idx == 70) {
		return 71;
	}
	else if (idx == 71) {
		return 72;
	}
	else if (idx == 72) {
		return 73;
	}
	else if (idx == 73) {
		return 74;
	}
	else if (idx == 74) {
		return 75;
	}
	else if (idx == 75) {
		return 76;
	}
	else if (idx == 76) {
		return 77;
	}
	else if (idx == 77) {
		return 78;
	}
	else if (idx == 78) {
		return 79;
	}
	else if (idx == 79) {
		return 80;
	}
	else if (idx == 80) {
		return 81;
	}
	else if (idx == 81) {
		return 82;
	}
	else if (idx == 82) {
		return 83;
	}
	else if (idx == 83) {
		return 84;
	}
	else if (idx == 84) {
		return 85;
	}
	else if (idx == 85) {
		return 86;
	}
	else if (idx == 86) {
		return 87;
	}
	else if (idx == 87) {
		return 88;
	}
	else if (idx == 88) {
		return 89;
	}
	else if (idx == 89) {
		return 90;
	}
	else if (idx == 90) {
		return 91;
	}
	else if (idx == 91) {
		return 92;
	}
	else if (idx == 92) {
		return 93;
	}
	else if (idx == 93) {
		return 94;
	}
	else if (idx == 94) {
		return 95;
	}
	else if (idx == 95) {
		return 96;
	}
	else if (idx == 96) {
		return 97;
	}
	else if (idx == 97) {
		return 98;
	}
	else if (idx == 98) {
		return 99;
	}
	else if (idx == 99) {
		return 100;
	}
	else if (idx == 100) {
		return 101;
	}
	else if (idx == 101) {
		return 102;
	}
	else if (idx == 102) {
		return 103;
	}
	else if (idx == 103) {
		return 104;
	}
	else if (idx == 104) {
		return 105;
	}
	else if (idx == 105) {
		return 106;
	}
	else if (idx == 106) {
		return 107;
	}
	else if (idx == 107) {
		return 108;
	}
	else if (idx == 108) {
		return 109;
	}
	else if (idx == 109) {
		return 110;
	}
	else if (idx == 110) {
		return 111;
	}
	else if (idx == 111) {
		return 112;
	}
	else if (idx == 112) {
		return 113;
	}
	else if (idx == 113) {
		return 114;
	}
	else if (idx == 114) {
		return 115;
	}
	else if (idx == 115) {
		return 116;
	}
	else if (idx == 116) {
		return 117;
	}
	else if (idx == 117) {
		return 118;
	}
	else if (idx == 118) {
		return 119;
	}
	else if (idx == 119) {
		return 120;
	}
	else if (idx == 120) {
		return 121;
	}
	else if (idx == 121) {
		return 122;
	}
	else if (idx == 122) {
		return 123;
	}
	else if (idx == 123) {
		return 124;
	}
	else if (idx == 124) {
		return 125;
	}
	else if (idx == 125) {
		return 126;
	}
	else if (idx == 126) {
		return 127;
	}
	else {
		return 0;
	}
}



/* --------------------- sifive_gpio0 ------------ */


/* --------------------- sifive_gpio_button ------------ */


/* --------------------- sifive_gpio_led ------------ */


/* --------------------- sifive_gpio_switch ------------ */


/* --------------------- sifive_spi0 ------------ */


/* --------------------- sifive_test0 ------------ */
static inline unsigned long __metal_driver_sifive_test0_base( )
{
		return 16384;
}

static inline unsigned long __metal_driver_sifive_test0_size( )
{
		return 4096;
}



/* --------------------- sifive_uart0 ------------ */


/* --------------------- sifive_fe310_g000_hfrosc ------------ */


/* --------------------- sifive_fe310_g000_hfxosc ------------ */


/* --------------------- sifive_fe310_g000_pll ------------ */


/* --------------------- sifive_fe310_g000_prci ------------ */


/* --------------------- sifive_fu540_c000_l2 ------------ */


#define __METAL_DT_MAX_MEMORIES 7

asm (".weak __metal_memory_table");
struct metal_memory *__metal_memory_table[] = {
					&__metal_dt_mem_dtim_1000000,
					&__metal_dt_mem_itim_1800000,
					&__metal_dt_mem_itim_1808000,
					&__metal_dt_mem_itim_1810000,
					&__metal_dt_mem_itim_1818000,
					&__metal_dt_mem_itim_1820000,
					&__metal_dt_mem_memory_80000000};

/* From clint@2000000 */
#define __METAL_DT_RISCV_CLINT0_HANDLE (&__metal_dt_clint_2000000.controller)

#define __METAL_DT_CLINT_2000000_HANDLE (&__metal_dt_clint_2000000.controller)

#define __METAL_DT_MAX_HARTS 5

asm (".weak __metal_cpu_table");
struct __metal_driver_cpu *__metal_cpu_table[] = {
					&__metal_dt_cpu_0,
					&__metal_dt_cpu_1,
					&__metal_dt_cpu_2,
					&__metal_dt_cpu_3,
					&__metal_dt_cpu_4};

/* From interrupt_controller@c000000 */
#define __METAL_DT_RISCV_PLIC0_HANDLE (&__metal_dt_interrupt_controller_c000000.controller)

#define __METAL_DT_INTERRUPT_CONTROLLER_C000000_HANDLE (&__metal_dt_interrupt_controller_c000000.controller)

#define __METAL_DT_PMP_HANDLE (&__metal_dt_pmp)

/* From global_external_interrupts */
#define __METAL_DT_SIFIVE_GLOBAL_EXINTR0_HANDLE (&__metal_dt_global_external_interrupts.irc)

#define __METAL_DT_GLOBAL_EXTERNAL_INTERRUPTS_HANDLE (&__metal_dt_global_external_interrupts.irc)

#define __MEE_DT_MAX_GPIOS 0

asm (".weak __metal_gpio_table");
struct __metal_driver_sifive_gpio0 *__metal_gpio_table[] = {
					NULL };
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
#define __METAL_DT_MAX_SPIS 0

asm (".weak __metal_spi_table");
struct __metal_driver_sifive_spi0 *__metal_spi_table[] = {
					NULL };
/* From teststatus@4000 */
#define __METAL_DT_SHUTDOWN_HANDLE (&__metal_dt_teststatus_4000.shutdown)

#define __METAL_DT_TESTSTATUS_4000_HANDLE (&__metal_dt_teststatus_4000.shutdown)

/* From cache_controller@2010000 */
#define __METAL_DT_SIFIVE_FU540_C000_L2_HANDLE (&__metal_dt_cache_controller_2010000)

#define __METAL_DT_CACHE_CONTROLLER_2010000_HANDLE (&__metal_dt_cache_controller_2010000)

#endif /* MACROS_ELSE_COREIP_U54MC_RTL__METAL_H*/

#endif /* ! __METAL_MACHINE_MACROS */

#endif /* ! ASSEMBLY */
