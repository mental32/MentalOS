/* x86 64-bit boot code */
.global start_64

.section .text

start_64:
	mov %ax, 0
	mov %ss, %ax
	mov %ds, %ax
	mov %es, %ax
	mov %fs, %ax
	mov %gs, %ax

	.extern kernel_entry
	call kernel_entry

	cli

1:	hlt
	jmp 1b
