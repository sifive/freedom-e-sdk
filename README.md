# SiFive Freedom E SDK README #

This repository, maintained by SiFive Inc, makes it easy to get started developing
software for the Freedom E and Freedom S Embedded RISC-V Platforms. This SDK
is intended to work on any target supported by SiFive's distributions of the
RISC-V GNU Toolchain.

[Documentation for Freedom E SDK is available here](https://sifive.github.io/freedom-e-sdk-docs/index.html)

### Under Construction ###

This repository is currently under construction as we transition from the
legacy Freedom E SDK API to the new Freedom Metal Compatibility Library.

#### What is Freedom Metal? ###

[Freedom Metal](https://github.com/sifive/freedom-metal) ([Documentation](https://sifive.github.io/freedom-metal-docs/index.html))
is a library developed by SiFive for writing portable software for all of SiFive's
RISC-V IP, RISC-V FPGA evaluation images, and development boards. Programs written
against the Freedom Metal API are intended to build and run for all SiFive RISC-V
targets. This makes Freedom Metal suitable for writing portable tests, bare metal
application programming, and as a hardware abstraction layer for porting
operating systems to RISC-V.

Consumers of E SDK should also be aware that as we make this transition,
we are still making refinements to the API provided by Freedom Metal. As such,
**the Freedom Metal API should be considered in beta** until we tag a stable release
of Freedom E SDK.

### Contents ###

#### Freedom Metal Compatibility Library ####

* Board Support Packages (found under `bsp/`)
  - Supported Targets:
    - [SiFive HiFive 1](https://www.sifive.com/boards/hifive1)
      - sifive-hifive1
    - [SiFive Freedom E310 Arty](https://github.com/sifive/freedom)
      - freedom-e310-arty
    - SiFive CoreIP
      - coreip-e31
      - coreip-s51
    - SiFive CoreIP Arty FPGA Evaluation targets
      - coreip-e31-arty
      - coreip-s51-arty
  - The board support files for the Freedom Metal library are located entirely
    within a single target directory in `bsp/<target>/`. For example, the HiFive 1
    board support files for Freedom Metal are entirely within `bsp/sifive-hifive1/`
    and consist of the following:
    * design.dts
      - The DeviceTree description of the target. This file is used to parameterize
        the Freedom Metal library to the target device. It is included as reference
        so that users of Freedom Metal are aware of what features and peripherals
        are available on the target.
    * metal.h
      - The Freedom Metal machine header which is used internally to Freedom Metal
        to instantiate structures to support the target device.
    * metal.lds
      - The linker script for the target device.
    * openocd.cfg (for development board and FPGA targets)
      - Used to configure OpenOCD for flashing and debugging the target device.
    * settings.mk
      - Used to set `-march` and `-mabi` arguments to the RISC-V GNU Toolchain.
* A Few Example Programs (found under `software/`)
  - hello
    - Prints "Hello, World!" to stdout, if a serial device is present on the target.
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
  - example-coreip-welcome
    - Prints the SiFive banner and blinks LEDs 
    
#### (Deprecated) Legacy Freedom E SDK Library ####

As we transition to supporting SiFive targets and examples with the new Freedom Metal
compatibility library, the legacy Freedom E SDK libraries and examples are still available
within this repository.

As we port legacy example programs to the new Freedom Metal API, we will remove
the legacy version of the examples from this repository.

* Board Support Packages (found under `bsp/env`)
  - Supported Targets:
    - SiFive HiFive 1
      - freedom-e300-hifive1
    - SiFive Freedom E310 Arty
      - freedom-e300-arty
    - SiFive CoreIP Arty FPGA Evaluation Targets (e.g. coreplexip-e31-arty)
      - coreip-e2-arty
      - coreplexip-e31-arty
      - coreplexip-e51-arty
  - The Legacy board support files are located as follows:
    * `bsp/env/`
      - Holds board-specific files for the Legacy API
    * `bsp/drivers/`
      - Holds legacy device drivers for the PLIC, CLIC, and PRCI
    * `bsp/include`
      - Holds legacy header files for the Legacy API
    * `bsp/libwrap`
      - Holds wrappers around libc for the Legacy API
* A Few Example Programs
  - asm\_main
  - clic\_vectored
  - coremark
  - coreplexip\_welcome
  - demo\_gpio
  - dhrystone
  - double\_tap\_dontboot
  - global\_interrupts
  - i2c\_demo
  - led\_fade
  - local\_interrupts
  - performance\_counters
  - smp
  - vectored\_interrupts
  - watchdog

Legacy examples can be built using the same commands as the Freedom Metal examples and simply
omitting the `BSP=metal` argument or substituting it with `BSP=legacy`.

### Setting up the SDK ###

#### Prerequisites ####

To use this SDK, you will need the following software available on your machine:

* GNU Make
* Git
* RISC-V GNU Toolchain
* RISC-V OpenOCD (for use with development board and FPGA targets)

##### Install the RISC-V Toolchain and OpenOCD #####

The RISC-V GNU Toolchain and OpenOCD are available from the SiFive Website at

https://www.sifive.com/boards

For OpenOCD and/or RISC-V GNU Toolchain, download the .tar.gz for your platform,
and unpack it to your desired location. Then, use the `RISCV_PATH` and
`RISCV_OPENOCD_PATH` variables when using the tools:

```
cp openocd-<date>-<platform>.tar.gz /my/desired/location/
cp riscv64-unknown-elf-gcc-<date>-<platform>.tar.gz /my/desired/location
cd /my/desired/location
tar -xvf openocd-<date>-<platform>.tar.gz
tar -xvf riscv64-unknown-elf-gcc-<date>-<platform>.tar.gz
export RISCV_OPENOCD_PATH=/my/desired/location/openocd
export RISCV_PATH=/my/desired/location/riscv64-unknown-elf-gcc-<date>-<version>
```

#### Cloning the Repository ####

This repository can be cloned by running the following commands:

```
git clone --recursive https://github.com/sifive/freedom-e-sdk.git
cd freedom-e-sdk
```

The `--recursive` option is required to clone the git submodules included in the
repository. If at first you omit the `--recursive` option, you can achieve
the same effect by updating submodules using the command:

```
git submodule update --init --recursive
```

### Updating your SDK ###

If you'd like to update your SDK to the latest version:

```
git pull origin master
git submodule update --init --recursive
```

### Using the Tools ###

To ease the transition for consumers of the Legacy SDK, we've namespaced
the new Freedom Metal examples behind the environment variable `BSP`. To use the
Freedom Metal examples, you may `export BSP=metal` in your shell environment, or simply
pass `BSP=metal` as an argument to your `make` invocations as you see in the following
example commands.

#### Building an Example ####

To compile a bare-metal RISC-V program:

```
make BSP=metal [PROGRAM=hello] [TARGET=sifive-hifive1] software
```

The square brackets in the above command indicate optional parameters for the
Make invocation. As you can see, the default values of these parameters tell
the build script to build the `hello` example for the `sifive-hifive1` target.
If, for example, you wished to build the `timer-interrupt` example for the S51
Arty FPGA Evaluation target, you would instead run the command

```
make BSP=metal PROGRAM=timer-interrupt TARGET=coreip-s51-arty software
```

#### Building a Legacy Example ####

The legacy examples can still be built by omitting `BSP=metal` or by substituting
`BSP=legacy`. For example, to build the legacy `demo_gpio` application for
HiFive 1, run:

```
make PROGRAM=demo_gpio TARGET=freedom-e300-hifive1 software
```

#### Uploading to the Target Board ####

```
make BSP=metal [PROGRAM=hello] [TARGET=sifive-hifive1] upload
```

#### Debugging a Target Program ####

```
make BSP=metal [PROGRAM=hello] [TARGET=sifive-hifive1] debug
```

#### Cleaning a Target Program Build Directory ####

```
make BSP=metal [PROGRAM=hello] [TARGET=sifive-hifive1] clean
```

#### Create a Standalone Project ####

You can export a program to a standalone project directory using the `standalone`
target. The resulting project will be locked to a specific `TARGET`. Note
that this functionality is only supported for Freedom Metal programs, not the
Legacy Freedom E SDK.

`STANDALONE_DEST` is a required argument to provide the desired project location.

You can include the argument `INCLUDE_METAL_SOURCES=1` if you would like to
include the sources for the Freedom Metal library in the generated standalone
project. If this argument is not included, then the Freedom Metal library will
be included in the generated project as a pre-built archive.

```
make BSP=metal [PROGRAM=hello] [TARGET=sifive-hifive1] [INCLUDE_METAL_SOURCES=1] STANDALONE_DEST=/path/to/desired/location standalone
```

Run `make help` for more commands.

### Benchmarking ###

The Dhrystone and CoreMark benchmarks are still only supported by the Legacy
Freedom E SDK. When we port the benchmarks to Freedom Metal, we will update
this section to describe the updated build steps.

#### Dhrystone ####

After setting up the software and debug toolchains, you can build and
execute everyone's favorite benchmark as follows:

- Compile the benchmark with the command `make software TARGET=freedom-e300-hifive1 PROGRAM=dhrystone LINK_TARGET=dhrystone`. Note that a slightly different linker file is used for Dhrystone which stores read only data in DTIM instead of external flash.
- Run on the HiFive1 board with the command `make upload TARGET=freedom-e300-hifive1 PROGRAM=dhrystone`.
  This will take a few minutes.  Sample output is provided below.
- Compute DMIPS by dividing the Dhrystones per Second result by 1757, which
  was the VAX 11/780's performance.  In the example below, 729927 / 1757 =
  415 DMIPS.
- Compute DMIPS/MHz by dividing by the clock rate: in the example below,
  415 / 268 = 1.55 DMIPS/MHz.

```
core freq at 268694323 Hz

Dhrystone Benchmark, Version 2.1 (Language: C)

<snip>

Microseconds for one run through Dhrystone: 1.3
Dhrystones per Second:                      729927.0
```

#### CoreMark ####

We cannot distribute the CoreMark benchmark, but following are instructions
to download and run the benchmark on the HiFive1 board:

- Download CoreMark from EEMBC's web site and extract the archive from
  http://www.eembc.org/coremark/download.php.
- Copy the following files from the extracted archive into the
  `software/coremark` directory in this repository:
  - `core_list_join.c`
  - `core_main.c`
  - `coremark.h`
  - `core_matrix.c`
  - `core_state.c`
  - `core_util.c`
- Compile the benchmark with the command `make software PROGRAM=coremark`.
- Run on the HiFive1 board with the command `make upload PROGRAM=coremark`.
- Divide the reported Iterations/Sec by the reported core frequency in MHz to
  obtain a CoreMarks/MHz value.

### For More Information ###

Documentation, Forums, and much more available at

[dev.sifive.com](https://dev.sifive.com)
