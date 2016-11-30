#include "platform.h"

/* The functions in this file are only meant to support Dhrystone on an
 * embedded RV32 system and are obviously incorrect in general. */

// return the cycle counter as though it were the current time
long time(void)
{
  long t;
  asm volatile ("csrr %0, mcycle" : "=r" (t));
  return t / (get_cpu_freq() / 1000);
}

// set the number of dhrystone iterations
void scanf(const char* fmt, int* n)
{
  *n = 1500000;
}

// simple memory allocator
void* malloc(unsigned long sz)
{
  extern void* sbrk(long);
  void* res = sbrk(sz);
  if ((long)res == -1)
    return 0;
  return res;
}

// simple memory deallocator
void free(void* ptr) {}
