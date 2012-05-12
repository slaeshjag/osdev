#ifndef __GDT_H__
#define	__GDT_H__


#define			GDT_ACCESS_DUMMY	0x0
#define			GDT_ACCESS_CODE		0x9A
#define			GDT_ACCESS_DATA		0x92


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
} GDT_DESCRIPTOR;


#endif
