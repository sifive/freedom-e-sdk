// See LICENSE for license details.

/* This is an incomplete version of a syscall library, 
 * which really only supports simple reads and writes over UART.
 */

#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/times.h>
#include <stdio.h>
#include <string.h>

#include "platform.h"

void write_hex(int fd, uint32_t hex)
{
  uint8_t ii;
  uint8_t jj;
  char towrite;
  write(fd , "0x", 2);
  for (ii = 8 ; ii > 0; ii--) {
    jj = ii - 1;
    uint8_t digit = ((hex & (0xF << (jj*4))) >> (jj*4));
    towrite = digit < 0xA ? ('0' + digit) : ('A' +  (digit - 0xA));
    write(fd, &towrite, 1);
  }
}

void _exit(int code)
{
  //volatile uint32_t* leds = (uint32_t*) (GPIO_BASE_ADDR + GPIO_OUT_OFFSET);
  const char * message = "\nProgam has exited with code:";
  
  //*leds = (~(code));

  write(STDERR_FILENO, message, strlen(message));
  write_hex(STDERR_FILENO, code);

  while (1){};
    
}

void *sbrk(ptrdiff_t incr)
{
  extern char _end[];
  extern char _heap_end[];
  static char *curbrk = _end;

  if ((curbrk + incr < _end) || (curbrk + incr > _heap_end))
    return NULL - 1;

  curbrk += incr;
  return curbrk - incr;
}

static int stub(int err)
{
  return -1;
}

int open(const char* name, int flags, int mode)
{
  return stub(ENOENT);
}

int openat(int dirfd, const char* name, int flags, int mode)
{
  return stub(ENOENT);
}

int close(int fd)
{
  return stub(EBADF);
}

int execve(const char* name, char* const argv[], char* const env[])
{
  return stub(ENOMEM);
}

int fork()
{
  return stub(EAGAIN);
}

int fstat(int fd, struct stat *st)
{
  if (isatty(fd)) {
    st->st_mode = S_IFCHR;
    return 0;
  }

  return stub(EBADF);
}

int getpid()
{
  return 1;
}

int isatty(int fd)
{
  if (fd == STDOUT_FILENO || fd == STDERR_FILENO)
    return 1;

  return 0;
}

int kill(int pid, int sig)
{
  return stub(EINVAL);
}

int link(const char *old_name, const char *new_name)
{
  return stub(EMLINK);
}

off_t lseek(int fd, off_t ptr, int dir)
{
  if (isatty(fd))
    return 0;

  return stub(EBADF);
}

ssize_t read(int fd, void* ptr, size_t len)
{
  uint8_t * current = (uint8_t *)ptr;
  volatile uint32_t * uart_rx = (uint32_t *)(UART0_BASE_ADDR + UART_REG_RXFIFO);
  volatile uint8_t * uart_rx_cnt = (uint8_t *)(UART0_BASE_ADDR + UART_REG_RXCTRL + 2);

  ssize_t result = 0;
  
  if (isatty(fd)) {
    for (current = (uint8_t *)ptr;
        (current < ((uint8_t *)ptr) + len) && (*uart_rx_cnt > 0);
        current ++) {
      *current = *uart_rx;
      result++;
    }
    return result;
  }
 
  return stub(EBADF);
}

int stat(const char* file, struct stat* st)
{
  return stub(EACCES);
}

clock_t times(struct tms* buf)
{
  return stub(EACCES);
}

int unlink(const char* name)
{
  return stub(ENOENT);
}

int wait(int* status)
{
  return stub(ECHILD);
}

ssize_t write(int fd, const void* ptr, size_t len)
{
  const uint8_t * current = (const char *)ptr;
  volatile uint32_t * uart_tx = (uint32_t *)(UART0_BASE_ADDR + UART_REG_TXFIFO);

  size_t jj;
  if (isatty(fd)) {
    for (size_t jj = 0; jj < len; jj++) {
      while ((*uart_tx) & 0x80000000) ;
      *uart_tx = current[jj];

      if (current[jj] == '\n') {
        while ((*uart_tx) & 0x80000000) ;
        *uart_tx = '\r';
      }
    }
    return len;
  } 

  return stub(EBADF);
}
