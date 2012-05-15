;memcpy ����
memcpy:

push ebp
mov ebp,esp
mov eax,[ebp+8]
mov ebx,[ebp+12]
mov ecx,[ebp+16]
cmp ecx,0
je   nothing_copy
loop_copy:
  mov byte dl ,[ebx]
	mov byte [eax],dl
	inc ebx
	inc eax
loop loop_copy
nothing_copy:
mov eax,[ebp+8]
pop ebp
ret
;memset function
memset:
push ebp
mov ebp,esp
pushad
mov edi,[ebp+8]
mov eax,[ebp+12]
mov ecx,[ebp+16]
cmp ecx,0
je  memset_size_zero
memset_loop:
mov byte [edi],al
inc edi
loop memset_loop
memset_size_zero:
mov eax,[ebp+8]
popad
push ebp
ret

; Init8259A ---------------------------------------------------------------------------------------------
Init8259A:
;set timer interval
mov al,0x36
mov dx,0x43
out dx,al
mov eax,11930
mov edx,0x40
out dx,al
mov al,ah
out dx,al

	mov	al, 011h
	out	020h, al	; ��8259, ICW1.

	out	0A0h, al	; ��8259, ICW1.

	mov	al, 020h	; IRQ0 ��Ӧ�ж����� 0x20
	out	021h, al	; ��8259, ICW2.

	mov	al, 028h	; IRQ8 ��Ӧ�ж����� 0x28
	out	0A1h, al	; ��8259, ICW2.

	mov	al, 004h	; IR2 ��Ӧ��8259
	out	021h, al	; ��8259, ICW3.

	mov	al, 002h	; ��Ӧ��8259�� IR2
	out	0A1h, al	; ��8259, ICW3.

	mov	al, 001h
	out	021h, al	; ��8259, ICW4.

	out	0A1h, al	; ��8259, ICW4.

;  mov	al, 11111110b	; ����������ʱ���ж�
;	out	021h, al	; ��8259, OCW1.
;
;	mov	al, 11111111b	; ���δ�8259�����ж�
;	out	0A1h, al	; ��8259, OCW1.

	ret
;Init8259A ---------------------------------------------------------------------------------------------

print_str:
push ebp
mov ebp,esp
pushad 
mov esi,[ebp+8]
mov ecx,[ebp+12]
mov edx,[ebp+16]
add edx,edx
mov ah,0x0c
loop_show:
		mov al,[esi]
		mov [gs:edx],ax
		add edx,2
		add esi,1
loop loop_show
popad
pop ebp
ret

clear:
mov ax,0600h
mov bh,07
mov cx,0
mov dx,184fh
int 10h
ret

print_str_stack:
push ebp
mov ebp,esp
pushad 
mov esi,[ebp+8]
mov ecx,[ebp+12]
mov edx,[ebp+16]
add edx,edx
mov ah,0x0c
stack_loop_show:
		mov al,[ss:esi]
		mov [gs:edx],ax
		add edx,2
		add esi,1
loop stack_loop_show
popad
pop ebp
ret

stack_clear:
mov ax,0600h
mov bh,07
mov cx,0
mov dx,184fh
int  10h
ret
