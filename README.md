# README #

This repository, maintained by SiFive, Inc, makes it easy to get started developing software for the Freedom E RISC-V platform. 

### Contents ###

* RISC-V Software Toolchain 
* RISC-V Debugging Toolchain
* Board Support Packages for FE310 and Development Kits
* A Few Example Programs

### Setting up the SDK ###

First, clone this repository:

```
git clone --recursive https://github.com/sifive/freedom-e-sdk.git
```

Ubuntu packages needed:

	$ sudo apt-get install autoconf automake libmpc-dev libmpfr-dev libgmp-dev gawk bison flex texinfo libtool libusb-1.0-0-dev make g++ pkg-config libexpat1-dev zlib1g-dev  

Next, build the tools:

```
cd freedom-e-sdk
make tools
```

Provided you have your machine has enough resources you can speed up the build process by adding `-j n` to make where `n` is the amount of processors of your build system.

To compile a bare-metal RISC-V program:

```
cd freedom-e-sdk
make software [PROGRAM=demo_gpio]
```

To see additional options:

```
cd freedom-e-sdk
make help
```

### Benchmarking ###

#### Dhrystone ####

After setting up the software and debug toolchains, you can build and
execute everyone's favorite benchmark as follows:

- Compile the benchmark with the command `make software PROGRAM=dhrystone`.
- Run on the HiFive1 board with the command `make upload PROGRAM=dhrystone`.
  This will take a few minutes.  Sample output is provided below.
- Compute DMIPS by dividing the Dhrystones per Second result by 1757, which
  was the VAX 11/780's performance.  In the example below, 729927 / 1757 =
  415 DMIPS.
- Compute DMIPS/MHz by dividing by the clock rate: in the example below,
  415 / 260 = 1.60 DMIPS/MHz.

```
core freq at 259830579 Hz

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
