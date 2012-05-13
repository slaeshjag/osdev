#include "averta.h"


void kinit_mtable(struct AVERTA_MEMTABLE_FREE *table) {
	int i;

	#ifdef _32BIT_MEMADDR
	for (i = 0; i < 1022; i++)
	#else
	for (i = 0; i < 510; i++)
	#endif
		table->ptr[i] = NULL;
	table->back = NULL;
	table->next = NULL;

	return;
}


void k_free(void *ptr) {
	extern AVERTA_KERNEL_RC k_rc;
	struct AVERTA_MEMTABLE_FREE *table = ptr;
	int i;

	if (k_rc.mem_free.table == NULL) {
		k_rc.mem_free.table = ptr;
		k_rc.mem_free.last_entry = ptr;
		kinit_mtable(ptr);
	} else {
		#ifdef _32BIT_MEMADDR
		for (i = 0; i < 1022; i++)
		#else
		for (i = 0; i < 510; i++)
		#endif
			if (k_rc.mem_free.last_entry->ptr[i] != NULL)
				break;
		#ifdef _32BIT_MEMADDR
		if (i == 1022) {
		#else
		if (i == 510) {
		#endif
			kinit_mtable(ptr);
			table->back = k_rc.mem_free.last_entry;
			k_rc.mem_free.last_entry = ptr;
		} else
			k_rc.mem_free.table->ptr[i] = ptr;
	}

	k_rc.mem_free.pages_free++;

	return;
}
