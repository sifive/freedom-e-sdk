TARGET := dhrystone

ASM_SRCS := 
C_SRCS := dhry_stubs.c dhry_printf.c
HEADERS := dhry.h

DHRY_SRCS := dhry_1.c dhry_2.c
DHRY_CFLAGS := -O2 -DTIME -fno-inline -Wno-implicit

XLEN ?= 32
CFLAGS := -Dscanf=dhry_scanf -Dprintf=dhry_printf -Os -fno-common

DHRY_OBJS := $(patsubst %.c,%.o,$(DHRY_SRCS))
LINK_OBJS := $(DHRY_OBJS)

BSP_BASE = ../../bsp
include $(BSP_BASE)/env/common.mk

$(DHRY_OBJS): %.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $(DHRY_CFLAGS) -c -o $@ $<
