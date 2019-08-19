OUTPUT_ARCH("riscv")

ENTRY(_enter)

MEMORY
{
	ram (wxa!ri) : ORIGIN = 0x80000000, LENGTH = 0x1f80000000
	itim (wx!rai) : ORIGIN = 0x1800000, LENGTH = 0x4000
}

PHDRS
{
	ram PT_LOAD;
	ram_init PT_LOAD;
	itim PT_LOAD;
	itim_init PT_LOAD;
	tls PT_TLS;
}

SECTIONS
{

	__stack_size = DEFINED(__stack_size) ? __stack_size : 0x400;
	PROVIDE(__stack_size = __stack_size);
	__heap_size = DEFINED(__heap_size) ? __heap_size : 0x800;
	PROVIDE(__metal_boot_hart = 1);
	PROVIDE(__metal_chicken_bit = 0);


	.init : {
		KEEP (*(.text.metal.init.enter))
		KEEP (*(.text.metal.init.*))
		KEEP (*(SORT_NONE(.init)))
		KEEP (*(.text.libgloss.start))
	} >ram AT>ram :ram

	.fini : {
		KEEP (*(SORT_NONE(.fini)))
	} >ram AT>ram :ram



	.text : {
		*(.text.unlikely .text.unlikely.*)
		*(.text.startup .text.startup.*)
		*(.text .text.*)
		*(.gnu.linkonce.t.*)
	} >ram AT>ram :ram

	PROVIDE (__etext = .);
	PROVIDE (_etext = .);
	PROVIDE (etext = .);


	.rodata : {
		*(.rdata)
		*(.rodata .rodata.*)
		*(.gnu.linkonce.r.*)
		. = ALIGN(8);
		*(.srodata.cst16)
		*(.srodata.cst8)
		*(.srodata.cst4)
		*(.srodata.cst2)
		*(.srodata .srodata.*)
	} >ram AT>ram :ram


	. = ALIGN(8);

	.preinit_array : {
		PROVIDE_HIDDEN (__preinit_array_start = .);
		KEEP (*(.preinit_array))
		PROVIDE_HIDDEN (__preinit_array_end = .);
	} >ram AT>ram :ram

	.init_array : {
		PROVIDE_HIDDEN (__init_array_start = .);
		KEEP (*(SORT_BY_INIT_PRIORITY(.init_array.*) SORT_BY_INIT_PRIORITY(.ctors.*)))
		KEEP (*(.init_array EXCLUDE_FILE (*crtbegin.o *crtbegin?.o *crtend.o *crtend?.o ) .ctors))
		PROVIDE_HIDDEN (__init_array_end = .);
		PROVIDE_HIDDEN ( metal_constructors_start = .);
		KEEP (*(SORT_BY_INIT_PRIORITY(.metal.init_array.*)));
		KEEP (*(.metal.init_array));
		PROVIDE_HIDDEN ( metal_constructors_end = .);
	} >ram AT>ram :ram

	.fini_array : {
		PROVIDE_HIDDEN (__fini_array_start = .);
		KEEP (*(SORT_BY_INIT_PRIORITY(.fini_array.*) SORT_BY_INIT_PRIORITY(.dtors.*)))
		KEEP (*(.fini_array EXCLUDE_FILE (*crtbegin.o *crtbegin?.o *crtend.o *crtend?.o ) .dtors))
		PROVIDE_HIDDEN (__fini_array_end = .);
		PROVIDE_HIDDEN ( metal_destructors_start = .);
		KEEP (*(SORT_BY_INIT_PRIORITY(.metal.fini_array.*)));
		KEEP (*(.metal.fini_array));
		PROVIDE_HIDDEN ( metal_destructors_end = .);
	} >ram AT>ram :ram

	.ctors : {
		KEEP (*crtbegin.o(.ctors))
		KEEP (*crtbegin?.o(.ctors))
		KEEP (*(EXCLUDE_FILE (*crtend.o *crtend?.o ) .ctors))
		KEEP (*(SORT(.ctors.*)))
		KEEP (*(.ctors))
		KEEP (*(.metal.ctors metal.ctors.*));
	} >ram AT>ram :ram

	.dtors : {
		KEEP (*crtbegin.o(.dtors))
		KEEP (*crtbegin?.o(.dtors))
		KEEP (*(EXCLUDE_FILE (*crtend.o *crtend?.o ) .dtors))
		KEEP (*(SORT(.dtors.*)))
		KEEP (*(.dtors))
		KEEP (*(.metal.dtors metal.dtors.*));
	} >ram AT>ram :ram



	.itim : ALIGN(8) {
		*(.itim .itim.*)
	} >itim AT>ram :itim_init

	PROVIDE( metal_segment_itim_source_start = LOADADDR(.itim) );
	PROVIDE( metal_segment_itim_target_start = ADDR(.itim) );
	PROVIDE( metal_segment_itim_target_end = ADDR(.itim) + SIZEOF(.itim) );


	.data : ALIGN(8) {
		*(.data .data.*)
		*(.gnu.linkonce.d.*)
		. = ALIGN(8);
		PROVIDE( __global_pointer$ = . + 0x800 );
		*(.sdata .sdata.* .sdata2.*)
		*(.gnu.linkonce.s.*)
		. = ALIGN(8);
		*(.srodata.cst16)
		*(.srodata.cst8)
		*(.srodata.cst4)
		*(.srodata.cst2)
		*(.srodata .srodata.*)
		. = ALIGN(8);
		*(.rdata)
		*(.rodata .rodata.*)
		*(.gnu.linkonce.r.*)
	} >ram AT>ram :ram_init

	.tdata : {
		PROVIDE( __tls_base = . );
		*(.tdata .tdata.* .gnu.linkonce.td.*)
	} >ram AT>ram :tls :ram_init

	PROVIDE( metal_segment_data_source_start = LOADADDR(.data) );
	PROVIDE( metal_segment_data_target_start = ADDR(.data) );
	PROVIDE( __tdata_source = LOADADDR(.tdata) );
	PROVIDE( __tdata_size = SIZEOF(.tdata) );
	PROVIDE( _edata = . );
	PROVIDE( edata = . );
	PROVIDE( metal_segment_data_target_end = . );


	.tbss : {
		*(.tbss .tbss.* .gnu.linkonce.tb.*)
		*(.tcommon .tcommon.*)
		PROVIDE( __tls_end = . );
	} >ram AT>ram :tls :ram
	PROVIDE( __tbss_size = SIZEOF(.tbss));
	PROVIDE( __tls_size = __tls_end - __tls_base );

	.tbss_space : {
		. = . + __tbss_size;
	} >ram AT>ram :ram

	.bss : ALIGN(8) {
		*(.sbss*)
		*(.gnu.linkonce.sb.*)
		*(.bss .bss.*)
		*(.gnu.linkonce.b.*)
		*(COMMON)
	} >ram AT>ram :ram
	PROVIDE( metal_segment_bss_target_start = ADDR(.tbss) );
	PROVIDE( metal_segment_bss_target_end = . );

	.stack : {
		PROVIDE(metal_segment_stack_begin = .);
		. += __stack_size;
		PROVIDE( _sp = . );
		. += __stack_size;
		. += __stack_size;
		. += __stack_size;
		. += __stack_size;
		PROVIDE(metal_segment_stack_end = .);
	} >ram AT>ram :ram

	.heap : {
		PROVIDE( metal_segment_heap_target_start = . );
		. = DEFINED(__heap_max) ? LENGTH(ram) - ( . - ORIGIN(ram) ) : __heap_size;
		PROVIDE( metal_segment_heap_target_end = . );
		PROVIDE( _heap_end = . );
	} >ram AT>ram :ram


}

