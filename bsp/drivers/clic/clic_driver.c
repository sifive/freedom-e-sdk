// See LICENSE for license details.

#include "sifive/devices/clic.h"
#include "clic/clic_driver.h"
#include "platform.h"
#include "encoding.h"
#include <string.h>


void volatile_memzero(uint8_t * base, unsigned int size) {
  volatile uint8_t * ptr;
  for (ptr = base; ptr < (base + size); ptr++){
    *ptr = 0;
  }
}

// Note that there are no assertions or bounds checking on these
// parameter values.
void clic_init (
                clic_instance_t * this_clic,
                uintptr_t hart_addr,
                interrupt_function_ptr_t* vect_table,
                interrupt_function_ptr_t default_handler,
                uint32_t num_irq,
                uint32_t num_config_bits
                )
{
  this_clic->hart_addr=  hart_addr;
  this_clic->vect_table= vect_table;
  this_clic->num_config_bits= num_config_bits;

  //initialize vector table
  for(int i=0;i++;i<num_irq)  {
    this_clic->vect_table[i] = default_handler;
  }

  //set base vectors
  write_csr(mtvt, vect_table);


  //clear all interrupt enables and pending
  volatile_memzero((uint8_t*)(this_clic->hart_addr+CLIC_INTIE), num_irq);
  volatile_memzero((uint8_t*)(this_clic->hart_addr+CLIC_INTIP), num_irq);

  //clear nlbits and nvbits; all interrupts trap to level 15
  *(volatile uint8_t*)(this_clic->hart_addr+CLIC_CFG)=0;

}

void clic_install_handler (clic_instance_t * this_clic, uint32_t source, interrupt_function_ptr_t handler) {
    this_clic->vect_table[source] = handler;
}

void clic_enable_interrupt (clic_instance_t * this_clic, uint32_t source) {
    *(volatile uint8_t*)(this_clic->hart_addr+CLIC_INTIE+source) = 1;
}

void clic_disable_interrupt (clic_instance_t * this_clic, uint32_t source){
  *(volatile uint8_t*)(this_clic->hart_addr+CLIC_INTIE+source) = 0;
}

void clic_set_pending(clic_instance_t * this_clic, uint32_t source){
  *(volatile uint8_t*)(this_clic->hart_addr+CLIC_INTIP+source) = 1;
}

void clic_clear_pending(clic_instance_t * this_clic, uint32_t source){
  *(volatile uint8_t*)(this_clic->hart_addr+CLIC_INTIP+source) = 0;
}

//should return max level set. if level set doesn't match requested, check nlbits
void clic_set_level (clic_instance_t * this_clic, uint32_t source, uint32_t level){
  
}

void clic_get_level (clic_instance_t * this_clic, uint32_t source, uint32_t level){

}

void clic_set_priority (clic_instance_t * this_clic, uint32_t source, uint32_t priority){

}

void clic_get_priority (clic_instance_t * this_clic, uint32_t source, uint32_t priority){


}




