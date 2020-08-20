/* Copyright 2019 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */
/* ----------------------------------- */
/* ----------------------------------- */

#ifndef ASSEMBLY

#include <metal/machine/platform.h>

#ifdef __METAL_MACHINE_MACROS

#ifndef MACROS_IF_METAL_H
#define MACROS_IF_METAL_H

#define __METAL_CLINT_NUM_PARENTS 10

#ifndef __METAL_CLINT_NUM_PARENTS
#define __METAL_CLINT_NUM_PARENTS 0
#endif
#define __METAL_PLIC_SUBINTERRUPTS 54

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

#endif /* MACROS_IF_METAL_H*/

#else /* ! __METAL_MACHINE_MACROS */

#ifndef MACROS_ELSE_METAL_H
#define MACROS_ELSE_METAL_H

#define __METAL_CLINT_2000000_INTERRUPTS 10

#define METAL_MAX_CLINT_INTERRUPTS 10

#define __METAL_CLINT_NUM_PARENTS 10

#define __METAL_INTERRUPT_CONTROLLER_C000000_INTERRUPTS 9

#define __METAL_PLIC_SUBINTERRUPTS 54

#define METAL_MAX_PLIC_INTERRUPTS 9

#define __METAL_PLIC_NUM_PARENTS 9

#define METAL_SIFIVE_CCACHE0_INTERRUPTS { 1, 2, 3, }

#define METAL_SIFIVE_CCACHE0_INTERRUPT_PARENT &__metal_dt_interrupt_controller_c000000.controller

#define METAL_CACHE_DRIVER_PREFIX sifive_ccache0

#define METAL_SIFIVE_CCACHE0_PERFMON_COUNTERS 0

#define __METAL_DT_SIFIVE_CCACHE0_HANDLE (struct metal_cache *)NULL

#define __METAL_CLIC_SUBINTERRUPTS 0
#define METAL_MAX_CLIC_INTERRUPTS 0

#define METAL_MAX_LOCAL_EXT_INTERRUPTS 0

#define METAL_MAX_GLOBAL_EXT_INTERRUPTS 0

#define __METAL_GPIO_10060000_INTERRUPTS 16

#define METAL_MAX_GPIO_INTERRUPTS 16

#define __METAL_I2C_10030000_INTERRUPTS 0

#define METAL_MAX_I2C0_INTERRUPTS 0

#define __METAL_PWM_10020000_INTERRUPTS 4

#define __METAL_PWM_10021000_INTERRUPTS 4

#define METAL_MAX_PWM0_INTERRUPTS 4

#define METAL_MAX_PWM0_NCMP 4

#define __METAL_SERIAL_10010000_INTERRUPTS 1

#define __METAL_SERIAL_10011000_INTERRUPTS 1

#define METAL_MAX_UART_INTERRUPTS 1

#define METAL_MAX_SIMUART_INTERRUPTS 0


#include <metal/drivers/fixed-clock.h>
#include <metal/drivers/fixed-factor-clock.h>
#include <metal/memory.h>
#include <metal/drivers/riscv_clint0.h>
#include <metal/drivers/riscv_cpu.h>
#include <metal/drivers/riscv_plic0.h>
#include <metal/pmp.h>
#include <metal/drivers/sifive_ccache0.h>
#include <metal/drivers/sifive_gpio0.h>
#include <metal/drivers/sifive_i2c0.h>
#include <metal/drivers/sifive_pwm0.h>
#include <metal/drivers/sifive_spi0.h>
#include <metal/drivers/sifive_test0.h>
#include <metal/drivers/sifive_uart0.h>

/* From refclk */
extern struct __metal_driver_fixed_clock __metal_dt_refclk;

/* From tlclk */
extern struct __metal_driver_fixed_factor_clock __metal_dt_tlclk;

extern struct metal_memory __metal_dt_mem_dtim_1000000;

extern struct metal_memory __metal_dt_mem_itim_1800000;

extern struct metal_memory __metal_dt_mem_itim_1808000;

extern struct metal_memory __metal_dt_mem_itim_1810000;

extern struct metal_memory __metal_dt_mem_itim_1818000;

extern struct metal_memory __metal_dt_mem_itim_1820000;

extern struct metal_memory __metal_dt_mem_memory_80000000;

extern struct metal_memory __metal_dt_mem_spi_10040000;

