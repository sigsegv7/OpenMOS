/*
 * Copyright (c) 2025, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#include <sdk/string.h>

void *
memset(void *s, int c, USIZE n)
{
    if (s == NULL) {
        return NULL;
    }

    for (USIZE i = 0; i < n; ++i) {
        ((BYTE *)s)[i] = c;
    }

    return s;
}
