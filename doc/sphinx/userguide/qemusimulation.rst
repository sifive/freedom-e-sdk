Simulating with QEMU
====================

Freedom E SDK comes with a number of targets for simulating SiFive RISC-V cores
with QEMU, including:

 - qemu-sifive-e31
 - qemu-sifive-s51
 - qemu-sifive-u54
 - qemu-sifive-u54mc

Building for a QEMU Target
--------------------------

Compiling a bare-metal RISC-V program for QEMU targets is much the same as for
any other target in Freedom E SDK

.. code-block:: bash

   make PROGRAM=hello TARGET=qemu-sifive-e31 CONFIGURATION=debug software

One can choose to replace the ``hello`` PROGRAM with any other examples,
the ``debug`` build CONFIGRATION with the ``release``, and the ``qemu-sifive-e31`
target with others QEMU like ``qemu-sifive-u54``. For example, if you wished to
build the ``timer-interrupt`` example for the ``qemu-sifive-u54mc`` target using
the ``release`` build configuration, you would instead run the command

.. code-block:: bash

   make PROGRAM=timer-interrupt TARGET=qemu-sifive-u54mc CONFIGURATION=release software

Running in QEMU Simulation
--------------------------

Running a program in qemu simulation is as easy as invoking the ``simulate``
make target:

.. code-block:: bash

   make PROGRAM=hello TARGET=qemu-sifive-e31 CONFIGURATION=debug simulate

Cleaning a Target Program Build Directory
-----------------------------------------

The ``clean`` target can be used to restore a target program's directory to a clean state.

.. code-block:: bash

   make PROGRAM=hello TARGET=qemu-sifive-e31 CONFIGURATION=debug clean

