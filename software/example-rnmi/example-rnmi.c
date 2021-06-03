/* Copyright 2021 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#include <stdio.h>
#include <inttypes.h>
#include <metal/cpu.h>
#include <metal/machine.h>
#include <metal/csr.h>
#include <metal/nmi.h>
#include <metal/drivers/sifive_buserror0.h>

/* The sifive,error0 device is used to trigger a TileLink bus error for
 * testing the sifive,buserror0 device. If one isn't present, this example
 * will fail to compile because we have no way to trigger a bus error. */
#ifndef METAL_SIFIVE_ERROR0
#error Example requires a sifive,error0 device to drive bus errors
#endif

#define BADADDR METAL_SIFIVE_ERROR0_0_BASE_ADDRESS

/* The bus-error-unit device is used as RNMI source.
 * If one isn't present, this example will fail to
 * compile because we have no way to trigger a RNMI.
 */
#ifndef METAL_SIFIVE_BUSERROR0
#error Example requires a bus-error-unit device to drive RNMI
#endif

struct metal_cpu *cpu;
struct metal_interrupt *cpu_intr;
struct metal_buserror *beu;

volatile int rnmi_handled = 0;

void do_rnmi_irq(void) {
    printf("Enter RNMI interrupt ISR.\n");

    uintptr_t _mnscratch, _mnepc, _mncause, _mnstatus;
    uintptr_t _mscratch, _mepc, _mcause, _mstatus;

    METAL_CPU_GET_CSR(0x350, _mnscratch);
    METAL_CPU_GET_CSR(0x351, _mnepc);
    METAL_CPU_GET_CSR(0x352, _mncause);
    METAL_CPU_GET_CSR(0x353, _mnstatus);

    printf("mnscratch: 0x%08" PRIxPTR "\n", _mnscratch);
    printf("mnepc: 0x%08" PRIxPTR "\n", _mnepc);
    printf("mncause: 0x%08" PRIxPTR "\n", _mncause);
    printf("mnstatus: 0x%08" PRIxPTR "\n", _mnstatus);

    /* RNMI exception would overwrite CSRs
     * if RNMI was serviced in exception handler.
     * We need to backup current CSRs before triggering RNMI exception
     * and restore them after RNMI exception is handled.
     */
    METAL_CPU_GET_CSR(mscratch, _mscratch);
    METAL_CPU_GET_CSR(mepc, _mepc);
    METAL_CPU_GET_CSR(mcause, _mcause);
    METAL_CPU_GET_CSR(mstatus, _mstatus);

    printf("Try to trigger illegal instruction exception.\n");
    __asm__ volatile("csrr x0, 0x999");

    /* Restore CSRs. */
    METAL_CPU_SET_CSR(mscratch, _mscratch);
    METAL_CPU_SET_CSR(mepc, _mepc);
    METAL_CPU_SET_CSR(mcause, _mcause);
    METAL_CPU_SET_CSR(mstatus, _mstatus);

    metal_buserror_event_t event = metal_buserror_get_cause(beu);

    if (event & METAL_BUSERROR_EVENT_ANY) {
        printf("Handled TileLink bus error\n");
        rnmi_handled = 1;
        metal_buserror_clear_event_accrued(beu, METAL_BUSERROR_EVENT_ALL);
    }

    metal_buserror_clear_cause(beu);

    printf("Return from RNMI interrupt ISR.\n");
}

/* RNMI interrupt handler is marked with naked attribute
 * as we need to call mnret instruction by ourselves to
 * return from RNMI ISR because compiler currently doesn't
 * support this intruction.
*/
__attribute__ ((noinline))
METAL_PLACE_IN_RNMI_IRQ(0)
void rnmi_interrupt_isr(void) {
    /* Save context,
     * reserve stack for "ra" register as we only pollute "ra" register
     * with "jalr" instruction for do_rnmi_irq() function call in our ISR.
     */
    __asm__ volatile("addi sp, sp, -16");
    __asm__ volatile("sw ra, 12(sp)");

    do_rnmi_irq();

    /* Restore context */
    __asm__ volatile("lw ra, 12(sp)");
    __asm__ volatile("addi sp, sp, 16");

    /* mnret must be executed at the end of function
     * before function calls ret to return from
     * RNMI interrupt handler.
     */
    METAL_NMI_MNRET;
}

__attribute__ ((noinline))
METAL_PLACE_IN_RNMI_EXCP(0)
void rnmi_exception_isr(void) {
    printf("Enter RNMI exception ISR.\n");

    uintptr_t _mscratch, _mepc, _mcause, _mstatus;

    METAL_CPU_GET_CSR(mscratch, _mscratch);
    METAL_CPU_GET_CSR(mepc, _mepc);
    METAL_CPU_GET_CSR(mcause, _mcause);
    METAL_CPU_GET_CSR(mstatus, _mstatus);

    printf("mscratch: 0x%08" PRIxPTR "\n", _mscratch);
    printf("mepc: 0x%08" PRIxPTR "\n", _mepc);
    printf("mcause: 0x%08" PRIxPTR "\n", _mcause);
    printf("mstatus: 0x%08" PRIxPTR "\n", _mstatus);

    /* This illegal instruction exception is triggered on purpose,
     * move $mepc to the next intruction to avoid
     * recursively triggering illegal instruction exception.
     */
    METAL_CPU_SET_CSR(mepc, _mepc + 4);

    printf("Return from RNMI exception ISR.\n");
}

int main()
{
    printf("RNMI Driver Example.\n");

    cpu = metal_cpu_get(metal_cpu_get_current_hartid());
    if (cpu == NULL) {
        return 1;
    }

    beu = metal_cpu_get_buserror(cpu);
    if (beu == NULL) {
        return 2;
    }

    /* Clear any accrued events and the cause register */
    metal_buserror_clear_event_accrued(beu, METAL_BUSERROR_EVENT_ALL);
    metal_buserror_clear_cause(beu);

    /* Enable all bus error events */
    metal_buserror_set_event_enabled(beu, METAL_BUSERROR_EVENT_ALL, true);

    /* Fence above error event before check below */
    __asm__ ("fence");

    if (!metal_buserror_is_event_accrued(beu, METAL_BUSERROR_EVENT_ANY)) {
        printf("Cleared accrued bus error\n");
    }

    /* Enable hart-local interrupts for error events */
    metal_buserror_set_local_interrupt(beu, METAL_BUSERROR_EVENT_ALL, true);

    /* Fence above error clear before trigger below */
    /* Fence above interrupt enable before trigger below */
    __asm__ ("fence");

    /* Trigger an error event */
    *((volatile uint8_t *)BADADDR);

    /* Fence above error event before interrupt check below */
    __asm__ ("fence");
    __asm__ ("fence.i");

    if (!rnmi_handled) {
        return 3;
    }

    printf("Test passed!!\n");

    return 0;
}

