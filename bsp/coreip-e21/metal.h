#ifndef ASSEMBLY

#ifndef COREIP_E21__METAL_H
#define COREIP_E21__METAL_H

#ifdef __METAL_MACHINE_MACROS

#define __METAL_CLIC_SUBINTERRUPTS 143

#ifndef __METAL_CLIC_SUBINTERRUPTS
#define __METAL_CLIC_SUBINTERRUPTS 0
#endif

#else /* ! __METAL_MACHINE_MACROS */

#define METAL_MAX_CLINT_INTERRUPTS 0

#define METAL_MAX_PLIC_INTERRUPTS 0

#define __METAL_INTERRUPT_CONTROLLER_2000000_INTERRUPTS 3

#define __METAL_CLIC_SUBINTERRUPTS 143

#define METAL_MAX_CLIC_INTERRUPTS 3

#define __METAL_LOCAL_EXTERNAL_INTERRUPTS_0_INTERRUPTS 127

#define METAL_MAX_LOCAL_EXT_INTERRUPTS 127

#define METAL_MAX_GLOBAL_EXT_INTERRUPTS 0

#define METAL_MAX_GPIO_INTERRUPTS 0

#define METAL_MAX_UART_INTERRUPTS 0


#include <metal/drivers/fixed-clock.h>
#include <metal/drivers/riscv,cpu.h>
#include <metal/pmp.h>
#include <metal/drivers/sifive,clic0.h>
#include <metal/drivers/sifive,local-external-interrupts0.h>
#include <metal/drivers/sifive,test0.h>

/* From cpu@0 */
asm (".weak __metal_dt_cpu_0");
struct __metal_driver_cpu __metal_dt_cpu_0;

/* From interrupt_controller */
asm (".weak __metal_dt_interrupt_controller");
struct __metal_driver_riscv_cpu_intc __metal_dt_interrupt_controller;

asm (".weak __metal_dt_pmp_0");
struct metal_pmp __metal_dt_pmp_0;

/* From interrupt_controller@2000000 */
asm (".weak __metal_dt_interrupt_controller_2000000");
struct __metal_driver_sifive_clic0 __metal_dt_interrupt_controller_2000000;

/* From local_external_interrupts_0 */
asm (".weak __metal_dt_local_external_interrupts_0");
struct __metal_driver_sifive_local_external_interrupts0 __metal_dt_local_external_interrupts_0;

/* From teststatus@4000 */
asm (".weak __metal_dt_teststatus_4000");
struct __metal_driver_sifive_test0 __metal_dt_teststatus_4000;


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

/* From pmp@0 */
struct metal_pmp __metal_dt_pmp_0 = {
    .num_regions = 8UL,
};

/* From interrupt_controller@2000000 */
struct __metal_driver_sifive_clic0 __metal_dt_interrupt_controller_2000000 = {
    .vtable = &__metal_driver_vtable_sifive_clic0,
    .controller.vtable = &__metal_driver_vtable_sifive_clic0.clic_vtable,
    .control_base = 33554432UL,
    .control_size = 16777216UL,
    .init_done = 0,
    .num_interrupts = METAL_MAX_CLIC_INTERRUPTS,
    .interrupt_parent = &__metal_dt_interrupt_controller.controller,
    .interrupt_lines[0] = 3,
    .interrupt_lines[1] = 7,
    .interrupt_lines[2] = 11,
    .num_subinterrupts = 143UL,
    .num_intbits = 2UL,
    .max_levels = 16UL,
    .interrupt_controller = 1,
};

