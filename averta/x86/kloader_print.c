#include "kernel_base.h"


#define			KLOAD_PRINT_TTY_W		80
#define			KLOAD_PRINT_TTY_H		25


KLOAD_PRINT kload_cls() {
	int i, j;
	short *vram = (void *) 0xB8000;
	KLOAD_PRINT print;

	print.x = print.y = 0;
	
	for (i = 0; i < KLOAD_PRINT_TTY_H; i++)
		for (j = 0; j < KLOAD_PRINT_TTY_W; j++)
			vram[i*KLOAD_PRINT_TTY_W + j] = 0x0;

	return print;
}


KLOAD_PRINT kload_init() {
	return kload_cls();	
}


void kload_textbuffer_scroll() {
	short *vram = (void *) 0xB8000;
	int i, j;

	for (i = 1; i < KLOAD_PRINT_TTY_H; i++)
		for (j = 0; j < KLOAD_PRINT_TTY_W; j++)
			vram[(i-1)*KLOAD_PRINT_TTY_W + j] = vram[i*KLOAD_PRINT_TTY_W + j];
	
	i--;
	for (j = 0; j < KLOAD_PRINT_TTY_W; j++)
		vram[i*KLOAD_PRINT_TTY_W + j] = 0x0;
	
	return;
}


KLOAD_PRINT kload_print_chr(KLOAD_PRINT print, char c) {
	char *vram = (void *) 0xB8000;

	switch (c) {
		case '\n':
			print.x = 0;
			print.y++;
			if (print.y >= KLOAD_PRINT_TTY_H) {
				kload_textbuffer_scroll();
				print.y--;
			}
			break;
		default:
			vram[print.x*2 + print.y * KLOAD_PRINT_TTY_W*2] = c;
			vram[print.x*2 + print.y * KLOAD_PRINT_TTY_W*2 + 1] = 0x07;
			print.x++;
			if (print.x >= KLOAD_PRINT_TTY_W) {
				print.y++;
				print.x = 0;
			}

			if (print.y >= KLOAD_PRINT_TTY_H) {
				kload_textbuffer_scroll();
				print.y--;
			}
			break;
	}

	return print;
}



KLOAD_PRINT kload_print(KLOAD_PRINT print, char *str) {
	int i;

	for (i = 0; str[i] != 0; i++)
		print = kload_print_chr(print, str[i]);
	
	return print;
}


KLOAD_PRINT kload_print_hex(KLOAD_PRINT print, unsigned int val) {
	char c;
	int i;

	print = kload_print(print, "0x");

	for (i = 7; i >= 0; i--) {
		c = (val >> i*4) & 0xF;
		if (c < 10)
			c += 0x30;
		else
			c += 0x37;
		print = kload_print_chr(print, c);
	}

	return print;
}
