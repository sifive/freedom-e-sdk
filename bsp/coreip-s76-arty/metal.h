#ifndef ASSEMBLY

#ifndef COREIP_S76_ARTY__METAL_H
#define COREIP_S76_ARTY__METAL_H

#include <metal/machine/platform.h>

#ifdef __METAL_MACHINE_MACROS

#define __METAL_CLINT_NUM_PARENTS 2

#ifndef __METAL_CLINT_NUM_PARENTS
#define __METAL_CLINT_NUM_PARENTS 0
#endif
#define __METAL_PLIC_SUBINTERRUPTS 31

#define __METAL_PLIC_NUM_PARENTS 1

#ifndef __METAL_PLIC_SUBINTERRUPTS
#define __METAL_PLIC_SUBINTERRUPTS 0
#endif
#ifndef __METAL_PLIC_NUM_PARENTS
#define __METAL_PLIC_NUM_PARENTS 0
#endif
#ifndef __METAL_CLIC_SUBINTERRUPTS
#define __METAL_CLIC_SUBINTERRUPTS 0
#endif

#else /* ! __METAL_MACHINE_MACROS */

#define __METAL_CLINT_2000000_INTERRUPTS 2

#define METAL_MAX_CLINT_INTERRUPTS 2

#define __METAL_CLINT_NUM_PARENTS 2

#define __METAL_INTERRUPT_CONTROLLER_C000000_INTERRUPTS 1

#define __METAL_PLIC_SUBINTERRUPTS 31

#define METAL_MAX_PLIC_INTERRUPTS 1

#define __METAL_PLIC_NUM_PARENTS 1

#define __METAL_CLIC_SUBINTERRUPTS 0
#define METAL_MAX_CLIC_INTERRUPTS 0

#define METAL_MAX_LOCAL_EXT_INTERRUPTS 0

#define __METAL_GLOBAL_EXTERNAL_INTERRUPTS_INTERRUPTS 4

#define METAL_MAX_GLOBAL_EXT_INTERRUPTS 4

#define __METAL_GPIO_10060000_INTERRUPTS 4

#define __METAL_GPIO_20002000_INTERRUPTS 16

#define METAL_MAX_GPIO_INTERRUPTS 16

#define __METAL_SERIAL_20000000_INTERRUPTS 1

#define METAL_MAX_UART_INTERRUPTS 1


#include <metal/drivers/fixed-clock.h>
#include <metal/memory.h>
#include <metal/drivers/riscv,clint0.h>
#include <metal/drivers/riscv,cpu.h>
#include <metal/drivers/riscv,plic0.h>
#include <metal/pmp.h>
#include <metal/drivers/sifive,global-external-interrupts0.h>
#include <metal/drivers/sifive,gpio0.h>
#include <metal/drivers/sifive,gpio-buttons.h>
#include <metal/drivers/sifive,gpio-leds.h>
#include <metal/drivers/sifive,gpio-switches.h>
#include <metal/drivers/sifive,spi0.h>
#include <metal/drivers/sifive,test0.h>
#include <metal/drivers/sifive,uart0.h>

/* From tlclk */
asm (".weak __metal_dt_tlclk");
struct __metal_driver_fixed_clock __metal_dt_tlclk;

asm (".weak __metal_dt_mem_memory_80000000");
struct metal_memory __metal_dt_mem_memory_80000000;

asm (".weak __metal_dt_mem_spi_20004000");
struct metal_memory __metal_dt_mem_spi_20004000;

/* From clint@2000000 */
asm (".weak __metal_dt_clint_2000000");
struct __metal_driver_riscv_clint0 __metal_dt_clint_2000000;

/* From cpu@0 */
asm (".weak __metal_dt_cpu_0");
struct __metal_driver_cpu __metal_dt_cpu_0;

asm (".weak __metal_dt_cpu_0_interrupt_controller");
struct __metal_driver_riscv_cpu_intc __metal_dt_cpu_0_interrupt_controller;

/* From interrupt_controller@c000000 */
asm (".weak __metal_dt_interrupt_controller_c000000");
struct __metal_driver_riscv_plic0 __metal_dt_interrupt_controller_c000000;

