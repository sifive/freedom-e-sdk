#############################################################
# Configuration
#############################################################

# Allows users to create Makefile.local or ../Makefile.project with
# configuration variables, so they don't have to be set on the command-line
# every time.
extra_configs := $(wildcard Makefile.local ../Makefile.project)
ifneq ($(extra_configs),)
$(info Obtaining additional make variables from $(extra_configs))
include $(extra_configs)
endif

# Select Legacy BSP or Freedom Metal BSP
# Allowed values are 'legacy' and 'metal'
BSP ?= legacy

# Use BOARD as a synonym for TARGET
ifneq ($(BOARD),)
TARGET ?= $(BOARD)
endif

ifeq ($(BSP),legacy)
BSP_SUBDIR ?= env
TARGET ?= freedom-e300-hifive1
PROGRAM ?= demo_gpio
LINK_TARGET ?= flash
GDB_PORT ?= 3333

else # MEE
override BSP = metal
BSP_SUBDIR ?= 
PROGRAM ?= hello
TARGET ?= sifive-hifive1

endif # $(BSP)

TARGET_ROOT ?= $(abspath .)
PROGRAM_ROOT ?= $(abspath .)

SRC_DIR = $(PROGRAM_ROOT)/software/$(PROGRAM)

PROGRAM_ELF = $(SRC_DIR)/$(PROGRAM)
PROGRAM_HEX = $(SRC_DIR)/$(PROGRAM).hex

#############################################################
# BSP Loading
#############################################################

# Finds the directory in which this BSP is located, ensuring that there is
# exactly one.
BSP_DIR := $(wildcard $(TARGET_ROOT)/bsp/$(BSP_SUBDIR)/$(TARGET))
ifeq ($(words $(BSP_DIR)),0)
$(error Unable to find BSP for $(TARGET), expected to find either "bsp/$(TARGET)" or "bsp-addons/$(TARGET)")
endif
ifneq ($(words $(BSP_DIR)),1)
$(error Found multiple BSPs for $(TARGET): "$(BSP_DIR)")
endif

#############################################################
# Standalone Script Include
#############################################################

# The standalone script is included here because it needs $(SRC_DIR) and
# $(BSP_DIR) to be set.
#
# The standalone Makefile handles the following tasks:
#  - Including $(BSP_DIR)/settings.mk and validating RISCV_ARCH, RISCV_ABI
#  - Setting the toolchain path with CROSS_COMPILE and RISCV_PATH
#  - Providing the software and $(PROGRAM_ELF) Make targets for the MEE

include scripts/standalone.mk

#############################################################
# Prints help message
#############################################################
.PHONY: help
help:
	@echo " SiFive Freedom E Software Development Kit "
	@echo " Makefile targets:"
	@echo ""
	@echo " software BSP=metal [PROGRAM=$(PROGRAM) TARGET=$(TARGET)]:"
	@echo "    Build a software program to load with the"
	@echo "    debugger."
	@echo ""
	@echo " metal BSP=metal [TARGET=$(TARGET)]"
	@echo "    Build the MEE library for TARGET"
	@echo ""
	@echo " clean BSP=metal [PROGRAM=$(PROGRAM) TARGET=$(TARGET)]:"
	@echo "    Clean compiled objects for a specified "
	@echo "    software program."
	@echo ""
	@echo " upload BSP=metal [PROGRAM=$(PROGRAM) TARGET=$(TARGET)]:"
	@echo "    Launch OpenOCD to flash your program to the"
	@echo "    on-board Flash."
	@echo ""
	@echo " debug BSP=metal [PROGRAM=$(PROGRAM) TARGET=$(TARGET)]:"
	@echo "    Launch OpenOCD and attach GDB to the running program."
	@echo ""
	@echo " standalone BSP=metal STANDALONE_DEST=/path/to/desired/location"
	@echo "            [PROGRAM=$(PROGRAM) TARGET=$(TARGET)]:"
	@echo "    Export a program for a single target into a standalone"
	@echo "    project directory at STANDALONE_DEST."
	@echo ""
	@echo " For more information, read the accompanying README.md"

.PHONY: clean
clean:

#############################################################
# Enumerate MEE BSPs and Programs
#
# List all available MEE boards and programs in a form that 
# Freedom Studio knows how to parse.  Do not change the 
# format or fixed text of the output without consulting the 
# Freedom Studio dev team.
#############################################################
ifeq ($(BSP),metal)

