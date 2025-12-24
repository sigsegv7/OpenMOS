/*
 * Copyright (c) 2025, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#include <sdk/status.h>
#include <mm/pool.h>
#include <ob/directory.h>
#include <ob/object.h>

/* Forward declaration */
static OBJECT_HOOKS hooks;

static void
directory_reclaim(MOS_OBJECT *obj)
{
    if (obj->data != NULL) {
        mm_pool_free(obj->data);
    }

    obj->data = NULL;
}

MOS_STATUS
ob_new_directory(const char *name, MOS_OBJECT **res)
{
    MOS_OBJECT *ob;
    OBJECT_DIRECTORY *dir;
    MOS_STATUS status;

    if (res == NULL) {
        return STATUS_INVALID_ARG;
    }

    /* Allocate a backend directory object */
    dir = mm_pool_allocate(sizeof(*dir));
    if (dir == NULL) {
        return STATUS_NO_MEMORY;
    }

    /* Create a new frontend object */
    status = ob_new_object(name, OBJECT_DIR, &hooks, &ob);
    if (status != STATUS_SUCCESS) {
        mm_pool_free(dir);
    }

    TAILQ_INIT(&dir->list);
    ob->data = dir;
    *res = ob;
    return STATUS_SUCCESS;
}

static OBJECT_HOOKS hooks = {
    .reclaim = directory_reclaim
};
