#############################################################
# Makefile Arguments
#############################################################

# ROOT_DIR sets the root directory of Freedom E SDK or standalone project
ROOT_DIR ?= $(abspath .)
# BSP_DIR sets the path to the target-specific board support package.
BSP_DIR ?= $(abspath bsp)
# SRC_DIR sets the path to the program source directory
SRC_DIR ?= $(abspath src)
# FREERTOS_SOURCE_PATH sets the path to the FreeRTOS source directory
export FREERTOS_SOURCE_PATH = $(abspath FreeRTOS-metal)
# Set FREEDOM_E_SDK_VENV_PATH to use a project-local virtualenv
export FREEDOM_E_SDK_VENV_PATH ?=  $(abspath .)/venv
# Set FREERTOS_METAL_VENV_PATH to use same venv as FREEDOM_E_SDK_VENV_PATH
export FREERTOS_METAL_VENV_PATH ?= $(FREEDOM_E_SDK_VENV_PATH)
# SYSTEMVIEW_SOURCE_PATH sets the path to the SEGGER SystemView source directory
export SYSTEMVIEW_SOURCE_PATH = $(abspath Segger_SystemView-metal)
# SCL_SOURCE_PATH sets the path to the SCL source directory
export SCL_SOURCE_PATH = $(abspath scl-metal)

export FREEDOM_METAL=$(abspath freedom-metal)

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

ifeq ($(RISCV_CMODEL),)
RISCV_CMODEL = medany
endif

ifeq ($(RISCV_LIBC),)
RISCV_LIBC=nano
endif

ifeq ($(RISCV_LIBC),nano)
SPEC=nano
include $(FREEDOM_METAL)/metal_nano.make
endif

ifeq ($(RISCV_LIBC),picolibc)
SPEC=picolibc
include $(FREEDOM_METAL)/metal_pico.make
endif

ifeq ($(SPEC),)
$(error RISCV_LIBC set to an unsupported value: $(RISCV_LIBC))
endif

ifeq ($(findstring dhrystone,$(PROGRAM)),dhrystone)
ifeq ($(LINK_TARGET),)
  ifneq ($(TARGET),freedom-e310-arty)
  ifneq ($(TARGET),sifive-hifive1)
  ifneq ($(TARGET),sifive-hifive1-revb)
    LINK_TARGET = ramrodata
  endif
  endif
  endif
endif
endif

ifeq ($(findstring coremark,$(PROGRAM)),coremark)
ifeq ($(LINK_TARGET),)
LINK_TARGET = ramrodata
endif
endif

ifneq ($(findstring freertos,$(PROGRAM)),)
ifeq ($(LINK_TARGET),)
LINK_TARGET = freertos
endif
endif

ifeq ($(LINK_TARGET),)
LINK_TARGET = default
endif

# Determines the XLEN from the toolchain tuple
ifeq ($(patsubst rv32%,rv32,$(RISCV_ARCH)),rv32)
RISCV_XLEN := 32
else ifeq ($(patsubst rv64%,rv64,$(RISCV_ARCH)),rv64)
RISCV_XLEN := 64
else
$(error Unable to determine XLEN from $(RISCV_ARCH))
endif

MTIME_RATE_HZ_DEF=32768
ifeq ($(findstring qemu,$(TARGET)),qemu)
MTIME_RATE_HZ_DEF=10000000
else
ifeq ($(findstring unleashed,$(TARGET)),unleashed)
MTIME_RATE_HZ_DEF=1000000
endif
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
RISCV_OBJCOPY := $(CROSS_COMPILE)-objcopy
RISCV_GDB     := $(CROSS_COMPILE)-gdb
RISCV_AR      := $(CROSS_COMPILE)-ar
RISCV_SIZE    := $(CROSS_COMPILE)-size
else
RISCV_GCC     := $(abspath $(RISCV_PATH)/bin/$(CROSS_COMPILE)-gcc)
RISCV_GXX     := $(abspath $(RISCV_PATH)/bin/$(CROSS_COMPILE)-g++)
RISCV_OBJDUMP := $(abspath $(RISCV_PATH)/bin/$(CROSS_COMPILE)-objdump)
RISCV_OBJCOPY := $(abspath $(RISCV_PATH)/bin/$(CROSS_COMPILE)-objcopy)
RISCV_GDB     := $(abspath $(RISCV_PATH)/bin/$(CROSS_COMPILE)-gdb)
RISCV_AR      := $(abspath $(RISCV_PATH)/bin/$(CROSS_COMPILE)-ar)
RISCV_SIZE    := $(abspath $(RISCV_PATH)/bin/$(CROSS_COMPILE)-size)
PATH          := $(abspath $(RISCV_PATH)/bin):$(PATH)
endif

