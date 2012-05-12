void k_entry(void *mboot_d, unsigned int magic) {
	char *vram = (void *) 0xB8000;

	vram[0] = 'X';
	vram[1] = 0x07;

	return;
}
