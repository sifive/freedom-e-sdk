The SiFive E34 Standard Core adds single-precision floating-point to the SiFive E31 Standard Core, the world’s most deployed RISC-V core. The E34 enables advanced applications which require hardware floating-point capabilities such as signal processing and motor control.

This core target is suitable with Verilog RTL for verification and running application software building on top of freedom-metal libraries. The target supports:

- 1 hart with RV32IMAFC core
- 4 hardware breakpoints
- Physical Memory Protection with 8 regions
- 16 local interrupts signal that can be connected to off core complex devices
- Up to 127 PLIC interrupt signals that can be connected to off core complex devices, with 7 priority levels
