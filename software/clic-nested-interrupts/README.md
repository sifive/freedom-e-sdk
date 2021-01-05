# example-clic-nested-interrupts
A simple example demonstrating how to use CLIC preemptive (level and priority) nested interrupts.
Using Timer interrupt (TMR), Software interrupt (SIP) and CLIC Software interrupt (CSIP), the example
demontrate how SIP can preempt TMR (@level 127) before CSIP (@priority 223), both (@level 255, 223).
