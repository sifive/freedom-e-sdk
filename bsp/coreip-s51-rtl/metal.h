#ifndef ASSEMBLY

#ifndef COREIP_S51_RTL__METAL_H
#define COREIP_S51_RTL__METAL_H

#ifdef __METAL_MACHINE_MACROS

#define __METAL_PLIC_SUBINTERRUPTS 128

#ifndef __METAL_PLIC_SUBINTERRUPTS
#define __METAL_PLIC_SUBINTERRUPTS 0
#endif
#ifndef __METAL_CLIC_SUBINTERRUPTS
#define __METAL_CLIC_SUBINTERRUPTS 0
#endif

#else /* ! __METAL_MACHINE_MACROS */

#define __METAL_CLINT_2000000_INTERRUPTS 2

#define METAL_MAX_CLINT_INTERRUPTS 2

#define __METAL_INTERRUPT_CONTROLLER_C000000_INTERRUPTS 1

#define __METAL_PLIC_SUBINTERRUPTS 128

#define METAL_MAX_PLIC_INTERRUPTS 1

#define __METAL_CLIC_SUBINTERRUPTS 0
#define METAL_MAX_CLIC_INTERRUPTS 0

#define __METAL_LOCAL_EXTERNAL_INTERRUPTS_0_INTERRUPTS 16

#define METAL_MAX_LOCAL_EXT_INTERRUPTS 16

#define __METAL_GLOBAL_EXTERNAL_INTERRUPTS_INTERRUPTS 127

#define METAL_MAX_GLOBAL_EXT_INTERRUPTS 127

#define METAL_MAX_GPIO_INTERRUPTS 0

#define METAL_MAX_UART_INTERRUPTS 0


#include <metal/drivers/fixed-clock.h>
#include <metal/drivers/riscv,clint0.h>
#include <metal/drivers/riscv,cpu.h>
#include <metal/drivers/riscv,plic0.h>
#include <metal/pmp.h>
#include <metal/drivers/sifive,local-external-interrupts0.h>
#include <metal/drivers/sifive,global-external-interrupts0.h>
#include <metal/drivers/sifive,test0.h>

/* From clint@2000000 */
asm (".weak __metal_dt_clint_2000000");
struct __metal_driver_riscv_clint0 __metal_dt_clint_2000000;

/* From cpu@0 */
asm (".weak __metal_dt_cpu_0");
struct __metal_driver_cpu __metal_dt_cpu_0;

/* From interrupt_controller */
asm (".weak __metal_dt_interrupt_controller");
struct __metal_driver_riscv_cpu_intc __metal_dt_interrupt_controller;

/* From interrupt_controller@c000000 */
asm (".weak __metal_dt_interrupt_controller_c000000");
struct __metal_driver_riscv_plic0 __metal_dt_interrupt_controller_c000000;

asm (".weak __metal_dt_pmp_0");
struct metal_pmp __metal_dt_pmp_0;

/* From local_external_interrupts_0 */
asm (".weak __metal_dt_local_external_interrupts_0");
struct __metal_driver_sifive_local_external_interrupts0 __metal_dt_local_external_interrupts_0;

/* From global_external_interrupts */
asm (".weak __metal_dt_global_external_interrupts");
struct __metal_driver_sifive_global_external_interrupts0 __metal_dt_global_external_interrupts;

/* From teststatus@4000 */
asm (".weak __metal_dt_teststatus_4000");
struct __metal_driver_sifive_test0 __metal_dt_teststatus_4000;


/* From clint@2000000 */
struct __metal_driver_riscv_clint0 __metal_dt_clint_2000000 = {
    .vtable = &__metal_driver_vtable_riscv_clint0,
    .controller.vtable = &__metal_driver_vtable_riscv_clint0.clint_vtable,
    .control_base = 33554432UL,
    .control_size = 65536UL,
    .init_done = 0,
    .num_interrupts = METAL_MAX_CLINT_INTERRUPTS,
    .interrupt_parent = &__metal_dt_interrupt_controller.controller,
    .interrupt_lines[0] = 3,
    .interrupt_lines[1] = 7,
};