asm (".weak __metal_dt_pmp_0");
struct metal_pmp __metal_dt_pmp_0;

/* From global_external_interrupts */
asm (".weak __metal_dt_global_external_interrupts");
struct __metal_driver_sifive_global_external_interrupts0 __metal_dt_global_external_interrupts;

/* From gpio@10060000 */
asm (".weak __metal_dt_gpio_10060000");
struct __metal_driver_sifive_gpio0 __metal_dt_gpio_10060000;

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


/* From tlclk */
struct __metal_driver_fixed_clock __metal_dt_tlclk = {
    .vtable = &__metal_driver_vtable_fixed_clock,
    .clock.vtable = &__metal_driver_vtable_fixed_clock.clock,
    .rate = METAL_FIXED_CLOCK__CLOCK_FREQUENCY,
};

struct metal_memory __metal_dt_mem_memory_80000000 = {
    ._base_address = 2147483648UL,
    ._size = 268435456UL,
    ._attrs = {
        .R = 1,
        .W = 1,
        .X = 1,
        .C = 1,
        .A = 1},
};

struct metal_memory __metal_dt_mem_spi_20004000 = {
    ._base_address = 1073741824UL,
    ._size = 536870912UL,
    ._attrs = {
        .R = 1,
        .W = 1,
        .X = 1,
        .C = 1,
        .A = 1},
};

/* From clint@2000000 */
struct __metal_driver_riscv_clint0 __metal_dt_clint_2000000 = {
    .vtable = &__metal_driver_vtable_riscv_clint0,
    .controller.vtable = &__metal_driver_vtable_riscv_clint0.clint_vtable,
    .control_base = METAL_RISCV_CLINT0_2000000_BASE_ADDRESS,
    .control_size = METAL_RISCV_CLINT0_2000000_SIZE,
    .init_done = 0,
    .num_interrupts = METAL_MAX_CLINT_INTERRUPTS,
    .interrupt_parents[0] = &__metal_dt_cpu_0_interrupt_controller.controller,
    .interrupt_lines[0] = 3,
    .interrupt_parents[1] = &__metal_dt_cpu_0_interrupt_controller.controller,
    .interrupt_lines[1] = 7,
};

/* From cpu@0 */
struct __metal_driver_cpu __metal_dt_cpu_0 = {
    .vtable = &__metal_driver_vtable_cpu,
    .cpu.vtable = &__metal_driver_vtable_cpu.cpu_vtable,
    .timebase = 65000000UL,
    .interrupt_controller = &__metal_dt_cpu_0_interrupt_controller.controller,
};

/* From interrupt_controller */
struct __metal_driver_riscv_cpu_intc __metal_dt_cpu_0_interrupt_controller = {
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
    .interrupt_parents[0] = &__metal_dt_cpu_0_interrupt_controller.controller,
    .interrupt_lines[0] = 11,
    .control_base = METAL_RISCV_PLIC0_C000000_BASE_ADDRESS,
    .control_size = METAL_RISCV_PLIC0_C000000_SIZE,
    .max_priority = METAL_RISCV_PLIC0_C000000_RISCV_MAX_PRIORITY,
    .num_interrupts = METAL_RISCV_PLIC0_C000000_RISCV_NDEV,
    .interrupt_controller = 1,
};

/* From pmp@0 */
struct metal_pmp __metal_dt_pmp_0 = {
    .num_regions = METAL_RISCV_PMP_0_NUM_REGIONS,
};

/* From global_external_interrupts */
struct __metal_driver_sifive_global_external_interrupts0 __metal_dt_global_external_interrupts = {
    .vtable = &__metal_driver_vtable_sifive_global_external_interrupts0,
    .irc.vtable = &__metal_driver_vtable_sifive_global_external_interrupts0.global0_vtable,
    .init_done = 0,
/* From interrupt_controller@c000000 */
    .interrupt_parent = &__metal_dt_interrupt_controller_c000000.controller,
    .num_interrupts = METAL_MAX_GLOBAL_EXT_INTERRUPTS,
    .interrupt_lines[0] = 21,
    .interrupt_lines[1] = 22,
    .interrupt_lines[2] = 23,
    .interrupt_lines[3] = 24,
};

