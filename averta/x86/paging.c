#include "kernel_base.h"

void *paging_init() {
	PAGEDIRECTORY *paget = k_malloc();
	int i;

	for (i = 0; i < 1024; i++)
		paget->table[i] = 0;
	
	return paget;
}


PAGETABLE *paging_new_table() {
	PAGETABLE *table;
	int i;
	
	table = k_malloc();
	
	for (i = 0; i < 1024; i++)
		table->page[i] = 0;
	
	table += 0xF; /* Flags */
	return table;
}


PAGEDIRECTORY *paging_new_directory() {
	PAGEDIRECTORY *directory;
	int i;

	directory = k_malloc();

	for (i = 0; i < 1024; i++)
		directory->table[i] = NULL;
	return directory;
}


void paging_set_table(PAGEDIRECTORY *directory, void *phys, void *logic, int cache, int priv, int rw, int present) {
	int table, entry;
	unsigned int addr;
	PAGETABLE **table_p;

	addr = (unsigned int) logic;
	addr >>= 0xC;
	table = addr >> 0xA;
	entry = addr & 0x3FF;

	if (((unsigned int) directory->table[table] & 0x1) == 0)	/* Not present */
		directory->table[table] = paging_new_table();
	table_p = (void *) (directory->table[table]);
	table_p[entry] = phys;

	table_p[entry] += present;
	table_p[entry] += rw << 1;
	table_p[entry] += priv << 2;
	table_p[entry] += cache << 3;

	return;
}
