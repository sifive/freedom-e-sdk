// See LICENSE for license details.

#include <stdint.h>
#include "platform.h"
#include <unistd.h>
#include <string.h>
#include "init.h"
#ifdef HASESP32
#include <esp32/esp32.h>
#endif
#define FISHR ">))'>"
#define FISHL "<'((<"

#define NUMFISH 10
#define FISHMINX 1
#define FISHMAXX 65
#define FISHMINY 1
#define FISHMAXY 22

#define GPIO_LED_RED 22
#define GPIO_LED_GREEN 19
#define GPIO_LED_BLUE 21
#define GPIO_LED_MASK  ((uint32_t) 1 << GPIO_LED_RED) | ((uint32_t) 1 << GPIO_LED_GREEN) | ((uint32_t) 1 << GPIO_LED_BLUE)

#ifdef HASE24
#define MYMESSAGE "SiFive E2 CoreIP - FE240-G000 - E21 Core + FPU + 64K SRAM + CLIC - "
#else
#define MYMESSAGE "SiFive E3 CoreIP - FE340-G000 - E31 Core + 32K SRAM - HiFive1 - "
#endif

//Fish Colors
//30	black
//31	red
//32	green
//33	yellow
//34	blue
//35	magenta
//36	cyan
//37	white

void drawtext(int xset, char *xmsg)
{
  char c=xmsg[xset];
  _puts("\e[");
  _puti(FISHMAXY+1);
  _puts(";");
  _puti(0);
  _puts("f");
  _puts("\e[");
  _puti(37);
  _puts("m");    
  _puts(xmsg+xset);
  if(xset) {
    xmsg[xset]=0;
    _puts(xmsg);
    xmsg[xset]=c;
  }
}

void drawfish(int xpos, int ypos, int color, int dir)
{
  _puts("\e[");
  _puti(ypos);
  _puts(";");
  _puti(xpos);
  _puts("f");
  _puts("\e[");
  _puti(color);
  _puts("m");  
  if (dir<0) _puts(FISHL);
  else _puts(FISHR);
}


int main()
{
  uint32_t lfsr = lfsr32(0); // Init Random

  int fishposx[NUMFISH];
  int fishposy[NUMFISH];
  int fishcolor[NUMFISH];
  int fishdir[NUMFISH];
  
  int i=0,k=0;
  int xset=0;

  char mymessage[]=MYMESSAGE;
  

  // Init Fish.
  bench_rstclk();
  GPIO_REG(GPIO_IOF_EN) &= ~(GPIO_LED_MASK);
  GPIO_REG(GPIO_OUTPUT_EN) |= GPIO_LED_MASK;
  GPIO_REG(GPIO_OUTPUT_XOR) |= GPIO_LED_MASK;

  //Set 3,5,9 LOW for MOSI, SCK and CS2
  GPIO_REG(GPIO_OUTPUT_EN)  |= 0x228;    

  _puts("Spawning fishes...\r\n");
  
  for(i=0;i<NUMFISH;i++) {
    lfsr=lfsr32(lfsr);
    fishposx[i]=lfsr%(FISHMAXX-FISHMINX)+FISHMINX;
    lfsr=lfsr32(lfsr);
    fishposy[i]=lfsr%(FISHMAXY-FISHMINY)+FISHMINY;
    lfsr=lfsr32(lfsr);
    fishcolor[i]=31+lfsr%7;
    lfsr=lfsr32(lfsr);
    if (lfsr%2) fishdir[i]=1;
    else fishdir[i]=-1;
  }
  
  GPIO_REG(GPIO_OUTPUT_VAL) |= ((uint32_t) 1 << GPIO_LED_BLUE);
  setpll(125000000);
  //  UART_REG(UART_REG_DIV) = 170;
  GPIO_REG(GPIO_OUTPUT_VAL) |= ((uint32_t) 1 << GPIO_LED_GREEN);
  
  #ifdef HASESP32
  spi_ctrl* spictrl=(spi_ctrl*) SPI1_CTRL_ADDR;
  esp32_init();
  if ( at_sendrecv(spictrl, "AT+CWMODE=1\r\n",100) < 0) {
    GPIO_REG(GPIO_OUTPUT_VAL) |= ((uint32_t) 1 << GPIO_LED_RED);
    GPIO_REG(GPIO_OUTPUT_VAL) &= ~((uint32_t) 1 << GPIO_LED_GREEN);
    GPIO_REG(GPIO_OUTPUT_VAL) &= ~((uint32_t) 1 << GPIO_LED_BLUE);
  }
  if ( at_sendrecv(spictrl, "AT+CWLAP\r\n",1000) < 0)
    GPIO_REG(GPIO_OUTPUT_VAL) |= ((uint32_t) 1 << GPIO_LED_RED);
  at_sendrecv(spictrl, "AT+CWMODE=0\r\n",100);
  at_sendrecv(spictrl, "AT+SLEEP=1\r\n",100);  
  wait_ms(2000);
  #endif


  _puts("\e[?25l"); // Hide Cursor
  int j;
  for(j=0;;j++) {
    if (j%2) xset++;
    if (xset>strlen(mymessage)) xset=0;
    _puts("\e[2J"); // Clear Screen
    drawtext(xset,mymessage);
    for(i=0;i<NUMFISH;i++) {  
      drawfish(fishposx[i], fishposy[i],fishcolor[i],fishdir[i]);
    }
    k++;k=k%8;
    GPIO_REG(GPIO_OUTPUT_VAL) &= ~(GPIO_LED_MASK);
    if (!(k%2))
      GPIO_REG(GPIO_OUTPUT_VAL) |= ((uint32_t) 1 << GPIO_LED_RED);
    if (!((k/2)%2))
      GPIO_REG(GPIO_OUTPUT_VAL) |= ((uint32_t) 1 << GPIO_LED_GREEN);
    if (!((k/4)%2))
      GPIO_REG(GPIO_OUTPUT_VAL) |= ((uint32_t) 1 << GPIO_LED_BLUE);
    
    for(i=0;i<NUMFISH;i++) {
      lfsr=lfsr32(lfsr);      
      if ( lfsr % 40  > 1 ) {
	fishposx[i] += fishdir[i];
	if ( fishposx[i]<=FISHMINX ) fishdir[i]=1;
	if ( fishposx[i]>=FISHMAXX ) fishdir[i]=-1;
	lfsr=lfsr32(lfsr);
	if ( fishposx[i] % 5 == 0 && !(lfsr%5) ) {
	  lfsr=lfsr32(lfsr);      
	  if (lfsr % 2 ) fishposy[i]++;
	  else fishposy[i]--;
	  if ( fishposy[i] < FISHMINY ) fishposy[i]+=2;
	  if ( fishposy[i] > FISHMAXY ) fishposy[i]-=2;      
	}
      }
    }

    wait_ms(50);
  }
  return 0;
}
