/*
 * Copyright (c) 2025, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

    .text
    .globl _start
    .globl kern_main
    .extern md_gdt_load
    .extern g_GDTR
_start:
    cli
    cld

    lea g_GDTR(%rip), %rdi      /* BSP GDTR base */
    call md_gdt_load            /* Load it */

    xor %rbp, %rbp      /* Terminate callstack */
    call kern_main      /* Call kernel main */

1:  cli
    hlt
    jmp 1b
