# Copyright 2020 SiFive, Inc #
# SPDX-License-Identifier: Apache-2.0 #

PROGRAM ?= example-l2pm

$(PROGRAM): $(wildcard *.c) $(wildcard *.h) $(wildcard *.S)
	$(CC) $(CFLAGS) $(LDFLAGS) $(filter %.c %.S,$^) $(LOADLIBES) $(LDLIBS) -o $@

clean:
	rm -f $(PROGRAM) $(PROGRAM).hex
