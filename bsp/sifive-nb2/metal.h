/* Copyright 2019 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */
/* ----------------------------------- */
/* ----------------------------------- */

#ifndef ASSEMBLY

#include <metal/machine/platform.h>

#ifdef __METAL_MACHINE_MACROS

#ifndef MACROS_IF_METAL_H
#define MACROS_IF_METAL_H

#define __METAL_CLINT_NUM_PARENTS 8

#ifndef __METAL_CLINT_NUM_PARENTS
#define __METAL_CLINT_NUM_PARENTS 0
#endif
#define __METAL_PLIC_SUBINTERRUPTS 138

#define __METAL_PLIC_NUM_PARENTS 8

#ifndef __METAL_PLIC_SUBINTERRUPTS
#define __METAL_PLIC_SUBINTERRUPTS 0
#endif
#ifndef __METAL_PLIC_NUM_PARENTS
#define __METAL_PLIC_NUM_PARENTS 0
#endif
#ifndef __METAL_CLIC_SUBINTERRUPTS
#define __METAL_CLIC_SUBINTERRUPTS 0
#endif

#endif /* MACROS_IF_METAL_H*/

#else /* ! __METAL_MACHINE_MACROS */

#ifndef MACROS_ELSE_METAL_H
#define MACROS_ELSE_METAL_H

#define __METAL_CLINT_2000000_INTERRUPTS 8

#define METAL_MAX_CLINT_INTERRUPTS 8

#define __METAL_CLINT_NUM_PARENTS 8

#define __METAL_INTERRUPT_CONTROLLER_C000000_INTERRUPTS 8

#define __METAL_PLIC_SUBINTERRUPTS 138

#define METAL_MAX_PLIC_INTERRUPTS 8

#define __METAL_PLIC_NUM_PARENTS 8

#define METAL_SIFIVE_CCACHE0_INTERRUPTS { 130, 131, 132, 133, }

#define METAL_SIFIVE_CCACHE0_INTERRUPT_PARENT &__metal_dt_interrupt_controller_c000000.controller

#define METAL_CACHE_DRIVER_PREFIX sifive_ccache0

#define METAL_SIFIVE_CCACHE0_PERFMON_COUNTERS 0

#define __METAL_DT_SIFIVE_CCACHE0_HANDLE (struct metal_cache *)NULL

#define __METAL_CLIC_SUBINTERRUPTS 0
#define METAL_MAX_CLIC_INTERRUPTS 0

#define __METAL_LOCAL_EXTERNAL_INTERRUPTS_0_INTERRUPTS 16

#define __METAL_LOCAL_EXTERNAL_INTERRUPTS_1_INTERRUPTS 16

#define __METAL_LOCAL_EXTERNAL_INTERRUPTS_2_INTERRUPTS 16

#define __METAL_LOCAL_EXTERNAL_INTERRUPTS_3_INTERRUPTS 16

#define METAL_MAX_LOCAL_EXT_INTERRUPTS 16

#define __METAL_GLOBAL_EXTERNAL_INTERRUPTS_INTERRUPTS 127

#define METAL_MAX_GLOBAL_EXT_INTERRUPTS 127

#define METAL_MAX_GPIO_INTERRUPTS 0

#define METAL_MAX_I2C0_INTERRUPTS 0

#define METAL_MAX_PWM0_INTERRUPTS 0

#define METAL_MAX_PWM0_NCMP 0

#define __METAL_NB2EMMC_301007000_INTERRUPTS 2

#define METAL_MAX_EMMC_INTERRUPTS 2

#define METAL_EMMC_BUS_WIDTH 4

#define METAL_DMA_ENABLE 0

#define METAL_EMMC_MAX_FREQUENCY 26000000

#define METAL_FLASH_LABEL "MX25UM512"

#define METAL_JEDEC_ID_0 194

#define METAL_JEDEC_ID_1 128

#define METAL_JEDEC_ID_2 58

#define METAL_FLASH_BAUD 100000

#define METAL_FLASH_CHIP_SELECT 1

#define METAL_FLASH_SPI_MAX_FREQUENCY 2000000

#define METAL_FLASH_SIZE 33554432

#define METAL_FLASH_ERASE_BLOCK_SIZE 65536

#define METAL_FLASH_WRITE_BLOCK_SIZE 1

#define METAL_QSPI_AXI_BASE_ADDR 10737418240

#define METAL_QSPI_AXI_SIZE 67108864

#define __METAL_NB2UART0_302011000_INTERRUPTS 1

#define __METAL_NB2UART0_302012000_INTERRUPTS 1

#define METAL_MAX_UART_INTERRUPTS 1


#include <metal/drivers/fixed-clock.h>
#include <metal/memory.h>
#include <metal/drivers/riscv_clint0.h>
#include <metal/drivers/riscv_cpu.h>
#include <metal/drivers/riscv_plic0.h>
#include <metal/pmp.h>
#include <metal/drivers/sifive_buserror0.h>
#include <metal/drivers/sifive_ccache0.h>
#include <metal/drivers/sifive_local-external-interrupts0.h>
#include <metal/drivers/sifive_global-external-interrupts0.h>
#include <metal/drivers/sifive_test0.h>
#include <metal/drivers/sifive_trace.h>
#include <metal/drivers/sifive_nb2emmc.h>
#include <metal/drivers/sifive_flash.h>
#include <metal/drivers/sifive_nb2qspi0.h>
#include <metal/drivers/sifive_nb2uart0.h>
#include <metal/drivers/sifive_nb2wdt.h>

/* From subsystem_pbus_clock */
extern struct __metal_driver_fixed_clock __metal_dt_subsystem_pbus_clock;

extern struct metal_memory __metal_dt_mem_memory_800000000;

/* From clint@2000000 */
extern struct __metal_driver_riscv_clint0 __metal_dt_clint_2000000;

/* From cpu@0 */
extern struct __metal_driver_cpu __metal_dt_cpu_0;

/* From cpu@1 */
extern struct __metal_driver_cpu __metal_dt_cpu_1;

/* From cpu@2 */
extern struct __metal_driver_cpu __metal_dt_cpu_2;

/* From cpu@3 */
extern struct __metal_driver_cpu __metal_dt_cpu_3;

extern struct __metal_driver_riscv_cpu_intc __metal_dt_cpu_0_interrupt_controller;

extern struct __metal_driver_riscv_cpu_intc __metal_dt_cpu_1_interrupt_controller;

