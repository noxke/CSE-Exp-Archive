.model small
.stack
.data
string db 'abc ABC'
slength equ $-string
cmpstr db 'abc'
cmpslength equ $-cmpstr
.code
.startup
    mov ax, offset string
	mov si, 0
  	mov cx, slength
upper_again1:	;将字符串string大写
	mov al, string[si]
    cmp al, 61h
  	js upper1	;将小写字母替换为大写
    sub al, 20h
upper1:
    mov string[si], al
    inc si
	loop upper_again1
    
    mov si, 0
  	mov cx, cmpslength
upper_again2:	;将字符串cmpstr大写
	mov al, cmpstr[si]
    cmp al, 61h
  	js upper2	;将小写字母替换为大写
    sub al, 20h
upper2:
    mov cmpstr[si], al
    inc si
	loop upper_again2
   
   
   mov si, 0	;指针指向string
   mov di, 0	;指针指向cmpstr
   mov ax, 0	;记录次数
   mov cx, slength
loop_again:	;遍历字符串
    mov dx, si
loop_again1:
	mov bl, string[si]
    cmp bl, cmpstr[di]
    jnz	nequ	;字符不相同
    inc di
    inc si
    ; cmp si, slength	;string是否达到末尾
    ; jns nequ
    cmp di, cmpslength	;cmpstr是否到达末尾
    js loop_again1
    inc ax	;次数增加1
nequ:
    mov si, dx
    mov di, 0
	inc si
	loop loop_again
.exit 0
end