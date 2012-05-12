#ifndef __KLOADER_PRINT_H__
#define	__KLOADER_PRINT_H__


typedef struct {
	int		x;
	int		y;
} KLOAD_PRINT;


KLOAD_PRINT kload_cls();
KLOAD_PRINT kload_init();
KLOAD_PRINT kload_print(KLOAD_PRINT print, char *str);
KLOAD_PRINT kload_print_hex(KLOAD_PRINT print, unsigned int val);


#endif
