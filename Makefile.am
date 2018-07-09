# Copyright 2018 SiFive, Inc
# SPDX-License-Identifier: Apache-2.0

# Install some MEE-specific headers, one of which is automatically generated.
# The files that aren't automatically generated are the same for all machines.
nobase_include_HEADERS = \
	mee/machines/@MACHINE_NAME@.h \
	mee/drivers/sifive,uart0.h \
	mee/tty.h

# Builds the machine-specific MEE header file, which paramaterizes the MEE for
# one specific machine.  This is automatically picked up by GCC so users
# automatically get the relevant definitions.  This is a two-step process:
# first a DTB is built, and then the DTB is converted to a header file using an
# external tool.
machine.dtb: @DTC@ @MACHINE_DTS@
	$< $(filter %.dts,$^) -o $@ -O dtb -I dts

mee/machines/@MACHINE_NAME@.h: @MEE_HEADER_GENERATOR@ machine.dtb
	@mkdir -p $(dir $@)
	$< --dtb $(filter %.dtb,$^) --output $@

# Everything in here is compiled into a single library, which contains all the
# source files in the project.  It's named for one specific machine, which GCC
# uses to select the target machine that this MEE implementation points at.
lib_LIBRARIES = libmee-@MACHINE_NAME@.a

libmee_@MACHINE_NAME@_a_CFLAGS = -include mee/machines/@MACHINE_NAME@.h

libmee_@MACHINE_NAME@_a_SOURCES = \
	src/drivers/fixed-clock.c \
	src/drivers/sifive,uart0.c \
	src/before_main.c \
	src/tty.c \
	src/entry.S

# Quash an automake warning.
check_PROGRAMS =

# A simple "Hello, World!" program that directly uses the MEE interface to
# print to the serial terminal.
check_PROGRAMS += hello
hello_SOURCES   = test/hello.c
hello_CFLAGS    = -include mee/machines/@MACHINE_NAME@.h
hello_LDFLAGS   = -nostdlib -nostartfiles
hello_LDADD     = libmee-@MACHINE_NAME@.a

# Every C compilation depends on the machine header.
%.o: mee/machines/@MACHINE_NAME@.h
