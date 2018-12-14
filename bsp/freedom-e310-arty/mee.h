#ifndef ASSEMBLY
#include <mee/drivers/fixed-clock.h>
#include <mee/drivers/sifive,gpio0.h>
#include <mee/drivers/sifive,uart0.h>
/* From clock@0 */
asm (".weak __mee_dt_clock_0");
struct __mee_driver_fixed_clock __mee_dt_clock_0;

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
    .rate = 65000000UL,
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
/* From clock@0 */
    .clock = &__mee_dt_clock_0.clock,
/* From gpio@10012000 */
    .pinmux = &__mee_dt_gpio_10012000,
    .pinmux_output_selector = 196608UL,
    .pinmux_source_selector = 196608UL,
};

/* From serial@10013000 */
#define __MEE_DT_STDOUT_UART_HANDLE (&__mee_dt_serial_10013000.uart)
#define __MEE_DT_STDOUT_UART_BAUD 115200
#endif/*ASSEMBLY*/
