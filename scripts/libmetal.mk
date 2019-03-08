
#############################################################
# Compiles an instance of Metal targeted at $(TARGET)
#############################################################
METAL_SOURCE_PATH ?= freedom-metal
METAL_LDSCRIPT	   = $(BSP_DIR)/metal.lds
METAL_HEADER	   = $(BSP_DIR)/metal.h

.PHONY: metal
metal: $(BSP_DIR)/install/stamp

$(BSP_DIR)/build/Makefile:
	@rm -rf $(dir $@)
	@mkdir -p $(dir $@)
	cd $(dir $@) && \
		CFLAGS="$(RISCV_CFLAGS)" \
		$(abspath $(METAL_SOURCE_PATH)/configure) \
		--host=$(CROSS_COMPILE) \
		--prefix=$(abspath $(BSP_DIR)/install) \
		--disable-maintainer-mode \
		--with-preconfigured \
		--with-machine-name=$(TARGET) \
		--with-machine-header=$(abspath $(METAL_HEADER)) \
		--with-machine-ldscript=$(abspath $(METAL_LDSCRIPT)) \
		--with-builtin-libgloss
	touch -c $@

$(BSP_DIR)/install/stamp: $(BSP_DIR)/build/Makefile
	$(MAKE) -C $(abspath $(BSP_DIR)/build) install
	date > $@

$(BSP_DIR)/install/lib/libriscv%.a: $(BSP_DIR)/install/stamp ;@:

$(BSP_DIR)/install/lib/libmetal.a: $(BSP_DIR)/install/lib/libriscv__mmachine__$(TARGET).a
	cp $< $@

$(BSP_DIR)/install/lib/libmetal-gloss.a: $(BSP_DIR)/install/lib/libriscv__menv__metal.a
	cp $< $@

.PHONY: clean-metal
clean-metal:
	rm -rf $(BSP_DIR)/install
	rm -rf $(BSP_DIR)/build
clean: clean-metal

metal_install: metal
	$(MAKE) -C $(METAL_SOURCE_PATH) install

