# example-atomic

Demonstrates how to use the Metal Atomic API to atomically increment a single
memory location from all harts on the target, then waits as hart 0 until all
harts have finished incrementing.
