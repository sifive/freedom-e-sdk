/* Copyright 2018 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#include <mee/drivers/sifive,test0.h>
#include <mee/io.h>
#include <stdint.h>

#define FINISHER_OFFSET 0

void __mee_driver_sifive_test0_exit(const struct __mee_shutdown *sd, int code)
{
    const struct __mee_driver_sifive_test0 *test = (void *)sd;
    uint32_t out = (code << 16) + (code == 0 ? 0x5555 : 0x3333);
    while (1) {
        __MEE_ACCESS_ONCE((mee_io_u32 *)(test->base + FINISHER_OFFSET)) = out;
    }
}
