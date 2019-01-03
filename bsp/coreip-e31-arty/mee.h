#ifndef ASSEMBLY
#include <mee/drivers/fixed-clock.h>
#include <mee/drivers/sifive,gpio0.h>
#include <mee/drivers/sifive,uart0.h>
#include <mee/drivers/sifive,test0.h>
/* From clock@0 */
asm (".weak __mee_dt_clock_0");
struct __mee_driver_fixed_clock __mee_dt_clock_0;

/* From gpio@20002000 */
asm (".weak __mee_dt_gpio_20002000");
struct __mee_driver_sifive_gpio0 __mee_dt_gpio_20002000;

/* From serial@20000000 */
asm (".weak __mee_dt_serial_20000000");
struct __mee_driver_sifive_uart0 __mee_dt_serial_20000000;

/* From teststatus@4000 */
asm (".weak __mee_dt_teststatus_4000");
struct __mee_driver_sifive_test0 __mee_dt_teststatus_4000;

/* From clock@0 */
struct __mee_driver_fixed_clock __mee_dt_clock_0 = {
    .vtable = &__mee_driver_vtable_fixed_clock,
    .clock.vtable = &__mee_driver_vtable_fixed_clock.clock,
    .rate = 32500000UL,
};

/* From gpio@20002000 */
struct __mee_driver_sifive_gpio0 __mee_dt_gpio_20002000 = {
    .vtable = &__mee_driver_vtable_sifive_gpio0,
    .base = 536879104UL,
    .size = 4096UL,
};

/* From serial@20000000 */
struct __mee_driver_sifive_uart0 __mee_dt_serial_20000000 = {
    .vtable = &__mee_driver_vtable_sifive_uart0,
    .uart.vtable = &__mee_driver_vtable_sifive_uart0.uart,
    .control_base = 536870912UL,
    .control_size = 4096UL,
/* From clock@0 */
    .clock = &__mee_dt_clock_0.clock,
    .pinmux = NULL,
};

/* From teststatus@4000 */
struct __mee_driver_sifive_test0 __mee_dt_teststatus_4000 = {
    .vtable = &__mee_driver_vtable_sifive_test0,
    .shutdown.vtable = &__mee_driver_vtable_sifive_test0.shutdown,
    .base = 16384UL,
    .size = 4096UL,
};

/* From teststatus@4000 */
#define __MEE_DT_SHUTDOWN_HANDLE (&__mee_dt_teststatus_4000.shutdown)
/* From serial@20000000 */
#define __MEE_DT_STDOUT_UART_HANDLE (&__mee_dt_serial_20000000.uart)
#define __MEE_DT_STDOUT_UART_BAUD 115200
#endif/*ASSEMBLY*/
