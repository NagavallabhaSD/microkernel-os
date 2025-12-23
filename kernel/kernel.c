#include "gdt.h"
#include "idt.h"
#include "tss.h"
#include "paging.h"
#include "keyboard.h"
#include "pic.h"
#include "../ipc/ipc.h"

extern uint32_t kernel_stack_top;
extern void console_start();

void kernel_main() {
    gdt_init();
    tss_init((uint32_t)&kernel_stack_top);
    idt_init();
    pic_init();          // 🔴 REQUIRED
    paging_init();

    ipc_init();
    console_start();

    asm volatile("sti"); // 🔴 ENABLE INTERRUPTS

    while (1) asm volatile("hlt");
}
