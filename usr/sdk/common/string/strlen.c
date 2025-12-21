/*
 * Copyright (c) 2025, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#include <sdk/string.h>
#include <sdk/types.h>

USIZE
strlen(const char *str)
{
    USIZE len = 0;

    if (str == NULL) {
        return 0;
    }

    while (str[len++] != '\0');
    return len - 1;
}
