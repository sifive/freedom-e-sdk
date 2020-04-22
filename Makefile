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

TARGET_ROOT  ?= $(abspath .)
PROGRAM_ROOT ?= $(abspath .)

# Allow BOARD as a synonym for TARGET
ifneq ($(BOARD),)
TARGET ?= $(BOARD)
endif

# If the make command goal is any of the Freedom Studio goals
# then there is no need to include any of the other makefiles
# as we are not really building anything real.
ifeq ($(MAKECMDGOALS),standalone)
NO_INCLUDES = true
endif
ifeq ($(MAKECMDGOALS),list-targets)
NO_INCLUDES = true
endif
ifeq ($(MAKECMDGOALS),list-target-tags)
NO_INCLUDES = true
endif
ifeq ($(MAKECMDGOALS),list-programs)
NO_INCLUDES = true
endif
ifeq ($(MAKECMDGOALS),list-options)
NO_INCLUDES = true
endif

# Default PROGRAM and TARGET
PROGRAM ?= hello
TARGET ?= $(shell find $(TARGET_ROOT)/bsp/* -type d | head -n 1 | rev | cut -d '/' -f 1 | rev)

# The configuration defaults to Debug. Valid choices are:
#  - debug
#  - release
CONFIGURATION ?= debug

# Setup differences between host platforms
ifeq ($(OS),Windows_NT)
    SED_RE_FLAG = -r
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        SED_RE_FLAG = -r
    endif
    ifeq ($(UNAME_S),Darwin)
        SED_RE_FLAG = -E
    endif
endif

# Default to use relase configuration For Benchmark programs, like Coremark and Dhrystone.
ifeq ($(PROGRAM),dhrystone)
CONFIGURATION = release
endif

# Coremark require PORT_DIR set for different OS, freedom-metal for us!
ifeq ($(PROGRAM),coremark)
CONFIGURATION = release
ifeq ($(PORT_DIR),)
PORT_DIR = freedom-metal
endif
endif

SRC_DIR = $(PROGRAM_ROOT)/software/$(PROGRAM)

PROGRAM_ELF = $(SRC_DIR)/$(CONFIGURATION)/$(PROGRAM).elf
PROGRAM_HEX = $(SRC_DIR)/$(CONFIGURATION)/$(PROGRAM).hex
PROGRAM_LST = $(SRC_DIR)/$(CONFIGURATION)/$(PROGRAM).lst

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

ifeq ($(NO_INCLUDES),)
include scripts/standalone.mk
endif

##############################################################
# Virtualenv Script Include
##############################################################

ifeq ($(NO_INCLUDES),)
include scripts/virtualenv.mk
endif

#############################################################
# Help Script Include
#############################################################

include scripts/help.mk

help::
	@echo ""
	@echo " standalone STANDALONE_DEST=/path/to/desired/location"
	@echo "            [PROGRAM=$(PROGRAM)] [TARGET=$(TARGET)]:"
	@echo "    Exports a program for a single target into a standalone"
	@echo "    project directory at STANDALONE_DEST."


open-docs: scripts/open-docs
	$^ $(TARGET_ROOT)

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

#############################################################
# Prints freedostudio api version .  This version should be 
# incremented if the list-targets, list-target-tags.
# list-programs, list-options, or standalone targets change
# in any way that affects Freedom Studio requirements.
# A given version of Freedom Studio may not support 
# 'future' versions of freedom-e-sdk.  Backward support
# should be supported.
#############################################################
.PHONY: freedomstudio-api-version
freedomstudio-api-version:
	@echo 1.0

# Find all settings.mk with TARGET_REQUIRE_TAGS in TARGET_TAGS
# Freedom Studio uses this macro.  Changing this macro may break Freedom Studio's
# ability to create new projects.
MATCHING_SETTINGS = $(shell scripts/filter-targets $(TARGET_ROOT)/bsp $(TARGET_REQUIRE_TAGS))

# Get the name of the containing directory of all matching settings.mk
# Freedom Studio uses this macro.  Changing this macro may break Freedom Studio's
# ability to create new projects.
MATCHING_TARGETS = $(patsubst $(TARGET_ROOT)/bsp/%/,%,$(dir $(MATCHING_SETTINGS)))

# Freedom Studio uses this target.  Changing this target may break Freedom Studio's
# ability to create new projects.
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
# Freedom Studio uses this target.  Changing this target may break Freedom Studio's
# ability to create new projects.
.PHONY: list-target-tags
list-target-tags:
	@echo target-tags: $(shell find $(TARGET_ROOT)/bsp -name settings.mk | \
		xargs grep -he "TARGET_TAGS" | \
		sed $(SED_RE_FLAG) 's/TARGET_TAGS.*=(.*)/\1/' | \
		tr ' ' '\n' | \
		sort | \
		uniq)

# Metal programs are any submodules in the software folder
# Freedom Studio uses this target.  Changing this target may break Freedom Studio's
# ability to create new projects.
.PHONY: list-programs
list-programs:
	@echo program-list: $(shell ls $(PROGRAM_ROOT)/software)

# Freedom Studio uses this target.  Changing this target may break Freedom Studio's
# ability to create new projects.
.PHONY: list-options
list-options: list-programs list-targets

#############################################################
# Import rules to build Freedom Metal
#############################################################

ifeq ($(NO_INCLUDES),)
include scripts/libmetal.mk
endif

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

# Freedom Studio uses the 'standalone' target.  Changing this target may break Freedom Studio's
# ability to create new projects.
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
		requirements.txt \
		scripts/devicetree-overlay-generator \
		scripts/ldscript-generator \
		scripts/cmsis-svd-generator \
		scripts/openocdcfg-generator \
		scripts/esdk-settings-generator \
		scripts/elf2hex \
		scripts/standalone.mk \
		scripts/libmetal.mk \
		scripts/virtualenv.mk \
		scripts/upload_debug.mk \
		scripts/help.mk \
		scripts/upload \
		scripts/debug \
		scripts/simulate \
		scripts/open-docs
	cp -r $(addprefix $(BSP_DIR)/,$(filter-out build,$(shell ls $(BSP_DIR)))) $</bsp/

	cp -r freedom-metal $</
	find $</freedom-metal -name ".git*" | xargs rm -rf

ifneq ($(shell grep FreeRTOS.mk $(SRC_DIR)/Makefile),)
	cp -r FreeRTOS-metal $</
	find $</FreeRTOS-metal -name ".git*" | xargs rm -rf
endif

ifneq ($(shell grep SystemView.mk $(SRC_DIR)/Makefile),)
	cp -r Segger_SystemView-metal $</

	find $</Segger_SystemView-metal -name ".git*" | xargs rm -rf
endif

	mkdir -p $</scripts
	cp scripts/virtualenv.mk $</scripts

	cp -r scripts/elf2hex $</scripts
	find $</scripts/elf2hex -name ".git*" | xargs rm -rf

	cp scripts/upload $</scripts
	cp scripts/debug $</scripts
	cp scripts/simulate $</scripts
	cp scripts/open-docs $</scripts

	cp -r scripts/devicetree-overlay-generator $</scripts
	find $</scripts/devicetree-overlay-generator -name ".git*" | xargs rm -rf

	cp -r scripts/ldscript-generator $</scripts
	find $</scripts/ldscript-generator -name ".git*" | xargs rm -rf

	cp -r scripts/cmsis-svd-generator $</scripts
	find $</scripts/cmsis-svd-generator -name ".git*" | xargs rm -rf

	cp -r scripts/openocdcfg-generator $</scripts
	find $</scripts/openocdcfg-generator -name ".git*" | xargs rm -rf

	cp -r scripts/esdk-settings-generator $</scripts
	find $</scripts/esdk-settings-generator -name ".git*" | xargs rm -rf

ifeq ($(PORT_DIR),)
	$(MAKE) -C $(SRC_DIR) clean
else
	$(MAKE) -C $(SRC_DIR) PORT_DIR=${PORT_DIR} clean
endif
	cp -r $(SRC_DIR)/* $</src/

	cp debug.mk $</debug.mk
	cp release.mk $</release.mk
	cp requirements.txt $</requirements.txt

	touch $</bsp/core.dts
	touch $</bsp/design.dts
	touch $</bsp/metal.default.lds
	touch $</bsp/metal.ramrodata.lds
	touch $</bsp/metal.scratchpad.lds
	touch $</bsp/metal.freertos.lds
	touch $</bsp/metal.h
	touch $</bsp/metal-platform.h
	touch $</bsp/design.svd
	touch $</bsp/settings.mk

	echo "PROGRAM = $(PROGRAM)" > $</Makefile
	echo "TARGET = ${TARGET}" >> $</Makefile
ifneq ($(PORT_DIR),)
	echo "PORT_DIR = $(PORT_DIR)" >> $</Makefile
endif
	echo "" >> $</Makefile
	echo "# The configuration defaults to Debug. Valid choices are:" >> $</Makefile
	echo "#   - debug" >> $</Makefile
	echo "#   - release" >> $</Makefile
	echo "CONFIGURATION ?= ${CONFIGURATION}" >> $</Makefile
	echo "" >> $</Makefile
	cat scripts/standalone.mk >> $</Makefile
	cat scripts/libmetal.mk >> $</Makefile
	cat scripts/upload_debug.mk >> $</Makefile
	cat scripts/help.mk >> $</Makefile
else # "rtl" not in TARGET_TAGS
standalone: \
		$(STANDALONE_DEST) \
		$(STANDALONE_DEST)/bsp \
		$(STANDALONE_DEST)/src \
		$(SRC_DIR) \
		freedom-metal \
		debug.mk \
		release.mk \
		requirements.txt \
		scripts/devicetree-overlay-generator \
		scripts/ldscript-generator \
		scripts/cmsis-svd-generator \
		scripts/openocdcfg-generator \
		scripts/esdk-settings-generator \
		scripts/standalone.mk \
		scripts/libmetal.mk \
		scripts/virtualenv.mk \
		scripts/upload_debug.mk \
		scripts/help.mk \
		scripts/upload \
		scripts/debug \
		scripts/simulate \
		scripts/open-docs
	cp -r $(addprefix $(BSP_DIR)/,$(filter-out build,$(shell ls $(BSP_DIR)))) $</bsp/

	cp -r freedom-metal $</
	find $</freedom-metal -name ".git*" | xargs rm -rf

ifneq ($(shell grep FreeRTOS.mk $(SRC_DIR)/Makefile),)
	cp -r FreeRTOS-metal $</
	find $</FreeRTOS-metal -name ".git*" | xargs rm -rf
endif

ifneq ($(shell grep SystemView.mk $(SRC_DIR)/Makefile),)
	cp -r Segger_SystemView-metal $</

	find $</Segger_SystemView-metal -name ".git*" | xargs rm -rf
endif

	mkdir -p $</scripts
	cp scripts/virtualenv.mk $</scripts

	cp scripts/upload $</scripts
	cp scripts/debug $</scripts
	cp scripts/simulate $</scripts
	cp scripts/open-docs $</scripts

	cp -r scripts/devicetree-overlay-generator $</scripts
	find $</scripts/devicetree-overlay-generator -name ".git*" | xargs rm -rf

	cp -r scripts/ldscript-generator $</scripts
	find $</scripts/ldscript-generator -name ".git*" | xargs rm -rf

	cp -r scripts/cmsis-svd-generator $</scripts
	find $</scripts/cmsis-svd-generator -name ".git*" | xargs rm -rf

	cp -r scripts/openocdcfg-generator $</scripts
	find $</scripts/openocdcfg-generator -name ".git*" | xargs rm -rf

	cp -r scripts/esdk-settings-generator $</scripts
	find $</scripts/esdk-settings-generator -name ".git*" | xargs rm -rf

ifeq ($(PORT_DIR),)
	$(MAKE) -C $(SRC_DIR) clean
else
	$(MAKE) -C $(SRC_DIR) PORT_DIR=${PORT_DIR} clean
endif
	cp -r $(SRC_DIR)/* $</src/

	cp debug.mk $</debug.mk
	cp release.mk $</release.mk
	cp requirements.txt $</requirements.txt

	touch $</bsp/core.dts
	touch $</bsp/design.dts
	touch $</bsp/metal.default.lds
	touch $</bsp/metal.ramrodata.lds
	touch $</bsp/metal.scratchpad.lds
	touch $</bsp/metal.freertos.lds
	touch $</bsp/metal.h
	touch $</bsp/metal-platform.h
	touch $</bsp/design.svd
	touch $</bsp/settings.mk

	echo "PROGRAM = $(PROGRAM)" > $</Makefile
	echo "TARGET = ${TARGET}" >> $</Makefile
ifneq ($(PORT_DIR),)
	echo "PORT_DIR = $(PORT_DIR)" >> $</Makefile
endif
	echo "" >> $</Makefile
	echo "# The configuration defaults to Debug. Valid choices are:" >> $</Makefile
	echo "#   - debug" >> $</Makefile
	echo "#   - release" >> $</Makefile
	echo "CONFIGURATION ?= ${CONFIGURATION}" >> $</Makefile
	echo "" >> $</Makefile
	cat scripts/standalone.mk >> $</Makefile
	cat scripts/libmetal.mk >> $</Makefile
	cat scripts/upload_debug.mk >> $</Makefile
	cat scripts/help.mk >> $</Makefile
endif # rtl in TARGET_TAGS

endif # STANDALONE_DEST

#############################################################
# Import rules to upload and debug
#############################################################

include scripts/upload_debug.mk
