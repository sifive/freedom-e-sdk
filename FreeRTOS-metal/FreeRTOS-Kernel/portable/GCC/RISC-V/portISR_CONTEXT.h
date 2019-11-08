#ifndef RISCV_portISR_CONTEXT_H
#define RISCV_portISR_CONTEXT_H
/*
 * NOTE: This header file is used in both C and ASM.
 *       You'll see the #ifdef  __ASSEMBLY__
 *
 *       This allows a cross check between C data
 *       structures and ASM structure offsets 
 *       to be shared between ASM and C.
 *
 * As a result, be careful of what and how you change this file.
 */
#ifndef __riscv_xlen
#error Missing __riscv_xlen
#endif

#if __riscv_xlen == 64
	#define portWORD_SIZE 8
	#define store_x sd
	#define load_x ld
#elif __riscv_xlen == 32
	#define store_x sw
	#define load_x lw
	#define portWORD_SIZE 4
#else
	#error Assembler did not define __riscv_xlen
#endif

/* integer registers */
#define PORT_REGISTER_SIZEOF        (__riscv_xlen / 8)
#if defined(__riscv_flen)
/* how large are floating point registers */
#define PORT_FPU_REGISTER_SIZEOF  (__riscv_flen / 8)
#endif

#if !defined(portADDITIONAL_CONTEXT_REGS)
/*
 * if the port requires additional thing saved as part
 * of the task context, must be non-zero
 *
 * NOTE: For ABI Stack alignment reasons also a multiple of 4.
 *
 *       Provide a default value that can be used in compile time
 *       non-preprocessor C expressions.
 *       
 */
#define portADDITIONAL_CONTEXT_REGS 0
#endif


/* these index must match the union below, and be visible/usable in ASM code. */
#define PORT_CONTEXT_xIDX(X)      (X) /* index into "raw" for register x? */
#define PORT_CONTEXT_mcauseIDX    (32)
#define PORT_CONTEXT_mepcIDX      (33)
#define PORT_CONTEXT_mstatusIDX   (34)
#define PORT_CONTEXT_rufIDX    	  (35)
#define PORT_CONTEXT_extraIDX(X)  (36+X)
#define PORT_CONTEXT_lastIDX      (36+portADDITIONAL_CONTEXT_REGS)

/* used in assembler, as byte offsets from the start of the context */
#define PORT_CONTEXT_xOFFSET( X )   (PORT_CONTEXT_xIDX(X)    * PORT_REGISTER_SIZEOF)
#define PORT_CONTEXT_mcauseOFFSET   (PORT_CONTEXT_mcauseIDX  * PORT_REGISTER_SIZEOF)
#define PORT_CONTEXT_mepcOFFSET     (PORT_CONTEXT_mepcIDX    * PORT_REGISTER_SIZEOF)
#define PORT_CONTEXT_mstatusOFFSET  (PORT_CONTEXT_mstatusIDX * PORT_REGISTER_SIZEOF)
#define PORT_CONTEXT_rufOFFSET   	(PORT_CONTEXT_rufIDX  	 * PORT_REGISTER_SIZEOF)
#define PORT_CONTEXT_extraOFFSET(X) (PORT_CONTEXT_mepcIDX    * PORT_REGISTER_SIZEOF)
/* total size of the structure usable in ASM. */
#define PORT_CONTEXT_SIZEOF         (PORT_CONTEXT_lastIDX   * PORT_REGISTER_SIZEOF)

#ifndef __ASSEMBLY__
/* these are required for the union below */
#include <stdint.h> /* C99 standar types */
#include <assert.h> /* static assert */

/*
 * This is a IRQ Context - during an interrupt or exception.
 * At an interrupt, this is pushed onto the stack
 *
 * To maintain RISCV ABI stack alignment requirements(16bytes)
 * this data structure must be a MULTIPLE of 16 bytes in size.
 */
union portRISCV_CONTEXT {
    uintptr_t raw[PORT_CONTEXT_lastIDX];
    struct {
	/* for simplicity, position x[0] is not used */
	uintptr_t x[32];
	uintptr_t mcause;  	/* 33rd register */
	uintptr_t mepc;    	/* 34th register */
	uintptr_t mstatus; 	/* 35th register */
	uintptr_t ruf;  	/* 36th register */
#if portADDITIONAL_CONTEXT_REGS
#if (portADDITIONAL_CONTEXT_REGS % 4) != 0
#error Must be multiple of 4.
#endif
	uintptr_t extra[ portADDITIONAL_CONTEXT_REGS ];
#endif
    } named;
};

/* this is the common raw assembler trap handler code */
void freertos_risc_v_trap_handler(void);

void portRISCV_ASM_ASSERT(void);

#endif /* __ASSEMBLY__ */

#endif /* RISCV_portISR_CONTEXT_H */
