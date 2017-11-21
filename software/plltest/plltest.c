// See LICENSE for license details.

// This demo shows how to use basic
// RISC-V profiling counters, mcycle
// (counts the number of processor cycles)
// and minstret (counts the number of retired instructions). 
// Note that both are writable as well.

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

// The CSR encodings are in this header.
#include "encoding.h"
#include "platform.h"
#include "../utils/utils.h"

int main()
{
  char c=0;
  char cont=1;

  uint32_t myreg;

  unsigned long lowfreq, hifreq;

  int hfrosc_trim=PRCI_REG(PRCI_HFROSCCFG)/ROSC_TRIM(1)&0x1F;
  int hfrosc_div=PRCI_REG(PRCI_HFROSCCFG)/ROSC_DIV(1)&0x3F;

  int pll_r=PRCI_REG(PRCI_PLLCFG)/PLL_R(1)&0x03;
  int pll_f=PRCI_REG(PRCI_PLLCFG)/PLL_F(1)&0x3F;
  int pll_q=PRCI_REG(PRCI_PLLCFG)/PLL_Q(1)&0x03;
  
  UART0_REG(UART_REG_TXCTRL) = UART_TXEN;
  UART0_REG(UART_REG_RXCTRL) = UART_RXEN;
  SPI0_REG(SPI_REG_SCKDIV) = 16;

  wait_ms(100); // wait for clocking to settle

  setpll(100000000);

  wait_ms(100);

  uart_set(BAUDRATE);
  wait_ms(100);
  
  printf(">5>\n555\n>5>\n>>>SiFive\n\n");
  clock_stat();

  while(cont) {
    pll_r=PRCI_REG(PRCI_PLLCFG)/PLL_R(1)&0x03;
    pll_f=PRCI_REG(PRCI_PLLCFG)/PLL_F(1)&0x3F;
    pll_q=PRCI_REG(PRCI_PLLCFG)/PLL_Q(1)&0x03;
    c=wait_for_keypress();
    switch(c) {
    case 'x':
    case 'X':
      cont=0;
      break;

    case 13:
      print_cpu_freq();
      break;

    case '1':
      setpll(100000000);
      break;

    case '2':
      setpll(200000000);
      break;
      
    case '3':
      setpll(300000000);
      break;

    case '4':
      setpll(320000000);
      break;

    case '5':
      setpll(250000000);
      break;

    case '6':
      setpll(150000000);
      break;

    case '7':
      setpll(75000000);
      break;

    case '8':
      setpll(50000000);
      break;

    case '9':
      setpll(25000000);
      break;

    case '0':
      setpll(10000000);
      break;

    case '?':
      printf("# - Autoset PLL 100,200,300,320,350,etc..\n");
      printf("a - Measure HFROSC range\n");
      printf("i/I - Print information.\n");
      printf("b/B - Bypass PLL.\n");
      printf("c/C - Turn off/ON Xtal Osc.\n");
      printf("d/D - Increment/Decrement HFROSC divider.\n");
      printf("f/F - Increment/Decrement PLL F ( Multiplier ).\n");
      printf("l- Set HFROSC Low Trim.\n");
      printf("o/O - Turn off/ON Ring Osc.\n");
      printf("p - Compute ~800 digits of pi.\n");
      printf("P - Compute prime numbers.\n");
      printf("q/Q - Increment/Decrement PLL Q ( Divider ).\n");
      printf("r/R - Increment/Decrement PLL R ( Divider ).\n");
      printf("h/H - Select PLL Reference HFROSC vs HFXOSC.\n");
      printf("s/S - Select PLL Out.\n");
      printf("t/T - Increment/Decrement HFROSC trim.\n");
      printf("u/U - Increment/Decrement UART Divider.\n");
      printf("x/X - eXit\n");
      break;

    case 'c':
      PRCI_REG(PRCI_HFXOSCCFG) &= ~ROSC_EN(1);
      wait_ms(100);
      clock_stat();
      break;

    case 'C':
      PRCI_REG(PRCI_HFXOSCCFG) |= ROSC_EN(1);
      wait_ms(100);
      clock_stat();
      break;

    case 'i':
    case 'I':
      uart_set(BAUDRATE);
      clock_stat();
      break;

    case 'a': // ring osc range
      setringbits(0,1);
      wait_ms(50);
      lowfreq=cpu_freq(50);
      setringbits(0x1F,1);
      wait_ms(50);
      hifreq=cpu_freq(50);
      hfrosc_trim=PRCI_REG(PRCI_HFROSCCFG)/ROSC_TRIM(1)&0x1F;
      hfrosc_div=PRCI_REG(PRCI_HFROSCCFG)/ROSC_DIV(1)&0x3F;
      printf("Ring oscillator range is %d.%d MHz - %d.%d MHz.\n",
	     lowfreq/1000000, lowfreq%1000000/1000,
	     hifreq/1000000, hifreq%1000000/1000);
      break;

    case 'b':
      PRCI_REG(PRCI_PLLCFG) &= ~PLL_BYPASS(1);
      uart_set(BAUDRATE);
      clock_stat();
      break;

    case 'B':
      PRCI_REG(PRCI_PLLCFG) |= PLL_BYPASS(1);
      uart_set(BAUDRATE);
      clock_stat();
      break;

    case 'd':
      if(hfrosc_div>0) hfrosc_div--;
      myreg= (ROSC_DIV(hfrosc_div)+ROSC_TRIM(hfrosc_trim)+ROSC_EN(1));
      PRCI_REG(PRCI_HFROSCCFG) = myreg;
      uart_set(BAUDRATE);
      clock_stat();
      break;

    case 'D':
      if(hfrosc_div < 31 ) hfrosc_div++;
      myreg= (ROSC_DIV(hfrosc_div)+ROSC_TRIM(hfrosc_trim)+ROSC_EN(1));
      PRCI_REG(PRCI_HFROSCCFG) = myreg;
      uart_set(BAUDRATE);
      clock_stat();
      break;

    case 'f':
      if(pll_f > 0 ) pll_f--;
      setpllbits(pll_r, pll_f, pll_q);
      uart_set(BAUDRATE);
      clock_stat();
      break;

    case 'F':
      if(pll_f < 63 ) pll_f++;
      setpllbits(pll_r, pll_f, pll_q);
      uart_set(BAUDRATE);
      clock_stat();
      break;

    case 'h':
      PRCI_REG(PRCI_PLLCFG) &= ~PLL_REFSEL(1);
      uart_set(BAUDRATE);
      clock_stat();
      break;

    case 'H':
      PRCI_REG(PRCI_PLLCFG) |= PLL_REFSEL(1);
      uart_set(BAUDRATE);
      clock_stat();
      break;

    case 'l': // Min Ring OSC
      setringbits(0,1);
      wait_ms(50);
      hfrosc_trim=PRCI_REG(PRCI_HFROSCCFG)/ROSC_TRIM(1)&0x1F;
      hfrosc_div=PRCI_REG(PRCI_HFROSCCFG)/ROSC_DIV(1)&0x3F;
      clock_stat();
      break;

    case 'm': //
      setpwm(20);
      break;

    case 'o':
      PRCI_REG(PRCI_HFROSCCFG) &= ~ROSC_EN(1);
      wait_ms(100);
      clock_stat();
      break;

    case 'O':
      PRCI_REG(PRCI_HFROSCCFG) |= ROSC_EN(1);
      wait_ms(100);
      clock_stat();
      break;

    case 'p':
      getpi();
      break;
      
    case 'P':
      getprimes(1000000);
      break;
      
    case 'q':
      if(pll_q > 1 ) pll_q--;
      setpllbits(pll_r, pll_f, pll_q);
      uart_set(BAUDRATE);
      clock_stat();
      break;

    case 'Q':
      if(pll_q < 3) pll_q++;
      setpllbits(pll_r, pll_f, pll_q);
      uart_set(BAUDRATE);
      clock_stat();
      break;

    case 'r':
      if(pll_r > 0 ) pll_r--;
      setpllbits(pll_r, pll_f, pll_q);
      uart_set(BAUDRATE);
      clock_stat();
      break;

    case 'R':
      if(pll_r < 3 ) pll_r++;
      setpllbits(pll_r, pll_f, pll_q);
      uart_set(BAUDRATE);
      clock_stat();
      break;

    case 's':
      PRCI_REG(PRCI_PLLCFG) &= ~PLL_SEL(1);
      uart_set(BAUDRATE);
      clock_stat();
      break;

    case 'S':
      PRCI_REG(PRCI_PLLCFG) |= PLL_SEL(1);
      uart_set(BAUDRATE);
      clock_stat();
      break;

    case 't':
      if ( hfrosc_trim > 0 ) hfrosc_trim--;
      myreg= (ROSC_DIV(hfrosc_div)+ROSC_TRIM(hfrosc_trim)+ROSC_EN(1));
      PRCI_REG(PRCI_HFROSCCFG) = myreg;
      uart_set(BAUDRATE);
      clock_stat();
      break;

    case 'T':
      if( hfrosc_trim < 31 ) hfrosc_trim++;
      myreg= (ROSC_DIV(hfrosc_div)+ROSC_TRIM(hfrosc_trim)+ROSC_EN(1));
      PRCI_REG(PRCI_HFROSCCFG) = myreg;
      uart_set(BAUDRATE);
      clock_stat();
      break;

    case 'U':
    case 0x95:
      UART0_REG(UART_REG_DIV)=UART0_REG(UART_REG_DIV)+1;
      printf("UART Set div=0x%X.\n", UART0_REG(UART_REG_DIV));
      break;

    case 'u':
    case 0xB5:
      if(UART0_REG(UART_REG_DIV)>0)
	 UART0_REG(UART_REG_DIV)=UART0_REG(UART_REG_DIV)-1;
      printf("UART Set div=0x%X.\n", UART0_REG(UART_REG_DIV));
      break;
      
    default:
      //      uart_set(BAUDRATE);
      //      clock_stat();
      printf("Unknown command %c [0x%X] %c.\n",c,c,c&0x7f);
      break;
    }
  }
      
      




  //  printf("Press Key to select HROSC.\n");
  //  wait_for_keypress();
  //  printf("Pre Reg: %x\n", PRCI_REG(PRCI_PLLCFG));
  //  printf("Post Reg: %x\n", PRCI_REG(PRCI_PLLCFG) & ~PLL_SEL(1));
  //  PRCI_REG(PRCI_PLLCFG) &= ~PLL_SEL(1);
  //  uart_set(BAUDRATE);
  //  wait_ms(100);
  //  clock_stat();
  
  return 0;

}
