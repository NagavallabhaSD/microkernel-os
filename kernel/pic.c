#include <stdint.h>
#include "pic.h"

#define PIC1_CMD  0x20
#define PIC1_DATA 0x21
#define PIC2_CMD  0xA0
#define PIC2_DATA 0xA1

static inline void outb(uint16_t port, uint8_t val) {
    asm volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

void pic_init(void) {
    /* Start initialization */
    outb(PIC1_CMD, 0x11);
    outb(PIC2_CMD, 0x11);

    /* Remap IRQs */
    outb(PIC1_DATA, 0x20);
    outb(PIC2_DATA, 0x28);

    /* Setup cascading */
    outb(PIC1_DATA, 0x04);
    outb(PIC2_DATA, 0x02);

    /* Environment info */
    outb(PIC1_DATA, 0x01);
    outb(PIC2_DATA, 0x01);

    /* Mask all except keyboard (IRQ1) */
    outb(PIC1_DATA, 0xFD);  // 11111101
    outb(PIC2_DATA, 0xFF);
}

void pic_send_eoi(uint8_t irq) {
    if (irq >= 8)
        outb(PIC2_CMD, 0x20);

    outb(PIC1_CMD, 0x20);
}
