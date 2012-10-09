#include "kernel_base.h"
#include "gdt.h"

void GDTFillEntry(GDT_DESCRIPTOR *desc) {

	desc->offset = &desc->entry;
	desc->size = sizeof(GDT_ENTRY) * GDT_ENTRY_COUNT - 1;

	/* NULL ENTRY */
	desc->entry[0].limit_l = 0;
	desc->entry[0].base_l = 0;
	desc->entry[0].access = 0;
	desc->entry[0].limit_h = 0;
	desc->entry[0].flags = 0;
	desc->entry[0].base_h = 0;
	
	/* CODE (Ring 0) */
	desc->entry[1].limit_l = 0xFFFF;
	desc->entry[1].base_l = 0;
	desc->entry[1].access = GDT_ACCESS_CODE;
	desc->entry[1].limit_h = 0xF;
	desc->entry[1].flags = 0xC;
	desc->entry[1].base_h = 0;
	
	/* DATA (Ring 0) */
	desc->entry[2].limit_l = 0xFFFF;
	desc->entry[2].base_l = 0;
	desc->entry[2].access = GDT_ACCESS_DATA;
	desc->entry[2].limit_h = 0xF;
	desc->entry[2].flags = 0xC;
	desc->entry[2].base_h = 0;
	
	/* TSS (Not used yet) */
	desc->entry[3].limit_l = 0xFFFF;
	desc->entry[3].base_l = 0;
	desc->entry[3].access = GDT_ACCESS_CODE;
	desc->entry[3].limit_h = 0xF;
	desc->entry[3].flags = 0xC;
	desc->entry[3].base_h = 0;
	
	/* CODE (Ring 3) */
	desc->entry[4].limit_l = 0xFFFF;
	desc->entry[4].base_l = 0;
	desc->entry[4].access = GDT_ACCESS_CODE3;
	desc->entry[4].limit_h = 0xF;
	desc->entry[4].flags = 0xC;
	desc->entry[4].base_h = 0;
	
	/* DATA (Ring 3) */
	desc->entry[5].limit_l = 0xFFFF;
	desc->entry[5].base_l = 0;
	desc->entry[5].access = GDT_ACCESS_DATA3;
	desc->entry[5].limit_h = 0xF;
	desc->entry[5].flags = 0xC;
	desc->entry[5].base_h = 0;

	load_gdt(desc);

	return;
}
