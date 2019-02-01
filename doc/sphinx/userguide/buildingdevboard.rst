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

.. code-block:: bash

   make BSP=mee [PROGRAM=hello] [TARGET=sifive-hifive1] upload

Debugging a Target Program
--------------------------

.. code-block:: bash

   make BSP=mee [PROGRAM=hello] [TARGET=sifive-hifive1] debug

Cleaning a Target Program Build Directory
-----------------------------------------

.. code-block:: bash

   make BSP=mee [PROGRAM=hello] [TARGET=sifive-hifive1] clean

