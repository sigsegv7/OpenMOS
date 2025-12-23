/*
 * Copyright (c) 2025, Ian Moffett.
 * Provided under the BSD-3 clause.
 */


#ifndef _MM_VMM_H_
#define _MM_VMM_H_ 1

#include <sdk/param.h>
#include <kern/bpt.h>

/* Machine pagesize */
#define PAGESIZE 4096

/*
 * Macros to convert virtual addresses to physical and
 * vice versa.
 */
#define vma_to_pma(VMA)         \
    PTR_NOFFSET((UPTR)(VMA), bpt_kernel_base())
#define pma_to_vma(PMA)         \
    (void *)PTR_OFFSET((PMA), bpt_kernel_base())

#endif  /* !_MM_VMM_H_ */
