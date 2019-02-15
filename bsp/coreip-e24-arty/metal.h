#ifndef ASSEMBLY

#ifndef COREIP_E24_ARTY__METAL_H
#define COREIP_E24_ARTY__METAL_H

#ifdef __METAL_MACHINE_MACROS

#define __METAL_CLIC_SUBINTERRUPTS 169

#ifndef __METAL_CLIC_SUBINTERRUPTS
#define __METAL_CLIC_SUBINTERRUPTS 0
#endif

#else /* ! __METAL_MACHINE_MACROS */

#define METAL_MAX_CLINT_INTERRUPTS 0

#define METAL_MAX_PLIC_INTERRUPTS 0

#define __METAL_INTERRUPT_CONTROLLER_2000000_INTERRUPTS 3

#define __METAL_CLIC_SUBINTERRUPTS 169

#define METAL_MAX_CLIC_INTERRUPTS 3

#define __METAL_LOCAL_EXTERNAL_INTERRUPTS_0_INTERRUPTS 127

#define METAL_MAX_LOCAL_EXT_INTERRUPTS 127

#define __METAL_GLOBAL_EXTERNAL_INTERRUPTS_INTERRUPTS 4

#define METAL_MAX_GLOBAL_EXT_INTERRUPTS 4

#define __METAL_GPIO_20002000_INTERRUPTS 16

#define METAL_MAX_GPIO_INTERRUPTS 16

#define __METAL_SERIAL_20000000_INTERRUPTS 1

#define METAL_MAX_UART_INTERRUPTS 1


#include <metal/drivers/fixed-clock.h>
#include <metal/drivers/riscv,cpu.h>
#include <metal/pmp.h>
#include <metal/drivers/sifive,clic0.h>
#include <metal/drivers/sifive,local-external-interrupts0.h>
#include <metal/drivers/sifive,global-external-interrupts0.h>
#include <metal/drivers/sifive,gpio0.h>
#include <metal/drivers/sifive,gpio-buttons.h>
#include <metal/drivers/sifive,gpio-leds.h>
#include <metal/drivers/sifive,gpio-switches.h>
#include <metal/drivers/sifive,spi0.h>
#include <metal/drivers/sifive,test0.h>
#include <metal/drivers/sifive,uart0.h>

/* From clock@0 */
asm (".weak __metal_dt_clock_0");
struct __metal_driver_fixed_clock __metal_dt_clock_0;

/* From cpu@0 */
asm (".weak __metal_dt_cpu_0");
struct __metal_driver_cpu __metal_dt_cpu_0;

/* From interrupt_controller */
asm (".weak __metal_dt_interrupt_controller");
struct __metal_driver_riscv_cpu_intc __metal_dt_interrupt_controller;

/* From interrupt_controller@2000000 */
asm (".weak __metal_dt_interrupt_controller_2000000");
struct __metal_driver_sifive_clic0 __metal_dt_interrupt_controller_2000000;

/* From local_external_interrupts_0 */
asm (".weak __metal_dt_local_external_interrupts_0");
struct __metal_driver_sifive_local_external_interrupts0 __metal_dt_local_external_interrupts_0;

/* From global_external_interrupts */
asm (".weak __metal_dt_global_external_interrupts");
struct __metal_driver_sifive_global_external_interrupts0 __metal_dt_global_external_interrupts;

/* From gpio@20002000 */
asm (".weak __metal_dt_gpio_20002000");
struct __metal_driver_sifive_gpio0 __metal_dt_gpio_20002000;

/* From button@0 */
asm (".weak __metal_dt_button_0");
struct __metal_driver_sifive_gpio_button __metal_dt_button_0;

/* From button@1 */
asm (".weak __metal_dt_button_1");
struct __metal_driver_sifive_gpio_button __metal_dt_button_1;

/* From button@2 */
asm (".weak __metal_dt_button_2");
struct __metal_driver_sifive_gpio_button __metal_dt_button_2;

/* From button@3 */
asm (".weak __metal_dt_button_3");
struct __metal_driver_sifive_gpio_button __metal_dt_button_3;

/* From led@0red */
asm (".weak __metal_dt_led_0red");
struct __metal_driver_sifive_gpio_led __metal_dt_led_0red;

/* From led@0green */
asm (".weak __metal_dt_led_0green");
struct __metal_driver_sifive_gpio_led __metal_dt_led_0green;

/* From led@0blue */
asm (".weak __metal_dt_led_0blue");
struct __metal_driver_sifive_gpio_led __metal_dt_led_0blue;

