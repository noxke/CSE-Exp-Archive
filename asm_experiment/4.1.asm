.model small
.stack
.data
.code
.startup
    call input      ; 调用input子程序获取十进制输入的n，出口参数保存在dx寄存器中
    mov ax, dx      ; 将入口参数n传入寄存器ax
    call feibo1
    mov dx, ax      ; 从ax中取出计算结果
    call display    ; 十进制输出，入口参数在dx中
.exit 0
feibo1 proc         ; 入口参数n使用ax寄存器传递，出口参数result使用寄存器ax传递 
    push bp
    mov bp, sp
    push bx
    push dx
    cmp ax, 2
    jg	r			;n>2时递归计算
	mov ax, 1
    jmp endf		;n<=2时返回1
r:    
    mov bx, ax
    sub ax, 1
    call feibo1		;feibo1(n-1)，入口、出口参数在ax中
    mov dx, ax
    mov ax, bx
    sub ax, 2
    call feibo1		;feibo1(n-2)，入口、出口参数在ax中
    add ax, dx		;feibo1(n-1) + feibo1(n-2)
endf:
	pop dx
    pop bx
    pop bp
	ret
feibo1 endp

input proc          ; 十进制输入，出口参数在dx中
    mov dx, 0
ag:
    mov ah, 01h     ; 调用dos功能输入字符
    int 21h
    cmp al, 30h     ; 输入字符不为数字，结束输入
    jl endi
    cmp al, 39h     ; 输入字符不为数字，结束输入
    jg endi
    sub al, 30h     ; 将ACSCII转化为十进制
    xchg al, dl
    mov bl, 10
    imul bl
    add dl, al
    jmp ag
endi:
    mov bx, dx
    mov ah, 02h
    mov dl, 0dh     ; 换行
    int 21h
    mov dx, bx
    ret
input endp

display proc        ; 十进制输出，入口参数在dx中
    mov ax, dx
    mov cx, 0
again:
    cmp ax, 0
    jz enddisp
    mov dx, 0
    mov bx, 10
    idiv bx ; 对10取余，逐位储存在堆栈中
    push dx ; 将余数压入堆栈，使其逆置
    inc cx
    jmp again
enddisp:
l:
    mov ah, 02h
    pop dx  ; 逐次取出余数
    add dl, 30h ; 转换为ASCII码
    int 21h
    loop l
    ret
display endp
end