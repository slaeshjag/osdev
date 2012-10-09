#include "kernel_base.h"


int  k_mem_occupied(MBOOT_TABLE *mboot, unsigned int addr) {
	extern void end;
	unsigned int i;

	if (addr < (unsigned int) &end)
		return 1;
	for (i = 0; i < mboot->mods_count; i++)
		if (addr >= (unsigned int) mboot->mods_addr[i].mod_start &&
			addr < (unsigned int) mboot->mods_addr[i].mod_end)
				return 1;
	if (addr + 0x1000 > (unsigned int) mboot->mmap && addr < (unsigned int) mboot->mmap + mboot->mmap_len)
		return 1;
	return 0;
}


KLOAD_PRINT k_mmap_print(KLOAD_PRINT print, MBOOT_TABLE *mboot) {
	int i, sz;

	print = kload_print(print, "****************************************\n");
	print = kload_print(print, "* START      * LENGTH     * TYPE       *\n");

	sz = mboot->mmap_len / sizeof(MBOOT_MMAP);
	for (i = 0; i < sz; i++) {
		print = kload_print(print, "* ");
		print = kload_print_hex(print, mboot->mmap[i].base_addr_l);
		print = kload_print(print, " * ");
		print = kload_print_hex(print, mboot->mmap[i].length_l);
		print = kload_print(print, " * ");
		print = kload_print_hex(print, mboot->mmap[i].type);
		print = kload_print(print, " *\n");
	}

	print = kload_print(print, "****************************************\n");
	return print;
}		


void k_init_memory(MBOOT_TABLE *mboot) {
	extern AVERTA_KERNEL_RC k_rc;
	unsigned int h, i, j, sz, pages;

	k_rc.mem_free.table = NULL;
	k_rc.mem_free.last_entry = NULL;
	k_rc.mem_free.pages_free = 0;
	k_rc.mem_free.page_size = 4096;
	sz = mboot->mmap_len / sizeof(MBOOT_MMAP);

	for (h = 0; h < 2; h++, pages = 0) {
		for (i = 0; i < sz; i++) {
			if (mboot->mmap[i].type != 1)			/* Not usable RAM */
				continue;
			if (mboot->mmap[i].base_addr_h > 0)		/* 32-bit addressing <.< */
				continue;
			if (mboot->mmap[i].base_addr_l & 0xFFF)	{	/* Needs to be page-aligned */
				mboot->mmap[i].length_l += (mboot->mmap[i].base_addr_l & 0xFFF);
				mboot->mmap[i].length_l -= 0x1000;
				mboot->mmap[i].base_addr_l -= (mboot->mmap[i].base_addr_l & 0xFFF);
				mboot->mmap[i].base_addr_l += 0x1000;
			}

			if (!h) {
				pages += mboot->mmap[i].length_l >> 12;
				continue;
			} else
				pages = mboot->mmap[i].length_l >> 12;
			for (j = 0; j < pages; j++) {
				if (k_mem_occupied(mboot, mboot->mmap[i].base_addr_l + (j<<12)))
					continue;
				k_free((void *) mboot->mmap[i].base_addr_l + j*0x1000);
			}
		}
		
		kinit_mtable(pages);

	}

	return;
}


int k_system_check(MBOOT_TABLE *mboot, unsigned int magic) {
	if (magic != 0x2BADB002)
		return -1;
	if (mboot->flags.cmdline == 0)
		return -1;
	if (mboot->flags.meminfo_mmap == 0)
		return -1;
	
	return 0;
}


void k_init_platform(PLATFORM *platform) {
	int i;
	void *ptr = NULL;

	platform->pagedirectory = paging_new_directory();

	for (i = 0; i < 8192; i++)
		paging_set_table(platform->pagedirectory, ptr, ptr, 0, 0, 1, 1);
		

	GDTFillEntry(&platform->gdt);

	return;
}


void k_entry(void *mboot_d, unsigned int magic) {
	KLOAD_PRINT print;
	MBOOT_TABLE *mboot_t = mboot_d;
	extern AVERTA_KERNEL_RC k_rc;
	unsigned int *mboot_data = mboot_d;

	print = kload_init();
	print = kload_print(print, "Oilpot v.0.1 - (C)opyleft Steven Arnow 2012\n");

	if (k_system_check(mboot_d, magic) < 0) {
		print = kload_print(print, "==== KERNEL PANIC ====\nSystem or bootloader not supported!");
		return;
	}

	k_init_memory(mboot_d);
	/* Platform check needs to be done I think */
	k_rc.platform = k_malloc();
	k_init_platform(k_rc.platform);

	print = k_mmap_print(print, mboot_d);
	print = kload_print(print, "\nAmount of usable pages detected: ");
	print = kload_print_hex(print, k_rc.mem_free.pages_free);
	print = kload_print(print, "\nCMD-line: ");
	print = kload_print(print, mboot_t->cmdline);
	print = kload_print(print, "\nPlatform struct address: ");
	print = kload_print_hex(print, (unsigned int) k_rc.platform);

	return;
}
