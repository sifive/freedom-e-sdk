Simulating with Spike
=====================

Freedom E SDK comes with a target for simulating the RISC-V ISA with Spike:

 - spike

Building for Spike
------------------

Compiling a bare-metal RISC-V program for Spike is much the same as any other
target in Freedom E SDK

.. code-block:: bash

   make TARGET=spike PROGRAM=hello CONFIGURATION=debug software

One can choose to replace the ``hello`` PROGRAM with any other examples,
like ``timer-interrupt`` example, and the ``debug`` build CONFIGRATION
with the ``release`` for an optimize build configuration.

.. code-block:: bash

   make PROGRAM=timer-interrupt TARGET=spike CONFIGURATION=release software

Changing the Spike Simulation Target
------------------------------------

Spike accepts various options to configure the simulation target, like ISA, the
number of harts, and more. You can configure these options by editing
``bsp/spike/spike_options.sh`` and adding your options to the exported
``SPIKE_OPTIONS`` variable.

Editing these options usually requires regenerating the BSP files using
freedom-devicetree-tools, so if you edit ``SPIKE_OPTIONS``, make sure that
the freedom-devicetree-tools submodule has been built and its output binaries
are in your ``PATH``.

Running in Spike Simulation
---------------------------

With the Spike simulator in your ``PATH``, running a program in spike is as
easy as invoking the ``simulate`` make target:

.. code-block:: bash

   make TARGET=spike PROGRAM=hello CONFIGURATION=debug simulate

Cleaning a Target Program Build Directory
-----------------------------------------

The ``clean`` target can be used to restore a target program's directory to a clean state.

.. code-block:: bash

   make TARGET=spike PROGRAM=hello CONFIGURATION=debug clean

