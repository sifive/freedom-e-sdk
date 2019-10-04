Simulating with Spike
=====================

Freedom E SDK comes with a target for simulating the RISC-V ISA with Spike:

 - spike

Building for Spike
------------------

Compiling a bare-metal RISC-V program for Spike is much the same as any other
target in Freedom E SDK

.. code-block:: bash

   make TARGET=spike [PROGRAM=hello] [CONFIGURATION=debug] software

The square brackets in the above command indicate optional parameters for the
Make invocation. As you can see, the default values of these parameters tell
the build script to build the ``hello`` example for the ``spike`` target
using the ``debug`` build configuration. If, for example, you wished to build
the ``timer-interrupt`` example for using the ``release`` build configuration,
you would instead run the command

.. code-block:: bash

   make PROGRAM=timer-interrupt TARGET=spike CONFIGURATION=release software

Running in Spike Simulation
---------------------------

With the Spike simulator in your ``PATH``, running a program in spike is as
easy as invoking the ``simulate`` make target:

.. code-block:: bash

   make TARGET=spike [PROGRAM=hello] [CONFIGURATION=debug] simulate

Cleaning a Target Program Build Directory
-----------------------------------------

The ``clean`` target can be used to restore a target program's directory to a clean state.

.. code-block:: bash

   make TARGET=spike [PROGRAM=hello] [CONFIGURATION=debug] clean

