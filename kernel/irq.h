#ifndef IRQ_H
#define IRQ_H

#include <stdint.h>

typedef void (*irq_handler_t)(void);

void irq_init(void);
void irq_register(uint8_t irq, irq_handler_t handler);
void irq_dispatch(uint8_t irq);

#endif
