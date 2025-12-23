/*
 * Copyright (c) 2025, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#include <sdk/string.h>
#include <kern/panic.h>
#include <kern/spinlock.h>
#include <kern/trace.h>
#include <mu/cpu.h>

static SPINLOCK panic_sync;
static char panic_buf[256];
static va_list ap;

void
panic(const char *fmt, ...)
{
    spinlock_acquire(&panic_sync, SPINLOCK_IRQMUT);
    va_start(ap, fmt);

    vsnprintf(panic_buf, sizeof(panic_buf), fmt, ap);
    trace("panic: ");
    trace(panic_buf);

    for (;;) {
        mu_cpu_halt();
    }
}
