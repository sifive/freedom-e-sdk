// See LICENSE file for license details

#ifndef _FE300PRCI_DRIVER_H_
#define _FE300PRCI_DRIVER_H_

#include <unistd.h>


/* Measure and return the approximate frequency of the 
 * CPU, as given by measuring the mcycle counter against 
 * the mtime ticks.
 */
static uint32_t PRCI_measure_mcycle_freq(uint32_t mtime_ticks, uint32_t mtime_freq);

/* Safely switch over to the HFROSC using the given div
 * and trim settings.
 */
static void PRCI_use_hfrosc(int div, int trim);

/* Safely switch over to the PLL using the given
 * settings.
 * 
 * Note that not all combinations of the inputs are actually
 * legal, and this function does not check for their
 * legality ("safely" means that this function won't turn off
 * or glitch the clock the CPU is actually running off, but
 * doesn't protect against you making it too fast or slow.)
 */

static void PRCI_use_pll(int refsel, int bypass,
			 int r, int f, int q, int finaldiv,
			 int hfroscdiv, int hfrosctrim);

/* Use the default clocks configured at reset.
 * This is ~16Mhz HFROSC and turns off the LFROSC
 * (on the current FE310 Dev Platforms, an external LFROSC is 
 * used as it is more power efficient).
 */
static void PRCI_use_default_clocks();

/* This routine will adjust the HFROSC trim
 * as the PLL clock source, measure the resulting
 * frequency, and attempt to get close to the requested
 * frequency. It returns the actual measured frequency. 
 *
 * Note that the requested frequency must be within the 
 * range supported by the PLL so not all values are 
 * achievable with this function, and not all 
 * are guaranteed to actually work.
 */
uint32_t PRCI_set_hfrosctrim_for_f_cpu(uint32_t f_cpu);

#endif
  
