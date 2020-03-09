# Copyright 2019 SiFive, Inc #
# SPDX-License-Identifier: Apache-2.0 #

# Provide a default for no verbose output
HIDE ?= @

PROGRAM ?= example-freertos-minimal

OBJ_DIR ?= ./$(CONFIGURATION)/build

C_SOURCES = $(wildcard *.c)

# ----------------------------------------------------------------------
# FREERTOS 
# ----------------------------------------------------------------------
FREERTOS_SOURCE_PATH ?= ../../FreeRTOS-metal
#     Include FREERTOS source
include $(FREERTOS_SOURCE_PATH)/FreeRTOS.mk


#     Add FreeRTOS include 
_COMMON_CFLAGS  += -I./
_COMMON_CFLAGS  += ${FREERTOS_INCLUDES}
_COMMON_CFLAGS  += -DportHANDLE_INTERRUPT=FreedomMetal_InterruptHandler
_COMMON_CFLAGS  += -DportHANDLE_EXCEPTION=FreedomMetal_ExceptionHandler

#     Add define needed for FreeRTOS 
_COMMON_CFLAGS  += -DMTIME_CTRL_ADDR=0x2000000

ifeq ($(TARGET),sifive-hifive-unleashed)
_COMMON_CFLAGS  += -DMTIME_RATE_HZ=1000000
else
_COMMON_CFLAGS  += -DMTIME_RATE_HZ=32768
endif

#     Update our list of C source files.
C_SOURCES += ${FREERTOS_C_SOURCES}
C_SOURCES += ${FREERTOS_HEAP_4_C}

#     Update our list of S source files.
S_SOURCES += ${FREERTOS_S_SOURCES}

# ----------------------------------------------------------------------
# Build List of Object according C/CPP/S source file list
# ----------------------------------------------------------------------
_C_OBJ_FILES   += $(C_SOURCES:%.c=${OBJ_DIR}/%.o)
_CXX_OBJ_FILES += $(CXX_SOURCES:%.cpp=${OBJ_DIR}/%.o)

_asm_s := $(filter %.s,$(S_SOURCES))
_asm_S := $(filter %.S,$(S_SOURCES))
_ASM_OBJ_FILES := $(_asm_s:%.s=${OBJ_DIR}/%.o) $(_asm_S:%.S=${OBJ_DIR}/%.o)

OBJS += ${_C_OBJ_FILES}
OBJS += ${_CXX_OBJ_FILES}
OBJS += ${_ASM_OBJ_FILES}

# ----------------------------------------------------------------------
# Compile Object Files From Assembly
# ----------------------------------------------------------------------
$(OBJ_DIR)/%.o: %.S
	@echo "Assemble: $<"
	$(HIDE)$(CC) -D__ASSEMBLY__ -c -o $@ $(ASFLAGS) $(CPPFLAGS) $(_COMMON_CFLAGS) $<
	@echo

# ----------------------------------------------------------------------
# Compile Object Files From C
# ----------------------------------------------------------------------
$(OBJ_DIR)/%.o: %.c
	@echo "Compile: $<"
	$(HIDE)$(CC) -c -o $@ $(CFLAGS) $(CPPFLAGS) $(CFLAGS_COMMON) $(_COMMON_CFLAGS) $<
	@echo

# ----------------------------------------------------------------------
# Compile Object Files From CPP
# ----------------------------------------------------------------------
$(OBJ_DIR)/%.o: %.cpp
	@echo "Compile: $<"
	$(HIDE)$(CXX) -c -o $@ $(CXXFLAGS) $(CPPFLAGS) $(CFLAGS_COMMON) $(_COMMON_CFLAGS) $<

# ----------------------------------------------------------------------
# Add custom flags for link
# ----------------------------------------------------------------------
# Reduce default size of the stack and the heap
#
_ADD_LDFLAGS  += -Wl,--defsym,__stack_size=0x200
_ADD_LDFLAGS  += -Wl,--defsym,__heap_size=0x200

# ----------------------------------------------------------------------
# create dedicated directory for Object files
# ----------------------------------------------------------------------
BUILD_DIRECTORIES = \
        $(OBJ_DIR) 

# ----------------------------------------------------------------------
# Build rules
# ----------------------------------------------------------------------
$(BUILD_DIRECTORIES):
	mkdir -p $@

directories: $(BUILD_DIRECTORIES)

$(PROGRAM): \
	directories \
	$(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(_ADD_LDFLAGS) $(OBJS) $(LOADLIBES) $(LDLIBS) -o $@
	@echo

clean::
	rm -rf $(BUILD_DIRECTORIES)
	rm -f $(PROGRAM) $(PROGRAM).hex
