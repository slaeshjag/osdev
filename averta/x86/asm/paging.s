section text

;global page_directory_set

page_directory_set:
	mov cr3, eax

	mov eax, cr0
	or eax, 0x80000000
	mov cr0, eax

	ret

