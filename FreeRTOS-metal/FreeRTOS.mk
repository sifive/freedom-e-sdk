#
# Copyright 2019 SiFive, Inc #
# SPDX-License-Identifier: Apache-2.0 #
#

FREERTOS_DIR=$(dir $(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST)))/FreeRTOS-Kernel
FREERTOS_MEMMANG_DIR =${FREERTOS_DIR}/portable/MemMang

# ----------------------------------------------------------------------
# CORE PART
# ----------------------------------------------------------------------
FREERTOS_C_SOURCES = croutine.c
FREERTOS_C_SOURCES += event_groups.c
FREERTOS_C_SOURCES += list.c
FREERTOS_C_SOURCES += queue.c
FREERTOS_C_SOURCES += stream_buffer.c
FREERTOS_C_SOURCES += tasks.c
FREERTOS_C_SOURCES += timers.c

# ----------------------------------------------------------------------
# Add Platform port - Here file for RISC-V port
# ----------------------------------------------------------------------
FREERTOS_C_SOURCES += port.c
FREERTOS_S_SOURCES += portASM.S

# ----------------------------------------------------------------------
# Define HEAP managment model
# ----------------------------------------------------------------------
FREERTOS_HEAP_1_C		= heap_1.c
FREERTOS_HEAP_2_C		= heap_2.c
FREERTOS_HEAP_3_C		= heap_3.c
FREERTOS_HEAP_4_C		= heap_4.c
FREERTOS_HEAP_5_C		= heap_5.c

# ----------------------------------------------------------------------
# Includes Location
# ----------------------------------------------------------------------
FREERTOS_INCLUDES := -I${FREERTOS_DIR}/include
FREERTOS_INCLUDES += -I${FREERTOS_MEMMANG_DIR}
FREERTOS_INCLUDES += -I${FREERTOS_DIR}/portable/GCC/RISC-V
FREERTOS_INCLUDES += -I${FREERTOS_DIR}/portable/GCC/RISC-V/chip_specific_extensions/RV32I_CLINT_no_extensions

# ----------------------------------------------------------------------
# Modify the VPATH
# ----------------------------------------------------------------------
VPATH:=${FREERTOS_DIR}:${FREERTOS_MEMMANG_DIR}:${FREERTOS_DIR}/portable/GCC/RISC-V:${VPATH}
