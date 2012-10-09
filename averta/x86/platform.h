#ifndef __PLATFORM_H__
#define	__PLATFORM_H__

typedef struct {
	GDT_DESCRIPTOR		gdt;
	PAGEDIRECTORY		*pagedirectory;
} PLATFORM;


#endif
