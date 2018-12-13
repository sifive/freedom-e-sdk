#ifndef ASSEMBLY
#include <mee/drivers/fixed-clock.h>
#include <mee/drivers/sifive,fe310-g000,pll.h>
#include <mee/drivers/sifive,fe310-g000,prci.h>
#include <mee/drivers/sifive,fe310-g000,hfxosc.h>
#include <mee/drivers/sifive,fe310-g000,hfrosc.h>
#include <mee/drivers/sifive,gpio0.h>
#include <mee/drivers/sifive,uart0.h>
/* From clock@0 */
asm (".weak __mee_dt_clock_0");
struct __mee_driver_fixed_clock __mee_dt_clock_0;

/* From clock@2 */
asm (".weak __mee_dt_clock_2");
struct __mee_driver_fixed_clock __mee_dt_clock_2;

/* From clock@5 */
asm (".weak __mee_dt_clock_5");
struct __mee_driver_fixed_clock __mee_dt_clock_5;

/* From clock@4 */
asm (".weak __mee_dt_clock_4");
struct __mee_driver_sifive_fe310_g000_pll __mee_dt_clock_4;

/* From prci@10008000 */
asm (".weak __mee_dt_prci_10008000");
struct __mee_driver_sifive_fe310_g000_prci __mee_dt_prci_10008000;

/* From clock@1 */
asm (".weak __mee_dt_clock_1");
struct __mee_driver_sifive_fe310_g000_hfxosc __mee_dt_clock_1;

/* From clock@3 */
asm (".weak __mee_dt_clock_3");
struct __mee_driver_sifive_fe310_g000_hfrosc __mee_dt_clock_3;

/* From gpio@10012000 */
asm (".weak __mee_dt_gpio_10012000");
struct __mee_driver_sifive_gpio0 __mee_dt_gpio_10012000;

/* From serial@10013000 */
asm (".weak __mee_dt_serial_10013000");
struct __mee_driver_sifive_uart0 __mee_dt_serial_10013000;

/* From clock@0 */
struct __mee_driver_fixed_clock __mee_dt_clock_0 = {
    .vtable = &__mee_driver_vtable_fixed_clock,
    .clock.vtable = &__mee_driver_vtable_fixed_clock.clock,
    .rate = 16000000UL,
};

/* From clock@2 */
struct __mee_driver_fixed_clock __mee_dt_clock_2 = {
    .vtable = &__mee_driver_vtable_fixed_clock,
    .clock.vtable = &__mee_driver_vtable_fixed_clock.clock,
    .rate = 72000000UL,
};

/* From clock@5 */
struct __mee_driver_fixed_clock __mee_dt_clock_5 = {
    .vtable = &__mee_driver_vtable_fixed_clock,
    .clock.vtable = &__mee_driver_vtable_fixed_clock.clock,
    .rate = 32000000UL,
};

/* From clock@4 */
struct __mee_driver_sifive_fe310_g000_pll __mee_dt_clock_4 = {
    .vtable = &__mee_driver_vtable_sifive_fe310_g000_pll,
    .clock.vtable = &__mee_driver_vtable_sifive_fe310_g000_pll.clock,
/* From clock@3 */
    .pllsel0 = &__mee_dt_clock_3.clock,
/* From clock@1 */
    .pllref = &__mee_dt_clock_1.clock,
/* From prci@10008000 */
    .divider_base = &__mee_dt_prci_10008000,
    .divider_offset = 12UL,
/* From prci@10008000 */
    .config_base = &__mee_dt_prci_10008000,
    .config_offset = 8UL,
    .init_rate = 16000000UL,
};

/* From clock@4 */
#define __MEE_DT_SIFIVE_FE310_G000_PLL_HANDLE (&__mee_dt_clock_4)
/* From prci@10008000 */
struct __mee_driver_sifive_fe310_g000_prci __mee_dt_prci_10008000 = {
    .vtable = &__mee_driver_vtable_sifive_fe310_g000_prci,
    .base = 268468224UL,
    .size = 32768UL,
};

/* From clock@1 */
struct __mee_driver_sifive_fe310_g000_hfxosc __mee_dt_clock_1 = {
    .vtable = &__mee_driver_vtable_sifive_fe310_g000_hfxosc,
    .clock.vtable = &__mee_driver_vtable_sifive_fe310_g000_hfxosc.clock,
/* From clock@0 */
    .ref = &__mee_dt_clock_0.clock,
/* From prci@10008000 */
    .config_base = &__mee_dt_prci_10008000,
    .config_offset = 4UL,
};

/* From clock@3 */
struct __mee_driver_sifive_fe310_g000_hfrosc __mee_dt_clock_3 = {
    .vtable = &__mee_driver_vtable_sifive_fe310_g000_hfrosc,
    .clock.vtable = &__mee_driver_vtable_sifive_fe310_g000_hfrosc.clock,
/* From clock@2 */
    .ref = &__mee_dt_clock_2.clock,
/* From prci@10008000 */
    .config_base = &__mee_dt_prci_10008000,
    .config_offset = 0UL,
};

/* From gpio@10012000 */
struct __mee_driver_sifive_gpio0 __mee_dt_gpio_10012000 = {
    .vtable = &__mee_driver_vtable_sifive_gpio0,
    .base = 268509184UL,
    .size = 4096UL,
};

/* From serial@10013000 */
struct __mee_driver_sifive_uart0 __mee_dt_serial_10013000 = {
    .vtable = &__mee_driver_vtable_sifive_uart0,
    .uart.vtable = &__mee_driver_vtable_sifive_uart0.uart,
    .control_base = 268513280UL,
    .control_size = 4096UL,
/* From clock@4 */
    .clock = &__mee_dt_clock_4.clock,
/* From gpio@10012000 */
    .pinmux = &__mee_dt_gpio_10012000,
    .pinmux_output_selector = 196608UL,
    .pinmux_source_selector = 196608UL,
};

/* From serial@10013000 */
#define __MEE_DT_STDOUT_UART_HANDLE (&__mee_dt_serial_10013000.uart)
#define __MEE_DT_STDOUT_UART_BAUD 115200
#endif/*ASSEMBLY*/
