/* x86 32-bit boot code */

.global start_32
.extern start_64

.section .text

start_32:
	mov $stack_top, %esp

	call start_64

	/*
	Place the system into an infinite loop.
	1) Disable interrupts with cli
	2) Wait for next interrupt to arrive with hlt
	3) Jump to hlt if it ever wakes due to a non-maskable interrupt occuring or due to system managment mode.
	*/
	cli
1:	hlt
	jmp 1b

.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:
