PROGRAM ?= rvoffload_example

BSP_BASE = ../../bsp

$(PROGRAM): min.c
	$(CC) $(CFLAGS) $(LDFLAGS) $^ $(LOADLIBES) $(LDLIBS) -o $@
	$(OBJCOPY) -S -O binary $(PROGRAM) $(PROGRAM).bin

clean:
	rm -f $(PROGRAM) $(PROGRAM).hex

