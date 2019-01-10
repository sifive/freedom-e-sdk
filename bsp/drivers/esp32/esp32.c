#include <stdint.h>
#include "platform.h"
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include "init.h"
#include "spi/spi.h"
#include "esp32/esp32.h"

unsigned int esp32_diag_mode=1;

static char tx_buf[64];
static char rx_buf[128];

void _putx(char c) {
  if(isprint(c)) _putc(c);
  else {
    _putc('#');
    _puti(c);
    _putc(' ');
  }
}

void _putnps(char *mychar) {
  int i=0;
  while(mychar[i] != 0 ) {
    if ( isprint(mychar[i]) ) _putc(mychar[i]);
    i++;
  }
}

// Wait for ready flag ... to a point.
int at_wait_done( int timeout )
{
  // Wait for done.
  int pdq=0;
  for(;!(GPIO_REG(GPIO_INPUT_VAL) & WF_INT_MASK) && pdq<timeout;pdq++) wait_ms(10);
  if ( pdq==timeout) return (timeout);
  else return (0);

}

int spi_transceive_one(spi_ctrl* spictrl, int num_xfers, int check_ready)
{
  int i;
  int32_t in;
  wait_ms(5); // Separate Transfers
  spictrl->csmode.mode = SPI_CSMODE_HOLD;
  for (i=0; i<num_xfers; i++) {
    // This puts a single bit in the queue.
    spictrl->txdata.data = tx_buf[i];
    // NOTE - we have 2 problems here
    // For SLOW processors, the SPI speed needs to be SLOW enough that
    //   we can execute the SPI_CSMODE_AUTO before the SPI transaction
    //   completes.
    // For FAST processors, there needs to be a delay here so that the
    //   SPI_CSMODE_AUTO does not execute UNTIL the SPI transation has
    //   already started.  Otherwise you get a runt CSB pulse.
    // This is hacky.  What we really need here is a "real" way to do multi-
    //  byte SPI transfers.
    #ifndef HASE24
    for(int j=0;j<30;j++) __asm__("NOP");  // 30 works for GuavaII at 16MHz.
    #endif
    if(i==num_xfers-1) spictrl->csmode.mode = SPI_CSMODE_AUTO;
    // Wait for readback to become available
    while ((in=(int32_t) spictrl->rxdata.raw_bits) < 0);
    rx_buf[i] = in & 0xFF;
  }
  return 0;

}

int
spi_transceive(spi_ctrl* spictrl, int num_xfers, int check_ready)
{
	spi_transceive_one(spictrl, num_xfers, check_ready);
	return 0;
}

int
at_sendflag(spi_ctrl* spictrl, char at_flag)
{
  int i;
  tx_buf[0] = at_flag;
  tx_buf[1] = 0;
  tx_buf[2] = 0;
  tx_buf[3] = 0;

  for (i=0; i<128; i++) rx_buf[i] = 0;  

  if(esp32_diag_mode > 2) {
    _puts("Sending Flag: ");
    for(i=0;i<4;i++) _putx(tx_buf[i]);
    _puts("\r\n");
  }  
  // Wait for Ready up to 100ms, but continue without an error
  // if we have to wait.
  if ( at_wait_done(10) ) {
    if (esp32_diag_mode > 1 ) _puts("Send Flag Timed Out Waiting for Ready\r\n");
  } else if (esp32_diag_mode>2) _puts("Send Flag Started\r\n");

  spi_transceive(spictrl, 4, 1);
  
  // Wait for flag done.  Retry up to 10x if we don't get the right thing.
  if ( at_wait_done(10) ) {
    for(int j=0;j<10;j++) {
      if (!at_wait_done(100) && rx_buf[0] == 'C') break;
      if(esp32_diag_mode>1) _puts("Send Flag Timed Out Busy. Retrying.\r\n");
      spi_transceive(spictrl, 4, 1);
    }
    if ( at_wait_done(10) ) _puts("Send Flag Timed Out Busy. Giving Up.\r\n");
  }
  else if (esp32_diag_mode>2) _puts("Send Flag Done\r\n");
  
  if(esp32_diag_mode > 2) {
    _puts("Flag Received: ");
    for(i=0;i<4;i++) _putx(rx_buf[i]);
    _puts("\r\n");
  }
  
  
  if (rx_buf[0] != 'C')
    {
      if (at_flag == AT_SEND)
	_puts(" Send Flag error: ");
      if (at_flag == AT_RECV)
	_puts(" Recv Flag error: ");
      for(i=0;i<4;i++) _putx(rx_buf[i]);
      return 1;
    }
  
  return 0;
}

