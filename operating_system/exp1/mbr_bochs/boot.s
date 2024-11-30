section .text
	global _start
_start:
	org 0x7C00
	mov ax, boot_msg
	mov bx, 0x0009
	call print_str
	call print_endl
	mov ax, mem_size_msg
	mov bx, 0x0002
	call print_str
	call get_mem_size
	call print_hex
boot_end:
	jmp boot_end

get_mem_size:
	mov ah, 0x88	; get extended memory (kb)
	int 0x15
	add ax, 0x400	; 1M basic memory
	ret

print_str:
	; print string at ax
	push ax
	mov si, ax
print_str_loop:
	mov al, byte [si]
	test al, al
	jz print_str_end
	inc si
	jmp print_str_loop
print_str_end
	mov ah, 0x03	; cursor position
	int 0x10
	pop ax
	mov bp, ax	; str
	mov cx, si
	sub cx, ax	; str length
	mov ax, 0x1301
	int 0x10
	ret
print_endl:
	; CR LR
	mov ax, 0x0E0D
	int 0x10
	mov al, 0x0A
	int 0x10
	ret

print_hex:
	; print hex number in ax
	mov bx, ax
	mov ax, 0x0E30
	int 0x10
	mov al, 0x78
	int 0x10
	mov cx, 4
print_hex_loop:
	mov al, bh
	shr al, 4
	and al, 0x0F
	add al, 0x37
	cmp al, 0x41	; >= A
	jg hex_a
	sub al, 7	; < A
hex_a:
	int 0x10
	shl bx, 4
	loop print_hex_loop
	mov al, 0x6b
	int 0x10
	mov al, 0x62
	int 0x10
	call print_endl
	ret
	
boot_msg:	db "Hello Noxke!", 0
mem_size_msg:	db "Memory Size:", 0
times	510-($-$$)	db 0
dw	0xAA55	; boot singature