/* From switch@0 */
asm (".weak __metal_dt_switch_0");
struct __metal_driver_sifive_gpio_switch __metal_dt_switch_0;

/* From switch@1 */
asm (".weak __metal_dt_switch_1");
struct __metal_driver_sifive_gpio_switch __metal_dt_switch_1;

/* From switch@2 */
asm (".weak __metal_dt_switch_2");
struct __metal_driver_sifive_gpio_switch __metal_dt_switch_2;

/* From switch@3 */
asm (".weak __metal_dt_switch_3");
struct __metal_driver_sifive_gpio_switch __metal_dt_switch_3;

/* From spi@20004000 */
asm (".weak __metal_dt_spi_20004000");
struct __metal_driver_sifive_spi0 __metal_dt_spi_20004000;

/* From teststatus@4000 */
asm (".weak __metal_dt_teststatus_4000");
struct __metal_driver_sifive_test0 __metal_dt_teststatus_4000;

/* From serial@20000000 */
asm (".weak __metal_dt_serial_20000000");
struct __metal_driver_sifive_uart0 __metal_dt_serial_20000000;


/* From clock@0 */
struct __metal_driver_fixed_clock __metal_dt_clock_0 = {
    .vtable = &__metal_driver_vtable_fixed_clock,
    .clock.vtable = &__metal_driver_vtable_fixed_clock.clock,
    .rate = 32500000UL,
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
    .num_subinterrupts = 169UL,
    .num_intbits = 4UL,
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
    .interrupt_lines[0] = 26,
    .interrupt_lines[1] = 27,
    .interrupt_lines[2] = 28,
    .interrupt_lines[3] = 29,
    .interrupt_lines[4] = 30,
    .interrupt_lines[5] = 31,
    .interrupt_lines[6] = 32,
    .interrupt_lines[7] = 33,
    .interrupt_lines[8] = 34,
    .interrupt_lines[9] = 35,
    .interrupt_lines[10] = 36,
    .interrupt_lines[11] = 37,
    .interrupt_lines[12] = 38,
    .interrupt_lines[13] = 39,
    .interrupt_lines[14] = 40,
    .interrupt_lines[15] = 41,
    .interrupt_lines[16] = 42,
    .interrupt_lines[17] = 43,
    .interrupt_lines[18] = 44,
    .interrupt_lines[19] = 45,
    .interrupt_lines[20] = 46,
    .interrupt_lines[21] = 47,
    .interrupt_lines[22] = 48,
    .interrupt_lines[23] = 49,
    .interrupt_lines[24] = 50,
    .interrupt_lines[25] = 51,
    .interrupt_lines[26] = 52,
    .interrupt_lines[27] = 53,
    .interrupt_lines[28] = 54,
    .interrupt_lines[29] = 55,
    .interrupt_lines[30] = 56,
    .interrupt_lines[31] = 57,
    .interrupt_lines[32] = 58,
    .interrupt_lines[33] = 59,
    .interrupt_lines[34] = 60,
    .interrupt_lines[35] = 61,
    .interrupt_lines[36] = 62,
    .interrupt_lines[37] = 63,
    .interrupt_lines[38] = 64,
    .interrupt_lines[39] = 65,
    .interrupt_lines[40] = 66,
    .interrupt_lines[41] = 67,
    .interrupt_lines[42] = 68,
    .interrupt_lines[43] = 69,
    .interrupt_lines[44] = 70,
    .interrupt_lines[45] = 71,
    .interrupt_lines[46] = 72,
    .interrupt_lines[47] = 73,
    .interrupt_lines[48] = 74,
    .interrupt_lines[49] = 75,
    .interrupt_lines[50] = 76,
    .interrupt_lines[51] = 77,
    .interrupt_lines[52] = 78,
    .interrupt_lines[53] = 79,
    .interrupt_lines[54] = 80,
    .interrupt_lines[55] = 81,
    .interrupt_lines[56] = 82,
    .interrupt_lines[57] = 83,
    .interrupt_lines[58] = 84,
    .interrupt_lines[59] = 85,
    .interrupt_lines[60] = 86,
    .interrupt_lines[61] = 87,
    .interrupt_lines[62] = 88,
    .interrupt_lines[63] = 89,
    .interrupt_lines[64] = 90,
    .interrupt_lines[65] = 91,
    .interrupt_lines[66] = 92,
    .interrupt_lines[67] = 93,
    .interrupt_lines[68] = 94,
    .interrupt_lines[69] = 95,
    .interrupt_lines[70] = 96,
    .interrupt_lines[71] = 97,
    .interrupt_lines[72] = 98,
    .interrupt_lines[73] = 99,
    .interrupt_lines[74] = 100,
    .interrupt_lines[75] = 101,
    .interrupt_lines[76] = 102,
    .interrupt_lines[77] = 103,
    .interrupt_lines[78] = 104,
    .interrupt_lines[79] = 105,
    .interrupt_lines[80] = 106,
    .interrupt_lines[81] = 107,
    .interrupt_lines[82] = 108,
    .interrupt_lines[83] = 109,
    .interrupt_lines[84] = 110,
    .interrupt_lines[85] = 111,
    .interrupt_lines[86] = 112,
    .interrupt_lines[87] = 113,
    .interrupt_lines[88] = 114,
    .interrupt_lines[89] = 115,
    .interrupt_lines[90] = 116,
    .interrupt_lines[91] = 117,
    .interrupt_lines[92] = 118,
    .interrupt_lines[93] = 119,
    .interrupt_lines[94] = 120,
    .interrupt_lines[95] = 121,
    .interrupt_lines[96] = 122,
    .interrupt_lines[97] = 123,
    .interrupt_lines[98] = 124,
    .interrupt_lines[99] = 125,
    .interrupt_lines[100] = 126,
    .interrupt_lines[101] = 127,
    .interrupt_lines[102] = 128,
    .interrupt_lines[103] = 129,
    .interrupt_lines[104] = 130,
    .interrupt_lines[105] = 131,
    .interrupt_lines[106] = 132,
    .interrupt_lines[107] = 133,
    .interrupt_lines[108] = 134,
    .interrupt_lines[109] = 135,
    .interrupt_lines[110] = 136,
    .interrupt_lines[111] = 137,
    .interrupt_lines[112] = 138,
    .interrupt_lines[113] = 139,
    .interrupt_lines[114] = 140,
    .interrupt_lines[115] = 141,
    .interrupt_lines[116] = 142,
    .interrupt_lines[117] = 143,
    .interrupt_lines[118] = 144,
    .interrupt_lines[119] = 145,
    .interrupt_lines[120] = 146,
    .interrupt_lines[121] = 147,
    .interrupt_lines[122] = 148,
    .interrupt_lines[123] = 149,
    .interrupt_lines[124] = 150,
    .interrupt_lines[125] = 151,
    .interrupt_lines[126] = 152,
};

