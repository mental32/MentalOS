#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "include/terminal.h"
#include "include/port.h"
#include "include/utils.h"

inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg){
	return fg | bg << 4;
}

inline uint16_t vga_entry(unsigned char uc, uint8_t color){
	return (uint16_t) uc | (uint16_t) color << 8;
}

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

inline void set_terminal_color(enum vga_color fg, enum vga_color bg){
	terminal_color = fg | bg << 4;
}

void move_cursor(unsigned short pos){
	outb(0x3d4, 14);
	outb(0x3d5, ((pos >> 8) & 0x00ff));
	outb(0x3d4, 15);
	outb(0x3d5, pos & 0x00ff);
}

void auto_move_cursor(){
	unsigned short pos = 0;
	pos = pos + terminal_row * 80;
	pos = pos + terminal_column;

	move_cursor(pos);
}

void _VGA_TERM_INIT(void) 
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK);
	terminal_buffer = (uint16_t*) 0xB8000;

	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}

	_show_vga_logo();
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
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
	auto_move_cursor();
}

void printf(const char* data, ...){
	for (int i = 0; i < strlen(data); i++)
		put_char(data[i]);
}

void printf_colour(const char* data, uint8_t colour){
	uint8_t old_colour = terminal_color; // save old terminal colour
	terminal_color = colour;             // use new colour

	for (int i = 0; i < strlen(data); i++){
		put_char(data[i]);
	}

	terminal_color = old_colour;        // return previous colour
}

void fill_screen(char data){
	for (size_t y = 0; y != VGA_HEIGHT; y++){
		for (size_t x = 0; x != VGA_WIDTH; x++){
			put_char_at(data, terminal_color, x, y);
		}
	}
}

const char* _vga_logo = " __  __            _        _  ___  ____  \n\r"
						"|  \\/  | ___ _ __ | |_ __ _| |/ _ \\/ ___| \n\r"
						"| |\\/| |/ _ \\ '_ \\| __/ _` | | | | \\___ \\ \n\r"
						"| |  | |  __/ | | | || (_| | | |_| |___) |\n\r"
						"|_|  |_|\\___|_| |_|\\__\\__,_|_|\\___/|____/ \n\r"
						"                                          \n\r";

void _show_vga_logo(void){
	printf(_vga_logo);
}

void write_status_bar(char* data){
	size_t _oldx, _oldy;
	_oldx = terminal_column;
	_oldy = terminal_row;

	terminal_row = 24;
	terminal_column = 0;

	printf(data);

	terminal_row = _oldy;
	terminal_column = _oldx;
	auto_move_cursor();
}
