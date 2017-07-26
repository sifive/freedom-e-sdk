// See LICENSE for license details

#ifndef VENTRY_S
#define VENTRY_S

#include "encoding.h"
#include "sifive/bits.h"

.macro TRAP_ENTRY
  addi sp, sp, -32*REGBYTES

  STORE x1, 1*REGBYTES(sp)
  STORE x2, 2*REGBYTES(sp)
  STORE x3, 3*REGBYTES(sp)
  STORE x4, 4*REGBYTES(sp)
  STORE x5, 5*REGBYTES(sp)
  STORE x6, 6*REGBYTES(sp)
  STORE x7, 7*REGBYTES(sp)
  STORE x8, 8*REGBYTES(sp)
  STORE x9, 9*REGBYTES(sp)
  STORE x10, 10*REGBYTES(sp)
  STORE x11, 11*REGBYTES(sp)
  STORE x12, 12*REGBYTES(sp)
  STORE x13, 13*REGBYTES(sp)
  STORE x14, 14*REGBYTES(sp)
  STORE x15, 15*REGBYTES(sp)
  STORE x16, 16*REGBYTES(sp)
  STORE x17, 17*REGBYTES(sp)
  STORE x18, 18*REGBYTES(sp)
  STORE x19, 19*REGBYTES(sp)
  STORE x20, 20*REGBYTES(sp)
  STORE x21, 21*REGBYTES(sp)
  STORE x22, 22*REGBYTES(sp)
  STORE x23, 23*REGBYTES(sp)
  STORE x24, 24*REGBYTES(sp)
  STORE x25, 25*REGBYTES(sp)
  STORE x26, 26*REGBYTES(sp)
  STORE x27, 27*REGBYTES(sp)
  STORE x28, 28*REGBYTES(sp)
  STORE x29, 29*REGBYTES(sp)
  STORE x30, 30*REGBYTES(sp)
  STORE x31, 31*REGBYTES(sp)
.endm

.macro TRAP_EXIT
# Remain in M-mode after mret
  li t0, MSTATUS_MPP
  csrs mstatus, t0

  LOAD x1, 1*REGBYTES(sp)
  LOAD x2, 2*REGBYTES(sp)
  LOAD x3, 3*REGBYTES(sp)
  LOAD x4, 4*REGBYTES(sp)
  LOAD x5, 5*REGBYTES(sp)
  LOAD x6, 6*REGBYTES(sp)
  LOAD x7, 7*REGBYTES(sp)
  LOAD x8, 8*REGBYTES(sp)
  LOAD x9, 9*REGBYTES(sp)
  LOAD x10, 10*REGBYTES(sp)
  LOAD x11, 11*REGBYTES(sp)
  LOAD x12, 12*REGBYTES(sp)
  LOAD x13, 13*REGBYTES(sp)
  LOAD x14, 14*REGBYTES(sp)
  LOAD x15, 15*REGBYTES(sp)
  LOAD x16, 16*REGBYTES(sp)
  LOAD x17, 17*REGBYTES(sp)
  LOAD x18, 18*REGBYTES(sp)
  LOAD x19, 19*REGBYTES(sp)
  LOAD x20, 20*REGBYTES(sp)
  LOAD x21, 21*REGBYTES(sp)
  LOAD x22, 22*REGBYTES(sp)
  LOAD x23, 23*REGBYTES(sp)
  LOAD x24, 24*REGBYTES(sp)
  LOAD x25, 25*REGBYTES(sp)
  LOAD x26, 26*REGBYTES(sp)
  LOAD x27, 27*REGBYTES(sp)
  LOAD x28, 28*REGBYTES(sp)
  LOAD x29, 29*REGBYTES(sp)
  LOAD x30, 30*REGBYTES(sp)
  LOAD x31, 31*REGBYTES(sp)

  addi sp, sp, 32*REGBYTES
  mret
.endm



.macro TRAP_ENTRY2
  addi sp, sp, -14*REGBYTES

  STORE x2, 1*REGBYTES(sp)
  STORE x8, 2*REGBYTES(sp)
  STORE x9, 3*REGBYTES(sp)
  STORE x18, 4*REGBYTES(sp)
  STORE x19, 5*REGBYTES(sp)
  STORE x20, 6*REGBYTES(sp)
  STORE x21, 7*REGBYTES(sp)
  STORE x22, 8*REGBYTES(sp)
  STORE x23, 9*REGBYTES(sp)
  STORE x24, 10*REGBYTES(sp)
  STORE x25, 11*REGBYTES(sp)
  STORE x26, 12*REGBYTES(sp)
  STORE x27, 13*REGBYTES(sp)
.endm

.macro TRAP_EXIT2
# Remain in M-mode after mret
  li t0, MSTATUS_MPP
  csrs mstatus, t0

  LOAD x3, 1*REGBYTES(sp)
  LOAD x8, 2*REGBYTES(sp)
  LOAD x9, 3*REGBYTES(sp)
  LOAD x18, 4*REGBYTES(sp)
  LOAD x19, 5*REGBYTES(sp)
  LOAD x20, 6*REGBYTES(sp)
  LOAD x21, 7*REGBYTES(sp)
  LOAD x22, 8*REGBYTES(sp)
  LOAD x23, 9*REGBYTES(sp)
  LOAD x24, 10*REGBYTES(sp)
  LOAD x25, 11*REGBYTES(sp)
  LOAD x26, 12*REGBYTES(sp)
  LOAD x27, 13*REGBYTES(sp)

  addi sp, sp, 14*REGBYTES
  mret
