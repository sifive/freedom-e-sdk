// See LICENSE for license details.

#include <stdio.h>
#include <stdlib.h>
#include "platform.h"
#include <string.h>
#include "plic_driver.h"
#include "encoding.h"
#include <unistd.h>

#define RTC_FREQUENCY 32768

void reset_demo (void);

// Structures for registering different interrupt handlers
// for different parts of the application.
typedef void (*function_ptr_t) (void);

void no_interrupt_handler (void) {};

function_ptr_t g_ext_interrupt_handlers[PLIC_NUM_INTERRUPTS];

function_ptr_t g_m_timer_interrupt_handler = no_interrupt_handler;

// Instance data for the PLIC.

plic_instance_t g_plic;

// Simple variables for LEDs, buttons, etc.
volatile unsigned int* g_output_vals  = (unsigned int *) (GPIO_BASE_ADDR + GPIO_OUTPUT_VAL);
volatile unsigned int* g_input_vals   = (unsigned int *) (GPIO_BASE_ADDR + GPIO_INPUT_VAL);
volatile unsigned int* g_output_en    = (unsigned int *) (GPIO_BASE_ADDR + GPIO_OUTPUT_EN);
volatile unsigned int* g_input_en     = (unsigned int *) (GPIO_BASE_ADDR + GPIO_INPUT_EN);

/*Entry Point for PLIC Interrupt Handler*/
void handle_m_ext_interrupt(){
  plic_source int_num  = PLIC_claim_interrupt(&g_plic);
  if ((int_num >=1 ) && (int_num <= 8)) {
    g_ext_interrupt_handlers[int_num]();
  }
  else {
    exit(1 + (uintptr_t) int_num);
  }
  PLIC_complete_interrupt(&g_plic, int_num);
}


/*Entry Point for Machine Timer Interrupt Handler*/
void handle_m_time_interrupt(){

  clear_csr(mie, MIP_MTIP);
  
  // Reset the timer for 3s in the future.
  // This also clears the existing timer interrupt.
  
  volatile uint64_t * mtime       = (uint64_t*) (CLINT_BASE_ADDR + CLINT_MTIME);
  volatile uint64_t * mtimecmp    = (uint64_t*) (CLINT_BASE_ADDR + CLINT_MTIMECMP);
  uint64_t now = *mtime;
  uint64_t then = now + 3 * RTC_FREQUENCY;
  *mtimecmp = then;
 
  // read the current value of the LEDS and invert them.
  uint32_t leds = *g_output_vals;
  
  *g_output_vals ^= ((0x1 << RED_LED_OFFSET)   |
		     (0x1 << GREEN_LED_OFFSET) |
		     (0x1 << BLUE_LED_OFFSET));
  
  // Re-enable the timer interrupt.
  set_csr(mie, MIP_MTIP);
  
}


/*Entry Point for Machine Timer Interrupt  Handler*/
void handle_m_timer_interrupt(){
  g_m_timer_interrupt_handler();
}

const char * instructions_msg = " \
\n\
                SIFIVE, INC.\n\
\n\
         5555555555555555555555555\n\
        5555                   5555\n\
       5555                     5555\n\
      5555                       5555\n\
     5555       5555555555555555555555\n\
    5555       555555555555555555555555\n\
   5555                             5555\n\
  5555                               5555\n\
 5555                                 5555\n\
5555555555555555555555555555          55555\n\
 55555           555555555           55555\n\
   55555           55555           55555\n\
     55555           5           55555\n\
       55555                   55555\n\
         55555               55555\n\
           55555           55555\n\
             55555       55555\n\
               55555   55555\n\
                 555555555\n\
                   55555\n\
                     5\n\
\n\
 SiFive E-Series Coreplex Demo on Arty Board\n \
 \n\
 ";

void print_instructions() {
  
  write (STDOUT_FILENO, instructions_msg, strlen(instructions_msg));
  
}

void button_0_handler(void) {

  // All LEDS on
  * g_output_vals = (0x1 << RED_LED_OFFSET) |
                    (0x1 << GREEN_LED_OFFSET) |
                    (0x1 << BLUE_LED_OFFSET);

};


void reset_demo (){

    // Disable the machine & timer interrupts until setup is done.
  
  clear_csr(mie, MIP_MEIP);
  clear_csr(mie, MIP_MTIP);

  for (int ii = 0; ii < PLIC_NUM_INTERRUPTS; ii ++){
    g_ext_interrupt_handlers[ii] = no_interrupt_handler;
  }

#if HAS_BOARD_BUTTONS
  g_ext_interrupt_handlers[INT_DEVICE_BUTTON_0] = button_0_handler;
#endif
  
  print_instructions();

#if HAS_BOARD_BUTTONS  
  PLIC_enable_interrupt (&g_plic, INT_DEVICE_BUTTON_0);
#endif
  
    // Set the machine timer to go off in 3 seconds.
    // The
    volatile uint64_t * mtime       = (uint64_t*) (CLINT_BASE_ADDR + CLINT_MTIME);
    volatile uint64_t * mtimecmp    = (uint64_t*) (CLINT_BASE_ADDR + CLINT_MTIMECMP);
    uint64_t now = *mtime;
    uint64_t then = now + 3*RTC_FREQUENCY;
    *mtimecmp = then;
    
    // Enable the Machine-External bit in MIE
    set_csr(mie, MIP_MEIP);

    // Enable the Machine-Timer bit in MIE
    set_csr(mie, MIP_MTIP);
    
    // Enable interrupts in general.
    set_csr(mstatus, MSTATUS_MIE);
}

int main(int argc, char **argv)
{
  // Set up the GPIOs such that the LED GPIO
  // can be used as both Inputs and Outputs.

#ifdef HAS_ONBOARD_BUTTONS
  * g_output_en  &= ~((0x1 << BUTTON_0_OFFSET) | (0x1 << BUTTON_1_OFFSET) | (0x2 << BUTTON_2_OFFSET));
  * g_pullup_en  &= ~((0x1 << BUTTON_0_OFFSET) | (0x1 << BUTTON_1_OFFSET) | (0x2 << BUTTON_2_OFFSET));
  * g_input_en   |= ((0x1 << BUTTON_0_OFFSET) | (0x1 << BUTTON_1_OFFSET) | (0x2 << BUTTON_2_OFFSET));
#endif
  
  * g_input_en  &= ~((0x1<< RED_LED_OFFSET) | (0x1<< GREEN_LED_OFFSET) | (0x1 << BLUE_LED_OFFSET)) ;
  * g_output_en  |=  ((0x1<< RED_LED_OFFSET)| (0x1<< GREEN_LED_OFFSET) | (0x1 << BLUE_LED_OFFSET)) ;

  /**************************************************************************
   * Set up the PLIC
   * 
   *************************************************************************/
  PLIC_init(&g_plic,
	    PLIC_BASE_ADDR,
	    PLIC_NUM_INTERRUPTS,
	    PLIC_NUM_PRIORITIES);

  reset_demo();

  while (1);

  return 0;

}
