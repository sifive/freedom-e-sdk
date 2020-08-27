/* Copyright 2019 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */
/* ----------------------------------- */
/* ----------------------------------- */

#ifndef ASSEMBLY

#include <metal/machine/platform.h>

#ifdef __METAL_MACHINE_MACROS

#ifndef MACROS_IF_METAL_H
#define MACROS_IF_METAL_H

#define __METAL_CLINT_NUM_PARENTS 2

#ifndef __METAL_CLINT_NUM_PARENTS
#define __METAL_CLINT_NUM_PARENTS 0
#endif
#define __METAL_PLIC_SUBINTERRUPTS 55

#define __METAL_PLIC_NUM_PARENTS 1

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

#define __METAL_CLINT_2000000_INTERRUPTS 2

#define METAL_MAX_CLINT_INTERRUPTS 2

#define __METAL_CLINT_NUM_PARENTS 2

#define __METAL_INTERRUPT_CONTROLLER_C000000_INTERRUPTS 1

#define __METAL_PLIC_SUBINTERRUPTS 55

#define METAL_MAX_PLIC_INTERRUPTS 1

#define __METAL_PLIC_NUM_PARENTS 1

#define __METAL_CLIC_SUBINTERRUPTS 0
#define METAL_MAX_CLIC_INTERRUPTS 0

#define METAL_MAX_LOCAL_EXT_INTERRUPTS 0

#define METAL_MAX_GLOBAL_EXT_INTERRUPTS 0

#define __METAL_GPIO_10012000_INTERRUPTS 32

#define METAL_MAX_GPIO_INTERRUPTS 32

#define METAL_MAX_I2C0_INTERRUPTS 0

#define METAL_MAX_PWM0_INTERRUPTS 0

#define METAL_MAX_PWM0_NCMP 0

#define __METAL_UART_10013000_INTERRUPTS 1

#define __METAL_UART_10023000_INTERRUPTS 1

#define METAL_MAX_UART_INTERRUPTS 1

#define METAL_MAX_SIMUART_INTERRUPTS 0


#include <metal/drivers/fixed-clock.h>
#include <metal/memory.h>
#include <metal/drivers/riscv_clint0.h>
#include <metal/drivers/riscv_cpu.h>
#include <metal/drivers/riscv_plic0.h>
#include <metal/pmp.h>
#include <metal/drivers/sifive_gpio0.h>
#include <metal/drivers/sifive_spi0.h>
#include <metal/drivers/sifive_test0.h>
#include <metal/drivers/sifive_uart0.h>
#include <metal/drivers/sifive_fe310-g000_prci.h>

extern struct metal_memory __metal_dt_mem_rom_1000;

extern struct metal_memory __metal_dt_mem_rom_10000;

extern struct metal_memory __metal_dt_mem_itim_8000000;

extern struct metal_memory __metal_dt_mem_dtim_80000000;

extern struct metal_memory __metal_dt_mem_spi_10014000;

/* From clint@2000000 */
extern struct __metal_driver_riscv_clint0 __metal_dt_clint_2000000;

/* From cpu@0 */
extern struct __metal_driver_cpu __metal_dt_cpu_0;

extern struct __metal_driver_riscv_cpu_intc __metal_dt_cpu_0_interrupt_controller;

/* From interrupt_controller@c000000 */
extern struct __metal_driver_riscv_plic0 __metal_dt_interrupt_controller_c000000;

/* From gpio@10012000 */
extern struct __metal_driver_sifive_gpio0 __metal_dt_gpio_10012000;

/* From spi@10014000 */
extern struct __metal_driver_sifive_spi0 __metal_dt_spi_10014000;

/* From test@12000 */
extern struct __metal_driver_sifive_test0 __metal_dt_test_12000;

/* From uart@10013000 */
extern struct __metal_driver_sifive_uart0 __metal_dt_uart_10013000;

/* From uart@10023000 */
extern struct __metal_driver_sifive_uart0 __metal_dt_uart_10023000;

/* From pcri@10008000 */
extern struct __metal_driver_sifive_fe310_g000_prci __metal_dt_pcri_10008000;



/* --------------------- fixed_clock ------------ */


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
	else {
		return -1;
	}
}

