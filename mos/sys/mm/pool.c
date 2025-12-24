/*
 * Copyright (c) 2025, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#include <sdk/types.h>
#include <sdk/units.h>
#include <kern/spinlock.h>
#include <kern/panic.h>
#include <mm/pool.h>
#include <mm/vmm.h>
#include <mm/pmm.h>

#define POOLSIZE_BYTES (UNIT_MIB * 2)
#define POOLSIZE_PAGES (POOLSIZE_BYTES / PAGESIZE)

static BOOL is_init = false;
static void *pool_virt_base;
static UPTR pool_pma = 0;
static SPINLOCK lock;
static tlsf_t tlsf_ctx;

void *
mm_pool_allocate(USIZE sz)
{
    void *tmp;

    spinlock_acquire(&lock, true);
    tmp = tlsf_malloc(tlsf_ctx, sz);
    spinlock_release(&lock);
    return tmp;
}

void
mm_pool_free(void *pool)
{
    spinlock_acquire(&lock, true);
    tlsf_free(tlsf_ctx, pool);
    spinlock_release(&lock);
}

void
mm_pool_init(void)
{
    if (is_init) {
        return;
    }

    pool_pma = mm_alloc_frame(POOLSIZE_PAGES);
    if (pool_pma == 0) {
        panic("pool: could not initialize root pool\n");
    }

    spinlock_init("pool", &lock);
    pool_virt_base = pma_to_vma(pool_pma);
    tlsf_ctx = tlsf_create_with_pool(pool_virt_base, POOLSIZE_BYTES);
    is_init = true;
}
