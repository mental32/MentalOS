GCCPARAMS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra
LDPARAMS = -T kernel/linker.ld -o myos.bin -ffreestanding -O2 -nostdlib

objects = kernel.o terminal.o boot.o

libcc = ./libc/terminal.c
headers = ./libc/include/terminal.h

kernel.o: $(kernel/%.c) $(libcc) $(headers)
	i686-elf-gcc -c $(libcc) kernel/kernel.c -std=gnu99 -ffreestanding -O2 -Wall -Wextra

boot.o: kernel/boot.s
	i686-elf-as kernel/boot.s -o boot.o

bin: $(objects)
	i686-elf-gcc $(LDPARAMS)  $(objects) -lgcc
	rm *.o

iso: bin
	mkdir -p iso/boot/grub
	cp myos.bin iso/boot/myos.bin
	echo 'menuentry "myos" {'                 > iso/boot/grub/grub.cfg
	echo 'multiboot /boot/myos.bin'           >> iso/boot/grub/grub.cfg
	echo '}'                                  >> iso/boot/grub/grub.cfg
	grub-mkrescue -o myos.iso iso
	rm -rf iso/
	rm myos.bin

run: iso
	(killall VirtualBox && sleep 1) || true
	VirtualBox --startvm 'myos' &