extern struct metal_memory __metal_dt_mem_spi_10041000;

extern struct metal_memory __metal_dt_mem_spi_10050000;

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

/* From cpu@4 */
extern struct __metal_driver_cpu __metal_dt_cpu_4;

extern struct __metal_driver_riscv_cpu_intc __metal_dt_cpu_0_interrupt_controller;

extern struct __metal_driver_riscv_cpu_intc __metal_dt_cpu_1_interrupt_controller;

extern struct __metal_driver_riscv_cpu_intc __metal_dt_cpu_2_interrupt_controller;

extern struct __metal_driver_riscv_cpu_intc __metal_dt_cpu_3_interrupt_controller;

extern struct __metal_driver_riscv_cpu_intc __metal_dt_cpu_4_interrupt_controller;

/* From interrupt_controller@c000000 */
extern struct __metal_driver_riscv_plic0 __metal_dt_interrupt_controller_c000000;

extern struct metal_pmp __metal_dt_pmp;

/* From gpio@10060000 */
extern struct __metal_driver_sifive_gpio0 __metal_dt_gpio_10060000;

/* From i2c@10030000 */
extern struct __metal_driver_sifive_i2c0 __metal_dt_i2c_10030000;

/* From pwm@10020000 */
extern struct __metal_driver_sifive_pwm0 __metal_dt_pwm_10020000;

/* From pwm@10021000 */
extern struct __metal_driver_sifive_pwm0 __metal_dt_pwm_10021000;

/* From spi@10040000 */
extern struct __metal_driver_sifive_spi0 __metal_dt_spi_10040000;

/* From spi@10041000 */
extern struct __metal_driver_sifive_spi0 __metal_dt_spi_10041000;

/* From spi@10050000 */
extern struct __metal_driver_sifive_spi0 __metal_dt_spi_10050000;

/* From teststatus@4000 */
extern struct __metal_driver_sifive_test0 __metal_dt_teststatus_4000;

/* From serial@10010000 */
extern struct __metal_driver_sifive_uart0 __metal_dt_serial_10010000;

/* From serial@10011000 */
extern struct __metal_driver_sifive_uart0 __metal_dt_serial_10011000;



/* --------------------- fixed_clock ------------ */
static __inline__ unsigned long __metal_driver_fixed_clock_rate(const struct metal_clock *clock)
{
	if ((uintptr_t)clock == (uintptr_t)&__metal_dt_refclk) {
		return METAL_FIXED_CLOCK__CLOCK_FREQUENCY;
	}
	else {
		return 0;
	}
}



/* --------------------- fixed_factor_clock ------------ */
static __inline__ struct metal_clock * __metal_driver_fixed_factor_clock_parent(const struct metal_clock *clock)
{
	if ((uintptr_t)clock == (uintptr_t)&__metal_dt_tlclk) {
		return (struct metal_clock *)&__metal_dt_refclk.clock;
	}
	else {
		return NULL;
	}
}

static __inline__ unsigned long __metal_driver_fixed_factor_clock_mult(const struct metal_clock *clock)
{
	if ((uintptr_t)clock == (uintptr_t)&__metal_dt_tlclk) {
		return METAL_FIXED_FACTOR_CLOCK__CLOCK_MULT;
	}
	else {
		return 0;
	}
}

