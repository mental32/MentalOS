#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
 
#include "terminal.h"
#include "utils.h"
#include "cpuid.h"

#define print printf

/* Check if the compiler thinks we are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 
/* This os will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This os needs to be compiled with a ix86-elf compiler"
#endif

int kernel_entry(){
	/* Initialize terminal interface */
	_VGA_TERM_INIT();

	char* vendor[12];
	char* brand_string[12 * 4];

	cpuid_get_vendor(vendor);
	cpuid_get_brand(brand_string);

	printf("< MentalOS >\r\n\r\n");
	printf("> TODO: Setup PS/2 Keyboard driver\r\n");
	printf("> TODO: Setup memory Paging (Legacy Non-PSE Non-PAE)\r\n");
	printf("> TODO: Setup memory Paging (PAE)\r\n");
	printf("> TODO: Implement Global Descriptor Table\r\n");
	printf("> TODO: Implement Interrupt Descriptor Table\r\n");
	printf("> TODO: Enable Long Mode\r\n");
	printf("> TODO: Build a 64bit kernel\r\n");
	printf("\r\nHello world :)")

	write_status_bar(brand_string);

	return 0;
}
