// See LICENSE for license details.

#ifndef _SIFIVE_PLATFORM_H
#define _SIFIVE_PLATFORM_H

// Some things missing from the official encoding.h
#define MCAUSE_INT         0x80000000
#define MCAUSE_CAUSE       0x7FFFFFFF

#include "sifive/const.h"
#include "sifive/devices/aon.h"
#include "sifive/devices/clint.h"
#include "sifive/devices/gpio.h"
#include "sifive/devices/plic.h"
#include "sifive/devices/pwm.h"
#include "sifive/devices/spi.h"
#include "sifive/devices/uart.h"

/****************************************************************************
 * Platform definitions
 *****************************************************************************/

#define TRAPVEC_TABLE_BASE_ADDR _AC(0x00001010,UL)
#define CLINT_BASE_ADDR _AC(0x02000000,UL)
#define PLIC_BASE_ADDR _AC(0x0C000000,UL)
#define AON_BASE_ADDR _AC(0x10000000,UL)
#define GPIO_BASE_ADDR _AC(0x10012000,UL)
#define UART0_BASE_ADDR _AC(0x10013000,UL)
#define SPI0_BASE_ADDR _AC(0x10014000,UL)
#define PWM0_BASE_ADDR _AC(0x10015000,UL)
#define UART1_BASE_ADDR _AC(0x10023000,UL)
#define SPI1_BASE_ADDR _AC(0x10024000,UL)
#define PWM1_BASE_ADDR _AC(0x10025000,UL)
#define SPI2_BASE_ADDR _AC(0x10034000,UL)
#define PWM2_BASE_ADDR _AC(0x10035000,UL)
#define SPI0_MMAP_ADDR _AC(0x20000000,UL)
#define MEM_BASE_ADDR _AC(0x80000000,UL)

#define IOF0_SPI1_MASK _AC(0x000007FC,UL)
#define IOF0_UART0_MASK _AC(0x00030000,UL)
#define IOF0_UART1_MASK _AC(0x03000000,UL)
#define IOF0_SPI2_MASK _AC(0xFC000000,UL)
#define IOF1_PWM0_MASK _AC(0x0000000F,UL)
#define IOF1_PWM2_MASK _AC(0x00003C00,UL)
#define IOF1_PWM1_MASK _AC(0x00780000,UL)

#define INT_RESERVED 0
#define INT_WDOGCMP 1
#define INT_RTCCMP 2
#define INT_UART0_BASE 3
#define INT_UART1_BASE 4
#define INT_SPI0_BASE 5
#define INT_SPI1_BASE 6
#define INT_SPI2_BASE 7
#define INT_GPIO_BASE 8
#define INT_PWM0_BASE 40
#define INT_PWM1_BASE 44
#define INT_PWM2_BASE 48

#define PLIC_NUM_INTERRUPTS 52
#define PLIC_NUM_PRIORITIES 7

#include "hifive1.h"

#endif /* _SIFIVE_PLATFORM_H */