/* From gpio@10060000 */
struct __metal_driver_sifive_gpio0 __metal_dt_gpio_10060000 = {
    .vtable = &__metal_driver_vtable_sifive_gpio0,
    .gpio.vtable = &__metal_driver_vtable_sifive_gpio0.gpio,
    .base = METAL_SIFIVE_GPIO0_10060000_BASE_ADDRESS,
    .size = METAL_SIFIVE_GPIO0_10060000_SIZE,
/* From interrupt_controller@c000000 */
    .interrupt_parent = &__metal_dt_interrupt_controller_c000000.controller,
    .num_interrupts = METAL_MAX_GPIO_INTERRUPTS,
    .interrupt_lines[0] = 27,
    .interrupt_lines[1] = 28,
    .interrupt_lines[2] = 29,
    .interrupt_lines[3] = 30,
};

/* From gpio@20002000 */
struct __metal_driver_sifive_gpio0 __metal_dt_gpio_20002000 = {
    .vtable = &__metal_driver_vtable_sifive_gpio0,
    .gpio.vtable = &__metal_driver_vtable_sifive_gpio0.gpio,
    .base = METAL_SIFIVE_GPIO0_20002000_BASE_ADDRESS,
    .size = METAL_SIFIVE_GPIO0_20002000_SIZE,
/* From interrupt_controller@c000000 */
    .interrupt_parent = &__metal_dt_interrupt_controller_c000000.controller,
    .num_interrupts = METAL_MAX_GPIO_INTERRUPTS,
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
};

/* From button@0 */
struct __metal_driver_sifive_gpio_button __metal_dt_button_0 = {
    .vtable = &__metal_driver_vtable_sifive_button,
    .button.vtable = &__metal_driver_vtable_sifive_button.button_vtable,
/* From gpio@10060000 */
    .gpio = &__metal_dt_gpio_10060000,
    .pin = 4UL,
/* From global_external_interrupts */
    .interrupt_parent = &__metal_dt_global_external_interrupts.irc,
    .interrupt_line = 0UL,
    .label = "BTN0",
};

/* From button@1 */
struct __metal_driver_sifive_gpio_button __metal_dt_button_1 = {
    .vtable = &__metal_driver_vtable_sifive_button,
    .button.vtable = &__metal_driver_vtable_sifive_button.button_vtable,
/* From gpio@10060000 */
    .gpio = &__metal_dt_gpio_10060000,
    .pin = 5UL,
/* From global_external_interrupts */
    .interrupt_parent = &__metal_dt_global_external_interrupts.irc,
    .interrupt_line = 1UL,
    .label = "BTN1",
};

/* From button@2 */
struct __metal_driver_sifive_gpio_button __metal_dt_button_2 = {
    .vtable = &__metal_driver_vtable_sifive_button,
    .button.vtable = &__metal_driver_vtable_sifive_button.button_vtable,
/* From gpio@10060000 */
    .gpio = &__metal_dt_gpio_10060000,
    .pin = 6UL,
/* From global_external_interrupts */
    .interrupt_parent = &__metal_dt_global_external_interrupts.irc,
    .interrupt_line = 2UL,
    .label = "BTN2",
};

/* From button@3 */
struct __metal_driver_sifive_gpio_button __metal_dt_button_3 = {
    .vtable = &__metal_driver_vtable_sifive_button,
    .button.vtable = &__metal_driver_vtable_sifive_button.button_vtable,
/* From gpio@10060000 */
    .gpio = &__metal_dt_gpio_10060000,
    .pin = 7UL,
/* From global_external_interrupts */
    .interrupt_parent = &__metal_dt_global_external_interrupts.irc,
    .interrupt_line = 3UL,
    .label = "BTN3",
};

/* From led@0red */
struct __metal_driver_sifive_gpio_led __metal_dt_led_0red = {
    .vtable = &__metal_driver_vtable_sifive_led,
    .led.vtable = &__metal_driver_vtable_sifive_led.led_vtable,
/* From gpio@10060000 */
    .gpio = &__metal_dt_gpio_10060000,
    .pin = 0UL,
    .label = "LD0red",
};

