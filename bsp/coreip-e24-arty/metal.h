/* Copyright 2019 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */
/* ----------------------------------- */
/* [XXXXX] 21-05-2019 10-54-34        */
/* ----------------------------------- */

#ifndef ASSEMBLY

#include <metal/machine/platform.h>

#ifdef __METAL_MACHINE_MACROS

#ifndef MACROS_IF_COREIP_E24_ARTY__METAL_H
#define MACROS_IF_COREIP_E24_ARTY__METAL_H

#ifndef __METAL_CLINT_NUM_PARENTS
#define __METAL_CLINT_NUM_PARENTS 0
#endif
#ifndef __METAL_PLIC_SUBINTERRUPTS
#define __METAL_PLIC_SUBINTERRUPTS 0
#endif
#ifndef __METAL_PLIC_NUM_PARENTS
#define __METAL_PLIC_NUM_PARENTS 0
#endif
#define __METAL_CLIC_SUBINTERRUPTS 153

#ifndef __METAL_CLIC_SUBINTERRUPTS
#define __METAL_CLIC_SUBINTERRUPTS 0
#endif

#endif /* MACROS_IF_COREIP_E24_ARTY__METAL_H*/

#else /* ! __METAL_MACHINE_MACROS */

#ifndef MACROS_ELSE_COREIP_E24_ARTY__METAL_H
#define MACROS_ELSE_COREIP_E24_ARTY__METAL_H

#define METAL_MAX_CLINT_INTERRUPTS 0

#define __METAL_CLINT_NUM_PARENTS 0

#define __METAL_PLIC_SUBINTERRUPTS 0
#define METAL_MAX_PLIC_INTERRUPTS 0

#define __METAL_PLIC_NUM_PARENTS 0

#define __METAL_INTERRUPT_CONTROLLER_2000000_INTERRUPTS 3

#define __METAL_CLIC_SUBINTERRUPTS 153

#define METAL_MAX_CLIC_INTERRUPTS 3

#define __METAL_LOCAL_EXTERNAL_INTERRUPTS_0_INTERRUPTS 127

#define METAL_MAX_LOCAL_EXT_INTERRUPTS 127

#define __METAL_GLOBAL_EXTERNAL_INTERRUPTS_INTERRUPTS 4

#define METAL_MAX_GLOBAL_EXT_INTERRUPTS 4

#define __METAL_GPIO_20002000_INTERRUPTS 16

#define METAL_MAX_GPIO_INTERRUPTS 16

#define __METAL_SERIAL_20000000_INTERRUPTS 1

#define METAL_MAX_UART_INTERRUPTS 1


#include <metal/drivers/fixed-clock.h>
#include <metal/memory.h>
#include <metal/drivers/riscv,cpu.h>
#include <metal/pmp.h>
#include <metal/drivers/sifive,clic0.h>
#include <metal/drivers/sifive,local-external-interrupts0.h>
#include <metal/drivers/sifive,global-external-interrupts0.h>
#include <metal/drivers/sifive,gpio0.h>
#include <metal/drivers/sifive,gpio-buttons.h>
#include <metal/drivers/sifive,gpio-leds.h>
#include <metal/drivers/sifive,gpio-switches.h>
#include <metal/drivers/sifive,spi0.h>
#include <metal/drivers/sifive,test0.h>
#include <metal/drivers/sifive,uart0.h>

/* From clock@0 */
struct __metal_driver_fixed_clock __metal_dt_clock_0;

struct metal_memory __metal_dt_mem_sys_sram_0_80000000;

struct metal_memory __metal_dt_mem_sys_sram_1_80008000;

struct metal_memory __metal_dt_mem_spi_20004000;

/* From cpu@0 */
struct __metal_driver_cpu __metal_dt_cpu_0;

struct __metal_driver_riscv_cpu_intc __metal_dt_cpu_0_interrupt_controller;

struct metal_pmp __metal_dt_pmp;

/* From interrupt_controller@2000000 */
struct __metal_driver_sifive_clic0 __metal_dt_interrupt_controller_2000000;

/* From local_external_interrupts_0 */
struct __metal_driver_sifive_local_external_interrupts0 __metal_dt_local_external_interrupts_0;

/* From global_external_interrupts */
struct __metal_driver_sifive_global_external_interrupts0 __metal_dt_global_external_interrupts;

