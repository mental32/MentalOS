GCCPARAMS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra 
LDPARAMS = -T kernel/boot/linker.ld -o myos.bin -ffreestanding -O2 -nostdlib

objects = kernel.o terminal.o boot.o utils.o memory.o cpuid.o

boot = kernel/boot/32bit.s kernel/boot/64bit.s kernel/boot/multiboot.s
libcc = ./libc/terminal.c \
		./libc/utils.c \
		./libc/memory.c \
		./libc/cpuid.c

kernel.o: kernel/kernel.c $(libcc)
	i686-elf-gcc -I ./libc/include/ -c $(libcc) kernel/kernel.c -$(GCCPARAMS)

boot.o: $(boot)
	i686-elf-as $(boot) -o boot.o

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

clean:
	rm *.o
