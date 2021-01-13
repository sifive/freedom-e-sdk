/* Copyright 2021 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <metal/machine/platform.h>
#include <metal/remapper.h>

#define VALID_REGS_NUM  7

/* rom_data should be placed in ROM section, total size: 16 bytes. */
volatile const int rom_data[] __attribute__((aligned(16), section(".rodata"))) = {1, 2, 3, 4};

/* ram_data should be placed in RAM section, total size: 16 bytes. */
volatile int ram_data[] __attribute__((aligned(16))) = {5, 6, 7, 8};

/*
 * The default C standard library Newlib-Nano used by FESDK
 * doesn't support portable PRIx64 macro,
 * so we have to implement our own print function to print
 * uint64_t integer in hex format.
 */
static __attribute__((unused)) void put_hex64(uint64_t value)
{
    const int SIZE = 64;
    char buf[SIZE];
    buf[SIZE-1] = '\0';
    char *p = &buf[SIZE-1];
    int v;

    do {
        v = value % 16;
        if (v < 10) {
            *(--p) = v + '0';
        } else {
            *(--p) = (v - 10) + 'a';
        }
        value /= 16;
    } while(value);

    printf("%s", p);
}

void print_rom_data(void) {
    for (int i = 0; i < 4; i++) {
        printf("rom_data[%d] = %d\n", i, rom_data[i]);
    }
}

void valid_rom_data(int answers[]) {
    for (int i = 0; i < 4; i++) {
        if (rom_data[i] != answers[i]) {
            printf("rom_data[%d] = %u, correct value = %d\n",
                   i, rom_data[i], answers[i]);
            exit(1);
        }
    }
}

void print_remappervalid(struct metal_remapper *remapper, int idx) {
    printf("remappervalid[%d] = 0x%08" PRIx32 "\n",
           idx, metal_remapper_get_valid(remapper, idx));
}

int main(void) {
    struct metal_remapper *remapper;
    uintptr_t rom_data_addr = (uintptr_t)rom_data;
    uintptr_t ram_data_addr = (uintptr_t)ram_data;
    uint32_t remap_size = sizeof(rom_data);

    remapper = metal_remapper_get_device();
    if (!remapper) {
        return 1;
    }

    int version = metal_remapper_get_version(remapper);
    uint64_t from_region_base = metal_remapper_get_from_region_base(remapper);
    uint64_t from_region_size = metal_remapper_get_from_region_size(remapper);
    uint64_t to_region_base = metal_remapper_get_to_region_base(remapper);
    uint64_t to_region_size = metal_remapper_get_to_region_size(remapper);
    uint64_t max_from_entry_region_size =
        metal_remapper_get_max_from_entry_region_size(remapper);

    printf("Address Remapper version: %d\n", version);
    printf("From region base address: 0x");
    put_hex64(from_region_base);
    printf("\n");
    printf("From region size: 0x");
    put_hex64(from_region_size);
    printf(" bytes\n");
    printf("To region base address: 0x");
    put_hex64(to_region_base);
    printf("\n");
    printf("To region size: 0x");
    put_hex64(to_region_size);
    printf(" bytes\n");
    printf("Maximum From entry region size: 0x");
    put_hex64(max_from_entry_region_size);
    printf(" bytes\n");
    printf("\n");

    /* Ensure the remapped addresses are within From/To regions. */
    if ((rom_data_addr < from_region_base) ||
        (rom_data_addr > (from_region_base + from_region_size))) {
        return 2;
    }

    if ((ram_data_addr < to_region_base) ||
        (ram_data_addr > (to_region_base + to_region_size))) {
        return 3;
    }

    /* Ensure the remapping region size is within maximum from entry regions size. */
    if (remap_size > max_from_entry_region_size) {
        return 4;
    }

    int entry_idx = 113;
    int valid_reg_idx = entry_idx / 32;
    uint32_t remap_encoding = (remap_size >> 1) - 1;

    /*
     * Expect remap_encoding to be 0x7
     * because we are trying to remap 16-byte rom_data.
     */
    if (remap_encoding != 0x7) {
        return 5;
    }

    /* Remap ram_data to rom_data with remapping size. */
    struct metal_remapper_entry entry = {
        .idx = entry_idx,
        /*
         * We are safe to OR remap_encoding here
         * as rom_data is already 16-byte aligned.
         */
        .from_addr = rom_data_addr | remap_encoding,
        .to_addr = ram_data_addr,
    };
    metal_remapper_set_remap(remapper, &entry);

    uint64_t from_addr = metal_remapper_get_from(remapper, entry.idx);
    uint64_t to_addr = metal_remapper_get_to(remapper, entry.idx);

    printf("Remap entry - From[]: 0x");
    put_hex64(from_addr);
    printf("\n");
    printf("Remap entry - To[]: 0x");
    put_hex64(to_addr);
    printf("\n");
    printf("Remap rom_data to ram_data, remap size: %" PRIu32 " bytes.\n",
           remap_size);

    printf("rom_data address: 0x%08" PRIxPTR "\n", rom_data_addr);
    printf("ram_data address: 0x%08" PRIxPTR "\n", ram_data_addr);

    printf("Enable remap...\n");
    metal_remapper_enable_remap(remapper, entry.idx);
    print_rom_data();
    valid_rom_data((int[]){5, 6, 7, 8});
    print_remappervalid(remapper, valid_reg_idx);
    printf("\n");

    printf("Disable remap...\n");
    metal_remapper_disable_remap(remapper, entry.idx);
    print_rom_data();
    valid_rom_data((int[]){1, 2, 3, 4});
    print_remappervalid(remapper, valid_reg_idx);
    printf("\n");

    printf("Enable remap...\n");
    metal_remapper_enable_remap(remapper, entry.idx);
    print_rom_data();
    valid_rom_data((int[]){5, 6, 7, 8});
    print_remappervalid(remapper, valid_reg_idx);
    printf("\n");

    printf("Flush all remaps...\n");
    metal_remapper_flush(remapper);
    print_rom_data();
    valid_rom_data((int[]){1, 2, 3, 4});
    printf("\n");

    for (int i = 0; i < VALID_REGS_NUM; i++) {
        print_remappervalid(remapper, i);
    }

    printf("End of example.\n");

    return 0;
}

