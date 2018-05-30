#include <stdint.h>

static char lookup[] = "e1234567890-=tqwertyuiop[]Easdfghjkl;'`\\zxcvbnm,./";

static inline void outb(uint16_t port, uint8_t val){
    asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
    /* There's an outb %al, $imm8  encoding, for compile-time constant port numbers that fit in 8b.  (N constraint).
     * Wider immediate constants would be truncated at assemble-time (e.g. "i" constraint).
     * The  outb  %al, %dx  encoding is the only option for all other cases.
     * %1 expands to %dx because  port  is a uint16_t.  %w1 could be used if we had the port number a wider C type */
}

static inline uint8_t inb(uint16_t port){
    uint8_t ret;
    asm volatile ( "inb %1, %0"
                   : "=a"(ret)
                   : "Nd"(port) );
    return ret;
}

static inline uint16_t inw(uint16_t port){
    uint8_t ret;
    asm volatile ( "inw %1, %0"
                   : "=a"(ret)
                   : "Nd"(port) );
    return ret;
}

static inline uint32_t inl(uint16_t port){
    uint8_t ret;
    asm volatile ( "inl %1, %0"
                   : "=a"(ret)
                   : "Nd"(port) );
    return ret;
}

int get_scancode_set(){
	while (!(inb(0x64) & 2));
	outb(0x64, 0xF0);
	while (!(inb(0x64) & 1));
	return 5;	
}


uint8_t get_status(){
	return inb(0x64);
}

uint8_t getScancode(){
    while (!(inb(0x64) & 1));
    return inb(0x60);
}

char getchar(){
    return lookup[getScancode() + 1];
}
