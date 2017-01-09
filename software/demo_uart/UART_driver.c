// See LICENSE file for license details

/* Standard includes */
#include <string.h>

/* HiFive/FE310 includes*/
#include "sifive/devices/uart.h"
#include "encoding.h"

/* Local includes */
#include "UART_driver.h"

/* Enables the UART for I/O.
 *
 * baud: baud rate to set.
 * stop_bits: 0 for 1 stop-bit, anything else for 2.
 */
void UART_init(unsigned long baud, int stop_bits) {
  /* Set pins 16 (RX) and 17 (TX) as I/O
   * Ref: HiFive1 Getting Starting guide (v1.0.2), Pg. 24
   */
  GPIO_REG(GPIO_OUTPUT_XOR) &= ~(IOF0_UART0_MASK);
  GPIO_REG(GPIO_IOF_SEL)    &= ~(IOF0_UART0_MASK);
  GPIO_REG(GPIO_IOF_EN)     |= IOF0_UART0_MASK;

  /* Set remaining UART attributes */
  UART_set_baud(baud);
  UART_set_stop_bits(stop_bits);

  /* Enable TX and RX by writing to the enable bits
   * of their respective controller registers
   */
  UART0_REG(UART_REG_TXCTRL) |= UART_TXEN;
  UART0_REG(UART_REG_RXCTRL) |= UART_RXEN;
}

/* Disables the UART
 */
void UART_deinit()
{
  /* Disable pins 16 (RX) and 17 (TX) as I/O */
  GPIO_REG(GPIO_IOF_EN)      &= ~IOF0_UART0_MASK;

  /* Disable TX and RX by clearing enable bits of 
   * their respective controller registers
   */
  UART0_REG(UART_REG_TXCTRL) &= ~UART_TXEN;
  UART0_REG(UART_REG_RXCTRL) &= ~UART_RXEN;
}

/* Sets the baud rate.
 *
 * baud: baud rate to set.
 */
void UART_set_baud(unsigned long baud)
{
  /* Set the baud rate, where:
   * F_baud = f_in/(div+1)
   * Ref: SiFive E300 Platform Reference Manual (v1.0.1), Pg. 39
   */
  UART0_REG(UART_REG_DIV)     = get_cpu_freq() / baud-1;
}

/* Sets the number of stop bits.
 *
 * stop_bits: 0 for 1 stop-bit, anything else for 2.
 */
void UART_set_stop_bits(int stop_bits)
{
  UART0_REG(UART_REG_TXCTRL)  &= (((stop_bits ? 1 : 0) << 1) & 0xFFFFFFFF);
}

/* Outputs a character on the UART device. If blocking is
 * disabled and the device is disabled an error is returned.
 *
 * ch: The character to output.
 * blocking: Set to 0 to prevent blocking writes.
 *
 * Returns 0 on success, -1 on error.
 */
int UART_put_char(char ch, int blocking)
{
  volatile uint32_t *val = &UART0_REG(UART_REG_TXFIFO);
  uint32_t busy = (*val) & 0x80000000;
  if (blocking) {
    while (*val & 0x80000000);
  } else if (busy){
    return -1;
  }
  UART0_REG(UART_REG_TXFIFO) = ch;
  return 0;
}

/* Retrieves a single character from the UART receive buffer.
 *
 * ch: pointer to a destination char to put the read character into.
 * blocking: whether the function should block until success.
 *
 * Returns 0 on success.
 */
int UART_get_char(char * ch, int blocking)
{
  int busy;

  do {
    UART_probe_rx();
    busy = (rxbuf_head == rxbuf_tail);
  } while (blocking && busy);

  if (busy) {
    return -1;
  }

  *ch = rxbuf[rxbuf_tail++];
  rxbuf_tail &= UART_RXBUF_MASK;
  return 0;
}

/* Checks whether a byte is pending in UART receive buffer and 
 * pops it if present.
 *
 * Returns 0 on success.
 */
int UART_probe_rx()
{
  int32_t c;

  if ((c = UART0_REG(UART_REG_RXFIFO)) >= 0) {
    rxbuf[rxbuf_head++] = (char)c;
    rxbuf_head &= UART_RXBUF_MASK;
    return 0;
  }
  return -1;
}

/* Writes a string to the UART.
 *
 * msg: the string to ouput.
 * blocking: enable to enforce waiting 
 *
 * Returns the number of bytes written.
 */
int UART_write(char * msg, int blocking)
{
  int i, ret;
  for (i=0; i<strlen(msg); i++) {
    ret = UART_put_char(msg[i], blocking);
    if (0 != ret) {
        break;
    }
  }
  return i;
}

/* Reads a string from the UART device and places the result
 * into a buffer. Reading stops when either the end of the string is
 * reached, the specified buffer size is reached or a terminating
 * character is encountered.
 *
 * buffer: pointer to a char array to write characters into.
 * max_chars: maximum number of characters to read before returning.
 * N.B: sending a shorter string buffer than specified by max_chars
 * can result in a seg-fault.
 * terminator: Reading stops when this character is encountered.
 *
 * Returns the number of bytes read.
 */
int UART_read_n(char * buffer, int max_chars, char terminator, int blocking)
{
  int i;
  for (i=0; i<max_chars; i++) {
    if (0 != UART_get_char(&buffer[i], blocking)) {
        break;
    }
    if ((buffer[i] == terminator) || (buffer[i] == 0)) {
      break;
    }
  }
  return i;
}
