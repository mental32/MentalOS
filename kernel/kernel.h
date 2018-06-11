#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifndef _KERNEL_H
#define _KERNEL_H

/* Check if the compiler thinks we are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 
/* This os will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This os needs to be compiled with a ix86-elf compiler"
#endif

#endif
