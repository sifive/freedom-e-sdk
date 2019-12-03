/* Copyright 2019 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

/* FreeRTOS kernel includes. */
#include <FreeRTOS.h>

/* Freedom metal includes. */
#include <metal/machine.h>
#include <metal/machine/platform.h>

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#if( configUSE_SEGGER_SYSTEMVIEW == 1 )
# include "SEGGER_SYSVIEW_FreeRTOS.h"
#endif

StackType_t *xISRStackTop;
#if (__riscv_xlen == 64)
uint64_t *__freertos_irq_stack_top;
extern uint64_t metal_segment_stack_end;
#elif (__riscv_xlen == 32)
uint32_t *__freertos_irq_stack_top;
extern uint32_t metal_segment_stack_end;
#endif


#if( configAPPLICATION_ALLOCATED_HEAP == 1 )
uint8_t ucHeap;
#endif

__attribute__((constructor)) static void FreeRTOS_init(void);
#ifdef SEGGER_SYSTEMVIEW
__attribute__((constructor)) static void SEGGER_SysView_init(void);
#endif

__attribute__((constructor)) static void FreeRTOS_init(void)
{
#if (__riscv_xlen == 64)
  uint64_t Addr = (uint64_t)&metal_segment_stack_end;
#elif (__riscv_xlen == 32)
  uint32_t Addr = (uint32_t)&metal_segment_stack_end;
#endif

#if( configAPPLICATION_ALLOCATED_HEAP == 1 )
	ucHeap = (uint8_t *)&metal_segment_heap_target_start;
#endif

  Addr &= (~0x0f); /* align per ABI requirement */

  xISRStackTop = (StackType_t *)Addr;
}


void FreedomMetal_InterruptHandler( portUBASE_TYPE hartid, portUBASE_TYPE mcause, portUBASE_TYPE mtvec )
{	
    int id;
    void *priv;
    struct __metal_driver_riscv_cpu_intc *intc;
    struct __metal_driver_cpu *cpu;

    cpu = __metal_cpu_table[hartid];

    if ( cpu ) {

        intc = (struct __metal_driver_riscv_cpu_intc *)
          __metal_driver_cpu_interrupt_controller((struct metal_cpu *)cpu);
        id = mcause & METAL_MCAUSE_CAUSE;

		if ((id < METAL_INTERRUPT_ID_LC0) ||
		   ((mtvec & METAL_MTVEC_MASK) == METAL_MTVEC_DIRECT)) {
		    priv = intc->metal_int_table[id].exint_data;
			if (intc->metal_int_table[id].handler != NULL)
		    	intc->metal_int_table[id].handler(id, priv);
			goto cleanup;
		}
		if ((mtvec & METAL_MTVEC_MASK) == METAL_MTVEC_CLIC) {
		    uintptr_t mtvt;
		    metal_interrupt_handler_t mtvt_handler;

		    __asm volatile ("csrr %0, mtvt" : "=r"(mtvt));
		    priv = intc->metal_int_table[METAL_INTERRUPT_ID_SW].sub_int;
		    mtvt_handler = (metal_interrupt_handler_t)mtvt;
			if (mtvt_handler != NULL)
		    	mtvt_handler(id, priv);
			goto cleanup;
		}
	}

cleanup:
	return;
}

void FreedomMetal_ExceptionHandler( void )
{
    int id;
    uintptr_t mcause, hartid;
    struct __metal_driver_riscv_cpu_intc *intc;
    struct __metal_driver_cpu *cpu;
	
    __asm__ __volatile__ ("csrr %0, mhartid" : "=r"(hartid));
    cpu = __metal_cpu_table[hartid];

    if ( cpu ) {
        intc = (struct __metal_driver_riscv_cpu_intc *)
          __metal_driver_cpu_interrupt_controller((struct metal_cpu *)cpu);

        __asm__ __volatile__ ("csrr %0, mcause" : "=r"(mcause));
        id = mcause & METAL_MCAUSE_CAUSE;

		configASSERT( id < METAL_ECALL_U_EXCEPTION_CODE );

		if (id < METAL_ECALL_U_EXCEPTION_CODE) {
			if (intc->metal_exception_table[id] != NULL)
				intc->metal_exception_table[id]((struct metal_cpu *)cpu, id);
		}
	}

	for( ;; ); // return i dangerous, we just got a critical exception.
	return;
}

#if( configUSE_SEGGER_SYSTEMVIEW == 1 )
__attribute__((constructor)) static void SEGGER_SysView_init(void)
{
	SEGGER_SYSVIEW_Conf();
  SEGGER_SYSVIEW_Start();
}

U32 SEGGER_SYSVIEW_X_GetInterruptId(void) {
#if (__riscv_xlen == 64)
  uintptr_t mcause;

  __asm__ __volatile__ ("csrr %0, mcause" : "=r"(mcause));

  if (mcause & 0x8000000000000000)
    mcause = mcause & 0x7FFFFFFFFFFFFFFF;
  else
    mcause = mcause & 0x8000000000000000;

  return (U32)mcause;
#elif (__riscv_xlen == 32)
  uintptr_t mcause;

  __asm__ __volatile__ ("csrr %0, mcause" : "=r"(mcause));

  if (mcause & 0x80000000)
    mcause = mcause & 0x7FFFFFFF;
  else
    mcause = mcause & 0x80000000;

  return (U32)mcause;
#endif
}

#ifndef configCLINT_BASE_ADDRESS
  #error No CLINT Base Address defined
#endif

U32 SEGGER_SYSVIEW_X_GetTimestamp(void) {
#if (__riscv_xlen == 64)
  return (U32)(*(( uint64_t * volatile ) ( configCLINT_BASE_ADDRESS + 0xBFF8) ));
#elif (__riscv_xlen == 32) 
  uint32_t lo, hi;

    /* Guard against rollover when reading */
    do {
        hi = *(( uint32_t * volatile ) ( configCLINT_BASE_ADDRESS + 0xBFFC) );
        lo = *(( uint32_t * volatile ) ( configCLINT_BASE_ADDRESS + 0xBFF8) );
    } while ( *(( uint32_t * volatile ) ( configCLINT_BASE_ADDRESS + 0xBFFC)) != hi);

	return (U32)lo;
#endif
}

#endif
