# Copyright 2019 SiFive, Inc #

PROGRAM ?= example-latency-test

TEMP_HEAP_RESULT = $(shell ./calculate_heap_size.sh $(LDFLAGS))

ifeq ($(TEMP_HEAP_RESULT), )
HEAP_SIZE  = 0x6000
else
HEAP_SIZE  = $(word 1, $(TEMP_HEAP_RESULT))
endif

$(PROGRAM): clean $(wildcard *.c) $(wildcard *.h) $(wildcard *.S)
	$(CC) $(CFLAGS) $(LDFLAGS) -Xlinker --defsym=__heap_size=$(HEAP_SIZE) -Xlinker --defsym=__heap_max=1 $(filter %.c %.S,$^) $(LOADLIBES) $(LDLIBS) -o $@
	riscv64-unknown-elf-objdump -d $@ > $@.dump

clean:
	rm -f $(PROGRAM) $(PROGRAM).dump $(PROGRAM).hex
