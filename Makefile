# Copyright 2019 SiFive, Inc #
# SPDX-License-Identifier: Apache-2.0 #

PROGRAM ?= mem-latency


$(PROGRAM): clean $(wildcard *.c) $(wildcard *.h) $(wildcard *.S)
	$(CC) $(CFLAGS) $(LDFLAGS) -Xlinker --defsym=__heap_max=0x1 $(filter %.c %.S,$^) $(LOADLIBES) $(LDLIBS) -o $@
	riscv64-unknown-elf-objdump -d $@ > $@.dump

clean:
	rm -f $(PROGRAM) $(PROGRAM).dump $(PROGRAM).hex
