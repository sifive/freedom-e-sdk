#############################################################
# Configuration
#############################################################

# Allow users to select a different cross compiler.
CROSS_COMPILE ?= riscv64-unknown-elf

# Allows users to create Makefile.local or ../Makefile.project with
# configuration variables, so they don't have to be set on the command-line
# every time.
extra_configs := $(wildcard Makefile.local ../Makefile.project)
ifneq ($(extra_configs),)
$(info Obtaining additional make variables from $(extra_configs))
include $(extra_configs)
endif

# Default target

# legacy for old e-sdk or mee
BSP ?= legacy

ifeq ($(BSP),legacy)
BSP_SUBDIR ?= env
BOARD ?= freedom-e300-hifive1
PROGRAM ?= demo_gpio
LINK_TARGET ?= flash
GDB_PORT ?= 3333

else # MEE
BSP_SUBDIR ?= 
PROGRAM ?= hello
BOARD ?= sifive-hifive1

endif # $(BSP)

# Variables the user probably shouldn't override.
#############################################################
# BSP Loading
#############################################################

# Finds the directory in which this BSP is located, ensuring that there is
# exactly one.
board_dir := $(wildcard bsp/$(BSP_SUBDIR)/$(BOARD))
ifeq ($(words $(board_dir)),0)
$(error Unable to find BSP for $(BOARD), expected to find either "bsp/$(BOARD)" or "bsp-addons/$(BOARD)")
endif
ifneq ($(words $(board_dir)),1)
$(error Found multiple BSPs for $(BOARD): "$(board_dir)")
endif

ifeq ($(BSP), mee)

include $(board_dir)/settings.mk

else

# There must be a settings makefile fragment in the BSP's board directory.
ifeq ($(wildcard $(board_dir)/settings.mk),)
$(error Unable to find BSP for $(BOARD), expected to find $(board_dir)/settings.mk)
endif

include $(board_dir)/settings.mk

ifeq ($(RISCV_ARCH),)
$(error $(board_dir)/board.mk must set RISCV_ARCH, the RISC-V ISA string to target)
endif

ifeq ($(RISCV_ABI),)
$(error $(board_dir)/board.mk must set RISCV_ABI, the ABI to target)
endif

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
# Prints help message
#############################################################
.PHONY: help
help:
	@echo "  SiFive Freedom E Software Development Kit "
	@echo "  Makefile targets:"
	@echo ""
	@echo " software BSP=legacy [PROGRAM=$(PROGRAM) BOARD=$(BOARD)]:"
	@echo "    Build a software program to load with the"
	@echo "    debugger."
	@echo ""
	@echo " mee BSP=mee [BOARD=$(BOARD)]"
	@echo "    Build the MEE library for BOARD"
	@echo ""
	@echo " examples BSP=mee [BOARD=$(BOARD)]"
	@echo "     Build all the examples for the given board."
	@echo ""
	@echo " clean [PROGRAM=$(PROGRAM) BOARD=$(BOARD)]:"
	@echo "    Clean compiled objects for a specified "
	@echo "    software program."
	@echo ""
	@echo " upload [PROGRAM=$(PROGRAM) BOARD=$(BOARD)]:"
	@echo "    Launch OpenOCD to flash your program to the"
	@echo "    on-board Flash."
	@echo ""
	@echo " run_openocd [BOARD=$(BOARD)]:"
	@echo " run_gdb     [PROGRAM=$(PROGRAM) BOARD=$(BOARD)]:"
	@echo "     Launch OpenOCD or GDB seperately. Allows Ctrl-C to halt running"
	@echo "     programs."
	@echo ""
	@echo " dasm [PROGRAM=$(PROGRAM)]:"
	@echo "     Generates the dissassembly output of 'objdump -D' to stdout."
	@echo ""
	@echo " For more information, visit dev.sifive.com"

.PHONY: clean
clean:

#############################################################
# This section is for tool configuration
#############################################################

# If users don't specify RISCV_PATH then assume that the tools will just be in
# their path.
ifeq ($(RISCV_PATH),)
RISCV_GCC     := $(CROSS_COMPILE)-gcc
RISCV_GXX     := $(CROSS_COMPILE)-g++
RISCV_OBJDUMP := $(CROSS_COMPILE)-objdump
RISCV_GDB     := $(CROSS_COMPILE)-gdb
RISCV_AR      := $(CROSS_COMPILE)-ar
RISCV_OPENOCD := openocd
else
RISCV_GCC     := $(abspath $(RISCV_PATH)/bin/$(CROSS_COMPILE)-gcc)
RISCV_GXX     := $(abspath $(RISCV_PATH)/bin/$(CROSS_COMPILE)-g++)
RISCV_OBJDUMP := $(abspath $(RISCV_PATH)/bin/$(CROSS_COMPILE)-objdump)
RISCV_GDB     := $(abspath $(RISCV_PATH)/bin/$(CROSS_COMPILE)-gdb)
RISCV_AR      := $(abspath $(RISCV_PATH)/bin/$(CROSS_COMPILE)-ar)
RISCV_OPENOCD := $(abspath $(RISCV_PATH)/bin/openocd)
PATH          := $(abspath $(RISCV_PATH)/bin):$(PATH)
endif

#############################################################
# Compiles an instance of the MEE targeted at $(BOARD)
#############################################################
ifeq ($(BSP),mee)
MEE_SOURCE_PATH	  ?= freedom-mee
MEE_BSP_PATH       = bsp/$(BOARD)
MEE_LDSCRIPT	   = $(MEE_BSP_PATH)/mee.lds
MEE_HEADER	   = $(MEE_BSP_PATH)/mee.h

