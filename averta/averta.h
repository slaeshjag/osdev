#ifndef __AVERTA_H__
#define	__AVERTA_H__

#define	_32BIT_MEMADDR
#define	NULL			(void *) 0x0

#include "averta_mm.h"


typedef struct {
	AVERTA_MEM_FREE		mem_free;
	void			*platform;
} AVERTA_KERNEL_RC;


extern AVERTA_KERNEL_RC k_rc;

#endif
