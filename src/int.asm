%macro Enter 0
pushad
push es
push fs
push gs
%endmacro
%macro Leave 0
pop gs
pop fs
pop es
popad
iretd
%endmacro
error_code:
db 0x0
;#DE vector 0
asm_div_error:
Enter
call do_div_error
Leave
iret
;#DB vector 1
asm_debug:
Enter
call do_debug
Leave
iret
;no monster int vector 2
asm_mon:
iret

;BP breakpoint vector 3
asm_breakpoint:
Enter
call do_breakpoint
Leave
iret

;#OF overflow vector 4
asm_overflow:
Enter
call do_overflow
Leave
iret
;#BR overbound vector 5
asm_overbound:
Enter
call do_overbound
Leave
iret

;#UD undefine opcode vector 6
asm_undefine:
Enter
call do_undefine
Leave
iret
;#NM device no found vector 7
asm_nm:
Enter
call do_nm
Leave
iret
;#DF vector 8
asm_doublefault:
pop dword [error_code]
Enter
push dword [error_code]
call do_doublefault
pop dword [error_code]
Leave
iret
; coprocessor segment overflow vector 9
asm_cop:
Enter
call do_cop
Leave
iret

;#TS invalid tss vector 10
asm_tss:
pop dword [error_code]
Enter
push dword [error_code]
call do_tss
pop dword [error_code]
Leave
iret
;#NP segment no present vector 11
asm_seg_fault:
pop dword [error_code]
Enter
push dword [error_code]
call do_seg_fault
pop dword [error_code]
Leave
iret

;#SS  stack segment fault vector 12
asm_stack_fault:
pop dword [error_code]
Enter
push dword [error_code]
call do_stack_fault
pop dword [error_code]
Leave
iret

;#GP  general protect vector 13 
asm_general_protect:
pop dword [error_code]
Enter
push dword [error_code]
call do_general_protect
pop dword [error_code]
Leave
iret

;#PF page fault vector 14
asm_page_fault:
pop dword [error_code]
Enter
push dword [error_code]
call do_page_fault
pop dword [error_code]
Leave
iret

;#reserve vector 15
asm_reserve:
iret
;#MF x87 fpu error vector 16
asm_fpu_error:
Enter
call do_fpu_error
Leave
iret

;#AC align fault vector 17
asm_align_check:
pop dword [error_code]
Enter
push dword [error_code]
call do_align_check
pop dword [error_code]
Leave
iret

;#MC machine check  vector 18
asm_machine_check:
Enter
call do_machine_check
Leave
iret
asm_simd_fault:
Enter
call do_simd_fault
Leave
iret

;20~31 is reserved by intel

asm_general_handler:
iretd

;timer interrupt vector 32 0x20
asm_int_timer:
push dword ds
pushad
mov eax,0x10
mov ds,ax

mov al,0x20
out 0x20,al
call do_int_timer
popad
pop dword ds
iretd

asm_int_keyboard:
cli
pushad
call do_int_keyboard
popad
mov al,0x20
out 0x20,al
sti
iretd

asm_int_hd:
call do_int_hd
iretd

asm_sys_call:
push edx
push ecx
push ebx
push eax
call sys_call
pop eax
pop ebx
pop ecx
pop edx
iretd
