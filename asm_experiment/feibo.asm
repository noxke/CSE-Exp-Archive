.model small
.stack
.data
.code
.startup
    mov ax, 3
    push ax
    call feibo1
    pop ax
.exit 0
feibo1 proc
    push bp
    mov bp, sp
    push ax
    push bx
    push dx
    mov ax, [bp+4]	;从栈中取出n
    cmp ax, 2
    jg	r			;n>2时递归计算
	mov ax, 1
    jmp endf		;n<=2时返回1
r:    
    mov bx, ax
    sub ax, 1
    push ax			;向栈中压入n-1
    call feibo1		;feibo1(n-1)
    pop ax			;从栈中取出n-1的结果
    mov dx, ax
    mov ax, bx
    sub ax, 2
    push ax			;向栈中压入n-2
    call feibo1		;feibo1(n-2)
    pop ax			;从栈中取出n-2的结果
    add ax, dx		;feibo1(n-1) + feibo1(n-2)
endf:
	mov [bp+4], ax	;将计算结果放入栈中返回
	pop dx
    pop bx
    pop ax
    pop bp
	ret
feibo1 endp
end