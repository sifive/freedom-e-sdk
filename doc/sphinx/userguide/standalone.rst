Creating a Standalone Project
=============================

You can export a program to a standalone project directory using the ``standalone``
target. The resulting project will be locked to a specific ``TARGET``. Note
that this functionality is only supported for Freedom Metal programs, not the
Legacy Freedom E SDK.

``STANDALONE_DEST`` is a required argument to provide the desired project location.

You can include the argument ``INCLUDE_METAL_SOURCES=1`` if you would like to
include the sources for the Freedom Metal library in the generated standalone
project. If this argument is not included, then the Freedom Metal library will
be included in the generated project as a pre-built archive.

.. code-block:: bash

   make BSP=mee [PROGRAM=hello] [TARGET=sifive-hifive1] [INCLUDE_METAL_SOURCES=1] STANDALONE_DEST=/path/to/desired/location standalone

