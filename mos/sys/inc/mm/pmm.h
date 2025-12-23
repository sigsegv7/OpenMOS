/*
 * Copyright (c) 2025, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#ifndef _MM_PMM_H_
#define _MM_PMM_H_ 1

#include <sdk/types.h>

/*
 * Allocate one or more physical memory frames
 *
 * @count: Number of frames to allocate
 * @flags: Optional flags
 *
 * Returns the base of the page aligned area on success
 * and zero on failure.
 */
UPTR mm_alloc_frame(USIZE count);

/*
 * Deallocate a previously allocated region of frames
 *
 * @base: Base of frames
 * @count: Number of frames to free
 */
void mm_free_frame(UPTR base, USIZE count);

/*
 * Initialize the physical memory manager
 */
void pmm_init(void);

#endif  /* !_MM_PMM_H_ */
