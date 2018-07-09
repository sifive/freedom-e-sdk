/* Copyright 2018 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#include <mee/drivers/sifive,uart0.h>

/* An initialization routine for the MEE. */
void __mee_before_main(long hartid)
{
    /* We only support single-hart systems for now. */
    if (hartid != 0)
        return;

#ifdef __MEE_DT_SIFIVE_UART0_0_HANDLE
    __mee_driver_sifive_uart0_init(__MEE_DT_SIFIVE_UART0_0_HANDLE);
#endif

#ifdef __MEE_DT_SIFIVE_UART0_1_HANDLE
# error "Only one sifive,uart0 is supported"
#endif
}
