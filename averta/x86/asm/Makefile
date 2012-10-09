default:
	nasm -f elf -o boilerplate.o boilerplate.s
	nasm -f elf -o loadgdt.o loadgdt.s
	nasm -f elf -o paging_s.o paging.s

clean:
	rm -f *.o