/* From global_external_interrupts */
struct __metal_driver_sifive_global_external_interrupts0 __metal_dt_global_external_interrupts = {
    .vtable = &__metal_driver_vtable_sifive_global_external_interrupts0,
    .irc.vtable = &__metal_driver_vtable_sifive_global_external_interrupts0.global0_vtable,
    .init_done = 0,
/* From interrupt_controller@2000000 */
    .interrupt_parent = &__metal_dt_interrupt_controller_2000000.controller,
    .num_interrupts = METAL_MAX_GLOBAL_EXT_INTERRUPTS,
    .interrupt_lines[0] = 22,
    .interrupt_lines[1] = 23,
    .interrupt_lines[2] = 24,
    .interrupt_lines[3] = 25,
};

/* From gpio@20002000 */
struct __metal_driver_sifive_gpio0 __metal_dt_gpio_20002000 = {
    .vtable = &__metal_driver_vtable_sifive_gpio0,
    .base = 536879104UL,
    .size = 4096UL,
/* From interrupt_controller@2000000 */
    .interrupt_parent = &__metal_dt_interrupt_controller_2000000.controller,
    .num_interrupts = METAL_MAX_GPIO_INTERRUPTS,
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
};

/* From button@0 */
struct __metal_driver_sifive_gpio_button __metal_dt_button_0 = {
    .vtable = &__metal_driver_vtable_sifive_button,
    .button.vtable = &__metal_driver_vtable_sifive_button.button_vtable,
/* From gpio@20002000 */
    .gpio = &__metal_dt_gpio_20002000,
    .pin = 4UL,
/* From local_external_interrupts_0 */
    .interrupt_parent = &__metal_dt_local_external_interrupts_0.irc,
    .interrupt_line = 9UL,
    .label = "BTN0",
};

