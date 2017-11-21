#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

// The CSR encodings are in this header.
#include "encoding.h"
#include "platform.h"
#include "utils.h"

unsigned long mtime_lou(void)
{
  return *(volatile unsigned long *)(CLINT_CTRL_ADDR + CLINT_MTIME);
}

int setpwm(int pwmno)
{
  int gpio_no=pwmno;
  
  uint32_t gpio_mask = 1 << gpio_no;
  GPIO_REG(GPIO_OUTPUT_EN) |= gpio_mask; // Turn on output
  GPIO_REG(GPIO_OUTPUT_XOR) |= gpio_mask; // Turn on output
  GPIO_REG(GPIO_IOF_SEL) |= gpio_mask; // Select IO Function 1
  GPIO_REG(GPIO_IOF_EN) |= gpio_mask; // Turn on IO Function

  PWM1_REG(PWM_CFG) = PWM_CFG_ENALWAYS | PWM_CFG_ZEROCMP; // Enable PWM
  PWM1_REG(PWM_S) = 0; // Enable PWM
  PWM1_REG(PWM_COUNT) = 0; // Enable PWM
  PWM1_REG(PWM_CMP0) = 1; // Cycle is 2 counts
  PWM1_REG(PWM_CMP1) = 1; // 
  PWM1_REG(PWM_CMP2) = 1; // 
  PWM1_REG(PWM_CMP3) = 1; // 
}

