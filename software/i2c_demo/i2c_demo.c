#include <stdio.h>
#include <stdlib.h>
#include "platform.h"
#include <string.h>
#include <unistd.h>
#include <math.h>
#include "stdatomic.h"

#define MPU6050_ADDR 0x68

#define MPU6050_RA_ACCEL_XOUT_H     0x3B
#define MPU6050_RA_ACCEL_XOUT_L     0x3C
#define MPU6050_RA_ACCEL_YOUT_H     0x3D
#define MPU6050_RA_ACCEL_YOUT_L     0x3E
#define MPU6050_RA_ACCEL_ZOUT_H     0x3F
#define MPU6050_RA_ACCEL_ZOUT_L     0x40
#define MPU6050_RA_TEMP_OUT_H       0x41
#define MPU6050_RA_TEMP_OUT_L       0x42
#define MPU6050_RA_GYRO_XOUT_H      0x43
#define MPU6050_RA_GYRO_XOUT_L      0x44
#define MPU6050_RA_GYRO_YOUT_H      0x45
#define MPU6050_RA_GYRO_YOUT_L      0x46
#define MPU6050_RA_GYRO_ZOUT_H      0x47
#define MPU6050_RA_GYRO_ZOUT_L      0x48
#define MPU6050_RA_PWR_MGMT_1       0x6B
#define MPU6050_RA_WHO_AM_I         0x75

#define SDA PIN_8_OFFSET
#define SCL PIN_9_OFFSET

#define LONG 25 // Equals ~400KHz
#define SHORT 5

//busy wait for the specified time
void wait_ms(uint64_t ms) {
  static const uint64_t ms_tick = RTC_FREQ/1000;
  volatile uint64_t * mtime  = (uint64_t*) (CLINT_CTRL_ADDR + CLINT_MTIME);
  uint64_t then = (ms_tick * ms) + *mtime;
  while(*mtime<then);
}

inline void delay_number_of_nop(uint32_t count)
{
  for(volatile uint32_t j = 0; j < count; j++)
  {
    asm("nop");
  }
}

_Bool i2c_busy(void)
{
  GPIO_REG(GPIO_INPUT_EN) |= ((0x1 << SCL) | (0x1 << SDA));
  GPIO_REG(GPIO_OUTPUT_EN)  &= ~((0x1 << SCL) | (0x1 << SDA));
  return (GPIO_REG(GPIO_INPUT_VAL) & ((0x1 << SCL) | (0x1 << SDA))) != ((0x1 << SCL) | (0x1 << SDA));
}

void i2c_start(void)
{
  GPIO_REG(GPIO_INPUT_EN)  &=  ~((0x1 << SDA) | (0x1 << SCL));

  GPIO_REG(GPIO_OUTPUT_VAL) &= ~(0x1 << SDA);
  GPIO_REG(GPIO_OUTPUT_EN)  |=  (0x1 << SDA);
  delay_number_of_nop(SHORT);
  GPIO_REG(GPIO_OUTPUT_VAL) &= ~(0x1 << SCL);
  GPIO_REG(GPIO_OUTPUT_EN)  |=  (0x1 << SCL);
}

void i2c_repeated_start(void)
{
  delay_number_of_nop(SHORT);
  GPIO_REG(GPIO_OUTPUT_VAL) |=  (0x1 << SCL);
  GPIO_REG(GPIO_OUTPUT_EN)  |=  (0x1 << SCL);
  delay_number_of_nop(SHORT);
  i2c_start();
}


void i2c_stop(void)
{
  GPIO_REG(GPIO_INPUT_EN) |= (0x1 << SCL);
  GPIO_REG(GPIO_OUTPUT_EN)  &= ~(0x1 << SCL);
  delay_number_of_nop(SHORT);
  GPIO_REG(GPIO_INPUT_EN) |= (0x1 << SDA);
  GPIO_REG(GPIO_OUTPUT_EN)  &= ~(0x1 << SDA);
}

