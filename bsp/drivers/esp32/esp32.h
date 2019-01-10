// See LICENSE for license details.

#include <stdint.h>
#include "platform.h"
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include "spi/spi.h"

#ifndef SIFIVE_ESP32
  #define SIFIVE_ESP32

  #define AT_RECV		1
  #define AT_SEND		2
  #define WF_INT_MASK	(1 << 10)

  #define AT_OKAY 1
  #define AT_READY 2
  #define AT_ERROR -1

  #ifndef ESP32_SPI_PORT
    #define ESP32_SPI_PORT SPI1_CTRL_ADDR
  #endif

  #ifndef ESP32_SPI_CSID
    #define ESP32_SPI_CSID 2
  #endif

  #ifndef ESP32_IOF_DQ0
    #define ESP32_IOF_DQ0 SPI1_IOF_DQ0
  #endif

  #ifndef ESP32_IOF_DQ1
    #define ESP32_IOF_DQ1 SPI1_IOF_DQ1
  #endif

  #ifndef ESP32_IOF_SCK
    #define ESP32_IOF_SCK SPI1_IOF_SCK
  #endif

  #ifndef ESP32_IOF_CS
    #define ESP32_IOF_CS SPI1_IOF_CS2
  #endif

  #ifndef ESP32_SPI_SCKDIV
    #define ESP32_SPI_SCKDIV 100
  #endif


int at_sendflag(spi_ctrl* spictrl, char at_flag);
int at_send(spi_ctrl* spictrl, char *at_cmd, int timeout);
int at_recv_one(spi_ctrl* spictrl);
int at_recv(spi_ctrl* spictrl);
int esp32_init();
int at_sendrecv(spi_ctrl* spictrl, char *at_cmd, int timeout);
int spi_transceive(spi_ctrl* spictrl, int num_xfers, int check_ready);
int spi_transceive_one(spi_ctrl* spictrl, int num_xfers, int check_ready);

#endif
