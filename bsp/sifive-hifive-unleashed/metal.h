#ifndef ASSEMBLY

#ifndef SIFIVE_HIFIVE_UNLEASHED__METAL_H
#define SIFIVE_HIFIVE_UNLEASHED__METAL_H

#ifdef __METAL_MACHINE_MACROS

#define __METAL_CLINT_NUM_PARENTS 10

#ifndef __METAL_CLINT_NUM_PARENTS
#define __METAL_CLINT_NUM_PARENTS 0
#endif
#define __METAL_PLIC_SUBINTERRUPTS 54

#define __METAL_PLIC_NUM_PARENTS 9

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

#define __METAL_CLINT_2000000_INTERRUPTS 10

#define METAL_MAX_CLINT_INTERRUPTS 10

#define __METAL_CLINT_NUM_PARENTS 10

#define __METAL_INTERRUPT_CONTROLLER_C000000_INTERRUPTS 9

#define __METAL_PLIC_SUBINTERRUPTS 54

#define METAL_MAX_PLIC_INTERRUPTS 9

#define __METAL_PLIC_NUM_PARENTS 9

#define __METAL_CLIC_SUBINTERRUPTS 0
#define METAL_MAX_CLIC_INTERRUPTS 0

#define METAL_MAX_LOCAL_EXT_INTERRUPTS 0

#define METAL_MAX_GLOBAL_EXT_INTERRUPTS 0

#define __METAL_GPIO_10060000_INTERRUPTS 16

#define METAL_MAX_GPIO_INTERRUPTS 16

#define __METAL_SERIAL_10010000_INTERRUPTS 1

#define __METAL_SERIAL_10011000_INTERRUPTS 1

#define METAL_MAX_UART_INTERRUPTS 1


#include <metal/drivers/fixed-clock.h>
#include <metal/drivers/fixed-factor-clock.h>
#include <metal/memory.h>
#include <metal/drivers/riscv,clint0.h>
#include <metal/drivers/riscv,cpu.h>
#include <metal/drivers/riscv,plic0.h>
#include <metal/pmp.h>
#include <metal/drivers/sifive,gpio0.h>
#include <metal/drivers/sifive,spi0.h>
#include <metal/drivers/sifive,test0.h>
#include <metal/drivers/sifive,uart0.h>
#include <metal/drivers/sifive,fu540-c000,l2.h>

/* From refclk */
asm (".weak __metal_dt_refclk");
struct __metal_driver_fixed_clock __metal_dt_refclk;

/* From tlclk */
asm (".weak __metal_dt_tlclk");
struct __metal_driver_fixed_factor_clock __metal_dt_tlclk;

asm (".weak __metal_dt_mem_dtim_1000000");
struct metal_memory __metal_dt_mem_dtim_1000000;

asm (".weak __metal_dt_mem_itim_1800000");
struct metal_memory __metal_dt_mem_itim_1800000;

asm (".weak __metal_dt_mem_itim_1808000");
struct metal_memory __metal_dt_mem_itim_1808000;

asm (".weak __metal_dt_mem_itim_1810000");
struct metal_memory __metal_dt_mem_itim_1810000;

asm (".weak __metal_dt_mem_itim_1818000");
struct metal_memory __metal_dt_mem_itim_1818000;

asm (".weak __metal_dt_mem_itim_1820000");
struct metal_memory __metal_dt_mem_itim_1820000;

asm (".weak __metal_dt_mem_memory_80000000");
struct metal_memory __metal_dt_mem_memory_80000000;

asm (".weak __metal_dt_mem_spi_10040000");
struct metal_memory __metal_dt_mem_spi_10040000;

asm (".weak __metal_dt_mem_spi_10041000");
struct metal_memory __metal_dt_mem_spi_10041000;

asm (".weak __metal_dt_mem_spi_10050000");
struct metal_memory __metal_dt_mem_spi_10050000;

/* From clint@2000000 */
asm (".weak __metal_dt_clint_2000000");
struct __metal_driver_riscv_clint0 __metal_dt_clint_2000000;

