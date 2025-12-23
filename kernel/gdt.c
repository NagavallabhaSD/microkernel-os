#include <stdint.h>
#include "gdt.h"
#include "tss.h"   // ← THIS WAS MISSING


/* GDT entry structure */
struct gdt_entry {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t  base_middle;
    uint8_t  access;
    uint8_t  granularity;
    uint8_t  base_high;
} __attribute__((packed));

/* GDT pointer */
struct gdt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

static struct gdt_entry gdt[6];   // ⬅ 6 entries (TSS included)
static struct gdt_ptr gp;

extern void gdt_flush(uint32_t);
extern struct tss_entry tss;

/* Set one GDT entry */
static void gdt_set_gate(
    int num,
    uint32_t base,
    uint32_t limit,
    uint8_t access,
    uint8_t gran
) {
    gdt[num].base_low    = base & 0xFFFF;
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high   = (base >> 24) & 0xFF;

    gdt[num].limit_low   = limit & 0xFFFF;
    gdt[num].granularity = (limit >> 16) & 0x0F;
    gdt[num].granularity |= gran & 0xF0;

    gdt[num].access = access;
}

void gdt_init() {
    gp.limit = (sizeof(struct gdt_entry) * 6) - 1;  // ⬅ FIXED
    gp.base  = (uint32_t)&gdt;

    /* 0x00: Null segment */
    gdt_set_gate(0, 0, 0, 0, 0);

    /* 0x08: Kernel code */
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

    /* 0x10: Kernel data */
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

    /* 0x18: User code */
    gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);

    /* 0x20: User data */
    gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);

    /* 0x28: TSS (THIS IS THE PART YOU ASKED ABOUT) */
    uint32_t base  = (uint32_t)&tss;
    uint32_t limit = sizeof(struct tss_entry);
    gdt_set_gate(5, base, limit, 0x89, 0x40);


    gdt_flush((uint32_t)&gp);
}