SEGGER_JLINK_EXE := JLinkExe
SEGGER_JLINK_GDB_SERVER := JLinkGDBServer

QEMU_RISCV32 = qemu-system-riscv32
QEMU_RISCV64 = qemu-system-riscv64

#############################################################
# Software Flags
#############################################################

# Set the arch, ABI, and code model
RISCV_CCASFLAGS += -march=$(RISCV_ARCH) -mabi=$(RISCV_ABI) -mcmodel=$(RISCV_CMODEL)
RISCV_CFLAGS    += -march=$(RISCV_ARCH) -mabi=$(RISCV_ABI) -mcmodel=$(RISCV_CMODEL)
RISCV_CXXFLAGS  += -march=$(RISCV_ARCH) -mabi=$(RISCV_ABI) -mcmodel=$(RISCV_CMODEL)
RISCV_ASFLAGS   += -march=$(RISCV_ARCH) -mabi=$(RISCV_ABI) -mcmodel=$(RISCV_CMODEL)
# Prune unused functions and data
ifeq ($(RISCV_SERIES),sifive-8-series)
ifeq ($(findstring dhrystone,$(PROGRAM)),dhrystone)
RISCV_CFLAGS   += -fno-function-sections -fno-data-sections
RISCV_CXXFLAGS += -fno-function-sections -fno-data-sections
else
RISCV_CFLAGS   += -ffunction-sections -fdata-sections
RISCV_CXXFLAGS += -ffunction-sections -fdata-sections
endif
else
RISCV_CFLAGS   += -ffunction-sections -fdata-sections
RISCV_CXXFLAGS += -ffunction-sections -fdata-sections
endif
# Include the Metal headers
RISCV_CCASFLAGS += -I$(abspath $(FREEDOM_METAL))
RISCV_CFLAGS    += -I$(abspath $(FREEDOM_METAL))
RISCV_CXXFLAGS  += -I$(abspath $(FREEDOM_METAL))
# Reference selected library
RISCV_ASFLAGS   += --specs=$(SPEC).specs
RISCV_CCASFLAGS += --specs=$(SPEC).specs
RISCV_CFLAGS    += --specs=$(SPEC).specs
RISCV_CXXFLAGS  += --specs=$(SPEC).specs
# Set the MTIME frequency
RISCV_CFLAGS    += -DMTIME_RATE_HZ_DEF=$(MTIME_RATE_HZ_DEF)
RISCV_CXXFLAGS  += -DMTIME_RATE_HZ_DEF=$(MTIME_RATE_HZ_DEF)

# Turn on garbage collection for unused sections
RISCV_LDFLAGS += -Wl,--gc-sections
# Turn on linker map file generation
RISCV_LDFLAGS += -Wl,-Map,$(PROGRAM).map
# Turn off the C standard library
RISCV_LDFLAGS += -nostartfiles -nostdlib
# Find the archive files and linker scripts
RISCV_LDFLAGS += -T$(abspath $(filter %.lds,$^))

# Link to the relevant libraries
RISCV_LDLIBS += -Wl,--start-group -lc -lgcc -lm -Wl,--end-group

# Load the configuration Makefile
CONFIGURATION_FILE = $(wildcard $(CONFIGURATION).mk)
ifeq ($(words $(CONFIGURATION_FILE)),0)
$(error Unable to find the Makefile $(CONFIGURATION).mk for CONFIGURATION=$(CONFIGURATION))
endif
include $(CONFIGURATION).mk

# Benchmark CFLAGS go after loading the CONFIGURATION so that they can override the optimization level