/* From cpu@0 */
asm (".weak __metal_dt_cpu_0");
struct __metal_driver_cpu __metal_dt_cpu_0;

/* From cpu@1 */
asm (".weak __metal_dt_cpu_1");
struct __metal_driver_cpu __metal_dt_cpu_1;

/* From cpu@2 */
asm (".weak __metal_dt_cpu_2");
struct __metal_driver_cpu __metal_dt_cpu_2;

/* From cpu@3 */
asm (".weak __metal_dt_cpu_3");
struct __metal_driver_cpu __metal_dt_cpu_3;

/* From cpu@4 */
asm (".weak __metal_dt_cpu_4");
struct __metal_driver_cpu __metal_dt_cpu_4;

asm (".weak __metal_dt_cpu_0_interrupt_controller");
struct __metal_driver_riscv_cpu_intc __metal_dt_cpu_0_interrupt_controller;

asm (".weak __metal_dt_cpu_1_interrupt_controller");
struct __metal_driver_riscv_cpu_intc __metal_dt_cpu_1_interrupt_controller;

asm (".weak __metal_dt_cpu_2_interrupt_controller");
struct __metal_driver_riscv_cpu_intc __metal_dt_cpu_2_interrupt_controller;

asm (".weak __metal_dt_cpu_3_interrupt_controller");
struct __metal_driver_riscv_cpu_intc __metal_dt_cpu_3_interrupt_controller;

asm (".weak __metal_dt_cpu_4_interrupt_controller");
struct __metal_driver_riscv_cpu_intc __metal_dt_cpu_4_interrupt_controller;

/* From interrupt_controller@c000000 */
asm (".weak __metal_dt_interrupt_controller_c000000");
struct __metal_driver_riscv_plic0 __metal_dt_interrupt_controller_c000000;

asm (".weak __metal_dt_pmp_0");
struct metal_pmp __metal_dt_pmp_0;

/* From gpio@10060000 */
asm (".weak __metal_dt_gpio_10060000");
struct __metal_driver_sifive_gpio0 __metal_dt_gpio_10060000;

/* From spi@10040000 */
asm (".weak __metal_dt_spi_10040000");
struct __metal_driver_sifive_spi0 __metal_dt_spi_10040000;

/* From spi@10041000 */
asm (".weak __metal_dt_spi_10041000");
struct __metal_driver_sifive_spi0 __metal_dt_spi_10041000;

/* From spi@10050000 */
asm (".weak __metal_dt_spi_10050000");
struct __metal_driver_sifive_spi0 __metal_dt_spi_10050000;

/* From teststatus@4000 */
asm (".weak __metal_dt_teststatus_4000");
struct __metal_driver_sifive_test0 __metal_dt_teststatus_4000;

/* From serial@10010000 */
asm (".weak __metal_dt_serial_10010000");
struct __metal_driver_sifive_uart0 __metal_dt_serial_10010000;

/* From serial@10011000 */
asm (".weak __metal_dt_serial_10011000");
struct __metal_driver_sifive_uart0 __metal_dt_serial_10011000;

/* From cache_controller@2010000 */
asm (".weak __metal_dt_cache_controller_2010000");
struct __metal_driver_sifive_fu540_c000_l2 __metal_dt_cache_controller_2010000;


/* From refclk */
struct __metal_driver_fixed_clock __metal_dt_refclk = {
    .vtable = &__metal_driver_vtable_fixed_clock,
    .clock.vtable = &__metal_driver_vtable_fixed_clock.clock,
    .rate = 33333333UL,
};

/* From tlclk */
struct __metal_driver_fixed_factor_clock __metal_dt_tlclk = {
    .vtable = &__metal_driver_vtable_fixed_factor_clock,
    .clock.vtable = &__metal_driver_vtable_fixed_factor_clock.clock,
/* From refclk */
    .parent = &__metal_dt_refclk.clock,
    .mult = 1,
    .div = 2,
};

