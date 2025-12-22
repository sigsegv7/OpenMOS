/*
 * Copyright (c) 2025, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#include <sdk/types.h>
#include <sdk/string.h>

static char *itoa_base10_convert(QUAD value, char *buf);

static char *
itoa_base10_convert(QUAD value, char *buf)
{
    UQUAD i;
    UBYTE tmp;
    BOOL is_negative;

    i = 0;
    is_negative = false;

    if (value == 0) {
        buf[i++] = '0';
        buf[i++] = '\0';
        return buf;
    }

    if (value < 0) {
        /* Easier to handle positive numbers */
        value *= -1;
        is_negative = true;
    }

    while (value > 0) {
        buf[i++] = '0' + (value % 10);
        value /= 10;
    }

    if (is_negative) {
        buf[i++] = '-';
    }

    buf[i--] = '\0';

    /* Result is in reverse */
    for (int j = 0; j < i; ++j, --i) {
        tmp = buf[j];
        buf[j] = buf[i];
        buf[i] = tmp;
    }

    return buf;
}

static char *
itoa_convert_base16(UQUAD n, char *buffer)
{
    BOOL pad;
    UBYTE nibble;
    UBYTE i, j, tmp;
    const char *ascii_nums = "0123456789ABCDEF";

    i = 0;
    pad = false;

    if (n == 0) {
        /* Zero, no need to parse */
        memcpy(buffer, "0x00\0", 5);
        return buffer;
    }
    /* If one digit, pad out 2 later */
    if (n < 0x10) {
        pad = true;
    }

    while (n > 0) {
        nibble = (UBYTE)n & 0x0F;
        nibble = ascii_nums[nibble];
        buffer[i++] = nibble;
        n >>= 4;        /* Fetch next nibble */
    }

    if (pad) {
        buffer[i++] = '0';
    }

    /* Add "0x" prefix */
    buffer[i++] = 'x';
    buffer[i++] = '0';
    buffer[i--] = '\0';

    /* Unreverse the result */
    for (j = 0; j < i; ++j, --i) {
        tmp = buffer[j];
        buffer[j] = buffer[i];
        buffer[i] = tmp;
    }
    return buffer;
}

char *
itoa(QUAD value, char *buf, int base)
{
    switch (base) {
        case 10:
            return itoa_base10_convert(value, buf);
        case 16:
            return itoa_convert_base16(value, buf);
        default:
            return NULL;
    }
}
