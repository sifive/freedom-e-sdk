#include <stdint.h>
#include <unistd.h>

#include "platform.h"

#define HFXTAL

extern int main();

static void freedom_e300_clock_setup()
{
  // This is a very coarse parameterization. To revisit in the future
  // as more chips and boards are added.
  volatile uint32_t * pllcfg     = (volatile uint32_t*)  (PRCI_BASE_ADDR + PRCI_PLLCFG);
  volatile uint32_t * plldiv     = (volatile uint32_t*)  (PRCI_BASE_ADDR + PRCI_PLLDIV);
  volatile uint32_t * hfrosccfg  = (volatile uint32_t*)  (PRCI_BASE_ADDR + PRCI_HFROSCCFG);
  volatile uint32_t * lfrosccfg  = (volatile uint32_t*)  (AON_BASE_ADDR + AON_LFROSC);
  volatile uint64_t * mtimecmp   = (volatile uint64_t*)  (CLINT_BASE_ADDR + CLINT_MTIMECMP);
  volatile uint64_t * mtime      = (volatile uint64_t*)  (CLINT_BASE_ADDR + CLINT_MTIME);

  //Ensure that we aren't running off the PLL before we mess with it.
  if (*pllcfg & PLL_SEL(1)) {
    //Make sure the HFROSC is running at its default setting
    *hfrosccfg  = (ROSC_DIV(4) | ROSC_TRIM(16) | ROSC_EN(1));
    while ((*hfrosccfg & ROSC_RDY(1)) == 0) {}
    *pllcfg &= ~PLL_SEL(1);
  }

  // Set PLL Source to be HFXOSC if available.
  uint32_t config_value = 0;
  
#ifdef HFXTAL
  config_value |= PLL_REFSEL(1);
#else
  // TODO!!!: Setting trim of HFRSOC
#endif

  if (F_CPU == 256000000UL) {

    // In case we are executing from QSPI,
    // (which is quite likely) we need to
    // set the QSPI clock divider appropriately
    // before boosting the clock frequency.

    // Div = f_sck/2
    *(uint32_t*)(SPI0_BASE_ADDR + SPI_REG_SCKDIV) = 8;
    
    // Set DIV Settings for PLL
    // Both HFROSC and HFXOSC are modeled as ideal
    // 16MHz sources (assuming dividers are set properly for
    // HFROSC).
    // (Legal values of f_REF are 6-48MHz)
    
    // Set DIVR to divide-by-2 to get 8MHz frequency
    // (legal values of f_R are 6-12 MHz)
    
    config_value |= PLL_BYPASS(1);
    config_value |= PLL_R(0x1);
    
    // Set DIVF to get 512Mhz frequncy
    // There is an implied multiply-by-2, 16Mhz.
    // So need to write 32-1
    // (legal values of f_F are 384-768 MHz)
    config_value |= PLL_F(0x1F);
    
    // Set DIVQ to divide-by-2 to get 256 MHz frequency
    // (legal values of f_Q are 50-400Mhz)
    config_value |= PLL_Q(0x1);
    
    // Set our Final output divide to divide-by-1:
    *plldiv = (PLL_FINAL_DIV_BY_1(1) | PLL_FINAL_DIV(0));

    *pllcfg = config_value;

    // Un-Bypass the PLL.
    *pllcfg &= ~PLL_BYPASS(1);

    // Wait for PLL Lock
    // Note that the Lock signal can be glitchy.
    // Need to wait 100 us
    // RTC is running at 32kHz. 
    // So wait 4 ticks of RTC.
    uint64_t now = *mtime;
    uint64_t then = now + 4;

    while ((*mtime) < then){ 
    }
    
    // Now it is safe to check for PLL Lock
    while ((*pllcfg & PLL_LOCK(1)) == 0) {
    }

  } else { // if (F_CPU == 16000000UL) TODO:  For all other frequencies, ignore the setting (for now).

    // Bypass
    config_value |= PLL_BYPASS(1);

    *pllcfg = config_value;
    
    // If we don't have an HFXTAL, this doesn't really matter.
    // Set our Final output divide to divide-by-1:
    *plldiv = (PLL_FINAL_DIV_BY_1(1) | PLL_FINAL_DIV(0));
  }
  
  // Switch over to PLL Clock source
  *pllcfg |= PLL_SEL(1);
  
#ifdef HFXTAL
  // Turn off the HFROSC
   * hfrosccfg  &= ~ROSC_EN(1);
#endif
   
#ifdef LFCLKBYPASS
   // Turn off the LFROSC
   * lfrosccfg &= ~ROSC_EN(1);
#endif
}

static void uart_init()
{
  *(uint32_t*)(GPIO_BASE_ADDR + GPIO_IOF_SEL) &= ~IOF0_UART0_MASK;
  *(uint32_t*)(GPIO_BASE_ADDR + GPIO_IOF_EN) |= IOF0_UART0_MASK;
  *(uint32_t*)(UART0_BASE_ADDR + UART_REG_DIV) = 139;
  *(uint32_t*)(UART0_BASE_ADDR + UART_REG_TXCTRL) |= UART_TXEN;
}

void _init()
{
  freedom_e300_clock_setup();
  uart_init();
  _exit(main());
}