struct metal_memory __metal_dt_mem_dtim_1000000 = {
    ._base_address = 16777216UL,
    ._size = 8192UL,
    ._attrs = {
        .R = 1,
        .W = 1,
        .X = 1,
        .C = 1,
        .A = 1},
};

struct metal_memory __metal_dt_mem_itim_1800000 = {
    ._base_address = 25165824UL,
    ._size = 16384UL,
    ._attrs = {
        .R = 1,
        .W = 1,
        .X = 1,
        .C = 1,
        .A = 1},
};

struct metal_memory __metal_dt_mem_itim_1808000 = {
    ._base_address = 25198592UL,
    ._size = 32768UL,
    ._attrs = {
        .R = 1,
        .W = 1,
        .X = 1,
        .C = 1,
        .A = 1},
};

struct metal_memory __metal_dt_mem_itim_1810000 = {
    ._base_address = 25231360UL,
    ._size = 32768UL,
    ._attrs = {
        .R = 1,
        .W = 1,
        .X = 1,
        .C = 1,
        .A = 1},
};

struct metal_memory __metal_dt_mem_itim_1818000 = {
    ._base_address = 25264128UL,
    ._size = 32768UL,
    ._attrs = {
        .R = 1,
        .W = 1,
        .X = 1,
        .C = 1,
        .A = 1},
};

struct metal_memory __metal_dt_mem_itim_1820000 = {
    ._base_address = 25296896UL,
    ._size = 32768UL,
    ._attrs = {
        .R = 1,
        .W = 1,
        .X = 1,
        .C = 1,
        .A = 1},
};

struct metal_memory __metal_dt_mem_memory_80000000 = {
    ._base_address = 2147483648UL,
    ._size = 135291469824UL,
    ._attrs = {
        .R = 1,
        .W = 1,
        .X = 1,
        .C = 1,
        .A = 1},
};

struct metal_memory __metal_dt_mem_spi_10040000 = {
    ._base_address = 536870912UL,
    ._size = 268435456UL,
    ._attrs = {
        .R = 1,
        .W = 1,
        .X = 1,
        .C = 1,
        .A = 1},
};

struct metal_memory __metal_dt_mem_spi_10041000 = {
    ._base_address = 805306368UL,
    ._size = 268435456UL,
    ._attrs = {
        .R = 1,
        .W = 1,
        .X = 1,
        .C = 1,
        .A = 1},
};

struct metal_memory __metal_dt_mem_spi_10050000 = {
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
    .control_base = 33554432UL,
    .control_size = 65536UL,
    .init_done = 0,
    .num_interrupts = METAL_MAX_CLINT_INTERRUPTS,
    .interrupt_parents[0] = &__metal_dt_cpu_0_interrupt_controller.controller,
    .interrupt_lines[0] = 3,
    .interrupt_parents[1] = &__metal_dt_cpu_0_interrupt_controller.controller,
    .interrupt_lines[1] = 7,
    .interrupt_parents[2] = &__metal_dt_cpu_1_interrupt_controller.controller,
    .interrupt_lines[2] = 3,
    .interrupt_parents[3] = &__metal_dt_cpu_1_interrupt_controller.controller,
    .interrupt_lines[3] = 7,
    .interrupt_parents[4] = &__metal_dt_cpu_2_interrupt_controller.controller,
    .interrupt_lines[4] = 3,
    .interrupt_parents[5] = &__metal_dt_cpu_2_interrupt_controller.controller,
    .interrupt_lines[5] = 7,
    .interrupt_parents[6] = &__metal_dt_cpu_3_interrupt_controller.controller,
    .interrupt_lines[6] = 3,
    .interrupt_parents[7] = &__metal_dt_cpu_3_interrupt_controller.controller,
    .interrupt_lines[7] = 7,
    .interrupt_parents[8] = &__metal_dt_cpu_4_interrupt_controller.controller,
    .interrupt_lines[8] = 3,
    .interrupt_parents[9] = &__metal_dt_cpu_4_interrupt_controller.controller,
    .interrupt_lines[9] = 7,
};