/* From cpu@0 */
struct __metal_driver_cpu __metal_dt_cpu_0 = {
    .vtable = &__metal_driver_vtable_cpu,
    .cpu.vtable = &__metal_driver_vtable_cpu.cpu_vtable,
    .timebase = 1000000UL,
    .interrupt_controller = &__metal_dt_interrupt_controller.controller,
};

/* From interrupt_controller */
struct __metal_driver_riscv_cpu_intc __metal_dt_interrupt_controller = {
    .vtable = &__metal_driver_vtable_riscv_cpu_intc,
    .controller.vtable = &__metal_driver_vtable_riscv_cpu_intc.controller_vtable,
    .init_done = 0,
    .interrupt_controller = 1,
};

/* From interrupt_controller@c000000 */
struct __metal_driver_riscv_plic0 __metal_dt_interrupt_controller_c000000 = {
    .vtable = &__metal_driver_vtable_riscv_plic0,
    .controller.vtable = &__metal_driver_vtable_riscv_plic0.plic_vtable,
    .init_done = 0,
/* From interrupt_controller */
    .interrupt_parent = &__metal_dt_interrupt_controller.controller,
    .interrupt_line = 11UL,
    .control_base = 201326592UL,
    .control_size = 67108864UL,
    .max_priority = 7UL,
    .num_interrupts = 128UL,
    .interrupt_controller = 1,
};

/* From pmp@0 */
struct metal_pmp __metal_dt_pmp_0 = {
    .num_regions = 8UL,
};

/* From local_external_interrupts_0 */
struct __metal_driver_sifive_local_external_interrupts0 __metal_dt_local_external_interrupts_0 = {
    .vtable = &__metal_driver_vtable_sifive_local_external_interrupts0,
    .irc.vtable = &__metal_driver_vtable_sifive_local_external_interrupts0.local0_vtable,
    .init_done = 0,
/* From interrupt_controller */
    .interrupt_parent = &__metal_dt_interrupt_controller.controller,
    .num_interrupts = METAL_MAX_LOCAL_EXT_INTERRUPTS,
    .interrupt_lines[0] = 16,
    .interrupt_lines[1] = 17,
    .interrupt_lines[2] = 18,
    .interrupt_lines[3] = 19,
    .interrupt_lines[4] = 20,
    .interrupt_lines[5] = 21,
    .interrupt_lines[6] = 22,
    .interrupt_lines[7] = 23,
    .interrupt_lines[8] = 24,
    .interrupt_lines[9] = 25,
    .interrupt_lines[10] = 26,
    .interrupt_lines[11] = 27,
    .interrupt_lines[12] = 28,
    .interrupt_lines[13] = 29,
    .interrupt_lines[14] = 30,
    .interrupt_lines[15] = 31,
};

