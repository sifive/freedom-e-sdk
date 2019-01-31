#ifndef ASSEMBLY

#ifndef COREIP_S51__MEE_H
#define COREIP_S51__MEE_H

#ifdef __MEE_MACHINE_MACROS
#endif

#ifndef __MEE_MACHINE_MACROS
#define __MEE_CLINT_2000000_INTERRUPTS 		2
#define MEE_MAX_CLINT_INTERRUPTS	 __MEE_CLINT_2000000_INTERRUPTS

#define __MEE_INTERRUPT_CONTROLLER_C000000_INTERRUPTS 		1
#define MEE_MAX_PLIC_INTERRUPTS	 __MEE_INTERRUPT_CONTROLLER_C000000_INTERRUPTS

#define __MEE_LOCAL_EXTERNAL_INTERRUPTS_0_INTERRUPTS 		16
#define MEE_MAX_LOCAL_EXT_INTERRUPTS	 __MEE_LOCAL_EXTERNAL_INTERRUPTS_0_INTERRUPTS

#define __MEE_GLOBAL_EXTERNAL_INTERRUPTS_INTERRUPTS 		255
#define MEE_MAX_GLOBAL_EXT_INTERRUPTS	 __MEE_GLOBAL_EXTERNAL_INTERRUPTS_INTERRUPTS

#include <mee/drivers/riscv,cpu.h>
#include <mee/drivers/riscv,clint0.h>
#include <mee/drivers/riscv,plic0.h>
#include <mee/pmp.h>
#include <mee/drivers/sifive,local-external-interrupts0.h>
#include <mee/drivers/sifive,global-external-interrupts0.h>
#include <mee/drivers/sifive,test0.h>
/* From cpu@0 */
asm (".weak __mee_dt_cpu_0");
struct __mee_driver_cpu __mee_dt_cpu_0;

/* From clint@2000000 */
asm (".weak __mee_dt_clint_2000000");
struct __mee_driver_riscv_clint0 __mee_dt_clint_2000000;

/* From interrupt_controller@c000000 */
asm (".weak __mee_dt_interrupt_controller_c000000");
struct __mee_driver_riscv_plic0 __mee_dt_interrupt_controller_c000000;

/* From interrupt_controller */
asm (".weak __mee_dt_interrupt_controller");
struct __mee_driver_riscv_cpu_intc __mee_dt_interrupt_controller;

/* From local_external_interrupts_0 */
asm (".weak __mee_dt_local_external_interrupts_0");
struct __mee_driver_sifive_local_external_interrupts0 __mee_dt_local_external_interrupts_0;

/* From global_external_interrupts */
asm (".weak __mee_dt_global_external_interrupts");
struct __mee_driver_sifive_global_external_interrupts0 __mee_dt_global_external_interrupts;

asm (".weak __mee_dt_pmp_0");
struct mee_pmp __mee_dt_pmp_0;

/* From teststatus@4000 */
asm (".weak __mee_dt_teststatus_4000");
struct __mee_driver_sifive_test0 __mee_dt_teststatus_4000;

/* From cpu@0 */
struct __mee_driver_cpu __mee_dt_cpu_0 = {
    .vtable = &__mee_driver_vtable_cpu,
    .cpu.vtable = &__mee_driver_vtable_cpu.cpu_vtable,
    .timebase = 1000000UL,
    .interrupt_controller = &__mee_dt_interrupt_controller.controller,
};

/* From cpu@0 */
#define __MEE_DT_RISCV_CPU_HANDLE (&__mee_dt_cpu_0.cpu)

#define __MEE_DT_CPU_0_HANDLE (&__mee_dt_cpu_0.cpu)

/* From interrupt_controller */
struct __mee_driver_riscv_cpu_intc __mee_dt_interrupt_controller = {
    .vtable = &__mee_driver_vtable_riscv_cpu_intc,
    .controller.vtable = &__mee_driver_vtable_riscv_cpu_intc.controller_vtable,
    .init_done = 0,
    .interrupt_controller = 1,
};

/* From interrupt_controller */
#define __MEE_DT_RISCV_CPU_INTC_HANDLE (&__mee_dt_interrupt_controller.controller)

#define __MEE_DT_INTERRUPT_CONTROLLER_HANDLE (&__mee_dt_interrupt_controller.controller)

/* From clint@2000000 */
struct __mee_driver_riscv_clint0 __mee_dt_clint_2000000 = {
    .vtable = &__mee_driver_vtable_riscv_clint0,
    .controller.vtable = &__mee_driver_vtable_riscv_clint0.clint_vtable,
    .control_base = 33554432UL,
    .control_size = 65536UL,
    .init_done = 0,
    .num_interrupts = MEE_MAX_CLINT_INTERRUPTS,
    .interrupt_parent = &__mee_dt_interrupt_controller.controller,
    .interrupt_lines[0] = 3,
    .interrupt_lines[1] = 7,
};

/* From clint@2000000 */
#define __MEE_DT_RISCV_CLINT0_HANDLE (&__mee_dt_clint_2000000.controller)

