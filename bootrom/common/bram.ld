OUTPUT_ARCH("riscv")
ENTRY(_start)

MEMORY
{
	rom (rx) : ORIGIN = 0x00001000, LENGTH = 4K
	ram (rwx) : ORIGIN = 0x80000000, LENGTH = 256M
}

SECTIONS
{
	PROVIDE(_rom = ORIGIN(rom));
	PROVIDE(_rom_end = _rom + LENGTH(rom));
	PROVIDE(_ram = ORIGIN(ram));
	PROVIDE(_ram_end = _ram + LENGTH(ram));

	.text : {
		PROVIDE(_ftext = .);
		*(.text.init)
		*(.text .text.* .gnu.linkonce.t.*)
		PROVIDE(_etext = .);
	} > rom

	.rodata : {
		*(.rodata .rodata.* .gnu.linkonce.r.*)
	} > rom

	.bss : ALIGN(8) {
		PROVIDE(_fbss = .);
		*(.bss .bss.* .gnu.linkonce.b.*)
		*(.sbss .sbss.* .gnu.linkonce.sb.*)
		. = ALIGN(8);
		PROVIDE(_ebss = .);
	} > ram

	. += 0x1000;
	PROVIDE(_sp = NEXT(0x1000));

	PROVIDE(_end = .);
}
