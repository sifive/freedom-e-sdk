// See LICENSE for license details.

#ifndef _SIFIVE_PLATFORM_H
#define _SIFIVE_PLATFORM_H

#include "sifive/const.h"
#include "sifive/riscv_test_defaults.h"
#include "sifive/devices/aon.h"
#include "sifive/devices/clint.h"
#include "sifive/devices/freedome300prci.h"
#include "sifive/devices/gpio.h"
#include "sifive/devices/i2c.h"
#include "sifive/devices/otp.h"
#include "sifive/devices/plic.h"
#include "sifive/devices/pwm.h"
#include "sifive/devices/spi.h"
#include "sifive/devices/uart.h"

 // Some things missing from the official encoding.h
#if __riscv_xlen == 32
  #define MCAUSE_INT         0x80000000UL
  #define MCAUSE_CAUSE       0x000003FFUL
#else
   #define MCAUSE_INT         0x8000000000000000UL
   #define MCAUSE_CAUSE       0x00000000000003FFUL
#endif

/****************************************************************************
 * Platform definitions
 *****************************************************************************/

// CPU info
#define JEDEC_ID_SIFIVE 1161
#define CSR_SIFIVE_CHICKEN 1985
#define CSR_SIFIVE_INSTID0 4092
#define NUM_CORES 1
#define MAX_HART_ID 0
#define GLOBAL_INT_SIZE 52
#define GLOBAL_INT_MAX_PRIORITY 7
#define RTC_FREQUENCY_HZ _AC(32768,UL)
#define RTC_PERIOD_NS _AC(30517,UL)

// Memory map
#define AON_CTRL_ADDR _AC(0x10000000,UL)
#define AON_CTRL_SIZE _AC(0x1000,UL)
#define CLINT_CTRL_ADDR _AC(0x2000000,UL)
#define CLINT_CTRL_SIZE _AC(0x10000,UL)
#define DEBUG_CTRL_ADDR _AC(0x0,UL)
#define DEBUG_CTRL_SIZE _AC(0x1000,UL)
#define DTIM_MEM_ADDR _AC(0x80000000,UL)
#define DTIM_MEM_SIZE _AC(0x4000,UL)
#define ERROR_MEM_ADDR _AC(0x3000,UL)
#define ERROR_MEM_SIZE _AC(0x1000,UL)
#define FREEDOME300PRCI_CTRL_ADDR _AC(0x10008000,UL)
#define FREEDOME300PRCI_CTRL_SIZE _AC(0x1000,UL)
#define GPIO_CTRL_ADDR _AC(0x10012000,UL)
#define GPIO_CTRL_SIZE _AC(0x1000,UL)
#define I2C_CTRL_ADDR _AC(0x10016000,UL)
#define I2C_CTRL_SIZE _AC(0x1000,UL)
#define ITIM_MEM_ADDR _AC(0x8000000,UL)
#define ITIM_MEM_SIZE _AC(0x2000,UL)
#define MASKROM_MEM_ADDR _AC(0x10000,UL)
#define MASKROM_MEM_SIZE _AC(0x2000,UL)
#define MODESELECT_MEM_ADDR _AC(0x1000,UL)
#define MODESELECT_MEM_SIZE _AC(0x1000,UL)
#define OTP_CTRL_ADDR _AC(0x10010000,UL)
#define OTP_CTRL_SIZE _AC(0x1000,UL)
#define OTP_MEM_ADDR _AC(0x20000,UL)
#define OTP_MEM_SIZE _AC(0x2000,UL)
#define PLIC_CTRL_ADDR _AC(0xc000000,UL)
#define PLIC_CTRL_SIZE _AC(0x4000000,UL)
#define PWM0_CTRL_ADDR _AC(0x10015000,UL)
#define PWM0_CTRL_SIZE _AC(0x1000,UL)
#define PWM1_CTRL_ADDR _AC(0x10025000,UL)
#define PWM1_CTRL_SIZE _AC(0x1000,UL)
#define PWM2_CTRL_ADDR _AC(0x10035000,UL)
#define PWM2_CTRL_SIZE _AC(0x1000,UL)
#ifndef PWM_CTRL_ADDR
  #define PWM_CTRL_ADDR PWM0_CTRL_ADDR
