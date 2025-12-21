/*
 * Copyright (c) 2025, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#ifndef _SDK_PARAM_H_
#define _SDK_PARAM_H_ 1

#include <sdk/types.h>

/* Offset a pointer +/- 'n' */
#define PTR_OFFSET(P, OFF) (void *)((UQUAD)(P) + (OFF))
#define PTR_NOFFSET(P, OFF) (void *)((UQUAD)(P) - (OFF))

/* Bit related macros */
#define ISSET(v, f)  ((v) & (f))
#define BIT(n) (1ULL << (n))
#define MASK(n) ((1ULL << n) - 1)

/* Align up/down a value */
#define ALIGN_DOWN(value, align)      ((value) & ~((align)-1))
#define ALIGN_UP(value, align)        (((value) + (align)-1) & ~((align)-1))

/* Bitmap helper macros */
#define SETBIT(a, b) ((a)[(b) >> 3] |= BIT(b % 8))
#define CLRBIT(a, b) ((a)[(b) >> 3] &= ~BIT(b % 8))
#define TESTBIT(a, b) (ISSET((a)[(b) >> 3], BIT(b % 8)))

#define NELEM(a) (sizeof(a) / sizeof(a[0]))

#endif  /* !_SDK_PARAM_H_ */
