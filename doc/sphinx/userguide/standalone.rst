Creating a Standalone Project
=============================

You can export a program to a standalone project directory using the ``standalone``
target. The resulting project will be locked to a specific ``TARGET``. Note
that this functionality is only supported for Freedom Metal programs, not the
Legacy Freedom E SDK.

``STANDALONE_DEST`` is a required argument to provide the desired project location.

.. code-block:: bash

   make PROGRAM=hello TARGET=sifive-hifive1 STANDALONE_DEST=/path/to/desired/location standalone

