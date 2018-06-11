#include "kernel.h"

#include "terminal.h"
#include "utils.h"
#include "cpuid.h"

void kernel_entry(void){
	/* Initialize terminal interface */
	_VGA_TERM_INIT();

	uint8_t complete = vga_entry_color(VGA_COLOR_GREEN, VGA_COLOR_BLACK);
	uint8_t incomplete = vga_entry_color(VGA_COLOR_RED, VGA_COLOR_BLACK);

	char* vendor[12];
	char* brand_string[12 * 4];

	cpuid_get_vendor(vendor);
	cpuid_get_brand(brand_string);

	printf("< MentalOS >\r\n\r\n");

	printf("> TODO: Implement Global Descriptor Table ");
	printf_colour("(Complete!)\r\n", complete);

	printf("\r\n");

	printf("> TODO: Setup PS/2 Keyboard driver ");
	printf_colour("(Incomplete!)\r\n", incomplete);

	printf("> TODO: Setup memory Paging (Legacy Non-PSE Non-PAE) ");
	printf_colour("(Incomplete!)\r\n", incomplete);

	printf("> TODO: Setup memory Paging (PAE) ");
	printf_colour("(Incomplete!)\r\n", incomplete);

	printf("> TODO: Implement Interrupt Descriptor Table ");
	printf_colour("(Incomplete!)\r\n", incomplete);

	printf("> TODO: Enable Long Mode ");
	printf_colour("(Incomplete!)\r\n", incomplete);

	printf("> TODO: Build a 64bit kernel ");
	printf_colour("(Incomplete!)\r\n", incomplete);

	printf("\r\nHello world :)");

	write_status_bar(brand_string);

	while (1 == 1){}
}
