// See LICENSE file for licence details

#ifndef PLIC_DRIVER_H
#define PLIC_DRIVER_H


__BEGIN_DECLS

#include "platform.h"

typedef void (*interrupt_function_ptr_t) (void);

typedef struct __clic_instance_t
{
  uintptr_t hart_addr;
  interrupt_function_ptr_t* vect_table;
  uint32_t num_config_bits;
  uint32_t num_sources;  
} clic_instance_t;

// Note that there are no assertions or bounds checking on these
// parameter values.
void clic_init (clic_instance_t * this_clic, uintptr_t hart_addr, interrupt_function_ptr_t* vect_table, interrupt_function_ptr_t default_handler, uint32_t num_irq,uint32_t num_config_bits);
void clic_install_handler (clic_instance_t * this_clic, uint32_t source, interrupt_function_ptr_t handler);
void clic_enable_interrupt (clic_instance_t * this_clic, uint32_t source);
void clic_disable_interrupt (clic_instance_t * this_clic, uint32_t source);
void clic_set_pending(clic_instance_t * this_clic, uint32_t source);
void clic_clear_pending(clic_instance_t * this_clic, uint32_t source);
void clic_set_level (clic_instance_t * this_clic, uint32_t source, uint32_t priority);
void clic_get_level (clic_instance_t * this_clic, uint32_t source, uint32_t priority);
void clic_set_priority (clic_instance_t * this_clic, uint32_t source, uint32_t priority);
void clic_get_priority (clic_instance_t * this_clic, uint32_t source, uint32_t priority);

__END_DECLS

#endif
