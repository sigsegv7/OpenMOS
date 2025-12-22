/*
 * Copyright (c) 2025, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#ifndef _KERN_BPTVAR_H_
#define _KERN_BPTVAR_H_ 1

#include <sdk/types.h>
#include <sdk/status.h>
#include <kern/bpt.h>

/* Initialize the limine boot protocol */
MOS_STATUS bpt_limine_init(BPT_HOOKS *hooks_res);

#endif  /* !_KERN_BPTVAR_H_ */