.endm



#Vector table for E31/E51

  .section      .text.entry	
  .align 8
  .global vtrap_entry
vtrap_entry:
  j sync_trap
  .align 2
  j reserved
  .align 2
  j reserved
  .align 2
  j vmsi_Handler
  .align 2
  j reserved
  .align 2
  j reserved
  .align 2
  j reserved
  .align 2
  j vmti_Handler
  .align 2
  j reserved
  .align 2
  j reserved
  .align 2
  j reserved
  .align 2
  j vmei_Handler
  .align 2
  j reserved
  .align 2
  j reserved
  .align 2
  j reserved
   .align 2
  j reserved
  .align 2
  j vlip_Handler0
  .align 2
  j vlip_Handler1
  .align 2
  j vlip_Handler2
  .align 2
  j vlip_Handler3
  .align 2
  j vlip_Handler4
  .align 2
  j vlip_Handler5
  .align 2
  j vlip_Handler6
  .align 2
  j vlip_Handler7
  .align 2
  j vlip_Handler8
  .align 2
  j vlip_Handler9
  .align 2
  j vlip_Handler10
  .align 2
  j vlip_Handler11
  .align 2
  j vlip_Handler12
  .align 2
  j vlip_Handler13
  .align 2
  j vlip_Handler14
  .align 2
  j vlip_Handler15
  
#synchronous trap
sync_trap:
  TRAP_ENTRY
  csrr a0, mcause
  csrr a1, mepc
  mv a2, sp
  jal handle_sync_trap
  csrw mepc, a0
  TRAP_EXIT

#Machine Software Interrupt
vmsi_Handler:
  TRAP_ENTRY
  jal reserved
  TRAP_EXIT

#Machine Timer Interrupt
vmti_Handler:
  TRAP_ENTRY2
  jal handle_m_time_interrupt
  TRAP_EXIT2

#Machine External Interrupt
vmei_Handler:
  TRAP_ENTRY2
  jal handle_m_external_interrupt
  TRAP_EXIT2

#LIP0
vlip_Handler0:
  TRAP_ENTRY
  jal handle_local_interrupt0
  TRAP_EXIT

#LIP1
vlip_Handler1:
  TRAP_ENTRY
  jal handle_local_interrupt1
  TRAP_EXIT

#LIP2
vlip_Handler2:
  TRAP_ENTRY
  jal handle_local_interrupt2
  TRAP_EXIT

#LIP3
vlip_Handler3:
  TRAP_ENTRY
  jal handle_local_interrupt3
  TRAP_EXIT

#LIP4
vlip_Handler4:
  TRAP_ENTRY
  jal handle_local_interrupt4
  TRAP_EXIT

#LIP5
vlip_Handler5:
  TRAP_ENTRY2
  jal handle_local_interrupt5
  TRAP_EXIT2

#LIP6
vlip_Handler6:
  TRAP_ENTRY
  jal handle_local_interrupt6
  TRAP_EXIT

#LIP7
vlip_Handler7:
  TRAP_ENTRY
  jal handle_local_interrupt7
  TRAP_EXIT

#LIP8
vlip_Handler8:
  TRAP_ENTRY
  jal handle_local_interrupt8
  TRAP_EXIT

#LIP9
vlip_Handler9:
  TRAP_ENTRY
  jal handle_local_interrupt9
  TRAP_EXIT

#LIP10
vlip_Handler10:
  TRAP_ENTRY
  jal handle_local_interrupt10
  TRAP_EXIT

#LIP11
vlip_Handler11:
  TRAP_ENTRY
  jal handle_local_interrupt11
  TRAP_EXIT

#LIP12
vlip_Handler12:
  TRAP_ENTRY
  jal handle_local_interrupt12
  TRAP_EXIT

#LIP13
vlip_Handler13:
  TRAP_ENTRY
  jal handle_local_interrupt13
  TRAP_EXIT

#LIP14
vlip_Handler14:
  TRAP_ENTRY
  jal handle_local_interrupt14
  TRAP_EXIT

#LIP15
vlip_Handler15:
  TRAP_ENTRY
  jal handle_local_interrupt15
  TRAP_EXIT

#unimplemented ISRs trap here
.weak reserved
reserved:
.weak handle_local_interrupt0
handle_local_interrupt0:
.weak handle_local_interrupt1
handle_local_interrupt1:
.weak handle_local_interrupt2
handle_local_interrupt2:
.weak handle_local_interrupt3
handle_local_interrupt3:
.weak handle_local_interrupt4
handle_local_interrupt4:
.weak handle_local_interrupt5
handle_local_interrupt5:
.weak handle_local_interrupt6
handle_local_interrupt6:
.weak handle_local_interrupt7
handle_local_interrupt7:
.weak handle_local_interrupt8
handle_local_interrupt8:
.weak handle_local_interrupt9
handle_local_interrupt9:
.weak handle_local_interrupt10
handle_local_interrupt10:
.weak handle_local_interrupt11
handle_local_interrupt11:
.weak handle_local_interrupt12
handle_local_interrupt12:
.weak handle_local_interrupt13
handle_local_interrupt13:
.weak handle_local_interrupt14
handle_local_interrupt14:
.weak handle_local_interrupt15
handle_local_interrupt15:
1:
  j 1b
	
#endif
