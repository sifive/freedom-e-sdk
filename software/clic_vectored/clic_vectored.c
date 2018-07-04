// See LICENSE for license details.
#include <stdio.h>
#include <stdlib.h>
#include "platform.h"
#include <string.h>
#include "encoding.h"
#include <unistd.h>
#include "sifive/devices/clic.h"
#include "clic/clic_driver.h"
#include "sifive/devices/clint.h"

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
 E21 Core IP Eval Kit 'clic_vectored' demo.\n\
 This demo uses buttons 0, 1, and 2 on the\n\
 Arty board to trigger vectored clic interrupts.\n\
 The higher the button number, the higher the\n\
 interupt priority. Hold two buttons down at\n\
 the same time to see priorities in action.\n\
\n\
\n";

void print_instructions() {
  write (STDERR_FILENO, instructions_msg, strlen(instructions_msg));
}


//busy wait for the specified time
void wait_ms(uint64_t ms) {
  static const uint64_t ms_tick = RTC_FREQ/1000;
  volatile uint64_t * mtime  = (uint64_t*) (CLINT_CTRL_ADDR + CLINT_MTIME);
  uint64_t then = (ms_tick * ms) + *mtime;
  while(*mtime<then);
}

void button_0_isr(void) __attribute__((interrupt));
void button_0_isr(void) {
  // Toggle Red LED
  uint8_t level = clic_get_int_level(&clic, (LOCALINTIDBASE + LOCAL_INT_BTN_0));
  printf("Button 0 was pressed, interrupt level %d. Toggle Red.\n", level);
  GPIO_REG(GPIO_OUTPUT_VAL) = GPIO_REG(GPIO_OUTPUT_VAL) ^ (0x1 << RED_LED_OFFSET);
  wait_ms(500);
  clic_enable_interrupt(&clic, (LOCALINTIDBASE + LOCAL_INT_BTN_0));
  GPIO_REG(GPIO_OUTPUT_VAL) = GPIO_REG(GPIO_OUTPUT_VAL) ^ (0x1 << RED_LED_OFFSET);
}

void button_0_setup(void) {
  clic_install_handler(&clic, (LOCALINTIDBASE + LOCAL_INT_BTN_0), button_0_isr);
  clic_set_int_level(&clic, (LOCALINTIDBASE + LOCAL_INT_BTN_0), 1);
  clic_enable_interrupt(&clic, (LOCALINTIDBASE + LOCAL_INT_BTN_0));
}

void button_1_isr(void) __attribute__((interrupt));
void button_1_isr(void) {
  // Toggle Red LED
  uint8_t level = clic_get_int_level(&clic, (LOCALINTIDBASE + LOCAL_INT_BTN_1));
  printf("Button 1 was pressed, interrupt level %d. Toggle Blue.\n", level);
  GPIO_REG(GPIO_OUTPUT_VAL) = GPIO_REG(GPIO_OUTPUT_VAL) ^ (0x1 << BLUE_LED_OFFSET);
  wait_ms(500);
  clic_enable_interrupt(&clic, (LOCALINTIDBASE + LOCAL_INT_BTN_1));
  GPIO_REG(GPIO_OUTPUT_VAL) = GPIO_REG(GPIO_OUTPUT_VAL) ^ (0x1 << BLUE_LED_OFFSET);
}

void button_1_setup(void) {
  clic_install_handler(&clic, (LOCALINTIDBASE + LOCAL_INT_BTN_1), button_1_isr);
  clic_set_int_level(&clic, (LOCALINTIDBASE + LOCAL_INT_BTN_1), 2);
  clic_enable_interrupt(&clic, (LOCALINTIDBASE + LOCAL_INT_BTN_1));
}

void button_2_isr(void) __attribute__((interrupt));
void button_2_isr(void) {
  // Toggle Red LED
  uint8_t level = clic_get_int_level(&clic, (LOCALINTIDBASE + LOCAL_INT_BTN_2));
  printf("Button 2 was pressed, interrupt level %d. Toggle Green.\n", level);
  GPIO_REG(GPIO_OUTPUT_VAL) = GPIO_REG(GPIO_OUTPUT_VAL) ^ (0x1 << GREEN_LED_OFFSET);
  wait_ms(500);
  clic_enable_interrupt(&clic, (LOCALINTIDBASE + LOCAL_INT_BTN_2));
  GPIO_REG(GPIO_OUTPUT_VAL) = GPIO_REG(GPIO_OUTPUT_VAL) ^ (0x1 << GREEN_LED_OFFSET);
}

void button_2_setup(void) {
  clic_install_handler(&clic, (LOCALINTIDBASE + LOCAL_INT_BTN_2), button_2_isr);
  clic_set_int_level(&clic, (LOCALINTIDBASE + LOCAL_INT_BTN_2), 3);
  clic_enable_interrupt(&clic, (LOCALINTIDBASE + LOCAL_INT_BTN_2));
}

/*Entry Point for Machine Software Interrupt Handler*/
uint32_t COUNT;
void msi_isr()__attribute((interrupt));
void msi_isr() {
  //clear the  SW interrupt
  CLINT_REG(CLINT_MSIP) = 0;
  COUNT++;
}

void msi_setup(void)  {
  clic_install_handler(&clic, MSIPID, msi_isr);
  clic_set_int_level(&clic, MSIPID, 1);
  clic_enable_interrupt(&clic, MSIPID);
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

  //initialize clic registers and vector table
  clic_init(&clic, CLIC_HART0_ADDR, 
            (interrupt_function_ptr_t*)localISR,
            default_handler,
            CLIC_NUM_INTERRUPTS,
            CLIC_CONFIG_BITS);

  //use all 4 config bits for levels, no shv
  clic_set_cliccfg(&clic, ((CLIC_CONFIG_BITS<<1)|0));

  //initialize gpio and buttons.
  //each button registers an interrupt handler
  config_gpio();
  button_0_setup();
  button_1_setup();
  button_2_setup();
  msi_setup();

  // Enable all global interrupts
  set_csr(mstatus, MSTATUS_MIE);
  print_instructions();

   while(1)  {
    wait_ms(10000);
    printf("Count=%d\n", COUNT);
    //Trigger a SW interrupt
    CLINT_REG(CLINT_MSIP) = 1;
  }

  return 0;

}
