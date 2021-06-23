# SiFive HiFive Unmatched

The SiFive HiFive Unmatched features an FU740-C000 SoC with the U74-MC Core IP.

## Configuring MSEL

The mode select switches should be set as follows:
```
                   BOOT MODE SEL               BATT CONN
 +==================+-+-+-+-+-+=================|======|===+
 |                  | | | | |X| ON              (      )   |
 |                  | | | | | |                 (      )   |
 |        CHIP_ID-> |X|X|X|X| | OFF             (______)   |
 |                +-+-+-+-+-+-+                            |
 |                     3 2 1 0 <--MSEL                     |
 |                                                         |
```

This will cause the board to boot from the SPI flash at 0x2000\_0000.
