TARGET := coremark

C_SRCS := \
	../dhrystone/dhry_stubs.c \
	../dhrystone/dhry_printf.c \
	core_list_join.c \
	core_main.c \
	core_matrix.c \
	core_state.c \
	core_util.c \
	core_portme.c \

HEADERS := \
	coremark.h \
	core_portme.h \

CFLAGS := -Dscanf=dhry_scanf -Dee_printf=dhry_printf -O2 -fno-common -funroll-loops
CFLAGS += -DFLAGS_STR=\""$(CFLAGS)"\"
CFLAGS += -DITERATIONS=10000 -DPERFORMANCE_RUN=1

BSP_BASE = ../../bsp
include $(BSP_BASE)/env/common.mk
