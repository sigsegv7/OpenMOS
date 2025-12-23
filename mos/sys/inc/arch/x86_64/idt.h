/*
 * Copyright (c) 2025, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#ifndef _MACHINE_IDT_H_
#define _MACHINE_IDT_H_ 1

#include <sdk/types.h>
#include <sdk/defs.h>

#define IDT_INT_GATE    0x8E
#define IDT_TRAP_GATE   0x8F
#define IDT_USER_GATE   0xEE

/*
 * Represents a 64-bit interrupt gate descriptor
 * for the x86_64 architecture. See section 6.14.1
 * for more information.
 */
typedef struct {
    USHORT offset_low;
    USHORT target_cs;
    UBYTE  ist   : 3;
    UBYTE  zero  : 5;
    UBYTE  type  : 4;
    UBYTE  zero1 : 1;
    UBYTE  dpl   : 2;
    UBYTE  p     : 1;
    USHORT offset_mid;
    ULONG  offset_high;
    ULONG  reserved;
} IDT_GATE;

/*
 * This descriptor is loaded into the processor core
 * for when it needs to reference a gate descriptor.
 *
 * @limit:  IDT limit
 * @offset: Base address of IDT
 */
typedef struct {
    USHORT limit;
    UPTR   offset;
} PACKED IDT_DESCRIPTOR;

/*
 * Set an interrupt gate descriptor within the
 * interrupt descriptor table.
 *
 * @vector: Interrupt vector to set
 * @isr:    Interrupt service routine
 * @type:   Gate descriptor type
 * @ist:    Interrupt stack table index to use
 */
void md_idt_set_entry(UBYTE vector, UPTR isr, UBYTE type, UBYTE ist);

/*
 * Load the interrupt descriptor table into the current
 * processor core.
 */
void md_idt_load(void);

#endif  /* !_MACHINE_IDT_H_ */
