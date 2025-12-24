/*
 * Copyright (c) 2025, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#ifndef _OB_OBJECT_H_
#define _OB_OBJECT_H_ 1

#include <sdk/queue.h>
#include <sdk/types.h>
#include <sdk/status.h>

#define OBJECT_NAMESIZE_MAX 64

/* Forward declarations */
struct _OBJECT_HOOKS;

/*
 * Represents valid object types that can be used
 * in the MOS object manager.
 *
 * @OBJECT_NULL: NULL object - all operations are ignored
 * @OBJECT_DIR: Directory object
 */
typedef enum {
    OBJECT_NULL,
    OBJECT_DIR
} OBJECT_TYPE;

/*
 * Represents an object which contains an opaque reference
 * to another object of varying type.
 *
 * @name: Object name
 * @type: Object type
 * @data: Data this object references [based on type]
 * @ref:  Reference counter
 * @hooks: Object hooks
 * @link: Queue link
 */
typedef struct _MOS_OBJECT {
    char name[OBJECT_NAMESIZE_MAX];
    OBJECT_TYPE type;
    void *data;
    ULONG ref;
    struct _OBJECT_HOOKS *hooks;
    TAILQ_ENTRY(_MOS_OBJECT) link;
} MOS_OBJECT;

/*
 * Represents various hooks that are invoked during
 * different object related events.
 */
typedef struct _OBJECT_HOOKS {
    void(*reclaim)(MOS_OBJECT *obj);
} OBJECT_HOOKS;

/*
 * Create a new system object.
 *
 * @name: Object name
 * @type: Object type
 * @hooks: Hooks to use
 * @res: Result pointer is written here
 */
MOS_STATUS ob_new_object(
    const char *name, OBJECT_TYPE type,
    OBJECT_HOOKS *hooks, MOS_OBJECT **res
);

/*
 * Release an object from memory
 *
 * @obj: Object to release from memory
 */
MOS_STATUS ob_release_object(MOS_OBJECT *obj);

#endif  /* !_OB_OBJECT_H_ */
