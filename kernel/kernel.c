#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
 
#include "../libc/include/terminal.h"

/* Check if the compiler thinks we are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 
/* This os will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This os needs to be compiled with a ix86-elf compiler"
#endif

void kernel_main(void) 
{
	/* Initialize terminal interface */
	_VGA_TERM_INIT();
 
	/* Newline support is left as an exercise. */
	set_terminal_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK);
	printf("Hello, kernel World!\r\nWelcome to MentalOS\r\n");
}
