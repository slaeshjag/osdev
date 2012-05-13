#ifndef __AVERTA_MM__H__
#define	__AVERTA_MM__H__


struct AVERTA_MEMTABLE_FREE {
	struct AVERTA_MEMTABLE_FREE	*back;
	#ifdef _32BIT_MEMADDR
	void				*ptr[1022];
	#else 	/* Assume 64-bit target */
	void				*ptr[510];
	#endif
	struct AVERTA_MEMTABLE_FREE	*next;
};


typedef struct {
	struct AVERTA_MEMTABLE_FREE	*table;
	struct AVERTA_MEMTABLE_FREE	*last_entry;
	unsigned int			pages_free;
} AVERTA_MEM_FREE;

void k_free(void *ptr);


#endif
