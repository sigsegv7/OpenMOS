/*
 * Copyright (c) 2025, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#include <sdk/types.h>
#include <sdk/status.h>
#include <proto/limine.h>
#include <kern/bpt.h>
#include <kern/bptvar.h>

/* HHDM request */
static struct limine_hhdm_response *hhdm_resp;
static volatile struct limine_hhdm_request hhdm_req = {
    .id = LIMINE_HHDM_REQUEST,
    .revision = 0
};

static MOS_STATUS
limine_get_vars(BPT_VARS *res)
{
    if (res == NULL) {
        return STATUS_INVALID_ARG;
    }

    res->kernel_base = hhdm_resp->offset;
    return STATUS_SUCCESS;
}

MOS_STATUS
bpt_limine_init(BPT_HOOKS *hooks_res)
{
    if (hooks_res == NULL) {
        return STATUS_INVALID_ARG;
    }

    hhdm_resp = hhdm_req.response;
    hooks_res->get_vars = limine_get_vars;
    return STATUS_SUCCESS;
}
