#include <stdint.h>
#include "paging.h"

#define VGA ((volatile char*)0xB8000)
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

static uint32_t page_directory[1024] __attribute__((aligned(4096)));
static uint32_t first_page_table[1024] __attribute__((aligned(4096)));

/* Clear the entire VGA text screen */
static void clear_screen(uint8_t color) {
    for (int y = 0; y < VGA_HEIGHT; y++) {
        for (int x = 0; x < VGA_WIDTH; x++) {
            int idx = (y * VGA_WIDTH + x) * 2;
            VGA[idx] = ' ';
            VGA[idx + 1] = color;
        }
    }
}

/* Print a string at a given row */
static void print_at(const char* s, int row, uint8_t color) {
    volatile char* v = VGA + row * VGA_WIDTH * 2;
    for (int i = 0; s[i]; i++) {
        v[i * 2] = s[i];
        v[i * 2 + 1] = color;
    }
}

/* Initialize paging (identity-mapped) */
void paging_init() {
    for (int i = 0; i < 1024; i++) {
        first_page_table[i] = (i * 0x1000) | 0x3;
    }

    page_directory[0] = ((uint32_t)first_page_table) | 0x3;

    for (int i = 1; i < 1024; i++) {
        page_directory[i] = 0;
    }

    asm volatile("mov %0, %%cr3" :: "r"(page_directory));

    uint32_t cr0;
    asm volatile("mov %%cr0, %0" : "=r"(cr0));
    cr0 |= 0x80000000;
    asm volatile("mov %0, %%cr0" :: "r"(cr0));
}

/* Page fault handler (clean screen demo version) */
void page_fault_handler(uint32_t error_code, uint32_t fault_addr) {
    clear_screen(0x07);

    print_at("======================================", 5, 0x4F);
    print_at("        PAGE FAULT DETECTED             ", 6, 0x4F);
    print_at("======================================", 7, 0x4F);

    print_at("Paging is ACTIVE", 10, 0x2F);
    print_at("Invalid memory access trapped safely", 12, 0x1F);
    print_at("System halted to prevent corruption", 14, 0x1F);

    print_at("This proves paging & protection work", 17, 0x0A);

    while (1) {
        asm volatile("hlt");
    }
}
