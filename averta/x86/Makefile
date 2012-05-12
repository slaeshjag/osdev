CFLAGS += -Wall -Wextra -nostdlib -fno-builtin -nostartfiles -nodefaultlibs -m32


default:
	cd asm && make
	$(CC) $(CFLAGS) -c kernel_base.c -o kernel_base.o

clean:
	cd asm && make clean
	rm -f *.o
