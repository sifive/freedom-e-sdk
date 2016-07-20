// See LICENSE for license details.

#ifndef SIFIVE_SHARED_H
#define SIFIVE_SHARED_H

#include "uart.h"
#include "gpio.h"
#include "plic.h"

// Some things missing from the official encoding.h
#define MCAUSE_INT         0x80000000
#define MCAUSE_CAUSE       0x7FFFFFFF

/****************************************************************************
 * Platform definitions
 *****************************************************************************/

#define MTIMECMP_BASE_ADDR     0x44004000UL
#define MTIME_ADDR             0x4400BFF8UL
#define PLIC_BASE_ADDR         0x40000000UL
#define UART_BASE_ADDR         0x48000000UL
#define GPIO_BASE_ADDR         0x48002000UL
#define SPI_BASE_ADDR          0x48001000UL


/****************************************************************************
 * Clock Parameters
 *****************************************************************************/

#define RTC_PRESCALER 100
#define CLOCK_FREQUENCY 62500000

/****************************************************************************
 * GPIO Connections
 *****************************************************************************/


// Each of these OFFSETS holds 4 bits.

#define RED_LEDS_OFFSET   0
#define GREEN_LEDS_OFFSET 4
#define BLUE_LEDS_OFFSET  8
#define JA_OUT_OFFSET     12 // JA Pins 1-4 are outputs.

#define BUTTONS_OFFSET    16
#define SWITCHES_OFFSET   20
#define JA_IN_OFFSET      24 // JA Pins 7-10 are inputs.
// reserved input offset   38 // Tied to zero.

/****************************************************************************
 * External Interrupts handled by PLIC.
 *****************************************************************************/

// Interrupt devices
#define INT_DEVICE_BUTTON_0 1
#define INT_DEVICE_BUTTON_1 2
#define INT_DEVICE_BUTTON_2 3
#define INT_DEVICE_BUTTON_3 4

#define INT_DEVICE_JA_7 5
#define INT_DEVICE_JA_8 6
#define INT_DEVICE_JA_9 7
#define INT_DEVICE_JA_10 8


// Setting these correctly makes the initialization scripts
// run faster.
#define PLIC_NUM_SOURCES 31
#define PLIC_NUM_PRIORITIES 0

void write_hex(int fd, uint32_t hex);

#endif
