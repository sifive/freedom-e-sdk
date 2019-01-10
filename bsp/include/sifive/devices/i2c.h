// See LICENSE for license details.

#ifndef _SIFIVE_I2C_H
#define _SIFIVE_I2C_H


// CHECK: word vs byte alignment
// OC I2C Linux driver defines registers w/o alignment:
// http://lxr.free-electrons.com/source/drivers/i2c/busses/i2c-ocores.c?v=4.6#L46
//
// However, register accessor functions use reg_shift value
// http://lxr.free-electrons.com/source/drivers/i2c/busses/i2c-ocores.c?v=4.6#L80
// which is platform specific:
// http://lxr.free-electrons.com/source/drivers/i2c/busses/i2c-ocores.c?v=4.6#L346

#define I2C_PRESCALER_LO  (0x00)
#define I2C_PRESCALER_HI  (0x04)
#define I2C_CONTROL       (0x08)
#define I2C_DATA          (0x0C)
#define I2C_CMD           (0x10) /* write only */
#define I2C_STATUS        (0x10) /* read only, same address as I2C_CMD */

// I2C_CONTROL register
#define I2C_CONTROL_CORE_EN(x)  (((x) & 0x1) << 7)
#define I2C_CONTROL_INT_EN(x)   (((x) & 0x1) << 6)

// I2C_CMD register
#define I2C_CMD_START(x)              (((x) & 0x1) << 7)
#define I2C_CMD_STOP(x)               (((x) & 0x1) << 6)
#define I2C_CMD_READ(x)               (((x) & 0x1) << 5)
#define I2C_CMD_WRITE(x)              (((x) & 0x1) << 4)
#define I2C_CMD_NACK(x)               (((x) & 0x1) << 3)
#define I2C_CMD_IRQ_ACK(x)            (((x) & 0x1))

// I2C_STATUS register
#define I2C_STATUS_RECEIVED_NACK(x)   (((x) & 0x80) >> 7)
#define I2C_STATUS_BUSY(x)            (((x) & 0x40) >> 6)
#define I2C_STATUS_ARB_LOST(x)        (((x) & 0x20) >> 5)
#define I2C_STATUS_TRS_INPROGRESS(x)  (((x) & 0x02) >> 1)
#define I2C_STATUS_IRQ_FLAG(x)        (((x) & 0x01))


#ifndef __ASSEMBLER__

#include <stdint.h>

/**
 * Get smallest clock prescaler that divides input_khz to a quotient less than or
 * equal to max_target_khz;
 */
inline uint16_t i2c_min_clk_prescaler(unsigned int input_khz, unsigned int max_target_khz)
{
  // f_sck = f_in / (2 * (div + 1)) => div = (f_in / (2*f_sck)) - 1
  // prescale = (f_in / (5*f_scl)) - 1
  //
  // The nearest integer solution for div requires rounding up as to not exceed
  // max_target_khz.
  //
  // div = ceil(f_in / (5*f_scl)) - 1
  //     = floor((f_in - 1 + 5*f_scl) / (5*f_scl)) - 1
  //
  // This should not overflow as long as (f_in - 1 + 5*f_scl) does not exceed
  // 2^32 - 1, which is unlikely since we represent frequencies in kHz.
  unsigned int quotient = (input_khz + 5 * max_target_khz - 1) / (5 * max_target_khz);
  // Avoid underflow
  if (quotient == 0) {
    return 0;
  } else {
    return quotient - 1;
  }
}

#endif /* !__ASSEMBLER__ */

#endif /* _SIFIVE_I2C_H */
