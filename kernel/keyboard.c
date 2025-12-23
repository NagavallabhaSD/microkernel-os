#include <stdint.h>
#include "keyboard.h"

#define KBD_PORT 0x60
#define VGA ((volatile char*)0xB8000)

static const char keymap[128] = {
    0,27,'1','2','3','4','5','6','7','8','9','0','-','=',8,
    '\t','q','w','e','r','t','y','u','i','o','p','[',']','\n',0,
    'a','s','d','f','g','h','j','k','l',';','\'','`',0,'\\',
    'z','x','c','v','b','n','m',',','.','/',0,'*',0,' '
};

static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    asm volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

void keyboard_irq() {
    uint8_t sc = inb(KBD_PORT);
    if (sc & 0x80) return;

    char c = keymap[sc];

    if (c == 'p' || c == 'P') {
        volatile uint32_t* bad = (uint32_t*)0xDEADBEEF;
        *bad = 1; // 🔥 deliberate page fault
    }

    VGA[0] = c;
    VGA[1] = 0x0A;
}
