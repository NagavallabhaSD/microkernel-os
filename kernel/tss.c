#include "tss.h"

struct tss_entry tss;

extern void tss_flush();

void tss_init(uint32_t kernel_stack) {
    tss.esp0 = kernel_stack;
    tss.ss0  = 0x10;   // kernel data selector
    tss.iomap = 0xFFFF;
    tss_flush();
}
