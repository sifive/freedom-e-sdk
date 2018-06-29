// See LICENSE for license details.

#ifndef _SIFIVE_CLIC_H
#define _SIFIVE_CLIC_H

#define CLIC_CTRL_ADDR _AC(0x2000000,UL)

#define CLIC_MSIP           0x0000
#define CLIC_MSIP_size      0x4
#define CLIC_MTIMECMP       0x4000
#define CLIC_MTIMECMP_size  0x8
#define CLIC_MTIME          0xBFF8
#define CLIC_MTIME_size     0x8

#define CLIC_INTIP          0x0800000
#define CLIC_INTIE          0x0800400
#define CLIC_INTCFG         0x0800800
#define CLIC_CFG            0x0800c00

// These interrupt IDs are consistent across old and new mtvec modes
#define SSIPID              1
#define MSIPID              3
#define STIPID              5
#define MTIPID              7
#define SEIPID              9
#define MEIPID              11
#define CSIPID              12
#define LOCALINTIDBASE      16

#define CLIC_REG(offset)    _REG32(CLIC_CTRL_ADDR, offset)
#define CLIC_REG8(offset)   (*(volatile uint8_t *)((CLIC_CTRL_ADDR) + (offset)))

#ifndef CLINT_CTRL_ADDR
#define CLINT_CTRL_ADDR CLIC_CTRL_ADDR
#endif
#ifndef CLINT_REG
#define CLINT_REG CLIC_REG
#endif
#ifndef CLINT_MSIP
#define CLINT_MSIP CLIC_MSIP
#endif
#ifndef CLINT_MTIME
#define CLINT_MTIME CLIC_MTIME
#endif
#ifndef CLINT_MTIMECMP
#define CLINT_MTIMECMP CLIC_MTIMECMP
#endif

#endif /* _SIFIVE_CLIC_H */ 
