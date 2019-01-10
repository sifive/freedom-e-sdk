#include <errno.h>
#include <stdint.h>
#include <sys/types.h>
#include "platform.h"
#include "encoding.h"
#ifdef SIFIVE_BENCH_TEST
#include "init.h"
#endif

// The code in this file is a mashup of several files from freedom-e-sdk.

// From freedom-e300-arty/init.c

unsigned long get_cpu_freq()
{
#ifdef SIFIVE_BENCH_TEST
  //  Assume 16MHz for now.
  return 16000000;
#else
  // Pretend that the CPU frequency is much lower than it actually is so that we
  // don't need to measure time for as long and can actually feasibly run this
  // in simulation.
  // We need to remember to reverse this operation from the number that
  // Dhrystone reports.
  return 1000;
#endif
}

unsigned long get_timer_freq()
{
  return get_cpu_freq();
}

unsigned long get_timer_value()
{
  return read_csr(mcycle);
}


// From dhry_stubs.c

/* The functions in this file are only meant to support Dhrystone on an
 * embedded RV32 system and are obviously incorrect in general. */

long time(void)
{
  //  return get_timer_value() / get_timer_freq();
  return get_timer_value();
}

// set the number of dhrystone iterations
void __wrap_scanf(const char* fmt, int* n)
{
  *n = 500;
}
