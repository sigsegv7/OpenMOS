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

void *
mm_pool_allocate(USIZE sz)
{
    PCR *pcr = mu_cpu_self();
    void *tmp;

    spinlock_acquire(&pcr->tlsf_lock, true);
    tmp = tlsf_malloc(pcr->tlsf, sz);
    spinlock_release(&pcr->tlsf_lock);
    return tmp;
}

void
mm_pool_free(void *pool)
{
    PCR *pcr = mu_cpu_self();

    spinlock_acquire(&pcr->tlsf_lock, true);
    tlsf_free(pcr->tlsf, pool);
    spinlock_release(&pcr->tlsf_lock);
}

void
mm_pool_init(PCR *pcr)
{
    void *pool_virt_base;
    UPTR pool_pma;

    if (pcr == NULL) {
        return;
    }

    pool_pma = mm_alloc_frame(POOLSIZE_PAGES);
    if (pool_pma == 0) {
        panic("pool: could not initialize root pool\n");
    }

    spinlock_init("pool", &pcr->tlsf_lock);
    pool_virt_base = pma_to_vma(pool_pma);
    pcr->tlsf = tlsf_create_with_pool(pool_virt_base, POOLSIZE_BYTES);
}
