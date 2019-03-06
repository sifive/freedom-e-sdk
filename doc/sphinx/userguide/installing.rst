Installing Freedom E SDK
========================

Supported Systems
-----------------

Freedom E SDK is supported on Linux, MacOS, and Windows.

Linux support is officially provided to distributions we distribute
builds of the RISC-V toolchain for. Currently, these distributions are

- Ubuntu
- CentOS

We expect other Linux distributions to work as well, provided that the
user can either run our provided toolchains on them or produce their own
toolchain.

Windows support is not directly provided by Freedom E SDK, but through
our Integrated Development Environment, Freedom Studio.

Prerequisites
-------------

To use this SDK, you will need the following software available on your machine:

- GNU Make
- Git
- The RISC-V GNU Embedded Toolchain
- RISC-V OpenOCD (for use with development board and FPGA targets)

Install the RISC-V Toolchain and OpenOCD
----------------------------------------

The RISC-V GNU Toolchain and OpenOCD are available from `the SiFive Website <https://www.sifive.com/boards>`_.

For OpenOCD and/or RISC-V GNU Toolchain, download the .tar.gz for your platform,
and unpack it to your desired location. Then, set the ``RISCV_PATH`` and
``RISCV_OPENOCD_PATH`` environment variables when using the tools:

.. code-block:: bash

   cp openocd-<date>-<platform>.tar.gz /my/desired/location/
   cp riscv64-unknown-elf-gcc-<date>-<platform>.tar.gz /my/desired/location
   cd /my/desired/location
   tar -xvf openocd-<date>-<platform>.tar.gz
   tar -xvf riscv64-unknown-elf-gcc-<date>-<platform>.tar.gz
   export RISCV_OPENOCD_PATH=/my/desired/location/openocd
   export RISCV_PATH=/my/desired/location/riscv64-unknown-elf-gcc-<date>-<version>

Install Segger J-Link Software
------------------------------

Some targets supported by Freedom E SDK (like the SiFive HiFive1 Rev B) use Segger J-Link OB
for programming and debugging. If you intend to use these targets, install the Segger J-Link
Software and Documentation Pack for your machine:

`Segger J-Link Software Downloads <https://www.segger.com/downloads/jlink#J-LinkSoftwareAndDocumentationPack>`_

Cloning the Repository
----------------------

This repository can be cloned by running the following commands:

.. code-block:: bash

   git clone --recursive https://github.com/sifive/freedom-e-sdk.git
   cd freedom-e-sdk

The ``--recursive`` option is required to clone the git submodules included in the
repository. If at first you omit the ``--recursive`` option, you can achieve
the same effect by updating submodules using the command:

.. code-block:: bash

   git submodule update --init --recursive

Updating the SDK
----------------

If you'd like to update your SDK to the latest version:

.. code-block:: bash

   git pull origin master
   git submodule update --init --recursive
