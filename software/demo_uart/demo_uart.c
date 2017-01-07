/* See LICENSE file for license details */

/* Standard includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* HiFive1/FE310 includes */
#include "encoding.h"

/* Local includes */
#include "UART_driver.h"

#define RTC_FREQUENCY 32768
const char * msg = "Hello, SiFive! Keep up the great work.\n\r";

void handle_m_time_interrupt()
{
  /* Disable timer interrupt */
  clear_csr(mie, MIP_MTIP);

  /* Reset the timer for 3s in the future.
   * This also clears the existing timer interrupt.
   */
  volatile uint64_t * mtime       = (uint64_t*) (CLINT_BASE_ADDR + CLINT_MTIME);
  volatile uint64_t * mtimecmp    = (uint64_t*) (CLINT_BASE_ADDR + CLINT_MTIMECMP);
  uint64_t now = *mtime;
  uint64_t then = now + 1.5 * RTC_FREQUENCY;
  *mtimecmp = then;

  /* Send a message out the UART (allow blocking)*/
  UART_write(msg, 1);

  /* Re-enable the timer interrupt */
  set_csr(mie, MIP_MTIP);
}

void handle_m_ext_interrupt()
{
}

void start_demo()
{
  /* Disable the machine & timer interrupts until setup is done. */
  clear_csr(mie, MIP_MEIP);
  clear_csr(mie, MIP_MTIP);

  /* Set the machine timer to go off in 3 seconds. */
  volatile uint64_t * mtime       = (uint64_t*) (CLINT_BASE_ADDR + CLINT_MTIME);
  volatile uint64_t * mtimecmp    = (uint64_t*) (CLINT_BASE_ADDR + CLINT_MTIMECMP);
  uint64_t now = *mtime;
  uint64_t then = now + 1.5*RTC_FREQUENCY;
  *mtimecmp = then;

  /* Enable the Machine-Timer bit in MIE */
  set_csr(mie, MIP_MTIP);
  /* Enable interrupts in general. */
  set_csr(mstatus, MSTATUS_MIE);

  /* Set up 9600 baud with 1 stop bit */
  UART_init(9600, 0);
}

int main()
{
  /* Sanity test our output at the default 115200 baud */
  write(STDOUT_FILENO, msg, strlen(msg));

  /* Init repeating timers and set UART output configuration */
  start_demo();

  while (1) {};

  return 0;
}
