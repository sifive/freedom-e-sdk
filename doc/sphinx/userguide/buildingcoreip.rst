Building for SiFive CoreIP
==========================

Building an Example
-------------------

To compile a bare-metal RISC-V program:

.. code-block:: bash

   make BSP=mee [PROGRAM=hello] [TARGET=coreip-e31] software

The square brackets in the above command indicate optional parameters for the
Make invocation. As you can see, the default values of these parameters tell
the build script to build the ``hello`` example for the ``coreip-e31`` target.
If, for example, you wished to build the ``timer-interrupt`` example for the S51
Core IP target, you would instead run the command

.. code-block:: bash

   make BSP=mee PROGRAM=timer-interrupt TARGET=coreip-s51 software

Cleaning a Target Program Build Directory
-----------------------------------------

The ``clean`` target can be used to restore a target program's directory to a clean state.

.. code-block:: bash

   make BSP=mee [PROGRAM=hello] [TARGET=coreip-e31] clean

