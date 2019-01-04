# SiFive Freedom E SDK README #

This repository, maintained by SiFive Inc, makes it easy to get started developing
software for the Freedom E and Freedom S Embedded RISC-V Platforms. 

### Contents ###

#### Freedom Metal Compatibility Library ####

* Board Support Packages for
  - SiFive HiFive 1 (sifive-hifive1)
  - SiFive Freedom E310 Arty (freedom-e310-arty)
  - SiFive CoreIP (e.g. coreip-e31)
  - SiFive CoreIP Arty FPGA Evaluation targets (e.g. coreip-e31-arty)
* A Few Example Programs
  - Example programs targeting the Freedom Metal compatibility library can be identified
    as submodules within the software/ directory, rather than being maintained in-tree
    like the legacy examples are.

#### (Deprecated) Legacy Freedom E SDK Library ####

As we transition to supporting SiFive targets and examples with the new Freedom Metal
compatibility library, the legacy Freedom E SDK libraries and examples are still available
within this repository.

* Board Support Packages for
  - SiFive HiFive 1 (freedom-e300-hifive1)
  - SiFive Freedom E310 Arty (freedom-e300-arty)
  - SiFive CoreIP Arty FPGA Evaluation Targets (e.g. coreplexip-e31-arty)
  - Additional legacy targets are contained within the bsp/env/ directory.
* A Few Example Programs
  - Example programs targeting the legacy Freedom E SDK can be identified as being tracked
    within this repository in the software/ directory, rathre than being maintained
    out-of-tree like the Freedom Metal examples are.

Legacy examples can be built using the same commands as the Freedom Metal examples and simply
omitting the `BSP=mee` argument or substituting it with `BSP=legacy`.

### Setting up the SDK ###

First, clone this repository:

```
git clone --recursive https://github.com/sifive/freedom-e-sdk.git
```

If at first you omit the `--recursive` option, you can update submodules using the command:

```
git submodule update --init --recursive
```

To see Makefile options:

```
cd freedom-e-sdk
make help
```

#### Install the RISC-V Toolchain ####

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

### Updating your SDK ###

If you'd like to update your SDK to the latest version:

```
cd freedom-e-sdk
git pull origin master
git submodule update --init --recursive
```

### Using the Tools ###

#### Building an Example ####

To compile a bare-metal RISC-V program:

```
cd freedom-e-sdk
make BSP=mee [PROGRAM=hello] [BOARD=sifive-hifive1] software
```

#### Uploading to the Target Board ####

```
cd freedom-e-sdk
make BSP=mee [PROGRAM=hello] [BOARD=sifive-hifive1] upload
```

#### Debugging a Target Program ####

```
cd freedom-e-sdk
make BSP=mee [PROGRAM=hello] [BOARD=sifive-hifive1] debug
```

#### Cleaning a Target Program Build Directory ####

```
cd freedom-e-sdk
make BSP=mee [PROGRAM=hello] [BOARD=sifive-hifive1] clean
```

Run `make help` for more commands.

### Benchmarking ###

#### Dhrystone ####

After setting up the software and debug toolchains, you can build and
execute everyone's favorite benchmark as follows:

- Compile the benchmark with the command `make software BOARD=freedom-e300-hifive1 PROGRAM=dhrystone LINK_TARGET=dhrystone`. Note that a slightly different linker file is used for Dhrystone which stores read only data in DTIM instead of external flash.
- Run on the HiFive1 board with the command `make upload BOARD=freedom-e300-hifive1 PROGRAM=dhrystone`.
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
