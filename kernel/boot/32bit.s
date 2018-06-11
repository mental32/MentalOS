/* x86 32-bit boot code */

.global start_32
.extern start_64

.section .text

start_32:
	mov $stack_top, %esp

	lgdt (gdt_descriptor)

	call start_64

.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

.section .data

gdt_start:
	.long 0x0
	.long 0x0

gdt_code:
	.word 0xffff
	.word 0x0
	.byte 0x0
	.byte 0x9A
	.byte 0xCF
	.byte 0x0

gdt_data:
	.word 0xffff
	.word 0x0
	.byte 0x0
	.byte 0x92
	.byte 0xCF
	.byte 0x0

gdt_end:

gdt_descriptor:
	.word gdt_end - gdt_start - 1
	.long gdt_start
