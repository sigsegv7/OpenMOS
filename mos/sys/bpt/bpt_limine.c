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

/* Memory map */
static struct limine_memmap_response *mem_resp;
static volatile struct limine_memmap_request mem_req = {
    .id = LIMINE_MEMMAP_REQUEST,
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

static MOS_STATUS
limine_get_mementry(USIZE index, BPT_MEMENTRY *res)
{
    struct limine_memmap_entry *entry;

    if (res == NULL) {
        return STATUS_INVALID_ARG;
    }

    if (index >= mem_resp->entry_count) {
        return STATUS_INVALID_ARG;
    }

    entry = mem_resp->entries[index];
    res->base = entry->base;
    res->length = entry->length;
    res->type = entry->type;    /* 1:1 */
    return STATUS_SUCCESS;
}

MOS_STATUS
bpt_limine_init(BPT_HOOKS *hooks_res)
{
    if (hooks_res == NULL) {
        return STATUS_INVALID_ARG;
    }

    hhdm_resp = hhdm_req.response;
    mem_resp = mem_req.response;

    hooks_res->get_vars = limine_get_vars;
    hooks_res->get_mementry = limine_get_mementry;
    return STATUS_SUCCESS;
}
