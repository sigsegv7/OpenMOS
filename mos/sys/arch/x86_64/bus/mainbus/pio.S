/*
 * Copyright (c) 2025, Ian Moffett.
 * Provided under the BSD-3 clause.
 */
    .text
    .globl md_outb
md_outb:
    mov %rdi, %rdx
    mov %rsi, %rax
    outb %al, %dx
    retq

    .globl md_outw
md_outw:
    mov %rdi, %rdx
    mov %rsi, %rax
    outw %ax, %dx
    retq

    .globl md_outl
md_outl:
    mov %rdi, %rdx
    mov %rsi, %rax
    outl %eax, %dx

    .globl md_inb
md_inb:
    mov %rdi, %rdx
    xor %rax, %rax
    inb %dx, %al
    retq

    .globl md_inw
md_inw:
    mov %rdi, %rdx
    xor %rax, %rax
    inw %dx, %ax
    retq

    .globl md_inl
md_inl:
    mov %rdi, %rdx
    xor %rax, %rax
    inl %dx, %eax
    retq
