/*
 * Copyright (c) 2025, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#ifndef _MACHINE_GDT_H_
#define _MACHINE_GDT_H_ 1

#ifndef __ASSEMBLER__
#include <sdk/types.h>
#include <sdk/defs.h>
#endif  /* __ASSEMBLER__ */

/* Kernel code/data */
#define GDT_KCODE  0x08
#define GDT_KDATA  0x10

/* User code/data */
#define GDT_UCODE  0x18
#define GDT_UDATA  0x20

/* Task state segment */
#define GDT_TSS    0x28
#define GDT_TSS_INDEX 0x05

#ifndef __ASSEMBLER__
typedef struct {
    USHORT limit;
    USHORT base_low;
    UBYTE base_mid;
    UBYTE access;
    UBYTE granularity;
    UBYTE base_hi;
} PACKED GDT_ENTRY;

typedef struct {
    USHORT limit;
    UPTR offset;
} PACKED GDTR;

#endif  /* !__ASSEMBLER__ */
#endif  /* !_MACHINE_GDT_H_ */
