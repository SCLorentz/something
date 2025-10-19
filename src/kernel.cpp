// https://wiki.osdev.org/Bare_Bones --> I don't actualy include and .iso maker, but this tutorial includes this
#include "std.h"

/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

/*#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif*/

extern "C" void kernel_main(void) 
{
    terminal_initialize();
    println("Hello, kernel World!");
    println("message in white", VGA_COLOR_WHITE);
    println("message in red", VGA_COLOR_RED);
}
