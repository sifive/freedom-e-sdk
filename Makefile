RISCV ?= $(CURDIR)/toolchain
PATH := $(RISCV)/bin:$(PATH)

srcdir := $(dir $(realpath $(lastword $(MAKEFILE_LIST))))
srcdir := $(srcdir:/=)
wrkdir := $(CURDIR)/work

#############################################################
# Prints help message
#############################################################

.PHONY: help
help :
	@echo "  SiFive Freedom E Software Development Kit "
	@echo "  Makefile targets:"
	@echo ""
	@echo " tools:"
	@echo "    Install compilation & debugging tools"
	@echo ""
	@echo " fpga [BOOTROM=demo]:"
	@echo "    Rebuild the image (including Boot SW) to"
	@echo "	   reprogram the FPGA. "
	@echo ""
	@echo " software [PROGRAM=demo_gpio]:"
	@echo "    Build a software program to load with the"
	@echo "    debugger."
	@echo ""
	@echo " run_debug [PROGRAM=demo_gpio]:"
	@echo "    Launch the debugging tools to load or"
	@echo "    debug running programs."
	@echo ""
	@echo " For more information, visit dev.sifive.com"

#############################################################
# This section is for tool installation
#############################################################

toolchain_srcdir := $(srcdir)/riscv-gnu-toolchain
toolchain32_wrkdir := $(wrkdir)/riscv32-gnu-toolchain
toolchain64_wrkdir := $(wrkdir)/riscv64-gnu-toolchain
toolchain_dest := $(CURDIR)/toolchain

gdb_srcdir := $(srcdir)/riscv-binutils-gdb
gdb_wrkdir := $(wrkdir)/riscv-binutils-gdb
gdb_dest := $(CURDIR)/toolchain

openocd_srcdir := $(srcdir)/openocd
openocd_wrkdir := $(wrkdir)/openocd
openocd_dest := $(CURDIR)/toolchain

target64 := riscv64-unknown-linux-gnu
target32 := riscv32-unknown-linux-gnu


.PHONY: all
all: tools
	@echo All done.

tools: tools64 tools32 openocd gdb
	@echo All Tools Installed

tools64: $(toolchain_dest)/bin/$(target64)-gcc
tools32: $(toolchain_dest)/bin/$(target32)-gcc
openocd: $(openocd_dest)/bin/openocd
gdb:     $(gdb_dest)/bin/$(target64)-gdb

$(toolchain_dest)/bin/$(target64)-gcc: $(toolchain_srcdir)
	mkdir -p $(toolchain64_wrkdir)
	cd $(toolchain64_wrkdir); $(toolchain_srcdir)/configure --prefix=$(toolchain_dest) 
	$(MAKE) -C $(toolchain64_wrkdir)

$(toolchain_dest)/bin/$(target32)-gcc: $(toolchain_srcdir)
	mkdir -p $(toolchain32_wrkdir)
	cd $(toolchain32_wrkdir); $(toolchain_srcdir)/configure --prefix=$(toolchain_dest) --with-arch=RV32IMA
	$(MAKE) -C $(toolchain32_wrkdir)

$(openocd_dest)/bin/openocd: $(openocd_srcdir)
	mkdir -p $(openocd_wrkdir)
	cd $(openocd_srcdir); \
	$(openocd_srcdir)/bootstrap
	cd $(openocd_wrkdir); \
	$(openocd_srcdir)/configure --prefix=$(openocd_dest)
	$(MAKE) -C $(openocd_wrkdir)
	$(MAKE) -C $(openocd_wrkdir) install

$(gdb_dest)/bin/$(target64)-gdb : $(gdb_srcdir)
	mkdir -p $(gdb_wrkdir)
	cd $(gdb_wrkdir); $(gdb_srcdir)/configure --prefix=$(gdb_dest) --target=riscv64-unknown-elf
	$(MAKE) -C $(gdb_wrkdir)
	$(MAKE) -C $(gdb_wrkdir) install


.PHONY: uninstall
uninstall:
	rm -rf -- $(toolchain_dest)

#############################################################
# This Section is for MCS File Generation (
#############################################################

BOOTROM ?= demo
BOOTROM_DIR = $(srcdir)/bootrom/$(BOOTROM)/

.PHONY:
fpga:
	cd $(BOOTROM_DIR);\
	make mcs

fpga_clean:
	cd $(BOOTROM_DIR);\
	make clean

#############################################################
# This Section is for Software (non-boot) compilation
#############################################################

PROGRAM ?= demo_gpio
PROGRAM_DIR = $(srcdir)/software/$(PROGRAM)

.PHONY: software
software:
	cd $(PROGRAM_DIR);\
	make

software_clean:
	cd $(PROGRAM_DIR);\
	make clean

#############################################################
# This Section is for launching the debugger
#############################################################
OPENOCD      = $(toolchain_dest)/bin/openocd
OPENOCDARGS += -f $(srcdir)/riscv-tests/debug/targets/m2gl_m2s/openocd.cfg

GDB     = $(toolchain_dest)/bin/riscv64-unknown-elf-gdb
GDBARGS += -ex "target extended-remote localhost:3333"

run_debug:
	$(OPENOCD) $(OPENOCDARGS) &
	$(GDB) $(PROGRAM_DIR)/$(PROGRAM) $(GDBARGS)

.PHONY: clean
clean:
	rm -rf -- $(wrkdir) 
