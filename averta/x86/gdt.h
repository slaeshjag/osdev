#ifndef __GDT_H__
#define	__GDT_H__


#define			GDT_ACCESS_DUMMY	0x0
#define			GDT_ACCESS_CODE		0x9A
#define			GDT_ACCESS_DATA		0x92
#define			GDT_ACCESS_CODE3	0xFA
#define			GDT_ACCESS_DATA3	0xF2

#define			GDT_ENTRY_COUNT		6

#define			GDT_TYPE_CODE0		1
#define			GDT_TYPE_DATA0		2
#define			GDT_TYPE_TSS		3
#define			GDT_TYPE_CODE3		4
#define			GDT_TYPE_DATA3		5

extern void load_gdt(void *gdt_descriptor);

typedef struct {
	unsigned int		limit_l	:	16;
	unsigned int		base_l	:	24;
	unsigned int		access	:	8;
	unsigned int		limit_h	:	4;
	unsigned int		flags	:	4;
	unsigned int		base_h	:	8;
} __attribute__((packed)) GDT_ENTRY;


typedef struct {
	unsigned int		size	:	16;
	void			*offset;
	GDT_ENTRY		entry[GDT_ENTRY_COUNT];
} __attribute__((packed)) GDT_DESCRIPTOR;


void GDTFillEntry(GDT_DESCRIPTOR *desc);

#endif
