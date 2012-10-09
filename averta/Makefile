LDFLAGS = -b elf32-i386 --oformat=elf32-i386 -melf_i386
OBJ = obj/boilerplate.o obj/loadgdt.o obj/kernel_base.o obj/kloader_print.o obj/paging.o obj/paging_s.o obj/averta_mm.o obj/gdt.o
CFLAGS += -Wall -Wextra -nostdlib -fno-builtin -nostartfiles -nodefaultlibs -m32 -g

default:
	mkdir -p obj
	mkdir -p bin
	cd x86 && make
	cp -f x86/*.o obj
	cp -f x86/asm/*.o obj
	$(CC) $(CFLAGS) -c averta_mm.c -o obj/averta_mm.o
	$(LD) -T link_x86.ld -o bin/kernel.bin $(OBJ)  $(LDFLAGS)

clean:
	cd x86 && make clean
	rm -Rf bin/
	rm -Rf obj/
