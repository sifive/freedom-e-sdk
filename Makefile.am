# Copyright 2018 SiFive, Inc
# SPDX-License-Identifier: Apache-2.0

# Everything in here is compiled into a single library, which contains all the
# source files in the project.
lib_LIBRARIES = libmee.a

libmee_a_SOURCES = \
	src/entry.S \
	src/tty.c

# Quash an automake warning.
check_PROGRAMS =

# A simple "Hello, World!" program that directly uses the MEE interface to
# print to the serial terminal.
check_PROGRAMS += hello
hello_SOURCES   = test/hello.c
hello_LDFLAGS   = -nostdlib -nostartfiles
hello_LDADD     = libmee.a
