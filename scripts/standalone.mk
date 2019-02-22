#############################################################
# Makefile Arguments
#############################################################

# BSP_DIR sets the path to the target-specific board support package.
BSP_DIR ?= $(abspath bsp)
# SRC_DIR sets the path to the program source directory
SRC_DIR ?= $(abspath src)

#############################################################
# BSP loading
#############################################################

# There must be a settings makefile fragment in the BSP's board directory.
ifeq ($(wildcard $(BSP_DIR)/settings.mk),)
$(error Unable to find BSP for $(TARGET), expected to find $(BSP_DIR)/settings.mk)
endif

# Include the BSP settings
include $(BSP_DIR)/settings.mk

# Check that settings.mk sets RISCV_ARCH and RISCV_ABI
ifeq ($(RISCV_ARCH),)
$(error $(BSP_DIR)/board.mk must set RISCV_ARCH, the RISC-V ISA string to target)
endif

ifeq ($(RISCV_ABI),)
$(error $(BSP_DIR)/board.mk must set RISCV_ABI, the ABI to target)
endif

# Determines the XLEN from the toolchain tuple
ifeq ($(patsubst rv32%,rv32,$(RISCV_ARCH)),rv32)
RISCV_XLEN := 32
else ifeq ($(patsubst rv64%,rv64,$(RISCV_ARCH)),rv64)
RISCV_XLEN := 64
else
$(error Unable to determine XLEN from $(RISCV_ARCH))
endif

#############################################################
# Toolchain
#############################################################

# Allow users to select a different cross compiler.
CROSS_COMPILE ?= riscv64-unknown-elf

# If users don't specify RISCV_PATH then assume that the tools will just be in
# their path.
ifeq ($(RISCV_PATH),)
RISCV_GCC     := $(CROSS_COMPILE)-gcc
RISCV_GXX     := $(CROSS_COMPILE)-g++
RISCV_OBJDUMP := $(CROSS_COMPILE)-objdump
RISCV_GDB     := $(CROSS_COMPILE)-gdb
RISCV_AR      := $(CROSS_COMPILE)-ar
RISCV_SIZE    := $(CROSS_COMPILE)-size
else
RISCV_GCC     := $(abspath $(RISCV_PATH)/bin/$(CROSS_COMPILE)-gcc)
RISCV_GXX     := $(abspath $(RISCV_PATH)/bin/$(CROSS_COMPILE)-g++)
RISCV_OBJDUMP := $(abspath $(RISCV_PATH)/bin/$(CROSS_COMPILE)-objdump)
RISCV_GDB     := $(abspath $(RISCV_PATH)/bin/$(CROSS_COMPILE)-gdb)
RISCV_AR      := $(abspath $(RISCV_PATH)/bin/$(CROSS_COMPILE)-ar)
RISCV_SIZE    := $(abspath $(RISCV_PATH)/bin/$(CROSS_COMPILE)-size)
PATH          := $(abspath $(RISCV_PATH)/bin):$(PATH)
endif

#############################################################
# Software
#############################################################

ifneq ($(BSP),legacy)

PROGRAM_ELF ?= $(SRC_DIR)/$(PROGRAM)

.PHONY: all
all: software

.PHONY: software
software: $(PROGRAM_ELF)

ifneq ($(COREIP_MEM_WIDTH),)
software: $(PROGRAM_HEX)
endif

PROGRAM_SRCS = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/*.h) $(wildcard $(SRC_DIR)/*.S)

$(PROGRAM_ELF): \
		$(PROGRAM_SRCS) \
		$(BSP_DIR)/install/lib/libmetal.a \
		$(BSP_DIR)/install/lib/libmetal-gloss.a \
		$(BSP_DIR)/metal.lds
	$(MAKE) -C $(dir $@) $(notdir $@) \
		AR=$(RISCV_AR) \
		CC=$(RISCV_GCC) \
		CXX=$(RISCV_GXX) \
		CFLAGS="-Os -march=$(RISCV_ARCH) -mabi=$(RISCV_ABI) -g -mcmodel=medany -I$(abspath $(BSP_DIR)/install/include/)" \
		CXXFLAGS="-Os -march=$(RISCV_ARCH) -mabi=$(RISCV_ABI) -g -mcmodel=medany -I$(abspath $(BSP_DIR)/install/include/)" \
		LDFLAGS="-nostartfiles -nostdlib -L$(sort $(dir $(abspath $(filter %.a,$^)))) -T$(abspath $(filter %.lds,$^))" \
		LDLIBS="-Wl,--start-group -lc -lgcc -lmetal -lmetal-gloss -Wl,--end-group"
	touch -c $@

	$(RISCV_SIZE) $@

.PHONY: clean-software
clean-software:
	$(MAKE) -C $(SRC_DIR) clean
clean: clean-software

endif # BSP != legacy

