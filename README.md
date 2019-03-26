# SiFive Freedom E SDK README #

This repository, maintained by SiFive Inc, makes it easy to get started developing
software for the Freedom E and Freedom S Embedded RISC-V Platforms. This SDK
is intended to work on any target supported by SiFive's distributions of the
RISC-V GNU Toolchain.

[Documentation for Freedom E SDK is available here](https://sifive.github.io/freedom-e-sdk-docs/index.html)

Freedom E SDK was recently transitioned to using the Freedom Metal compatibility
library. If you're looking for the old Freedom E SDK, software examples, and
board support files, you can find those on the [v1\_0 branch](https://github.com/sifive/freedom-e-sdk/tree/v1_0).

#### What is Freedom Metal? ###

[Freedom Metal](https://github.com/sifive/freedom-metal) ([Documentation](https://sifive.github.io/freedom-metal-docs/index.html))
is a library developed by SiFive for writing portable software for all of SiFive's
RISC-V IP, RISC-V FPGA evaluation images, and development boards. Programs written
against the Freedom Metal API are intended to build and run for all SiFive RISC-V
targets. This makes Freedom Metal suitable for writing portable tests, bare metal
application programming, and as a hardware abstraction layer for porting
operating systems to RISC-V.

### Contents ###

#### Freedom Metal Compatibility Library ####

* Board Support Packages (found under `bsp/`)
  - Supported Targets:
    - [SiFive HiFive 1](https://www.sifive.com/boards/hifive1)
      - sifive-hifive1
    - SiFive HiFive 1 Rev B
      - sifive-hifive1-revb
    - [SiFive Freedom E310 Arty](https://github.com/sifive/freedom)
      - freedom-e310-arty
    - SiFive CoreIP RTL
      - coreip-e20-rtl
      - coreip-e21-rtl
      - coreip-e24-rtl
      - coreip-e31-rtl
      - coreip-e34-rtl
      - coreip-s51-rtl
      - coreip-s54-rtl
      - coreip-e76-rtl
      - coreip-s76-rtl
    - SiFive CoreIP Arty FPGA Evaluation targets
      - coreip-e20-arty
      - coreip-e21-arty
      - coreip-e24-arty
      - coreip-e31-arty
      - coreip-e34-arty
      - coreip-s51-arty
      - coreip-s54-arty
      - coreip-e76-arty
      - coreip-s76-arty
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
    * metal.%.lds
      - Generated linker scripts for the target. The different scripts allow
        for different memory configurations.
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
  - sifive-welcome
    - Prints the SiFive banner and blinks LEDs 

### Setting up the SDK ###

#### Prerequisites ####

To use this SDK, you will need the following software available on your machine:

* GNU Make
* Git
* RISC-V GNU Toolchain
* RISC-V OpenOCD (for use with development board and FPGA targets)
* Segger J-LINK (for use with certain development boards)

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

##### Install Segger J-Link Software

Some targets supported by Freedom E SDK (like the SiFive HiFive1 Rev B) use
Segger J-Link OB for programming and debugging. If you intend to use these
targets, install the Segger J-Link Software and Documentation Pack for your
machine:

[Segger J-Link Software Downloads](https://www.segger.com/downloads/jlink#J-LinkSoftwareAndDocumentationPack)

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

#### Building an Example ####

To compile a bare-metal RISC-V program:

```
make [PROGRAM=hello] [TARGET=sifive-hifive1] [CONFIGURATION=debug] software
```

The square brackets in the above command indicate optional parameters for the
Make invocation. As you can see, the default values of these parameters tell
the build script to build the `hello` example for the `sifive-hifive1` target
with the `debug` configuration. If, for example, you wished to build the
`timer-interrupt` example for the S51 Arty FPGA Evaluation target,
with the `release` configuration, you would instead run the command

```
make PROGRAM=timer-interrupt TARGET=coreip-s51-arty CONFIGURATION=release software
```

#### Uploading to the Target Board ####

```
make [PROGRAM=hello] [TARGET=sifive-hifive1] [CONFIGURATION=debug] upload
```

#### Debugging a Target Program ####

```
make [PROGRAM=hello] [TARGET=sifive-hifive1] [CONFIGURATION=debug] debug
```

#### Cleaning a Target Program Build Directory ####

```
make [PROGRAM=hello] [TARGET=sifive-hifive1] [CONFIGURATION=debug] clean
```

#### Create a Standalone Project ####

You can export a program to a standalone project directory using the `standalone`
target. The resulting project will be locked to a specific `TARGET`. Note
that this functionality is only supported for Freedom Metal programs, not the
Legacy Freedom E SDK.

`STANDALONE_DEST` is a required argument to provide the desired project location.

```
make [PROGRAM=hello] [TARGET=sifive-hifive1] [INCLUDE_METAL_SOURCES=1] STANDALONE_DEST=/path/to/desired/location standalone
```

Run `make help` for more commands.

### For More Information ###

Documentation, Forums, and much more available at

[dev.sifive.com](https://dev.sifive.com)
