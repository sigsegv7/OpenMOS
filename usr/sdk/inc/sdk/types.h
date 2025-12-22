/*
 * Copyright (c) 2025, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#ifndef _SDK_TYPES_H_
#define _SDK_TYPES_H_ 1

#define NULL ((void *)0)

#ifndef true
#define true 1
#endif  /* !true */

#ifndef false
#define false 0
#endif  /* !false */

/* Boolean type */
typedef _Bool BOOL;

/* Signed types */
typedef char        BYTE;
typedef short       SHORT;
typedef int         LONG;
typedef long long   QUAD;
typedef QUAD        SSIZE;

/* Unsigned types */
typedef unsigned char        UBYTE;
typedef unsigned short       USHORT;
typedef unsigned int         ULONG;
typedef unsigned long long   UQUAD;
typedef UQUAD                USIZE;
typedef UQUAD                UPTR;

#endif  /* !_SDK_TYPES_H_ */
