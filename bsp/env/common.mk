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

CC = $(BSP_BASE)/../toolchain/bin/riscv32-unknown-elf-gcc

LDFLAGS := -T $(LINKER_SCRIPT) -nostdlib -nostartfiles -lc -lgcc
LDFLAGS += -L$(ENV_DIR)

ASM_OBJS := $(patsubst %.S,%.o,$(ASM_SRCS))
C_OBJS := $(patsubst %.c,%.o,$(C_SRCS))

ASM_STRIP_OBJS := $(foreach f,$(ASM_OBJS),$(notdir $f))
C_STRIP_OBJS := $(foreach f,$(C_OBJS),$(notdir $f))

$(TARGET): $(ASM_OBJS) $(C_OBJS) $(LINKER_SCRIPT)
	$(CC) $(CFLAGS) $(INCLUDES) $(ASM_STRIP_OBJS) $(C_STRIP_OBJS) -o $@ $(LDFLAGS)

$(ASM_OBJS): %.o: %.S
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $(notdir $@) $<

$(C_OBJS): %.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $(notdir $@) $<

all: $(TARGET)

clean:
	rm -f $(TARGET) *.o

.PHONY: all clean
