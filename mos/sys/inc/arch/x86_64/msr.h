/*
 * Copyright (c) 2025, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#ifndef _MACHINE_MSR_H_
#define _MACHINE_MSR_H_ 1

#define IA32_APIC_BASE      0x0000001B
#define IA32_GS_BASE        0xC0000101
#define IA32_MTRR_CAP       0x000000FE
#define IA32_DEF_TYPE       0x000002FF
#define IA32_MTRR_PHYSBASE  0x00000200
#define IA32_MTRR_PHYSMASK  0x00000201
#define IA32_KERNEL_GS_BASE 0xC0000102
#define IA32_EFER           0xC0000080

#endif  /* !_MACHINE_MSR_H_ */
