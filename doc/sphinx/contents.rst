Contents of the SDK
===================

Supported Targets
-----------------

Freedom E SDK comes packaged with the following board support packages under the
``bsp/`` directory.

- `SiFive HiFive 1 <https://www.sifive.com/boards/hifive1>`_

  - sifive-hifive1

- SiFive HiFive 1 Rev B

  - sifive-hifive1-revb

- `SiFive Freedom E310 Arty <https://github.com/sifive/freedom>`_

  - freedom-e310-arty

- SiFive CoreIP RTL

  - coreip-e20-rtl
  - coreip-e21-rtl
  - coreip-e24-rtl
  - coreip-e31-rtl
  - coreip-s51-rtl
  - coreip-s54-rtl
  - coreip-e76-rtl
  - coreip-s76-rtl

- SiFive CoreIP Arty FPGA Evaluation targets

  - coreip-e20-arty
  - coreip-e21-arty
  - coreip-e24-arty
  - coreip-e31-arty
  - coreip-s51-arty
  - coreip-s54-arty
  - coreip-e76-arty
  - coreip-s76-arty

The board support files for the Freedom Metal library are located entirely
within a single target directory in ``bsp/<target>/``. For example, the HiFive 1
board support files for Freedom Metal are entirely within ``bsp/sifive-hifive1/``
and consist of the following:

* ``design.dts``

  - The DeviceTree description of the target. This file is used to parameterize
    the Freedom Metal library to the target device. It is included as reference
    so that users of Freedom Metal are aware of what features and peripherals
    are available on the target.

* ``metal.h``

  - The Freedom Metal machine header which is used internally to Freedom Metal
    to instantiate structures to support the target device.

* ``metal.lds``

  - The linker script for the target device.

* ``openocd.cfg`` (for development board and FPGA targets)

  - Used to configure OpenOCD for flashing and debugging the target device.

* ``settings.mk``

  - Used to set ``-march`` and ``-mabi`` arguments to the RISC-V GNU Toolchain.

Freedom Metal
-------------

`Freedom Metal <https://github.com/sifive/freedom-metal>`_
(`Documentation <https://sifive.github.io/freedom-metal-docs/index.html>`_)
is a library developed by SiFive for writing portable software for all of SiFive's
RISC-V IP, RISC-V FPGA evaluation images, and development boards. Programs written
against the Freedom Metal API are intended to build and run for all SiFive RISC-V
targets. This makes Freedom Metal suitable for writing portable tests, bare metal
application programming, and as a hardware abstraction layer for porting
operating systems to RISC-V.

Freedom E SDK is a consumer of the Freedom Metal library. Freedom Metal allows the
SDK examples to be portable to all supported SiFive targets.

Example Programs
----------------

The example programs can be found under the ``software/`` directory.

- empty

  - An empty project. Serves as a good starting point for your own program.

- hello

  - Prints "Hello, World!" to stdout, if a serial device is present on the target.

- example-coreip-welcome

  - Prints a welcome message and interacts with the LEDs.

- return-pass

  - Returns status code 0 indicating program success.

- return-fail

  - Returns status code 1 indicating program failure.

- example-itim

  - Demonstrates how to statically link application code into the Instruction
    Tightly Integrated Memory (ITIM) if an ITIM is present on the target.

- software-interrupt

  - Demonstrates how to register a handler for and trigger a software interrupt

- timer-interrupt

  - Demonstrates how to register a handler for and trigger a timer interrupt

- local-interrupt

  - Demonstrates how to register a handler for and trigger a local interrupt

- example-pmp

  - Demonstrates how to configure a Physical Memory Protection (PMP) region

- example-spi

  - Demonstrates how to use the SPI API to transfer bytes to a peripheral
