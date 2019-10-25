# Copyright 2019 SiFive, Inc #

PROGRAM ?= mem-test


$(PROGRAM): clean $(wildcard *.c) $(wildcard *.h) $(wildcard *.S)
	$(CC) $(CFLAGS) $(LDFLAGS)  -Xlinker --defsym=__heap_size=0x8000000 -Xlinker --defsym=__heap_max=0x1 $(filter %.c %.S,$^) $(LOADLIBES) $(LDLIBS) -o $@
	riscv64-unknown-elf-objdump -d $@ > $@.dump

clean:
	rm -f $(PROGRAM) $(PROGRAM).dump $(PROGRAM).hex
