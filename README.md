# Introduction

benchmark-mem-latency is a micro-benchmark for measureing the memory latency.

# Setup

Clone benchmark-mem-latency under PATH-TO-FREEDOME-E-SDK/software

    git clone git@github.com:sifive/benchmark-mem-latency.git freedom-e-sdk/software/benchmark-mem-latency

To build and run on the Arty FPGA board.

    make -C freedom-e-sdk CONFIGURATION=release  PROGRAM=benchmark-mem-latency TARGET=design-arty clean software upload

To build and run on verilator.

    make -C freedom-e-sdk CONFIGURATION=release  PROGRAM=benchmark-mem-latency TARGET=design-rtl clean software
    module load verilator/4.028
    make benchmark-mem-latency.verilator.out

# Result


For Arty FPGA you can check the result directly on UART.
For eaxmple:
```
---test end---
  heap size: 1019 K
    4 K : 2  cycle
    8 K : 2  cycle
   16 K : 2  cycle
   32 K : 15  cycle
   64 K : 17  cycle
  128 K : 18  cycle
  256 K : 18  cycle
  512 K : 48  cycle
---test end---
```
which indicats this core has 
 - 16KB   2-cycle L1 load-to-use latency
 - 256KB  18-cycle L2 load-to-use latency


For RTLsim, you need to execute following command to get the result.
```
python analyze_rtlsim_result.py --rtlOut sim.err [--detail]

```