/* From cpu@0 */
struct __metal_driver_cpu __metal_dt_cpu_0 = {
    .vtable = &__metal_driver_vtable_cpu,
    .cpu.vtable = &__metal_driver_vtable_cpu.cpu_vtable,
    .timebase = 1000000UL,
    .interrupt_controller = &__metal_dt_cpu_0_interrupt_controller.controller,
};

/* From cpu@1 */
struct __metal_driver_cpu __metal_dt_cpu_1 = {
    .vtable = &__metal_driver_vtable_cpu,
    .cpu.vtable = &__metal_driver_vtable_cpu.cpu_vtable,
    .timebase = 1000000UL,
    .interrupt_controller = &__metal_dt_cpu_1_interrupt_controller.controller,
};

/* From cpu@2 */
struct __metal_driver_cpu __metal_dt_cpu_2 = {
    .vtable = &__metal_driver_vtable_cpu,
    .cpu.vtable = &__metal_driver_vtable_cpu.cpu_vtable,
    .timebase = 1000000UL,
    .interrupt_controller = &__metal_dt_cpu_2_interrupt_controller.controller,
};

/* From cpu@3 */
struct __metal_driver_cpu __metal_dt_cpu_3 = {
    .vtable = &__metal_driver_vtable_cpu,
    .cpu.vtable = &__metal_driver_vtable_cpu.cpu_vtable,
    .timebase = 1000000UL,
    .interrupt_controller = &__metal_dt_cpu_3_interrupt_controller.controller,
};

/* From cpu@4 */
struct __metal_driver_cpu __metal_dt_cpu_4 = {
    .vtable = &__metal_driver_vtable_cpu,
    .cpu.vtable = &__metal_driver_vtable_cpu.cpu_vtable,
    .timebase = 1000000UL,
    .interrupt_controller = &__metal_dt_cpu_4_interrupt_controller.controller,
};

/* From interrupt_controller */
struct __metal_driver_riscv_cpu_intc __metal_dt_cpu_0_interrupt_controller = {
    .vtable = &__metal_driver_vtable_riscv_cpu_intc,
    .controller.vtable = &__metal_driver_vtable_riscv_cpu_intc.controller_vtable,
    .init_done = 0,
    .interrupt_controller = 1,
};

/* From interrupt_controller */
struct __metal_driver_riscv_cpu_intc __metal_dt_cpu_1_interrupt_controller = {
    .vtable = &__metal_driver_vtable_riscv_cpu_intc,
    .controller.vtable = &__metal_driver_vtable_riscv_cpu_intc.controller_vtable,
    .init_done = 0,
    .interrupt_controller = 1,
};

/* From interrupt_controller */
struct __metal_driver_riscv_cpu_intc __metal_dt_cpu_2_interrupt_controller = {
    .vtable = &__metal_driver_vtable_riscv_cpu_intc,
    .controller.vtable = &__metal_driver_vtable_riscv_cpu_intc.controller_vtable,
    .init_done = 0,
    .interrupt_controller = 1,
};

/* From interrupt_controller */
struct __metal_driver_riscv_cpu_intc __metal_dt_cpu_3_interrupt_controller = {
    .vtable = &__metal_driver_vtable_riscv_cpu_intc,
    .controller.vtable = &__metal_driver_vtable_riscv_cpu_intc.controller_vtable,
    .init_done = 0,
    .interrupt_controller = 1,
};

