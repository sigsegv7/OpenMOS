/*
 * Copyright (c) 2025, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#ifndef _SDK_DEFS_H_
#define _SDK_DEFS_H_ 1

#define ASM             __asm__ __volatile__
#define ATTR(x)         __attribute__((x))
#define ALIGN(n)        ATTR(aligned((n)))
#define NO_RETURN       ATTR(no_return)
#define ALWAYS_INLINE   ATTR(always_inline)
#define PACKED          ATTR(packed)

#endif  /* !_SDK_DEFS_H_ */
