The [Freedom E310 Arty](https://github.com/sifive/freedom) is a completely open-source
implementation of RISC-V using the Rocket Chip Generator, designed for use with
the [Digilent Arty FPGA Evaluation Kit](https://www.xilinx.com/products/boards-and-kits/arty.html).

This target is ideal for getting familiarize with RISC-V ISA instructions set and
freedom-metal libraries. It supports:

- 1 hart with RV32IMAC core
- 4 hardware breakpoints
- 16 local interrupts signal that can be connected to off core complex devices
- Up to 26 PLIC interrupt signals that can be connected to off core complex devices, with 7 priority levels
- GPIO with 16 interrupt lines
- SPI memory with 1 interrupt line
- Serial port with 1 interrupt line
