#include "kernel_base.h"



void k_entry(void *mboot_d, unsigned int magic) {
	KLOAD_PRINT print;

	print = kload_init();
	print = kload_print(print, "Hello, world!\n...");
	print = kload_print_hex(print, magic);
	print = kload_print(print, ",, ");
	print = kload_print_hex(print, (unsigned int) mboot_d);

	return;
}
