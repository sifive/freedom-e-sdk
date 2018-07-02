// See LICENSE for license details.

#include <stdio.h>
#include <stdlib.h>
#include "platform.h"
#include <string.h>
#include "encoding.h"
#include <unistd.h>
#include "sifive/devices/clic.h"
#include "clic/clic_driver.h"

#ifndef _SIFIVE_COREPLEXIP_ARTY_H
#error 'local_interrupts' demo only supported for Core IP Eval Kits
#endif

// Global Variable used to show
// software interrupts.
volatile uint32_t g_debouncing;

// vector table defined in init.c
typedef void (*interrupt_function_ptr_t) (void);
extern interrupt_function_ptr_t localISR[CLIC_NUM_INTERRUPTS]; 
extern void default_handler(void);

//clic data structure
clic_instance_t clic;

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

  //write (STDERR_FILENO, instructions_msg, strlen(instructions_msg));
  printf(instructions_msg);

}

void button_0_isr(void) __attribute__((interrupt));
void button_0_isr(void) {
  // Toggle Red LED
  	  
  const char button_0_msg[] = "Button 0 was pressed. Toggle Red.\n";
  write (STDOUT_FILENO, button_0_msg, strlen(button_0_msg));  
  GPIO_REG(GPIO_OUTPUT_VAL) = GPIO_REG(GPIO_OUTPUT_VAL) ^ (0x1 << RED_LED_OFFSET);
  clic_clear_pending(&clic, (LOCALINTIDBASE + LOCAL_INT_BTN_0));
}

void button_0_setup(void) {
  clic_install_handler(&clic, (LOCALINTIDBASE + LOCAL_INT_BTN_0), button_0_isr);
  clic_enable_interrupt(&clic, (LOCALINTIDBASE + LOCAL_INT_BTN_0));
}

void config_gpio()  {
  // Configure LEDs as outputs.
  GPIO_REG(GPIO_INPUT_EN)    &= ~((0x1<< RED_LED_OFFSET) | (0x1<< GREEN_LED_OFFSET) | (0x1 << BLUE_LED_OFFSET)) ;
  GPIO_REG(GPIO_OUTPUT_EN)   |=  ((0x1<< RED_LED_OFFSET)| (0x1<< GREEN_LED_OFFSET) | (0x1 << BLUE_LED_OFFSET)) ;
  GPIO_REG(GPIO_OUTPUT_VAL)  &= ((0x1<< RED_LED_OFFSET) | (0x1<< GREEN_LED_OFFSET)|  (0x1 << BLUE_LED_OFFSET)) ;
}

int main(int argc, char **argv)
{
  clear_csr(mstatus, MSTATUS_MIE);
  clear_csr(mie, IRQ_M_SOFT);
  clear_csr(mie, IRQ_M_TIMER);


  clic_init(&clic, CLIC_HART0_ADDR, 
            (interrupt_function_ptr_t*)localISR,
            default_handler,
            CLIC_NUM_INTERRUPTS,
            CLIC_NUM_CONFIG_BITS);


  config_gpio();
  button_0_setup();

  // Enable all global interrupts
  set_csr(mstatus, MSTATUS_MIE);


  print_instructions();
  while(1);

  return 0;

}
