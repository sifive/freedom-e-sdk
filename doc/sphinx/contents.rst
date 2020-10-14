Contents of the SDK
===================

Supported Targets
-----------------

Freedom E SDK comes packaged with the following board support packages under the
``bsp/`` directory.

- `SiFive HiFive 1 <https://www.sifive.com/boards/hifive1>`_

  - sifive-hifive1

- `SiFive HiFive 1 Rev B <https://www.sifive.com/boards/hifive1-rev-b>`_

  - sifive-hifive1-revb

- `SiFive HiFive Unleashed <https://www.sifive.com/boards/hifive-unleashed>`_

  - sifive-hifive-unleashed

- `SiFive Freedom E310 Arty <https://github.com/sifive/freedom>`_

  - freedom-e310-arty

- `QEMU Emulation of the SiFive E31 <https://github.com/sifive/freedom-tools>`_

  - qemu-sifive-e31

- `QEMU Emulation of the SiFive S51 <https://github.com/sifive/freedom-tools>`_

  - qemu-sifive-s51

- `QEMU Emulation of the SiFive U54 <https://github.com/sifive/freedom-tools>`_

  - qemu-sifive-u54

- `QEMU Emulation of the SiFive U54MC <https://github.com/sifive/freedom-tools>`_

  - qemu-sifive-u54mc

- `Spike RISC-V ISA EMulator <https://github.com/riscv/riscv-isa-sim>`_

  - spike

The board support files for the Freedom Metal library are located entirely
within a single target directory in ``bsp/<target>/``. For example, the HiFive 1
board support files for Freedom Metal are entirely within ``bsp/sifive-hifive1/``
and consist of the following:

* ``core.dts``

  - The DeviceTree description of the target. This file is used to parameterize
    the Freedom Metal library to the target device. It is included as reference
    so that users of Freedom Metal are aware of what features and peripherals
    are available on the target.

* ``design.dts``

  - The DeviceTree Overlay for describing the chosen node, and testrams.

* ``design.svd``

  - CMSIS SVD XML file used for describing the design peripherals, their
    registers register-fields in the device with offset information on where
    they are all mapped into the memory space.

* ``metal.h``

  - The Freedom Metal machine header which is used internally to Freedom Metal
    to instantiate structures to support the target device.

* ``metal-platform.h``

  - The Freedom Metal platform header which is used internally to Freedom Metal
    as the source for each device's memory-mapped base address, memory-mapped
    size, properties, and memory-mapped register offsets.

* ``metal.%.lds``

  - Linker scripts for the target device. Scripts other than ``metal.default.lds``
    are used for alternative memory layouts.

* ``openocd.cfg`` (for development board and FPGA targets)

  - Used to configure OpenOCD for flashing and debugging the target device.

* ``settings.mk``

  - Used to set ``-march`` and ``-mabi`` arguments to the RISC-V GNU Toolchain
    as well as configure target-specific build steps.

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

- atomics

  - Demonstrates how to use the Metal Atomic API to leverage the RISC-V atomic
    instruction set.

- cflush

  - A simple example demo how to use cflush (Data) L1 and use FENCE to ensure flush
    complete. 

- clic-hardware-vector-interrupts

  - A simple example demonstrating the use of CLIC hardware vector interrupts

- clic-nested-interrupts

  - A simple example demonstrating how to use CLIC preemptive vector interrupts

- clic-nonvector-interrupts

  - A simple example demonstrating how to use CLIC non vector interrupts

- clic-selective-vector-interrupts

  - A simple example demonstrating how to use CLIC selective vector interrupts

- coremark

  - "CoreMark" Benchmark Program that measures the performance of embedded
    microcrontrollers (MCU)

- csr

  - A simple example demonstrating the use of metal APIs for CSR register set
    and get.

- dhrystone

  - "Dhrystone" Benchmark Program by Reinhold P. Weicker

- empty

  - An empty project. Serves as a good starting point for your own program.

- example-buserror

  - Demonstrates how to use the SiFive Bus Error Unit in Freedom Metal

- example-freertos-blinky

  - A simple blinky starter application create just two tasks, one queue

- example-freertos-minimal

  - A simple starter example application to start FreeRTOS application

- example-freertos-pmp-blinky

  - A simple blinky starter application create just two tasks, one queue.
    In this example we use the PMP in order to restrict the acces to peripheral,
    in order to access to global variable we grant access to bss to each task.

- example-i2c

  - Demonstrates usage of the I2C API to communicate with I2C slaves.

- example-itim

  - Demonstrates how to statically link application code into the Instruction
    Tightly Integrated Memory (ITIM) if an ITIM is present on the target.

- example-pmp

  - Demonstrates how to configure a Physical Memory Protection (PMP) region

- example-pwm

  - Demonstrates usage of the PWM API for waveform generation.

- example-rtc

  - Demonstrates how to use the RTC API to start a Real-Time Clock, set a compare
    value, and handle an interrupt when the clock matches the compare value.

- example-spi

  - Demonstrates how to use the SPI API to transfer bytes to a peripheral
    
- example-watchdog

  - Demonstrates how to use the Watchdog API to set a watchdog timer to trigger an
    interrupt on timeout.

- example-user-mode

  - Demonstrates how to drop to user mode privilege level.

- example-user-syscall

  - Demonstrates how to register a handler for the "syscall from user mode" exception,
    drop to the user mode privilege level, and then issue a syscall.

- example-watchdog

  - Demonstrates how to use the Watchdog API to set a watchdog timer to trigger an
    interrupt on timeout.

- hello

  - Prints "Hello, World!" to stdout, if a serial device is present on the target.

- local-interrupt

  - Demonstrates how to register a handler for and trigger a local interrupt

- local-vector-interrupt

  - A simple example using "Timer and Software Interrupts" in CLINT vector mode.

- mem-latency

  - A memory test that measure the latency at different cache layers and memory blocks

- minimal-boot

  - Demonstrates how to replace the Metal constructors and replace them with your own.

- multicore-hello

  - An example which demonstrates how to run code on multiple CPU harts and to use
    the Metal Lock API to use a spinlock as a mutex.

- plic-interrupts
  
  - A simple example demonstrating how PLIC interrupts get uses on an Arty board.

- return-fail

  - Returns status code 1 indicating program failure.

- return-pass

  - Returns status code 0 indicating program success.

- sifive-welcome

  - Prints a welcome message and interacts with the LEDs.

- software-interrupt

  - Demonstrates how to register a handler for and trigger a software interrupt

- test-coreip

  - Assembly test code which executes instructions and checks for expected results.
    The tests are designed to work on SiFive CPU designs in RTL simulation or on the
    Arty FPGA board.

- timer-interrupt

  - Demonstrates how to register a handler for and trigger a timer interrupt

- uart-interrupt

  - A simple "UART Interrupt" example using metal-interrupts APIs for ARTY board.

- example-hpm

  - Demonstrates usage of the RISC-V hardware performance counter APIs.

- example-l2pm

  - Demonstrates usage of Sifive L2 performance monitor counter APIs to capture L2 cache event logs.

- example-l2pf

  - Example for usage and measuring effectiveness of SiFive L2 Prefetcher.

- example-lim

  - Demonstrates how to designate a function to be linked into the LIM (Loosely-Integrated Memory).