void i2c_init(void)
{
  //GPIO_REG(GPIO_IOF_EN) &= ((0x1 << SCL) | (0x1 << SDA));
  GPIO_REG(GPIO_OUTPUT_EN) &= ~((0x1 << SCL) | (0x1 << SDA));
  GPIO_REG(GPIO_PULLUP_EN) |= ((0x1 << SDA) | (0x1 << SCL));
  GPIO_REG(GPIO_INPUT_EN)  |=  (0x1 << SDA) | (0x1 << SCL);
}

void i2c_send_bytes_rs(uint8_t* data, uint8_t size, _Bool rs, uint8_t* data_r, uint8_t size_r)
{
  uint8_t address_r = data[0] | 0x01;

  for(uint8_t ii=0; ii<size; ii++)
  {
    GPIO_REG(GPIO_INPUT_EN)  &= ~(0x1 << SDA);
    GPIO_REG(GPIO_OUTPUT_EN) |=  (0x1 << SDA);
    for(uint8_t i=0; i<9; i++)
    {
      delay_number_of_nop(SHORT);

      if(i != 8)
      {
        if(data[ii] & 0x80)
          GPIO_REG(GPIO_OUTPUT_VAL) |=  (0x1 << SDA);
        else
          GPIO_REG(GPIO_OUTPUT_VAL) &= ~(0x1 << SDA);
      }
      else
      {
        GPIO_REG(GPIO_INPUT_EN)  |=  (0x1 << SDA);
        GPIO_REG(GPIO_OUTPUT_EN) &= ~(0x1 << SDA);
        if((GPIO_REG(GPIO_INPUT_VAL) & (0x1 << SDA)) != 0x0)
        {
            printf("NO ACK\n");
        }

        GPIO_REG(GPIO_INPUT_EN)  &= ~(0x1 << SDA);
        GPIO_REG(GPIO_OUTPUT_EN) |=  (0x1 << SDA);
        if(rs == 0)
        {
          GPIO_REG(GPIO_OUTPUT_VAL) &= ~(0x1 << SDA);
        }
        else
        {
          GPIO_REG(GPIO_OUTPUT_VAL) |= (0x1 << SDA);
        }

      }
      delay_number_of_nop(LONG-SHORT);

      GPIO_REG(GPIO_OUTPUT_VAL) |= (0x1 << SCL);

      delay_number_of_nop(LONG);

      GPIO_REG(GPIO_OUTPUT_VAL) &= ~(0x1 << SCL);

      data[ii] <<= 1;
    }
  }

  if(rs == 0)
    return;

  GPIO_REG(GPIO_OUTPUT_VAL) |= (0x1 << SCL);

  delay_number_of_nop(SHORT);

  GPIO_REG(GPIO_OUTPUT_VAL) &= ~(0x1 << SDA);

  delay_number_of_nop(SHORT);

  GPIO_REG(GPIO_OUTPUT_VAL) &= ~(0x1 << SCL);

  for(uint8_t i=0; i<9; i++)
  {
    delay_number_of_nop(SHORT);
    if(i != 8)
    {
      if(address_r & 0x80)
        GPIO_REG(GPIO_OUTPUT_VAL) |=  (0x1 << SDA);
      else
        GPIO_REG(GPIO_OUTPUT_VAL) &= ~(0x1 << SDA);
    }
    else
    {
      GPIO_REG(GPIO_INPUT_EN)  |=  (0x1 << SDA);
      GPIO_REG(GPIO_OUTPUT_EN) &= ~(0x1 << SDA);
      if((GPIO_REG(GPIO_INPUT_VAL) & (0x1 << SDA)) != 0x0)
      {
          printf("NO ACK\n");
      }
    }
    delay_number_of_nop(LONG-SHORT);

    GPIO_REG(GPIO_OUTPUT_VAL) |= (0x1 << SCL);

    delay_number_of_nop(LONG);

    GPIO_REG(GPIO_OUTPUT_VAL) &= ~(0x1 << SCL);

    address_r <<= 1;
  }

  // Receive Data
  for(uint8_t ii=0; ii<size_r; ii++)
  {
    for(uint8_t i=0; i<9; i++)
    {
      GPIO_REG(GPIO_OUTPUT_VAL) |= (0x1 << SCL);

      if(i!=8)
        data_r[ii] <<= 1;

      delay_number_of_nop(SHORT);

      if(i!=8)
      {
        if((GPIO_REG(GPIO_INPUT_VAL) & (0x1 << SDA)) != 0x0)
        {
          data_r[ii] |= 0x1;
        }
      }
      else if(ii == (size_r-1))
      {
        GPIO_REG(GPIO_INPUT_EN)  &= ~(0x1 << SDA);
        GPIO_REG(GPIO_OUTPUT_EN) |=  (0x1 << SDA);
        GPIO_REG(GPIO_OUTPUT_VAL) &= ~(0x1 << SDA);
      } else {

      }

      delay_number_of_nop(LONG-SHORT);

      GPIO_REG(GPIO_OUTPUT_VAL) &= ~(0x1 << SCL);

      if((i==7) && (ii != (size_r-1))){
          GPIO_REG(GPIO_INPUT_EN)  &= ~(0x1 << SDA);
          GPIO_REG(GPIO_OUTPUT_EN) |=  (0x1 << SDA);
          GPIO_REG(GPIO_OUTPUT_VAL) &= ~(0x1 << SDA);
      }
      delay_number_of_nop(LONG);

    }

    if(ii != (size_r-1)){
          GPIO_REG(GPIO_INPUT_EN)  |=  (0x1 << SDA);
          GPIO_REG(GPIO_OUTPUT_EN) &= ~(0x1 << SDA);
          delay_number_of_nop(SHORT);
    }
  }
}