.PHONY: mee
mee: $(MEE_BSP_PATH)/install/stamp

$(MEE_BSP_PATH)/build/Makefile:
	@rm -rf $(dir $@)
	@mkdir -p $(dir $@)
	cd $(dir $@) && \
		CFLAGS="-march=$(RISCV_ARCH) -mabi=$(RISCV_ABI) -g" \
		$(abspath $(MEE_SOURCE_PATH)/configure) \
		--host=$(CROSS_COMPILE) \
		--prefix=$(abspath $(MEE_BSP_PATH)/install) \
		--with-preconfigured \
		--with-machine-name=$(BOARD) \
		--with-machine-header=$(abspath $(MEE_HEADER)) \
		--with-machine-ldscript=$(abspath $(MEE_LDSCRIPT)) \
		--with-builtin-libgloss
	touch -c $@

$(MEE_BSP_PATH)/install/stamp: $(MEE_BSP_PATH)/build/Makefile
	$(MAKE) -C $(abspath $(MEE_BSP_PATH)/build) install
	date > $@

$(MEE_BSP_PATH)/install/lib/libriscv%.a: $(MEE_BSP_PATH)/install/stamp ;@:

$(MEE_BSP_PATH)/install/lib/libmee.a: $(MEE_BSP_PATH)/install/lib/libriscv__mmachine__$(BOARD).a
	cp $< $@

$(MEE_BSP_PATH)/install/lib/libmee-gloss.a: $(MEE_BSP_PATH)/install/lib/libriscv__menv__mee.a
	cp $< $@

.PHONY: clean-mee
clean-mee:
	rm -rf $(MEE_BSP_PATH)/install
	rm -rf $(MEE_BSP_PATH)/build
clean: clean-mee
endif

mee_install: mee
	$(MAKE) -C $(MEE_SOURCE_PATH) install

#############################################################
# This Section is for Software Compilation
#############################################################
PROGRAM_ELF = software/$(PROGRAM)/$(PROGRAM)

ifeq ($(BSP),mee)
.PHONY: software
software: $(PROGRAM_ELF)

$(PROGRAM_ELF): \
		$(shell find $(abspath $(dir $(PROGRAM_ELF))) -type f) \
		$(MEE_BSP_PATH)/install/lib/libmee.a \
		$(MEE_BSP_PATH)/install/lib/libmee-gloss.a \
		$(MEE_BSP_PATH)/mee.lds
	$(MAKE) -C $(dir $@) $(notdir $@) \
		CC=$(RISCV_GCC) \
		CXX=$(RISCV_GXX) \
		CFLAGS="-Os -march=$(RISCV_ARCH) -mabi=$(RISCV_ABI) -g" \
		CXXFLAGS="-Os -march=$(RISCV_ARCH) -mabi=$(RISCV_ABI) -g" \
		LDFLAGS="-nostartfiles -nostdlib -L$(sort $(dir $(abspath $(filter %.a,$^)))) -T$(abspath $(filter %.lds,$^))" \
		LDLIBS="-Wl,--start-group -lc -lmee -lmee-gloss -Wl,--end-group"
	touch -c $@

.PHONY: clean-software
clean-software:
	$(MAKE) -C $(dir $(PROGRAM_ELF)) clean
clean: clean-software

else
PROGRAM_DIR=$(dir $(PROGRAM_ELF))

.PHONY: software_clean
clean: software_clean
software_clean:
	$(MAKE) -C $(PROGRAM_DIR) CC=$(RISCV_GCC) RISCV_ARCH=$(RISCV_ARCH) RISCV_ABI=$(RISCV_ABI) AR=$(RISCV_AR) BSP_BASE=$(abspath bsp) BOARD=$(BOARD) LINK_TARGET=$(LINK_TARGET) clean

.PHONY: software
software: software_clean
	$(MAKE) -C $(PROGRAM_DIR) CC=$(RISCV_GCC) RISCV_ARCH=$(RISCV_ARCH) RISCV_ABI=$(RISCV_ABI) AR=$(RISCV_AR) BSP_BASE=$(abspath bsp) BOARD=$(BOARD) LINK_TARGET=$(LINK_TARGET)

dasm: software $(RISCV_OBJDUMP)
	$(RISCV_OBJDUMP) -D $(PROGRAM_ELF)
endif

#############################################################
# This Section is for uploading a program to SPI Flash
#############################################################
ifeq ($(BSP),mee)
upload: $(PROGRAM_ELF)
	scripts/upload --elf $(PROGRAM_ELF) --openocd $(RISCV_OPENOCD) --gdb $(RISCV_GDB) --openocd-config bsp/$(BOARD)/openocd.cfg

debug: $(PROGRAM_ELF)
	scripts/debug --elf $(PROGRAM_ELF) --openocd $(RISCV_OPENOCD) --gdb $(RISCV_GDB) --openocd-config bsp/$(BOARD)/openocd.cfg
else
OPENOCDCFG ?= bsp/env/$(BOARD)/openocd.cfg
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
	echo "Successfully uploaded '$(PROGRAM)' to $(BOARD)."
endif

#############################################################
# This Section is for launching the debugger
#############################################################

run_openocd:
	$(RISCV_OPENOCD) $(OPENOCDARGS)

GDBCMDS += -ex "set remotetimeout 240"
GDBCMDS += -ex "target extended-remote localhost:$(GDB_PORT)"

run_gdb:
	$(RISCV_GDB) $(PROGRAM_DIR)/$(PROGRAM) $(GDBARGS) $(GDBCMDS)