/* From button@1 */
struct __metal_driver_sifive_gpio_button __metal_dt_button_1 = {
    .vtable = &__metal_driver_vtable_sifive_button,
    .button.vtable = &__metal_driver_vtable_sifive_button.button_vtable,
/* From gpio@20002000 */
    .gpio = &__metal_dt_gpio_20002000,
    .pin = 5UL,
/* From local_external_interrupts_0 */
    .interrupt_parent = &__metal_dt_local_external_interrupts_0.irc,
    .interrupt_line = 10UL,
    .label = "BTN1",
};

/* From button@2 */
struct __metal_driver_sifive_gpio_button __metal_dt_button_2 = {
    .vtable = &__metal_driver_vtable_sifive_button,
    .button.vtable = &__metal_driver_vtable_sifive_button.button_vtable,
/* From gpio@20002000 */
    .gpio = &__metal_dt_gpio_20002000,
    .pin = 6UL,
/* From local_external_interrupts_0 */
    .interrupt_parent = &__metal_dt_local_external_interrupts_0.irc,
    .interrupt_line = 11UL,
    .label = "BTN2",
};

/* From button@3 */
struct __metal_driver_sifive_gpio_button __metal_dt_button_3 = {
    .vtable = &__metal_driver_vtable_sifive_button,
    .button.vtable = &__metal_driver_vtable_sifive_button.button_vtable,
/* From gpio@20002000 */
    .gpio = &__metal_dt_gpio_20002000,
    .pin = 7UL,
/* From local_external_interrupts_0 */
    .interrupt_parent = &__metal_dt_local_external_interrupts_0.irc,
    .interrupt_line = 12UL,
    .label = "BTN3",
};

/* From led@0red */
struct __metal_driver_sifive_gpio_led __metal_dt_led_0red = {
    .vtable = &__metal_driver_vtable_sifive_led,
    .led.vtable = &__metal_driver_vtable_sifive_led.led_vtable,
/* From gpio@20002000 */
    .gpio = &__metal_dt_gpio_20002000,
    .pin = 0UL,
    .label = "LD0red",
};

/* From led@0green */
struct __metal_driver_sifive_gpio_led __metal_dt_led_0green = {
    .vtable = &__metal_driver_vtable_sifive_led,
    .led.vtable = &__metal_driver_vtable_sifive_led.led_vtable,
/* From gpio@20002000 */
    .gpio = &__metal_dt_gpio_20002000,
    .pin = 1UL,
    .label = "LD0green",
};

/* From led@0blue */
struct __metal_driver_sifive_gpio_led __metal_dt_led_0blue = {
    .vtable = &__metal_driver_vtable_sifive_led,
    .led.vtable = &__metal_driver_vtable_sifive_led.led_vtable,
/* From gpio@20002000 */
    .gpio = &__metal_dt_gpio_20002000,
    .pin = 2UL,
    .label = "LD0blue",
};

/* From switch@0 */
struct __metal_driver_sifive_gpio_switch __metal_dt_switch_0 = {
    .vtable = &__metal_driver_vtable_sifive_switch,
    .flip.vtable = &__metal_driver_vtable_sifive_switch.switch_vtable,
    .gpio = NULL,
    .pin = 0,
/* From global_external_interrupts */
    .interrupt_parent = &__metal_dt_global_external_interrupts.irc,
    .interrupt_line = 0UL,
    .label = "SW0",
};

/* From switch@1 */
struct __metal_driver_sifive_gpio_switch __metal_dt_switch_1 = {
    .vtable = &__metal_driver_vtable_sifive_switch,
    .flip.vtable = &__metal_driver_vtable_sifive_switch.switch_vtable,
    .gpio = NULL,
    .pin = 0,
/* From global_external_interrupts */
    .interrupt_parent = &__metal_dt_global_external_interrupts.irc,
    .interrupt_line = 1UL,
    .label = "SW1",
};

/* From switch@2 */
struct __metal_driver_sifive_gpio_switch __metal_dt_switch_2 = {
    .vtable = &__metal_driver_vtable_sifive_switch,
    .flip.vtable = &__metal_driver_vtable_sifive_switch.switch_vtable,
    .gpio = NULL,
    .pin = 0,
/* From global_external_interrupts */
    .interrupt_parent = &__metal_dt_global_external_interrupts.irc,
    .interrupt_line = 2UL,
    .label = "SW2",
};

/* From switch@3 */
struct __metal_driver_sifive_gpio_switch __metal_dt_switch_3 = {
    .vtable = &__metal_driver_vtable_sifive_switch,
    .flip.vtable = &__metal_driver_vtable_sifive_switch.switch_vtable,
    .gpio = NULL,
    .pin = 0,
/* From local_external_interrupts_0 */
    .interrupt_parent = &__metal_dt_local_external_interrupts_0.irc,
    .interrupt_line = 8UL,
    .label = "SW3",
};

