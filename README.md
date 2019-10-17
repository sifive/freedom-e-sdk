# Introduction

mem-test is a micro-benchmark for detecting the memory sub-system micro-architecture.

Currently, it can detect:

* Number of memory hierarchy, e.g., L1, L2, L3, memory

# Result

For Arty FPGA you can check the result directly on UART.

For RTLsim, you need to execute following command to get the result.
```
python analyze_rtlsim_result.py --rtlOut sim.err [--detail]

```
