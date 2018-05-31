#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

#include "platform.h"
#include "encoding.h"

#define BAUDRATE 115200
#define OTP_CONTENTS_HFROSC_TRIM  2043
#define OTP_CONTENTS_LFROSC_TRIM  2042
#define OTP_CONTENTS_STAMP        2041

unsigned long int gCPU_FREQ=0;

extern int main(int argc, char** argv);
extern void trap_entry();

static unsigned long mtime_lo(void)
{
  return *(volatile unsigned long *)(CLINT_CTRL_ADDR + CLINT_MTIME);
}

#ifdef __riscv32

static uint32_t mtime_hi(void)
{
  return *(volatile uint32_t *)(CLINT_CTRL_ADDR + CLINT_MTIME + 4);
}

uint64_t get_timer_value()
{
  while (1) {
    uint32_t hi = mtime_hi();
    uint32_t lo = mtime_lo();
    if (hi == mtime_hi())
      return ((uint64_t)hi << 32) | lo;
  }
}

#else /* __riscv32 */

uint64_t get_timer_value()
{
  return mtime_lo();
}

#endif

unsigned long get_timer_freq()
{
  return 32768;
}

static void use_hfrosc(int div, int trim)
{
  // Make sure the HFROSC is running at its default setting
  PRCI_REG(PRCI_HFROSCCFG) = (ROSC_DIV(div) | ROSC_TRIM(trim) | ROSC_EN(1));
  while ((PRCI_REG(PRCI_HFROSCCFG) & ROSC_RDY(1)) == 0) ;
  PRCI_REG(PRCI_PLLCFG) &= ~PLL_SEL(1);
}

static void use_pll(int refsel, int bypass, int r, int f, int q)
{
  // Ensure that we aren't running off the PLL before we mess with it.
  if (PRCI_REG(PRCI_PLLCFG) & PLL_SEL(1)) {
    // Make sure the HFROSC is running at its default setting
    use_hfrosc(4, 16);
  }

  // Set PLL Source to be HFXOSC if available.
  uint32_t config_value = 0;

  config_value |= PLL_REFSEL(refsel);

  if (bypass) {
    // Bypass
    config_value |= PLL_BYPASS(1);

    PRCI_REG(PRCI_PLLCFG) = config_value;

    // If we don't have an HFXTAL, this doesn't really matter.
    // Set our Final output divide to divide-by-1:
    PRCI_REG(PRCI_PLLDIV) = (PLL_FINAL_DIV_BY_1(1) | PLL_FINAL_DIV(0));
  } else {
    // In case we are executing from QSPI,
    // (which is quite likely) we need to
    // set the QSPI clock divider appropriately
    // before boosting the clock frequency.

    // Div = f_sck/2
    SPI0_REG(SPI_REG_SCKDIV) = 8;

    // Set DIV Settings for PLL
    // Both HFROSC and HFXOSC are modeled as ideal
    // 16MHz sources (assuming dividers are set properly for
    // HFROSC).
    // (Legal values of f_REF are 6-48MHz)

    // Set DIVR to divide-by-2 to get 8MHz frequency
    // (legal values of f_R are 6-12 MHz)

    config_value |= PLL_BYPASS(1);
    config_value |= PLL_R(r);

    // Set DIVF to get 512Mhz frequncy
    // There is an implied multiply-by-2, 16Mhz.
    // So need to write 32-1
    // (legal values of f_F are 384-768 MHz)
    config_value |= PLL_F(f);

    // Set DIVQ to divide-by-2 to get 256 MHz frequency
    // (legal values of f_Q are 50-400Mhz)
    config_value |= PLL_Q(q);

    // Set our Final output divide to divide-by-1:
    PRCI_REG(PRCI_PLLDIV) = (PLL_FINAL_DIV_BY_1(1) | PLL_FINAL_DIV(0));

    PRCI_REG(PRCI_PLLCFG) = config_value;

    // Un-Bypass the PLL.
    PRCI_REG(PRCI_PLLCFG) &= ~PLL_BYPASS(1);

    // Wait for PLL Lock
    // Note that the Lock signal can be glitchy.
    // Need to wait 100 us
    // RTC is running at 32kHz.
    // So wait 4 ticks of RTC.
    uint32_t now = mtime_lo();
    while (mtime_lo() - now < 4) ;

    // Now it is safe to check for PLL Lock
    while ((PRCI_REG(PRCI_PLLCFG) & PLL_LOCK(1)) == 0) ;
  }

  // Switch over to PLL Clock source
  PRCI_REG(PRCI_PLLCFG) |= PLL_SEL(1);
}

static void use_default_clocks()
{
  // Turn off the LFROSC
  AON_REG(AON_LFROSC) &= ~ROSC_EN(1);

  // Use HFROSC
  use_hfrosc(4, 16);
}

unsigned long get_otp_stamp()
{
   return *((volatile uint32_t*)OTP_MEM_ADDR + OTP_CONTENTS_STAMP);
}

unsigned long mtime_lou(void)
{
  return *(volatile unsigned long *)(CLINT_CTRL_ADDR + CLINT_MTIME);
}

