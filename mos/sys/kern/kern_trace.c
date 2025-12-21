/*
 * Copyright (c) 2025, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#include <sdk/string.h>
#include <sdk/types.h>
#include <mu/uart.h>
#include <kern/trace.h>

void
trace_raw(const char *str)
{
    USIZE len;

    if (str == NULL) {
        return;
    }

    len = strlen(str);
    mu_uart_writed(str, len);
}