# MEE boards are any folders that aren't the Legacy BSP or update-targets.sh
EXCLUDE_TARGET_DIRS = drivers env include libwrap update-targets.sh
list-targets:
	@echo bsp-list: $(sort $(filter-out $(EXCLUDE_TARGET_DIRS),$(notdir $(wildcard bsp/*))))

# MEE programs are any submodules in the software folder
list-programs:
	@echo program-list: $(shell grep -o '= software/.*$$' .gitmodules | sed 's/.*\///')

list-options: list-programs list-targets

endif

#############################################################
# Import rules to build Freedom Metal
#############################################################
ifeq ($(BSP),metal)
include scripts/libmetal.mk
endif

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

#############################################################
# Standalone Project Export
#############################################################

ifeq ($(BSP),metal)
ifeq ($(STANDALONE_DEST),)
standalone:
	$(error Please provide STANDALONE_DEST to create a standalone project)
else

$(STANDALONE_DEST):
$(STANDALONE_DEST)/%:
	mkdir -p $@

# We have to use $$(shell ls ...) in this recipe instead of $$(wildcard) so that we
# pick up $$(BSP_DIR)/install
standalone: \
		$(STANDALONE_DEST) \
		$(STANDALONE_DEST)/bsp \
		$(STANDALONE_DEST)/src \
		$(BSP_DIR)/install/lib/libmetal.a \
		$(BSP_DIR)/install/lib/libmetal-gloss.a \
		$(SRC_DIR) \
		scripts/standalone.mk
	cp -r $(addprefix $(BSP_DIR)/,$(filter-out build,$(shell ls $(BSP_DIR)))) $</bsp/

	$(MAKE) -C $(SRC_DIR) clean
	cp -r $(SRC_DIR)/* $</src/

	echo "PROGRAM = $(PROGRAM)" > $</Makefile
	cat scripts/standalone.mk >> $</Makefile
endif
endif

#############################################################
# MEE Software Compilation
#############################################################

# Generation of $(PROGRAM_ELF) is handled by scripts/standalone.mk
# In this top level Makefile, just describe how to turn the elf into
# $(PROGRAM_HEX)

ifeq ($(BSP),metal)
$(PROGRAM_HEX): \
		scripts/elf2hex/install/bin/$(CROSS_COMPILE)-elf2hex \
		$(PROGRAM_ELF)
	$< --output $@ --input $(PROGRAM_ELF) --bit-width $(COREIP_MEM_WIDTH)
endif

#############################################################
# Legacy Software Compilation
#############################################################

ifeq ($(BSP),legacy)
PROGRAM_DIR=$(dir $(PROGRAM_ELF))

.PHONY: software_clean
clean: software_clean
software_clean:
	$(MAKE) -C $(PROGRAM_DIR) CC=$(RISCV_GCC) RISCV_ARCH=$(RISCV_ARCH) RISCV_ABI=$(RISCV_ABI) AR=$(RISCV_AR) BSP_BASE=$(abspath bsp) TARGET=$(TARGET) LINK_TARGET=$(LINK_TARGET) clean

.PHONY: software
software: software_clean
	$(MAKE) -C $(PROGRAM_DIR) CC=$(RISCV_GCC) RISCV_ARCH=$(RISCV_ARCH) RISCV_ABI=$(RISCV_ABI) AR=$(RISCV_AR) BSP_BASE=$(abspath bsp) TARGET=$(TARGET) LINK_TARGET=$(LINK_TARGET)

dasm: software $(RISCV_OBJDUMP)
	$(RISCV_OBJDUMP) -D $(PROGRAM_ELF)
endif

#############################################################
# Upload and Debug
#############################################################

ifneq ($(RISCV_OPENOCD_PATH),)
RISCV_OPENOCD=$(RISCV_OPENOCD_PATH)/bin/openocd
else
#if RISCV_OPENOCD_PATH is not set, just look on the PATH
RISCV_OPENOCD=openocd
endif

ifeq ($(BSP),metal)

upload: $(PROGRAM_ELF)
	scripts/upload --elf $(PROGRAM_ELF) --openocd $(RISCV_OPENOCD) --gdb $(RISCV_GDB) --openocd-config bsp/$(TARGET)/openocd.cfg

debug: $(PROGRAM_ELF)
	scripts/debug --elf $(PROGRAM_ELF) --openocd $(RISCV_OPENOCD) --gdb $(RISCV_GDB) --openocd-config bsp/$(TARGET)/openocd.cfg

else # BSP != metal

OPENOCDCFG ?= bsp/env/$(TARGET)/openocd.cfg
OPENOCDARGS += -f $(OPENOCDCFG)

GDB_UPLOAD_ARGS ?= --batch

GDB_UPLOAD_CMDS += -ex "set remotetimeout 240"
GDB_UPLOAD_CMDS += -ex "target extended-remote localhost:$(GDB_PORT)"
GDB_UPLOAD_CMDS += -ex "monitor reset halt"
GDB_UPLOAD_CMDS += -ex "monitor flash protect 0 64 last off"
GDB_UPLOAD_CMDS += -ex "load"
GDB_UPLOAD_CMDS += -ex "monitor resume"
GDB_UPLOAD_CMDS += -ex "monitor shutdown"
GDB_UPLOAD_CMDS += -ex "quit"

upload:
	$(RISCV_OPENOCD) $(OPENOCDARGS) & \
	$(RISCV_GDB) $(PROGRAM_DIR)/$(PROGRAM) $(GDB_UPLOAD_ARGS) $(GDB_UPLOAD_CMDS) && \
	echo "Successfully uploaded '$(PROGRAM)' to $(TARGET)."

#############################################################
# This Section is for launching the debugger
#############################################################

run_openocd:
	$(RISCV_OPENOCD) $(OPENOCDARGS)

GDBCMDS += -ex "set remotetimeout 240"
GDBCMDS += -ex "target extended-remote localhost:$(GDB_PORT)"

run_gdb:
	$(RISCV_GDB) $(PROGRAM_DIR)/$(PROGRAM) $(GDBARGS) $(GDBCMDS)

endif # BSP == metal
