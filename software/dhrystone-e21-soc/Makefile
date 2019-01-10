TARGET = dhrystone-e21-soc

C_SRCS := dhry_stubs.c dhry_printf.c dhry_1.c dhry_2.c
HEADERS := dhry.h

XLEN ?= 32
CFLAGS := -Os -O2 -DSIFIVE_BENCH_TEST -DTIME -fno-inline -fno-builtin-malloc -fno-builtin-printf -Wno-implicit -fno-common  -mcmodel=medany -march=$(RISCV_ARCH) -mabi=$(RISCV_ABI) -DNOENUM -falign-functions=4 -DCRTS_SPLIT_TEXT_DATA

# This is faster:
# -O3 -mexplicit-relocs

LDFLAGS := -Wl,--wrap=scanf -Wl,--wrap=printf -march=$(RISCV_ARCH) -mabi=$(RISCV_ABI) -mcmodel=medany

BSP_BASE = ../../bsp
LINKER_SCRIPT=$(ENV_DIR)/$(BOARD)/dhrystone.lds
include $(BSP_BASE)/env/common.mk





