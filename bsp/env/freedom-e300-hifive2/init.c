// See LICENSE for license details.

// This file contains utilities for working with Freedom Everywhere parts on
// the bench, including programming OTP, I2C interface, UART Interface
// and so on.

#include <stdint.h>
#include "platform.h"
#include <unistd.h>

#define GPIO_LED_RED 22
#define GPIO_LED_GREEN 19
#define GPIO_LED_BLUE 21

#define CORE_CLK_MHZ 16

#define TPP   50000
#define TSPP 400000
#define TPR     400
#define TVPP    500
#define TVRRS  3000
#define TAS       9
#define TDS       1

#define ERROR_ALREADY_BURNED -1

#define OTP_WORDS 2048

#define OTP_CONTENTS_FIRST_JUMP   0
#define OTP_CONTENTS_LIFECYCLE    2044
#define OTP_CONTENTS_HFROSC_TRIM  2043
#define OTP_CONTENTS_LFROSC_TRIM  2042
#define OTP_CONTENTS_STAMP        2041
#define OTP_CONTENTS_LAST_FENCE   2045

#define OTP_STAMP_MAGIC AON_REG(AON_BACKUP0)

#define TRIM_FREQ 72000000

#define BAUDRATE 115200

#ifndef UART0_REG
#define UART0_REG UART_REG
#endif

int print_to_uart1 = 0;

uint32_t lfosc_freq=32768;

// Read the machine cycle counter ( core clk freq )
uint64_t rd64cycle()
{
  uint32_t lo, hi;
  __asm__ __volatile__ ("csrr %0, mcycle\n\t"
                        "csrr %1, mcycleh"
                        : "=r" (lo), "=r" (hi));
  return lo | ((uint64_t)hi << 32);
}


// Measure CPU frequency based on LFOSC frequency.  Note that
// LFOSC frequency is normally 32768Hz, but will vary if
// LFROSC or LFRCOSC are used.
uint32_t measure_cpu_freq(uint32_t n, uint32_t mtime_freq)
 {
   // Remove any chance of rollover.
   CLINT_REG(CLINT_MTIME) = 0;

   uint32_t start_mtime = CLINT_REG(CLINT_MTIME);
   uint64_t start_mcycle = rd64cycle();
   
   while ((CLINT_REG(CLINT_MTIME) - start_mtime) < n) ;
   
   uint64_t end_mcycle = rd64cycle();
   uint32_t difference = end_mcycle - start_mcycle;
   
   return ((difference/n)*mtime_freq);
 }


#ifndef MINBENCH
// Write To UART
void _putc(char c) {
  if ( print_to_uart1 ) {
#ifdef UART1_IOF_MASK
    while ((int32_t) UART1_REG(UART_REG_TXFIFO) < 0);
    UART1_REG(UART_REG_TXFIFO) = c;
#endif
  } else {
    while ((int32_t) UART0_REG(UART_REG_TXFIFO) < 0);
    UART0_REG(UART_REG_TXFIFO) = c;    
  }
}

// return random value from timebase if passed 0
// OR return lfsr shift of passed value.
uint32_t lfsr32(uint32_t x)
{
  if (!x) x = rd64cycle() & 0xFFFFFFFF;
  uint32_t bit = (x ^ (x >> 10) ^ (x >> 30) ^ (x >> 31)) & 1;
  return (x >> 1) | (bit << 31);
}
 

//  This will put out HFOSC/1024 on GPIO5 for measurement
void hang_hfout()
{
  GPIO_REG(GPIO_OUTPUT_EN) |= 0x1 << 5;  
  while(1) {
      while((rd64cycle()>>9)%2);      
      GPIO_REG(GPIO_OUTPUT_VAL) |= 0x00000020;    
      while(!((rd64cycle()>>9)%2));
      GPIO_REG(GPIO_OUTPUT_VAL) &= 0xFFFFFFDF;
  }
}