extern struct __metal_driver_riscv_cpu_intc __metal_dt_cpu_2_interrupt_controller;

extern struct __metal_driver_riscv_cpu_intc __metal_dt_cpu_3_interrupt_controller;

/* From interrupt_controller@c000000 */
extern struct __metal_driver_riscv_plic0 __metal_dt_interrupt_controller_c000000;

extern struct metal_pmp __metal_dt_pmp;

/* From bus_error_unit@1700000 */
extern struct metal_buserror __metal_dt_bus_error_unit_1700000;

/* From bus_error_unit@1701000 */
extern struct metal_buserror __metal_dt_bus_error_unit_1701000;

/* From bus_error_unit@1702000 */
extern struct metal_buserror __metal_dt_bus_error_unit_1702000;

/* From bus_error_unit@1703000 */
extern struct metal_buserror __metal_dt_bus_error_unit_1703000;

/* From local_external_interrupts_0 */
extern struct __metal_driver_sifive_local_external_interrupts0 __metal_dt_local_external_interrupts_0;

/* From local_external_interrupts_1 */
extern struct __metal_driver_sifive_local_external_interrupts0 __metal_dt_local_external_interrupts_1;

/* From local_external_interrupts_2 */
extern struct __metal_driver_sifive_local_external_interrupts0 __metal_dt_local_external_interrupts_2;

/* From local_external_interrupts_3 */
extern struct __metal_driver_sifive_local_external_interrupts0 __metal_dt_local_external_interrupts_3;

/* From global_external_interrupts */
extern struct __metal_driver_sifive_global_external_interrupts0 __metal_dt_global_external_interrupts;

/* From teststatus@4000 */
extern struct __metal_driver_sifive_test0 __metal_dt_teststatus_4000;

/* From trace_encoder_0@10000000 */
extern struct __metal_driver_sifive_trace __metal_dt_trace_encoder_0_10000000;

/* From trace_encoder_1@10001000 */
extern struct __metal_driver_sifive_trace __metal_dt_trace_encoder_1_10001000;

/* From trace_encoder_2@10002000 */
extern struct __metal_driver_sifive_trace __metal_dt_trace_encoder_2_10002000;

/* From trace_encoder_3@10003000 */
extern struct __metal_driver_sifive_trace __metal_dt_trace_encoder_3_10003000;

/* From trace_funnel@10008000 */
extern struct __metal_driver_sifive_trace __metal_dt_trace_funnel_10008000;

/* From nb2emmc@301007000 */
extern struct __metal_driver_sifive_nb2emmc __metal_dt_nb2emmc_301007000;

/* From flash */
extern struct __metal_driver_sifive_flash __metal_dt_flash;

/* From nb2qspi0@261010000 */
extern struct __metal_driver_sifive_nb2qspi0 __metal_dt_nb2qspi0_261010000;

/* From nb2uart0@302011000 */
extern struct __metal_driver_sifive_nb2uart0 __metal_dt_nb2uart0_302011000;

/* From nb2uart0@302012000 */
extern struct __metal_driver_sifive_nb2uart0 __metal_dt_nb2uart0_302012000;

/* From nb2wdt@302058000 */
extern struct __metal_driver_sifive_nb2wdt __metal_dt_nb2wdt_302058000;



/* --------------------- fixed_clock ------------ */
static __inline__ unsigned long __metal_driver_fixed_clock_rate(const struct metal_clock *clock)
{
	if ((uintptr_t)clock == (uintptr_t)&__metal_dt_subsystem_pbus_clock) {
		return METAL_FIXED_CLOCK__CLOCK_FREQUENCY;
	}
	else {
		return 0;
	}
}



/* --------------------- fixed_factor_clock ------------ */


/* --------------------- sifive_clint0 ------------ */
static __inline__ unsigned long __metal_driver_sifive_clint0_control_base(struct metal_interrupt *controller)
{
	if ((uintptr_t)controller == (uintptr_t)&__metal_dt_clint_2000000) {
		return METAL_RISCV_CLINT0_2000000_BASE_ADDRESS;
	}
	else {
		return 0;
	}
}

static __inline__ unsigned long __metal_driver_sifive_clint0_control_size(struct metal_interrupt *controller)
{
	if ((uintptr_t)controller == (uintptr_t)&__metal_dt_clint_2000000) {
		return METAL_RISCV_CLINT0_2000000_SIZE;
	}
	else {
		return 0;
	}
}

static __inline__ int __metal_driver_sifive_clint0_num_interrupts(struct metal_interrupt *controller)
{
	if ((uintptr_t)controller == (uintptr_t)&__metal_dt_clint_2000000) {
		return METAL_MAX_CLINT_INTERRUPTS;
	}
	else {
		return 0;
	}
}

static __inline__ struct metal_interrupt * __metal_driver_sifive_clint0_interrupt_parents(struct metal_interrupt *controller, int idx)
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
	else {
		return NULL;
	}
}

static __inline__ int __metal_driver_sifive_clint0_interrupt_lines(struct metal_interrupt *controller, int idx)
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
	else {
		return 0;
	}
}



/* --------------------- cpu ------------ */
static __inline__ int __metal_driver_cpu_hartid(struct metal_cpu *cpu)
{
	if ((uintptr_t)cpu == (uintptr_t)&__metal_dt_cpu_0) {
		return 0;
	}
	else if ((uintptr_t)cpu == (uintptr_t)&__metal_dt_cpu_1) {
		return 1;
	}
	else if ((uintptr_t)cpu == (uintptr_t)&__metal_dt_cpu_2) {
		return 2;
	}
	else if ((uintptr_t)cpu == (uintptr_t)&__metal_dt_cpu_3) {
		return 3;
	}
	else {
		return -1;
	}
}