/* From gpio@20002000 */
struct __metal_driver_sifive_gpio0 __metal_dt_gpio_20002000;

/* From button@0 */
struct __metal_driver_sifive_gpio_button __metal_dt_button_0;

/* From button@1 */
struct __metal_driver_sifive_gpio_button __metal_dt_button_1;

/* From button@2 */
struct __metal_driver_sifive_gpio_button __metal_dt_button_2;

/* From button@3 */
struct __metal_driver_sifive_gpio_button __metal_dt_button_3;

/* From led@0red */
struct __metal_driver_sifive_gpio_led __metal_dt_led_0red;

/* From led@0green */
struct __metal_driver_sifive_gpio_led __metal_dt_led_0green;

/* From led@0blue */
struct __metal_driver_sifive_gpio_led __metal_dt_led_0blue;

/* From switch@0 */
struct __metal_driver_sifive_gpio_switch __metal_dt_switch_0;

/* From switch@1 */
struct __metal_driver_sifive_gpio_switch __metal_dt_switch_1;

/* From switch@2 */
struct __metal_driver_sifive_gpio_switch __metal_dt_switch_2;

/* From switch@3 */
struct __metal_driver_sifive_gpio_switch __metal_dt_switch_3;

/* From spi@20004000 */
struct __metal_driver_sifive_spi0 __metal_dt_spi_20004000;

/* From teststatus@4000 */
struct __metal_driver_sifive_test0 __metal_dt_teststatus_4000;

/* From serial@20000000 */
struct __metal_driver_sifive_uart0 __metal_dt_serial_20000000;



/* --------------------- fixed_clock ------------ */
static inline unsigned long __metal_driver_fixed_clock_rate(struct metal_clock *clock)
{
	if ((uintptr_t)clock == (uintptr_t)&__metal_dt_clock_0) {
		return METAL_FIXED_CLOCK_0_CLOCK_FREQUENCY;
	}
	else {
		return 0;
	}
}



/* --------------------- fixed_factor_clock ------------ */


/* --------------------- sifive_clint0 ------------ */


