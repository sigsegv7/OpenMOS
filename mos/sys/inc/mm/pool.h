/*
 * Copyright (c) 2025, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#ifndef _MM_POOL_H_
#define _MM_POOL_H_ 1

#include <sdk/types.h>
#include <mm/tlsf.h>
#include <mu/cpu.h>

/*
 * Allocate a pool of a specific size
 *
 * @sz: Number of bytes to allocate
 *
 * Returns the base of the pool allocated
 */
void *mm_pool_allocate(USIZE sz);

/*
 * Free an allocated pool
 */
void mm_pool_free(void *pool);

/*
 * Initialize the pool subsystem
 *
 * @pcr: Processor control region to fill in
 */
void mm_pool_init(PCR *pcr);

#endif  /* !_MM_POOL_H_ */
