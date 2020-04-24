# Copyright 2019 SiFive, Inc #
# SPDX-License-Identifier: Apache-2.0 #

PROGRAM ?= example-hca-metal

# ----------------------------------------------------------------------
# create dedicated directory for Object files
# ----------------------------------------------------------------------
BUILD_DIRECTORIES = \
        $(OBJ_DIR) 

# ----------------------------------------------------------------------
# Add custom flags for link lib scl
# ----------------------------------------------------------------------
LIB_SCL_DIR = $(abspath ../../scl-metal)
override CFLAGS  += -I$(LIB_SCL_DIR)/include -DSCL_WORD32 

override LDLIBS += -lscl
override LDFLAGS += -L$(join $(abspath  $(BUILD_DIRECTORIES)),/scl/lib)

# ----------------------------------------------------------------------
# Build rules
# ----------------------------------------------------------------------
$(BUILD_DIRECTORIES):
	mkdir -p $@

directories: $(BUILD_DIRECTORIES)

libscl:
	make -f Makefile -C $(LIB_SCL_DIR) BUILD_DIR=$(join $(abspath  $(BUILD_DIRECTORIES)),/scl) scl_library

$(PROGRAM): \
	directories \
	libscl \
	$(wildcard *.c) $(wildcard *.h) $(wildcard *.S)
	$(CC) $(CFLAGS) $(XCFLAGS) $(LDFLAGS) $(_ADD_LDFLAGS) $(OBJS) $(LOADLIBES) $(LDLIBS) -o $@
	@echo

clean::
	rm -rf $(BUILD_DIRECTORIES)
	rm -f $(PROGRAM) $(PROGRAM).hex
