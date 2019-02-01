Benchmarking
============

The Dhrystone and CoreMark benchmarks are still only supported by the Legacy
Freedom E SDK. When we port the benchmarks to Freedom Metal, we will update
this section to describe the updated build steps.

Dhrystone
---------

After setting up the software and debug toolchains, you can build and
execute everyone's favorite benchmark as follows:

- Compile the benchmark with the command ``make software TARGET=freedom-e300-hifive1 PROGRAM=dhrystone LINK_TARGET=dhrystone``. Note that a slightly different linker file is used for Dhrystone which stores read only data in DTIM instead of external flash.
- Run on the HiFive1 board with the command ``make upload TARGET=freedom-e300-hifive1 PROGRAM=dhrystone``.
  This will take a few minutes.  Sample output is provided below.
- Compute DMIPS by dividing the Dhrystones per Second result by 1757, which
  was the VAX 11/780's performance.  In the example below, 729927 / 1757 =
  415 DMIPS.
- Compute DMIPS/MHz by dividing by the clock rate: in the example below,
  415 / 268 = 1.55 DMIPS/MHz.

.. code-block:: none

   core freq at 268694323 Hz

   Dhrystone Benchmark, Version 2.1 (Language: C)

   <snip>

   Microseconds for one run through Dhrystone: 1.3
   Dhrystones per Second:                      729927.0

CoreMark
--------

We cannot distribute the CoreMark benchmark, but following are instructions
to download and run the benchmark on the HiFive1 board:

- Download CoreMark from EEMBC's web site and extract the archive from
  `<http://www.eembc.org/coremark/download.php>`_.
- Copy the following files from the extracted archive into the
  ``software/coremark`` directory in this repository:

  - ``core_list_join.c``
  - ``core_main.c``
  - ``coremark.h``
  - ``core_matrix.c``
  - ``core_state.c``
  - ``core_util.c``

- Compile the benchmark with the command ``make software PROGRAM=coremark``.
- Run on the HiFive1 board with the command ``make upload PROGRAM=coremark``.
- Divide the reported Iterations/Sec by the reported core frequency in MHz to
  obtain a CoreMarks/MHz value.
