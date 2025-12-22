/*
 * Copyright (c) 2025, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#include <kern/trace.h>
#include <kern/bpt.h>
#include <mu/uart.h>

#define write_boot_header()                     \
    trace_raw(                                  \
        "=========  M  /  O  S  ========\n"     \
        "Copyright (c) 2025, Ian Moffett\n"     \
        "===============================\n"     \
        "[ booting m/os ... ]\n"                \
    );

/* Forward declaration */
void kern_main(void);

void
kern_main(void)
{
    /* Initialize platform UARTs */
    mu_uart_init();

    /* Write the boot header */
    write_boot_header();

    /* Initialize the boot protocol translation layer */
    bpt_init();
}