#endif
#ifndef PWM_CTRL_SIZE
  #define PWM_CTRL_SIZE PWM0_CTRL_SIZE
#endif
#define SPI0_CTRL_ADDR _AC(0x10014000,UL)
#define SPI0_CTRL_SIZE _AC(0x1000,UL)
#define SPI0_MEM_ADDR _AC(0x20000000,UL)
#define SPI0_MEM_SIZE _AC(0x20000000,UL)
#define SPI1_CTRL_ADDR _AC(0x10024000,UL)
#define SPI1_CTRL_SIZE _AC(0x1000,UL)
#define SPI2_CTRL_ADDR _AC(0x10034000,UL)
#define SPI2_CTRL_SIZE _AC(0x1000,UL)
#ifndef SPI_CTRL_ADDR
  #define SPI_CTRL_ADDR SPI0_CTRL_ADDR
#endif
#ifndef SPI_CTRL_SIZE
  #define SPI_CTRL_SIZE SPI0_CTRL_SIZE
#endif
#ifndef SPI_MEM_ADDR
  #define SPI_MEM_ADDR SPI0_MEM_ADDR
#endif
#ifndef SPI_MEM_SIZE
  #define SPI_MEM_SIZE SPI0_MEM_SIZE
#endif
#define TEST_CTRL_ADDR _AC(0x4000,UL)
#define TEST_CTRL_SIZE _AC(0x1000,UL)
#define UART0_CTRL_ADDR _AC(0x10013000,UL)
#define UART0_CTRL_SIZE _AC(0x1000,UL)
#define UART1_CTRL_ADDR _AC(0x10023000,UL)
#define UART1_CTRL_SIZE _AC(0x1000,UL)
#ifndef UART_CTRL_ADDR
  #define UART_CTRL_ADDR UART0_CTRL_ADDR
#endif
#ifndef UART_CTRL_SIZE
  #define UART_CTRL_SIZE UART0_CTRL_SIZE
#endif

// IOF masks
#define I2C0_IOF_MASK _AC(0x3000,UL)
#define I2C0_IOF_NUMBER 0
#define I2C0_IOF_SCL 13
#define I2C0_IOF_SDA 12
#define PWM0_IOF_MASK _AC(0xf,UL)
#define PWM0_IOF_NUMBER 1
#define PWM0_IOF_PWM0 0
#define PWM0_IOF_PWM1 1
#define PWM0_IOF_PWM2 2
#define PWM0_IOF_PWM3 3
#define PWM1_IOF_MASK _AC(0x780000,UL)
#define PWM1_IOF_NUMBER 1
#define PWM1_IOF_PWM0 20
#define PWM1_IOF_PWM1 19
#define PWM1_IOF_PWM2 21
#define PWM1_IOF_PWM3 22
#define PWM2_IOF_MASK _AC(0x3c00,UL)
#define PWM2_IOF_NUMBER 1
#define PWM2_IOF_PWM0 10
#define PWM2_IOF_PWM1 11
#define PWM2_IOF_PWM2 12
#define PWM2_IOF_PWM3 13
#define SPI1_IOF_CS0 2
#define SPI1_IOF_CS1 8
#define SPI1_IOF_CS2 9
#define SPI1_IOF_CS3 10
#define SPI1_IOF_DQ0 3
#define SPI1_IOF_DQ1 4
#define SPI1_IOF_DQ2 6
#define SPI1_IOF_DQ3 7
#define SPI1_IOF_MASK _AC(0x7fc,UL)
#define SPI1_IOF_NUMBER 0
#define SPI1_IOF_SCK 5
#define SPI2_IOF_CS0 26
#define SPI2_IOF_DQ0 27
#define SPI2_IOF_DQ1 28
#define SPI2_IOF_DQ2 30
#define SPI2_IOF_DQ3 31
#define SPI2_IOF_MASK _AC(0xfc000000,UL)
#define SPI2_IOF_NUMBER 0
#define SPI2_IOF_SCK 29
#define TESTLOOPBACK0_IOF_MASK _AC(0xc000,UL)
#define TESTLOOPBACK0_IOF_NA_A 14
#define TESTLOOPBACK0_IOF_NA_B 15
#define TESTLOOPBACK0_IOF_NUMBER 1
#define UART0_IOF_MASK _AC(0x30000,UL)
#define UART0_IOF_NUMBER 0
#define UART0_IOF_RXD 16
#define UART0_IOF_TXD 17
#define UART1_IOF_MASK _AC(0x840000,UL)
#define UART1_IOF_NUMBER 0
#define UART1_IOF_RXD 23
#define UART1_IOF_TXD 18

