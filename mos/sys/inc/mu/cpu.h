/*
 * Copyright (c) 2025, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#ifndef _MU_CPU_H_
#define _MU_CPU_H_ 1

#include <sdk/types.h>

/*
 * Get the current IRQ state
 *
 * (TRUE: IRQs unmasked, FALSE: IRQs masked)
 */
BOOL mu_irq_state(void);

/*
 * Mask or unmask IRQs
 *
 * @mask: If true, mask IRQs
 */
void mu_irq_setmask(BOOL mask);

/*
 * Halt the current processor core
 */
void mu_cpu_halt(void);

/*
 * Signal a spinwait hint to the currnet
 * processor core
 */
void mu_cpu_pause(void);

#endif  /* !_MU_CPU_H_ */
