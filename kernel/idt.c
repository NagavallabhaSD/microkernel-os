#include <stdint.h>
#include "idt.h"

extern void irq1_handler();
extern void syscall_handler();
extern void page_fault_stub();

struct idt_entry {
    uint16_t off_low;
    uint16_t sel;
    uint8_t zero;
    uint8_t flags;
    uint16_t off_high;
} __attribute__((packed));

struct idt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

static struct idt_entry idt[256];
static struct idt_ptr idtp;

static void set_gate(int n, uint32_t h) {
    idt[n].off_low = h & 0xFFFF;
    idt[n].sel = 0x08;
    idt[n].zero = 0;
    idt[n].flags = 0x8E;
    idt[n].off_high = h >> 16;
}

void idt_init() {
    idtp.limit = sizeof(idt) - 1;
    idtp.base = (uint32_t)&idt;

    for (int i = 0; i < 256; i++)
        set_gate(i, 0);

    set_gate(33, (uint32_t)irq1_handler);
    set_gate(14, (uint32_t)page_fault_stub);
    set_gate(0x80, (uint32_t)syscall_handler);

    asm volatile("lidt (%0)" :: "r"(&idtp));
}