// Interrupt numbers
#define AON_INT_BASE 1
#define UART0_INT_BASE 3
#define UART1_INT_BASE 4
#define SPI0_INT_BASE 5
#define SPI1_INT_BASE 6
#define SPI2_INT_BASE 7
#define GPIO_INT_BASE 8
#define PWM0_INT_BASE 40
#define PWM1_INT_BASE 44
#define PWM2_INT_BASE 48
#define I2C_INT_BASE 52
#ifndef PWM_INT_BASE
  #define PWM_INT_BASE PWM0_INT_BASE
#endif
#ifndef SPI_INT_BASE
  #define SPI_INT_BASE SPI0_INT_BASE
#endif
#ifndef UART_INT_BASE
  #define UART_INT_BASE UART0_INT_BASE
#endif

// Helper functions
#define _REG64(p, i) (*(volatile uint64_t *)((p) + (i)))
#define _REG32(p, i) (*(volatile uint32_t *)((p) + (i)))
#define _REG16(p, i) (*(volatile uint16_t *)((p) + (i)))
// Bulk set bits in `reg` to either 0 or 1.
// E.g. SET_BITS(MY_REG, 0x00000007, 0) would generate MY_REG &= ~0x7
// E.g. SET_BITS(MY_REG, 0x00000007, 1) would generate MY_REG |= 0x7
#define SET_BITS(reg, mask, value) if ((value) == 0) { (reg) &= ~(mask); } else { (reg) |= (mask); }
#ifndef PWM_REG
  #define PWM_REG(offset) PWM0_REG(offset)
#endif
#ifndef PWM_REG64
  #define PWM_REG64(offset) PWM0_REG64(offset)
#endif
#ifndef SPI_REG
  #define SPI_REG(offset) SPI0_REG(offset)
#endif
#ifndef SPI_REG64
  #define SPI_REG64(offset) SPI0_REG64(offset)
#endif
#ifndef UART_REG
  #define UART_REG(offset) UART0_REG(offset)
#endif
#ifndef UART_REG64
  #define UART_REG64(offset) UART0_REG64(offset)
