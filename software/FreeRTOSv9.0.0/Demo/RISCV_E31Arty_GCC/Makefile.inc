# File to be included in all makefiles

TARGET=riscv64-unknown-elf
fesdk_builddir=../../../../work/build
#-----------------------------------------------------------
CCPATH	= $(fesdk_builddir)/riscv-gnu-toolchain/riscv64-unknown-elf/prefix/bin
BSP_BASE = ../../../../bsp
BOARD = coreplexip-e31-arty

GCC		= $(CCPATH)/$(TARGET)-gcc
OBJCOPY	= $(CCPATH)/$(TARGET)-objcopy
OBJDUMP	= $(CCPATH)/$(TARGET)-objdump
AR		= $(CCPATH)/$(TARGET)-ar
RANLIB	= $(CCPATH)/$(TARGET)-ranlib
SIZE    = $(CCPATH)/$(TARGET)-size 
GDB    	= $(CCPATH)/$(TARGET)-gdb

FREERTOS_SOURCE_DIR	= ../../Source
CC_OPTS = -mabi=ilp32 -g3 -gdwarf-2 -march=rv32imac
PROG	= RISCV_E31Arty_GCC
#-----------------------------------------------------------
RISCV_OPENOCD = $(fesdk_builddir)/openocd/prefix/bin/openocd


