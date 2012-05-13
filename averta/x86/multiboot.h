#ifndef __MULTIBOOT_H__
#define	__MULTIBOOT_H__



typedef struct {
	void			*mod_start;
	void			*mod_end;
	const char		*mod_name;
	unsigned int		null;
} MBOOT_MODULE;


typedef struct {
	unsigned int		entry_len;
	unsigned int		base_addr_l	: 32;
	unsigned int		base_addr_h	: 32;
	unsigned int		length_l	: 32;
	unsigned int		length_h	: 32;
	unsigned int		type;
} MBOOT_MMAP;


typedef struct {
	unsigned int		version		: 16;
	unsigned int		cseg		: 16;
	void			*offset;
	unsigned int		cseg_16		: 16;
	unsigned int		dseg		: 16;
	unsigned int		flags		: 16;
	unsigned int		cseg_len	: 16;
	unsigned int		cseg_16_len	: 16;
	unsigned int		dseg_len	: 16;
} MBOOT_APM;


typedef struct {
	unsigned int		meminfo_basic	: 1;
	unsigned int		boot_device	: 1;
	unsigned int		cmdline		: 1;
	unsigned int		modules		: 1;
	unsigned int		sym_aout	: 1;
	unsigned int		sym_elf		: 1;
	unsigned int		meminfo_mmap	: 1;
	unsigned int		drive_info	: 1;
	unsigned int		bios_config	: 1;
	unsigned int		bootloader_name	: 1;
	unsigned int		apm_table	: 1;
} MBOOT_FLAGS;


typedef struct {
	MBOOT_FLAGS		flags;
	unsigned int		mem_upper;
	unsigned int		mem_lower;
	unsigned int		boot_device;
	const char		*cmdline;
	unsigned int		mods_count;
	MBOOT_MODULE		*mods_addr;
	unsigned int		symbols[4];
	unsigned int		mmap_len;
	MBOOT_MMAP		*mmap;
	unsigned int		drives_lenght;
	void			*drives;
	void			*bios_config_table;
	const char		*bootloader_name;
	MBOOT_APM		*apm_table;
} __attribute__((packed)) MBOOT_TABLE;


#endif
