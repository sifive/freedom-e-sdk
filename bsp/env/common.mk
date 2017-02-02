# See LICENSE for license details.

ifndef _SIFIVE_MK_COMMON
_SIFIVE_MK_COMMON := # defined

.PHONY: all
all: $(TARGET)

include $(BSP_BASE)/libwrap/libwrap.mk

BOARD ?= freedom-e300-hifive1
ENV_DIR = $(BSP_BASE)/env
PLATFORM_DIR = $(ENV_DIR)/$(BOARD)

ASM_SRCS += $(ENV_DIR)/start.S
ASM_SRCS += $(ENV_DIR)/entry.S
C_SRCS += $(PLATFORM_DIR)/init.c

LINKER_SCRIPT := $(PLATFORM_DIR)/link.lds

INCLUDES += -I$(BSP_BASE)/include
INCLUDES += -I$(BSP_BASE)/drivers/
INCLUDES += -I$(ENV_DIR)
INCLUDES += -I$(PLATFORM_DIR)

TOOL_DIR = $(BSP_BASE)/../toolchain/bin

CC := $(TOOL_DIR)/riscv32-unknown-elf-gcc
AR := $(TOOL_DIR)/riscv32-unknown-elf-ar

LDFLAGS += -T $(LINKER_SCRIPT) -nostartfiles
LDFLAGS += -L$(ENV_DIR)

ASM_OBJS := $(ASM_SRCS:.S=.o)
C_OBJS := $(C_SRCS:.c=.o)

LINK_OBJS += $(ASM_OBJS) $(C_OBJS)
LINK_DEPS += $(LINKER_SCRIPT)

CLEAN_OBJS += $(TARGET) $(LINK_OBJS)

CFLAGS += -g

$(TARGET): $(LINK_OBJS) $(LINK_DEPS)
	$(CC) $(CFLAGS) $(INCLUDES) $(LINK_OBJS) -o $@ $(LDFLAGS)

$(ASM_OBJS): %.o: %.S $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

$(C_OBJS): %.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -include sys/cdefs.h -c -o $@ $<

.PHONY: clean
clean:
	rm -f $(CLEAN_OBJS)

endif # _SIFIVE_MK_COMMON
