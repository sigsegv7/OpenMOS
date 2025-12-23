/*
 * Copyright (c) 2025, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#ifndef _KERN_PANIC_H_
#define _KERN_PANIC_H_ 1

#include <sdk/types.h>
#include <sdk/stdarg.h>

/*
 * Signal to the operator that a severe error has
 * occurred and the system has been halted.
 */
void panic(const char *fmt, ...);

#endif  /* !_KERN_PANIC_H_ */
