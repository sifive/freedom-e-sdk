Building for a Dev Board or FPGA
================================

Building an Example
-------------------

To compile a bare-metal RISC-V program:

.. code-block:: bash

   make BSP=mee [PROGRAM=hello] [TARGET=sifive-hifive1] software

The square brackets in the above command indicate optional parameters for the
Make invocation. As you can see, the default values of these parameters tell
the build script to build the ``hello`` example for the ``sifive-hifive1`` target.
If, for example, you wished to build the ``timer-interrupt`` example for the S51
Arty FPGA Evaluation target, you would instead run the command

.. code-block:: bash

   make BSP=mee PROGRAM=timer-interrupt TARGET=coreip-s51-arty software

Uploading to the Target Board
-----------------------------

Uploading a program to the target development or FPGA board depends on having both
the RISC-V GNU Toolchain and RISC-V OpenOCD installed on your development system.
See :doc:`installing` for more information on installing OpenOCD.

With the toolchain and OpenOCD installed, uploading a program is as simple as plugging
the development board into your computer and running the following command:

.. code-block:: bash

   make BSP=mee [PROGRAM=hello] [TARGET=sifive-hifive1] upload

Debugging a Target Program
--------------------------

Debugging a program on a target development or FPGA board depends on having both
the RISC-V GNU Toolchain and RISC-V OpenOCD installed on your development system.
See :doc:`installing` for more information on installing OpenOCD.

Debugging with Freedom E SDK also assumes that the program has already been uploaded to
the target board.

With the toolchain and OpenOCD installed, debugging a program is as simple as plugging
the development board into your computer and running the following command:

.. code-block:: bash

   make BSP=mee [PROGRAM=hello] [TARGET=sifive-hifive1] debug

Cleaning a Target Program Build Directory
-----------------------------------------

The ``clean`` target can be used to restore a target program's directory to a clean state.

.. code-block:: bash

   make BSP=mee [PROGRAM=hello] [TARGET=sifive-hifive1] clean