#endif
#define AON_REG(offset) _REG32(AON_CTRL_ADDR, offset)
#define CLINT_REG(offset) _REG32(CLINT_CTRL_ADDR, offset)
#define DEBUG_REG(offset) _REG32(DEBUG_CTRL_ADDR, offset)
#define DTIM_REG(offset) _REG32(DTIM_CTRL_ADDR, offset)
#define ERROR_REG(offset) _REG32(ERROR_CTRL_ADDR, offset)
#define FREEDOME300PRCI_REG(offset) _REG32(FREEDOME300PRCI_CTRL_ADDR, offset)
#define GPIO_REG(offset) _REG32(GPIO_CTRL_ADDR, offset)
#define I2C_REG(offset) _REG32(I2C_CTRL_ADDR, offset)
#define ITIM_REG(offset) _REG32(ITIM_CTRL_ADDR, offset)
#define MASKROM_REG(offset) _REG32(MASKROM_CTRL_ADDR, offset)
#define MODESELECT_REG(offset) _REG32(MODESELECT_CTRL_ADDR, offset)
#define OTP_REG(offset) _REG32(OTP_CTRL_ADDR, offset)
#define PLIC_REG(offset) _REG32(PLIC_CTRL_ADDR, offset)
#define PWM0_REG(offset) _REG32(PWM0_CTRL_ADDR, offset)
#define PWM1_REG(offset) _REG32(PWM1_CTRL_ADDR, offset)
#define PWM2_REG(offset) _REG32(PWM2_CTRL_ADDR, offset)
#define SPI0_REG(offset) _REG32(SPI0_CTRL_ADDR, offset)
#define SPI1_REG(offset) _REG32(SPI1_CTRL_ADDR, offset)
#define SPI2_REG(offset) _REG32(SPI2_CTRL_ADDR, offset)
#define TEST_REG(offset) _REG32(TEST_CTRL_ADDR, offset)
#define UART0_REG(offset) _REG32(UART0_CTRL_ADDR, offset)
#define UART1_REG(offset) _REG32(UART1_CTRL_ADDR, offset)
#define AON_REG64(offset) _REG64(AON_CTRL_ADDR, offset)
#define CLINT_REG64(offset) _REG64(CLINT_CTRL_ADDR, offset)
#define DEBUG_REG64(offset) _REG64(DEBUG_CTRL_ADDR, offset)
#define DTIM_REG64(offset) _REG64(DTIM_CTRL_ADDR, offset)
#define ERROR_REG64(offset) _REG64(ERROR_CTRL_ADDR, offset)
#define FREEDOME300PRCI_REG64(offset) _REG64(FREEDOME300PRCI_CTRL_ADDR, offset)
#define GPIO_REG64(offset) _REG64(GPIO_CTRL_ADDR, offset)
#define I2C_REG64(offset) _REG64(I2C_CTRL_ADDR, offset)
#define ITIM_REG64(offset) _REG64(ITIM_CTRL_ADDR, offset)
#define MASKROM_REG64(offset) _REG64(MASKROM_CTRL_ADDR, offset)
#define MODESELECT_REG64(offset) _REG64(MODESELECT_CTRL_ADDR, offset)
#define OTP_REG64(offset) _REG64(OTP_CTRL_ADDR, offset)
#define PLIC_REG64(offset) _REG64(PLIC_CTRL_ADDR, offset)
#define PWM0_REG64(offset) _REG64(PWM0_CTRL_ADDR, offset)
#define PWM1_REG64(offset) _REG64(PWM1_CTRL_ADDR, offset)
#define PWM2_REG64(offset) _REG64(PWM2_CTRL_ADDR, offset)
#define SPI0_REG64(offset) _REG64(SPI0_CTRL_ADDR, offset)
#define SPI1_REG64(offset) _REG64(SPI1_CTRL_ADDR, offset)
#define SPI2_REG64(offset) _REG64(SPI2_CTRL_ADDR, offset)
#define TEST_REG64(offset) _REG64(TEST_CTRL_ADDR, offset)
#define UART0_REG64(offset) _REG64(UART0_CTRL_ADDR, offset)
#define UART1_REG64(offset) _REG64(UART1_CTRL_ADDR, offset)
// Helpers for getting and setting individual bit fields, shifting the values
// for you.
#define GET_FIELD(reg, mask) (((reg) & (mask)) / ((mask) & ~((mask) << 1)))
#define SET_FIELD(reg, mask, val) (((reg) & ~(mask)) | (((val) * ((mask) & ~((mask) << 1))) & (mask)))

// Misc
#define SPI0_CS_WIDTH 1
#define SPI0_SCKDIV_WIDTH 12
#define SPI1_CS_WIDTH 4
#define SPI1_SCKDIV_WIDTH 12
#define SPI2_CS_WIDTH 1
#define SPI2_SCKDIV_WIDTH 12
#define GPIO_WIDTH 32

#endif /* _SIFIVE_PLATFORM_H */
