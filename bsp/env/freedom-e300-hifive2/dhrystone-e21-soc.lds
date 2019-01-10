OUTPUT_ARCH("riscv")
ENTRY(_start)

MEMORY
{
  flash (rxai!w) : ORIGIN = 0x20400000, LENGTH = 512M
  sram0_mem (wxa!ri) : ORIGIN = 0x80000000, LENGTH = 32K
  sram1_mem (wxa!ri) : ORIGIN = 0x80008000, LENGTH = 32K  
}


PHDRS
{
  
  text PT_LOAD;
  rodata PT_LOAD;
  data PT_LOAD;
  bss PT_LOAD;
  
}

SECTIONS
{
  PROVIDE(_ram = ORIGIN(sram1_mem));
  PROVIDE(_ram_end = _ram + LENGTH(sram1_mem));

  

  .text ALIGN((ORIGIN(sram0_mem) + 0x0), 64) : AT(ALIGN((ORIGIN(sram0_mem) + 0x0), 64)) {
    PROVIDE(_ftext = .);
    *(.text.init)
    *(.text.unlikely .text.unlikely.*)
    *(.text .text.* .gnu.linkonce.t.*)
    PROVIDE(_etext = .);
    . += 0x40; /* to create a gap between .text and .data b/c ifetch can fetch ahead from .data */
  } >sram0_mem  :text

  .eh_frame ALIGN((ADDR(.text) + SIZEOF(.text)), 64) : AT(ALIGN((LOADADDR(.text) + SIZEOF(.text)), 64)) {
    *(.eh_frame)
  } >sram0_mem  :text

  .rodata ALIGN((ORIGIN(sram1_mem) + 0x0), 64) : AT(ALIGN((LOADADDR(.eh_frame) + SIZEOF(.eh_frame)), 64)) ALIGN_WITH_INPUT {
    *(.rodata .rodata.* .gnu.linkonce.r.*)
  } >sram1_mem  :rodata

  .srodata ALIGN((ADDR(.rodata) + SIZEOF(.rodata)), 64) : AT(ALIGN((LOADADDR(.rodata) + SIZEOF(.rodata)), 64)) ALIGN_WITH_INPUT {
    *(.srodata.cst16)
    *(.srodata.cst8)
    *(.srodata.cst4)
    *(.srodata.cst2)
    *(.srodata.*)
  } >sram1_mem  :rodata

  .data ALIGN((ADDR(.srodata) + SIZEOF(.srodata)), 64) : AT(ALIGN((LOADADDR(.srodata) + SIZEOF(.srodata)), 64)) ALIGN_WITH_INPUT {
    *(.data .data.* .gnu.linkonce.d.*)
    *(.tohost) /* TODO: Support sections that aren't explicitly listed in this linker script */
  } >sram1_mem  :data

  .sdata ALIGN((ADDR(.data) + SIZEOF(.data)), 64) : AT(ALIGN((LOADADDR(.data) + SIZEOF(.data)), 64)) ALIGN_WITH_INPUT {
    *(.sdata .sdata.* .gnu.linkonce.s.*)
  } >sram1_mem  :data

  PROVIDE(_data = ADDR(.rodata));
  PROVIDE(_data_lma = LOADADDR(.rodata));
  PROVIDE(_edata = .);

  .bss ALIGN((ADDR(.sdata) + SIZEOF(.sdata)), 64) : AT(ALIGN((ORIGIN(sram1_mem) + 0x0), 64)) ALIGN(8) {
    PROVIDE(_fbss = .);
    PROVIDE(__global_pointer$ = . + 0x7C0);
    *(.sbss .sbss.* .gnu.linkonce.sb.*)
    *(.bss .bss.* .gnu.linkonce.b.*)
    . = ALIGN(8);
    PROVIDE(_ebss = .);
  } >sram1_mem  :bss

  

  PROVIDE(_end = .);

  /*
   * heap_stack_region_usable_end: (ORIGIN(sram1_mem) + LENGTH(sram1_mem))
   * heap_stack_min_size: 4096
   * heap_stack_max_size: 1048576
   */
  PROVIDE(_sp = ALIGN(MIN((ORIGIN(sram1_mem) + LENGTH(sram1_mem)), _ebss + 1048576) - 7, 8));
  /*
   * Protect top of stack from heap, but this will not protect the heap from
   * stack overruns.
   */
  PROVIDE(_heap_end = _sp - 0x800);

  /* This section is a noop and is only used for the ASSERT */
  .stack : {
    ASSERT(_sp >= (_ebss + 4096), "Error: No room left for the heap and stack");
  }
}