// Wait for a keypress.  blocking != 0 means you wait.
//  you can also just check for a cached keypress.
//  glitter != 0 means flash the LEDs and output
//  one of the clk frequencies on GPIO5.
char _getc(int blocking, int glitter) {
  int32_t val;
  unsigned long i=0,k=0;
#ifdef UART1_IOF_MASK
  if (print_to_uart1)
    val = (int32_t) UART1_REG(UART_REG_RXFIFO);
  else
#endif
    val=(int32_t) UART0_REG(UART_REG_RXFIFO);

  if (blocking) {
    while(val > 0) {
#ifdef UART1_IOF_MASK
      if (print_to_uart1)
	val = (int32_t) UART1_REG(UART_REG_RXFIFO);
      else
#endif
	val=(int32_t) UART0_REG(UART_REG_RXFIFO);      
    }
    
    while(val < 1) {
      // This should either put out LFCLK/2 or HFCLK/1024.
      // NOTE that MTIME bit 0 is HALF the LFCLK frequency
#ifdef UART1_IOF_MASK    
      if (print_to_uart1)
	val = (int32_t) UART1_REG(UART_REG_RXFIFO);
      else
#endif
	val=(int32_t) UART0_REG(UART_REG_RXFIFO);      
      //while( (CLINT_REG(CLINT_MTIME) % 2) ) ;
      while((rd64cycle()>>9)%2);      
      GPIO_REG(GPIO_OUTPUT_VAL) |= 0x00000020;    
      //while( ! (CLINT_REG(CLINT_MTIME) % 2) ) ;
      while(!((rd64cycle()>>9)%2));
      GPIO_REG(GPIO_OUTPUT_VAL) &= 0xFFFFFFDF;
      
      if ( i++ > 500 && glitter) {
	k++; i=0;
	GPIO_REG(GPIO_OUTPUT_VAL) &= 0xFFF03FFF;
	GPIO_REG(GPIO_OUTPUT_VAL) |= (k%0x40)<<14;
      }
    }
  }
  if ( val > 0 ) {
    return (char) val&0xFF; 
  }
  return 0;
}


// Put a string out the UART.  Should be terminated by \r\n
void _puts(const char * s) {
  while (*s != '\0'){
    _putc(*s++);
  }
}

// Print Integer
// This reverses the integer and then prints that reversed
// number out so that we skip leading zeros but keep
// trailing zeros.
void _puti( uint32_t i) {
  uint32_t j=0;
  // Deal with negative numbers
  if( i & 0x80000000 ) {
    _putc('-');
    i=~i + 1;
  }
  int k=0;
  while( i>0 ) {
    j*=10;
    j+=i%10;
    i/=10;
    k++;
  }
  if (!k) k=1;
  while(k--){
    _putc('0'+j%10);
    j/=10;
  }
}

// Print Integer / 1000.  Useful in printing mA from uA and so on.
void _puti1k( unsigned long i) {
  _puti(i/1000);
  _putc('.');
  // Note that we cannot use _puti() here because we need to print
  // leading zeroes.
  for(int k=0;k<3;k++) {
    i=i%1000;    
    _putc('0'+i/100);
    i*=10;
  }
}

// Print Hex Word
void _puth( unsigned long i) {
  int j;
  _putc('0');
  _putc('x');  
  for (j=0;j<8;j++) {
    if (i/0x10000000 < 10) _putc('0'+i/0x10000000);
    else _putc('a'+i/0x10000000-10);
    i=i*16;
  }
}

// Error printer, returns same error.
//  This is used for adding an error message to error returns.
int errpt ( int error, char *test )
{
  if (!error) {
    _puts(test);
    _puts(" PASSED\r\n");
  } else {
    _puts("\r\nERROR: ");    
    _puts(test);
    _puts(" FAILED WITH CODE ");
    _puti(error);
    _puts("\r\n");        
  }
  return error;
}

// Sleep a number of nanoseconds.  Sort of.
// *Assumes* CORE_CLK_MHZ defined above, so of limited use.
void nanosleep(unsigned nsec)
{
  const unsigned nsec_per_cycle = 1000 / CORE_CLK_MHZ;
  const uint64_t end = rd64cycle() + ((nsec - 1) / nsec_per_cycle + 1);

  while (rd64cycle() < end)
    ;
}

//  Wait for a number of ms mased of LFOSC.  Assumes LFOSC is correct.
//  Will vary with different LFOSC.
void wait_ms(int wtime)
{
  // Lives by zeroing out mtime just to be sure
  CLINT_REG(CLINT_MTIME) = 0;
  while (CLINT_REG(CLINT_MTIME) < wtime*33) ;
}


// Wait a number of clicks of the LFCLK.  For shorter waits that 1ms.
void wait_lfclicks(int wtime)
{
  // Lives by zeroing out mtime just to be sure
  CLINT_REG(CLINT_MTIME) = 0;
  while (CLINT_REG(CLINT_MTIME) < wtime) ;
}

