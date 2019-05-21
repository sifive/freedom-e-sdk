/* Copyright 2019 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */
/* ----------------------------------- */
/* [XXXXX] 21-05-2019 10-54-35        */
/* ----------------------------------- */

#ifndef ASSEMBLY

#include <metal/machine/platform.h>

#ifdef __METAL_MACHINE_MACROS

#ifndef MACROS_IF_SIFIVE_HIFIVE_UNLEASHED__METAL_H
#define MACROS_IF_SIFIVE_HIFIVE_UNLEASHED__METAL_H

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

#endif /* MACROS_IF_SIFIVE_HIFIVE_UNLEASHED__METAL_H*/

#else /* ! __METAL_MACHINE_MACROS */

#ifndef MACROS_ELSE_SIFIVE_HIFIVE_UNLEASHED__METAL_H
#define MACROS_ELSE_SIFIVE_HIFIVE_UNLEASHED__METAL_H

#define __METAL_CLINT_2000000_INTERRUPTS 10

#define METAL_MAX_CLINT_INTERRUPTS 10

#define __METAL_CLINT_NUM_PARENTS 10

#define __METAL_INTERRUPT_CONTROLLER_C000000_INTERRUPTS 9

#define __METAL_PLIC_SUBINTERRUPTS 54

#define METAL_MAX_PLIC_INTERRUPTS 9

#define __METAL_PLIC_NUM_PARENTS 9

#define __METAL_CLIC_SUBINTERRUPTS 0
#define METAL_MAX_CLIC_INTERRUPTS 0

#define METAL_MAX_LOCAL_EXT_INTERRUPTS 0

#define METAL_MAX_GLOBAL_EXT_INTERRUPTS 0

#define __METAL_GPIO_10060000_INTERRUPTS 16

#define METAL_MAX_GPIO_INTERRUPTS 16

#define __METAL_SERIAL_10010000_INTERRUPTS 1

#define __METAL_SERIAL_10011000_INTERRUPTS 1

#define METAL_MAX_UART_INTERRUPTS 1


#include <metal/drivers/fixed-clock.h>
#include <metal/drivers/fixed-factor-clock.h>
#include <metal/memory.h>
#include <metal/drivers/riscv,clint0.h>
#include <metal/drivers/riscv,cpu.h>
#include <metal/drivers/riscv,plic0.h>
#include <metal/pmp.h>
#include <metal/drivers/sifive,gpio0.h>
#include <metal/drivers/sifive,spi0.h>
#include <metal/drivers/sifive,test0.h>
#include <metal/drivers/sifive,uart0.h>
#include <metal/drivers/sifive,fu540-c000,l2.h>

/* From refclk */
struct __metal_driver_fixed_clock __metal_dt_refclk;

/* From tlclk */
struct __metal_driver_fixed_factor_clock __metal_dt_tlclk;

struct metal_memory __metal_dt_mem_dtim_1000000;

struct metal_memory __metal_dt_mem_itim_1800000;

struct metal_memory __metal_dt_mem_itim_1808000;

struct metal_memory __metal_dt_mem_itim_1810000;

struct metal_memory __metal_dt_mem_itim_1818000;

struct metal_memory __metal_dt_mem_itim_1820000;

struct metal_memory __metal_dt_mem_memory_80000000;

struct metal_memory __metal_dt_mem_spi_10040000;

struct metal_memory __metal_dt_mem_spi_10041000;

struct metal_memory __metal_dt_mem_spi_10050000;

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

/* From gpio@10060000 */
struct __metal_driver_sifive_gpio0 __metal_dt_gpio_10060000;

/* From spi@10040000 */
struct __metal_driver_sifive_spi0 __metal_dt_spi_10040000;

/* From spi@10041000 */
struct __metal_driver_sifive_spi0 __metal_dt_spi_10041000;

/* From spi@10050000 */
struct __metal_driver_sifive_spi0 __metal_dt_spi_10050000;

/* From teststatus@4000 */
struct __metal_driver_sifive_test0 __metal_dt_teststatus_4000;

