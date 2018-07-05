# Freedom Machine-mode Execution Environment

The standard RISC-V software stack defines machine-mode software as
running in a machine-mode execution environment, also known as an MEE.
This repository provides a MEE that is designed to run on SiFive's
Freedom platform devices.  As the MEE runs at machine mode it's not
designed with binary compatibility in mind but is instead tailored to a
specific machine.

## Describing a Target Machine

The MEE is not natively self-hosting and is therefor designed to be
cross compiled for a target machine.  This target machine is described
by a device tree file, which is then provided to the MEE's build scripts
in order to parameterize it for the target machine.

## MEE Interface

The whole point of the MEE is to define an interface against which
portable programs can be written.  Since this is machine-mode software
the degree of portability is very limited, but nontheless some about of
portability can reasonably be achieved.  Specifically, that means

* The existance of devices can be staticly probed.
* Devices exist behind a well-defined API that abstracts away their
  physical addresses.

This allows portable software to be written against the MEE that will
run on all SiFive systems that are capable of meeting its requirements.

### Internal Symbols vs Public Symbols

Any symbol beginning with `__mee_` is internal to the MEE and must not
be called or defined by user code.  Symbols beginning with `mee_` are
public interfaces and can be considered to be a stable API.  The best
documentation for most of these symbols are found in the code, but some
is listed below.

As the MEE is desgined for bare-metal development there is no stable ABI.

### Pre-C Environment

The MEE handles entering the C library's start routine, which is defined
by the symbol `_start`.  This symbol must be defined by the C library in
order to allow the MEE to do anything meaningful.

The MEE follows the standard RISC-V bootloader ABI when calling
`_start`:

* `a0` contains the hart ID.
* `a1` contains a pointer to the machine description.  The MEE always
  sets this to NULL, as machines are described staticly.
* `a2` contains a callback that should be called from within the child
  environment after it has initialized itself.

This can be described as a the C function `void _start(long hartid,
unsigned char *dtb, void (*after_init)(void))'.  Note that the MEE does
not initialize a C environment and therefor this cannot actually be a C
function -- for example, there may not be a stack.

### Special Sections

Many special sections are utilized by this MEE implementation in order
to allow compact code to be generated while still providing API
guarntees.  These sections are all named such that standard linker
scripts will produce the correct answer, albiet at some performance or
code size cost.  A list of interesting sections is described below:

* `.text.mee.nop`: Every sub-section in here will consist of exactly the
  same C function: `int func(...) { return -1; }`.  Functions that look
  like this are frequently weakly referenced in order to provide default
  implementations of MBI functionality that cannot be implemented on the
  given target.
