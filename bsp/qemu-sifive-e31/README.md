SiFive QEMU E31 is a virtual development platform matching the Freedom E310 (with more memory though).
It’s the best way to start prototyping and developing your RISC‑V applications.

This target is ideal for getting familiarize with RISC-V ISA instructions set and freedom-metal libraries. It supports:

- 1 hart with RV32IMAC core
- 4 hardware breakpoints
- 16 local interrupts signal that can be connected to off core complex devices
- Up to 127 PLIC interrupt signals that can be connected to off core complex devices, with 7 priority levels
- GPIO memory with 16 interrupt lines
- SPI memory with 1 interrupt line
- Serial port with 1 interrupt line
- 1 RGB LEDS
- DTIM memory with 4M bytes

This BSP matches the QEMU code in https://github.com/sifive/freedom-qemu