/* From interrupt_controller */
struct __metal_driver_riscv_cpu_intc __metal_dt_cpu_4_interrupt_controller = {
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
    .interrupt_parents[1] = &__metal_dt_cpu_1_interrupt_controller.controller,
    .interrupt_lines[1] = 11,
    .interrupt_parents[2] = &__metal_dt_cpu_1_interrupt_controller.controller,
    .interrupt_lines[2] = 9,
    .interrupt_parents[3] = &__metal_dt_cpu_2_interrupt_controller.controller,
    .interrupt_lines[3] = 11,
    .interrupt_parents[4] = &__metal_dt_cpu_2_interrupt_controller.controller,
    .interrupt_lines[4] = 9,
    .interrupt_parents[5] = &__metal_dt_cpu_3_interrupt_controller.controller,
    .interrupt_lines[5] = 11,
    .interrupt_parents[6] = &__metal_dt_cpu_3_interrupt_controller.controller,
    .interrupt_lines[6] = 9,
    .interrupt_parents[7] = &__metal_dt_cpu_4_interrupt_controller.controller,
    .interrupt_lines[7] = 11,
    .interrupt_parents[8] = &__metal_dt_cpu_4_interrupt_controller.controller,
    .interrupt_lines[8] = 9,
    .control_base = 201326592UL,
    .control_size = 67108864UL,
    .max_priority = 7UL,
    .num_interrupts = 54UL,
    .interrupt_controller = 1,
};

/* From pmp@0 */
struct metal_pmp __metal_dt_pmp_0 = {
    .num_regions = 1UL,
};

/* From gpio@10060000 */
struct __metal_driver_sifive_gpio0 __metal_dt_gpio_10060000 = {
    .vtable = &__metal_driver_vtable_sifive_gpio0,
    .gpio.vtable = &__metal_driver_vtable_sifive_gpio0.gpio,
    .base = 268828672UL,
    .size = 4096UL,
/* From interrupt_controller@c000000 */
    .interrupt_parent = &__metal_dt_interrupt_controller_c000000.controller,
    .num_interrupts = METAL_MAX_GPIO_INTERRUPTS,
    .interrupt_lines[0] = 7,
    .interrupt_lines[1] = 8,
    .interrupt_lines[2] = 9,
    .interrupt_lines[3] = 10,
    .interrupt_lines[4] = 11,
    .interrupt_lines[5] = 12,
    .interrupt_lines[6] = 13,
    .interrupt_lines[7] = 14,
    .interrupt_lines[8] = 15,
    .interrupt_lines[9] = 16,
    .interrupt_lines[10] = 17,
    .interrupt_lines[11] = 18,
    .interrupt_lines[12] = 19,
    .interrupt_lines[13] = 20,
    .interrupt_lines[14] = 21,
    .interrupt_lines[15] = 22,
};

/* From spi@10040000 */
struct __metal_driver_sifive_spi0 __metal_dt_spi_10040000 = {
    .vtable = &__metal_driver_vtable_sifive_spi0,
    .spi.vtable = &__metal_driver_vtable_sifive_spi0.spi,
    .control_base = 268697600UL,
    .control_size = 4096UL,
/* From tlclk */
    .clock = &__metal_dt_tlclk.clock,
    .pinmux = NULL,
};

/* From spi@10041000 */
struct __metal_driver_sifive_spi0 __metal_dt_spi_10041000 = {
    .vtable = &__metal_driver_vtable_sifive_spi0,
    .spi.vtable = &__metal_driver_vtable_sifive_spi0.spi,
    .control_base = 268701696UL,
    .control_size = 4096UL,
/* From tlclk */
    .clock = &__metal_dt_tlclk.clock,
    .pinmux = NULL,
};

