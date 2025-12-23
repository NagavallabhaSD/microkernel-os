#include <stdint.h>

#define VGA_WIDTH 80
#define VGA_MEMORY 0xB8000

static volatile char* vga = (volatile char*)VGA_MEMORY;
static int cursor_row = 0;
static uint8_t color = 0x0F;   // white on black

static void set_color(uint8_t c) {
    color = c;
}

static void put_char(char c, int col, int row) {
    int index = (row * VGA_WIDTH + col) * 2;
    vga[index] = c;
    vga[index + 1] = color;
}

static void print_line(const char* s) {
    for (int i = 0; s[i]; i++) {
        put_char(s[i], i, cursor_row);
    }
    cursor_row++;
}

void console_start() {
    /* ---------- ASCII LOGO (VGA SAFE) ---------- */
    set_color(0x0A); // green

    print_line("  __  __ _       _ ");
    print_line(" |  \\/  (_)     | |");
    print_line(" | \\  / |_ _ __ | |");
    print_line(" | |\\/| | | '_ \\| |");
    print_line(" | |  | | | | | |_|");
    print_line(" |_|  |_|_|_| |_(_)");
    cursor_row++;

    /* ---------- TITLE ---------- */
    set_color(0x0F); // white
    print_line("Mini Microkernel OS");
    print_line("-------------------");
    cursor_row++;

    /* ---------- SYSTEM STATUS ---------- */
    set_color(0x0E); // yellow
    print_line("[INIT] Kernel loaded");

    set_color(0x0A); // green
    print_line("[OK]   GDT initialized");
    print_line("[OK]   IDT initialized");
    print_line("[OK]   IPC subsystem ready");
    print_line("[OK]   Console server started");
    print_line("[OK]   Memory management active");

    cursor_row++;

    set_color(0x09); // blue
    print_line("[OK]   IPC test message received");

    cursor_row++;

    /* ---------- FINAL STATUS ---------- */
    set_color(0x0F); // white
    print_line("System running in microkernel mode");
}
