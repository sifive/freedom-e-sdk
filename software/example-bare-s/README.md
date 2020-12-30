# example-bare-s

Demonstrates how to switch mode to bare S mode,
and verify the following behavior
- Write to satp CSR should be ignored.
- Execute to sfence.vma instruction should raise illegal instruction exception.
