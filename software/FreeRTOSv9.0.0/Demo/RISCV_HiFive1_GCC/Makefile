include ./Makefile.inc


FREERTOS_SRC = \
	$(FREERTOS_SOURCE_DIR)/croutine.c \
	$(FREERTOS_SOURCE_DIR)/list.c \
	$(FREERTOS_SOURCE_DIR)/queue.c \
	$(FREERTOS_SOURCE_DIR)/tasks.c \
	$(FREERTOS_SOURCE_DIR)/timers.c \
	$(FREERTOS_SOURCE_DIR)/portable/MemMang/heap_4.c \


PORT_SRC = $(FREERTOS_SOURCE_DIR)/portable/GCC/RISCV/port.c
PORT_ASM = $(FREERTOS_SOURCE_DIR)/portable/GCC/RISCV/portasm.S

DEMO_SRC +=	$(BSP_BASE)/env/freedom-e300-hifive1/init.c
DEMO_SRC +=	$(BSP_BASE)/drivers/plic/plic_driver.c
DEMO_SRC +=	main.c

DEMO_ASM += entry.S
DEMO_ASM += start.S

INCLUDES = \
	-I. \
	-I$(FREERTOS_SOURCE_DIR)/include \
	-I$(FREERTOS_SOURCE_DIR)/portable/GCC/RISCV \
	-I../Common/include \
	-I$(BSP_BASE)/include 	\
	-I$(BSP_BASE)/drivers	\
 	-I$(BSP_BASE)/env	\
 	-I$(BSP_BASE)/env/$(BOARD)	

DEFINES = \
	-D_HIFIVE 

CFLAGS = \
	$(WARNINGS) $(INCLUDES) $(DEFINES) \
	-ffunction-sections -fdata-sections -Wall -c -fno-builtin-printf -include sys/cdefs.h

AFLAGS = \
	$(WARNINGS) $(INCLUDES) $(DEFINES) \
	-Wall -c -Wa,-march=rv32imac -x assembler-with-cpp

GCCVER 	= $(shell $(GCC) --version | grep gcc | cut -d" " -f9)

#
# Define all object files.
#
RTOS_OBJ = $(FREERTOS_SRC:.c=.o)
APP_OBJ  = $(APP_SRC:.c=.o)
PORT_OBJ = $(PORT_SRC:.c=.o)
DEMO_OBJ = $(DEMO_SRC:.c=.o)
DEMO_ASM_OBJ = $(DEMO_ASM:.S=.o)
PORT_ASM_OBJ = $(PORT_ASM:.S=.o)
OBJS =  $(PORT_ASM_OBJ) $(PORT_OBJ) $(RTOS_OBJ) $(DEMO_OBJ) $(APP_OBJ) $(DEMO_ASM_OBJ)

LDFLAGS	 = -T link.lds -nostartfiles -static -nostdlib -Wl,-Map=$(PROG).map -Wl,--wrap=malloc -Wl,--wrap=free\
-Wl,--wrap=open -Wl,--wrap=lseek -Wl,--wrap=read -Wl,--wrap=write -Wl,--wrap=fstat -Wl,--wrap=stat\
-Wl,--wrap=close -Wl,--wrap=link -Wl,--wrap=unlink -Wl,--wrap=execve -Wl,--wrap=fork -Wl,--wrap=getpid\
-Wl,--wrap=kill -Wl,--wrap=wait -Wl,--wrap=isatty -Wl,--wrap=times -Wl,--wrap=sbrk -Wl,--wrap=_exit\
-L. -Wl,--start-group -Wl,--end-group -Wl,-gc-sections

LIBS	 = -lc -lgcc -lwrap-hifive1

%.o: %.c
	@echo "    CC $<"
	@$(GCC) -c $(CC_OPTS) $(CFLAGS) -o $@ $<

%.o: %.S
	@echo "    CC $<"
	@$(GCC) -c $(CC_OPTS)  $(AFLAGS) -o $@ $<

all: $(PROG).elf

$(PROG).elf  : $(OBJS) Makefile 
	@echo Linking....
	@$(GCC) -o $@ $(CC_OPTS) $(LDFLAGS) $(OBJS) $(LIBS)
	@$(OBJDUMP) -S $(PROG).elf > $(PROG).asm	
	@$(SIZE) $(PROG).elf 
	@echo Completed $@

clean :
	@rm -f $(OBJS)
	@rm -f $(PROG).elf 
	@rm -f $(PROG).map
	@rm -f $(PROG).asm

force_true:
	@true

#-------------------------------------------------------------

#############################################################
# This Section is for uploading a program to SPI Flash
#############################################################
OPENOCDCFG ?= $(BSP_BASE)/env/$(BOARD)/openocd.cfg
OPENOCDARGS += -f $(OPENOCDCFG)

GDB_UPLOAD_ARGS ?= --batch

GDB_UPLOAD_CMDS += -ex "set remotetimeout 240"
GDB_UPLOAD_CMDS += -ex "target extended-remote localhost:3333"
GDB_UPLOAD_CMDS += -ex "monitor reset halt"
GDB_UPLOAD_CMDS += -ex "monitor flash protect 0 64 last off"
GDB_UPLOAD_CMDS += -ex "load"
GDB_UPLOAD_CMDS += -ex "monitor resume"
GDB_UPLOAD_CMDS += -ex "monitor shutdown"
GDB_UPLOAD_CMDS += -ex "quit"

upload:
	$(RISCV_OPENOCD) $(OPENOCDARGS) & \
	$(GDB) $(PROG).elf $(GDB_UPLOAD_ARGS) $(GDB_UPLOAD_CMDS);\
	echo "Successfully uploaded '$(PROG)' to $(BOARD)."

#############################################################
# This Section is for launching the debugger
#############################################################

run_openocd:
	$(RISCV_OPENOCD) $(OPENOCDARGS)

GDBCMDS += -ex "set remotetimeout 240"
GDBCMDS += -ex "target extended-remote localhost:3333"

run_gdb:
	$(GDB) $(PROG).elf $(GDBARGS) $(GDBCMDS)