/* From serial@10010000 */
struct __metal_driver_sifive_uart0 __metal_dt_serial_10010000;

/* From serial@10011000 */
struct __metal_driver_sifive_uart0 __metal_dt_serial_10011000;

/* From cache_controller@2010000 */
struct __metal_driver_sifive_fu540_c000_l2 __metal_dt_cache_controller_2010000;



/* --------------------- fixed_clock ------------ */
static inline unsigned long __metal_driver_fixed_clock_rate(struct metal_clock *clock)
{
	if ((uintptr_t)clock == (uintptr_t)&__metal_dt_refclk) {
		return METAL_FIXED_CLOCK__CLOCK_FREQUENCY;
	}
	else {
		return 0;
	}
}



/* --------------------- fixed_factor_clock ------------ */
static inline struct metal_clock * __metal_driver_fixed_factor_clock_parent(struct metal_clock *clock)
{
		return (struct metal_clock *)&__metal_dt_refclk.clock;
}

static inline unsigned long __metal_driver_fixed_factor_clock_mult(struct metal_clock *clock)
{
	if ((uintptr_t)clock == (uintptr_t)&__metal_dt_tlclk) {
		return METAL_FIXED_FACTOR_CLOCK__CLOCK_MULT;
	}
	else {
		return 0;
	}
}

static inline unsigned long __metal_driver_fixed_factor_clock_div(struct metal_clock *clock)
{
	if ((uintptr_t)clock == (uintptr_t)&__metal_dt_tlclk) {
		return METAL_FIXED_FACTOR_CLOCK__CLOCK_DIV;
	}
	else {
		return 0;
	}
}



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