#define __MEE_DT_CLINT_2000000_HANDLE (&__mee_dt_clint_2000000.controller)

/* From local_external_interrupts_0 */
struct __mee_driver_sifive_local_external_interrupts0 __mee_dt_local_external_interrupts_0 = {
    .vtable = &__mee_driver_vtable_sifive_local_external_interrupts0,
    .irc.vtable = &__mee_driver_vtable_sifive_local_external_interrupts0.local0_vtable,
    .init_done = 0,
/* From interrupt_controller */
    .interrupt_parent = &__mee_dt_interrupt_controller.controller,
    .num_interrupts = MEE_MAX_LOCAL_EXT_INTERRUPTS,
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

/* From local_external_interrupts_0 */
#define __MEE_DT_SIFIVE_LOCAL_EXINTR0_HANDLE (&__mee_dt_local_external_interrupts_0.irc)

#define __MEE_DT_LOCAL_EXTERNAL_INTERRUPTS_0_HANDLE (&__mee_dt_local_external_interrupts_0.irc)

/* From interrupt_controller@c000000 */
struct __mee_driver_riscv_plic0 __mee_dt_interrupt_controller_c000000 = {
    .vtable = &__mee_driver_vtable_riscv_plic0,
    .controller.vtable = &__mee_driver_vtable_riscv_plic0.plic_vtable,
    .init_done = 0,
/* From interrupt_controller */
    .interrupt_parent = &__mee_dt_interrupt_controller.controller,
    .interrupt_line = 11UL,
    .control_base = 201326592UL,
    .control_size = 67108864UL,
    .max_priority = 7UL,
    .num_interrupts = 255UL,
    .interrupt_controller = 1,
};

/* From interrupt_controller@c000000 */
#define __MEE_DT_RISCV_PLIC0_HANDLE (&__mee_dt_interrupt_controller_c000000.controller)

#define __MEE_DT_INTERRUPT_CONTROLLER_C000000_HANDLE (&__mee_dt_interrupt_controller_c000000.controller)

/* From global_external_interrupts */
struct __mee_driver_sifive_global_external_interrupts0 __mee_dt_global_external_interrupts = {
    .vtable = &__mee_driver_vtable_sifive_global_external_interrupts0,
    .irc.vtable = &__mee_driver_vtable_sifive_global_external_interrupts0.global0_vtable,
    .init_done = 0,
/* From interrupt_controller@c000000 */
    .interrupt_parent = &__mee_dt_interrupt_controller_c000000.controller,
    .num_interrupts = MEE_MAX_GLOBAL_EXT_INTERRUPTS,
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
    .interrupt_lines[127] = 128,
    .interrupt_lines[128] = 129,
    .interrupt_lines[129] = 130,
    .interrupt_lines[130] = 131,
    .interrupt_lines[131] = 132,
    .interrupt_lines[132] = 133,
    .interrupt_lines[133] = 134,
    .interrupt_lines[134] = 135,
    .interrupt_lines[135] = 136,
    .interrupt_lines[136] = 137,
    .interrupt_lines[137] = 138,
    .interrupt_lines[138] = 139,
    .interrupt_lines[139] = 140,
    .interrupt_lines[140] = 141,
    .interrupt_lines[141] = 142,
    .interrupt_lines[142] = 143,
    .interrupt_lines[143] = 144,
    .interrupt_lines[144] = 145,
    .interrupt_lines[145] = 146,
    .interrupt_lines[146] = 147,
    .interrupt_lines[147] = 148,
    .interrupt_lines[148] = 149,
    .interrupt_lines[149] = 150,
    .interrupt_lines[150] = 151,
    .interrupt_lines[151] = 152,
    .interrupt_lines[152] = 153,
    .interrupt_lines[153] = 154,
    .interrupt_lines[154] = 155,
    .interrupt_lines[155] = 156,
    .interrupt_lines[156] = 157,
    .interrupt_lines[157] = 158,
    .interrupt_lines[158] = 159,
    .interrupt_lines[159] = 160,
    .interrupt_lines[160] = 161,
    .interrupt_lines[161] = 162,
    .interrupt_lines[162] = 163,
    .interrupt_lines[163] = 164,
    .interrupt_lines[164] = 165,
    .interrupt_lines[165] = 166,
    .interrupt_lines[166] = 167,
    .interrupt_lines[167] = 168,
    .interrupt_lines[168] = 169,
    .interrupt_lines[169] = 170,
    .interrupt_lines[170] = 171,
    .interrupt_lines[171] = 172,
    .interrupt_lines[172] = 173,
    .interrupt_lines[173] = 174,
    .interrupt_lines[174] = 175,
    .interrupt_lines[175] = 176,
    .interrupt_lines[176] = 177,
    .interrupt_lines[177] = 178,
    .interrupt_lines[178] = 179,
    .interrupt_lines[179] = 180,
    .interrupt_lines[180] = 181,
    .interrupt_lines[181] = 182,
    .interrupt_lines[182] = 183,
    .interrupt_lines[183] = 184,
    .interrupt_lines[184] = 185,
    .interrupt_lines[185] = 186,
    .interrupt_lines[186] = 187,
    .interrupt_lines[187] = 188,
    .interrupt_lines[188] = 189,
    .interrupt_lines[189] = 190,
    .interrupt_lines[190] = 191,
    .interrupt_lines[191] = 192,
    .interrupt_lines[192] = 193,
    .interrupt_lines[193] = 194,
    .interrupt_lines[194] = 195,
    .interrupt_lines[195] = 196,
    .interrupt_lines[196] = 197,
    .interrupt_lines[197] = 198,
    .interrupt_lines[198] = 199,
    .interrupt_lines[199] = 200,
    .interrupt_lines[200] = 201,
    .interrupt_lines[201] = 202,
    .interrupt_lines[202] = 203,
    .interrupt_lines[203] = 204,
    .interrupt_lines[204] = 205,
    .interrupt_lines[205] = 206,
    .interrupt_lines[206] = 207,
    .interrupt_lines[207] = 208,
    .interrupt_lines[208] = 209,
    .interrupt_lines[209] = 210,
    .interrupt_lines[210] = 211,
    .interrupt_lines[211] = 212,
    .interrupt_lines[212] = 213,
    .interrupt_lines[213] = 214,
    .interrupt_lines[214] = 215,
    .interrupt_lines[215] = 216,
    .interrupt_lines[216] = 217,
    .interrupt_lines[217] = 218,
    .interrupt_lines[218] = 219,
    .interrupt_lines[219] = 220,
    .interrupt_lines[220] = 221,
    .interrupt_lines[221] = 222,
    .interrupt_lines[222] = 223,
    .interrupt_lines[223] = 224,
    .interrupt_lines[224] = 225,
    .interrupt_lines[225] = 226,
    .interrupt_lines[226] = 227,
    .interrupt_lines[227] = 228,
    .interrupt_lines[228] = 229,
    .interrupt_lines[229] = 230,
    .interrupt_lines[230] = 231,
    .interrupt_lines[231] = 232,
    .interrupt_lines[232] = 233,
    .interrupt_lines[233] = 234,
    .interrupt_lines[234] = 235,
    .interrupt_lines[235] = 236,
    .interrupt_lines[236] = 237,
    .interrupt_lines[237] = 238,
    .interrupt_lines[238] = 239,
    .interrupt_lines[239] = 240,
    .interrupt_lines[240] = 241,
    .interrupt_lines[241] = 242,
    .interrupt_lines[242] = 243,
    .interrupt_lines[243] = 244,
    .interrupt_lines[244] = 245,
    .interrupt_lines[245] = 246,
    .interrupt_lines[246] = 247,
    .interrupt_lines[247] = 248,
    .interrupt_lines[248] = 249,
    .interrupt_lines[249] = 250,
    .interrupt_lines[250] = 251,
    .interrupt_lines[251] = 252,
    .interrupt_lines[252] = 253,
    .interrupt_lines[253] = 254,
    .interrupt_lines[254] = 255,
};

/* From global_external_interrupts */
#define __MEE_DT_SIFIVE_GLOBAL_EXINTR0_HANDLE (&__mee_dt_global_external_interrupts.irc)

#define __MEE_DT_GLOBAL_EXTERNAL_INTERRUPTS_HANDLE (&__mee_dt_global_external_interrupts.irc)

/* From pmp@0 */
struct mee_pmp __mee_dt_pmp_0 = {
    .num_regions = 8UL,
};

#define __MEE_DT_PMP_HANDLE (&__mee_dt_pmp_0)

/* From teststatus@4000 */
struct __mee_driver_sifive_test0 __mee_dt_teststatus_4000 = {
    .vtable = &__mee_driver_vtable_sifive_test0,
    .shutdown.vtable = &__mee_driver_vtable_sifive_test0.shutdown,
    .base = 16384UL,
    .size = 4096UL,
};

/* From teststatus@4000 */
#define __MEE_DT_SHUTDOWN_HANDLE (&__mee_dt_teststatus_4000.shutdown)

#define __MEE_DT_TESTSTATUS_4000_HANDLE (&__mee_dt_teststatus_4000.shutdown)

#define __MEE_DT_MAX_HARTS 1

asm (".weak __mee_cpu_table");
struct __mee_driver_cpu *__mee_cpu_table[] = {
					&__mee_dt_cpu_0};

#define __MEE_DT_MAX_LEDS 0

asm (".weak __mee_led_table");
struct __mee_driver_sifive_gpio_led *__mee_led_table[] = {
					NULL };
#define __MEE_DT_MAX_BUTTONS 0

asm (".weak __mee_button_table");
struct __mee_driver_sifive_gpio_button *__mee_button_table[] = {
					NULL };
#define __MEE_DT_MAX_SWITCHES 0

asm (".weak __mee_switch_table");
struct __mee_driver_sifive_gpio_switch *__mee_switch_table[] = {
					NULL };
#endif

#endif /*MEE__MACHINE__COREIP_S51__MEE_H*/

#endif/*ASSEMBLY*/
