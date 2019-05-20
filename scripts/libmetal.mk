
#############################################################
# Compiles an instance of Metal targeted at $(TARGET)
#############################################################
METAL_SOURCE_PATH ?= freedom-metal
METAL_LDSCRIPT	   = $(BSP_DIR)/metal.$(LINK_TARGET).lds
METAL_HEADER	   = $(BSP_DIR)/metal.h
METAL_INLINE       = $(BSP_DIR)/metal-inline.h
PLATFORM_HEADER	   = $(BSP_DIR)/metal-platform.h

METAL_PREFIX       = $(abspath $(BSP_DIR)/install)
METAL_BUILD_DIR    = $(abspath $(BSP_DIR)/build/$(CONFIGURATION))
METAL_LIB_DIR	   = $(abspath $(BSP_DIR)/install/lib/$(CONFIGURATION))

.PHONY: metal
metal: $(METAL_LIB_DIR)/stamp

$(METAL_BUILD_DIR)/Makefile:
	@rm -rf $(dir $@)
	@mkdir -p $(dir $@)
	cd $(dir $@) && \
		CFLAGS="$(RISCV_CFLAGS)" \
		$(abspath $(METAL_SOURCE_PATH)/configure) \
		--host=$(CROSS_COMPILE) \
		--prefix=$(METAL_PREFIX) \
		--libdir=$(METAL_LIB_DIR) \
		--disable-maintainer-mode \
		--with-preconfigured \
		--with-machine-name=$(TARGET) \
		--with-machine-header=$(abspath $(METAL_HEADER)) \
                --with-machine-inline=$(abspath $(METAL_INLINE)) \
		--with-platform-header=$(abspath $(PLATFORM_HEADER)) \
		--with-machine-ldscript=$(abspath $(METAL_LDSCRIPT)) \
		--with-builtin-libgloss
	touch -c $@

$(METAL_LIB_DIR)/stamp: $(BSP_DIR)/build/$(CONFIGURATION)/Makefile
	$(MAKE) -C $(abspath $(BSP_DIR)/build/$(CONFIGURATION)) install
	date > $@

$(METAL_LIB_DIR)/libriscv%.a: $(METAL_LIB_DIR)/stamp ;@:

$(METAL_LIB_DIR)/libmetal.a: $(METAL_LIB_DIR)/libriscv__mmachine__$(TARGET).a
	cp $< $@

$(METAL_LIB_DIR)/libmetal-gloss.a: $(METAL_LIB_DIR)/libriscv__menv__metal.a
	cp $< $@

# If we're cleaning the last Metal library for a TARGET, then remove
# the install directory, otherwise just remove the built libs for that
# CONFIGURATION.
ifeq ($(words $(wildcard $(METAL_PREFIX)/lib/*)),1)
METAL_CLEAN = $(METAL_PREFIX)
else
METAL_CLEAN = $(METAL_LIB_DIR)
endif

.PHONY: clean-metal
clean-metal:
	rm -rf $(METAL_CLEAN)
	rm -rf $(METAL_BUILD_DIR)
clean: clean-metal

metal_install: metal
	$(MAKE) -C $(METAL_SOURCE_PATH) install