// Wait ms
int wait_ms(int wtime)
{
  uint32_t now = mtime_lou();
  while (mtime_lou() - now < wtime*33) ;
}


static unsigned long __attribute__((noinline)) measure_cpu_freq(size_t n)
{
  unsigned long start_mtime, delta_mtime;
  unsigned long mtime_freq = get_timer_freq();

  // Don't start measuruing until we see an mtime tick
  unsigned long tmp = mtime_lo();
  do {
    start_mtime = mtime_lo();
  } while (start_mtime == tmp);

  unsigned long start_mcycle = read_csr(mcycle);

  do {
    delta_mtime = mtime_lo() - start_mtime;
  } while (delta_mtime < n);

  unsigned long delta_mcycle = read_csr(mcycle) - start_mcycle;

  return (delta_mcycle / delta_mtime) * mtime_freq
         + ((delta_mcycle % delta_mtime) * mtime_freq) / delta_mtime;
}

unsigned long __attribute__((noinline)) cpu_freq(size_t n)
{
  // NB = unsigned long is only big enough for about n=50.
  unsigned long start_mtime, delta_mtime;
  unsigned long mtime_freq = 32768;

  wait_ms(20);

  // Don't start measuring until we see an mtime tick
  unsigned long tmp = mtime_lou();
  do {
    start_mtime = mtime_lou();
  } while (start_mtime == tmp);

  unsigned long start_mcycle = read_csr(mcycle);

  do {
    delta_mtime = mtime_lou() - start_mtime;
  } while (delta_mtime < n);

  unsigned long delta_mcycle = read_csr(mcycle) - start_mcycle;

  return (delta_mcycle * mtime_freq / delta_mtime)
    + ((delta_mcycle % delta_mtime) * mtime_freq) / delta_mtime;
}

unsigned long get_cpu_freq()
{
  if (!gCPU_FREQ) {
    gCPU_FREQ = cpu_freq(10);
  }
  return gCPU_FREQ;
}

unsigned long ugetc(int blocking)
{
  unsigned long pc=UART0_REG(UART_REG_RXFIFO);
  while (blocking && ( pc & 0x80000000 )) pc=UART0_REG(UART_REG_RXFIFO);
  return pc;
}

void uart_set(size_t baud_rate)
{
  GPIO_REG(GPIO_IOF_SEL) &= ~IOF0_UART0_MASK;
  GPIO_REG(GPIO_IOF_EN) |= IOF0_UART0_MASK;
  UART0_REG(UART_REG_DIV) = cpu_freq(10) / baud_rate - 1;
  UART0_REG(UART_REG_TXCTRL) |= UART_TXEN;
  wait_ms(100);
}

static void uart_init(size_t baud_rate)
{
  GPIO_REG(GPIO_IOF_SEL) &= ~IOF0_UART0_MASK;
  GPIO_REG(GPIO_IOF_EN) |= IOF0_UART0_MASK;
  UART0_REG(UART_REG_DIV) = get_cpu_freq() / baud_rate - 1;
  UART0_REG(UART_REG_TXCTRL) |= UART_TXEN;
}



#ifdef USE_PLIC
extern void handle_m_ext_interrupt();
#endif

#ifdef USE_M_TIME
extern void handle_m_time_interrupt();
#endif

uintptr_t handle_trap(uintptr_t mcause, uintptr_t epc)
{
  if (0){
#ifdef USE_PLIC
    // External Machine-Level interrupt from PLIC
  } else if ((mcause & MCAUSE_INT) && ((mcause & MCAUSE_CAUSE) == IRQ_M_EXT)) {
    handle_m_ext_interrupt();
#endif
#ifdef USE_M_TIME
    // External Machine-Level interrupt from PLIC
  } else if ((mcause & MCAUSE_INT) && ((mcause & MCAUSE_CAUSE) == IRQ_M_TIMER)){
    handle_m_time_interrupt();
#endif
  }
  else {
    write(1, "trap\n", 5);
    _exit(1 + mcause);
  }
  return epc;
}

int setpllbits(int pll_r, int pll_f, int pll_q)
{
  // Turn on Crystal Oscillator and wait for it to spin up
  if( !(PRCI_REG(PRCI_HFXOSCCFG) & ROSC_EN(1)) ) {
    PRCI_REG(PRCI_HFXOSCCFG) |= ROSC_EN(1);
    wait_ms(100);
  }

  // Switch Clocking to Crystal Osc.
  PRCI_REG(PRCI_PLLCFG) |= PLL_BYPASS(1);
  wait_ms(50);

  // Switch PLL clocking to Crystal Osc.
  PRCI_REG(PRCI_PLLCFG) |= PLL_REFSEL(1);
  // Make sure PLL is selected.
  PRCI_REG(PRCI_PLLCFG) |= PLL_SEL(1);

  // Write PLL values with constant Q
  PRCI_REG(PRCI_PLLCFG) = (PRCI_REG(PRCI_PLLCFG) & 0xFFFF0000) + PLL_R(pll_r) + PLL_F(pll_f) + PLL_Q(2);
  wait_ms(50); // wait to lose lock

  // Wait for lock, but no more than 100ms.
  if ( PRCI_REG(PRCI_PLLCFG) & PLL_LOCK(1) ) wait_ms(100);

  // Un-bypass the PLL.
  PRCI_REG(PRCI_PLLCFG) &= ~PLL_BYPASS(1);
  wait_ms(50);

  // Write PLL Q Value
  // Unbypassing the PLL at high frequency causes instability
  PRCI_REG(PRCI_PLLCFG) = (PRCI_REG(PRCI_PLLCFG) & 0xFFFF0000) + PLL_R(pll_r) + PLL_F(pll_f) + PLL_Q(pll_q);
  wait_ms(50);

}


