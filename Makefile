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

# Allow BOARD as a synonym for TARGET
ifneq ($(BOARD),)
TARGET ?= $(BOARD)
endif

# Default PROGRAM and TARGET
PROGRAM ?= hello
TARGET ?= sifive-hifive1

TARGET_ROOT  ?= $(abspath .)
PROGRAM_ROOT ?= $(abspath .)

SRC_DIR = $(PROGRAM_ROOT)/software/$(PROGRAM)

PROGRAM_ELF = $(SRC_DIR)/$(CONFIGURATION)/$(PROGRAM).elf
PROGRAM_HEX = $(SRC_DIR)/$(CONFIGURATION)/$(PROGRAM).hex

#############################################################
# BSP Loading
#############################################################

# Finds the directory in which this BSP is located, ensuring that there is
# exactly one.
BSP_DIR := $(wildcard $(TARGET_ROOT)/bsp/$(TARGET))
ifeq ($(words $(BSP_DIR)),0)
$(error Unable to find BSP for $(TARGET), expected to find "bsp/$(TARGET)")
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
#  - Providing the software and $(PROGRAM_ELF) Make targets for Metal

include scripts/standalone.mk

#############################################################
# Prints help message
#############################################################
.PHONY: help
help:
	@echo " SiFive Freedom E Software Development Kit "
	@echo " Makefile targets:"
	@echo ""
	@echo " software [PROGRAM=$(PROGRAM)] [TARGET=$(TARGET)]"
	@echo "          [CONFIGURATION=$(CONFIGURATION)]:"
	@echo "    Builds the requested PROGRAM for the TARGET using the"
	@echo "    specified build CONFIGURATION."
	@echo ""
	@echo " metal [TARGET=$(TARGET)] [CONFIGURATION=$(CONFIGURATION)]"
	@echo "    Builds the Freedom Metal library for TARGET."
	@echo ""
	@echo " clean [PROGRAM=$(PROGRAM)] [TARGET=$(TARGET)]"
	@echo "       [CONFIGURATION=$(CONFIGURATION)]:"
	@echo "    Cleans compiled objects for a specified "
	@echo "    software program."
	@echo ""
	@echo " upload [PROGRAM=$(PROGRAM)] [TARGET=$(TARGET)]"
	@echo "        [CONFIGURATION=$(CONFIGURATION)]:"
	@echo "    For board and FPGA TARGETs, uploads the program to the"
	@echo "    on-board flash."
	@echo ""
	@echo " debug [PROGRAM=$(PROGRAM)] [TARGET=$(TARGET)]"
	@echo "       [CONFIGURATION=$(CONFIGURATION)]:"
	@echo "    For board and FPGA TARGETs, attaches GDB to the"
	@echo "    running program."
	@echo ""
	@echo " standalone STANDALONE_DEST=/path/to/desired/location"
	@echo "            [PROGRAM=$(PROGRAM)] [TARGET=$(TARGET)]:"
	@echo "    Exports a program for a single target into a standalone"
	@echo "    project directory at STANDALONE_DEST."
	@echo ""
	@echo " For more information, view the Freedom E SDK Documentation at"
	@echo "   https://sifive.github.io/freedom-e-sdk-docs/index.html"

.PHONY: clean
clean:

#############################################################
# Enumerate BSPs and Programs
#
# List all available boards and programs in a form that 
# Freedom Studio knows how to parse.  Do not change the 
# format or fixed text of the output without consulting the 
# Freedom Studio dev team.
#############################################################

# Find all settings.mk with TARGET_REQUIRE_TAGS in TARGET_TAGS
MATCHING_SETTINGS = $(shell scripts/filter-targets $(TARGET_ROOT)/bsp $(TARGET_REQUIRE_TAGS))

# Get the name of the containing directory of all matching settings.mk
MATCHING_TARGETS = $(patsubst $(TARGET_ROOT)/bsp/%/,%,$(dir $(MATCHING_SETTINGS)))

.PHONY: list-targets
list-targets:
	@echo bsp-list: $(sort $(MATCHING_TARGETS))

# Lists all available TARGET_TAGS
#
#  1. Find all settings.mk
#  2. Extract the TARGET_TAGS line
#  3. Extract the value of TARGET_TAGS
#  4. Split each tag onto a newline
#  5. Sort the lines
#  6. Find unique tags
#
.PHONY: list-target-tags
list-target-tags:
	@echo target-tags: $(shell find $(TARGET_ROOT)/bsp -name settings.mk | \
		xargs grep -he "TARGET_TAGS" | \
		sed -r 's/TARGET_TAGS.*=(.*)/\1/' | \
		tr ' ' '\n' | \
		sort | \
		uniq)

