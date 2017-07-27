// See LICENSE for license details.

#include <stdio.h>
#include <stdlib.h>
#include "platform.h"
#include <string.h>
#include "plic/plic_driver.h"
#include "encoding.h"
#include <unistd.h>

#ifndef _SIFIVE_COREPLEXIP_ARTY_H
#error 'global_interrupts' demo only supported for Coreplex IP Eval Kits
#endif

// Global Instance data for the PLIC
// for use by the PLIC Driver.
plic_instance_t g_plic;

// Structures for registering different interrupt handlers
// for different parts of the application.
typedef void (*interrupt_function_ptr_t) (void);
//array of function pointers which contains the PLIC
//interrupt handlers
interrupt_function_ptr_t g_ext_interrupt_handlers[PLIC_NUM_INTERRUPTS];

const char * instructions_msg = " \
\n\
                SIFIVE, INC.\n\
E31/E51 Coreplex IP Eval Kit 'vectored_interrupts' demo.  \n\
\n\
This demo demonstrates Vectored Interrupts capabilities of\n\
the E31/E51 Coreplex. The vector table is defined in      \n\
bsp/env/ventry.S                                          \n\
Button 0 is a global external interrupt routed to the PLIC.\n\
Button 1 is a local interrupt.\n\
\n";

void print_instructions() {

  write (STDOUT_FILENO, instructions_msg, strlen(instructions_msg));

}

void set_timer() {
  
  volatile uint64_t * mtime       = (uint64_t*) (CLINT_CTRL_ADDR + CLINT_MTIME);
  volatile uint64_t * mtimecmp    = (uint64_t*) (CLINT_CTRL_ADDR + CLINT_MTIMECMP);
  uint64_t now = *mtime;
  uint64_t then = now + 1*RTC_FREQ;
  *mtimecmp = then;

  set_csr(mie, MIP_MTIP);
}

/*Entry Point for Machine Timer Interrupt Handler*/
/*called from bsp/env/ventry.s          */
void handle_m_time_interrupt(){
  static uint32_t onoff=1;

  clear_csr(mie, MIP_MTIP);

  // Set Green LED
  if(onoff)	{
	  GPIO_REG(GPIO_OUTPUT_VAL)  |=  (0x1 << GREEN_LED_OFFSET) ;
	  onoff=0;
  }else	{
	  GPIO_REG(GPIO_OUTPUT_VAL)  &=  ~((0x1 << GREEN_LED_OFFSET)) ;
	  onoff=1;
  }
  set_timer();

  //re-enable button1 irq
  set_csr(mie, MIP_MLIP(LOCAL_INT_BTN_1));

}

/*Synchronous Trap Handler*/
/*called from bsp/env/ventry.s          */
void handle_sync_trap( ) {
    write(1, "vUnhandled Trap:\n", 16);
    _exit(1 + read_csr(mcause));
}

/*Entry Point for PLIC Interrupt Handler*/
/*called from bsp/env/ventry.s          */
void handle_m_external_interrupt(){
  printf("In PLIC handler\n");
  plic_source int_num  = PLIC_claim_interrupt(&g_plic);
  if ((int_num >=1 ) && (int_num < PLIC_NUM_INTERRUPTS)) {
    g_ext_interrupt_handlers[int_num]();
  }
  else {
    exit(1 + (uintptr_t) int_num);
  }
  PLIC_complete_interrupt(&g_plic, int_num);
}

//default empty PLIC handler
void invalid_global_isr() {
  printf("Unexpected global interrupt!\n");
}

/* b0 global interrupt isr                */
/*called from handle_m_external_interrupt */
void button_0_handler() {
  static uint32_t onoff=1;
  // Set Green LED

  printf("In Button 0 handler\n");

  if(onoff)	{
	  GPIO_REG(GPIO_OUTPUT_VAL)  |=  (0x1 << BLUE_LED_OFFSET) ;
	  onoff=0;
  }else	{
	  GPIO_REG(GPIO_OUTPUT_VAL)  &=  ~((0x1 << BLUE_LED_OFFSET)) ;
	  onoff=1;
  }

  //clear irq - interrupt pending register is write 1 to clear
  GPIO_REG(GPIO_FALL_IP) |= (1<<BUTTON_0_OFFSET);
}