static __inline__ unsigned long __metal_driver_fixed_factor_clock_div(const struct metal_clock *clock)
{
	if ((uintptr_t)clock == (uintptr_t)&__metal_dt_tlclk) {
		return METAL_FIXED_FACTOR_CLOCK__CLOCK_DIV;
	}
	else {
		return 0;
	}
}



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
	else if ((uintptr_t)cpu == (uintptr_t)&__metal_dt_cpu_4) {
		return 4;
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
	else if ((uintptr_t)cpu == (uintptr_t)&__metal_dt_cpu_4) {
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
	else if ((uintptr_t)cpu == (uintptr_t)&__metal_dt_cpu_4) {
		return &__metal_dt_cpu_4_interrupt_controller.controller;
	}
	else {
		return NULL;
	}
}

static __inline__ int __metal_driver_cpu_num_pmp_regions(struct metal_cpu *cpu)
{
	if ((uintptr_t)cpu == (uintptr_t)&__metal_dt_cpu_0) {
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
	else if ((uintptr_t)cpu == (uintptr_t)&__metal_dt_cpu_4) {
		return 8;
	}
	else {
		return 0;
	}
}

static __inline__ struct metal_buserror * __metal_driver_cpu_buserror(struct metal_cpu *cpu)
{
	if ((uintptr_t)cpu == (uintptr_t)&__metal_dt_cpu_0) {
		return NULL;
	}
	else if ((uintptr_t)cpu == (uintptr_t)&__metal_dt_cpu_1) {
		return NULL;
	}
	else if ((uintptr_t)cpu == (uintptr_t)&__metal_dt_cpu_2) {
		return NULL;
	}
	else if ((uintptr_t)cpu == (uintptr_t)&__metal_dt_cpu_3) {
		return NULL;
	}
	else if ((uintptr_t)cpu == (uintptr_t)&__metal_dt_cpu_4) {
		return NULL;
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

static __inline__ int __metal_driver_sifive_plic0_interrupt_lines(struct metal_interrupt *controller, int idx)
{
	if (idx == 0) {
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

static __inline__ int __metal_driver_sifive_plic0_context_ids(int hartid)
{
	if (hartid == 0) {
		return 0;
	}
	else if (hartid == 1) {
		return 1;
	}
	else if (hartid == 2) {
		return 3;
	}
	else if (hartid == 3) {
		return 5;
	}
	else if (hartid == 4) {
		return 7;
	}
	else {
		return -1;
	}
}



/* --------------------- sifive_buserror0 ------------ */


/* --------------------- sifive_clic0 ------------ */


/* --------------------- sifive_local_external_interrupts0 ------------ */


/* --------------------- sifive_global_external_interrupts0 ------------ */


/* --------------------- sifive_gpio0 ------------ */
static __inline__ unsigned long __metal_driver_sifive_gpio0_base(struct metal_gpio *gpio)
{
	if ((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_10060000) {
		return METAL_SIFIVE_GPIO0_10060000_BASE_ADDRESS;
	}
	else {
		return 0;
	}
}

static __inline__ unsigned long __metal_driver_sifive_gpio0_size(struct metal_gpio *gpio)
{
	if ((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_10060000) {
		return METAL_SIFIVE_GPIO0_10060000_SIZE;
	}
	else {
		return 0;
	}
}

static __inline__ int __metal_driver_sifive_gpio0_num_interrupts(struct metal_gpio *gpio)
{
	if ((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_10060000) {
		return METAL_MAX_GPIO_INTERRUPTS;
	}
	else {
		return 0;
	}
}

static __inline__ struct metal_interrupt * __metal_driver_sifive_gpio0_interrupt_parent(struct metal_gpio *gpio)
{
	if ((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_10060000) {
		return (struct metal_interrupt *)&__metal_dt_interrupt_controller_c000000.controller;
	}
	else {
		return 0;
	}
}

static __inline__ int __metal_driver_sifive_gpio0_interrupt_lines(struct metal_gpio *gpio, int idx)
{
	if (((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_10060000) && (idx == 0)) {
		return 7;
	}
	else if ((((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_10060000) && (idx == 1))) {
		return 8;
	}
	else if ((((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_10060000) && (idx == 2))) {
		return 9;
	}
	else if ((((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_10060000) && (idx == 3))) {
		return 10;
	}
	else if ((((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_10060000) && (idx == 4))) {
		return 11;
	}
	else if ((((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_10060000) && (idx == 5))) {
		return 12;
	}
	else if ((((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_10060000) && (idx == 6))) {
		return 13;
	}
	else if ((((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_10060000) && (idx == 7))) {
		return 14;
	}
	else if ((((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_10060000) && (idx == 8))) {
		return 15;
	}
	else if ((((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_10060000) && (idx == 9))) {
		return 16;
	}
	else if ((((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_10060000) && (idx == 10))) {
		return 17;
	}
	else if ((((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_10060000) && (idx == 11))) {
		return 18;
	}
	else if ((((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_10060000) && (idx == 12))) {
		return 19;
	}
	else if ((((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_10060000) && (idx == 13))) {
		return 20;
	}
	else if ((((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_10060000) && (idx == 14))) {
		return 21;
	}
	else if ((((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_10060000) && (idx == 15))) {
		return 22;
	}
	else {
		return 0;
	}
}



/* --------------------- sifive_gpio_button ------------ */


/* --------------------- sifive_gpio_led ------------ */


/* --------------------- sifive_gpio_switch ------------ */


/* --------------------- sifive_i2c0 ------------ */
static __inline__ unsigned long __metal_driver_sifive_i2c0_control_base(struct metal_i2c *i2c)
{
	if ((uintptr_t)i2c == (uintptr_t)&__metal_dt_i2c_10030000) {
		return METAL_SIFIVE_I2C0_10030000_BASE_ADDRESS;
	}
	else {
		return 0;
	}
}

static __inline__ unsigned long __metal_driver_sifive_i2c0_control_size(struct metal_i2c *i2c)
{
	if ((uintptr_t)i2c == (uintptr_t)&__metal_dt_i2c_10030000) {
		return METAL_SIFIVE_I2C0_10030000_SIZE;
	}
	else {
		return 0;
	}
}

static __inline__ struct metal_clock * __metal_driver_sifive_i2c0_clock(struct metal_i2c *i2c)
{
	if ((uintptr_t)i2c == (uintptr_t)&__metal_dt_i2c_10030000) {
		return (struct metal_clock *)&__metal_dt_tlclk.clock;
	}
	else {
		return NULL;
	}
}

static __inline__ struct __metal_driver_sifive_gpio0 * __metal_driver_sifive_i2c0_pinmux(struct metal_i2c *i2c)
{
	if ((uintptr_t)i2c == (uintptr_t)&__metal_dt_i2c_10030000) {
		return NULL;
	}
	else {
		return NULL;
	}
}

static __inline__ unsigned long __metal_driver_sifive_i2c0_pinmux_output_selector(struct metal_i2c *i2c)
{
	if ((uintptr_t)i2c == (uintptr_t)&__metal_dt_i2c_10030000) {
		return 0;
	}
	else {
		return 0;
	}
}

static __inline__ unsigned long __metal_driver_sifive_i2c0_pinmux_source_selector(struct metal_i2c *i2c)
{
	if ((uintptr_t)i2c == (uintptr_t)&__metal_dt_i2c_10030000) {
		return 0;
	}
	else {
		return 0;
	}
}

static __inline__ int __metal_driver_sifive_i2c0_num_interrupts(struct metal_i2c *i2c)
{
		return METAL_MAX_I2C0_INTERRUPTS;
}

static __inline__ struct metal_interrupt * __metal_driver_sifive_i2c0_interrupt_parent(struct metal_i2c *i2c)
{
		return NULL;
}

static __inline__ int __metal_driver_sifive_i2c0_interrupt_line(struct metal_i2c *i2c)
{
	if ((uintptr_t)i2c == (uintptr_t)&__metal_dt_i2c_10030000) {
		return 0;
	}
	else {
		return 0;
	}
}



/* --------------------- sifive_pwm0 ------------ */
static __inline__ unsigned long __metal_driver_sifive_pwm0_control_base(struct metal_pwm *pwm)
{
	if ((uintptr_t)pwm == (uintptr_t)&__metal_dt_pwm_10020000) {
		return METAL_SIFIVE_PWM0_10020000_BASE_ADDRESS;
	}
	else if ((uintptr_t)pwm == (uintptr_t)&__metal_dt_pwm_10021000) {
		return METAL_SIFIVE_PWM0_10021000_BASE_ADDRESS;
	}
	else {
		return 0;
	}
}

static __inline__ unsigned long __metal_driver_sifive_pwm0_control_size(struct metal_pwm *pwm)
{
	if ((uintptr_t)pwm == (uintptr_t)&__metal_dt_pwm_10020000) {
		return METAL_SIFIVE_PWM0_10020000_SIZE;
	}
	else if ((uintptr_t)pwm == (uintptr_t)&__metal_dt_pwm_10021000) {
		return METAL_SIFIVE_PWM0_10021000_SIZE;
	}
	else {
		return 0;
	}
}

static __inline__ struct metal_clock * __metal_driver_sifive_pwm0_clock(struct metal_pwm *pwm)
{
	if ((uintptr_t)pwm == (uintptr_t)&__metal_dt_pwm_10020000) {
		return (struct metal_clock *)&__metal_dt_tlclk.clock;
	}
	else if ((uintptr_t)pwm == (uintptr_t)&__metal_dt_pwm_10021000) {
		return (struct metal_clock *)&__metal_dt_tlclk.clock;
	}
	else {
		return NULL;
	}
}

static __inline__ struct __metal_driver_sifive_gpio0 * __metal_driver_sifive_pwm0_pinmux(struct metal_pwm *pwm)
{
	if ((uintptr_t)pwm == (uintptr_t)&__metal_dt_pwm_10020000) {
		return NULL;
	}
	else if ((uintptr_t)pwm == (uintptr_t)&__metal_dt_pwm_10021000) {
		return NULL;
	}
	else {
		return NULL;
	}
}

static __inline__ unsigned long __metal_driver_sifive_pwm0_pinmux_output_selector(struct metal_pwm *pwm)
{
	if ((uintptr_t)pwm == (uintptr_t)&__metal_dt_pwm_10020000) {
		return 0;
	}
	else if ((uintptr_t)pwm == (uintptr_t)&__metal_dt_pwm_10021000) {
		return 0;
	}
	else {
		return 0;
	}
}

static __inline__ unsigned long __metal_driver_sifive_pwm0_pinmux_source_selector(struct metal_pwm *pwm)
{
	if ((uintptr_t)pwm == (uintptr_t)&__metal_dt_pwm_10020000) {
		return 0;
	}
	else if ((uintptr_t)pwm == (uintptr_t)&__metal_dt_pwm_10021000) {
		return 0;
	}
	else {
		return 0;
	}
}

static __inline__ int __metal_driver_sifive_pwm0_num_interrupts(struct metal_pwm *pwm)
{
	if ((uintptr_t)pwm == (uintptr_t)&__metal_dt_pwm_10020000) {
		return __METAL_PWM_10020000_INTERRUPTS;
	}
	else if ((uintptr_t)pwm == (uintptr_t)&__metal_dt_pwm_10021000) {
		return __METAL_PWM_10021000_INTERRUPTS;
	}
	else {
		return 0;
	}
}

static __inline__ struct metal_interrupt * __metal_driver_sifive_pwm0_interrupt_parent(struct metal_pwm *pwm)
{
		return (struct metal_interrupt *)&__metal_dt_interrupt_controller_c000000.controller;
}

static __inline__ int __metal_driver_sifive_pwm0_interrupt_lines(struct metal_pwm *pwm, int idx)
{
	if (((uintptr_t)pwm == (uintptr_t)&__metal_dt_pwm_10020000) && (idx == 0)) {
		return 42;
	}
	else if ((((uintptr_t)pwm == (uintptr_t)&__metal_dt_pwm_10020000) && (idx == 1))) {
		return 43;
	}
	else if ((((uintptr_t)pwm == (uintptr_t)&__metal_dt_pwm_10020000) && (idx == 2))) {
		return 44;
	}
	else if ((((uintptr_t)pwm == (uintptr_t)&__metal_dt_pwm_10020000) && (idx == 3))) {
		return 45;
	}
	else if ((((uintptr_t)pwm == (uintptr_t)&__metal_dt_pwm_10021000) && (idx == 0))) {
		return 46;
	}
	else if ((((uintptr_t)pwm == (uintptr_t)&__metal_dt_pwm_10021000) && (idx == 1))) {
		return 47;
	}
	else if ((((uintptr_t)pwm == (uintptr_t)&__metal_dt_pwm_10021000) && (idx == 2))) {
		return 48;
	}
	else if ((((uintptr_t)pwm == (uintptr_t)&__metal_dt_pwm_10021000) && (idx == 3))) {
		return 49;
	}
	else {
		return 0;
	}
}

static __inline__ int __metal_driver_sifive_pwm0_compare_width(struct metal_pwm *pwm)
{
	if ((uintptr_t)pwm == (uintptr_t)&__metal_dt_pwm_10020000) {
		return 16;
	}
	else if ((uintptr_t)pwm == (uintptr_t)&__metal_dt_pwm_10021000) {
		return 16;
	}
	else {
		return 0;
	}
}

static __inline__ int __metal_driver_sifive_pwm0_comparator_count(struct metal_pwm *pwm)
{
	if ((uintptr_t)pwm == (uintptr_t)&__metal_dt_pwm_10020000) {
		return 4;
	}
	else if ((uintptr_t)pwm == (uintptr_t)&__metal_dt_pwm_10021000) {
		return 4;
	}
	else {
		return 0;
	}
}



/* --------------------- sifive_rtc0 ------------ */

static __inline__ unsigned long __metal_driver_sifive_spi0_control_base(struct metal_spi *spi)
{
	if ((uintptr_t)spi == (uintptr_t)&__metal_dt_spi_10040000) {
		return METAL_SIFIVE_SPI0_10040000_BASE_ADDRESS;
	}
	else if ((uintptr_t)spi == (uintptr_t)&__metal_dt_spi_10041000) {
		return METAL_SIFIVE_SPI0_10041000_BASE_ADDRESS;
	}
	else if ((uintptr_t)spi == (uintptr_t)&__metal_dt_spi_10050000) {
		return METAL_SIFIVE_SPI0_10050000_BASE_ADDRESS;
	}
	else {
		return 0;
	}
}

static __inline__ unsigned long __metal_driver_sifive_spi0_control_size(struct metal_spi *spi)
{
	if ((uintptr_t)spi == (uintptr_t)&__metal_dt_spi_10040000) {
		return METAL_SIFIVE_SPI0_10040000_SIZE;
	}
	else if ((uintptr_t)spi == (uintptr_t)&__metal_dt_spi_10041000) {
		return METAL_SIFIVE_SPI0_10041000_SIZE;
	}
	else if ((uintptr_t)spi == (uintptr_t)&__metal_dt_spi_10050000) {
		return METAL_SIFIVE_SPI0_10050000_SIZE;
	}
	else {
		return 0;
	}
}

static __inline__ struct metal_clock * __metal_driver_sifive_spi0_clock(struct metal_spi *spi)
{
	if ((uintptr_t)spi == (uintptr_t)&__metal_dt_spi_10040000) {
		return (struct metal_clock *)&__metal_dt_tlclk.clock;
	}
	else if ((uintptr_t)spi == (uintptr_t)&__metal_dt_spi_10041000) {
		return (struct metal_clock *)&__metal_dt_tlclk.clock;
	}
	else if ((uintptr_t)spi == (uintptr_t)&__metal_dt_spi_10050000) {
		return (struct metal_clock *)&__metal_dt_tlclk.clock;
	}
	else {
		return 0;
	}
}

static __inline__ struct __metal_driver_sifive_gpio0 * __metal_driver_sifive_spi0_pinmux(struct metal_spi *spi)
{
	if ((uintptr_t)spi == (uintptr_t)&__metal_dt_spi_10040000) {
		return NULL;
	}
	else if ((uintptr_t)spi == (uintptr_t)&__metal_dt_spi_10041000) {
		return NULL;
	}
	else if ((uintptr_t)spi == (uintptr_t)&__metal_dt_spi_10050000) {
		return NULL;
	}
	else {
		return 0;
	}
}

static __inline__ unsigned long __metal_driver_sifive_spi0_pinmux_output_selector(struct metal_spi *spi)
{
	if ((uintptr_t)spi == (uintptr_t)&__metal_dt_spi_10040000) {
		return 0;
	}
	else if ((uintptr_t)spi == (uintptr_t)&__metal_dt_spi_10041000) {
		return 0;
	}
	else if ((uintptr_t)spi == (uintptr_t)&__metal_dt_spi_10050000) {
		return 0;
	}
	else {
		return 0;
	}
}

static __inline__ unsigned long __metal_driver_sifive_spi0_pinmux_source_selector(struct metal_spi *spi)
{
	if ((uintptr_t)spi == (uintptr_t)&__metal_dt_spi_10040000) {
		return 0;
	}
	else if ((uintptr_t)spi == (uintptr_t)&__metal_dt_spi_10041000) {
		return 0;
	}
	else if ((uintptr_t)spi == (uintptr_t)&__metal_dt_spi_10050000) {
		return 0;
	}
	else {
		return 0;
	}
}



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

/* --------------------- sifive_uart0 ------------ */
static __inline__ unsigned long __metal_driver_sifive_uart0_control_base(struct metal_uart *uart)
{
	if ((uintptr_t)uart == (uintptr_t)&__metal_dt_serial_10010000) {
		return METAL_SIFIVE_UART0_10010000_BASE_ADDRESS;
	}
	else if ((uintptr_t)uart == (uintptr_t)&__metal_dt_serial_10011000) {
		return METAL_SIFIVE_UART0_10011000_BASE_ADDRESS;
	}
	else {
		return 0;
	}
}

static __inline__ unsigned long __metal_driver_sifive_uart0_control_size(struct metal_uart *uart)
{
	if ((uintptr_t)uart == (uintptr_t)&__metal_dt_serial_10010000) {
		return METAL_SIFIVE_UART0_10010000_SIZE;
	}
	else if ((uintptr_t)uart == (uintptr_t)&__metal_dt_serial_10011000) {
		return METAL_SIFIVE_UART0_10011000_SIZE;
	}
	else {
		return 0;
	}
}

static __inline__ int __metal_driver_sifive_uart0_num_interrupts(struct metal_uart *uart)
{
	if ((uintptr_t)uart == (uintptr_t)&__metal_dt_serial_10010000) {
		return METAL_MAX_UART_INTERRUPTS;
	}
	else if ((uintptr_t)uart == (uintptr_t)&__metal_dt_serial_10011000) {
		return METAL_MAX_UART_INTERRUPTS;
	}
	else {
		return 0;
	}
}

static __inline__ struct metal_interrupt * __metal_driver_sifive_uart0_interrupt_parent(struct metal_uart *uart)
{
	if ((uintptr_t)uart == (uintptr_t)&__metal_dt_serial_10010000) {
		return (struct metal_interrupt *)&__metal_dt_interrupt_controller_c000000.controller;
	}
	else if ((uintptr_t)uart == (uintptr_t)&__metal_dt_serial_10011000) {
		return (struct metal_interrupt *)&__metal_dt_interrupt_controller_c000000.controller;
	}
	else {
		return 0;
	}
}

static __inline__ int __metal_driver_sifive_uart0_interrupt_line(struct metal_uart *uart)
{
	if ((uintptr_t)uart == (uintptr_t)&__metal_dt_serial_10010000) {
		return 4;
	}
	else if ((uintptr_t)uart == (uintptr_t)&__metal_dt_serial_10011000) {
		return 5;
	}
	else {
		return 0;
	}
}

static __inline__ struct metal_clock * __metal_driver_sifive_uart0_clock(struct metal_uart *uart)
{
	if ((uintptr_t)uart == (uintptr_t)&__metal_dt_serial_10010000) {
		return (struct metal_clock *)&__metal_dt_tlclk.clock;
	}
	else if ((uintptr_t)uart == (uintptr_t)&__metal_dt_serial_10011000) {
		return (struct metal_clock *)&__metal_dt_tlclk.clock;
	}
	else {
		return 0;
	}
}

static __inline__ struct __metal_driver_sifive_gpio0 * __metal_driver_sifive_uart0_pinmux(struct metal_uart *uart)
{
	if ((uintptr_t)uart == (uintptr_t)&__metal_dt_serial_10010000) {
		return NULL;
	}
	else if ((uintptr_t)uart == (uintptr_t)&__metal_dt_serial_10011000) {
		return NULL;
	}
	else {
		return 0;
	}
}

static __inline__ unsigned long __metal_driver_sifive_uart0_pinmux_output_selector(struct metal_uart *uart)
{
	if ((uintptr_t)uart == (uintptr_t)&__metal_dt_serial_10010000) {
		return 0;
	}
	else if ((uintptr_t)uart == (uintptr_t)&__metal_dt_serial_10011000) {
		return 0;
	}
	else {
		return 0;
	}
}

static __inline__ unsigned long __metal_driver_sifive_uart0_pinmux_source_selector(struct metal_uart *uart)
{
	if ((uintptr_t)uart == (uintptr_t)&__metal_dt_serial_10010000) {
		return 0;
	}
	else if ((uintptr_t)uart == (uintptr_t)&__metal_dt_serial_10011000) {
		return 0;
	}
	else {
		return 0;
	}
}



/* --------------------- sifive_simuart0 ------------ */


/* --------------------- sifive_wdog0 ------------ */


/* --------------------- sifive_fe310_g000_hfrosc ------------ */


/* --------------------- sifive_fe310_g000_hfxosc ------------ */


/* --------------------- sifive_fe310_g000_lfrosc ------------ */


/* --------------------- sifive_fe310_g000_pll ------------ */


/* --------------------- sifive_fe310_g000_prci ------------ */


#define __METAL_DT_MAX_MEMORIES 9

__asm__ (".weak __metal_memory_table");
struct metal_memory *__metal_memory_table[] = {
					&__metal_dt_mem_dtim_1000000,
					&__metal_dt_mem_itim_1800000,
					&__metal_dt_mem_itim_1808000,
					&__metal_dt_mem_itim_1810000,
					&__metal_dt_mem_itim_1818000,
					&__metal_dt_mem_itim_1820000,
					&__metal_dt_mem_memory_80000000,
					&__metal_dt_mem_spi_10040000,
					&__metal_dt_mem_spi_10041000};

/* From serial@10010000 */
#define __METAL_DT_STDOUT_UART_HANDLE (&__metal_dt_serial_10010000.uart)

#define __METAL_DT_SERIAL_10010000_HANDLE (&__metal_dt_serial_10010000.uart)

#define __METAL_DT_STDOUT_UART_BAUD 115200

/* From clint@2000000 */
#define __METAL_DT_RISCV_CLINT0_HANDLE (&__metal_dt_clint_2000000.controller)

#define __METAL_DT_CLINT_2000000_HANDLE (&__metal_dt_clint_2000000.controller)

#define __METAL_DT_MAX_HARTS 5

#define __METAL_CPU_0_ICACHE_HANDLE 1

#define __METAL_CPU_1_ICACHE_HANDLE 1

#define __METAL_CPU_1_DCACHE_HANDLE 1

#define __METAL_CPU_2_ICACHE_HANDLE 1

#define __METAL_CPU_2_DCACHE_HANDLE 1

#define __METAL_CPU_3_ICACHE_HANDLE 1

#define __METAL_CPU_3_DCACHE_HANDLE 1

#define __METAL_CPU_4_ICACHE_HANDLE 1

#define __METAL_CPU_4_DCACHE_HANDLE 1

__asm__ (".weak __metal_cpu_table");
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

#define __MEE_DT_MAX_GPIOS 1

__asm__ (".weak __metal_gpio_table");
struct __metal_driver_sifive_gpio0 *__metal_gpio_table[] = {
					&__metal_dt_gpio_10060000};

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
#define __METAL_DT_MAX_I2CS 1

__asm__ (".weak __metal_i2c_table");
struct __metal_driver_sifive_i2c0 *__metal_i2c_table[] = {
					&__metal_dt_i2c_10030000};

#define __METAL_DT_MAX_PWMS 2

__asm__ (".weak __metal_pwm_table");
struct __metal_driver_sifive_pwm0 *__metal_pwm_table[] = {
					&__metal_dt_pwm_10020000,
					&__metal_dt_pwm_10021000};

#define __METAL_DT_MAX_RTCS 0

__asm__ (".weak __metal_rtc_table");
struct __metal_driver_sifive_rtc0 *__metal_rtc_table[] = {
					NULL };
#define __METAL_DT_MAX_SPIS 3

__asm__ (".weak __metal_spi_table");
struct __metal_driver_sifive_spi0 *__metal_spi_table[] = {
					&__metal_dt_spi_10040000,
					&__metal_dt_spi_10041000,
					&__metal_dt_spi_10050000};

/* From teststatus@4000 */
#define __METAL_DT_SHUTDOWN_HANDLE (&__metal_dt_teststatus_4000.shutdown)

#define __METAL_DT_TESTSTATUS_4000_HANDLE (&__metal_dt_teststatus_4000.shutdown)

#define __METAL_DT_MAX_UARTS 2

__asm__ (".weak __metal_uart_table");
struct __metal_driver_sifive_uart0 *__metal_uart_table[] = {
					&__metal_dt_serial_10010000,
					&__metal_dt_serial_10011000};

#define __METAL_DT_MAX_SIMUARTS 0

__asm__ (".weak __metal_simuart_table");
struct __metal_driver_sifive_simuart0 *__metal_simuart_table[] = {
					NULL };
#define __METAL_DT_MAX_WDOGS 0

__asm__ (".weak __metal_wdog_table");
struct __metal_driver_sifive_wdog0 *__metal_wdog_table[] = {
					NULL };
#endif /* MACROS_ELSE_METAL_H*/

#endif /* ! __METAL_MACHINE_MACROS */

#endif /* ! ASSEMBLY */
