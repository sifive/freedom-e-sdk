# Copyright 2018 SiFive, Inc
# SPDX-License-Identifier: Apache-2.0

# Every C compilation depends on the machine header.  This is a bit of a hack:
# instead of enforcing the dependency on the .o we pretend that the C file
# itself depends on the header.  This is the only way I could figure out that
# would satisfy the dependency inside automake.
%.c: mee/machine/@MACHINE_NAME@.h
%.S: mee/machine/@MACHINE_NAME@.h
%.o: mee/machine/@MACHINE_NAME@.h

# Every test depends on the generated linker script.
$(check_PROGRAMS): mee-@MACHINE_NAME@.lds

# Every test depends on the freshly-compiled library.
$(check_PROGRAMS): libmee-@MACHINE_NAME@.a

# Generates a linker script that's more reasonable that whatever GCC's default
# is.
ldsdir = $(libdir)
lds_DATA = mee-@MACHINE_NAME@.lds
mee-@MACHINE_NAME@.lds: @LDSCRIPT_GENERATOR@ @MACHINE_NAME@.dtb
	$< --dtb $(filter %.dtb,$^) --linker $@

# In order to generate code that's actually compatible with a machine we must
# pass the march and mabi arguments to GCC that coorespond to the hardware.
# This is handled by generating a makefile fragment, including it, and then
# adding those argument to CFLAGS.
-include @MACHINE_NAME@.mk
@MACHINE_NAME@.mk: @MAKEATTRIBUTES_GENERATOR@ @MACHINE_NAME@.dtb
	$< --dtb $(filter %.dtb,$^) --output $@

# Install some MEE-specific headers, one of which is automatically generated.
# The files that aren't automatically generated are the same for all machines.
nobase_include_HEADERS = \
	mee/machine/@MACHINE_NAME@.h \
	mee/drivers/fixed-clock.h \
	mee/drivers/sifive,fe310-g000,hfrosc.h \
	mee/drivers/sifive,fe310-g000,hfxosc.h \
	mee/drivers/sifive,fe310-g000,pll.h \
	mee/drivers/sifive,fe310-g000,prci.h \
	mee/drivers/sifive,gpio0.h \
	mee/drivers/sifive,uart0.h \
	mee/drivers/sifive,test0.h \
	mee/compiler.h \
	mee/clock.h \
	mee/io.h \
	mee/shutdown.h \
	mee/tty.h \
	mee/uart.h

# Builds the machine-specific MEE header file, which paramaterizes the MEE for
# one specific machine.  This is automatically picked up by GCC so users
# automatically get the relevant definitions.  This is a two-step process:
# first a DTB is built, and then the DTB is converted to a header file using an
# external tool.
@MACHINE_NAME@.dtb: @DTC@ @MACHINE_DTS@
	$< $(filter %.dts,$^) -o $@ -O dtb -I dts

mee/machine/@MACHINE_NAME@.h: @MEE_HEADER_GENERATOR@ @MACHINE_NAME@.dtb
	@mkdir -p $(dir $@)
	$< --dtb $(filter %.dtb,$^) --output $@

# Everything in here is compiled into a single library, which contains all the
# source files in the project.  It's named for one specific machine, which GCC
# uses to select the target machine that this MEE implementation points at.
lib_LIBRARIES = libmee-@MACHINE_NAME@.a

libmee_@MACHINE_NAME@_a_CFLAGS  = -mmee-machine=@MACHINE_NAME@
libmee_@MACHINE_NAME@_a_CFLAGS += -ffunction-sections -fdata-sections
libmee_@MACHINE_NAME@_a_CFLAGS += -march=$(FRAMEWORK_BOARD_DTS_MARCH) -mabi=$(FRAMEWORK_BOARD_DTS_MABI)
libmee_@MACHINE_NAME@_a_CCASFLAGS = $(libmee_@MACHINE_NAME@_a_CFLAGS) -DASSEMBLY

libmee_@MACHINE_NAME@_a_SOURCES = \
	src/drivers/fixed-clock.c \
	src/drivers/sifive,fe310-g000,hfrosc.c \
	src/drivers/sifive,fe310-g000,hfxosc.c \
	src/drivers/sifive,fe310-g000,prci.c \
	src/drivers/sifive,fe310-g000,pll.c \
	src/drivers/sifive,test0.c \
	src/drivers/sifive,gpio0.c \
	src/drivers/sifive,uart0.c \
	src/before_main.c \
	src/clock.c \
	src/tty.c \
	src/shutdown.c \
	src/uart.c \
	src/entry.S

# Quash an automake warning.
check_PROGRAMS =

# The simplest possible pair of tests: one that passes and one that fails
check_PROGRAMS       += return_pass
return_pass_SOURCES   = test/return_pass.c
return_pass_CFLAGS    = -mmee-machine=@MACHINE_NAME@
return_pass_CFLAGS   += -ffunction-sections -fdata-sections
return_pass_CFLAGS   += -march=$(FRAMEWORK_BOARD_DTS_MARCH) -mabi=$(FRAMEWORK_BOARD_DTS_MABI)
return_pass_LDFLAGS   = -L. -Wl,--gc-sections -Wl,-Map=return_pass.map

check_PROGRAMS       += return_fail
return_fail_SOURCES   = test/return_fail.c
return_fail_CFLAGS    = -mmee-machine=@MACHINE_NAME@
return_fail_CFLAGS   += -ffunction-sections -fdata-sections
return_fail_CFLAGS   += -march=$(FRAMEWORK_BOARD_DTS_MARCH) -mabi=$(FRAMEWORK_BOARD_DTS_MABI)
return_fail_LDFLAGS   = -L. -Wl,--gc-sections -Wl,-Map=return_fail.map

# A simple "Hello, World!" program that directly uses the MEE interface to
# print to the serial terminal.
check_PROGRAMS       += hello
hello_SOURCES         = test/hello.c
hello_CFLAGS          = -mmee-machine=@MACHINE_NAME@
hello_CFLAGS         += -ffunction-sections -fdata-sections
hello_CFLAGS         += -march=$(FRAMEWORK_BOARD_DTS_MARCH) -mabi=$(FRAMEWORK_BOARD_DTS_MABI)
hello_LDFLAGS         = -L. -Wl,--gc-sections -Wl,-Map=hello.map

# Extra clean targets
clean-local:
	-rm -rf @MACHINE_NAME@.mk
	-rm -rf mee/machine/@MACHINE_NAME@.h @MACHINE_NAME@.dtb mee-@MACHINE_NAME@.lds
	-rm -rf return_pass.map return_fail.map
	-rm -rf hello.map
