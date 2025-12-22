/*
 * Copyright (c) 2025, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#ifndef _KERN_SPINLOCK_H_
#define _KERN_SPINLOCK_H_ 1

#include <sdk/types.h>
#include <sdk/status.h>
#include <sdk/param.h>

/* Parameters */
#define SPINLOCK_NAMELEN 16

/* Flags */
#define SPINLOCK_IRQMUT BIT(0)      /* Mutate IRQ state */

/*
 * Represents a spinlock
 *
 * @name: Spinlock name
 * @lock: Actual lock
 */
typedef struct {
    char name[SPINLOCK_NAMELEN];
    USIZE lock;
} SPINLOCK;

/*
 * Initialize a spinlock descriptor
 *
 * @name: Name of spinlock
 * @res: Result is written here
 */
MOS_STATUS spinlock_init(const char *name, SPINLOCK *res);

/*
 * Acquire a spinlock
 *
 * @lock: Lock to acquire
 * @flags: Optional flags
 */
void spinlock_acquire(SPINLOCK *lock, USHORT flags);

/*
 * Release a spinlock
 *
 * @lock: Lock to release
 */
void spinlock_release(SPINLOCK *lock);

#endif  /* !_KERN_SPINLOCK_H_ */
