# SiFive HiFive Unleashed

The SiFive HiFive Unleashed features an FU540-C000 SoC with the U54-MC Core IP.

## Configuring MSEL

The mode select switches should be set as follows:
```
      USB   LED    Mode Select                  Ethernet
 +===|___|==****==+-+-+-+-+-+-+=================|******|===+
 |                | | | |X|X|X|                 |      |   |
 |                | | | | | | |                 |      |   |
 |        HFXSEL->|X|X|X| | | |                 |______|   |
 |                +-+-+-+-+-+-+                            |
 |        RTCSEL-----/ 0 1 2 3 <--MSEL                     |
 |                                                         |
```

This will cause the board to boot from the SPI flash at 0x2000\_0000.