# Metal programs are any submodules in the software folder
.PHONY: list-programs
list-programs:
	@echo program-list: $(shell grep -o '= software/.*$$' .gitmodules | sed 's/.*\///')

.PHONY: list-options
list-options: list-programs list-targets

#############################################################
# Import rules to build Freedom Metal
#############################################################

include scripts/libmetal.mk

#############################################################
# Standalone Project Export
#############################################################

ifeq ($(STANDALONE_DEST),)
standalone:
	$(error Please provide STANDALONE_DEST to create a standalone project)
else # STANDALONE_DEST != ""

$(STANDALONE_DEST):
$(STANDALONE_DEST)/%:
	mkdir -p $@

ifneq ($(filter rtl,$(TARGET_TAGS)),)
# TARGETs with the "rtl" TARGET_TAG need elf2hex in their standalone project
standalone: \
		$(STANDALONE_DEST) \
		$(STANDALONE_DEST)/bsp \
		$(STANDALONE_DEST)/src \
		$(SRC_DIR) \
		freedom-metal \
		debug.mk \
		release.mk \
		scripts/elf2hex \
		scripts/standalone.mk \
		scripts/libmetal.mk
	cp -r $(addprefix $(BSP_DIR)/,$(filter-out build,$(shell ls $(BSP_DIR)))) $</bsp/

	cp -r freedom-metal $</

	find $</freedom-metal -name ".git*" | xargs rm

	mkdir -p $</scripts
	cp -r scripts/elf2hex $</scripts

	find $</scripts/elf2hex -name ".git*" | xargs rm

	$(MAKE) -C $(SRC_DIR) clean
	cp -r $(SRC_DIR)/* $</src/

	cp debug.mk $</debug.mk
	cp release.mk $</release.mk

	echo "PROGRAM = $(PROGRAM)" > $</Makefile
	cat scripts/standalone.mk >> $</Makefile
	cat scripts/libmetal.mk >> $</Makefile
else # "rtl" not in TARGET_TAGS
standalone: \
		$(STANDALONE_DEST) \
		$(STANDALONE_DEST)/bsp \
		$(STANDALONE_DEST)/src \
		$(SRC_DIR) \
		freedom-metal \
		debug.mk \
		release.mk \
		scripts/standalone.mk \
		scripts/libmetal.mk
	cp -r $(addprefix $(BSP_DIR)/,$(filter-out build,$(shell ls $(BSP_DIR)))) $</bsp/

	cp -r freedom-metal $</

	find $</freedom-metal -name ".git*" | xargs rm

	$(MAKE) -C $(SRC_DIR) clean
	cp -r $(SRC_DIR)/* $</src/

	cp debug.mk $</debug.mk
	cp release.mk $</release.mk

	echo "PROGRAM = $(PROGRAM)" > $</Makefile
	cat scripts/standalone.mk >> $</Makefile
	cat scripts/libmetal.mk >> $</Makefile
endif # rtl in TARGET_TAGS

endif # STANDALONE_DEST

#############################################################
# Upload and Debug
#############################################################

ifneq ($(RISCV_OPENOCD_PATH),)
RISCV_OPENOCD=$(RISCV_OPENOCD_PATH)/bin/openocd
else
#if RISCV_OPENOCD_PATH is not set, just look on the PATH
RISCV_OPENOCD=openocd
endif

ifneq ($(filter jlink,$(TARGET_TAGS)),)
upload: $(PROGRAM_HEX)
	scripts/upload --hex $(PROGRAM_HEX) --jlink $(SEGGER_JLINK_EXE)
else
upload: $(PROGRAM_ELF)
	scripts/upload --elf $(PROGRAM_ELF) --openocd $(RISCV_OPENOCD) --gdb $(RISCV_GDB) --openocd-config bsp/$(TARGET)/openocd.cfg
endif

ifneq ($(filter jlink,$(TARGET_TAGS)),)
debug: $(PROGRAM_ELF)
	scripts/debug --elf $(PROGRAM_ELF) --jlink $(SEGGER_JLINK_GDB_SERVER) --gdb $(RISCV_GDB)
else
debug: $(PROGRAM_ELF)
	scripts/debug --elf $(PROGRAM_ELF) --openocd $(RISCV_OPENOCD) --gdb $(RISCV_GDB) --openocd-config bsp/$(TARGET)/openocd.cfg
endif


