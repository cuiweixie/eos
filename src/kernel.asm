%include "sym_asm_c.inc"
%macro Descriptor 3
	dw	%2 & 0FFFFh				; 段界限1
	dw	%1 & 0FFFFh				; 段基址1
	db	(%1 >> 16) & 0FFh			; 段基址2
	dw	((%2 >> 8) & 0F00h) | (%3 & 0F0FFh)	; 属性1 + 段界限2 + 属性2
	db	(%1 >> 24) & 0FFh			; 段基址3
%endmacro
; Multiboot header constant definition
MULTIBOOT_PAGE_ALIGN   equ 1<<0
MULTIBOOT_MEMORY_INFO  equ 1<<1
MULTIBOOT_HEADER_MAGIC equ 0x1BADB002
MULTIBOOT_HEADER_FLAGS equ MULTIBOOT_PAGE_ALIGN | MULTIBOOT_MEMORY_INFO
CHECKSUM equ -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)
global _start
[section .text]
[bits 32]
align 32
multiboot_header:
    dd MULTIBOOT_HEADER_MAGIC
    dd MULTIBOOT_HEADER_FLAGS
    dd CHECKSUM
_start:
call kernel_main
mov eax,0x18
mov gs,ax

;set task0's environment 
mov ax,0x20
lldt ax
mov ax,0x28
ltr ax

mov ax,0x10
mov ds,ax
mov es,ax
mov ss,ax
mov ax,0x18
mov gs,ax
mov eax,kernel_stack
mov esp,eax

pushfd
and dword [esp],0xffffbfff
popfd

push dword 0x17
push dword task0_user_stack
pushfd 
push dword 0xf
push dword Task0
iretd

;interrupt descriptor table 
align 64
idt:
times 256 dq 0x00008e0000080000
idt_len equ $-idt
idt_ptr dw idt_len
        dd idt

; global descriptor table is here
align 64
gdt:
      dq 0x0000000000000000
      dq 0x00c09a000000ffff
      dq 0x00c092000000ffff
      dq 0x00c0f20b8000ffff
ldt0_seg:
      Descriptor 0,0xffff,0x00e2
tss0_seg:
      Descriptor 0,103,0x00e9
ldt1_seg:
      Descriptor 0,0xffff,0x00e2
tss1_seg:
      Descriptor 0,103,0x00e9
times 250 dq 0x0
gdt_len equ $-gdt
gdt_ptr dw gdt_len-1
        dd gdt

;init stack
times 1024 dd 0
task0_user_stack:
times 1024 dd 0
kernel_stack:
align 64
ldt0:
dq 0x0000000000000000
dq 0x00c0fa00000003ff
dq 0x00c0f200000003ff
tss0:
dd 0
dd task0_kernel_stack,0x10
dd 0,0,0,0,0x1fe0000
dd 0,0,0,0,0
dd 0,0,0,0,0
;dd 0,0,0,0,0,0
dd 0x17,0x0f,0x17,0x17,0x17,0x18
dd 0x20,0x8000000
stack_0:
times 128 dd 0
task0_kernel_stack:

align 64
ldt1:
dq 0x0000000000000000
dq 0x00c0fa00000003ff
dq 0x00c0f200000003ff
tss1:
dd 0
dd task1_kernel_stack,0x10
dd 0,0,0,0,0x1fe0000
dd Task1,0x200
dd 0,0,0,0
dd task1_user_stack,0,0,0
dd 0x17,0x0f,0x17,0x17,0x17,0x18
dd 0x30,0x8000000
stack_1:
times 128 dd 0
task1_kernel_stack:
times 128 dd 0
task1_user_stack:

align 32
current: dd 0
scr_loc: dd 0

enable_tss:
mov edi, [gdt_ptr+2]
lea edi, [edi+eax+5]
and byte [edi],0xfd
ret
%include  "lib.inc"
%include "int.asm"
