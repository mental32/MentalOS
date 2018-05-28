#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "include/terminal.h"

inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg){
	return fg | bg << 4;
}

inline uint16_t vga_entry(unsigned char uc, uint8_t color){
	return (uint16_t) uc | (uint16_t) color << 8;
}
 
size_t strlen(const char* str) 
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

inline uint8_t set_terminal_color(enum vga_color fg, enum vga_color bg){
	terminal_color = fg | bg << 4;
}

void _VGA_TERM_INIT(void) 
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = (uint16_t*) 0xB8000;

	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

void put_char_at(char c, uint8_t color, size_t x, size_t y) 
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

void put_char(char c){
	if (c == '\n'){
		terminal_row++;
	}
	else if (c == '\r'){
		terminal_column = 0;
	}
	else{
		put_char_at(c, terminal_color, terminal_column, terminal_row);
		if (++terminal_column == VGA_WIDTH) {
			terminal_column = 0;
			if (++terminal_row == VGA_HEIGHT)
				terminal_row = 0;
		}
	}
}

void printf(const char* data){
	for (size_t i = 0; i < strlen(data); i++)
		put_char(data[i]);
}

void fill_screen(char data){
	for (size_t y = 0; y != VGA_HEIGHT; y++){
		for (size_t x = 0; x != VGA_WIDTH; x++){
			put_char_at(data, terminal_color, x, y);
		}
	}
}