/*
 * Copyright (c) 2025, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#ifndef _KERN_TRACE_H_
#define _KERN_TRACE_H_

#define TRACE_BUF_LEN 256

/*
 * Write a raw null terminated string to the system
 * trace logs
 *
 * @str: String to write
 */
void trace_raw(const char *str);

/*
 * Write a formatted string to the system trace
 * logs
 *
 * @fmt: Format string
 * @<...>: Args
 */
void trace(const char *fmt, ...);

#endif  /* !_KERN_TRACE_H_ */
