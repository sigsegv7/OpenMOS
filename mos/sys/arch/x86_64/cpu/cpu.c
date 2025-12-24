/*
 * Copyright (c) 2025, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#include <sdk/types.h>
#include <kern/trace.h>
#include <md/msr.h>
#include <mu/cpu.h>

#define dtrace(fmt, ...) trace("cpu: " fmt, ##__VA_ARGS__)

PCR *
mu_cpu_self(void)
{
    return (PCR *)md_rdmsr(IA32_GS_BASE);
}

void
mu_cpu_conf(PCR *pcr)
{
    if (pcr == NULL) {
        return;
    }

    md_wrmsr(IA32_GS_BASE, (UPTR)pcr);
    dtrace("pcr engaged\n");
}
