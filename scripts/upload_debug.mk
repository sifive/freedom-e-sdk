#############################################################
# Upload and Debug
#############################################################

ifneq ($(RISCV_OPENOCD_PATH),)
RISCV_OPENOCD=$(RISCV_OPENOCD_PATH)/bin/openocd
else
#if RISCV_OPENOCD_PATH is not set, just look on the PATH
RISCV_OPENOCD=openocd
endif

ifneq ($(filter jlink,$(TARGET_TAGS)),)
upload: $(PROGRAM_HEX)
	scripts/upload --hex $(PROGRAM_HEX) --jlink $(SEGGER_JLINK_EXE)
else
upload: $(PROGRAM_ELF)
	scripts/upload --elf $(PROGRAM_ELF) --openocd $(RISCV_OPENOCD) --gdb $(RISCV_GDB) --openocd-config $(BSP_DIR)/openocd.cfg
endif

ifneq ($(filter jlink,$(TARGET_TAGS)),)
debug: $(PROGRAM_ELF)
	scripts/debug --elf $(PROGRAM_ELF) --jlink $(SEGGER_JLINK_GDB_SERVER) --gdb $(RISCV_GDB)
else
debug: $(PROGRAM_ELF)
	scripts/debug --elf $(PROGRAM_ELF) --openocd $(RISCV_OPENOCD) --gdb $(RISCV_GDB) --openocd-config $(BSP_DIR)/openocd.cfg
endif

ifeq ($(findstring qemu,$(TARGET)),qemu)
ifeq ($(findstring rv32,$(RISCV_ARCH)),rv32)
simulate: $(PROGRAM_ELF)
	scripts/simulate --elf $(PROGRAM_ELF) --qemu $(QEMU_RISCV32) --qemu-config $(BSP_DIR)/qemu.cfg
else # findstring rv32
simulate: $(PROGRAM_ELF)
	scripts/simulate --elf $(PROGRAM_ELF) --qemu $(QEMU_RISCV64) --qemu-config $(BSP_DIR)/qemu.cfg
endif # findstring rv32
else # findstring qemu
ifeq ($(findstring spike,$(TARGET)),spike)
simulate: $(PROGRAM_ELF) $(BSP_DIR)/spike_options.sh
	. $(BSP_DIR)/spike_options.sh && scripts/simulate --elf $(PROGRAM_ELF) --spike $(shell which spike) ; echo "Spike exited with code $$?"
else
simulate:
	@echo "No supported emulator for target $(TARGET)!"
endif # findstring spike
endif # findstring qemu
