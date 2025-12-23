/*
 * Copyright (c) 2025, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#ifndef _MACHINE_FRAME_H_
#define _MACHINE_FRAME_H_ 1

#include <sdk/types.h>
#include <sdk/defs.h>

/*
 * Processor state
 */
typedef struct {
    UQUAD vector;
    UQUAD r15;
    UQUAD r14;
    UQUAD r13;
    UQUAD r12;
    UQUAD r11;
    UQUAD r10;
    UQUAD r9;
    UQUAD r8;
    UQUAD rbp;
    UQUAD rdi;
    UQUAD rsi;
    UQUAD rbx;
    UQUAD rdx;
    UQUAD rcx;
    UQUAD rax;
    UQUAD error_code;
    UQUAD rip;
    UQUAD cs;
    UQUAD rflags;
    UQUAD rsp;
    UQUAD ss;
} PACKED TRAPFRAME;

#endif  /* !_MACHINE_FRAME_H_ */