/* --------------------- sifive_gpio0 ------------ */
static inline unsigned long __metal_driver_sifive_gpio0_base(struct metal_gpio *gpio)
{
	if ((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_10060000) {
		return METAL_SIFIVE_GPIO0_10060000_BASE_ADDRESS;
	}
	else {
		return 0;
	}
}

static inline unsigned long __metal_driver_sifive_gpio0_size(struct metal_gpio *gpio)
{
	if ((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_10060000) {
		return METAL_SIFIVE_GPIO0_10060000_SIZE;
	}
	else {
		return 0;
	}
}

static inline int __metal_driver_sifive_gpio0_num_interrupts(struct metal_gpio *gpio)
{
	if ((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_10060000) {
		return METAL_MAX_GPIO_INTERRUPTS;
	}
	else {
		return 0;
	}
}

static inline struct metal_interrupt * __metal_driver_sifive_gpio0_interrupt_parent(struct metal_gpio *gpio)
{
	if ((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_10060000) {
		return (struct metal_interrupt *)&__metal_dt_interrupt_controller_c000000.controller;
	}
	else {
		return 0;
	}
}

static inline int __metal_driver_sifive_gpio0_interrupt_lines(struct metal_gpio *gpio, int idx)
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


/* --------------------- sifive_spi0 ------------ */
static inline unsigned long __metal_driver_sifive_spi0_control_base(struct metal_spi *spi)
{
	if ((uintptr_t)spi == (uintptr_t)&__metal_dt_spi_10040000) {
		return METAL_SIFIVE_SPI0_10040000_BASE_ADDRESS;
	}
	else {
		return 0;
	}
}

static inline unsigned long __metal_driver_sifive_spi0_control_size(struct metal_spi *spi)
{
	if ((uintptr_t)spi == (uintptr_t)&__metal_dt_spi_10040000) {
		return METAL_SIFIVE_SPI0_10040000_SIZE;
	}
	else {
		return 0;
	}
}

static inline struct metal_clock * __metal_driver_sifive_spi0_clock(struct metal_spi *spi)
{
		return (struct metal_clock *)&__metal_dt_tlclk.clock;
}

static inline struct __metal_driver_sifive_gpio0 * __metal_driver_sifive_spi0_pinmux(struct metal_spi *spi)
{
		return NULL;
}

static inline unsigned long __metal_driver_sifive_spi0_pinmux_output_selector(struct metal_spi *spi)
{
		return 0;
}

static inline unsigned long __metal_driver_sifive_spi0_pinmux_source_selector(struct metal_spi *spi)
{
		return 0;
}



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
static inline unsigned long __metal_driver_sifive_uart0_control_base(struct metal_uart *uart)
{
	if ((uintptr_t)uart == (uintptr_t)&__metal_dt_serial_10010000) {
		return METAL_SIFIVE_UART0_10010000_BASE_ADDRESS;
	}
	else {
		return 0;
	}
}

static inline unsigned long __metal_driver_sifive_uart0_control_size(struct metal_uart *uart)
{
	if ((uintptr_t)uart == (uintptr_t)&__metal_dt_serial_10010000) {
		return METAL_SIFIVE_UART0_10010000_SIZE;
	}
	else {
		return 0;
	}
}

static inline int __metal_driver_sifive_uart0_num_interrupts(struct metal_uart *uart)
{
	if ((uintptr_t)uart == (uintptr_t)&__metal_dt_serial_10010000) {
		return METAL_MAX_UART_INTERRUPTS;
	}
	else {
		return 0;
	}
}

static inline struct metal_interrupt * __metal_driver_sifive_uart0_interrupt_parent(struct metal_uart *uart)
{
	if ((uintptr_t)uart == (uintptr_t)&__metal_dt_serial_10010000) {
		return (struct metal_interrupt *)&__metal_dt_interrupt_controller_c000000.controller;
	}
	else {
		return NULL;
	}
}

static inline int __metal_driver_sifive_uart0_interrupt_line(struct metal_uart *uart)
{
		return 4;
}

static inline struct metal_clock * __metal_driver_sifive_uart0_clock(struct metal_uart *uart)
{
		return (struct metal_clock *)&__metal_dt_tlclk.clock;
}

static inline struct __metal_driver_sifive_gpio0 * __metal_driver_sifive_uart0_pinmux(struct metal_uart *uart)
{
		return NULL;
}

static inline unsigned long __metal_driver_sifive_uart0_pinmux_output_selector(struct metal_uart *uart)
{
		return 0;
}

static inline unsigned long __metal_driver_sifive_uart0_pinmux_source_selector(struct metal_uart *uart)
{
		return 0;
}



/* --------------------- sifive_fe310_g000_hfrosc ------------ */


/* --------------------- sifive_fe310_g000_hfxosc ------------ */


/* --------------------- sifive_fe310_g000_pll ------------ */


/* --------------------- sifive_fe310_g000_prci ------------ */


/* --------------------- sifive_fu540_c000_l2 ------------ */


#define __METAL_DT_MAX_MEMORIES 9

asm (".weak __metal_memory_table");
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

#define __MEE_DT_MAX_GPIOS 1

asm (".weak __metal_gpio_table");
struct __metal_driver_sifive_gpio0 *__metal_gpio_table[] = {
					&__metal_dt_gpio_10060000};

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
#define __METAL_DT_MAX_SPIS 3

asm (".weak __metal_spi_table");
struct __metal_driver_sifive_spi0 *__metal_spi_table[] = {
					&__metal_dt_spi_10040000,
					&__metal_dt_spi_10041000,
					&__metal_dt_spi_10050000};

/* From teststatus@4000 */
#define __METAL_DT_SHUTDOWN_HANDLE (&__metal_dt_teststatus_4000.shutdown)

#define __METAL_DT_TESTSTATUS_4000_HANDLE (&__metal_dt_teststatus_4000.shutdown)

/* From cache_controller@2010000 */
#define __METAL_DT_SIFIVE_FU540_C000_L2_HANDLE (&__metal_dt_cache_controller_2010000)

#define __METAL_DT_CACHE_CONTROLLER_2010000_HANDLE (&__metal_dt_cache_controller_2010000)

#endif /* MACROS_ELSE_SIFIVE_HIFIVE_UNLEASHED__METAL_H*/

#endif /* ! __METAL_MACHINE_MACROS */

#endif /* ! ASSEMBLY */
