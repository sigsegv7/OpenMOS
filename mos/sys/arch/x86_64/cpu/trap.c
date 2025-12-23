/*
 * Copyright (c) 2025, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#include <kern/panic.h>
#include <md/frame.h>

/* Forward declaration */
void trap_dispatch(TRAPFRAME *tf);

void
trap_dispatch(TRAPFRAME *tf)
{
    panic("fatal vector %x\n", tf->vector);
}
