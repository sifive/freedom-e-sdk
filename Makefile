srcdir := $(dir $(realpath $(lastword $(MAKEFILE_LIST))))
srcdir := $(srcdir:/=)
wrkdir := $(CURDIR)/work

DEFAULT_BOARD := freedom-e300-hifive1
DEFAULT_PROGRAM := demo_gpio

#############################################################
# Prints help message
#############################################################

.PHONY: help
help :
	@echo "  SiFive Freedom E Software Development Kit "
	@echo "  Makefile targets:"
	@echo ""
	@echo " tools:"
	@echo "    Install compilation & debugging tools."
	@echo ""
	@echo " uninstall:"
	@echo "    Uninstall the compilation & debugging tools."
	@echo ""
	@echo " software [PROGRAM=$(DEFAULT_PROGRAM) BOARD=$(DEFAULT_BOARD)]:"
	@echo "    Build a software program to load with the"
	@echo "    debugger."
	@echo ""
	@echo " upload [PROGRAM=$(DEFAULT_PROGRAM) BOARD=$(DEFAULT_BOARD)]:"
	@echo "    Launch OpenOCD to flash your program to the"
	@echo "    on-board Flash."
	@echo ""
	@echo " run_debug [PROGRAM=$(DEFAULT_PROGRAM) BOARD=$(DEFAULT_BOARD)]:"
	@echo "    Launch OpenOCD & GDB to load or debug "
	@echo "    running programs. Does not allow Ctrl-C to halt running programs."
	@echo ""
	@echo " run_openocd [BOARD=$(DEFAULT_BOARD)]:"
	@echo " run_gdb     [PROGRAM=$(DEFAULT_PROGRAM) BOARD=$(DEFAULT_BOARD)]:"
	@echo "     Launch OpenOCD or GDB seperately. Allows Ctrl-C to halt running"
	@echo "     programs."
	@echo ""
	@echo " dasm [PROGRAM=$(DEFAULT_BOARD)]:"
	@echo "     Generates the dissassembly output of 'objdump -D' to stdout."
	@echo ""
	@echo " For more information, visit dev.sifive.com"


#############################################################
# This section is for tool installation
#############################################################

toolchain_srcdir := $(srcdir)/riscv-gnu-toolchain
toolchain32_wrkdir := $(wrkdir)/riscv32-gnu-toolchain
toolchain_dest := $(CURDIR)/toolchain
PATH := $(toolchain_dest)/bin:$(PATH)

openocd_srcdir := $(srcdir)/openocd
openocd_wrkdir := $(wrkdir)/openocd
openocd_dest := $(CURDIR)/toolchain

target32 := riscv32-unknown-linux-gnu


.PHONY: all
all: tools
	@echo All done.

tools: tools32 openocd
	@echo All Tools Installed

tools32: $(toolchain_dest)/bin/$(target32)-gcc
openocd: $(openocd_dest)/bin/openocd

$(toolchain_dest)/bin/$(target32)-gcc: $(toolchain_srcdir)
	mkdir -p $(toolchain32_wrkdir)
	cd $(toolchain32_wrkdir); $(toolchain_srcdir)/configure --prefix=$(toolchain_dest) --with-arch=rv32imac --with-abi=ilp32
	$(MAKE) -C $(toolchain32_wrkdir)

$(openocd_dest)/bin/openocd: $(openocd_srcdir)
	mkdir -p $(openocd_wrkdir)
	cd $(openocd_srcdir); \
	$(openocd_srcdir)/bootstrap
	cd $(openocd_wrkdir); \
	$(openocd_srcdir)/configure --prefix=$(openocd_dest)
	$(MAKE) -C $(openocd_wrkdir)
	$(MAKE) -C $(openocd_wrkdir) install

.PHONY: uninstall
uninstall:
	rm -rf $(wrkdir)
	rm -rf $(toolchain_dest)

#############################################################
# This Section is for Software Compilation
#############################################################
BOARD ?= $(DEFAULT_BOARD)
PROGRAM ?= $(DEFAULT_PROGRAM)
PROGRAM_DIR = $(srcdir)/software/$(PROGRAM)
PROGRAM_ELF = $(srcdir)/software/$(PROGRAM)/$(PROGRAM)

.PHONY: software_clean
software_clean:
	$(MAKE) -C $(PROGRAM_DIR) clean

.PHONY: software
software: software_clean
	$(MAKE) -C $(PROGRAM_DIR)

dasm: software	
	$(toolchain_dest)/bin/riscv32-unknown-elf-objdump -D $(PROGRAM_ELF)

#############################################################
# This Section is for uploading a program to SPI Flash
#############################################################
OPENOCD_UPLOAD = $(srcdir)/bsp/tools/openocd_upload.sh
OPENOCDCFG ?= $(srcdir)/bsp/env/$(BOARD)/openocd.cfg

upload:
	$(OPENOCD_UPLOAD) $(PROGRAM_ELF) $(OPENOCDCFG)

#############################################################
# This Section is for launching the debugger
#############################################################

OPENOCD     = $(toolchain_dest)/bin/openocd
OPENOCDARGS += -f $(OPENOCDCFG)

GDB     = $(toolchain_dest)/bin/riscv32-unknown-elf-gdb
GDBCMDS += -ex "target extended-remote localhost:3333"
GDBARGS =

run_openocd:
	$(OPENOCD) $(OPENOCDARGS)

run_gdb:
	$(GDB) $(PROGRAM_DIR)/$(PROGRAM) $(GDBARGS)

run_debug:
	$(OPENOCD) $(OPENOCDARGS) &
	$(GDB) $(PROGRAM_DIR)/$(PROGRAM) $(GDBARGS) $(GDBCMDS)

.PHONY: clean
clean:
	rm -rf -- $(wrkdir) 