/* From spi@20004000 */
struct __metal_driver_sifive_spi0 __metal_dt_spi_20004000 = {
    .vtable = &__metal_driver_vtable_sifive_spi0,
    .spi.vtable = &__metal_driver_vtable_sifive_spi0.spi,
    .control_base = 536887296UL,
    .control_size = 4096UL,
    .clock = NULL,
    .pinmux = NULL,
};

/* From teststatus@4000 */
struct __metal_driver_sifive_test0 __metal_dt_teststatus_4000 = {
    .vtable = &__metal_driver_vtable_sifive_test0,
    .shutdown.vtable = &__metal_driver_vtable_sifive_test0.shutdown,
    .base = 16384UL,
    .size = 4096UL,
};

/* From serial@20000000 */
struct __metal_driver_sifive_uart0 __metal_dt_serial_20000000 = {
    .vtable = &__metal_driver_vtable_sifive_uart0,
    .uart.vtable = &__metal_driver_vtable_sifive_uart0.uart,
    .control_base = 536870912UL,
    .control_size = 4096UL,
/* From clock@0 */
    .clock = &__metal_dt_clock_0.clock,
    .pinmux = NULL,
/* From interrupt_controller@2000000 */
    .interrupt_parent = &__metal_dt_interrupt_controller_2000000.controller,
    .num_interrupts = METAL_MAX_UART_INTERRUPTS,
    .interrupt_line = 16UL,
};


/* From serial@20000000 */
#define __METAL_DT_STDOUT_UART_HANDLE (&__metal_dt_serial_20000000.uart)

#define __METAL_DT_SERIAL_20000000_HANDLE (&__metal_dt_serial_20000000.uart)

#define __METAL_DT_STDOUT_UART_BAUD 115200

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

/* From interrupt_controller@2000000 */
#define __METAL_DT_SIFIVE_CLIC0_HANDLE (&__metal_dt_interrupt_controller_2000000.controller)

#define __METAL_DT_INTERRUPT_CONTROLLER_2000000_HANDLE (&__metal_dt_interrupt_controller_2000000.controller)

/* From local_external_interrupts_0 */
#define __METAL_DT_SIFIVE_LOCAL_EXINTR0_HANDLE (&__metal_dt_local_external_interrupts_0.irc)

#define __METAL_DT_LOCAL_EXTERNAL_INTERRUPTS_0_HANDLE (&__metal_dt_local_external_interrupts_0.irc)

/* From global_external_interrupts */
#define __METAL_DT_SIFIVE_GLOBAL_EXINTR0_HANDLE (&__metal_dt_global_external_interrupts.irc)

#define __METAL_DT_GLOBAL_EXTERNAL_INTERRUPTS_HANDLE (&__metal_dt_global_external_interrupts.irc)

#define __METAL_DT_MAX_BUTTONS 4

asm (".weak __metal_button_table");
struct __metal_driver_sifive_gpio_button *__metal_button_table[] = {
					&__metal_dt_button_0,
					&__metal_dt_button_1,
					&__metal_dt_button_2,
					&__metal_dt_button_3};

#define __METAL_DT_MAX_LEDS 3

asm (".weak __metal_led_table");
struct __metal_driver_sifive_gpio_led *__metal_led_table[] = {
					&__metal_dt_led_0red,
					&__metal_dt_led_0green,
					&__metal_dt_led_0blue};

#define __METAL_DT_MAX_SWITCHES 4

asm (".weak __metal_switch_table");
struct __metal_driver_sifive_gpio_switch *__metal_switch_table[] = {
					&__metal_dt_switch_0,
					&__metal_dt_switch_1,
					&__metal_dt_switch_2,
					&__metal_dt_switch_3};

#define __METAL_DT_MAX_SPIS 1

asm (".weak __metal_spi_table");
struct __metal_driver_sifive_spi0 *__metal_spi_table[] = {
					&__metal_dt_spi_20004000};

/* From teststatus@4000 */
#define __METAL_DT_SHUTDOWN_HANDLE (&__metal_dt_teststatus_4000.shutdown)

#define __METAL_DT_TESTSTATUS_4000_HANDLE (&__metal_dt_teststatus_4000.shutdown)


#endif /* ! __METAL_MACHINE_MACROS */
#endif /* COREIP_E24_ARTY__METAL_H*/
#endif /* ! ASSEMBLY */