// Set UART frequency.  lfosc_freq MUST be initialized first.
void uart_set(size_t baud_rate)
{
  wait_ms(100);
#ifdef UART1_IOF_MASK  
  if ( print_to_uart1 ) {  
    GPIO_REG(GPIO_IOF_SEL) &= ~UART1_IOF_MASK;
    GPIO_REG(GPIO_IOF_EN) |= UART1_IOF_MASK;
    UART1_REG(UART_REG_DIV) = measure_cpu_freq(3000,lfosc_freq) / baud_rate - 1;
    UART1_REG(UART_REG_TXCTRL) |= UART_TXEN;
  } else {
#endif
    GPIO_REG(GPIO_IOF_SEL) &= ~UART0_IOF_MASK;
    GPIO_REG(GPIO_IOF_EN) |= UART0_IOF_MASK;
    UART0_REG(UART_REG_DIV) = measure_cpu_freq(3000,lfosc_freq) / baud_rate - 1;
    UART0_REG(UART_REG_TXCTRL) |= UART_TXEN;
#ifdef UART1_IOF_MASK    
  }
#endif
  wait_ms(100);
}

// Set HFCLK source to ring oscillator with a certain trim/div.
void setringbits(int trim, int div )
{
  // Turn on Crystal Oscillator and wait for it to spin up
  if( !(FREEDOME300PRCI_REG(FREEDOME300PRCI_HFXOSCCFG) & ROSC_EN(1)) ) {
    FREEDOME300PRCI_REG(FREEDOME300PRCI_HFXOSCCFG) |= ROSC_EN(1);
    wait_ms(100);
  }

  // Switch Clocking to Crystal Osc.
  FREEDOME300PRCI_REG(FREEDOME300PRCI_PLLCFG) |= PLL_BYPASS(1);
  wait_ms(50);
  
  // Turn on ring osc and wait for it to spin up if neeeded.
  if( !(FREEDOME300PRCI_REG(FREEDOME300PRCI_HFROSCCFG) & ROSC_EN(1)) ) {
    FREEDOME300PRCI_REG(FREEDOME300PRCI_HFROSCCFG) |= ROSC_EN(1);
    wait_ms(100);
  }
  // Set bit values
  FREEDOME300PRCI_REG(FREEDOME300PRCI_HFROSCCFG) = (ROSC_DIV(div)+ROSC_TRIM(trim)+ROSC_EN(1));
  wait_ms(50);
  // Make sure PLL is deselected. ( muxes between PLL and HFROSC )
  FREEDOME300PRCI_REG(FREEDOME300PRCI_PLLCFG) &= ~PLL_SEL(1);
  wait_ms(50);

  // Make sure PLL is deselected ( muxes betwwen HFX and HFR/PLL )
  FREEDOME300PRCI_REG(FREEDOME300PRCI_PLLCFG) |= PLL_BYPASS(1);
  uart_set(BAUDRATE);
}

// Set HFCLK source to PLL with certain settings.
void setpllbits(int pll_r, int pll_f, int pll_q)
{
  /*
  _puts("Setting PLL: R=");
  _puti(pll_r);
  _puts(" F=");
  _puti(pll_f);
  _puts(" Q=");
  _puti(pll_q);
  _puts("\r\n");
  // Wait to clear UART buffer
  wait_ms(10);
  */
  
  // Turn on Crystal Oscillator and wait for it to spin up
  if( !(FREEDOME300PRCI_REG(FREEDOME300PRCI_HFXOSCCFG) & ROSC_EN(1)) ) {
    FREEDOME300PRCI_REG(FREEDOME300PRCI_HFXOSCCFG) |= ROSC_EN(1);
    wait_ms(10);
  }

  // Switch Core Clocking to Crystal Osc.
  FREEDOME300PRCI_REG(FREEDOME300PRCI_PLLCFG) |= PLL_BYPASS(1);
  wait_ms(5);

  // Switch PLL clocking to Crystal Osc.
  FREEDOME300PRCI_REG(FREEDOME300PRCI_PLLCFG) |= PLL_REFSEL(1);
  // Make sure PLL is selected.
  FREEDOME300PRCI_REG(FREEDOME300PRCI_PLLCFG) |= PLL_SEL(1);

  // Write PLL values with constant Q
  FREEDOME300PRCI_REG(FREEDOME300PRCI_PLLCFG) = (FREEDOME300PRCI_REG(FREEDOME300PRCI_PLLCFG) & 0xFFFF0000) + PLL_R(pll_r) + PLL_F(pll_f) + PLL_Q(pll_q);
  wait_ms(10); // wait to lose lock if it's going to lose lock

  // Wait for lock, but no more than 500ms.
  if ( FREEDOME300PRCI_REG(FREEDOME300PRCI_PLLCFG) & PLL_LOCK(1) ) wait_ms(500);

  // Un-bypass the PLL.
  FREEDOME300PRCI_REG(FREEDOME300PRCI_PLLCFG) &= ~PLL_BYPASS(1);
  //  wait_ms(50);

  // Write PLL Q Value
  // Unbypassing the PLL at high frequency seems to cause instability
  //  FREEDOME300PRCI_REG(FREEDOME300PRCI_PLLCFG) = (FREEDOME300PRCI_REG(FREEDOME300PRCI_PLLCFG) & 0xFFFF0000) + PLL_R(pll_r) + PLL_F(pll_f) + PLL_Q(pll_q);
  //  wait_ms(50);

}

