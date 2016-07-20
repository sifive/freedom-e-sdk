RISCV ?= $(CURDIR)/toolchain
PATH := $(RISCV)/bin:$(PATH)

srcdir := $(dir $(realpath $(lastword $(MAKEFILE_LIST))))
srcdir := $(srcdir:/=)
wrkdir := $(CURDIR)/work

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
all: $(hex)
	@echo All done.

tools: tools64 tools32 openocd gdb

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


.PHONY: clean
clean:
	rm -rf -- $(wrkdir) 


.PHONY: superclean
superclean:
	rm -rf -- $(toolchain_dest)
