#include <stdio.h>
#include <stdlib.h>

#include "probe.h"

static trap_fn tfn = default_trap_handler;

void register_trap_fn(trap_fn fn)
{
	tfn = fn;
}

void default_trap_handler(uintptr_t mcause, uintptr_t mepc)
{
	if (tfn) {
		tfn(mcause, mepc);
	} else {
	  	printf("machine mode: unhandlable trap %p @ %p", mcause, mepc);
	  	exit(1);
	}
}

__attribute__((naked)) void mtvec_entry(void)
{
	asm volatile(
		/* save callee save registers */
		EXPAND_STACK(TRAP_CTX_SIZE)
		SAVE_REG(ra,0)
		SAVE_REG(a0,1)
		SAVE_REG(a1,2)
		SAVE_REG(a2,3)
		SAVE_REG(a3,4)
		SAVE_REG(a4,5)
		SAVE_REG(a5,6)
		SAVE_REG(a6,7)
		SAVE_REG(a7,8)
		SAVE_REG(t0,9)
		SAVE_REG(t1,10)
		SAVE_REG(t2,11)
		SAVE_REG(t3,12)
		SAVE_REG(t4,13)
		SAVE_REG(t5,14)
		SAVE_REG(t6,15)

		/* call trap handler */
		"csrr a0, mcause\n"
		"csrr a1, mepc\n"
		"mv	  a2, sp\n"
		"call tfn\n"

		/* restore callee save registers */
		RSTR_REG(ra,0)
		RSTR_REG(a0,1)
		RSTR_REG(a1,2)
		RSTR_REG(a2,3)
		RSTR_REG(a3,4)
		RSTR_REG(a4,5)
		RSTR_REG(a5,6)
		RSTR_REG(a6,7)
		RSTR_REG(a7,8)
		RSTR_REG(t0,9)
		RSTR_REG(t1,10)
		RSTR_REG(t2,11)
		RSTR_REG(t3,12)
		RSTR_REG(t4,13)
		RSTR_REG(t5,14)
		RSTR_REG(t6,15)
		CONTRACT_STACK(TRAP_CTX_SIZE)

		/* return from trap handler */
		"mret\n"
	);
}
