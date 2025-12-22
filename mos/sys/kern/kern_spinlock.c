/*
 * Copyright (c) 2025, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#include <sdk/types.h>
#include <sdk/status.h>
#include <sdk/string.h>
#include <mu/cpu.h>
#include <kern/spinlock.h>

MOS_STATUS
spinlock_init(const char *name, SPINLOCK *res)
{
    USIZE name_len;

    if (name == NULL || res == NULL) {
        return STATUS_INVALID_ARG;
    }

    name_len = strlen(name);
    if (name_len >= SPINLOCK_NAMELEN - 1) {
        return STATUS_NAME_TOO_LONG;
    }

    memcpy(res->name, name, name_len);
    res->lock = 0;
    return STATUS_SUCCESS;
}

void
spinlock_acquire(SPINLOCK *lock, USHORT flags)
{
    BOOL irq_state = false;

    if (lock == NULL) {
        return;
    }

    /*
     * Usually this should be the default but this kind of thing should
     * be somewhat deterministic. If we are to mutate, mask the interrupts.
     */
    if (ISSET(flags, SPINLOCK_IRQMUT)) {
        irq_state = mu_irq_state();
        mu_irq_setmask(true);
    }

    /*
     * Now we'll spin. And no, we will not put ourselves to sleep
     * here. This needs to be invoked early on before there even
     * is such thing as a process context.
     */
    while (mu_cpu_aswap(&lock->lock, 1)) {
        mu_cpu_pause();
    }

    /* Restore the state if we've mutated it */
    if (ISSET(flags, SPINLOCK_IRQMUT) && irq_state) {
        mu_irq_setmask(false);
    }
}

void
spinlock_release(SPINLOCK *lock)
{
    if (lock == NULL) {
        return;
    }

    mu_cpu_aswap(&lock->lock, 0);
}
