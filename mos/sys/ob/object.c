/*
 * Copyright (c) 2025, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#include <sdk/status.h>
#include <sdk/atomic.h>
#include <sdk/string.h>
#include <ob/object.h>
#include <mm/pool.h>

MOS_STATUS
ob_new_object(const char *name, OBJECT_TYPE type, OBJECT_HOOKS *hooks, MOS_OBJECT **res)
{
    MOS_OBJECT *object;
    USIZE name_len;

    if (res == NULL || hooks == NULL) {
        return STATUS_INVALID_ARG;
    }

    /* Truncate the name if needed */
    name_len = strlen(name);
    if (name_len >= OBJECT_NAMESIZE_MAX) {
        name_len = OBJECT_NAMESIZE_MAX - 1;
    }

    object = mm_pool_allocate(sizeof(*object));
    if (object == NULL) {
        return STATUS_NO_MEMORY;
    }

    memcpy(object->name, name, name_len);
    object->type  = type;
    object->data  = NULL;
    object->ref   = 1;
    object->hooks = hooks;
    *res = object;
    return STATUS_SUCCESS;
}

MOS_STATUS
ob_release_object(MOS_OBJECT *obj)
{
    OBJECT_HOOKS *hooks;

    if (obj == NULL) {
        return STATUS_INVALID_ARG;
    }

    if ((hooks = obj->hooks) == NULL) {
        return STATUS_IO_ERROR;
    }

    /* Drop the ref, bail if there are still references */
    if (atomic_dec_int(&obj->ref) > 0) {
        return STATUS_SUCCESS;
    }

    /* Reclaim the object if we can */
    if (hooks->reclaim != NULL) {
        hooks->reclaim(obj);
    }

    mm_pool_free(obj);
    return STATUS_SUCCESS;
}
