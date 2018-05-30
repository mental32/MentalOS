#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>	

#include "include/gnu_cpuid.h"
#include "include/memory.h"
#include "include/terminal.h"

void cpuid_get_brand(char *buf){
    uint32_t *brand = (uint32_t *)buf;
    __cpuid(0x80000002 , brand[0], brand[1], brand[2], brand[3]);
    __cpuid(0x80000003 , brand[4], brand[5], brand[6], brand[7]);
    __cpuid(0x80000004 , brand[8], brand[9], brand[10], brand[11]);
}

void cpuid_get_vendor(char *buf){
	unsigned eax, ebx, ecx, edx;
	eax = 0;

	__get_cpuid(0x00, &eax, &ebx, &ecx, &edx);

	char* string[] = {ebx, edx, ecx, 0};
	memcpy(buf, string, 12);
}
