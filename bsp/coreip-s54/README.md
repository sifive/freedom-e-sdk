The SiFive S54 Standard Core is a 64-bit embedded processor that is fully-compliant with the RISC-V ISA. It adds support for the F and D standard extensions, which provide the S54 with double-precision floating-point capabilities.

The S54 is ideal for demanding applications such as avionics, signal processing, and industrial automation.

This core target is suitable with Verilog RTL for verification and running application software building on top of freedom-metal libraries. The target supports:

- 1 hart with RV64IMAFDC core
- 4 hardware breakpoints
- Physical Memory Protection with 8 regions
- 16 local interrupts signal that can be connected to off core complex devices
- Up to 255 PLIC interrupt signals that can be connected to off core complex devices, with 7 priority levels
