// See LICENSE for license details.

#include <stdio.h>
#include <stdlib.h>
#include "platform.h"
#include <string.h>
#include "encoding.h"
#include <unistd.h>
#include "sifive/devices/clic.h"

#ifndef _SIFIVE_COREPLEXIP_ARTY_H
#error 'local_interrupts' demo only supported for Coreplex IP Eval Kits
#endif

// Global Variable used to show
// software interrupts.
volatile uint32_t g_debouncing;

void debounce();

static void clic_enable(int offset) __attribute__((noinline));
static void clic_enable(int offset)
{
  CLIC_REG8(CLIC_INTCFG + offset) = 0xff;
  CLIC_REG8(CLIC_INTIE  + offset) = 1;
}

static void clic_disable(int offset) __attribute__((noinline));
static void clic_disable(int offset)
{
  CLIC_REG8(CLIC_INTCFG + offset) = 0xff;
  CLIC_REG8(CLIC_INTIE  + offset) = 0;
}

// Structures for registering different interrupt handlers
// for different parts of the application.
typedef void (*interrupt_function_ptr_t) (void);

// This function enables some of the local interrupts sources
// used in this demo -- just those for the buttons and
// Switch 3.

void enable_local_interrupts(){
  clic_enable(IRQ_M_LOCAL + LOCAL_INT_SW_3);
  clic_enable(IRQ_M_LOCAL + LOCAL_INT_BTN_0);
  clic_enable(IRQ_M_LOCAL + LOCAL_INT_BTN_1);
  clic_enable(IRQ_M_LOCAL + LOCAL_INT_BTN_2);
  clic_enable(IRQ_M_LOCAL + LOCAL_INT_BTN_3);
}

void disable_local_interrupts() {
  clic_disable(IRQ_M_LOCAL + LOCAL_INT_SW_3);
  clic_disable(IRQ_M_LOCAL + LOCAL_INT_BTN_0);
  clic_disable(IRQ_M_LOCAL + LOCAL_INT_BTN_1);
  clic_disable(IRQ_M_LOCAL + LOCAL_INT_BTN_2);
  clic_disable(IRQ_M_LOCAL + LOCAL_INT_BTN_3);
}

/*Entry Point for Machine Software Interrupt Handler*/
void msi_isr() {
  const char msi_msg[] = "    Debouncing: (this message due to Software Interrupt)\n\n";
  write (STDOUT_FILENO, msi_msg, strlen(msi_msg));  

  //clear the  SW interrupt
  CLIC_REG(CLIC_MSIP) = 0;
}

/*Entry Point for Machine Timer Interrupt Handler*/
void mti_isr(){
  const char mti_msg[] = "    Timer interrupt, done debouncing.\n\n";
  write (STDOUT_FILENO, mti_msg, strlen(mti_msg));  

  // Disable the timer interrupt. The Debounce logic sets it.
  clic_disable(IRQ_M_TIMER);

  // Enable all the local interrupts
  enable_local_interrupts();
}

const char * instructions_msg = " \
\n\
                         SiFive, Inc\n\
 E21 Core IP Eval Kit 'clic_interrupts' demo.\n\
\n\
The Buttons 0-3 and Switch 3 are enabled as local\n\
interrupts sources. A .5 s 'debounce' timer is used \n\
between these interrupts. Software interrupts are\n\
used to print a message while debouncing.\n\
Note the priority of the interrupts sources.\n\
\n";

void print_instructions() {

  write (STDERR_FILENO, instructions_msg, strlen(instructions_msg));

}

void button_0_isr(void) {

  // Toggle Red LED
  const char button_0_msg[] = "Button 0 was pressed. Toggle Red.\n";
  write (STDOUT_FILENO, button_0_msg, strlen(button_0_msg));  
  GPIO_REG(GPIO_OUTPUT_VAL) = GPIO_REG(GPIO_OUTPUT_VAL) ^ (0x1 << RED_LED_OFFSET);
  debounce();  
};

void button_1_isr(void) {

  // Toggle Green LED
  const char button_1_msg[] = "Button 1 was pressed. Toggle Green.\n";
  write (STDOUT_FILENO, button_1_msg, strlen(button_1_msg));  
  GPIO_REG(GPIO_OUTPUT_VAL) = GPIO_REG(GPIO_OUTPUT_VAL) ^ (0x1 << GREEN_LED_OFFSET);
  debounce();
};


void button_2_isr(void) {

  // Toggle Blue LED
  const char button_2_msg[] = "Button 2 was pressed. Toggle Blue.\n";
  write (STDOUT_FILENO, button_2_msg, strlen(button_2_msg));  
  GPIO_REG(GPIO_OUTPUT_VAL) = GPIO_REG(GPIO_OUTPUT_VAL) ^ (0x1 << BLUE_LED_OFFSET);
  debounce();
  
};