int
at_send(spi_ctrl* spictrl, char *at_cmd, int timeout)
{
  int rc = 0;
  int i;
  
  short cmd_len = (short) strlen(at_cmd);

  if (esp32_diag_mode) {
    _putnps(at_cmd);
    _puts("-->");
  }
  
  // Note - the busy signal will be LOW here.
  
  //  First send the flag which sets directionality of the transaction
  rc = at_sendflag(spictrl, AT_SEND);
  
  if (rc != 0)		// Return on first failure
    return rc;
  else if (esp32_diag_mode > 2) _puts("Flag Sent\r\n");

  // Second, send the length of the command to be sent.
  tx_buf[0] = cmd_len & 127;
  tx_buf[1] = cmd_len >> 7;
  tx_buf[2] = 0;
  tx_buf[3] = 'A';
	
  spi_transceive(spictrl, 4, 1);

  if (esp32_diag_mode > 2) _puts("Length Sent\r\n");  

  // Wait for done.
  if ( at_wait_done(timeout) ) _puts("CMD Length Timed Out Busy\r\n");
  else if (esp32_diag_mode>2) _puts("CMD Length Sent\r\n");
	
  if (rx_buf[0] != 'b')
    {
      _puts("Send length error: ");
      for(i=0;i<4;i++) _putx(rx_buf[i]);
      return 1;	// Return error on failure
    }

  // Copy at_cmd to tx_buf
  strncpy(tx_buf, at_cmd, cmd_len);

  spi_transceive(spictrl, cmd_len, 1);


  if (rx_buf[0] == 'C')
    {
      _puts(" Send sync error ");
      return 1;	// Return error on failure
    }
  
  // Wait for done.
  if ( at_wait_done(timeout) ) _puts("CMD Timed Out Busy\r\n");
  else if (esp32_diag_mode > 2) _puts("CMD Done\r\n");
  
  return 0;
}

int
at_recv_one(spi_ctrl* spictrl)
{
  int i;
  int rc = 0;
  int resp_len = 0;

  // Repeat this like 7 times if needed.
  for(int j=0;;j++) {
    if (esp32_diag_mode > 2 ) _puts("RECV Flag Check\r\n");  
    rc = at_sendflag(spictrl, AT_RECV);
    if (rc != 0) return rc;
    else
      if (esp32_diag_mode > 2 ) _puts("RECV Flag OK\r\n");

    // Clear the send/receive buffers
    for (i=0; i<128; i++) rx_buf[i] = 0;
    for (i=0; i<64; i++) tx_buf[i] = 0;  
  
    // Receive the length
    spi_transceive(spictrl, 4, 1);

    // Wait for done.
    if ( at_wait_done(100) ) _puts("Receive Length Timed Out Busy\r\n");
    else if (esp32_diag_mode>2) _puts("Receive Length OK\r\n");

    if(esp32_diag_mode > 2) {
      _puts("Length Received: ");
      for(i=0;i<4;i++) _putx(rx_buf[i]);
      _puts("\r\n");
    }  
  
    if (rx_buf[3] == 'B') break;

    if(esp32_diag_mode>1) {
      _puts("Recv length error: ");
      _putc(rx_buf[3]);
      _puts("\r\n");
    }
    if( j>8 ) return 1; // Return error on failure
    else {
      if(esp32_diag_mode>1)_puts("Retrying...\r\n");
      wait_ms(100);
    }
  }

  resp_len = (rx_buf[1] << 7) + rx_buf[0];
  if (esp32_diag_mode > 1)
    {
      _puts("Recv Length is: ");
      _puti(resp_len);
      _putc(' ');
      _puts("\r\n");      
    }

  // Clear the repsonse buffer
  for (i=0; i<128; i++) rx_buf[i] = 0;

  // Receive the response
  spi_transceive(spictrl, resp_len, 0);
  rx_buf[resp_len] = 0;		// Null terminate
  
  if (esp32_diag_mode > 1)
    {
      _puts("rx_buf contents: ");
      i = 0;
      while (resp_len--)
	{
	  _puti(rx_buf[i++]);
	  _putc(' ');
	}
    _puts("\r\n");      
    }
  
  return 0;
}

