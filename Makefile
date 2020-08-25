# Copyright 2019 SiFive, Inc #
# SPDX-License-Identifier: Apache-2.0 #

# Provide a default for no verbose output
HIDE ?= @

PROGRAM ?= example-freertos-pmp-blinky

OBJ_DIR ?= ./$(CONFIGURATION)/build

C_SOURCES = $(wildcard *.c)

#     Add local include 
override CFLAGS  += -I./

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
# Add custom flags for link
# ----------------------------------------------------------------------
# Reduce default size of the stack and the heap
#
_ADD_LDFLAGS  += -Wl,--defsym,__stack_size=0x200
_ADD_LDFLAGS  += -Wl,--defsym,__heap_size=0x200

# ----------------------------------------------------------------------
# Add custom flags for FreeRTOS
# ----------------------------------------------------------------------
FREERTOS_SOURCE_PATH ?= ../../FreeRTOS-metal
FREERTOS_DIR = $(abspath $(FREERTOS_SOURCE_PATH))
include $(FREERTOS_DIR)/scripts/FreeRTOS.mk

export FREERTOS_CONFIG_DIR = $(abspath ./)
MAKE_CONFIG += 	freeRTOS.define.portHANDLE_INTERRUPT = FreedomMetal_InterruptHandler \
				freeRTOS.define.portHANDLE_EXCEPTION = FreedomMetal_ExceptionHandler 
				
ifeq ($(TARGET),sifive-hifive-unleashed)
	MAKE_CONFIG += freeRTOS.define.MTIME_RATE_HZ = 1000000
else
	MAKE_CONFIG += freeRTOS.define.MTIME_RATE_HZ = 32768
endif
export HEAP = 4

override CFLAGS +=      $(foreach dir,$(FREERTOS_INCLUDES),-I $(dir)) \
                                        -I $(FREERTOS_CONFIG_DIR) \
                                        -I $(join $(abspath  $(BUILD_DIRECTORIES)),/FreeRTOS/include)

override LDLIBS += -lFreeRTOS
override LDFLAGS += -L$(join $(abspath  $(BUILD_DIRECTORIES)),/FreeRTOS/lib)

# ----------------------------------------------------------------------
# Update LDLIBS
# ----------------------------------------------------------------------
FILTER_PATTERN = -Wl,--end-group
override LDLIBS := $(filter-out $(FILTER_PATTERN),$(LDLIBS)) -Wl,--end-group

ifneq ($(filter rtl,$(TARGET_TAGS)),)
override CFLAGS += -D_RTL_
endif

# ----------------------------------------------------------------------
# Export MAKE_CONFIG string (use to pass arguments, for example to generate 
# configuration header)
# ----------------------------------------------------------------------
export MAKE_CONFIG

# ----------------------------------------------------------------------
# Compile Object Files From Assembly
# ----------------------------------------------------------------------
$(OBJ_DIR)/%.o: %.S libfreertos
	@echo "Assemble: $<"
	$(HIDE)$(CC) -o $@ $(ASFLAGS) $(XCFLAGS) $(CPPFLAGS) $(_COMMON_CFLAGS) $<
	@echo

# ----------------------------------------------------------------------
# Compile Object Files From C
# ----------------------------------------------------------------------
$(OBJ_DIR)/%.o: %.c libfreertos
	@echo "Compile: $<"
	$(HIDE)$(CC) -c -o $@ $(CFLAGS) $(XCFLAGS) $(CPPFLAGS) $(CFLAGS_COMMON) $(_COMMON_CFLAGS) $<
	@echo

# ----------------------------------------------------------------------
# Compile Object Files From CPP
# ----------------------------------------------------------------------
$(OBJ_DIR)/%.o: %.cpp libfreertos
	@echo "Compile: $<"
	$(HIDE)$(CXX) -c -o $@ $(CXXFLAGS) $(XCFLAGS) $(CPPFLAGS) $(CFLAGS_COMMON) $(_COMMON_CFLAGS) $<

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

libfreertos:
	make -f Makefile -C $(FREERTOS_DIR) \
		BUILD_DIR=$(join $(abspath  $(BUILD_DIRECTORIES)),/FreeRTOS) \
		libFreeRTOS.a \
		VERBOSE=$(VERBOSE) \
		PMP=ENABLE

$(PROGRAM): \
	directories \
	libfreertos \
	$(OBJS)
	$(CC) $(CFLAGS) $(XCFLAGS) $(LDFLAGS) $(_ADD_LDFLAGS) $(OBJS) $(LOADLIBES) $(LDLIBS) -o $@
	@echo

clean::
	rm -rf $(BUILD_DIRECTORIES)
	rm -f $(PROGRAM) $(PROGRAM).hex
