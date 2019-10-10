/* Copyright 2019 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#include <metal/cpu.h>
#include <metal/i2c.h>
#include <metal/io.h>
#include <metal/machine.h>
#include <metal/uart.h>
#include <stdio.h>
#include <time.h>

/* PmodAD2, PmodTmp2 sensor modules are connected to I2C0 bus */
#define TEMP_SENSOR_I2C_ADDR 0x4B
#define TEMP_SENSOR_ID 0xCB
#define ADC_I2C_ADDR 0x28
#define I2C_BAUDRATE 100000

/* Return values */
#define RET_OK 0
#define RET_NOK 1
/* Buffer length macros */
#define LEN0 0
#define LEN1 1
#define LEN2 2
/* 1s delay macro */
#define WAIT_1S(timeout)                                                       \
  timeout = time(NULL) + 1;                                                    \
  while (timeout > time(NULL))                                                 \
    ;

int main(void) {
  unsigned int temp, volt;
  unsigned char buf[LEN2];
  time_t timeout;
  struct metal_i2c *i2c;

  printf("%s %s \n", __DATE__, __TIME__);
  printf("I2C demo test..\n");

  i2c = metal_i2c_get_device(0);

  if (i2c == NULL) {
    printf("I2C not available \n");
    return RET_NOK;
  }

  metal_i2c_init(i2c, I2C_BAUDRATE, METAL_I2C_MASTER);

  /* Attempt to read ADT7420 Chip ID */
  buf[0] = 0x0B;
  metal_i2c_write(i2c, TEMP_SENSOR_I2C_ADDR, LEN1, buf, METAL_I2C_STOP_DISABLE);
  metal_i2c_read(i2c, TEMP_SENSOR_I2C_ADDR, LEN1, buf, METAL_I2C_STOP_ENABLE);

  /* Verify Chip ID */
  if (buf[0] == TEMP_SENSOR_ID) {
    printf("PmodTmp2 module detected \n");
  } else {
    printf("Failed to detect PmodTmp2 module \n");
    return RET_NOK;
  }

  /* Attempt to access AD7991, configure to convert on Vin0. */
  buf[0] = 0x10;
  if (metal_i2c_write(i2c, ADC_I2C_ADDR, LEN1, buf, METAL_I2C_STOP_ENABLE) !=
      RET_OK) {
    printf("Failed to detect PmodAD2 module \n");
    return RET_NOK;
  } else {
    printf("PmodAD2 module detected \n");
  }

  /* Loop and print data from slaves every 1s */
  while (1) {
    /* Slave access using read / write APIs */
    buf[0] = 0x0;
    metal_i2c_write(i2c, TEMP_SENSOR_I2C_ADDR, LEN1, buf,
                    METAL_I2C_STOP_DISABLE);
    metal_i2c_read(i2c, TEMP_SENSOR_I2C_ADDR, LEN2, buf, METAL_I2C_STOP_ENABLE);

    /* Get temperature value from received data */
    temp = ((unsigned int)buf[0] << 8 | buf[1]) >> 7;
    metal_i2c_read(i2c, ADC_I2C_ADDR, LEN2, buf, METAL_I2C_STOP_ENABLE);

    /* Convert data to represent ADC values in mV */
    volt = (((unsigned int)buf[0] << 8 | buf[1]) & 0xFFF) * 0.806;

    printf("temp: %u volts : %u \n", temp, volt);

    /* Slave access using transfer API */
    buf[0] = 0x0;
    metal_i2c_transfer(i2c, TEMP_SENSOR_I2C_ADDR, buf, LEN1, buf, LEN2);

    /* Get temperature value from received data */
    temp = ((unsigned int)buf[0] << 8 | buf[1]) >> 7;

    metal_i2c_transfer(i2c, ADC_I2C_ADDR, buf, LEN0, buf, LEN2);

    /* Convert data to represent ADC values in mV */
    volt = (((unsigned int)buf[0] << 8 | buf[1]) & 0xFFF) * 0.806;

    printf("temp: %u volts : %u \n", temp, volt);

    /* Wait 1s */
    WAIT_1S(timeout);
  }

  return RET_OK;
}
