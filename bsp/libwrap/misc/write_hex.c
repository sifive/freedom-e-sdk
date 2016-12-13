/* See LICENSE of license details. */

#include <stdint.h>
#include <unistd.h>
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
