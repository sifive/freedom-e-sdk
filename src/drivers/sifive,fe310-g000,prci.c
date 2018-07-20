/* Copyright 2018 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#include <mee/drivers/sifive,fe310-g000,prci.h>

long __mee_driver_sifive_fe310_g000_prci_get_reg(const struct __mee_driver_sifive_fe310_g000_prci *prci, long offset) {
    return __MEE_ACCESS_ONCE((mee_io_u32 *)(prci->base + offset));
}

long __mee_driver_sifive_fe310_g000_prci_set_reg(const struct __mee_driver_sifive_fe310_g000_prci *prci, long offset, long value) {
    return __MEE_ACCESS_ONCE((mee_io_u32 *)(prci->base + offset)) = value;
}
