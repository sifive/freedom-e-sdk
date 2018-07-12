# Copyright 2018 SiFive, Inc
# SPDX-License-Identifier: Apache-2.0

# Every C compilation depends on the machine header.  This is a bit of a hack:
# instead of enforcing the dependency on the .o we pretend that the C file
# itself depends on the header.  This is the only way I could figure out that
# would satisfy the dependency inside automake.
%.c: mee/machine/@MACHINE_NAME@.h

# Every test depends on the generated linker script.
$(check_PROGRAMS): mee-@MACHINE_NAME@.lds

# Every test depends on the freshly-compiled library.
$(check_PROGRAMS): libmee-@MACHINE_NAME@.a

# Install some MEE-specific headers, one of which is automatically generated.
# The files that aren't automatically generated are the same for all machines.
nobase_include_HEADERS = \
	mee/machine/@MACHINE_NAME@.h \
	mee/drivers/sifive,uart0.h \
	mee/tty.h

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

libmee_@MACHINE_NAME@_a_CFLAGS = -mmee-machine=@MACHINE_NAME@

libmee_@MACHINE_NAME@_a_SOURCES = \
	src/drivers/fixed-clock.c \
	src/drivers/sifive,uart0.c \
	src/before_main.c \
	src/tty.c \
	src/shutdown.c \
	src/entry.S

# Generates a linker script that's more reasonable that whatever GCC's default
# is.
mee-@MACHINE_NAME@.lds: @LDSCRIPT_GENERATOR@ @MACHINE_NAME@.dtb
	$< --dtb $(filter %.dtb,$^) --linker $@

# Quash an automake warning.
check_PROGRAMS =

# A simple "Hello, World!" program that directly uses the MEE interface to
# print to the serial terminal.
check_PROGRAMS += hello
hello_SOURCES   = test/hello.c
hello_CFLAGS    = -mmee-machine=@MACHINE_NAME@
hello_LDFLAGS   = -L.
