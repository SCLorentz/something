// https://wiki.osdev.org/RISC-V_Bare_Bones
#include "tty.h"

size_t terminal_row = 0;
size_t terminal_column = 0;
uint8_t terminal_color = 0;
uint16_t* terminal_buffer = (uint16_t*)0xB8000;

void terminal_initialize(void) 
{
	terminal_row = 0;
	terminal_column = 0;
    #if defined(__i686__)
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);

	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
    #endif
}

void terminal_setcolor(uint8_t color) 
{
	terminal_color = color;
}

#if defined(__i686__)
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) 
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}
#endif

#if defined(__riscv)
unsigned char * uart = (unsigned char *)0x10000000;
#endif
void terminal_putchar(char c) 
{
    #if defined(__i686__)
    terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT)
			terminal_row = 0;
	}
    #elif defined(__riscv)
    *uart = c;
	return;
    #endif
}

#if defined(__i686__)
void terminal_write(const char* data) 
{
    size_t size = strlen(data);
    for (size_t i = 0; i < size; i++)
        terminal_putchar(data[i]);
}
#elif defined(__riscv)
void terminal_write(const char* data) {
    while(*data != '\0') {
		terminal_putchar(*data);
		data++;
	}
	return;
}
#endif

#if defined(__i686__)
void println(const char* data, uint8_t color)
#elif defined(__riscv)
void println(const char* data)
#endif
{
    #if defined(__i686__)
    terminal_setcolor(color);
    #endif
    terminal_column = 0;
    terminal_write(data);
    terminal_row++;
}
