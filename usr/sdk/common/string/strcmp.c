/*
 * Copyright (c) 2025, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#include <sdk/string.h>
#include <sdk/types.h>

int
strcmp(const char *s1, const char *s2)
{
    while (*s1 == *s2++) {
        if (*s1++ == 0) {
            return (0);
        }
    }

    return (*(UBYTE *)s1 - *(UBYTE *)--s2);
}