static __inline__ int __metal_driver_cpu_timebase(struct metal_cpu *cpu)
{
	if ((uintptr_t)cpu == (uintptr_t)&__metal_dt_cpu_0) {
		return 32768;
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
	else {
		return NULL;
	}
}

static __inline__ int __metal_driver_cpu_num_pmp_regions(struct metal_cpu *cpu)
{
	if ((uintptr_t)cpu == (uintptr_t)&__metal_dt_cpu_0) {
		return 0;
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
	else {
		return NULL;
	}
}

static __inline__ int __metal_driver_sifive_plic0_interrupt_lines(struct metal_interrupt *controller, int idx)
{
	if (idx == 0) {
		return 11;
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
	else {
		return -1;
	}
}



/* --------------------- sifive_buserror0 ------------ */


/* --------------------- sifive_ccache0 ------------ */


/* --------------------- sifive_clic0 ------------ */


/* --------------------- sifive_local_external_interrupts0 ------------ */


/* --------------------- sifive_global_external_interrupts0 ------------ */


/* --------------------- sifive_gpio0 ------------ */
static __inline__ unsigned long __metal_driver_sifive_gpio0_base(struct metal_gpio *gpio)
{
	if ((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_10012000) {
		return METAL_SIFIVE_GPIO0_10012000_BASE_ADDRESS;
	}
	else {
		return 0;
	}
}

static __inline__ unsigned long __metal_driver_sifive_gpio0_size(struct metal_gpio *gpio)
{
	if ((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_10012000) {
		return METAL_SIFIVE_GPIO0_10012000_SIZE;
	}
	else {
		return 0;
	}
}

static __inline__ int __metal_driver_sifive_gpio0_num_interrupts(struct metal_gpio *gpio)
{
	if ((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_10012000) {
		return METAL_MAX_GPIO_INTERRUPTS;
	}
	else {
		return 0;
	}
}

static __inline__ struct metal_interrupt * __metal_driver_sifive_gpio0_interrupt_parent(struct metal_gpio *gpio)
{
	if ((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_10012000) {
		return (struct metal_interrupt *)&__metal_dt_interrupt_controller_c000000.controller;
	}
	else {
		return 0;
	}
}

static __inline__ int __metal_driver_sifive_gpio0_interrupt_lines(struct metal_gpio *gpio, int idx)
{
	if (((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_10012000) && (idx == 0)) {
		return 8;
	}
	else if ((((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_10012000) && (idx == 1))) {
		return 9;
	}
	else if ((((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_10012000) && (idx == 2))) {
		return 10;
	}
	else if ((((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_10012000) && (idx == 3))) {
		return 11;
	}
	else if ((((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_10012000) && (idx == 4))) {
		return 12;
	}
	else if ((((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_10012000) && (idx == 5))) {
		return 13;
	}
	else if ((((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_10012000) && (idx == 6))) {
		return 14;
	}
	else if ((((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_10012000) && (idx == 7))) {
		return 15;
	}
	else if ((((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_10012000) && (idx == 8))) {
		return 16;
	}
	else if ((((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_10012000) && (idx == 9))) {
		return 17;
	}
	else if ((((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_10012000) && (idx == 10))) {
		return 18;
	}
	else if ((((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_10012000) && (idx == 11))) {
		return 19;
	}
	else if ((((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_10012000) && (idx == 12))) {
		return 20;
	}
	else if ((((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_10012000) && (idx == 13))) {
		return 21;
	}
	else if ((((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_10012000) && (idx == 14))) {
		return 22;
	}
	else if ((((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_10012000) && (idx == 15))) {
		return 23;
	}
	else if ((((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_10012000) && (idx == 16))) {
		return 24;
	}
	else if ((((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_10012000) && (idx == 17))) {
		return 25;
	}
	else if ((((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_10012000) && (idx == 18))) {
		return 26;
	}
	else if ((((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_10012000) && (idx == 19))) {
		return 27;
	}
	else if ((((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_10012000) && (idx == 20))) {
		return 28;
	}
	else if ((((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_10012000) && (idx == 21))) {
		return 29;
	}
	else if ((((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_10012000) && (idx == 22))) {
		return 30;
	}
	else if ((((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_10012000) && (idx == 23))) {
		return 31;
	}
	else if ((((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_10012000) && (idx == 24))) {
		return 32;
	}
	else if ((((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_10012000) && (idx == 25))) {
		return 33;
	}
	else if ((((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_10012000) && (idx == 26))) {
		return 34;
	}
	else if ((((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_10012000) && (idx == 27))) {
		return 34;
	}
	else if ((((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_10012000) && (idx == 28))) {
		return 36;
	}
	else if ((((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_10012000) && (idx == 29))) {
		return 37;
	}
	else if ((((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_10012000) && (idx == 30))) {
		return 38;
	}
	else if ((((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_10012000) && (idx == 31))) {
		return 39;
	}
	else {
		return 0;
	}
}



/* --------------------- sifive_gpio_button ------------ */


/* --------------------- sifive_gpio_led ------------ */


/* --------------------- sifive_gpio_switch ------------ */


/* --------------------- sifive_i2c0 ------------ */


/* --------------------- sifive_pwm0 ------------ */


/* --------------------- sifive_rtc0 ------------ */

static __inline__ unsigned long __metal_driver_sifive_spi0_control_base(struct metal_spi *spi)
{
	if ((uintptr_t)spi == (uintptr_t)&__metal_dt_spi_10014000) {
		return METAL_SIFIVE_SPI0_10014000_BASE_ADDRESS;
	}
	else {
		return 0;
	}
}

static __inline__ unsigned long __metal_driver_sifive_spi0_control_size(struct metal_spi *spi)
{
	if ((uintptr_t)spi == (uintptr_t)&__metal_dt_spi_10014000) {
		return METAL_SIFIVE_SPI0_10014000_SIZE;
	}
	else {
		return 0;
	}
}

static __inline__ struct metal_clock * __metal_driver_sifive_spi0_clock(struct metal_spi *spi)
{
	if ((uintptr_t)spi == (uintptr_t)&__metal_dt_spi_10014000) {
		return NULL;
	}
	else {
		return 0;
	}
}

static __inline__ struct __metal_driver_sifive_gpio0 * __metal_driver_sifive_spi0_pinmux(struct metal_spi *spi)
{
	if ((uintptr_t)spi == (uintptr_t)&__metal_dt_spi_10014000) {
		return NULL;
	}
	else {
		return 0;
	}
}

static __inline__ unsigned long __metal_driver_sifive_spi0_pinmux_output_selector(struct metal_spi *spi)
{
	if ((uintptr_t)spi == (uintptr_t)&__metal_dt_spi_10014000) {
		return 0;
	}
	else {
		return 0;
	}
}

static __inline__ unsigned long __metal_driver_sifive_spi0_pinmux_source_selector(struct metal_spi *spi)
{
	if ((uintptr_t)spi == (uintptr_t)&__metal_dt_spi_10014000) {
		return 0;
	}
	else {
		return 0;
	}
}



/* --------------------- sifive_test0 ------------ */
static __inline__ unsigned long __metal_driver_sifive_test0_base(const struct __metal_shutdown *sd)
{
	if ((uintptr_t)sd == (uintptr_t)&__metal_dt_test_12000) {
		return METAL_SIFIVE_TEST0_12000_BASE_ADDRESS;
	}
	else {
		return 0;
	}
}

static __inline__ unsigned long __metal_driver_sifive_test0_size(const struct __metal_shutdown *sd)
{
	if ((uintptr_t)sd == (uintptr_t)&__metal_dt_test_12000) {
		return METAL_SIFIVE_TEST0_12000_SIZE;
	}
	else {
		return 0;
	}
}



/* --------------------- sifive_trace ------------ */

/* --------------------- sifive_uart0 ------------ */
static __inline__ unsigned long __metal_driver_sifive_uart0_control_base(struct metal_uart *uart)
{
	if ((uintptr_t)uart == (uintptr_t)&__metal_dt_uart_10013000) {
		return METAL_SIFIVE_UART0_10013000_BASE_ADDRESS;
	}
	else if ((uintptr_t)uart == (uintptr_t)&__metal_dt_uart_10023000) {
		return METAL_SIFIVE_UART0_10023000_BASE_ADDRESS;
	}
	else {
		return 0;
	}
}

static __inline__ unsigned long __metal_driver_sifive_uart0_control_size(struct metal_uart *uart)
{
	if ((uintptr_t)uart == (uintptr_t)&__metal_dt_uart_10013000) {
		return METAL_SIFIVE_UART0_10013000_SIZE;
	}
	else if ((uintptr_t)uart == (uintptr_t)&__metal_dt_uart_10023000) {
		return METAL_SIFIVE_UART0_10023000_SIZE;
	}
	else {
		return 0;
	}
}

static __inline__ int __metal_driver_sifive_uart0_num_interrupts(struct metal_uart *uart)
{
	if ((uintptr_t)uart == (uintptr_t)&__metal_dt_uart_10013000) {
		return METAL_MAX_UART_INTERRUPTS;
	}
	else if ((uintptr_t)uart == (uintptr_t)&__metal_dt_uart_10023000) {
		return METAL_MAX_UART_INTERRUPTS;
	}
	else {
		return 0;
	}
}

static __inline__ struct metal_interrupt * __metal_driver_sifive_uart0_interrupt_parent(struct metal_uart *uart)
{
	if ((uintptr_t)uart == (uintptr_t)&__metal_dt_uart_10013000) {
		return (struct metal_interrupt *)&__metal_dt_interrupt_controller_c000000.controller;
	}
	else if ((uintptr_t)uart == (uintptr_t)&__metal_dt_uart_10023000) {
		return (struct metal_interrupt *)&__metal_dt_interrupt_controller_c000000.controller;
	}
	else {
		return 0;
	}
}

static __inline__ int __metal_driver_sifive_uart0_interrupt_line(struct metal_uart *uart)
{
	if ((uintptr_t)uart == (uintptr_t)&__metal_dt_uart_10013000) {
		return 3;
	}
	else if ((uintptr_t)uart == (uintptr_t)&__metal_dt_uart_10023000) {
		return 4;
	}
	else {
		return 0;
	}
}

static __inline__ struct metal_clock * __metal_driver_sifive_uart0_clock(struct metal_uart *uart)
{
	if ((uintptr_t)uart == (uintptr_t)&__metal_dt_uart_10013000) {
		return NULL;
	}
	else if ((uintptr_t)uart == (uintptr_t)&__metal_dt_uart_10023000) {
		return NULL;
	}
	else {
		return 0;
	}
}

static __inline__ struct __metal_driver_sifive_gpio0 * __metal_driver_sifive_uart0_pinmux(struct metal_uart *uart)
{
	if ((uintptr_t)uart == (uintptr_t)&__metal_dt_uart_10013000) {
		return NULL;
	}
	else if ((uintptr_t)uart == (uintptr_t)&__metal_dt_uart_10023000) {
		return NULL;
	}
	else {
		return 0;
	}
}

static __inline__ unsigned long __metal_driver_sifive_uart0_pinmux_output_selector(struct metal_uart *uart)
{
	if ((uintptr_t)uart == (uintptr_t)&__metal_dt_uart_10013000) {
		return 0;
	}
	else if ((uintptr_t)uart == (uintptr_t)&__metal_dt_uart_10023000) {
		return 0;
	}
	else {
		return 0;
	}
}

static __inline__ unsigned long __metal_driver_sifive_uart0_pinmux_source_selector(struct metal_uart *uart)
{
	if ((uintptr_t)uart == (uintptr_t)&__metal_dt_uart_10013000) {
		return 0;
	}
	else if ((uintptr_t)uart == (uintptr_t)&__metal_dt_uart_10023000) {
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
static __inline__ long __metal_driver_sifive_fe310_g000_prci_base( )
{
		return METAL_SIFIVE_FE310_G000_PRCI_10008000_BASE_ADDRESS;
}

static __inline__ long __metal_driver_sifive_fe310_g000_prci_size( )
{
		return METAL_SIFIVE_FE310_G000_PRCI_10008000_SIZE;
}

static __inline__ const struct __metal_driver_vtable_sifive_fe310_g000_prci * __metal_driver_sifive_fe310_g000_prci_vtable( )
{
		return &__metal_driver_vtable_sifive_fe310_g000_prci;
}



/* --------------------- sifive_fu540_c000_l2 ------------ */


#define __METAL_DT_MAX_MEMORIES 5

__asm__ (".weak __metal_memory_table");
struct metal_memory *__metal_memory_table[] = {
					&__metal_dt_mem_rom_1000,
					&__metal_dt_mem_rom_10000,
					&__metal_dt_mem_itim_8000000,
					&__metal_dt_mem_dtim_80000000,
					&__metal_dt_mem_spi_10014000};

/* From uart@10013000 */
#define __METAL_DT_STDOUT_UART_HANDLE (&__metal_dt_uart_10013000.uart)

#define __METAL_DT_UART_10013000_HANDLE (&__metal_dt_uart_10013000.uart)

#define __METAL_DT_STDOUT_UART_BAUD 115200

/* From clint@2000000 */
#define __METAL_DT_RISCV_CLINT0_HANDLE (&__metal_dt_clint_2000000.controller)

#define __METAL_DT_CLINT_2000000_HANDLE (&__metal_dt_clint_2000000.controller)

#define __METAL_DT_MAX_HARTS 1

__asm__ (".weak __metal_cpu_table");
struct __metal_driver_cpu *__metal_cpu_table[] = {
					&__metal_dt_cpu_0};

/* From interrupt_controller@c000000 */
#define __METAL_DT_RISCV_PLIC0_HANDLE (&__metal_dt_interrupt_controller_c000000.controller)

#define __METAL_DT_INTERRUPT_CONTROLLER_C000000_HANDLE (&__metal_dt_interrupt_controller_c000000.controller)

#define __MEE_DT_MAX_GPIOS 1

__asm__ (".weak __metal_gpio_table");
struct __metal_driver_sifive_gpio0 *__metal_gpio_table[] = {
					&__metal_dt_gpio_10012000};

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
#define __METAL_DT_MAX_SPIS 1

__asm__ (".weak __metal_spi_table");
struct __metal_driver_sifive_spi0 *__metal_spi_table[] = {
					&__metal_dt_spi_10014000};

/* From test@12000 */
#define __METAL_DT_SHUTDOWN_HANDLE (&__metal_dt_test_12000.shutdown)

#define __METAL_DT_TEST_12000_HANDLE (&__metal_dt_test_12000.shutdown)

#define __METAL_DT_MAX_UARTS 2

__asm__ (".weak __metal_uart_table");
struct __metal_driver_sifive_uart0 *__metal_uart_table[] = {
					&__metal_dt_uart_10013000,
					&__metal_dt_uart_10023000};

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
