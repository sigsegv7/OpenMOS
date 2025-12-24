/*
 * Copyright (c) 2025, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#ifndef _SYS_ATOMIC_H_
#define _SYS_ATOMIC_H_ 1

#include <sdk/types.h>

static inline ULONG
atomic_add_long_nv(volatile ULONG *p, ULONG v)
{
    return __sync_add_and_fetch(p, v);
}

static inline ULONG
atomic_add_int_nv(volatile ULONG *p, ULONG v)
{
    return __sync_add_and_fetch(p, v);
}

static inline ULONG
atomic_add_64_nv(volatile UQUAD *p, ULONG v)
{
    return __sync_add_and_fetch(p, v);
}

static inline ULONG
atomic_sub_long_nv(volatile ULONG *p, ULONG v)
{
    return __sync_sub_and_fetch(p, v);
}

static inline ULONG
atomic_sub_int_nv(volatile ULONG *p, ULONG v)
{
    return __sync_sub_and_fetch(p, v);
}

static inline ULONG
atomic_sub_64_nv(volatile UQUAD *p, ULONG v)
{
    return __sync_sub_and_fetch(p, v);
}

static inline ULONG
atomic_load_int_nv(volatile ULONG *p, ULONG v)
{
    return __atomic_load_n(p, v);
}

static inline ULONG
atomic_load_long_nv(volatile ULONG *p, ULONG v)
{
    return __atomic_load_n(p, v);
}

static inline ULONG
atomic_load_64_nv(volatile UQUAD *p, ULONG v)
{
    return __atomic_load_n(p, v);
}

static inline void
atomic_store_int_nv(volatile ULONG *p, int nv, ULONG v)
{
    __atomic_store_n(p, nv, v);
}

static inline void
atomic_store_long_nv(volatile ULONG *p, LONG nv, ULONG v)
{
    __atomic_store_n(p, nv, v);
}

static inline void
atomic_store_64_nv(volatile UQUAD *p, LONG nv, ULONG v)
{
    __atomic_store_n(p, nv, v);
}

/* Atomic increment (and fetch) operations */
#define atomic_inc_long(P) atomic_add_long_nv((P), 1)
#define atomic_inc_int(P) atomic_add_int_nv((P), 1)
#define atomic_inc_64(P) atomic_add_64_nv((P), 1)

/* Atomic decrement (and fetch) operations */
#define atomic_dec_long(P) atomic_sub_long_nv((P), 1)
#define atomic_dec_int(P) atomic_sub_int_nv((P), 1)
#define atomic_dec_64(P) atomic_sub_64_nv((P), 1)

/* Atomic load operations */
#define atomic_load_int(P) atomic_load_int_nv((P), __ATOMIC_SEQ_CST)
#define atomic_load_long(P) atomic_load_long_nv((P), __ATOMIC_SEQ_CST)
#define atomic_load_64(P) atomic_load_64_nv((P), __ATOMIC_SEQ_CST)

/* Atomic store operations */
#define atomic_store_int(P, NV) atomic_store_int_nv((P), (NV), __ATOMIC_SEQ_CST)
#define atomic_store_long(P, NV) atomic_store_long_nv((P), (NV), __ATOMIC_SEQ_CST)
#define atomic_store_64(P, NV) atomic_store_64_nv((P), (NV), __ATOMIC_SEQ_CST)

#endif  /* !_SYS_ATOMIC_H_ */
