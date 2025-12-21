/*
 * Copyright (c) 2025, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#ifndef _MU_UART_H_
#define _MU_UART_H_ 1

#include <sdk/types.h>

/*
 * Initialize available platform UARTs
 */
void mu_uart_init(void);

/*
 * Write to the default platform UART
 *
 * @s: Data to write
 * @len: Length of data in bytes
 */
void mu_uart_writed(const char *s, USIZE len);

#endif  /* !_MU_UART_H_ */
