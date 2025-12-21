/*
 * Copyright (c) 2025, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#ifndef _MACHINE_PIO_H_
#define _MACHINE_PIO_H_ 1

#include <sdk/types.h>

/* PIO write helpers */
void md_outb(USHORT port, UBYTE data);
void md_outw(USHORT port, USHORT data);
void md_outl(USHORT port, ULONG data);

/* PIO read helpers */
UBYTE md_inb(USHORT port);
USHORT md_inw(USHORT port);
ULONG md_inl(USHORT port);

#endif  /* !_MACHINE_PIO_H_ */
