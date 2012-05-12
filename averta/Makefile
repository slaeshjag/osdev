LDFLAGS = -b elf32-i386 --oformat=elf32-i386 -melf_i386

default:
	mkdir -p obj
	mkdir -p bin
	cd x86 && make
	cp -f x86/*.o obj
	cp -f x86/asm/*.o obj
	$(LD) -T link_x86.ld -o bin/kernel.bin obj/boilerplate.o obj/kernel_base.o $(LDFLAGS)

clean:
	cd x86 && make clean
	rm -Rf bin/