int setpll(unsigned long int freq)
{

  // When operating from 16MHz crystal,
  // PLL can divide by (2,3,4)*(2,4,8)
  //  Max divide is 32
  //  Min divide is 4
  // PLL can multiply by 2-128

  int pll_r=PRCI_REG(PRCI_PLLCFG)/PLL_R(1)&0x03;
  int pll_f=PRCI_REG(PRCI_PLLCFG)/PLL_F(1)&0x3F;
  int pll_q=PRCI_REG(PRCI_PLLCFG)/PLL_Q(1)&0x03;

  // Determine Multiplication Factor based on 16MHz Crystal/32
  // 500kHz steps
  int ffactor=freq/500000;
  pll_r=3;
  pll_q=3;

  if(ffactor > 128){ pll_r--; ffactor=ffactor*3/4; }
  if(ffactor > 128){ pll_r--; ffactor=ffactor*2/3; }  
  if(ffactor > 128){ pll_q--; ffactor/=2; }
  if(ffactor > 128){ pll_q--; ffactor/=2; }
  pll_f=ffactor/2-1;
  // Limit VCO frequency to 768MHz
  if(ffactor > 128 ||
     16/(pll_r+1)*(pll_f+1)*2 > 768){ pll_q--; ffactor/=2; }
  pll_f=ffactor/2-1;

  printf("PLL FREF / R * F / Q ==> REF / %d * %d / %d\n", pll_r+1, 2*(pll_f+1), 1 << pll_q);
  printf("PLL FIREF= 6 < %d < 12 MHz, FVCO= 384 < %d < 768 MHz\n",  16/(pll_r+1), 16/(pll_r+1)*(pll_f+1)*2);

  wait_ms(10);

  setpllbits(pll_r, pll_f, pll_q);
  //use_pll(0,0,pll_r,pll_f,pll_q);

  wait_ms(100);
  
  gCPU_FREQ=cpu_freq(10);

  // Re-set the printer thing
  uart_set(BAUDRATE);
}


void _init()
{
  
  #ifndef NO_INIT

  GPIO_REG(GPIO_IOF_EN) = 0;
  GPIO_REG(GPIO_OUTPUT_EN) = 1;
  GPIO_REG(GPIO_OUTPUT_VAL) = 0;
  GPIO_REG(GPIO_INPUT_EN) = 0;
  GPIO_REG(GPIO_PULLUP_EN) = 0xFFFFFFFE;
  
  use_default_clocks();
  use_pll(0, 0, 1, 31, 1);
  uart_init(BAUDRATE);

  printf("core freq at %d Hz\n", get_cpu_freq());

  write_csr(mtvec, &trap_entry);
  if (read_csr(misa) & (1 << ('F' - 'A'))) { // if F extension is present
    write_csr(mstatus, MSTATUS_FS); // allow FPU instructions without trapping
    write_csr(fcsr, 0); // initialize rounding mode, undefined at reset
  }
  #endif

  #ifdef LOWPOWER
  // Turn off LFROSC
  PRCI_REG(AON_LFROSC) &= ~ROSC_EN(1); // On AON POWER
  // Turn off HFROSC
  PRCI_REG(PRCI_HFROSCCFG) &= ~ROSC_EN(1); // 1.4mA on MOFF POWER
  // Turn off HFXOSC
  //  PRCI_REG(PRCI_HFXOSCCFG) &= ~ROSC_EN(1); // Needed for PLL

  PWM0_REG(PWM_CFG) &= ~PWM_CFG_ENALWAYS; // Disable PWM0
  PWM1_REG(PWM_CFG) &= ~PWM_CFG_ENALWAYS; // Disable PWM1
  PWM2_REG(PWM_CFG) &= ~PWM_CFG_ENALWAYS; // Disable PWM2

  UART1_REG(UART_REG_TXCTRL) &= ~UART_TXEN; // Disable UART1 TX
  UART1_REG(UART_REG_TXCTRL) &= ~UART_RXEN; // Disable UART1 RX
  UART1_REG(UART_REG_DIV) = 0xFFFF; // Highest UART1 Divisor

  PRCI_REG(PRCI_PROCMONCFG) = PROCMON_SEL_PROCMON; // Set process mon output
  #endif
}

void _fini()
{
  #ifdef LOWPOWER
  // Turn on LFROSC
  PRCI_REG(AON_LFROSC) |= ROSC_EN(1);
  // Turn on HFROSC
  PRCI_REG(PRCI_HFROSCCFG) |= ROSC_EN(1);  
  #endif
}
