/*
 * Copyright (c) 2025, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#include <mu/uart.h>

/* Forward declaration */
void kern_main(void);

void
kern_main(void)
{
    /* Initialize platform UARTs */
    mu_uart_init();
}
