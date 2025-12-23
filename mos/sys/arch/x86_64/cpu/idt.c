/*
 * Copyright (c) 2025, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#include <sdk/defs.h>
#include <md/idt.h>
#include <md/gdt.h>

ALIGN(8) static IDT_GATE idt[256];
static IDT_DESCRIPTOR idtr = {
    .limit = sizeof(idt) - 1,
    .offset = (UPTR)&idt[0]
};

void
md_idt_set_entry(UBYTE vector, UPTR isr, UBYTE type, UBYTE ist)
{
    IDT_GATE *gate = &idt[vector];

    gate->offset_low = isr & 0xFFFF;
    gate->offset_mid = (isr >> 16) & 0xFFFF;
    gate->offset_high = (isr >> 32) & 0xFFFFFFFF;
    gate->p = 1;
    gate->dpl = (type == IDT_USER_GATE) ? 3 : 0;
    gate->zero = 0;
    gate->zero1 = 0;
    gate->reserved = 0;
    gate->ist = ist;
    gate->target_cs = GDT_KCODE;
    gate->type = type;
}

void
md_idt_load(void)
{
    ASM("lidt %0" :: "m" (idtr) : "memory");
}
