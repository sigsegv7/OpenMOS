/*
 * Copyright (c) 2025, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#include <kern/bpt.h>
#include <kern/bptvar.h>
#include <kern/trace.h>
#include <sdk/string.h>

/*
 * Verify that the boot protocol is actually defined
 * by the build environment.
 */
#ifndef _BOOT_PROTO
#error "Boot protocol undefined"
#else
#define BOOT_PROTO (_BOOT_PROTO)
#endif  /* !_BOOT_PROTO */

static BPT_HOOKS global_hooks;

MOS_STATUS
bpt_get_vars(BPT_VARS *res)
{
    if (res == NULL) {
        return STATUS_FAILURE;
    }

    if (global_hooks.get_vars == NULL) {
        return STATUS_IO_ERROR;
    }

    return global_hooks.get_vars(res);
}

MOS_STATUS
bpt_init(void)
{
    MOS_STATUS status = STATUS_INVALID_ARG;

    switch (BOOT_PROTO[0]) {
    case 'l':
        if (strcmp(BOOT_PROTO, "limine") == 0) {
            status = bpt_limine_init(&global_hooks);
        }

        break;
    }

    trace("bpt: hooks engaged\n");
    return status;
}