/* From spi@10050000 */
struct __metal_driver_sifive_spi0 __metal_dt_spi_10050000 = {
    .vtable = &__metal_driver_vtable_sifive_spi0,
    .spi.vtable = &__metal_driver_vtable_sifive_spi0.spi,
    .control_base = 268763136UL,
    .control_size = 4096UL,
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

/* From serial@10010000 */
struct __metal_driver_sifive_uart0 __metal_dt_serial_10010000 = {
    .vtable = &__metal_driver_vtable_sifive_uart0,
    .uart.vtable = &__metal_driver_vtable_sifive_uart0.uart,
    .control_base = 268500992UL,
    .control_size = 4096UL,
/* From tlclk */
    .clock = &__metal_dt_tlclk.clock,
    .pinmux = NULL,
/* From interrupt_controller@c000000 */
    .interrupt_parent = &__metal_dt_interrupt_controller_c000000.controller,
    .num_interrupts = METAL_MAX_UART_INTERRUPTS,
    .interrupt_line = 4UL,
};

/* From serial@10011000 */
struct __metal_driver_sifive_uart0 __metal_dt_serial_10011000 = {
    .vtable = &__metal_driver_vtable_sifive_uart0,
    .uart.vtable = &__metal_driver_vtable_sifive_uart0.uart,
    .control_base = 268505088UL,
    .control_size = 4096UL,
/* From tlclk */
    .clock = &__metal_dt_tlclk.clock,
    .pinmux = NULL,
/* From interrupt_controller@c000000 */
    .interrupt_parent = &__metal_dt_interrupt_controller_c000000.controller,
    .num_interrupts = METAL_MAX_UART_INTERRUPTS,
    .interrupt_line = 5UL,
};

/* From cache_controller@2010000 */
struct __metal_driver_sifive_fu540_c000_l2 __metal_dt_cache_controller_2010000 = {
    .vtable = &__metal_driver_vtable_sifive_fu540_c000_l2,
    .cache.vtable = &__metal_driver_vtable_sifive_fu540_c000_l2.cache,
};


#define __METAL_DT_MAX_MEMORIES 9

asm (".weak __metal_memory_table");
struct metal_memory *__metal_memory_table[] = {
					&__metal_dt_mem_dtim_1000000,
					&__metal_dt_mem_itim_1800000,
					&__metal_dt_mem_itim_1808000,
					&__metal_dt_mem_itim_1810000,
					&__metal_dt_mem_itim_1818000,
					&__metal_dt_mem_itim_1820000,
					&__metal_dt_mem_memory_80000000,
					&__metal_dt_mem_spi_10040000,
					&__metal_dt_mem_spi_10041000};

/* From serial@10010000 */
#define __METAL_DT_STDOUT_UART_HANDLE (&__metal_dt_serial_10010000.uart)

#define __METAL_DT_SERIAL_10010000_HANDLE (&__metal_dt_serial_10010000.uart)

#define __METAL_DT_STDOUT_UART_BAUD 115200

/* From clint@2000000 */
#define __METAL_DT_RISCV_CLINT0_HANDLE (&__metal_dt_clint_2000000.controller)

#define __METAL_DT_CLINT_2000000_HANDLE (&__metal_dt_clint_2000000.controller)

#define __METAL_DT_MAX_HARTS 5

asm (".weak __metal_cpu_table");
struct __metal_driver_cpu *__metal_cpu_table[] = {
					&__metal_dt_cpu_0,
					&__metal_dt_cpu_1,
					&__metal_dt_cpu_2,
					&__metal_dt_cpu_3,
					&__metal_dt_cpu_4};

/* From interrupt_controller@c000000 */
#define __METAL_DT_RISCV_PLIC0_HANDLE (&__metal_dt_interrupt_controller_c000000.controller)

#define __METAL_DT_INTERRUPT_CONTROLLER_C000000_HANDLE (&__metal_dt_interrupt_controller_c000000.controller)

/* From pmp@0 */
#define __METAL_DT_PMP_HANDLE (&__metal_dt_pmp_0)

#define __MEE_DT_MAX_GPIOS 1

asm (".weak __metal_gpio_table");
struct __metal_driver_sifive_gpio0 *__metal_gpio_table[] = {
					&__metal_dt_gpio_10060000};

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
#define __METAL_DT_MAX_SPIS 3

asm (".weak __metal_spi_table");
struct __metal_driver_sifive_spi0 *__metal_spi_table[] = {
					&__metal_dt_spi_10040000,
					&__metal_dt_spi_10041000,
					&__metal_dt_spi_10050000};

/* From teststatus@4000 */
#define __METAL_DT_SHUTDOWN_HANDLE (&__metal_dt_teststatus_4000.shutdown)

#define __METAL_DT_TESTSTATUS_4000_HANDLE (&__metal_dt_teststatus_4000.shutdown)


#endif /* ! __METAL_MACHINE_MACROS */
#endif /* SIFIVE_HIFIVE_UNLEASHED__METAL_H*/
#endif /* ! ASSEMBLY */