/* From global_external_interrupts */
struct __metal_driver_sifive_global_external_interrupts0 __metal_dt_global_external_interrupts = {
    .vtable = &__metal_driver_vtable_sifive_global_external_interrupts0,
    .irc.vtable = &__metal_driver_vtable_sifive_global_external_interrupts0.global0_vtable,
    .init_done = 0,
/* From interrupt_controller@c000000 */
    .interrupt_parent = &__metal_dt_interrupt_controller_c000000.controller,
    .num_interrupts = METAL_MAX_GLOBAL_EXT_INTERRUPTS,
    .interrupt_lines[0] = 1,
    .interrupt_lines[1] = 2,
    .interrupt_lines[2] = 3,
    .interrupt_lines[3] = 4,
    .interrupt_lines[4] = 5,
    .interrupt_lines[5] = 6,
    .interrupt_lines[6] = 7,
    .interrupt_lines[7] = 8,
    .interrupt_lines[8] = 9,
    .interrupt_lines[9] = 10,
    .interrupt_lines[10] = 11,
    .interrupt_lines[11] = 12,
    .interrupt_lines[12] = 13,
    .interrupt_lines[13] = 14,
    .interrupt_lines[14] = 15,
    .interrupt_lines[15] = 16,
    .interrupt_lines[16] = 17,
    .interrupt_lines[17] = 18,
    .interrupt_lines[18] = 19,
    .interrupt_lines[19] = 20,
    .interrupt_lines[20] = 21,
    .interrupt_lines[21] = 22,
    .interrupt_lines[22] = 23,
    .interrupt_lines[23] = 24,
    .interrupt_lines[24] = 25,
    .interrupt_lines[25] = 26,
    .interrupt_lines[26] = 27,
    .interrupt_lines[27] = 28,
    .interrupt_lines[28] = 29,
    .interrupt_lines[29] = 30,
    .interrupt_lines[30] = 31,
    .interrupt_lines[31] = 32,
    .interrupt_lines[32] = 33,
    .interrupt_lines[33] = 34,
    .interrupt_lines[34] = 35,
    .interrupt_lines[35] = 36,
    .interrupt_lines[36] = 37,
    .interrupt_lines[37] = 38,
    .interrupt_lines[38] = 39,
    .interrupt_lines[39] = 40,
    .interrupt_lines[40] = 41,
    .interrupt_lines[41] = 42,
    .interrupt_lines[42] = 43,
    .interrupt_lines[43] = 44,
    .interrupt_lines[44] = 45,
    .interrupt_lines[45] = 46,
    .interrupt_lines[46] = 47,
    .interrupt_lines[47] = 48,
    .interrupt_lines[48] = 49,
    .interrupt_lines[49] = 50,
    .interrupt_lines[50] = 51,
    .interrupt_lines[51] = 52,
    .interrupt_lines[52] = 53,
    .interrupt_lines[53] = 54,
    .interrupt_lines[54] = 55,
    .interrupt_lines[55] = 56,
    .interrupt_lines[56] = 57,
    .interrupt_lines[57] = 58,
    .interrupt_lines[58] = 59,
    .interrupt_lines[59] = 60,
    .interrupt_lines[60] = 61,
    .interrupt_lines[61] = 62,
    .interrupt_lines[62] = 63,
    .interrupt_lines[63] = 64,
    .interrupt_lines[64] = 65,
    .interrupt_lines[65] = 66,
    .interrupt_lines[66] = 67,
    .interrupt_lines[67] = 68,
    .interrupt_lines[68] = 69,
    .interrupt_lines[69] = 70,
    .interrupt_lines[70] = 71,
    .interrupt_lines[71] = 72,
    .interrupt_lines[72] = 73,
    .interrupt_lines[73] = 74,
    .interrupt_lines[74] = 75,
    .interrupt_lines[75] = 76,
    .interrupt_lines[76] = 77,
    .interrupt_lines[77] = 78,
    .interrupt_lines[78] = 79,
    .interrupt_lines[79] = 80,
    .interrupt_lines[80] = 81,
    .interrupt_lines[81] = 82,
    .interrupt_lines[82] = 83,
    .interrupt_lines[83] = 84,
    .interrupt_lines[84] = 85,
    .interrupt_lines[85] = 86,
    .interrupt_lines[86] = 87,
    .interrupt_lines[87] = 88,
    .interrupt_lines[88] = 89,
    .interrupt_lines[89] = 90,
    .interrupt_lines[90] = 91,
    .interrupt_lines[91] = 92,
    .interrupt_lines[92] = 93,
    .interrupt_lines[93] = 94,
    .interrupt_lines[94] = 95,
    .interrupt_lines[95] = 96,
    .interrupt_lines[96] = 97,
    .interrupt_lines[97] = 98,
    .interrupt_lines[98] = 99,
    .interrupt_lines[99] = 100,
    .interrupt_lines[100] = 101,
    .interrupt_lines[101] = 102,
    .interrupt_lines[102] = 103,
    .interrupt_lines[103] = 104,
    .interrupt_lines[104] = 105,
    .interrupt_lines[105] = 106,
    .interrupt_lines[106] = 107,
    .interrupt_lines[107] = 108,
    .interrupt_lines[108] = 109,
    .interrupt_lines[109] = 110,
    .interrupt_lines[110] = 111,
    .interrupt_lines[111] = 112,
    .interrupt_lines[112] = 113,
    .interrupt_lines[113] = 114,
    .interrupt_lines[114] = 115,
    .interrupt_lines[115] = 116,
    .interrupt_lines[116] = 117,
    .interrupt_lines[117] = 118,
    .interrupt_lines[118] = 119,
    .interrupt_lines[119] = 120,
    .interrupt_lines[120] = 121,
    .interrupt_lines[121] = 122,
    .interrupt_lines[122] = 123,
    .interrupt_lines[123] = 124,
    .interrupt_lines[124] = 125,
    .interrupt_lines[125] = 126,
    .interrupt_lines[126] = 127,
};

