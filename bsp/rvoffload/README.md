Mainly copy from bsp/sifive-hifive1
Program entry at DRAM `0x80100000` for hifive board (TEMP)
The offload entry no needs to setup architecture so we use `_prologue` as entry.

Example:
```$ make standalone BSP=metal STANDALONE_DEST=./rv_example/ INCLUDE_METAL_SOURCES=1 PROGRAM=rvoffload_example TARGET=rvoffload```
```$ cd ./rv_example ; make clean; make```

You will get an `elf` and `binray`.
The rvoffload runtime execute `binary` file.