/* From local_external_interrupts_0 */
struct __metal_driver_sifive_local_external_interrupts0 __metal_dt_local_external_interrupts_0 = {
    .vtable = &__metal_driver_vtable_sifive_local_external_interrupts0,
    .irc.vtable = &__metal_driver_vtable_sifive_local_external_interrupts0.local0_vtable,
    .init_done = 0,
/* From interrupt_controller@2000000 */
    .interrupt_parent = &__metal_dt_interrupt_controller_2000000.controller,
    .num_interrupts = METAL_MAX_LOCAL_EXT_INTERRUPTS,
    .interrupt_lines[0] = 0,
    .interrupt_lines[1] = 1,
    .interrupt_lines[2] = 2,
    .interrupt_lines[3] = 3,
    .interrupt_lines[4] = 4,
    .interrupt_lines[5] = 5,
    .interrupt_lines[6] = 6,
    .interrupt_lines[7] = 7,
    .interrupt_lines[8] = 8,
    .interrupt_lines[9] = 9,
    .interrupt_lines[10] = 10,
    .interrupt_lines[11] = 11,
    .interrupt_lines[12] = 12,
    .interrupt_lines[13] = 13,
    .interrupt_lines[14] = 14,
    .interrupt_lines[15] = 15,
    .interrupt_lines[16] = 16,
    .interrupt_lines[17] = 17,
    .interrupt_lines[18] = 18,
    .interrupt_lines[19] = 19,
    .interrupt_lines[20] = 20,
    .interrupt_lines[21] = 21,
    .interrupt_lines[22] = 22,
    .interrupt_lines[23] = 23,
    .interrupt_lines[24] = 24,
    .interrupt_lines[25] = 25,
    .interrupt_lines[26] = 26,
    .interrupt_lines[27] = 27,
    .interrupt_lines[28] = 28,
    .interrupt_lines[29] = 29,
    .interrupt_lines[30] = 30,
    .interrupt_lines[31] = 31,
    .interrupt_lines[32] = 32,
    .interrupt_lines[33] = 33,
    .interrupt_lines[34] = 34,
    .interrupt_lines[35] = 35,
    .interrupt_lines[36] = 36,
    .interrupt_lines[37] = 37,
    .interrupt_lines[38] = 38,
    .interrupt_lines[39] = 39,
    .interrupt_lines[40] = 40,
    .interrupt_lines[41] = 41,
    .interrupt_lines[42] = 42,
    .interrupt_lines[43] = 43,
    .interrupt_lines[44] = 44,
    .interrupt_lines[45] = 45,
    .interrupt_lines[46] = 46,
    .interrupt_lines[47] = 47,
    .interrupt_lines[48] = 48,
    .interrupt_lines[49] = 49,
    .interrupt_lines[50] = 50,
    .interrupt_lines[51] = 51,
    .interrupt_lines[52] = 52,
    .interrupt_lines[53] = 53,
    .interrupt_lines[54] = 54,
    .interrupt_lines[55] = 55,
    .interrupt_lines[56] = 56,
    .interrupt_lines[57] = 57,
    .interrupt_lines[58] = 58,
    .interrupt_lines[59] = 59,
    .interrupt_lines[60] = 60,
    .interrupt_lines[61] = 61,
    .interrupt_lines[62] = 62,
    .interrupt_lines[63] = 63,
    .interrupt_lines[64] = 64,
    .interrupt_lines[65] = 65,
    .interrupt_lines[66] = 66,
    .interrupt_lines[67] = 67,
    .interrupt_lines[68] = 68,
    .interrupt_lines[69] = 69,
    .interrupt_lines[70] = 70,
    .interrupt_lines[71] = 71,
    .interrupt_lines[72] = 72,
    .interrupt_lines[73] = 73,
    .interrupt_lines[74] = 74,
    .interrupt_lines[75] = 75,
    .interrupt_lines[76] = 76,
    .interrupt_lines[77] = 77,
    .interrupt_lines[78] = 78,
    .interrupt_lines[79] = 79,
    .interrupt_lines[80] = 80,
    .interrupt_lines[81] = 81,
    .interrupt_lines[82] = 82,
    .interrupt_lines[83] = 83,
    .interrupt_lines[84] = 84,
    .interrupt_lines[85] = 85,
    .interrupt_lines[86] = 86,
    .interrupt_lines[87] = 87,
    .interrupt_lines[88] = 88,
    .interrupt_lines[89] = 89,
    .interrupt_lines[90] = 90,
    .interrupt_lines[91] = 91,
    .interrupt_lines[92] = 92,
    .interrupt_lines[93] = 93,
    .interrupt_lines[94] = 94,
    .interrupt_lines[95] = 95,
    .interrupt_lines[96] = 96,
    .interrupt_lines[97] = 97,
    .interrupt_lines[98] = 98,
    .interrupt_lines[99] = 99,
    .interrupt_lines[100] = 100,
    .interrupt_lines[101] = 101,
    .interrupt_lines[102] = 102,
    .interrupt_lines[103] = 103,
    .interrupt_lines[104] = 104,
    .interrupt_lines[105] = 105,
    .interrupt_lines[106] = 106,
    .interrupt_lines[107] = 107,
    .interrupt_lines[108] = 108,
    .interrupt_lines[109] = 109,
    .interrupt_lines[110] = 110,
    .interrupt_lines[111] = 111,
    .interrupt_lines[112] = 112,
    .interrupt_lines[113] = 113,
    .interrupt_lines[114] = 114,
    .interrupt_lines[115] = 115,
    .interrupt_lines[116] = 116,
    .interrupt_lines[117] = 117,
    .interrupt_lines[118] = 118,
    .interrupt_lines[119] = 119,
    .interrupt_lines[120] = 120,
    .interrupt_lines[121] = 121,
    .interrupt_lines[122] = 122,
    .interrupt_lines[123] = 123,
    .interrupt_lines[124] = 124,
    .interrupt_lines[125] = 125,
    .interrupt_lines[126] = 126,
};

/* From teststatus@4000 */
struct __metal_driver_sifive_test0 __metal_dt_teststatus_4000 = {
    .vtable = &__metal_driver_vtable_sifive_test0,
    .shutdown.vtable = &__metal_driver_vtable_sifive_test0.shutdown,
    .base = 16384UL,
    .size = 4096UL,
};


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

/* From pmp@0 */
#define __METAL_DT_PMP_HANDLE (&__metal_dt_pmp_0)

/* From interrupt_controller@2000000 */
#define __METAL_DT_SIFIVE_CLIC0_HANDLE (&__metal_dt_interrupt_controller_2000000.controller)

#define __METAL_DT_INTERRUPT_CONTROLLER_2000000_HANDLE (&__metal_dt_interrupt_controller_2000000.controller)

/* From local_external_interrupts_0 */
#define __METAL_DT_SIFIVE_LOCAL_EXINTR0_HANDLE (&__metal_dt_local_external_interrupts_0.irc)

#define __METAL_DT_LOCAL_EXTERNAL_INTERRUPTS_0_HANDLE (&__metal_dt_local_external_interrupts_0.irc)

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
#endif /* COREIP_E21__METAL_H*/
#endif /* ! ASSEMBLY */
