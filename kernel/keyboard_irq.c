#include <stdint.h>
#include "ports.h"
#include "irq.h"
#include "../ipc/ipc.h"

void keyboard_irq(void) {
    uint8_t scancode = inb(0x60);

    message_t msg;
    msg.type = 1;          // keyboard message
    msg.data[0] = scancode;

    ipc_send(&msg);
}
