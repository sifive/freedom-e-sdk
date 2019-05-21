PROGRAM ?= rvoffload_example

BSP_BASE = ../../bsp

$(PROGRAM): min.c $(BSP_BASE)/rvoffload/prologue.S
	$(CC) $(CFLAGS) $(LDFLAGS) $^ $(LOADLIBES) $(LDLIBS) -o $@
	$(OBJCOPY) -S -O binary $(PROGRAM) $(PROGRAM).bin

clean:
	rm -f $(PROGRAM) $(PROGRAM).hex