/* From led@0green */
struct __metal_driver_sifive_gpio_led __metal_dt_led_0green = {
    .vtable = &__metal_driver_vtable_sifive_led,
    .led.vtable = &__metal_driver_vtable_sifive_led.led_vtable,
/* From gpio@10060000 */
    .gpio = &__metal_dt_gpio_10060000,
    .pin = 1UL,
    .label = "LD0green",
};

/* From led@0blue */
struct __metal_driver_sifive_gpio_led __metal_dt_led_0blue = {
    .vtable = &__metal_driver_vtable_sifive_led,
    .led.vtable = &__metal_driver_vtable_sifive_led.led_vtable,
/* From gpio@10060000 */
    .gpio = &__metal_dt_gpio_10060000,
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
/* From global_external_interrupts */
    .interrupt_parent = &__metal_dt_global_external_interrupts.irc,
    .interrupt_line = 3UL,
    .label = "SW3",
};

/* From spi@20004000 */
struct __metal_driver_sifive_spi0 __metal_dt_spi_20004000 = {
    .vtable = &__metal_driver_vtable_sifive_spi0,
    .spi.vtable = &__metal_driver_vtable_sifive_spi0.spi,
    .control_base = METAL_SIFIVE_SPI0_20004000_BASE_ADDRESS,
    .control_size = METAL_SIFIVE_SPI0_20004000_SIZE,
/* From tlclk */
    .clock = &__metal_dt_tlclk.clock,
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
    .control_base = METAL_SIFIVE_UART0_20000000_BASE_ADDRESS,
    .control_size = METAL_SIFIVE_UART0_20000000_SIZE,
/* From tlclk */
    .clock = &__metal_dt_tlclk.clock,
    .pinmux = NULL,
/* From interrupt_controller@c000000 */
    .interrupt_parent = &__metal_dt_interrupt_controller_c000000.controller,
    .num_interrupts = METAL_MAX_UART_INTERRUPTS,
    .interrupt_line = 25UL,
};


#define __METAL_DT_MAX_MEMORIES 2

asm (".weak __metal_memory_table");
struct metal_memory *__metal_memory_table[] = {
					&__metal_dt_mem_memory_80000000,
					&__metal_dt_mem_spi_20004000};

/* From serial@20000000 */
#define __METAL_DT_STDOUT_UART_HANDLE (&__metal_dt_serial_20000000.uart)

#define __METAL_DT_SERIAL_20000000_HANDLE (&__metal_dt_serial_20000000.uart)

#define __METAL_DT_STDOUT_UART_BAUD 115200

/* From clint@2000000 */
#define __METAL_DT_RISCV_CLINT0_HANDLE (&__metal_dt_clint_2000000.controller)

#define __METAL_DT_CLINT_2000000_HANDLE (&__metal_dt_clint_2000000.controller)

#define __METAL_DT_MAX_HARTS 1

asm (".weak __metal_cpu_table");
struct __metal_driver_cpu *__metal_cpu_table[] = {
					&__metal_dt_cpu_0};

/* From interrupt_controller@c000000 */
#define __METAL_DT_RISCV_PLIC0_HANDLE (&__metal_dt_interrupt_controller_c000000.controller)

#define __METAL_DT_INTERRUPT_CONTROLLER_C000000_HANDLE (&__metal_dt_interrupt_controller_c000000.controller)

/* From pmp@0 */
#define __METAL_DT_PMP_HANDLE (&__metal_dt_pmp_0)

/* From global_external_interrupts */
#define __METAL_DT_SIFIVE_GLOBAL_EXINTR0_HANDLE (&__metal_dt_global_external_interrupts.irc)

#define __METAL_DT_GLOBAL_EXTERNAL_INTERRUPTS_HANDLE (&__metal_dt_global_external_interrupts.irc)

#define __MEE_DT_MAX_GPIOS 2

asm (".weak __metal_gpio_table");
struct __metal_driver_sifive_gpio0 *__metal_gpio_table[] = {
					&__metal_dt_gpio_10060000,
					&__metal_dt_gpio_20002000};

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
#endif /* COREIP_S76_ARTY__METAL_H*/
#endif /* ! ASSEMBLY */
