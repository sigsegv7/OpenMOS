/*
 * Copyright (c) 2025, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#ifndef _SDK_STRING_H_
#define _SDK_STRING_H_ 1

 #include <sdk/types.h>

/*
 * Returns the length of a string
 *
 * @str: String to get length of
 */
USIZE strlen(const char *str);

/*
 * Copy a variable number of bytes from one memory location
 * to another.
 *
 * @dest: Destination buffer
 * @src: Source buffer
 * @count: Byte count
 *
 * Returns the base of `dest' on success
 */
void *memcpy(void *dest, const void *src, USIZE count);

#endif  /* !_SDK_STRING_H_ */
