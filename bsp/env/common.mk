# See LICENSE for license details.

PLATFORM ?= freedom-e300-hifive1
ENV_DIR = $(BSP_BASE)/env
PLATFORM_DIR = $(ENV_DIR)/$(PLATFORM)

ASM_SRCS += $(PLATFORM_DIR)/entry.S
C_SRCS += $(PLATFORM_DIR)/init.c
C_SRCS += $(ENV_DIR)/syscall.c

LINKER_SCRIPT := $(PLATFORM_DIR)/link.lds

INCLUDES += -I.
INCLUDES += -I$(BSP_BASE)/include
INCLUDES += -I$(ENV_DIR)
INCLUDES += -I$(PLATFORM_DIR)

CC := $(BSP_BASE)/../toolchain/bin/riscv32-unknown-elf-gcc

LDFLAGS += -T $(LINKER_SCRIPT) -nostdlib -nostartfiles -lc -lgcc
LDFLAGS += -L$(ENV_DIR)

ASM_OBJS := $(patsubst %.S,%.o,$(ASM_SRCS))
C_OBJS := $(patsubst %.c,%.o,$(C_SRCS))

LINK_OBJS += $(ASM_OBJS) $(C_OBJS)

$(TARGET): $(LINK_OBJS) $(LINKER_SCRIPT)
	$(CC) $(CFLAGS) $(INCLUDES) $(LINK_OBJS) -o $@ $(LDFLAGS)

$(ASM_OBJS): %.o: %.S $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

$(C_OBJS): %.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

all: $(TARGET)

clean:
	rm -f $(TARGET) $(LINK_OBJS)

.PHONY: all clean
