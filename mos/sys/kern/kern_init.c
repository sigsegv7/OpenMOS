/*
 * Copyright (c) 2025, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#include <kern/trace.h>
#include <kern/bpt.h>
#include <mu/uart.h>
#include <mu/cpu.h>
#include <mm/pmm.h>
#include <mm/pool.h>

#define write_boot_header()                     \
    trace_raw(                                  \
        "=========  M  /  O  S  ========\n"     \
        "Copyright (c) 2025, Ian Moffett\n"     \
        "===============================\n"     \
        "[ booting m/os ... ]\n"                \
    );

/* Forward declaration */
void kern_main(void);

static PCR bsp_pcr;

void
kern_main(void)
{
    /* Initialize platform UARTs */
    mu_uart_init();

    /* Write the boot header */
    write_boot_header();

    /* Initialize the boot protocol translation layer */
    bpt_init();

    /* Initialize the physical memory manager */
    pmm_init();

    /* Initialize the pool manager */
    mm_pool_init();

    /* Initialize the BSP PCR */
    mu_cpu_conf(&bsp_pcr);
}
