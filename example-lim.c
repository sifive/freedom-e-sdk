/* Copyright 2020 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

/*
 *  Example code to demonstrate usage of LIM.
 */
#include <metal/drivers/sifive_ccache0.h>
#include <metal/lim.h>
#include <stdio.h>

#ifdef METAL_SIFIVE_CCACHE0

/* Enable / Disable print statements */
#if 0
#define PRINT(...) printf(__VA_ARGS__)
#else
#define PRINT(...)
#endif

/* 'METAL_PLACE_IN_LIM' allocates the function into LIM region */
__attribute__((noinline)) METAL_PLACE_IN_LIM int run_in_lim(int x) {
  /* Print run_in_lim() start address */
  PRINT("LIM function address: %lx\n", (long unsigned)&run_in_lim);
  return x * x;
}

int main(void) {
  /* Initialize L2 cache */
  sifive_ccache0_init();

  PRINT("***LIM function demo***\n");

  int x = 2;
  int y = run_in_lim(x);

  if (y != 4) {
    PRINT("LIM test failed\n");
    return 1;
  }

  PRINT("LIM test passed\n");

  return 0;
}

#else

int main() { return 0; }

#endif
