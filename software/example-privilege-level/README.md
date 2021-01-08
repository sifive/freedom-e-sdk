# example-privilege-level

Demonstrates how to switch mode to supervisor mode from machine mode,
then switch mode to user mode from supervisor mode.

This program shows what should be done before switching mode, and
uses ecall to test mode transfer. After switching mode, we call the
ecall and check if we get the correct corresponding exceptions.
- Call ecall in S-mode, get the exception code 9 (Environment call from S-mode)
- Call ecall in U-mode, get the exception code 8 (Environment call from U-mode)
