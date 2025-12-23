#include "irq.h"
#include "pic.h"

static irq_handler_t irq_handlers[16];

void irq_init(void) {
    for (int i = 0; i < 16; i++)
        irq_handlers[i] = 0;
}

void irq_register(uint8_t irq, irq_handler_t handler) {
    if (irq < 16)
        irq_handlers[irq] = handler;
}

void irq_dispatch(uint8_t irq) {
    if (irq < 16 && irq_handlers[irq])
        irq_handlers[irq]();

    pic_send_eoi(irq);
}
