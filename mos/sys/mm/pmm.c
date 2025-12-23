/*
 * Copyright (c) 2025, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#include <sdk/types.h>
#include <sdk/param.h>
#include <sdk/units.h>
#include <sdk/string.h>
#include <kern/bpt.h>
#include <kern/trace.h>
#include <kern/spinlock.h>
#include <mm/pmm.h>
#include <mm/vmm.h>

#define dtrace(fmt, ...) trace("pmm: " fmt, ##__VA_ARGS__)

/* Memory statistics */
static USIZE mem_total = 0;
static USIZE mem_free = 0;
static UPTR usable_top = 0;

/* Bitmap */
static UBYTE *bitmap = NULL;
static USIZE bitmap_size = 0;
static USIZE last_bit = 0;
static SPINLOCK bitmap_lock;

/*
 * Table to convert numeric memory types into string
 * values
 */
static const char *memtype_tab[] = {
    [BPT_MEM_USABLE] = "usable",
    [BPT_MEM_RESERVED] = "reserved",
    [BPT_MEM_ACPI_RECLAIM] = "acpi reclaim",
    [BPT_MEM_ACPI_NVS] = "acpi nvs",
    [BPT_MEM_BAD] = "bad!",
    [BPT_MEM_BOOTLOADER] = "bootloader",
    [BPT_MEM_KERNEL] = "kernel",
    [BPT_MEM_FRAMEBUFFER] = "framebuffer"
};

/*
 * Print out storage size for stat dumps
 */
static inline void
print_mem_size(const char *title, USIZE length)
{
    if (title == NULL) {
        title = "bad";
    }

    if (length >= UNIT_GIB) {
        dtrace("%s :: %d gib\n", title, length / UNIT_GIB);
    } else if (length >= UNIT_MIB) {
        dtrace("%s :: %d mib\n", title, length / UNIT_MIB);
    } else {
        dtrace("%s :: %d bytes\n", title, length);
    }
}

/*
 * Mark a range in the bitmap as allocated or free
 *
 * @start: Range start
 * @end:   Range end
 * @alloc: If true, mark as allocated (1)
 *
 * 1: ALLOCATED
 * 0: FREE
 */
static void
bitmap_set_range(UPTR start, UPTR end, BOOL alloc)
{
    /* Clamp range to page boundary */
    start = ALIGN_DOWN(start, PAGESIZE);
    end = ALIGN_UP(end, PAGESIZE);

    for (UPTR p = start; p < end; p += PAGESIZE) {
        if (alloc) {
            SETBIT(bitmap, p / PAGESIZE);
        } else {
            CLRBIT(bitmap, p / PAGESIZE);
        }
    }
}

static void
pmm_fill_bitmap(void)
{
    BPT_MEMENTRY entry;
    MOS_STATUS status;
    UPTR start, end;

    /* Fill it all as allocated */
    memset(bitmap, 0xFF, bitmap_size);

    /* Go through each segment of memory */
    for (USIZE i = 0;; ++i) {
        status = bpt_get_mementry(i, &entry);

        /* End of list? */
        if (status != STATUS_SUCCESS) {
            break;
        }

        if (entry.type == BPT_MEM_USABLE) {
            start = entry.base;
            end = start + entry.length;
            bitmap_set_range(start, end, false);
        }
    }
}

static void
pmm_alloc_bitmap(void)
{
    BPT_MEMENTRY entry;
    MOS_STATUS status;

    /* Go through each segment of memory */
    for (USIZE i = 0;; ++i) {
        status = bpt_get_mementry(i, &entry);

        /* End of list? */
        if (status != STATUS_SUCCESS) {
            break;
        }

        if (entry.length < bitmap_size) {
            continue;
        }

        bitmap = pma_to_vma(entry.base);
        break;
    }

    pmm_fill_bitmap();
}

/*
 * Allocate one or more physical memory frames
 */
static UPTR
pmem_alloc(USIZE count)
{
    SSIZE start_idx = -1;
    USIZE frames_found = 0;
    UPTR start, end;
    USIZE max_bit;

    max_bit = usable_top / PAGESIZE;
    for (USIZE i = last_bit; i < max_bit; ++i) {
        if (!TESTBIT(bitmap, i)) {
            if (start_idx < 0)
                start_idx = i;
            if ((++frames_found) >= count)
                break;

            continue;
        }

        start_idx = -1;
    }

    if (start_idx < 0) {
        return 0;
    }

    start = start_idx * PAGESIZE;
    end = start + (count * PAGESIZE);
    bitmap_set_range(start, end, true);
    return start;
}

/*
 * Probe the physical memory and discover attributes
 * and such
 */
static void
pmm_probe(void)
{
    BPT_MEMENTRY entry;
    MOS_STATUS status;
    UPTR base, end;
    const char *typestr;

    /* Go through each segment of memory */
    for (USIZE i = 0;; ++i) {
        status =  bpt_get_mementry(i, &entry);

        /* End of list? */
        if (status != STATUS_SUCCESS) {
            break;
        }

        /* Drop bad entries */
        if (entry.type >= NELEM(memtype_tab)) {
            continue;
        }

        /* Get information about the area */
        base = entry.base;
        end = entry.base + entry.length;
        typestr = memtype_tab[entry.type];
        mem_total += entry.length;

        dtrace(
            "[%p - %p) :: %s\n",
            base,
            end,
            typestr == NULL
            ? "bad entry"
            : typestr
        );

        /* Usable memory types from here on out */
        if (entry.type != BPT_MEM_USABLE) {
            continue;
        }

        /* Get the highest usable address */
        if (end > usable_top) {
            usable_top = end;
        }

        mem_free += entry.length;
    }

    /* Compute the length of the bitmap */
    bitmap_size = usable_top / PAGESIZE;
    bitmap_size = ALIGN_UP(bitmap_size, 8) / 8;

    /* Print memory stats */
    print_mem_size("memory free", mem_free);
    print_mem_size("memory total", mem_total);
    print_mem_size("bitmap size", bitmap_size);
    dtrace("usable memory top <@> :: %p\n", usable_top);
}

UPTR
mm_alloc_frame(USIZE count)
{
    UPTR phys;

    spinlock_acquire(&bitmap_lock, SPINLOCK_IRQMUT);
    phys = pmem_alloc(count);
    if (phys == 0) {
        last_bit = 0;
        phys = pmem_alloc(count);
    }

    spinlock_release(&bitmap_lock);
    return phys;
}

void
mm_free_frame(UPTR base, USIZE count)
{
    UPTR range_end;

    spinlock_acquire(&bitmap_lock, SPINLOCK_IRQMUT);
    range_end = base + (count * PAGESIZE);
    bitmap_set_range(base, range_end, false);
    spinlock_release(&bitmap_lock);
}

void
pmm_init(void)
{
    spinlock_init("pmm", &bitmap_lock);

    dtrace("begin memory probe\n");
    pmm_probe();

    pmm_alloc_bitmap();
    dtrace("bitmap allocated OK\n");
}
