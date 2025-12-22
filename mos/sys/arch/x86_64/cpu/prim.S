/*
 * Copyright (c) 2025, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

    .text
    .globl mu_cpu_halt
    .globl mu_irq_state
    .globl mu_irq_setmask
    .globl mu_cpu_aswap
mu_cpu_halt:
    hlt
    retq
mu_cpu_pause:
    pause
    retq
mu_irq_state:
    pushfq
    pop %rax
    shr $9, %rax        /* IF */
    and $1, %rax        /* Isolate */
    retq
mu_cpu_aswap:
    xchg %rsi, (%rdi)   /* Swap */
    mov %rsi, %rax      /* Return old value */
    retq
mu_irq_setmask:
    test $1, %rdi
    jnz irq_mask
    sti
    retq
irq_mask:
    cli
    retq