void button_3_isr(void) {
  const char button_3_msg[] = "Button 3 was pressed! (No LEDs change).\n";
  write (STDOUT_FILENO, button_3_msg, strlen(button_3_msg));
  debounce();
}

void switch_3_isr(void) {
  const char sw_3_msg[] = "Switch 3 is on! But buttons have higher priority.\n";
  write (STDOUT_FILENO, sw_3_msg, strlen(sw_3_msg));
  debounce();
}

void debounce(int local_interrupt_num) {
  // Disable the most recent interrupt.
  // Don't enable it again until the timer goes off,
  // in .5 second.
  
  // Set the machine timer to go off in .5 seconds.
  // If the timer was already set to go off, this "cancels"
  // the current one.
  
  volatile uint64_t * mtime       = (uint64_t*) (CLINT_CTRL_ADDR + CLINT_MTIME);
  volatile uint64_t * mtimecmp    = (uint64_t*) (CLINT_CTRL_ADDR + CLINT_MTIMECMP);
  uint64_t now = *mtime;
  uint64_t then = now + .5*RTC_FREQ;
  *mtimecmp = then;

  disable_local_interrupts();
  g_debouncing = 1;

  // Enable the Machine-Timer bit in MIE
  clic_enable(IRQ_M_TIMER);
}

// See bsp/env/<BOARD>/init.c for how this
// interrupt vector is used.

interrupt_function_ptr_t localISR[32]; 

static void unmapped_interrupt(void) {
  printf("unmapped interrupt");
  asm volatile ("1: j 1b" ::: "memory");
}

int main(int argc, char **argv)
{
  // Configure LEDs as outputs.
  GPIO_REG(GPIO_INPUT_EN)    &= ~((0x1<< RED_LED_OFFSET) | (0x1<< GREEN_LED_OFFSET) | (0x1 << BLUE_LED_OFFSET)) ;
  GPIO_REG(GPIO_OUTPUT_EN)   |=  ((0x1<< RED_LED_OFFSET)| (0x1<< GREEN_LED_OFFSET) | (0x1 << BLUE_LED_OFFSET)) ;
  GPIO_REG(GPIO_OUTPUT_VAL)  |=   (0x1 << BLUE_LED_OFFSET) ;
  GPIO_REG(GPIO_OUTPUT_VAL)  &=  ~((0x1<< RED_LED_OFFSET) | (0x1<< GREEN_LED_OFFSET)) ;

  // The Buttons and Switches which are used as local interrupt sources
  // do not go through the GPIO peripheral, so they do not need to
  // be configured as inputs.
  
  // Disable the timer & local interrupts until setup is done (they're
  // not reset by default)
  
  // Unconfigure the CLIC before doing anything
  for (int i = 0; i < 1024; ++i)
    CLIC_REG8(CLIC_INTIE + i) = 0;

  // Write down the software interrupt pending bit, as we shouldn't start out
  // by debouncing anything at all.
  CLIC_REG(CLIC_MSIP) = 0;

  for (int isr = 0; isr < 32; isr++)
    localISR[isr] = &unmapped_interrupt;
  
  localISR[IRQ_M_SOFT]  = msi_isr;
  localISR[IRQ_M_TIMER] = mti_isr;
  localISR[IRQ_M_LOCAL + LOCAL_INT_SW_3]  = switch_3_isr;
  localISR[IRQ_M_LOCAL + LOCAL_INT_BTN_0] = button_0_isr;
  localISR[IRQ_M_LOCAL + LOCAL_INT_BTN_1] = button_1_isr;
  localISR[IRQ_M_LOCAL + LOCAL_INT_BTN_2] = button_2_isr;
  localISR[IRQ_M_LOCAL + LOCAL_INT_BTN_3] = button_3_isr;

  // Set up the CLIC interrupt mechanism
  CLIC_REG(CLIC_CFG) = 4<<1; // nmBits=0; nlBits=4; nvBits=0

  print_instructions();
  
  enable_local_interrupts();

  g_debouncing = 0;

  // Enable SW interrupts as well in this demo.
  clic_enable(IRQ_M_SOFT);
  
  // Enable all global interrupts
  set_csr(mstatus, MSTATUS_MIE);

  volatile int foo = 1;
  while(foo){
    if (g_debouncing){
      //Trigger a SW interrupt
      CLIC_REG(CLIC_MSIP) = 1;
      g_debouncing = 0;
    }
  }

  return 0;

}
