/* Copyright 2018 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#include <mee/drivers/sifive,gpio0.h>
#include <mee/io.h>

#define GPIO_IOF_EN     (0x38)
#define GPIO_IOF_SEL    (0x3C)

long __mee_driver_sifive_gpio0_enable_io(const struct __mee_driver_sifive_gpio0 *gpio, long source, long dest)
{
    MEE_ACCESS_ONCE((mee_io_u32 *)(gpio->base + GPIO_IOF_SEL)) &= ~source;
    MEE_ACCESS_ONCE((mee_io_u32 *)(gpio->base + GPIO_IOF_EN))  |= dest;
}
