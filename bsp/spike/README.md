The [Spike RISC-V ISA Simulator](https://github.com/riscv/riscv-isa-sim)
is a functional simulator of a RISC-V processor with one or more harts.

This target is ideal for those wishing to test on a particular combination of
RISC-V ISA extensions, including new extensions like the V vector extension.
Note, however, that supporting certain combinations of ISA extensions may
require a custom RISC-V embedded toolchain.

By default, this BSP supports the target emulated by Spike by default, which
provides:

- 1 hart with RV64IMAFDC
- A Memory Management Unit with SV48 Paging
- HTIF interface for standard I/O and shutdown

The options passed to Spike to change target emulation can be modified by
editing the `SPIKE_OPTIONS` varible in the `spike_options.sh` file in this
directory. After modifying this file, the BSP should be regenerated using
Freedom Devicetree Tools.
