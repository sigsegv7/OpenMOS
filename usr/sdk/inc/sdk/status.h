
/*
 * Copyright (c) 2025, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#ifndef _SDK_STATUS_H_
#define _SDK_STATUS_H_ 1

#include <sdk/types.h>

#define STATUS_SUCCESS      0       /* Success */
#define STATUS_FAILURE      1       /* Unspecified failure */
#define STATUS_NOT_FOUND    2       /* Resource not found */
#define STATUS_INVALID_ARG  3       /* Invalid argument */
#define STATUS_IO_ERROR     4       /* I/O error */
#define STATUS_BUSY         5       /* Resource busy */
#define STATUS_DENIED       6       /* Access to resource denied */
#define STATUS_NO_MEMORY    7       /* Out of memory */

typedef LONG MOS_STATUS;

#endif  /* !_SDK_STATUS_H_ */
