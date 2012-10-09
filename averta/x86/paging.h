#ifndef __PAGING_H__
#define	__PAGING_H__


typedef struct {
	void			*page[1024];
} PAGETABLE;

typedef struct {
	PAGETABLE		*table[1024];
} PAGEDIRECTORY;


extern void page_directory_set(PAGEDIRECTORY *directory);
PAGEDIRECTORY *paging_new_directory();
void paging_set_table(PAGEDIRECTORY *directory, void *phys, void *logic, int cache, int priv, int rw, int present);


#endif
