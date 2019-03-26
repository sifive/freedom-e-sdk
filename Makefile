PROGRAM ?= local-interrupt

override CFLAGS += -Xlinker --defsym=__stack_size=0x800

$(PROGRAM): $(wildcard *.c) $(wildcard *.h) $(wildcard *.S)

clean:
	rm -f $(PROGRAM) $(PROGRAM).hex

