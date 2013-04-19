section .multiboot 
; setting up the Multiboot header - see GRUB docs for details
; somehow thos doesn't work with defines instead of equ - assume something goes wrong with the offset later
MODULEALIGN equ  1<<0                   ; align loaded modules on page boundaries
MEMINFO     equ  1<<1                   ; provide memory map
MAGIC       equ  0x1BADB002             ; 'magic number' lets bootloader find the header
FLAGS       equ  MODULEALIGN | MEMINFO  ; this is the Multiboot 'flag' field
CHECKSUM    equ -(MAGIC + FLAGS)        ; checksum required

align 4 ; these are 4 bytes in length for meeting multiboot requirements
    dd MAGIC
    dd FLAGS
    dd CHECKSUM
; more information
; http://www.gnu.org/software/grub/manual/multiboot/multiboot.pdf

section .text

global loader            ; making entry point visible to linker
;global magic             ; we wont use this in init. Uncomment if you want to
;global mbd               ; we wont use this in init. Same here.

extern init ; defined in init.c - yes, thats the kernel
STACKSIZE equ 0x2000 ; 8k stacksize - enought for starters
 
loader:
    mov  esp, stack
    ;mov  [magic], eax                   ; Multiboot magic number
    ;mov  [mbd], ebx                     ; Multiboot info structure
 
    call init ; call the c kernel :)

.hang:
	cli
    hlt
    jmp  .hang
    
%include "loader/include.inc"
 
section .bss
 
align 4
stackend: resb STACKSIZE ; reserve 8k stack on a doubleword boundary
stack:
magic: resd 1
mbd:   resd 1
