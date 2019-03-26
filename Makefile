DHRY-LFLAGS =

DHRY-CFLAGS := -O3 -DTIME -DNOENUM -Wno-implicit -mexplicit-relocs -save-temps
DHRY-CFLAGS += -fno-inline -fno-builtin-printf -fno-common -falign-functions=4 
#Uncomment below for FPGA run, default DHRY_ITERS is 2000 for RTL
#DHRY-CFLAGS += -DDHRY_ITERS=2000000

SRC = dhry_1.c dhry_2.c
HDR = dhry.h

override CFLAGS += -specs=nano.specs $(DHRY-CFLAGS) -Xlinker --defsym=__stack_size=0x800
dhrystone: $(SRC) $(HDR)
	$(CC) $(CFLAGS) $(SRC) $(LDFLAGS) $(LOADLIBES) $(LDLIBS) -o $@

clean:
	rm -f *.i *.s *.o dhrystone dhrystone.hex

