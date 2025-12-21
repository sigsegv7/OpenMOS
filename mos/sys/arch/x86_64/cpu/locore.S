/*
 * Copyright (c) 2025, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

    .text
    .globl _start
_start:
    cli
    cld

1:  cli
    hlt
    jmp 1b
