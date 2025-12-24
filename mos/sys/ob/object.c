/*
 * Copyright (c) 2025, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#include <sdk/status.h>
#include <sdk/atomic.h>
#include <ob/object.h>
#include <mm/pool.h>

MOS_STATUS
ob_new_object(OBJECT_TYPE type, OBJECT_HOOKS *hooks, MOS_OBJECT **res)
{
    MOS_OBJECT *object;

    if (res == NULL || hooks == NULL) {
        return STATUS_INVALID_ARG;
    }

    object = mm_pool_allocate(sizeof(*object));
    if (object == NULL) {
        return STATUS_NO_MEMORY;
    }

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
