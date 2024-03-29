global entry
global __end
global k_rc
extern k_entry

MODULEALIGN 	equ	1<<0
MEMINFO		equ	1<<1
FLAGS		equ	MODULEALIGN | MEMINFO
MAGIC		equ	0x1BADB002
CHECKSUM	equ	-(MAGIC + FLAGS)

STACKSIZE	equ	0x4000
extern end

section .text

align 4
	dd MAGIC
	dd FLAGS
	dd CHECKSUM

	__end:
	dd end

entry:
	mov esp, stack + STACKSIZE
	push eax
	push ebx

	call k_entry

	cli
	hlt
	jmp $

section .bss

align 4
stack:
	resb STACKSIZE
k_rc:
	resb 4096
