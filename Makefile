override CFLAGS += -Xlinker --defsym=__stack_size=0x800

local-interrupt: local-interrupt.c

clean:
	rm -f local-interrupt local-interrupt.hex

