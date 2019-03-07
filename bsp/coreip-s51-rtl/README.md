The SiFive S51 Standard Core is a 64-bit embedded processor, fully compliant with the RISC-V ISA. A small-footprint, low-power design makes the S51 ideal for devices that require a tiny system controller in a larger 64-bit SoC. The S51 can also be used as a standalone controller for networking, storage, or other high-performance embedded applications.

This core target is suitable with Verilog RTL for verification and running application software building on top of freedom-metal libraries. The target supports:

- 1 hart with RV64IMAC core
- 4 hardware breakpoints
- Physical Memory Protection with 8 regions
- 16 local interrupts signal that can be connected to off core complex devices
- Up to 127 PLIC interrupt signals that can be connected to off core complex devices, with 7 priority levels
