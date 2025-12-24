/*
 * Copyright (c) 2025, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#ifndef _OB_DIRECTORY_H_
#define _OB_DIRECTORY_H_ 1

#include <sdk/queue.h>
#include <sdk/status.h>
#include <sdk/types.h>
#include <ob/object.h>

/*
 * Represents an directory object
 *
 * @entry_count: Number of entries
 * @list: Object list
 */
typedef struct {
    USIZE entry_count;
    TAILQ_HEAD(, MOS_OBJECT) list;
} OBJECT_DIRECTORY;

/*
 * Create a new directory object
 *
 * @name: Directory name
 * @res: Directory object pointer is written here
 */
MOS_STATUS ob_new_directory(const char *name, MOS_OBJECT **res);

#endif  /* !_OB_DIRECTORY_H_ */