static __inline__ int __metal_driver_cpu_timebase(struct metal_cpu *cpu)
{
	if ((uintptr_t)cpu == (uintptr_t)&__metal_dt_cpu_0) {
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

static __inline__ struct metal_interrupt * __metal_driver_cpu_interrupt_controller(struct metal_cpu *cpu)
{
	if ((uintptr_t)cpu == (uintptr_t)&__metal_dt_cpu_0) {
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

static __inline__ int __metal_driver_cpu_num_pmp_regions(struct metal_cpu *cpu)
{
	if ((uintptr_t)cpu == (uintptr_t)&__metal_dt_cpu_0) {
		return 4;
	}
	else if ((uintptr_t)cpu == (uintptr_t)&__metal_dt_cpu_1) {
		return 4;
	}
	else if ((uintptr_t)cpu == (uintptr_t)&__metal_dt_cpu_2) {
		return 4;
	}
	else if ((uintptr_t)cpu == (uintptr_t)&__metal_dt_cpu_3) {
		return 4;
	}
	else {
		return 0;
	}
}

static __inline__ struct metal_buserror * __metal_driver_cpu_buserror(struct metal_cpu *cpu)
{
	if ((uintptr_t)cpu == (uintptr_t)&__metal_dt_cpu_0) {
		return &__metal_dt_bus_error_unit_1700000;
	}
	else if ((uintptr_t)cpu == (uintptr_t)&__metal_dt_cpu_1) {
		return &__metal_dt_bus_error_unit_1701000;
	}
	else if ((uintptr_t)cpu == (uintptr_t)&__metal_dt_cpu_2) {
		return &__metal_dt_bus_error_unit_1702000;
	}
	else if ((uintptr_t)cpu == (uintptr_t)&__metal_dt_cpu_3) {
		return &__metal_dt_bus_error_unit_1703000;
	}
	else {
		return NULL;
	}
}



/* --------------------- sifive_plic0 ------------ */
static __inline__ unsigned long __metal_driver_sifive_plic0_control_base(struct metal_interrupt *controller)
{
	if ((uintptr_t)controller == (uintptr_t)&__metal_dt_interrupt_controller_c000000) {
		return METAL_RISCV_PLIC0_C000000_BASE_ADDRESS;
	}
	else {
		return 0;
	}
}

static __inline__ unsigned long __metal_driver_sifive_plic0_control_size(struct metal_interrupt *controller)
{
	if ((uintptr_t)controller == (uintptr_t)&__metal_dt_interrupt_controller_c000000) {
		return METAL_RISCV_PLIC0_C000000_SIZE;
	}
	else {
		return 0;
	}
}

static __inline__ int __metal_driver_sifive_plic0_num_interrupts(struct metal_interrupt *controller)
{
	if ((uintptr_t)controller == (uintptr_t)&__metal_dt_interrupt_controller_c000000) {
		return METAL_RISCV_PLIC0_C000000_RISCV_NDEV;
	}
	else {
		return 0;
	}
}

static __inline__ int __metal_driver_sifive_plic0_max_priority(struct metal_interrupt *controller)
{
	if ((uintptr_t)controller == (uintptr_t)&__metal_dt_interrupt_controller_c000000) {
		return METAL_RISCV_PLIC0_C000000_RISCV_MAX_PRIORITY;
	}
	else {
		return 0;
	}
}

static __inline__ struct metal_interrupt * __metal_driver_sifive_plic0_interrupt_parents(struct metal_interrupt *controller, int idx)
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
	else {
		return NULL;
	}
}

static __inline__ int __metal_driver_sifive_plic0_interrupt_lines(struct metal_interrupt *controller, int idx)
{
	if (idx == 0) {
		return 11;
	}
	else if (idx == 1) {
		return 9;
	}
	else if (idx == 2) {
		return 11;
	}
	else if (idx == 3) {
		return 9;
	}
	else if (idx == 4) {
		return 11;
	}
	else if (idx == 5) {
		return 9;
	}
	else if (idx == 6) {
		return 11;
	}
	else if (idx == 7) {
		return 9;
	}
	else {
		return 0;
	}
}

static __inline__ int __metal_driver_sifive_plic0_context_ids(int hartid)
{
	if (hartid == 0) {
		return 0;
	}
	else if (hartid == 1) {
		return 2;
	}
	else if (hartid == 2) {
		return 4;
	}
	else if (hartid == 3) {
		return 6;
	}
	else {
		return -1;
	}
}



/* --------------------- sifive_buserror0 ------------ */
static __inline__ uintptr_t __metal_driver_sifive_buserror0_control_base(const struct metal_buserror *buserror)
{
	if ((uintptr_t)buserror == (uintptr_t)&__metal_dt_bus_error_unit_1700000) {
		return METAL_SIFIVE_BUSERROR0_1700000_BASE_ADDRESS;
	}
	else if ((uintptr_t)buserror == (uintptr_t)&__metal_dt_bus_error_unit_1701000) {
		return METAL_SIFIVE_BUSERROR0_1701000_BASE_ADDRESS;
	}
	else if ((uintptr_t)buserror == (uintptr_t)&__metal_dt_bus_error_unit_1702000) {
		return METAL_SIFIVE_BUSERROR0_1702000_BASE_ADDRESS;
	}
	else if ((uintptr_t)buserror == (uintptr_t)&__metal_dt_bus_error_unit_1703000) {
		return METAL_SIFIVE_BUSERROR0_1703000_BASE_ADDRESS;
	}
	else {
		return 0;
	}
}

static __inline__ struct metal_interrupt * __metal_driver_sifive_buserror0_interrupt_parent(const struct metal_buserror *buserror)
{
	if ((uintptr_t)buserror == (uintptr_t)&__metal_dt_bus_error_unit_1700000) {
		return (struct metal_interrupt *)&__metal_dt_interrupt_controller_c000000.controller;
	}
	else if ((uintptr_t)buserror == (uintptr_t)&__metal_dt_bus_error_unit_1701000) {
		return NULL;
	}
	else if ((uintptr_t)buserror == (uintptr_t)&__metal_dt_bus_error_unit_1702000) {
		return NULL;
	}
	else if ((uintptr_t)buserror == (uintptr_t)&__metal_dt_bus_error_unit_1703000) {
		return NULL;
	}
	else {
		return NULL;
	}
}

static __inline__ int __metal_driver_sifive_buserror0_interrupt_id(const struct metal_buserror *buserror)
{
	if ((uintptr_t)buserror == (uintptr_t)&__metal_dt_bus_error_unit_1700000) {
		return 134;
	}
	else if ((uintptr_t)buserror == (uintptr_t)&__metal_dt_bus_error_unit_1701000) {
		return 135;
	}
	else if ((uintptr_t)buserror == (uintptr_t)&__metal_dt_bus_error_unit_1702000) {
		return 136;
	}
	else if ((uintptr_t)buserror == (uintptr_t)&__metal_dt_bus_error_unit_1703000) {
		return 137;
	}
	else {
		return 0;
	}
}



/* --------------------- sifive_clic0 ------------ */


/* --------------------- sifive_local_external_interrupts0 ------------ */
static __inline__ struct metal_interrupt * __metal_driver_sifive_local_external_interrupts0_interrupt_parent(struct metal_interrupt *controller)
{
	if ((uintptr_t)controller == (uintptr_t)&__metal_dt_local_external_interrupts_0) {
		return (struct metal_interrupt *)&__metal_dt_cpu_0_interrupt_controller.controller;
	}
	else {
		return NULL;
	}
}

static __inline__ int __metal_driver_sifive_local_external_interrupts0_num_interrupts(struct metal_interrupt *controller)
{
	if ((uintptr_t)controller == (uintptr_t)&__metal_dt_local_external_interrupts_0) {
		return METAL_MAX_LOCAL_EXT_INTERRUPTS;
	}
	else {
		return 0;
	}
}

static __inline__ int __metal_driver_sifive_local_external_interrupts0_interrupt_lines(struct metal_interrupt *controller, int idx)
{
	if (idx == 0) {
		return 16;
	}
	else if (idx == 1) {
		return 17;
	}
	else if (idx == 2) {
		return 18;
	}
	else if (idx == 3) {
		return 19;
	}
	else if (idx == 4) {
		return 20;
	}
	else if (idx == 5) {
		return 21;
	}
	else if (idx == 6) {
		return 22;
	}
	else if (idx == 7) {
		return 23;
	}
	else if (idx == 8) {
		return 24;
	}
	else if (idx == 9) {
		return 25;
	}
	else if (idx == 10) {
		return 26;
	}
	else if (idx == 11) {
		return 27;
	}
	else if (idx == 12) {
		return 28;
	}
	else if (idx == 13) {
		return 29;
	}
	else if (idx == 14) {
		return 30;
	}
	else if (idx == 15) {
		return 31;
	}
	else if (idx == 0) {
		return 16;
	}
	else if (idx == 1) {
		return 17;
	}
	else if (idx == 2) {
		return 18;
	}
	else if (idx == 3) {
		return 19;
	}
	else if (idx == 4) {
		return 20;
	}
	else if (idx == 5) {
		return 21;
	}
	else if (idx == 6) {
		return 22;
	}
	else if (idx == 7) {
		return 23;
	}
	else if (idx == 8) {
		return 24;
	}
	else if (idx == 9) {
		return 25;
	}
	else if (idx == 10) {
		return 26;
	}
	else if (idx == 11) {
		return 27;
	}
	else if (idx == 12) {
		return 28;
	}
	else if (idx == 13) {
		return 29;
	}
	else if (idx == 14) {
		return 30;
	}
	else if (idx == 15) {
		return 31;
	}
	else if (idx == 0) {
		return 16;
	}
	else if (idx == 1) {
		return 17;
	}
	else if (idx == 2) {
		return 18;
	}
	else if (idx == 3) {
		return 19;
	}
	else if (idx == 4) {
		return 20;
	}
	else if (idx == 5) {
		return 21;
	}
	else if (idx == 6) {
		return 22;
	}
	else if (idx == 7) {
		return 23;
	}
	else if (idx == 8) {
		return 24;
	}
	else if (idx == 9) {
		return 25;
	}
	else if (idx == 10) {
		return 26;
	}
	else if (idx == 11) {
		return 27;
	}
	else if (idx == 12) {
		return 28;
	}
	else if (idx == 13) {
		return 29;
	}
	else if (idx == 14) {
		return 30;
	}
	else if (idx == 15) {
		return 31;
	}
	else if (idx == 0) {
		return 16;
	}
	else if (idx == 1) {
		return 17;
	}
	else if (idx == 2) {
		return 18;
	}
	else if (idx == 3) {
		return 19;
	}
	else if (idx == 4) {
		return 20;
	}
	else if (idx == 5) {
		return 21;
	}
	else if (idx == 6) {
		return 22;
	}
	else if (idx == 7) {
		return 23;
	}
	else if (idx == 8) {
		return 24;
	}
	else if (idx == 9) {
		return 25;
	}
	else if (idx == 10) {
		return 26;
	}
	else if (idx == 11) {
		return 27;
	}
	else if (idx == 12) {
		return 28;
	}
	else if (idx == 13) {
		return 29;
	}
	else if (idx == 14) {
		return 30;
	}
	else if (idx == 15) {
		return 31;
	}
	else {
		return 0;
	}
}



/* --------------------- sifive_global_external_interrupts0 ------------ */
static __inline__ int __metal_driver_sifive_global_external_interrupts0_init_done()
{
		return 0;
}

static __inline__ struct metal_interrupt * __metal_driver_sifive_global_external_interrupts0_interrupt_parent(struct metal_interrupt *controller)
{
	if ((uintptr_t)controller == (uintptr_t)&__metal_dt_global_external_interrupts) {
		return (struct metal_interrupt *)&__metal_dt_interrupt_controller_c000000.controller;
	}
	else {
		return NULL;
	}
}

static __inline__ int __metal_driver_sifive_global_external_interrupts0_num_interrupts(struct metal_interrupt *controller)
{
	if ((uintptr_t)controller == (uintptr_t)&__metal_dt_global_external_interrupts) {
		return METAL_MAX_GLOBAL_EXT_INTERRUPTS;
	}
	else {
		return 0;
	}
}

static __inline__ int __metal_driver_sifive_global_external_interrupts0_interrupt_lines(struct metal_interrupt *controller, int idx)
{
	if (idx == 0) {
		return 3;
	}
	else if (idx == 1) {
		return 4;
	}
	else if (idx == 2) {
		return 5;
	}
	else if (idx == 3) {
		return 6;
	}
	else if (idx == 4) {
		return 7;
	}
	else if (idx == 5) {
		return 8;
	}
	else if (idx == 6) {
		return 9;
	}
	else if (idx == 7) {
		return 10;
	}
	else if (idx == 8) {
		return 11;
	}
	else if (idx == 9) {
		return 12;
	}
	else if (idx == 10) {
		return 13;
	}
	else if (idx == 11) {
		return 14;
	}
	else if (idx == 12) {
		return 15;
	}
	else if (idx == 13) {
		return 16;
	}
	else if (idx == 14) {
		return 17;
	}
	else if (idx == 15) {
		return 18;
	}
	else if (idx == 16) {
		return 19;
	}
	else if (idx == 17) {
		return 20;
	}
	else if (idx == 18) {
		return 21;
	}
	else if (idx == 19) {
		return 22;
	}
	else if (idx == 20) {
		return 23;
	}
	else if (idx == 21) {
		return 24;
	}
	else if (idx == 22) {
		return 25;
	}
	else if (idx == 23) {
		return 26;
	}
	else if (idx == 24) {
		return 27;
	}
	else if (idx == 25) {
		return 28;
	}
	else if (idx == 26) {
		return 29;
	}
	else if (idx == 27) {
		return 30;
	}
	else if (idx == 28) {
		return 31;
	}
	else if (idx == 29) {
		return 32;
	}
	else if (idx == 30) {
		return 33;
	}
	else if (idx == 31) {
		return 34;
	}
	else if (idx == 32) {
		return 35;
	}
	else if (idx == 33) {
		return 36;
	}
	else if (idx == 34) {
		return 37;
	}
	else if (idx == 35) {
		return 38;
	}
	else if (idx == 36) {
		return 39;
	}
	else if (idx == 37) {
		return 40;
	}
	else if (idx == 38) {
		return 41;
	}
	else if (idx == 39) {
		return 42;
	}
	else if (idx == 40) {
		return 43;
	}
	else if (idx == 41) {
		return 44;
	}
	else if (idx == 42) {
		return 45;
	}
	else if (idx == 43) {
		return 46;
	}
	else if (idx == 44) {
		return 47;
	}
	else if (idx == 45) {
		return 48;
	}
	else if (idx == 46) {
		return 49;
	}
	else if (idx == 47) {
		return 50;
	}
	else if (idx == 48) {
		return 51;
	}
	else if (idx == 49) {
		return 52;
	}
	else if (idx == 50) {
		return 53;
	}
	else if (idx == 51) {
		return 54;
	}
	else if (idx == 52) {
		return 55;
	}
	else if (idx == 53) {
		return 56;
	}
	else if (idx == 54) {
		return 57;
	}
	else if (idx == 55) {
		return 58;
	}
	else if (idx == 56) {
		return 59;
	}
	else if (idx == 57) {
		return 60;
	}
	else if (idx == 58) {
		return 61;
	}
	else if (idx == 59) {
		return 62;
	}
	else if (idx == 60) {
		return 63;
	}
	else if (idx == 61) {
		return 64;
	}
	else if (idx == 62) {
		return 65;
	}
	else if (idx == 63) {
		return 66;
	}
	else if (idx == 64) {
		return 67;
	}
	else if (idx == 65) {
		return 68;
	}
	else if (idx == 66) {
		return 69;
	}
	else if (idx == 67) {
		return 70;
	}
	else if (idx == 68) {
		return 71;
	}
	else if (idx == 69) {
		return 72;
	}
	else if (idx == 70) {
		return 73;
	}
	else if (idx == 71) {
		return 74;
	}
	else if (idx == 72) {
		return 75;
	}
	else if (idx == 73) {
		return 76;
	}
	else if (idx == 74) {
		return 77;
	}
	else if (idx == 75) {
		return 78;
	}
	else if (idx == 76) {
		return 79;
	}
	else if (idx == 77) {
		return 80;
	}
	else if (idx == 78) {
		return 81;
	}
	else if (idx == 79) {
		return 82;
	}
	else if (idx == 80) {
		return 83;
	}
	else if (idx == 81) {
		return 84;
	}
	else if (idx == 82) {
		return 85;
	}
	else if (idx == 83) {
		return 86;
	}
	else if (idx == 84) {
		return 87;
	}
	else if (idx == 85) {
		return 88;
	}
	else if (idx == 86) {
		return 89;
	}
	else if (idx == 87) {
		return 90;
	}
	else if (idx == 88) {
		return 91;
	}
	else if (idx == 89) {
		return 92;
	}
	else if (idx == 90) {
		return 93;
	}
	else if (idx == 91) {
		return 94;
	}
	else if (idx == 92) {
		return 95;
	}
	else if (idx == 93) {
		return 96;
	}
	else if (idx == 94) {
		return 97;
	}
	else if (idx == 95) {
		return 98;
	}
	else if (idx == 96) {
		return 99;
	}
	else if (idx == 97) {
		return 100;
	}
	else if (idx == 98) {
		return 101;
	}
	else if (idx == 99) {
		return 102;
	}
	else if (idx == 100) {
		return 103;
	}
	else if (idx == 101) {
		return 104;
	}
	else if (idx == 102) {
		return 105;
	}
	else if (idx == 103) {
		return 106;
	}
	else if (idx == 104) {
		return 107;
	}
	else if (idx == 105) {
		return 108;
	}
	else if (idx == 106) {
		return 109;
	}
	else if (idx == 107) {
		return 110;
	}
	else if (idx == 108) {
		return 111;
	}
	else if (idx == 109) {
		return 112;
	}
	else if (idx == 110) {
		return 113;
	}
	else if (idx == 111) {
		return 114;
	}
	else if (idx == 112) {
		return 115;
	}
	else if (idx == 113) {
		return 116;
	}
	else if (idx == 114) {
		return 117;
	}
	else if (idx == 115) {
		return 118;
	}
	else if (idx == 116) {
		return 119;
	}
	else if (idx == 117) {
		return 120;
	}
	else if (idx == 118) {
		return 121;
	}
	else if (idx == 119) {
		return 122;
	}
	else if (idx == 120) {
		return 123;
	}
	else if (idx == 121) {
		return 124;
	}
	else if (idx == 122) {
		return 125;
	}
	else if (idx == 123) {
		return 126;
	}
	else if (idx == 124) {
		return 127;
	}
	else if (idx == 125) {
		return 128;
	}
	else if (idx == 126) {
		return 129;
	}
	else {
		return 0;
	}
}



/* --------------------- sifive_gpio0 ------------ */


/* --------------------- sifive_gpio_button ------------ */


/* --------------------- sifive_gpio_led ------------ */


/* --------------------- sifive_gpio_switch ------------ */


/* --------------------- sifive_i2c0 ------------ */


/* --------------------- sifive_pwm0 ------------ */


/* --------------------- sifive_rtc0 ------------ */



/* --------------------- sifive_test0 ------------ */
static __inline__ unsigned long __metal_driver_sifive_test0_base(const struct __metal_shutdown *sd)
{
	if ((uintptr_t)sd == (uintptr_t)&__metal_dt_teststatus_4000) {
		return METAL_SIFIVE_TEST0_4000_BASE_ADDRESS;
	}
	else {
		return 0;
	}
}

static __inline__ unsigned long __metal_driver_sifive_test0_size(const struct __metal_shutdown *sd)
{
	if ((uintptr_t)sd == (uintptr_t)&__metal_dt_teststatus_4000) {
		return METAL_SIFIVE_TEST0_4000_SIZE;
	}
	else {
		return 0;
	}
}



/* --------------------- sifive_trace ------------ */
static __inline__ unsigned long __metal_driver_sifive_trace_base(const struct metal_uart *uart)
{
	if ((uintptr_t)uart == (uintptr_t)&__metal_dt_trace_encoder_0_10000000) {
		return METAL_SIFIVE_TRACE_10000000_BASE_ADDRESS;
	}
	else if ((uintptr_t)uart == (uintptr_t)&__metal_dt_trace_encoder_1_10001000) {
		return METAL_SIFIVE_TRACE_10001000_BASE_ADDRESS;
	}
	else if ((uintptr_t)uart == (uintptr_t)&__metal_dt_trace_encoder_2_10002000) {
		return METAL_SIFIVE_TRACE_10002000_BASE_ADDRESS;
	}
	else if ((uintptr_t)uart == (uintptr_t)&__metal_dt_trace_encoder_3_10003000) {
		return METAL_SIFIVE_TRACE_10003000_BASE_ADDRESS;
	}
	else if ((uintptr_t)uart == (uintptr_t)&__metal_dt_trace_funnel_10008000) {
		return METAL_SIFIVE_TRACE_10008000_BASE_ADDRESS;
	}
	else {
		return 0;
	}
}

static __inline__ unsigned long __metal_driver_sifive_trace_size(const struct metal_uart *uart)
{
	if ((uintptr_t)uart == (uintptr_t)&__metal_dt_trace_encoder_0_10000000) {
		return METAL_SIFIVE_TRACE_10000000_SIZE;
	}
	else if ((uintptr_t)uart == (uintptr_t)&__metal_dt_trace_encoder_1_10001000) {
		return METAL_SIFIVE_TRACE_10001000_SIZE;
	}
	else if ((uintptr_t)uart == (uintptr_t)&__metal_dt_trace_encoder_2_10002000) {
		return METAL_SIFIVE_TRACE_10002000_SIZE;
	}
	else if ((uintptr_t)uart == (uintptr_t)&__metal_dt_trace_encoder_3_10003000) {
		return METAL_SIFIVE_TRACE_10003000_SIZE;
	}
	else if ((uintptr_t)uart == (uintptr_t)&__metal_dt_trace_funnel_10008000) {
		return METAL_SIFIVE_TRACE_10008000_SIZE;
	}
	else {
		return 0;
	}
}


/* --------------------- sifive_nb2emmc ------------ */
static __inline__ unsigned long long __metal_driver_sifive_nb2emmc_base(struct metal_emmc *emmc)
{
	if ((uintptr_t)emmc == (uintptr_t)&__metal_dt_nb2emmc_301007000) {
		return METAL_SIFIVE_NB2EMMC_301007000_BASE_ADDRESS;
	}
	else {
		return 0;
	}
}

static __inline__ unsigned long long __metal_driver_sifive_nb2emmc_size(struct metal_emmc *emmc)
{
	if ((uintptr_t)emmc == (uintptr_t)&__metal_dt_nb2emmc_301007000) {
		return METAL_SIFIVE_NB2EMMC_301007000_SIZE;
	}
	else {
		return 0;
	}
}

static __inline__ int __metal_driver_sifive_nb2emmc_num_interrupts(struct metal_emmc *emmc)
{
	if ((uintptr_t)emmc == (uintptr_t)&__metal_dt_nb2emmc_301007000) {
		return METAL_MAX_EMMC_INTERRUPTS;
	}
	else {
		return 0;
	}
}

static __inline__ struct metal_interrupt * __metal_driver_sifive_nb2emmc_interrupt_parent(struct metal_emmc *emmc)
{
	if ((uintptr_t)emmc == (uintptr_t)&__metal_dt_nb2emmc_301007000) {
		return (struct metal_interrupt *)&__metal_dt_interrupt_controller_c000000.controller;
	}
	else {
		return 0;
	}
}

static __inline__ int __metal_driver_sifive_nb2emmc_interrupt_lines(struct metal_emmc *emmc, int idx)
{
	if (((uintptr_t)emmc == (uintptr_t)&__metal_dt_nb2emmc_301007000) && (idx == 0)) {
		return 45;
	}
	else if ((((uintptr_t)emmc == (uintptr_t)&__metal_dt_nb2emmc_301007000) && (idx == 1))) {
		return 46;
	}
	else {
		return 0;
	}
}


static __inline__ unsigned long long __metal_driver_sifive_nb2qspi0_control_base(struct metal_qspi *qspi)
{
	if ((uintptr_t)qspi == (uintptr_t)&__metal_dt_nb2qspi0_261010000) {
		return METAL_SIFIVE_NB2QSPI0_261010000_BASE_ADDRESS;
	}
	else {
		return 0;
	}
}

static __inline__ unsigned long long __metal_driver_sifive_nb2qspi0_control_size(struct metal_qspi *qspi)
{
	if ((uintptr_t)qspi == (uintptr_t)&__metal_dt_nb2qspi0_261010000) {
		return METAL_SIFIVE_NB2QSPI0_261010000_SIZE;
	}
	else {
		return 0;
	}
}

static __inline__ struct metal_clock * __metal_driver_sifive_nb2qspi0_clock(struct metal_qspi *qspi)
{
	if ((uintptr_t)qspi == (uintptr_t)&__metal_dt_nb2qspi0_261010000) {
		return (struct metal_clock *)&__metal_dt_subsystem_pbus_clock.clock;
	}
	else {
		return 0;
	}
}

static __inline__ struct __metal_driver_sifive_nb2gpio0 * __metal_driver_sifive_nb2qspi0_pinmux(struct metal_qspi *qspi)
{
	if ((uintptr_t)qspi == (uintptr_t)&__metal_dt_nb2qspi0_261010000) {
		return NULL;
	}
	else {
		return 0;
	}
}

static __inline__ unsigned long __metal_driver_sifive_nb2qspi0_pinmux_output_selector(struct metal_qspi *qspi)
{
	if ((uintptr_t)qspi == (uintptr_t)&__metal_dt_nb2qspi0_261010000) {
		return 0;
	}
	else {
		return 0;
	}
}

static __inline__ unsigned long __metal_driver_sifive_nb2qspi0_pinmux_source_selector(struct metal_qspi *qspi)
{
	if ((uintptr_t)qspi == (uintptr_t)&__metal_dt_nb2qspi0_261010000) {
		return 0;
	}
	else {
		return 0;
	}
}



/* --------------------- sifive_nb2uart0 ------------ */
static __inline__ unsigned long long __metal_driver_sifive_nb2uart0_control_base(struct metal_uart *uart)
{
	if ((uintptr_t)uart == (uintptr_t)&__metal_dt_nb2uart0_302011000) {
		return METAL_SIFIVE_NB2UART0_302011000_BASE_ADDRESS;
	}
	else if ((uintptr_t)uart == (uintptr_t)&__metal_dt_nb2uart0_302012000) {
		return METAL_SIFIVE_NB2UART0_302012000_BASE_ADDRESS;
	}
	else {
		return 0;
	}
}

static __inline__ unsigned long long __metal_driver_sifive_nb2uart0_control_size(struct metal_uart *uart)
{
	if ((uintptr_t)uart == (uintptr_t)&__metal_dt_nb2uart0_302011000) {
		return METAL_SIFIVE_NB2UART0_302011000_SIZE;
	}
	else if ((uintptr_t)uart == (uintptr_t)&__metal_dt_nb2uart0_302012000) {
		return METAL_SIFIVE_NB2UART0_302012000_SIZE;
	}
	else {
		return 0;
	}
}

static __inline__ int __metal_driver_sifive_nb2uart0_num_interrupts(struct metal_uart *uart)
{
	if ((uintptr_t)uart == (uintptr_t)&__metal_dt_nb2uart0_302011000) {
		return METAL_MAX_UART_INTERRUPTS;
	}
	else if ((uintptr_t)uart == (uintptr_t)&__metal_dt_nb2uart0_302012000) {
		return METAL_MAX_UART_INTERRUPTS;
	}
	else {
		return 0;
	}
}

static __inline__ struct metal_interrupt * __metal_driver_sifive_nb2uart0_interrupt_parent(struct metal_uart *uart)
{
	if ((uintptr_t)uart == (uintptr_t)&__metal_dt_nb2uart0_302011000) {
		return (struct metal_interrupt *)&__metal_dt_interrupt_controller_c000000.controller;
	}
	else if ((uintptr_t)uart == (uintptr_t)&__metal_dt_nb2uart0_302012000) {
		return NULL;
	}
	else {
		return 0;
	}
}

static __inline__ int __metal_driver_sifive_nb2uart0_interrupt_line(struct metal_uart *uart)
{
	if ((uintptr_t)uart == (uintptr_t)&__metal_dt_nb2uart0_302011000) {
		return 64;
	}
	else if ((uintptr_t)uart == (uintptr_t)&__metal_dt_nb2uart0_302012000) {
		return 65;
	}
	else {
		return 0;
	}
}

static __inline__ struct metal_clock * __metal_driver_sifive_nb2uart0_clock(struct metal_uart *uart)
{
	if ((uintptr_t)uart == (uintptr_t)&__metal_dt_nb2uart0_302011000) {
		return (struct metal_clock *)&__metal_dt_subsystem_pbus_clock.clock;
	}
	else if ((uintptr_t)uart == (uintptr_t)&__metal_dt_nb2uart0_302012000) {
		return (struct metal_clock *)&__metal_dt_subsystem_pbus_clock.clock;
	}
	else {
		return 0;
	}
}

static __inline__ struct __metal_driver_sifive_nb2gpio0 * __metal_driver_sifive_nb2uart0_pinmux(struct metal_uart *uart)
{
	if ((uintptr_t)uart == (uintptr_t)&__metal_dt_nb2uart0_302011000) {
		return NULL;
	}
	else if ((uintptr_t)uart == (uintptr_t)&__metal_dt_nb2uart0_302012000) {
		return NULL;
	}
	else {
		return 0;
	}
}

static __inline__ unsigned long __metal_driver_sifive_nb2uart0_pinmux_output_selector(struct metal_uart *uart)
{
	if ((uintptr_t)uart == (uintptr_t)&__metal_dt_nb2uart0_302011000) {
		return 0;
	}
	else if ((uintptr_t)uart == (uintptr_t)&__metal_dt_nb2uart0_302012000) {
		return 0;
	}
	else {
		return 0;
	}
}

static __inline__ unsigned long __metal_driver_sifive_nb2uart0_pinmux_source_selector(struct metal_uart *uart)
{
	if ((uintptr_t)uart == (uintptr_t)&__metal_dt_nb2uart0_302011000) {
		return 0;
	}
	else if ((uintptr_t)uart == (uintptr_t)&__metal_dt_nb2uart0_302012000) {
		return 0;
	}
	else {
		return 0;
	}
}



/* --------------------- sifive_nb2wdt ------------ */
static __inline__ unsigned long long __metal_driver_sifive_nb2wdt_control_base(const struct metal_watchdog *const watchdog)
{
	if ((uintptr_t)watchdog == (uintptr_t)&__metal_dt_nb2wdt_302058000) {
		return METAL_SIFIVE_NB2WDT_302058000_BASE_ADDRESS;
	}
	else {
		return 0;
	}
}

static __inline__ unsigned long long __metal_driver_sifive_nb2wdt_control_size(const struct metal_watchdog *const watchdog)
{
	if ((uintptr_t)watchdog == (uintptr_t)&__metal_dt_nb2wdt_302058000) {
		return METAL_SIFIVE_NB2WDT_302058000_SIZE;
	}
	else {
		return 0;
	}
}

static __inline__ struct metal_interrupt * __metal_driver_sifive_nb2wdt_interrupt_parent(const struct metal_watchdog *const watchdog)
{
	if ((uintptr_t)watchdog == (uintptr_t)&__metal_dt_nb2wdt_302058000) {
		return (struct metal_interrupt *)&__metal_dt_interrupt_controller_c000000.controller;
	}
	else {
		return 0;
	}
}

static __inline__ int __metal_driver_sifive_nb2wdt_interrupt_line(const struct metal_watchdog *const watchdog)
{
	if ((uintptr_t)watchdog == (uintptr_t)&__metal_dt_nb2wdt_302058000) {
		return 4;
	}
	else {
		return 0;
	}
}

static __inline__ struct metal_clock * __metal_driver_sifive_nb2wdt_clock(const struct metal_watchdog *const watchdog)
{
	if ((uintptr_t)watchdog == (uintptr_t)&__metal_dt_nb2wdt_302058000) {
		return (struct metal_clock *)&__metal_dt_subsystem_pbus_clock.clock;
	}
	else {
		return 0;
	}
}



/* --------------------- sifive_fe310_g000_hfrosc ------------ */


/* --------------------- sifive_fe310_g000_hfxosc ------------ */


/* --------------------- sifive_fe310_g000_lfrosc ------------ */


/* --------------------- sifive_fe310_g000_pll ------------ */


/* --------------------- sifive_fe310_g000_prci ------------ */


#define __METAL_DT_MAX_MEMORIES 1

__asm__ (".weak __metal_memory_table");
struct metal_memory *__metal_memory_table[] = {
					&__metal_dt_mem_memory_800000000};

/* From nb2uart0@302011000 */
#define __METAL_DT_STDOUT_UART_HANDLE (&__metal_dt_nb2uart0_302011000.uart)

#define __METAL_DT_NB2UART0_302011000_HANDLE (&__metal_dt_nb2uart0_302011000.uart)

#define __METAL_DT_STDOUT_UART_BAUD 9600

/* From clint@2000000 */
#define __METAL_DT_RISCV_CLINT0_HANDLE (&__metal_dt_clint_2000000.controller)

#define __METAL_DT_CLINT_2000000_HANDLE (&__metal_dt_clint_2000000.controller)

#define __METAL_DT_MAX_HARTS 4

#define __METAL_CPU_0_ICACHE_HANDLE 1

#define __METAL_CPU_0_DCACHE_HANDLE 1

#define __METAL_CPU_1_ICACHE_HANDLE 1

#define __METAL_CPU_1_DCACHE_HANDLE 1

#define __METAL_CPU_2_ICACHE_HANDLE 1

#define __METAL_CPU_2_DCACHE_HANDLE 1

#define __METAL_CPU_3_ICACHE_HANDLE 1

#define __METAL_CPU_3_DCACHE_HANDLE 1

__asm__ (".weak __metal_cpu_table");
struct __metal_driver_cpu *__metal_cpu_table[] = {
					&__metal_dt_cpu_0,
					&__metal_dt_cpu_1,
					&__metal_dt_cpu_2,
					&__metal_dt_cpu_3};

/* From interrupt_controller@c000000 */
#define __METAL_DT_RISCV_PLIC0_HANDLE (&__metal_dt_interrupt_controller_c000000.controller)

#define __METAL_DT_INTERRUPT_CONTROLLER_C000000_HANDLE (&__metal_dt_interrupt_controller_c000000.controller)

#define __METAL_DT_PMP_HANDLE (&__metal_dt_pmp)

/* From global_external_interrupts */
#define __METAL_DT_SIFIVE_GLOBAL_EXINTR0_HANDLE (&__metal_dt_global_external_interrupts.irc)

#define __METAL_DT_GLOBAL_EXTERNAL_INTERRUPTS_HANDLE (&__metal_dt_global_external_interrupts.irc)

#define __MEE_DT_MAX_GPIOS 0

__asm__ (".weak __metal_gpio_table");
struct __metal_driver_sifive_gpio0 *__metal_gpio_table[] = {
					NULL };
#define __METAL_DT_MAX_BUTTONS 0

__asm__ (".weak __metal_button_table");
struct __metal_driver_sifive_gpio_button *__metal_button_table[] = {
					NULL };
#define __METAL_DT_MAX_LEDS 0

__asm__ (".weak __metal_led_table");
struct __metal_driver_sifive_gpio_led *__metal_led_table[] = {
					NULL };
#define __METAL_DT_MAX_SWITCHES 0

__asm__ (".weak __metal_switch_table");
struct __metal_driver_sifive_gpio_switch *__metal_switch_table[] = {
					NULL };
#define __METAL_DT_MAX_I2CS 0

__asm__ (".weak __metal_i2c_table");
struct __metal_driver_sifive_i2c0 *__metal_i2c_table[] = {
					NULL };
#define __METAL_DT_MAX_PWMS 0

__asm__ (".weak __metal_pwm_table");
struct __metal_driver_sifive_pwm0 *__metal_pwm_table[] = {
					NULL };
#define __METAL_DT_MAX_RTCS 0

__asm__ (".weak __metal_rtc_table");
struct __metal_driver_sifive_rtc0 *__metal_rtc_table[] = {
					NULL };
#define __METAL_DT_MAX_SPIS 0

__asm__ (".weak __metal_spi_table");
struct __metal_driver_sifive_spi0 *__metal_spi_table[] = {
					NULL };
/* From teststatus@4000 */
#define __METAL_DT_SHUTDOWN_HANDLE (&__metal_dt_teststatus_4000.shutdown)

#define __METAL_DT_TESTSTATUS_4000_HANDLE (&__metal_dt_teststatus_4000.shutdown)

#define __METAL_DT_MAX_EMMC 1

__asm__ (".weak __metal_emmc_table");
struct __metal_driver_sifive_nb2emmc *__metal_emmc_table[] = {
					&__metal_dt_nb2emmc_301007000};

#define __METAL_DT_MAX_FLASH 1

__asm__ (".weak __metal_flash_table");
struct __metal_driver_sifive_flash *__metal_flash_table[] = {
					&__metal_dt_flash};

#define __METAL_DT_MAX_QSPIS 1

__asm__ (".weak __metal_qspi_table");
struct __metal_driver_sifive_nb2qspi0 *__metal_qspi_table[] = {
					&__metal_dt_nb2qspi0_261010000};

#define __METAL_DT_MAX_UARTS 2

__asm__ (".weak __metal_uart_table");
struct __metal_driver_sifive_nb2uart0 *__metal_uart_table[] = {
					&__metal_dt_nb2uart0_302011000,
					&__metal_dt_nb2uart0_302012000};

#define __METAL_DT_MAX_WDOGS 1

__asm__ (".weak __metal_wdog_table");
struct __metal_driver_sifive_nb2wdt *__metal_wdog_table[] = {
					&__metal_dt_nb2wdt_302058000};

#endif /* MACROS_ELSE_METAL_H*/

#endif /* ! __METAL_MACHINE_MACROS */

#endif /* ! ASSEMBLY */
