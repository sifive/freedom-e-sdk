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

static __attribute__ ((aligned(16))) StackType_t xISRStack[ configMINIMAL_STACK_SIZE  + 1 ] __attribute__ ((section (".heap"))) ;
__attribute__ ((aligned(4))) uint8_t ucHeap[ configTOTAL_HEAP_SIZE ] __attribute__ ((section (".heap")));


__attribute__((constructor)) static void FreeRTOS_init(void);

#if( configENABLE_FPU == 1 )
	extern void prvSetupFPU( void );
#endif /* configENABLE_FPU */

__attribute__((constructor)) static void FreeRTOS_init(void)
{
	struct metal_cpu *cpu;
	struct metal_interrupt *cpu_intr;
	extern BaseType_t xPortFreeRTOSInit( StackType_t xIsrStack );
	
	const char * const pcErrorMsg = "No External controller\n";

	/* Remove compiler warning about unused parameter. */
	( void ) pcErrorMsg;

#if ( configENABLE_FPU == 1 )
	prvSetupFPU();
#endif /* (configENABLE_FPU == 1 ) */

  /*
   * Initilize freedom-metal interrupt managment.
   *   Its SHOULD be made before calling xPortFreeRTOSInit because
   *   the interrupt/exeception handler MUST be the freertos handler.
   */
	cpu = metal_cpu_get(metal_cpu_get_current_hartid());
	if (cpu == NULL)
	{
		return;
	}

	cpu_intr = metal_cpu_interrupt_controller(cpu);
	if (cpu_intr == NULL)
	{
		return;
	}
	metal_interrupt_init(cpu_intr);

#ifdef METAL_RISCV_PLIC0
	{
		struct metal_interrupt *plic;

		// Check if this target has a plic. If not gracefull exit
		plic = metal_interrupt_get_controller(METAL_PLIC_CONTROLLER, 0);
		if (plic == NULL) {
			write( STDOUT_FILENO, pcErrorMsg, strlen( pcErrorMsg ) );

			for( ;; );
		} 
		metal_interrupt_init(plic);
	}
#endif

#ifdef METAL_SIFIVE_CLIC0
	{
	    struct metal_interrupt *clic;

		// Check we this target has a plic. If not gracefull exit
		clic = metal_interrupt_get_controller(METAL_CLIC_CONTROLLER, 0);
		if (clic == NULL) {
			write( STDOUT_FILENO, pcErrorMsg, strlen( pcErrorMsg ) );

			for( ;; );
		} 
		metal_interrupt_init(clic);
	}
#endif

	/*
	 * Call xPortFreeRTOSInit in order to set xISRTopStack
	 */
	if ( 0 != xPortFreeRTOSInit((StackType_t)&( xISRStack[ ( (configMINIMAL_STACK_SIZE - 1) & ~portBYTE_ALIGNMENT_MASK ) ] ))) {
		_exit(-1);
	}
}


void FreedomMetal_InterruptHandler( void )
{	
    int id;
    void *priv;
    struct __metal_driver_riscv_cpu_intc *intc;
    struct __metal_driver_cpu *cpu;
    portUBASE_TYPE mcause, hartid, mtvec;
	
    __asm__ __volatile__ (
		"csrr %0, mhartid \n"
		"csrr %1, mcause \n"
		"csrr %2, mtvec \n"
		: "=r"(hartid), "=r"(mcause), "=r"(mtvec)
		::
	);

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
    portUBASE_TYPE mcause, hartid;
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

	for( ;; ); // return is dangerous, we just got a critical exception.
	return;
}
