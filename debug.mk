###################################################
# Build Flags for the Debug Configuration
###################################################

# Set the optimization level
RISCV_ASFLAGS += -O0
RISCV_CFLAGS += -O0
RISCV_CXXFLAGS += -O0

# Enable debug
RISCV_ASFLAGS += -g
RISCV_CFLAGS += -g -mno-relax
RISCV_CXXFLAGS += -g -mno-relax
