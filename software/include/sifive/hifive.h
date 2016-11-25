// See LICENSE for license details.

#ifndef SIFIVE_HIFIVE_H
#define SIFIVE_HIFIVE_H

/****************************************************************************
 * Clock Parameters
 *****************************************************************************/

#define CLOCK_FREQUENCY 62500000

/****************************************************************************
 * GPIO Connections
 *****************************************************************************/

// These are the GPIO bit offsets for the RGB LED on HiFive1 Board.
// These are also mapped to RGB LEDs on the Freedom E300 Arty
// FPGA
// Dev Kit.

#define RED_LED_OFFSET   22
#define GREEN_LED_OFFSET 19
#define BLUE_LED_OFFSET  21

// These are the GPIO bit offsets for the differen digital pins
// on the headers for both the HiFive1 Board and the Freedom E300 Arty FPGA Dev Kit.
#define PIN_0_OFFSET 16
#define PIN_1_OFFSET 17
#define PIN_2_OFFSET 18
#define PIN_3_OFFSET 19
#define PIN_4_OFFSET 20
#define PIN_5_OFFSET 21
#define PIN_6_OFFSET 22
#define PIN_7_OFFSET 23
#define PIN_8_OFFSET 0
#define PIN_9_OFFSET 1
#define PIN_10_OFFSET 2
#define PIN_11_OFFSET 3
#define PIN_12_OFFSET 4
#define PIN_13_OFFSET 5
//#define PIN_14_OFFSET 8 //This pin is not connected on either board.
#define PIN_15_OFFSET 9
#define PIN_16_OFFSET 10
#define PIN_17_OFFSET 11
#define PIN_18_OFFSET 12
#define PIN_19_OFFSET 13


// These defines apply only to the
// Freedom E300 Arty FPGA Dev Kit
#define BUTTON_0_OFFSET 15
#define BUTTON_1_OFFSET 30
#define BUTTON_2_OFFSET 31
// On the Freedeom E300 Arty FGPA Dev Kit,
// Button 3 drives the "Digital Wakeup" pin,
// Equivalent to the "WAKE" button on the HiFive1 Board.
// These are mapped onto the Freedom E300 Arty FGPA Dev Kit
// to provide an additional UART RX/TX port.
#define JA_0_OFFSET    25 
#define JA_1_1_OFFSET  24

void write_hex(int fd, uint32_t hex);

#endif
