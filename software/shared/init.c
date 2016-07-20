// See LICENSE for license details.

#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <unistd.h>

#include "encoding.h"
#include "shared.h"

int main(void);

#ifdef USE_PLIC
extern void handle_m_ext_interrupt();
#endif


#ifdef USE_M_TIME
extern void handle_m_time_interrupt();
#endif


void _init(void)
{
  
  exit(main());
}

uintptr_t handle_trap(uintptr_t mcause, uintptr_t epc)
{
  if (0){
#ifdef USE_PLIC
  // External Machine-Level Interrupt from PLIC
 }else if ((mcause & MCAUSE_INT) && ((mcause & MCAUSE_CAUSE)  == IRQ_M_EXT)) {
    handle_m_ext_interrupt();
#endif
#ifdef USE_M_TIME
  // External Machine-Level Interrupt from PLIC
 }else if ((mcause & MCAUSE_INT) && ((mcause & MCAUSE_CAUSE)  == IRQ_M_TIMER)) {
    handle_m_time_interrupt();
#endif
  }    
  else{
    write(1, "trap\n", 5);
    _exit(1 + mcause);
  }
  return epc;
}