int
at_recv(spi_ctrl* spictrl)
{
  int i;
  int rc = 0;

  // Receive all messages until we see a done message or limit
  //	i = 2;	// TODO: TEMP: limit recv messages and then exit
		// WARNING: This may leave unread messages!
  i = 50;	// TODO: TEMP: limit recv messages and then exit
  while (i--){
    rc = at_recv_one(spictrl);
    if (rc != 0)		// Return on first failure
      {
	_puts("got recv error ");
	return rc;
      }

    if (esp32_diag_mode > 1) {
      _puts("Other Recv message# ");
      _puti(i);
      _putc(':');
      _putc(' ');
      _puts(rx_buf);		// Print results
      _puts("\r\n");            
    } else if ( esp32_diag_mode ) {
      _putnps(rx_buf);		// Print results
      _puts("\r\n");      
    }

    if (strncmp(rx_buf, "\r\nOK\r\n", 6) == 0)
      {
	if (esp32_diag_mode>1)
	  _puts("got ok\r\n");
	return AT_OKAY;
	break;
      }
    else if (strncmp(rx_buf, "\r\nready\r\n", 6) == 0)
      {
	if (esp32_diag_mode>1)
	  _puts("got ready\r\n");
	return AT_READY;	
	break;
      }
    else if (strncmp(rx_buf, "\r\nERROR\r\n", 6) == 0)
      {
	if (esp32_diag_mode>1)
	  _puts("got error\r\n");
	return AT_ERROR;	
	rc =  1;
	break;
      }
  }
  return rc;
}

int at_sendrecv(spi_ctrl* spictrl, char *at_cmd, int timeout)
{
  int rc = 0;

  rc = at_send(spictrl, at_cmd, timeout);
  if (rc != 0) return rc;

  rc = at_recv(spictrl);  // Receive message
  return rc;
}


int esp32_init() {
  spi_ctrl* spictrl;
  spictrl = (spi_ctrl*) ESP32_SPI_PORT;
  
  GPIO_REG(GPIO_IOF_SEL) &= ~(1 << ESP32_IOF_DQ0);
  GPIO_REG(GPIO_IOF_SEL) &= ~(1 << ESP32_IOF_DQ1);
  GPIO_REG(GPIO_IOF_SEL) &= ~(1 << ESP32_IOF_SCK);
  GPIO_REG(GPIO_IOF_SEL) &= ~(1 << ESP32_IOF_CS);
  GPIO_REG(GPIO_IOF_EN) |= (1 << ESP32_IOF_DQ0);
  GPIO_REG(GPIO_IOF_EN) |= (1 << ESP32_IOF_DQ1);
  GPIO_REG(GPIO_IOF_EN) |= (1 << ESP32_IOF_SCK);
  GPIO_REG(GPIO_IOF_EN) |= (1 << ESP32_IOF_CS);
  GPIO_REG(GPIO_INPUT_EN) |= (WF_INT_MASK);	// Enable intr pin

  spictrl->sckdiv =ESP32_SPI_SCKDIV;
  
  spictrl->fmt.raw_bits = 0x80000;
  spictrl->csid = ESP32_SPI_CSID;
  spictrl->fctrl.en = 0;	// Set direct mode
  
  // Don't require CS to go high between transfers.
  // This leaves a vestigial CS blip even when set to 0
  spictrl->delay1.intercs=0;

  // Automatically lower/raise CS. This is re-set in the transcieve function.
  spictrl->csmode.mode = SPI_CSMODE_AUTO;

  while (((int32_t) spictrl->rxdata.raw_bits) > 0); // Clear SPI recv FIFO
  _puts("\r\n");
  at_sendrecv(spictrl, "ATE0\r\n",100);
  at_sendrecv(spictrl, "AT+BLEINIT=0\r\n",100);
  at_sendrecv(spictrl, "AT+CWMODE=0\r\n",100);
  _puts("\r\n");

  return (0);
}