int setringbits(int trim, int div )
{
  // Turn on Crystal Oscillator and wait for it to spin up
  if( !(PRCI_REG(PRCI_HFXOSCCFG) & ROSC_EN(1)) ) {
    PRCI_REG(PRCI_HFXOSCCFG) |= ROSC_EN(1);
    wait_ms(100);
  }

  // Switch Clocking to Crystal Osc.
  PRCI_REG(PRCI_PLLCFG) |= PLL_BYPASS(1);
  wait_ms(50);
  
  // Turn on ring osc and wait for it to spin up if neeeded.
  if( !(PRCI_REG(PRCI_HFROSCCFG) & ROSC_EN(1)) ) {
    PRCI_REG(PRCI_HFROSCCFG) |= ROSC_EN(1);
    wait_ms(100);
  }
  // Set bit values
  PRCI_REG(PRCI_HFROSCCFG) = (ROSC_DIV(div)+ROSC_TRIM(trim)+ROSC_EN(1));
  wait_ms(50);
  // Make sure PLL is deselected. ( muxes between PLL and HFROSC )
  PRCI_REG(PRCI_PLLCFG) &= ~PLL_SEL(1);
  wait_ms(50);

  // Make sure PLL is deselected ( muxes betwwen HFX and HFR/PLL )
  PRCI_REG(PRCI_PLLCFG) |= PLL_BYPASS(1);
  uart_set(BAUDRATE);
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

  // Re-set the printer thing
  uart_set(BAUDRATE);

  print_cpu_freq();
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

void print_cpu_freq()
{
  unsigned long myfreq=cpu_freq(10);
  printf("CPU Clock is %d.%d MHz\n\n", myfreq/1000000, myfreq%1000000/1000);
}

int getprimes(unsigned long int pmax)
{
  unsigned long int ptest;
  unsigned long int dtest;
  int pcount=0;

  for(ptest=1;ptest<pmax;ptest++) {
    for(dtest=2;dtest<ptest;dtest++) {
      if ( ptest % dtest == 0) break;
    }
    if (check_for_keypress()) break;
    if(dtest>=ptest) {
      printf("%d\n",dtest);
      pcount++;
    }
  }
  printf("\n%d Primes found.\n",pcount);
  return pcount;
}

int getpi() {
    int r[3000 + 1];
    int i, k;
    int b, d;
    int c = 0;
    int f=1;

    for (i = 0; i < 3000; i++) {
        r[i] = 2000;
    }

    for (k = 3000; k > 0; k -= 14) {
        d = 0;

        i = k;
        for (;;) {
            d += r[i] * 10000;
            b = 2 * i - 1;

            r[i] = d % b;
            d /= b;
            i--;
            if (i == 0) break;
            d *= i;
        }
	if (f==1) printf("pi=%d.%.3d", (c + d / 10000)/1000, (c+d/10000)-3000);
	else printf("%.4d", c + d / 10000);
	f+=1;
	if (!(f%12) )    printf("\n");
        c = d % 10000;
    }

    printf("\n");
    return 0;
}

void uart_set(size_t baud_rate)
{
  GPIO_REG(GPIO_IOF_SEL) &= ~IOF0_UART0_MASK;
  GPIO_REG(GPIO_IOF_EN) |= IOF0_UART0_MASK;
  UART0_REG(UART_REG_DIV) = cpu_freq(10) / baud_rate - 1;
  UART0_REG(UART_REG_TXCTRL) |= UART_TXEN;
  wait_ms(100);
}


// Wait for keypress
char wait_for_keypress(){
  int32_t val;
  val=(int32_t) UART0_REG(UART_REG_RXFIFO);
  while(val > 0) val=(int32_t) UART0_REG(UART_REG_RXFIFO);
  while(val < 1) val=(int32_t) UART0_REG(UART_REG_RXFIFO);
  if ( val > 0 ) {
    //    return (char) val&0x7F; // note - cutting off top due to problem at low freq.
    return (char) val&0xFF; 
  }
  return 0;
}

// check for keypress
char check_for_keypress(){
  int32_t val;
  val=(int32_t) UART0_REG(UART_REG_RXFIFO);
  if ( val > 0 ) {
    //    return (char) val&0x7F; // note - cutting off top due to problem at low freq.
    return (char) val&0xFF; 
  }
  return 0;
}

// Wait ms
int wait_ms(int wtime)
{
  uint32_t now = mtime_lou();
  while (mtime_lou() - now < wtime*33) ;
}

int turn_stuff_off()
{
  // Turn off LFROSC
    PRCI_REG(AON_LFROSC) &= ~ROSC_EN(1);
  // Turn off HFROSC
    PRCI_REG(PRCI_HFROSCCFG) &= ~ROSC_EN(1);
  // Turn off HFXOSC
  //  PRCI_REG(PRCI_HFXOSCCFG) &= ~ROSC_EN(1);

  PWM0_REG(PWM_CFG) &= ~PWM_CFG_ENALWAYS; // Disable PWM0
  PWM1_REG(PWM_CFG) &= ~PWM_CFG_ENALWAYS; // Disable PWM1
  PWM2_REG(PWM_CFG) &= ~PWM_CFG_ENALWAYS; // Disable PWM2

  UART1_REG(UART_REG_TXCTRL) &= ~UART_TXEN; // Disable UART1 TX
  UART1_REG(UART_REG_TXCTRL) &= ~UART_RXEN; // Disable UART1 RX
  UART1_REG(UART_REG_DIV) = 0xFFFF; // Highest UART Divisor

}

int clock_stat()
{
  if( AON_REG(AON_LFROSC) & ROSC_EN(1) )
    printf("LFROSC is ON\n");
  else
    printf("LFROSC is off\n");

  if ( PRCI_REG(PRCI_HFROSCCFG) & ROSC_EN(1))
    printf("HFROSC is ON");
  else
    printf("HFROSC is off");

    if ( PRCI_REG(PRCI_HFROSCCFG) & ROSC_RDY(1))
    printf(" and READY\n");
  else
    printf(" and not ready\n");

  if ( PRCI_REG(PRCI_HFXOSCCFG) & ROSC_EN(1))
    printf("HFXOSC is ON");
  else
    printf("HFXOSC is off");

  if ( PRCI_REG(PRCI_HFXOSCCFG) & ROSC_RDY(1))
    printf(" and READY\n");
  else
    printf(" and not ready\n");

  if( PRCI_REG(PRCI_PLLCFG) & PLL_SEL(1) )
    printf("PLL is SELECTED.\n");
  else
    printf("PLL is deselected to HFROSC.\n");

  if ( PRCI_REG(PRCI_PLLCFG) & PLL_BYPASS(1))
    printf("PLL is BYPASSED to HFXOSC.\n");
  else
    printf("PLL is not bypassed\n");


  if( PRCI_REG(PRCI_PLLCFG) & PLL_REFSEL(1) )
    printf("PLL reference is HFXOSC\n");
  else
    printf("PLL reference is HFROSC\n");

  if( PRCI_REG(PRCI_PLLCFG) & PLL_LOCK(1))
    printf("PLL is LOCKED\n");
  else
    printf("PLL is unlocked\n");

  int lpll_r=PRCI_REG(PRCI_PLLCFG)/PLL_R(1)&0x03;
  int lpll_f=PRCI_REG(PRCI_PLLCFG)/PLL_F(1)&0x3F;
  int lpll_q=PRCI_REG(PRCI_PLLCFG)/PLL_Q(1)&0x03;

  printf("PLL FREF / R * F / Q ==> REF / %d * %d / %d\n", lpll_r+1, 2*(lpll_f+1), 1 << lpll_q);
  unsigned long myfreq=cpu_freq(10);
  printf("PLL FIREF= 6 < %d < 12 MHz, FVCO= 384 < %d < 768 MHz\n",  myfreq*(1<<lpll_q)/(2*(lpll_f+1))/1000000, myfreq*(1<<lpll_q)/1000000);

  printf("HFROSC Trim=0x%x", PRCI_REG(PRCI_HFROSCCFG)/ROSC_TRIM(1)&0x1F);
  printf(" Div=0x%x\n", PRCI_REG(PRCI_HFROSCCFG)/ROSC_DIV(1)&0x3F);
  printf("UART Set div=0x%X.\n", UART0_REG(UART_REG_DIV));

  print_cpu_freq();

}