// Set HFCLK to PLL at freq ( in Hz )
void setpll(unsigned long int freq)
{

  // When operating from 16MHz crystal,
  // PLL can divide by (2,3,4)*(2,4,8)
  //  Max divide is 32
  //  Min divide is 4
  // PLL can multiply by 2-128

  int pll_r=FREEDOME300PRCI_REG(FREEDOME300PRCI_PLLCFG)/PLL_R(1)&0x03;
  int pll_f=FREEDOME300PRCI_REG(FREEDOME300PRCI_PLLCFG)/PLL_F(1)&0x3F;
  int pll_q=FREEDOME300PRCI_REG(FREEDOME300PRCI_PLLCFG)/PLL_Q(1)&0x03;

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

  wait_ms(10);

  setpllbits(pll_r, pll_f, pll_q);

  // Re-set the printer thing
  uart_set(BAUDRATE);
}

#ifdef OTP_LOCK
#ifndef SKIP_OTP
void otp_get_lock()
{
  do {
    OTP_REG(OTP_LOCK) = 1;
  } while (!OTP_REG(OTP_LOCK));
}

void otp_release_lock()
{
  OTP_REG(OTP_LOCK) = 0;
}

void otp_begin_write()
{
  otp_get_lock();
  OTP_REG(OTP_VPPEN) = 1;
  OTP_REG(OTP_WE) = 1;
  OTP_REG(OTP_MRR) = 4;
  nanosleep(TVPP);
}

void otp_end_write()
{
  OTP_REG(OTP_MRR) = 0;
  OTP_REG(OTP_WE) = 0;
  OTP_REG(OTP_VPPEN) = 0;
  nanosleep(TVRRS);
  otp_release_lock();
}

void otp_write_word(int idx, uint32_t data, unsigned tpp)
{
  if (data == 0)
    return;

  OTP_REG(OTP_A) = idx;
  nanosleep(TAS);

  for (int i = 0; i < sizeof(data) * 8; i++) {
    if ((data >> i) & 1) {
      OTP_REG(OTP_D) = ((data >> i) & 1) << i;
      nanosleep(TDS);
      OTP_REG(OTP_CK) = 1;
      nanosleep(tpp);
      OTP_REG(OTP_CK) = 0;
      nanosleep(TPR);
    }
  }
}

uint32_t otp_read_word(int idx)
{
  return *((volatile uint32_t*)OTP_MEM_ADDR + idx);
}

// Note - as modified this does not zap ones in the original data.
//  It just checks that ones were all written.
//  Because a lot of times, the data is in non-volatile memory.
uint32_t zap_ones(int offset, uint32_t* a, int n)
{
  uint32_t res = 0;
  for (int i = 0; i < n; i++) {
    res |= (a[i] & ~otp_read_word(i + offset));
  }
  return res;
}

uint32_t otp_write_array_once(int offset,
                                     uint32_t* a,
                                     int n,
                                     unsigned tpp)
{
  otp_begin_write();
  for (int i = 0; i < n; i++)
    otp_write_word(i + offset, a[i], TPP);
  otp_end_write();

  return zap_ones(offset, a, n);
}

int otp_write_array(uint32_t offset,
                           uint32_t* a,
                           int n)
{

  // Check once more time -- don't allow old set bits
  // unless you're planning to write those.
  for (int j = 0; j < n; j++){
    if (otp_read_word(j + offset) & (~(a[j]))) {
      return (__LINE__);
    }
  }

  //  zap_ones(offset, a, n);

  if (otp_write_array_once(offset, a, n, TPP) == 0)
    return 0;

  // Following is the algorithm for handling bits that failed to program
  // with fast programming pulses.  In simulation, we should never get here.
  for (int i = 0; i < 10; i++)
    if (otp_write_array_once(offset, a, n, TSPP) == 0)
      return 0;

  return __LINE__;
}

