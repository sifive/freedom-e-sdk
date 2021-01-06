/* Copyright 2019 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#include <stdio.h>

#include <metal/init.h>

int my_global = 0;

void metal_init_run() {
    /* Run our own init instead of the metal constructors */
    my_global = 1;
}

void metal_fini_run() {
    /* Don't run the metal destructors */
}

int main() {
    /* Check to make sure our custom constructor ran */
    if (my_global != 1) {
        return 1;
    }

    /* Now run the metal constructors to initialize standard I/O */
    metal_init();

    printf("minimal-boot\n");

    /* Now run the metal destructors */
    metal_fini();

    return 0;
}
