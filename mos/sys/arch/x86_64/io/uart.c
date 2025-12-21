/*
 * Copyright (c) 2025, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#include <sdk/param.h>
#include <sdk/types.h>
#include <mu/uart.h>
#include <md/uart.h>
#include <md/pio.h>

#define DEFAULT_PORT UART_COM1

static USHORT commap[] = {
    UART_COM1, UART_COM2,
    UART_COM3, UART_COM4
};

static void
init_uart(USHORT port)
{
    UBYTE reg;

    /* Clear DLAB bit */
    reg = md_inb(UART_LCR(port));
    reg &= ~UART_LCR_DLAB;
    reg &= ~UART_PARITY_MASK;
    reg |= UART_LCR_STOP;
    md_outb(UART_LCR(port), reg);

    /* Disable interrupts */
    md_outb(UART_INTEN(port), 0);

    /* Set DLAB */
    reg = md_inb(UART_LCR(port));
    reg |= UART_LCR_DLAB;
    md_outb(UART_LCR(port), reg);

    /* 38400 baud */
    md_outb(UART_DIVLOW(port), 0x03);
    md_outb(UART_DIVHIGH(port), 0x00);
}

void
mu_uart_write(const char *s, USIZE len)
{
    for (USIZE i = 0; i < len; ++i) {
        md_outb(DEFAULT_PORT, s[i]);
    }
}

void
mu_uart_init(void)
{
    for (int i = 0; i < NELEM(commap); ++i) {
        init_uart(commap[i]);
    }
}
