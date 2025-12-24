/*
 * Copyright (c) 2025, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#ifndef _OB_OBJECT_H_
#define _OB_OBJECT_H_ 1

#include <sdk/queue.h>
#include <sdk/types.h>
#include <sdk/status.h>

/* Forward declarations */
struct _OBJECT_HOOKS;

/*
 * Represents valid object types that can be used
 * in the MOS object manager.
 *
 * @OBJECT_NULL: NULL object - all operations are ignored
 */
typedef enum {
    OBJECT_NULL,
} OBJECT_TYPE;

/*
 * Represents an object which contains an opaque reference
 * to another object of varying type.
 *
 * @type: Object type
 * @data: Data this object references [based on type]
 * @ref:  Reference counter
 * @hooks: Object hooks
 * @link: Queue link
 */
typedef struct _MOS_OBJECT {
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
 * @type: Object type
 * @res: Result pointer is written here
 */
MOS_STATUS ob_new_object(
    OBJECT_TYPE type, OBJECT_HOOKS *hooks,
    MOS_OBJECT **res
);

/*
 * Release an object from memory
 *
 * @obj: Object to release from memory
 */
MOS_STATUS ob_release_object(MOS_OBJECT *obj);

#endif  /* !_OB_OBJECT_H_ */
