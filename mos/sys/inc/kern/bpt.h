/*
 * Copyright (c) 2025, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#ifndef _KERN_BPT_H_
#define _KERN_BPT_H_ 1

#include <sdk/types.h>
#include <sdk/status.h>
#include <sdk/defs.h>

/*
 * Represents memory map entry types
 */
typedef enum {
    BPT_MEM_USABLE,
    BPT_MEM_RESERVED,
    BPT_MEM_ACPI_RECLAIM,
    BPT_MEM_ACPI_NVS,
    BPT_MEM_BAD,
    BPT_MEM_BOOTLOADER,
    BPT_MEM_KERNEL,
    BPT_MEM_FRAMEBUFFER
} BPT_MEM_TYPE;

/*
 * Represents boot protocol translation variables that
 * contain information provided by the bootloader
 *
 * @kernel_base: Higher half direct map offset (kernel load base)
 */
typedef struct {
    UPTR kernel_base;
} BPT_VARS;

/*
 * Represents a memory map entry
 *
 * @base: Base address of memory area
 * @length: Length of memory area in bytes
 * @type: Memory entry type
 */
typedef struct {
    UPTR base;
    USIZE length;
    BPT_MEM_TYPE type;
} BPT_MEMENTRY;

/*
 * Represents boot protocol translation hooks that can
 * be used to obtain state and variables from the underlying
 * boot protocol in use.
 */
typedef struct {
    MOS_STATUS(*get_vars)(BPT_VARS *res);
    MOS_STATUS(*get_mementry)(USIZE index, BPT_MEMENTRY *res);
} BPT_HOOKS;

/*
 * Obtain boot static variables provided by the
 * bootloader
 *
 * @res: Result is written here
 */
MOS_STATUS bpt_get_vars(BPT_VARS *res);

/*
 * Obtain a memory map entry
 *
 * @index: Entry index
 * @res: Entry result
 *
 * Returns STATUS_SUCCESS if the entry index is within
 * proper range.
 */
MOS_STATUS bpt_get_mementry(USIZE index, BPT_MEMENTRY *res);

/*
 * Initialize the boot protocol translation layer
 */
MOS_STATUS bpt_init(void);

ALWAYS_INLINE static inline UPTR
bpt_kernel_base(void)
{
    BPT_VARS vars;

    if (bpt_get_vars(&vars) != STATUS_SUCCESS) {
        return 0;
    }

    return vars.kernel_base;
}

#endif  /* !_KERN_BPT_H_ */
