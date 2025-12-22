/*
 * Copyright (c) 2025, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#include <sdk/string.h>

void *
memcpy(void *dest, const void *src, USIZE count)
{
    if (dest == NULL || src == NULL) {
        return NULL;
    }

    for (USIZE i = 0; i < count; ++i) {
        ((char *)dest)[i] = ((char *)src)[i];
    }

    return dest;
}
