/*
 * Copyright (c) 2025, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

    .text
    .globl _start
    .globl kern_main
_start:
    cli
    cld

    xor %rbp, %rbp      /* Terminate callstack */
    call kern_main      /* Call kernel main */

1:  cli
    hlt
    jmp 1b