/* --------------------- cpu ------------ */
static inline int __metal_driver_cpu_timebase(struct metal_cpu *cpu)
{
	if ((uintptr_t)cpu == (uintptr_t)&__metal_dt_cpu_0) {
		return 32000000;
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
	else {
		return NULL;
	}
}

static inline int __metal_driver_cpu_num_pmp_regions(struct metal_cpu *cpu)
{
	if ((uintptr_t)cpu == (uintptr_t)&__metal_dt_cpu_0) {
		return 4;
	}
	else {
		return 0;
	}
}



/* --------------------- sifive_plic0 ------------ */


/* --------------------- sifive_clic0 ------------ */
static inline unsigned long __metal_driver_sifive_clic0_control_base(struct metal_interrupt *controller)
{
	if ((uintptr_t)controller == (uintptr_t)&__metal_dt_interrupt_controller_2000000) {
		return METAL_SIFIVE_CLIC0_2000000_BASE_ADDRESS;
	}
	else {
		return 0;
	}
}

static inline unsigned long __metal_driver_sifive_clic0_control_size(struct metal_interrupt *controller)
{
	if ((uintptr_t)controller == (uintptr_t)&__metal_dt_interrupt_controller_2000000) {
		return METAL_SIFIVE_CLIC0_2000000_SIZE;
	}
	else {
		return 0;
	}
}

static inline int __metal_driver_sifive_clic0_num_interrupts(struct metal_interrupt *controller)
{
	if ((uintptr_t)controller == (uintptr_t)&__metal_dt_interrupt_controller_2000000) {
		return METAL_MAX_CLIC_INTERRUPTS;
	}
	else {
		return 0;
	}
}

static inline struct metal_interrupt * __metal_driver_sifive_clic0_interrupt_parent(struct metal_interrupt *controller)
{
	if ((uintptr_t)controller == (uintptr_t)&__metal_dt_interrupt_controller_2000000) {
		return (struct metal_interrupt *)&__metal_dt_cpu_0_interrupt_controller.controller;
	}
	else {
		return NULL;
	}
}

static inline int __metal_driver_sifive_clic0_interrupt_lines(struct metal_interrupt *controller, int idx)
{
	if (idx == 0) {
		return 3;
	}
	else if (idx == 1) {
		return 3;
	}
	else if (idx == 2) {
		return 7;
	}
	else if (idx == 3) {
		return 11;
	}
	else {
		return 0;
	}
}

static inline int __metal_driver_sifive_clic0_max_levels(struct metal_interrupt *controller)
{
	if ((uintptr_t)controller == (uintptr_t)&__metal_dt_interrupt_controller_2000000) {
		return METAL_SIFIVE_CLIC0_2000000_SIFIVE_NUMLEVELS;
	}
	else {
		return 0;
	}
}

static inline int __metal_driver_sifive_clic0_num_subinterrupts(struct metal_interrupt *controller)
{
	if ((uintptr_t)controller == (uintptr_t)&__metal_dt_interrupt_controller_2000000) {
		return METAL_SIFIVE_CLIC0_2000000_SIFIVE_NUMINTS;
	}
	else {
		return 0;
	}
}

static inline int __metal_driver_sifive_clic0_num_intbits(struct metal_interrupt *controller)
{
	if ((uintptr_t)controller == (uintptr_t)&__metal_dt_interrupt_controller_2000000) {
		return METAL_SIFIVE_CLIC0_2000000_SIFIVE_NUMINTBITS;
	}
	else {
		return 0;
	}
}



/* --------------------- sifive_local_external_interrupts0 ------------ */
static inline struct metal_interrupt * __metal_driver_sifive_local_external_interrupts0_interrupt_parent(struct metal_interrupt *controller)
{
	if ((uintptr_t)controller == (uintptr_t)&__metal_dt_local_external_interrupts_0) {
		return (struct metal_interrupt *)&__metal_dt_interrupt_controller_2000000.controller;
	}
	else {
		return NULL;
	}
}

static inline int __metal_driver_sifive_local_external_interrupts0_num_interrupts(struct metal_interrupt *controller)
{
	if ((uintptr_t)controller == (uintptr_t)&__metal_dt_local_external_interrupts_0) {
		return METAL_MAX_LOCAL_EXT_INTERRUPTS;
	}
	else {
		return 0;
	}
}

static inline int __metal_driver_sifive_local_external_interrupts0_interrupt_lines(struct metal_interrupt *controller, int idx)
{
	if (idx == 0) {
		return 26;
	}
	else if (idx == 1) {
		return 27;
	}
	else if (idx == 2) {
		return 28;
	}
	else if (idx == 3) {
		return 29;
	}
	else if (idx == 4) {
		return 30;
	}
	else if (idx == 5) {
		return 31;
	}
	else if (idx == 6) {
		return 32;
	}
	else if (idx == 7) {
		return 33;
	}
	else if (idx == 8) {
		return 34;
	}
	else if (idx == 9) {
		return 35;
	}
	else if (idx == 10) {
		return 36;
	}
	else if (idx == 11) {
		return 37;
	}
	else if (idx == 12) {
		return 38;
	}
	else if (idx == 13) {
		return 39;
	}
	else if (idx == 14) {
		return 40;
	}
	else if (idx == 15) {
		return 41;
	}
	else if (idx == 16) {
		return 42;
	}
	else if (idx == 17) {
		return 43;
	}
	else if (idx == 18) {
		return 44;
	}
	else if (idx == 19) {
		return 45;
	}
	else if (idx == 20) {
		return 46;
	}
	else if (idx == 21) {
		return 47;
	}
	else if (idx == 22) {
		return 48;
	}
	else if (idx == 23) {
		return 49;
	}
	else if (idx == 24) {
		return 50;
	}
	else if (idx == 25) {
		return 51;
	}
	else if (idx == 26) {
		return 52;
	}
	else if (idx == 27) {
		return 53;
	}
	else if (idx == 28) {
		return 54;
	}
	else if (idx == 29) {
		return 55;
	}
	else if (idx == 30) {
		return 56;
	}
	else if (idx == 31) {
		return 57;
	}
	else if (idx == 32) {
		return 58;
	}
	else if (idx == 33) {
		return 59;
	}
	else if (idx == 34) {
		return 60;
	}
	else if (idx == 35) {
		return 61;
	}
	else if (idx == 36) {
		return 62;
	}
	else if (idx == 37) {
		return 63;
	}
	else if (idx == 38) {
		return 64;
	}
	else if (idx == 39) {
		return 65;
	}
	else if (idx == 40) {
		return 66;
	}
	else if (idx == 41) {
		return 67;
	}
	else if (idx == 42) {
		return 68;
	}
	else if (idx == 43) {
		return 69;
	}
	else if (idx == 44) {
		return 70;
	}
	else if (idx == 45) {
		return 71;
	}
	else if (idx == 46) {
		return 72;
	}
	else if (idx == 47) {
		return 73;
	}
	else if (idx == 48) {
		return 74;
	}
	else if (idx == 49) {
		return 75;
	}
	else if (idx == 50) {
		return 76;
	}
	else if (idx == 51) {
		return 77;
	}
	else if (idx == 52) {
		return 78;
	}
	else if (idx == 53) {
		return 79;
	}
	else if (idx == 54) {
		return 80;
	}
	else if (idx == 55) {
		return 81;
	}
	else if (idx == 56) {
		return 82;
	}
	else if (idx == 57) {
		return 83;
	}
	else if (idx == 58) {
		return 84;
	}
	else if (idx == 59) {
		return 85;
	}
	else if (idx == 60) {
		return 86;
	}
	else if (idx == 61) {
		return 87;
	}
	else if (idx == 62) {
		return 88;
	}
	else if (idx == 63) {
		return 89;
	}
	else if (idx == 64) {
		return 90;
	}
	else if (idx == 65) {
		return 91;
	}
	else if (idx == 66) {
		return 92;
	}
	else if (idx == 67) {
		return 93;
	}
	else if (idx == 68) {
		return 94;
	}
	else if (idx == 69) {
		return 95;
	}
	else if (idx == 70) {
		return 96;
	}
	else if (idx == 71) {
		return 97;
	}
	else if (idx == 72) {
		return 98;
	}
	else if (idx == 73) {
		return 99;
	}
	else if (idx == 74) {
		return 100;
	}
	else if (idx == 75) {
		return 101;
	}
	else if (idx == 76) {
		return 102;
	}
	else if (idx == 77) {
		return 103;
	}
	else if (idx == 78) {
		return 104;
	}
	else if (idx == 79) {
		return 105;
	}
	else if (idx == 80) {
		return 106;
	}
	else if (idx == 81) {
		return 107;
	}
	else if (idx == 82) {
		return 108;
	}
	else if (idx == 83) {
		return 109;
	}
	else if (idx == 84) {
		return 110;
	}
	else if (idx == 85) {
		return 111;
	}
	else if (idx == 86) {
		return 112;
	}
	else if (idx == 87) {
		return 113;
	}
	else if (idx == 88) {
		return 114;
	}
	else if (idx == 89) {
		return 115;
	}
	else if (idx == 90) {
		return 116;
	}
	else if (idx == 91) {
		return 117;
	}
	else if (idx == 92) {
		return 118;
	}
	else if (idx == 93) {
		return 119;
	}
	else if (idx == 94) {
		return 120;
	}
	else if (idx == 95) {
		return 121;
	}
	else if (idx == 96) {
		return 122;
	}
	else if (idx == 97) {
		return 123;
	}
	else if (idx == 98) {
		return 124;
	}
	else if (idx == 99) {
		return 125;
	}
	else if (idx == 100) {
		return 126;
	}
	else if (idx == 101) {
		return 127;
	}
	else if (idx == 102) {
		return 128;
	}
	else if (idx == 103) {
		return 129;
	}
	else if (idx == 104) {
		return 130;
	}
	else if (idx == 105) {
		return 131;
	}
	else if (idx == 106) {
		return 132;
	}
	else if (idx == 107) {
		return 133;
	}
	else if (idx == 108) {
		return 134;
	}
	else if (idx == 109) {
		return 135;
	}
	else if (idx == 110) {
		return 136;
	}
	else if (idx == 111) {
		return 137;
	}
	else if (idx == 112) {
		return 138;
	}
	else if (idx == 113) {
		return 139;
	}
	else if (idx == 114) {
		return 140;
	}
	else if (idx == 115) {
		return 141;
	}
	else if (idx == 116) {
		return 142;
	}
	else if (idx == 117) {
		return 143;
	}
	else if (idx == 118) {
		return 144;
	}
	else if (idx == 119) {
		return 145;
	}
	else if (idx == 120) {
		return 146;
	}
	else if (idx == 121) {
		return 147;
	}
	else if (idx == 122) {
		return 148;
	}
	else if (idx == 123) {
		return 149;
	}
	else if (idx == 124) {
		return 150;
	}
	else if (idx == 125) {
		return 151;
	}
	else if (idx == 126) {
		return 152;
	}
	else {
		return 0;
	}
}



/* --------------------- sifive_global_external_interrupts0 ------------ */
static inline int __metal_driver_sifive_global_external_interrupts0_init_done()
{
		return 0;
}

static inline struct metal_interrupt * __metal_driver_sifive_global_external_interrupts0_interrupt_parent(struct metal_interrupt *controller)
{
	if ((uintptr_t)controller == (uintptr_t)&__metal_dt_global_external_interrupts) {
		return (struct metal_interrupt *)&__metal_dt_interrupt_controller_2000000.controller;
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
		return 22;
	}
	else if (idx == 1) {
		return 23;
	}
	else if (idx == 2) {
		return 24;
	}
	else if (idx == 3) {
		return 25;
	}
	else {
		return 0;
	}
}



/* --------------------- sifive_gpio0 ------------ */
static inline unsigned long __metal_driver_sifive_gpio0_base(struct metal_gpio *gpio)
{
	if ((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_20002000) {
		return METAL_SIFIVE_GPIO0_20002000_BASE_ADDRESS;
	}
	else {
		return 0;
	}
}

static inline unsigned long __metal_driver_sifive_gpio0_size(struct metal_gpio *gpio)
{
	if ((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_20002000) {
		return METAL_SIFIVE_GPIO0_20002000_SIZE;
	}
	else {
		return 0;
	}
}

static inline int __metal_driver_sifive_gpio0_num_interrupts(struct metal_gpio *gpio)
{
	if ((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_20002000) {
		return METAL_MAX_GPIO_INTERRUPTS;
	}
	else {
		return 0;
	}
}

static inline struct metal_interrupt * __metal_driver_sifive_gpio0_interrupt_parent(struct metal_gpio *gpio)
{
	if ((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_20002000) {
		return (struct metal_interrupt *)&__metal_dt_interrupt_controller_2000000.controller;
	}
	else {
		return 0;
	}
}

static inline int __metal_driver_sifive_gpio0_interrupt_lines(struct metal_gpio *gpio, int idx)
{
	if (((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_20002000) && (idx == 0)) {
		return 0;
	}
	else if ((((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_20002000) && (idx == 1))) {
		return 1;
	}
	else if ((((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_20002000) && (idx == 2))) {
		return 2;
	}
	else if ((((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_20002000) && (idx == 3))) {
		return 3;
	}
	else if ((((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_20002000) && (idx == 4))) {
		return 4;
	}
	else if ((((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_20002000) && (idx == 5))) {
		return 5;
	}
	else if ((((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_20002000) && (idx == 6))) {
		return 6;
	}
	else if ((((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_20002000) && (idx == 7))) {
		return 7;
	}
	else if ((((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_20002000) && (idx == 8))) {
		return 8;
	}
	else if ((((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_20002000) && (idx == 9))) {
		return 9;
	}
	else if ((((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_20002000) && (idx == 10))) {
		return 10;
	}
	else if ((((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_20002000) && (idx == 11))) {
		return 11;
	}
	else if ((((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_20002000) && (idx == 12))) {
		return 12;
	}
	else if ((((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_20002000) && (idx == 13))) {
		return 13;
	}
	else if ((((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_20002000) && (idx == 14))) {
		return 14;
	}
	else if ((((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_20002000) && (idx == 15))) {
		return 15;
	}
	else {
		return 0;
	}
}



/* --------------------- sifive_gpio_button ------------ */
static inline struct metal_gpio * __metal_driver_sifive_gpio_button_gpio(struct metal_button *button)
{
	if ((uintptr_t)button == (uintptr_t)&__metal_dt_button_0) {
		return (struct metal_gpio *)&__metal_dt_gpio_20002000;
	}
	else if ((uintptr_t)button == (uintptr_t)&__metal_dt_button_1) {
		return (struct metal_gpio *)&__metal_dt_gpio_20002000;
	}
	else if ((uintptr_t)button == (uintptr_t)&__metal_dt_button_2) {
		return (struct metal_gpio *)&__metal_dt_gpio_20002000;
	}
	else if ((uintptr_t)button == (uintptr_t)&__metal_dt_button_3) {
		return (struct metal_gpio *)&__metal_dt_gpio_20002000;
	}
	else {
		return NULL;
	}
}

static inline int __metal_driver_sifive_gpio_button_pin(struct metal_button *button)
{
	if ((uintptr_t)button == (uintptr_t)&__metal_dt_button_0) {
		return 4;
	}
	else if ((uintptr_t)button == (uintptr_t)&__metal_dt_button_1) {
		return 5;
	}
	else if ((uintptr_t)button == (uintptr_t)&__metal_dt_button_2) {
		return 6;
	}
	else if ((uintptr_t)button == (uintptr_t)&__metal_dt_button_3) {
		return 7;
	}
	else {
		return 0;
	}
}

static inline struct metal_interrupt * __metal_driver_sifive_gpio_button_interrupt_controller(struct metal_button *button)
{
	if ((uintptr_t)button == (uintptr_t)&__metal_dt_button_0) {
		return (struct metal_interrupt *)&__metal_dt_local_external_interrupts_0;
	}
	else if ((uintptr_t)button == (uintptr_t)&__metal_dt_button_1) {
		return (struct metal_interrupt *)&__metal_dt_local_external_interrupts_0;
	}
	else if ((uintptr_t)button == (uintptr_t)&__metal_dt_button_2) {
		return (struct metal_interrupt *)&__metal_dt_local_external_interrupts_0;
	}
	else if ((uintptr_t)button == (uintptr_t)&__metal_dt_button_3) {
		return (struct metal_interrupt *)&__metal_dt_local_external_interrupts_0;
	}
	else {
		return NULL;
	}
}

static inline int __metal_driver_sifive_gpio_button_interrupt_line(struct metal_button *button)
{
	if ((uintptr_t)button == (uintptr_t)&__metal_dt_button_0) {
		return 20;
	}
	else if ((uintptr_t)button == (uintptr_t)&__metal_dt_button_1) {
		return 21;
	}
	else if ((uintptr_t)button == (uintptr_t)&__metal_dt_button_2) {
		return 22;
	}
	else if ((uintptr_t)button == (uintptr_t)&__metal_dt_button_3) {
		return 23;
	}
	else {
		return 0;
	}
}

static inline char * __metal_driver_sifive_gpio_button_label(struct metal_button *button)
{
	if ((uintptr_t)button == (uintptr_t)&__metal_dt_button_0) {
		return "BTN0";
	}
	else if ((uintptr_t)button == (uintptr_t)&__metal_dt_button_1) {
		return "BTN1";
	}
	else if ((uintptr_t)button == (uintptr_t)&__metal_dt_button_2) {
		return "BTN2";
	}
	else if ((uintptr_t)button == (uintptr_t)&__metal_dt_button_3) {
		return "BTN3";
	}
	else {
		return "";
	}
}



/* --------------------- sifive_gpio_led ------------ */
static inline struct metal_gpio * __metal_driver_sifive_gpio_led_gpio(struct metal_led *led)
{
	if ((uintptr_t)led == (uintptr_t)&__metal_dt_led_0red) {
		return (struct metal_gpio *)&__metal_dt_gpio_20002000;
	}
	else if ((uintptr_t)led == (uintptr_t)&__metal_dt_led_0green) {
		return (struct metal_gpio *)&__metal_dt_gpio_20002000;
	}
	else if ((uintptr_t)led == (uintptr_t)&__metal_dt_led_0blue) {
		return (struct metal_gpio *)&__metal_dt_gpio_20002000;
	}
	else {
		return NULL;
	}
}

static inline int __metal_driver_sifive_gpio_led_pin(struct metal_led *led)
{
	if ((uintptr_t)led == (uintptr_t)&__metal_dt_led_0red) {
		return 0;
	}
	else if ((uintptr_t)led == (uintptr_t)&__metal_dt_led_0green) {
		return 1;
	}
	else if ((uintptr_t)led == (uintptr_t)&__metal_dt_led_0blue) {
		return 2;
	}
	else {
		return 0;
	}
}

static inline char * __metal_driver_sifive_gpio_led_label(struct metal_led *led)
{
	if ((uintptr_t)led == (uintptr_t)&__metal_dt_led_0red) {
		return "LD0red";
	}
	else if ((uintptr_t)led == (uintptr_t)&__metal_dt_led_0green) {
		return "LD0green";
	}
	else if ((uintptr_t)led == (uintptr_t)&__metal_dt_led_0blue) {
		return "LD0blue";
	}
	else {
		return "";
	}
}



/* --------------------- sifive_gpio_switch ------------ */
static inline struct metal_gpio * __metal_driver_sifive_gpio_switch_gpio(struct metal_switch *flip)
{
		return NULL;
}

static inline int __metal_driver_sifive_gpio_switch_pin(struct metal_switch *flip)
{
		return 0;
}

static inline struct metal_interrupt * __metal_driver_sifive_gpio_switch_interrupt_controller(struct metal_switch *flip)
{
	if ((uintptr_t)flip == (uintptr_t)&__metal_dt_switch_0) {
		return (struct metal_interrupt *)&__metal_dt_local_external_interrupts_0;
	}
	else if ((uintptr_t)flip == (uintptr_t)&__metal_dt_switch_1) {
		return (struct metal_interrupt *)&__metal_dt_local_external_interrupts_0;
	}
	else if ((uintptr_t)flip == (uintptr_t)&__metal_dt_switch_2) {
		return (struct metal_interrupt *)&__metal_dt_local_external_interrupts_0;
	}
	else if ((uintptr_t)flip == (uintptr_t)&__metal_dt_switch_3) {
		return (struct metal_interrupt *)&__metal_dt_local_external_interrupts_0;
	}
	else {
		return NULL;
	}
}

static inline int __metal_driver_sifive_gpio_switch_interrupt_line(struct metal_switch *flip)
{
	if ((uintptr_t)flip == (uintptr_t)&__metal_dt_switch_0) {
		return 16;
	}
	else if ((uintptr_t)flip == (uintptr_t)&__metal_dt_switch_1) {
		return 17;
	}
	else if ((uintptr_t)flip == (uintptr_t)&__metal_dt_switch_2) {
		return 18;
	}
	else if ((uintptr_t)flip == (uintptr_t)&__metal_dt_switch_3) {
		return 19;
	}
	else {
		return 0;
	}
}

static inline char * __metal_driver_sifive_gpio_switch_label(struct metal_switch *flip)
{
	if ((uintptr_t)flip == (uintptr_t)&__metal_dt_switch_0) {
		return "SW0";
	}
	else if ((uintptr_t)flip == (uintptr_t)&__metal_dt_switch_1) {
		return "SW1";
	}
	else if ((uintptr_t)flip == (uintptr_t)&__metal_dt_switch_2) {
		return "SW2";
	}
	else if ((uintptr_t)flip == (uintptr_t)&__metal_dt_switch_3) {
		return "SW3";
	}
	else {
		return "";
	}
}



/* --------------------- sifive_spi0 ------------ */
static inline unsigned long __metal_driver_sifive_spi0_control_base(struct metal_spi *spi)
{
	if ((uintptr_t)spi == (uintptr_t)&__metal_dt_spi_20004000) {
		return METAL_SIFIVE_SPI0_20004000_BASE_ADDRESS;
	}
	else {
		return 0;
	}
}

static inline unsigned long __metal_driver_sifive_spi0_control_size(struct metal_spi *spi)
{
	if ((uintptr_t)spi == (uintptr_t)&__metal_dt_spi_20004000) {
		return METAL_SIFIVE_SPI0_20004000_SIZE;
	}
	else {
		return 0;
	}
}

static inline struct metal_clock * __metal_driver_sifive_spi0_clock(struct metal_spi *spi)
{
		return NULL;
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
	if ((uintptr_t)uart == (uintptr_t)&__metal_dt_serial_20000000) {
		return METAL_SIFIVE_UART0_20000000_BASE_ADDRESS;
	}
	else {
		return 0;
	}
}

static inline unsigned long __metal_driver_sifive_uart0_control_size(struct metal_uart *uart)
{
	if ((uintptr_t)uart == (uintptr_t)&__metal_dt_serial_20000000) {
		return METAL_SIFIVE_UART0_20000000_SIZE;
	}
	else {
		return 0;
	}
}

static inline int __metal_driver_sifive_uart0_num_interrupts(struct metal_uart *uart)
{
	if ((uintptr_t)uart == (uintptr_t)&__metal_dt_serial_20000000) {
		return METAL_MAX_UART_INTERRUPTS;
	}
	else {
		return 0;
	}
}

static inline struct metal_interrupt * __metal_driver_sifive_uart0_interrupt_parent(struct metal_uart *uart)
{
	if ((uintptr_t)uart == (uintptr_t)&__metal_dt_serial_20000000) {
		return (struct metal_interrupt *)&__metal_dt_interrupt_controller_2000000.controller;
	}
	else {
		return NULL;
	}
}

static inline int __metal_driver_sifive_uart0_interrupt_line(struct metal_uart *uart)
{
		return 16;
}

static inline struct metal_clock * __metal_driver_sifive_uart0_clock(struct metal_uart *uart)
{
		return (struct metal_clock *)&__metal_dt_clock_0.clock;
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


#define __METAL_DT_MAX_MEMORIES 3

asm (".weak __metal_memory_table");
struct metal_memory *__metal_memory_table[] = {
					&__metal_dt_mem_sys_sram_0_80000000,
					&__metal_dt_mem_sys_sram_1_80008000,
					&__metal_dt_mem_spi_20004000};

/* From serial@20000000 */
#define __METAL_DT_STDOUT_UART_HANDLE (&__metal_dt_serial_20000000.uart)

#define __METAL_DT_SERIAL_20000000_HANDLE (&__metal_dt_serial_20000000.uart)

#define __METAL_DT_STDOUT_UART_BAUD 115200

#define __METAL_DT_MAX_HARTS 1

asm (".weak __metal_cpu_table");
struct __metal_driver_cpu *__metal_cpu_table[] = {
					&__metal_dt_cpu_0};

#define __METAL_DT_PMP_HANDLE (&__metal_dt_pmp)

/* From interrupt_controller@2000000 */
#define __METAL_DT_SIFIVE_CLIC0_HANDLE (&__metal_dt_interrupt_controller_2000000.controller)

#define __METAL_DT_INTERRUPT_CONTROLLER_2000000_HANDLE (&__metal_dt_interrupt_controller_2000000.controller)

/* From local_external_interrupts_0 */
#define __METAL_DT_SIFIVE_LOCAL_EXINTR0_HANDLE (&__metal_dt_local_external_interrupts_0.irc)

#define __METAL_DT_LOCAL_EXTERNAL_INTERRUPTS_0_HANDLE (&__metal_dt_local_external_interrupts_0.irc)

/* From global_external_interrupts */
#define __METAL_DT_SIFIVE_GLOBAL_EXINTR0_HANDLE (&__metal_dt_global_external_interrupts.irc)

#define __METAL_DT_GLOBAL_EXTERNAL_INTERRUPTS_HANDLE (&__metal_dt_global_external_interrupts.irc)

#define __MEE_DT_MAX_GPIOS 1

asm (".weak __metal_gpio_table");
struct __metal_driver_sifive_gpio0 *__metal_gpio_table[] = {
					&__metal_dt_gpio_20002000};

#define __METAL_DT_MAX_BUTTONS 4

asm (".weak __metal_button_table");
struct __metal_driver_sifive_gpio_button *__metal_button_table[] = {
					&__metal_dt_button_0,
					&__metal_dt_button_1,
					&__metal_dt_button_2,
					&__metal_dt_button_3};

#define __METAL_DT_MAX_LEDS 3

asm (".weak __metal_led_table");
struct __metal_driver_sifive_gpio_led *__metal_led_table[] = {
					&__metal_dt_led_0red,
					&__metal_dt_led_0green,
					&__metal_dt_led_0blue};

#define __METAL_DT_MAX_SWITCHES 4

asm (".weak __metal_switch_table");
struct __metal_driver_sifive_gpio_switch *__metal_switch_table[] = {
					&__metal_dt_switch_0,
					&__metal_dt_switch_1,
					&__metal_dt_switch_2,
					&__metal_dt_switch_3};

#define __METAL_DT_MAX_SPIS 1

asm (".weak __metal_spi_table");
struct __metal_driver_sifive_spi0 *__metal_spi_table[] = {
					&__metal_dt_spi_20004000};

/* From teststatus@4000 */
#define __METAL_DT_SHUTDOWN_HANDLE (&__metal_dt_teststatus_4000.shutdown)

#define __METAL_DT_TESTSTATUS_4000_HANDLE (&__metal_dt_teststatus_4000.shutdown)

#endif /* MACROS_ELSE_COREIP_E24_ARTY__METAL_H*/

#endif /* ! __METAL_MACHINE_MACROS */

#endif /* ! ASSEMBLY */