ifeq ($(findstring dhrystone,$(PROGRAM)),dhrystone)
ifeq ($(DHRY_OPTION),)
# Ground rules (default)
RISCV_XCFLAGS += -mexplicit-relocs -fno-inline
else ifeq ($(DHRY_OPTION),fast)
# With inline and without lto
RISCV_XCFLAGS += -mexplicit-relocs -finline
else ifeq ($(DHRY_OPTION),best)
# Best Score
RISCV_XCFLAGS += -finline -flto -fwhole-program
endif
RISCV_XCFLAGS += -DDHRY_ITERS=$(TARGET_DHRY_ITERS)
endif

ifeq ($(findstring coremark,$(PROGRAM)),coremark)
ifeq ($(RISCV_SERIES),sifive-8-series)
# 8-series currently uses 7-series mtune, but this may change
RISCV_XCFLAGS += -O2 -fno-common -funroll-loops -finline-functions -funroll-all-loops --param max-inline-insns-auto=20 -falign-functions=8 -falign-jumps=8 -falign-loops=8 --param inline-min-speedup=10 -mtune=sifive-7-series -ffast-math
endif
ifeq ($(RISCV_SERIES),sifive-7-series)
RISCV_XCFLAGS += -O2 -fno-common -funroll-loops -finline-functions -funroll-all-loops --param max-inline-insns-auto=20 -falign-functions=8 -falign-jumps=8 -falign-loops=8 --param inline-min-speedup=10 -mtune=sifive-7-series -ffast-math
endif
ifneq ($(RISCV_SERIES),sifive-8-series)
ifneq ($(RISCV_SERIES),sifive-7-series)
ifeq ($(RISCV_XLEN),32)
RISCV_XCFLAGS += -O2 -fno-common -funroll-loops -finline-functions -falign-functions=16 -falign-jumps=4 -falign-loops=4 -finline-limit=1000 -fno-if-conversion2 -fselective-scheduling -fno-tree-dominator-opts -fno-reg-struct-return -fno-rename-registers --param case-values-threshold=8 -fno-crossjumping -freorder-blocks-and-partition -fno-tree-loop-if-convert -fno-tree-sink -fgcse-sm -fno-strict-overflow
else
RISCV_XCFLAGS += -O2 -fno-common -funroll-loops -finline-functions -falign-functions=16 -falign-jumps=4 -falign-loops=4 -finline-limit=1000 -fno-if-conversion2 -fselective-scheduling -fno-tree-dominator-opts
endif
endif
endif
RISCV_XCFLAGS += -DITERATIONS=$(TARGET_CORE_ITERS)
endif

ifeq ($(findstring freertos,$(PROGRAM)),freertos)
RISCV_XCFLAGS += -DWAIT_MS=$(TARGET_FREERTOS_WAIT_MS)
endif

ifneq ($(filter rtl,$(TARGET_TAGS)),)
RISCV_XCFLAGS += -DHCA_BYPASS_TRNG
endif

# A method to pass cycle delay
RISCV_XCFLAGS += -DMETAL_WAIT_CYCLE=$(TARGET_INTR_WAIT_CYCLE)

#############################################################
# Software
#############################################################

PROGRAM_ELF ?= $(SRC_DIR)/$(CONFIGURATION)/$(PROGRAM).elf
PROGRAM_HEX ?= $(SRC_DIR)/$(CONFIGURATION)/$(PROGRAM).hex
PROGRAM_LST ?= $(SRC_DIR)/$(CONFIGURATION)/$(PROGRAM).lst

.PHONY: all
all: software

.PHONY: software
software: $(PROGRAM_ELF)

software: $(PROGRAM_HEX)