void write_byte(uint8_t address, uint8_t reg_addr, uint8_t val)
{
  uint8_t temp[3];
  uint8_t data;
  temp[0]=address<<1;
  temp[1]=reg_addr;
  temp[2]=val;
  while(i2c_busy());
  i2c_start();
  i2c_send_bytes_rs(temp, sizeof(temp), 0, &data, 1);
  i2c_stop();
}

uint8_t read_byte(uint8_t address, uint8_t reg_addr)
{
  uint8_t temp[2];
  uint8_t data;
  temp[0]=address<<1;
  temp[1]=reg_addr;
  while(i2c_busy());
  i2c_start();
  i2c_send_bytes_rs(temp, sizeof(temp), 1, &data, 1);
  i2c_stop();
  return data;
}

void read_bytes(uint8_t address, uint8_t reg_addr, uint8_t* data, uint8_t size)
{
  uint8_t temp[2];
  temp[0]=address<<1;
  temp[1]=reg_addr;
  while(i2c_busy());
  i2c_start();
  i2c_send_bytes_rs(temp, sizeof(temp), 1, data, size);
  i2c_stop();
}

int main(int argc, char **argv)
{
  uint8_t data;
  uint8_t accel[6];

  printf("BIT-BANG I2C DEMO with MPU-6050 IMU\n");

  i2c_init();

  printf("Power Management 1: 0x%02X\n", read_byte(MPU6050_ADDR, MPU6050_RA_PWR_MGMT_1));
  write_byte(MPU6050_ADDR, MPU6050_RA_PWR_MGMT_1, 0x80);

  wait_ms(10);

  printf("Power Management 1: 0x%02X\n", read_byte(MPU6050_ADDR, MPU6050_RA_PWR_MGMT_1));
  write_byte(MPU6050_ADDR, MPU6050_RA_PWR_MGMT_1, 0x00);

  printf("CHIP_ID: 0x%02X\n", read_byte(MPU6050_ADDR, MPU6050_RA_WHO_AM_I));
  printf("DONE\n");

  while(1)
  {
    //for(uint8_t i=0; i<6; i++){
    //  accel[i]=read_byte(MPU6050_ADDR, 0x3B+i);
    //}
    read_bytes(MPU6050_ADDR, 0x3B, accel, 6);
    int16_t x_accel = (accel[0]<<8)+accel[1];
    int16_t y_accel = (accel[2]<<8)+accel[3];
    int16_t z_accel = (accel[4]<<8)+accel[5];

    float z_g = z_accel;
    z_g = z_g/16384.0;
    int32_t z_g_int = z_g*100;
    z_g_int = abs(z_g_int);
    printf("Gravity in Z %d.%d\n", z_g_int/100, z_g_int%100);

    //printf("X: %06d, Y: %06d, Z: %06d\n", x_accel, y_accel, z_accel);

    wait_ms(100);
  }

  return 0;
}