#endif
#endif
#endif
//  Measures LFOSC frequency using 16MHz external crystal as a reference.
//  This is so LFOSC can be used as a reference later in the program.
uint32_t measure_lfosc_freq()
{

   // Run off 16 MHz Crystal for accuracy on burns and UART.
   FREEDOME300PRCI_REG(FREEDOME300PRCI_PLLCFG) = (PLL_REFSEL(1) | PLL_BYPASS(1));
   FREEDOME300PRCI_REG(FREEDOME300PRCI_PLLCFG) |= (PLL_SEL(1));
   
   //  Let's *not* assume LFRCOSC is 32kHz.  This should be 16MHz, but
   //  if LFRCOSC is not 32kHz, it won't be.
   uint32_t freq_scale = measure_cpu_freq(3000, 32768)/1000;
   // freq_scale should be 16MHz, but will be more if lfrcosc is slow.

   lfosc_freq = 32768 * 16000 / freq_scale;

   return lfosc_freq;
}

// Reset the clock to use 16MHz crystal and set lfosc_freq variable
void bench_rstclk()
{

  // Set NO QSPI Mode  
  SPI0_REG(SPI_REG_FMT) &= ~(0x03); 

  // Turn off interrupts at the source
  clear_csr(mstatus, MSTATUS_MIE); 

  // Reset all outputs
  GPIO_REG(GPIO_OUTPUT_EN)=0x0;
  GPIO_REG(GPIO_IOF_EN)=0x0;
  GPIO_REG(GPIO_OUTPUT_VAL)=0x0;
  GPIO_REG(GPIO_OUTPUT_XOR)=0x0;  

  // Stuff here is just for printing for users info*/
  // Configure UART to print
#ifdef UART1_IOF_MASK
  if ( print_to_uart1 ) {  
    GPIO_REG(GPIO_OUTPUT_VAL) |= UART1_IOF_MASK;
    GPIO_REG(GPIO_OUTPUT_EN) |= UART1_IOF_MASK;
    SET_BITS(GPIO_REG(GPIO_IOF_SEL), UART1_IOF_MASK, UART1_IOF_NUMBER);
    GPIO_REG(GPIO_IOF_EN) |= UART1_IOF_MASK;

    // 115200 Baud Rate
    UART1_REG(UART_REG_DIV) = 138;
    UART1_REG(UART_REG_TXCTRL) = (UART_TXEN | UART_TXWM(1));
    UART1_REG(UART_REG_RXCTRL) = UART_RXEN;
  } else {
#endif
    GPIO_REG(GPIO_OUTPUT_VAL) |= UART0_IOF_MASK;
    GPIO_REG(GPIO_OUTPUT_EN) |= UART0_IOF_MASK;
    SET_BITS(GPIO_REG(GPIO_IOF_SEL), UART0_IOF_MASK, UART0_IOF_NUMBER);
    GPIO_REG(GPIO_IOF_EN) |= UART0_IOF_MASK;

    // 115200 Baud Rate
    UART0_REG(UART_REG_DIV) = 138;
    UART0_REG(UART_REG_TXCTRL) = (UART_TXEN | UART_TXWM(1));
    UART0_REG(UART_REG_RXCTRL) = UART_RXEN;
#ifdef UART1_IOF_MASK
  }
#endif
  
  // Wait a bit because we were screwing with the GPIOs
  volatile int i=0;
  while(i < 10000){i++;}
  
  // Done configuring UART
  
  // Run off 16 MHz Crystal for accuracy.
  
  FREEDOME300PRCI_REG(FREEDOME300PRCI_PLLCFG) = (PLL_REFSEL(1) | PLL_BYPASS(1));
  FREEDOME300PRCI_REG(FREEDOME300PRCI_PLLCFG) |= (PLL_SEL(1));

  measure_lfosc_freq();

  #ifndef MINBENCH

  _puts("\e[1F"); // cursor to beginning of line
  _puts("\e[0J"); // clear from cursor to end of screen
  _puts("\e[?25h"); // show cursor
  _puts("\e[0;39;49m"); // default fg/bg colors.  No bold/etc.
  _puts("Bench Clock Reset Complete\r\n");

  #endif
}

void _init()
{
  #ifndef NO_INIT
  bench_rstclk();
  #endif
}


void _fini()
{
}
