#ifndef _TERM_H
#define _TERM_H

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "vga.h"
#include "std.h"

extern size_t terminal_row;
extern size_t terminal_column;
extern uint8_t terminal_color;
extern uint16_t* terminal_buffer;

void terminal_initialize(void);
void terminal_setcolor(uint8_t color);
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y);
void terminal_putchar(char c);
void terminal_write(const char* data, size_t size);
void println(const char* str, uint8_t color = VGA_COLOR_LIGHT_GREY);

#endif