/*b1 local vectored irq handler         */
/*called from bsp/env/ventry.s          */
void handle_local_interrupt5() {
  static uint32_t onoff=1;
  // Set Green LED

  printf("In Button 1 handler\n");

  if(onoff)	{
	  GPIO_REG(GPIO_OUTPUT_VAL)  |=  (0x1 << RED_LED_OFFSET) ;
	  onoff=0;
  }else	{
	  GPIO_REG(GPIO_OUTPUT_VAL)  &=  ~((0x1 << RED_LED_OFFSET)) ;
	  onoff=1;
  }

  //debounce by turning off until next timer tick
  clear_csr(mie, MIP_MLIP(LOCAL_INT_BTN_1));
}

/*configures Button0 as a global gpio irq*/
void b0_irq_init()  {

    //dissable hw io function
    GPIO_REG(GPIO_IOF_EN )    &=  ~(1 << BUTTON_0_OFFSET);

    //set to input
    GPIO_REG(GPIO_INPUT_EN)   |= (1<<BUTTON_0_OFFSET);
    GPIO_REG(GPIO_PULLUP_EN)  |= (1<<BUTTON_0_OFFSET);

    //set to interrupt on falling edge
    GPIO_REG(GPIO_FALL_IE)    |= (1<<BUTTON_0_OFFSET);

    PLIC_init(&g_plic,
  	    PLIC_CTRL_ADDR,
  	    PLIC_NUM_INTERRUPTS,
  	    PLIC_NUM_PRIORITIES);

    PLIC_enable_interrupt (&g_plic, INT_DEVICE_BUTTON_0);
    PLIC_set_priority(&g_plic, INT_DEVICE_BUTTON_0, 2);
    g_ext_interrupt_handlers[INT_DEVICE_BUTTON_0] = button_0_handler;
}

/*configures Button1 as a local interrupt*/
void b1_irq_init()  {

    //enable the interrupt
    set_csr(mie, MIP_MLIP(LOCAL_INT_BTN_1));

}

/*turn down the brightness, and configure GPIO */
void led_init() {
  // Make sure people aren't blinded by LEDs connected here.
  PWM0_REG(PWM_CMP0)  = 0xFE;
  PWM0_REG(PWM_CMP1)  = 0xFF;
  PWM0_REG(PWM_CMP2)  = 0xFF;
  PWM0_REG(PWM_CMP3)  = 0xFF;
  // Set up RGB LEDs for a visual.
  GPIO_REG(GPIO_OUTPUT_EN)   |=  ((0x1<< RED_LED_OFFSET)| (0x1<< GREEN_LED_OFFSET)| (0x1<< BLUE_LED_OFFSET));
  GPIO_REG(GPIO_OUTPUT_VAL)  &=  ~((0x1<< RED_LED_OFFSET) | (0x1<< GREEN_LED_OFFSET) | (0x1<< BLUE_LED_OFFSET));

}

int main(int argc, char **argv)
{
  //setup default global interrupt handler
  for (int gisr = 0; gisr < PLIC_NUM_INTERRUPTS; gisr++){
    g_ext_interrupt_handlers[PLIC_NUM_INTERRUPTS] = invalid_global_isr;
  }
  
  print_instructions();
  
  led_init();
  b0_irq_init();
  b1_irq_init();

  // Set up machine timer interrupt.
  set_timer();

  // Enable Global (PLIC) interrupts.
  set_csr(mie, MIP_MEIP);
  
  // Enable all interrupts
  set_csr(mstatus, MSTATUS_MIE);


  while(1){
    asm volatile ("wfi");
  }
  
  return 0;

}