/* From teststatus@4000 */
struct __metal_driver_sifive_test0 __metal_dt_teststatus_4000 = {
    .vtable = &__metal_driver_vtable_sifive_test0,
    .shutdown.vtable = &__metal_driver_vtable_sifive_test0.shutdown,
    .base = 16384UL,
    .size = 4096UL,
};


/* From clint@2000000 */
#define __METAL_DT_RISCV_CLINT0_HANDLE (&__metal_dt_clint_2000000.controller)

#define __METAL_DT_CLINT_2000000_HANDLE (&__metal_dt_clint_2000000.controller)

/* From cpu@0 */
#define __METAL_DT_RISCV_CPU_HANDLE (&__metal_dt_cpu_0.cpu)

#define __METAL_DT_CPU_0_HANDLE (&__metal_dt_cpu_0.cpu)

#define __METAL_DT_MAX_HARTS 1

asm (".weak __metal_cpu_table");
struct __metal_driver_cpu *__metal_cpu_table[] = {
					&__metal_dt_cpu_0};

/* From interrupt_controller */
#define __METAL_DT_RISCV_CPU_INTC_HANDLE (&__metal_dt_interrupt_controller.controller)

#define __METAL_DT_INTERRUPT_CONTROLLER_HANDLE (&__metal_dt_interrupt_controller.controller)

/* From interrupt_controller@c000000 */
#define __METAL_DT_RISCV_PLIC0_HANDLE (&__metal_dt_interrupt_controller_c000000.controller)

#define __METAL_DT_INTERRUPT_CONTROLLER_C000000_HANDLE (&__metal_dt_interrupt_controller_c000000.controller)

/* From pmp@0 */
#define __METAL_DT_PMP_HANDLE (&__metal_dt_pmp_0)

/* From local_external_interrupts_0 */
#define __METAL_DT_SIFIVE_LOCAL_EXINTR0_HANDLE (&__metal_dt_local_external_interrupts_0.irc)

#define __METAL_DT_LOCAL_EXTERNAL_INTERRUPTS_0_HANDLE (&__metal_dt_local_external_interrupts_0.irc)

/* From global_external_interrupts */
#define __METAL_DT_SIFIVE_GLOBAL_EXINTR0_HANDLE (&__metal_dt_global_external_interrupts.irc)

#define __METAL_DT_GLOBAL_EXTERNAL_INTERRUPTS_HANDLE (&__metal_dt_global_external_interrupts.irc)

#define __MEE_DT_MAX_GPIOS 0

asm (".weak __metal_gpio_table");
struct __metal_driver_sifive_gpio0 *__metal_gpio_table[] = {
					NULL };
#define __METAL_DT_MAX_BUTTONS 0

asm (".weak __metal_button_table");
struct __metal_driver_sifive_gpio_button *__metal_button_table[] = {
					NULL };
#define __METAL_DT_MAX_LEDS 0

asm (".weak __metal_led_table");
struct __metal_driver_sifive_gpio_led *__metal_led_table[] = {
					NULL };
#define __METAL_DT_MAX_SWITCHES 0

asm (".weak __metal_switch_table");
struct __metal_driver_sifive_gpio_switch *__metal_switch_table[] = {
					NULL };
#define __METAL_DT_MAX_SPIS 0

asm (".weak __metal_spi_table");
struct __metal_driver_sifive_spi0 *__metal_spi_table[] = {
					NULL };
/* From teststatus@4000 */
#define __METAL_DT_SHUTDOWN_HANDLE (&__metal_dt_teststatus_4000.shutdown)

#define __METAL_DT_TESTSTATUS_4000_HANDLE (&__metal_dt_teststatus_4000.shutdown)


#endif /* ! __METAL_MACHINE_MACROS */
#endif /* COREIP_S51_RTL__METAL_H*/
#endif /* ! ASSEMBLY */
