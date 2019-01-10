TARGET = fish
C_SRCS += fish.c
C_SRCS += $(BSP_BASE)/drivers/esp32/esp32.c
C_SRCS += $(BSP_BASE)/drivers/spi/spi.c
CFLAGS += -O2 -fno-builtin-printf -DNO_INIT -DHASESP32 -DHASE24

BSP_BASE = ../../bsp
include $(BSP_BASE)/env/common.mk
