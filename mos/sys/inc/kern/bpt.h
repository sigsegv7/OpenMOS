/*
 * Copyright (c) 2025, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#ifndef _KERN_BPT_H_
#define _KERN_BPT_H_ 1

#include <sdk/types.h>
#include <sdk/status.h>

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
 * Represents boot protocol translation hooks that can
 * be used to obtain state and variables from the underlying
 * boot protocol in use.
 */
typedef struct {
    MOS_STATUS(*get_vars)(BPT_VARS *res);
} BPT_HOOKS;

/*
 * Obtain boot static variables provided by the
 * bootloader
 *
 * @res: Result is written here
 */
MOS_STATUS bpt_get_vars(BPT_VARS *res);

/*
 * Initialize the boot protocol translation layer
 */
MOS_STATUS bpt_init(void);

#endif  /* !_KERN_BPT_H_ */
