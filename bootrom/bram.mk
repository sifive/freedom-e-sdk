ifndef _BRAM_MK
_BRAM_MK := # defined

BRAM_ADDR := 0x1000

BASEDIR := $(dir $(lastword $(MAKEFILE_LIST)))
BASEDIR := $(BASEDIR:/=)
DATADIR := $(BASEDIR)/common

LDSCRIPT := $(DATADIR)/bram.ld
MEMSCRIPT := $(DATADIR)/mem.awk

BITFILEDIR := $(BASEDIR)/../bitfile
BITFILE_VERSION ?= 0-1

BITFILE := $(BITFILEDIR)/freedom-e300-arty-$(BITFILE_VERSION).bit
CFGFILE := $(BITFILEDIR)/FreedomE-$(BITFILE_VERSION).cfg
MEMINFO := $(BITFILEDIR)/freedom-e300-arty-$(BITFILE_VERSION).mmi
BRAM_INST := `cat $(BITFILEDIR)/freedom-e300-arty-$(BITFILE_VERSION)-bootrom.txt`

XLEN = 32
BRAM_WIDTH=64

all: mcs

$(BITFILE):
	@echo "In order to get Version $(BITFILE_VERSION) of the bitfile:"
	@echo ""
	@cat $(BITFILEDIR)/README.md

CC := ../../toolchain/bin/riscv$(XLEN)-unknown-elf-gcc
UPDATEMEM ?= updatemem

CDEFINES += -DCFG_STRING=\"$(CFGFILE)\"

CFLAGS ?= -m$(XLEN) -O2 -std=c11 -pedantic -Wall \
	-nostartfiles -fno-common -mcmodel=medany -g \
	$(CDEFINES)

LDFLAGS ?= -T$(LDSCRIPT) -static -nostdlib
OBJCOPY ?= objcopy
elf: $(PROG).elf
hex: $(PROG).hex
mem: $(PROG).impl.mem
mcs: $(PROG).mcs

$(PROG).elf: $(SRCS) $(EXTRAS) $(CFGFILE)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(SRCS)

$(PROG).hex: $(PROG).elf
	$(OBJCOPY) -S -O verilog --change-addresses -$(BRAM_ADDR) $< $@

# Manually reverse the byte order due to limitations in UpdateMEM.
# Per UG898: "When UpdateMEM inputs data, it takes data from data input
# files in Bit Lane sized chunks from the most right value first to the
# left most.  For example, if the first 64 bits of input data are
# 0xB47DDE02826A8419 then the value 0xB4 is the first value to be set
# into a Block RAM."
$(PROG).impl.mem: $(PROG).hex $(MEMSCRIPT)
	awk -v WIDTH=$(BRAM_WIDTH) -v REVERSE=1 -f $(MEMSCRIPT) $< > $@

.PHONY: $(PROG).mcs
$(PROG).mcs : $(BITFILE) $(PROG).impl.mem
	@echo ""
	@echo ""
	@echo "TO COMPLETE THE BUILD OF $(PROG).mcs, "
	@echo "ENTER THE FOLLOWING IN THE VIVADO TCL WINDOW:"
	@echo ""
	@echo "cd `pwd`"
	@echo ""
	@echo "exec $(UPDATEMEM) -meminfo $(MEMINFO) -data $(PROG).impl.mem -proc $(BRAM_INST) -bit $(BITFILE) --out $(PROG).bit -force"
	@echo ""
	@echo "write_cfgmem -format mcs -interface spix4 -size 16 -loadbit {up 0x0 $(PROG).bit} -file $(PROG).mcs -force"
	@echo ""

clean:
	rm -f -- $(foreach ext,elf hex impl.mem bit mcs,$(PROG).$(ext))

endif # _BRAM_MK