PROGRAM_SRCS = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/*.h) $(wildcard $(SRC_DIR)/*.S)

$(PROGRAM_ELF): \
		$(PROGRAM_SRCS) \
		$(METAL_SRC) $(METAL_HELPER_SRC) \
		$(BSP_DIR)/metal.$(LINK_TARGET).lds
	mkdir -p $(dir $@)
	$(MAKE) $(METAL_MK)
	$(MAKE) -C $(SRC_DIR) $(basename $(notdir $@)) \
		PORT_DIR=$(PORT_DIR) \
		PROGRAM=$(PROGRAM) \
		AR=$(RISCV_AR) \
		CC=$(RISCV_GCC) \
		CXX=$(RISCV_GXX) \
		ASFLAGS="$(RISCV_ASFLAGS)" \
		CCASFLAGS="$(RISCV_CCASFLAGS)" \
		CFLAGS="$(RISCV_CFLAGS)" \
		CXXFLAGS="$(RISCV_CXXFLAGS)" \
		XCFLAGS="$(RISCV_XCFLAGS)" \
		LDFLAGS="$(RISCV_LDFLAGS)" \
		LDLIBS="$(METAL_SRC) $(METAL_HELPER_SRC) $(RISCV_LDLIBS)" \
		FREERTOS_METAL_VENV_PATH="$(FREERTOS_METAL_VENV_PATH)"
	mv $(SRC_DIR)/$(basename $(notdir $@)) $@
	mv $(SRC_DIR)/$(basename $(notdir $@)).map $(dir $@)
	touch -c $@
	$(RISCV_OBJDUMP) --source --all-headers --demangle --line-numbers --wide $@ > $(PROGRAM_LST)
	$(RISCV_SIZE) $@

# Use elf2hex if we're creating a hex file for RTL simulation
ifneq ($(filter rtl,$(TARGET_TAGS)),)
.PHONY: software
$(PROGRAM_HEX): \
		scripts/elf2hex/install/bin/$(CROSS_COMPILE)-elf2hex \
		$(PROGRAM_ELF)
	$< --output $@ --input $(PROGRAM_ELF) --bit-width $(COREIP_MEM_WIDTH)
else
$(PROGRAM_HEX): \
		$(PROGRAM_ELF)
	$(RISCV_OBJCOPY) -O ihex $(PROGRAM_ELF) $@
endif

.PHONY: clean-software
clean-software:
	$(MAKE) -C $(SRC_DIR) PORT_DIR=$(PORT_DIR) clean
	rm -rf $(SRC_DIR)/$(CONFIGURATION)
.PHONY: clean
clean: clean-software

#############################################################
# Metal Code Generation
#############################################################

ifneq ($(wildcard $(BSP_DIR)/metal.mk),)
# If the BSP has metal.mk, use the pregenerated code
METAL_MK = $(BSP_DIR)/metal.mk
else
# If the BSP does not have metal.mk, we'll be generating the
# Freedom Metal sources on a per-application basis, potentially
# with a per-application config.
APPLICATION_CONFIG = $(wildcard $(SRC_DIR)/*.ini)
ifneq ($(APPLICATION_CONFIG),)
METAL_CODEGEN_FLAGS += --application-config $(APPLICATION_CONFIG)
endif

METAL_MK = $(SRC_DIR)/$(CONFIGURATION)/metal.mk

$(METAL_MK): $(FREEDOM_E_SDK_VENV_PATH)/.stamp $(APPLICATION_CONFIG) $(METAL_MK_DEPEND)
	@mkdir -p $(dir $@)
	. $(FREEDOM_E_SDK_VENV_PATH)/bin/activate && \
	  python3 $(FREEDOM_METAL)/scripts/codegen.py \
	    --dts $(BSP_DIR)/design.dts \
	    --source-paths freedom-metal freedom-metal/sifive-blocks \
	    --output-dir $(shell realpath $(dir $@) --relative-to=$(ROOT_DIR)) \
	    $(METAL_CODEGEN_FLAGS)
	@touch $@
endif

include $(METAL_MK)

$(METAL_SRC): $(METAL_MK)
$(METAL_HELPER_SRC): $(METAL_MK)

RISCV_CFLAGS += -I$(dir $(METAL_MK)) $(METAL_CFLAGS) $(METAL_HELPER_CFLAGS)
RISCV_CXX_FLAGS += -I$(dir $(METAL_MK)) $(METAL_CFLAGS) $(METAL_HELPER_CFLAGS)

#############################################################
# Metal BSP Support Files
#############################################################

OVERLAY_GENERATOR = scripts/devicetree-overlay-generator/generate_overlay.py
LDSCRIPT_GENERATOR = scripts/ldscript-generator/generate_ldscript.py
CMSIS_SVD_GENERATOR = scripts/cmsis-svd-generator/generate_svd.py
SETTINGS_GENERATOR = scripts/esdk-settings-generator/generate_settings.py

$(BSP_DIR)/design.dts: $(BSP_DIR)/core.dts $(OVERLAY_GENERATOR)
	$(MAKE) -f scripts/virtualenv.mk virtualenv
	. $(FREEDOM_E_SDK_VENV_PATH)/bin/activate && $(OVERLAY_GENERATOR) --type $(TARGET) --output $@ --rename-include $(notdir $<) $<

$(BSP_DIR)/metal.default.lds: $(BSP_DIR)/design.dts $(LDSCRIPT_GENERATOR)
	$(MAKE) -f scripts/virtualenv.mk virtualenv
	. $(FREEDOM_E_SDK_VENV_PATH)/bin/activate && $(LDSCRIPT_GENERATOR) -d $< -o $@

$(BSP_DIR)/metal.ramrodata.lds: $(BSP_DIR)/design.dts $(LDSCRIPT_GENERATOR)
	$(MAKE) -f scripts/virtualenv.mk virtualenv
	. $(FREEDOM_E_SDK_VENV_PATH)/bin/activate && $(LDSCRIPT_GENERATOR) -d $< -o $@ --ramrodata

$(BSP_DIR)/metal.scratchpad.lds: $(BSP_DIR)/design.dts $(LDSCRIPT_GENERATOR)
	$(MAKE) -f scripts/virtualenv.mk virtualenv
	. $(FREEDOM_E_SDK_VENV_PATH)/bin/activate && $(LDSCRIPT_GENERATOR) -d $< -o $@ --scratchpad

$(BSP_DIR)/metal.freertos.lds: $(BSP_DIR)/design.dts $(LDSCRIPT_GENERATOR)
	$(MAKE) -f scripts/virtualenv.mk virtualenv
	. $(FREEDOM_E_SDK_VENV_PATH)/bin/activate && $(LDSCRIPT_GENERATOR) -d $< -o $@ --freertos

$(BSP_DIR)/design.svd: $(BSP_DIR)/design.dts $(CMSIS_SVD_GENERATOR)
	$(MAKE) -f scripts/virtualenv.mk virtualenv
	. $(FREEDOM_E_SDK_VENV_PATH)/bin/activate && $(CMSIS_SVD_GENERATOR) -d $< -o $@

$(BSP_DIR)/settings.mk: $(BSP_DIR)/design.dts $(SETTINGS_GENERATOR)
	$(MAKE) -f scripts/virtualenv.mk virtualenv
	. $(FREEDOM_E_SDK_VENV_PATH)/bin/activate && $(SETTINGS_GENERATOR) -d $< -o $@ -t $(TARGET)

ifeq ($(findstring spike,$(TARGET)),spike)
$(BSP_DIR)/spike_options.sh:
	echo "export SPIKE_OPTIONS=\"\"" > $@

ifneq ($(shell which spike),)
$(BSP_DIR)/core.dts: $(BSP_DIR)/spike_options.sh
	. $< && scripts/spikedts $@
endif # which spike
endif # findstring spike,$(TARGET)

.PHONY: bsp
metal-bsp:\
	   $(BSP_DIR)/metal.default.lds \
	   $(BSP_DIR)/metal.ramrodata.lds \
	   $(BSP_DIR)/metal.scratchpad.lds \
	   $(BSP_DIR)/metal.freertos.lds \
	   $(BSP_DIR)/settings.mk

#############################################################
# elf2hex
#############################################################
scripts/elf2hex/build/Makefile: scripts/elf2hex/configure
	@rm -rf $(dir $@)
	@mkdir -p $(dir $@)
	cd $(dir $@); \
		$(abspath $<) \
		--prefix=$(abspath $(dir $<))/install \
		--target=$(CROSS_COMPILE)

scripts/elf2hex/install/bin/$(CROSS_COMPILE)-elf2hex: scripts/elf2hex/build/Makefile
	$(MAKE) -C $(dir $<) install
	touch -c $@

.PHONY: clean-elf2hex
clean-elf2hex:
	rm -rf scripts/elf2hex/build scripts/elf2hex/install
clean: clean-elf2hex

##############################################################
# Virtualenv Script Include
##############################################################

include scripts/virtualenv.mk
