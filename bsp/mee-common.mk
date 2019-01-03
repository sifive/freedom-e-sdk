# See LICENSE for license details.

ifndef _SIFIVE_MK_COMMON
_SIFIVE_MK_COMMON := # defined

.PHONY: all
all: $(TARGET)

ASM_OBJS := $(ASM_SRCS:.S=.o)
C_OBJS := $(C_SRCS:.c=.o)

LINK_OBJS += $(ASM_OBJS) $(C_OBJS)

CLEAN_OBJS += $(TARGET) $(LINK_OBJS) $(TARGET).hex

$(TARGET): $(LINK_OBJS) $(LINK_DEPS)
	$(CC) $(LDFLAGS) $(CFLAGS) $(INCLUDES) $(LINK_OBJS) -o $@ $(LDLIBS)

$(ASM_OBJS): %.o: %.S $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

$(C_OBJS): %.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

.PHONY: clean
clean:
	rm -f $(CLEAN_OBJS)

endif # _SIFIVE_MK_COMMON
