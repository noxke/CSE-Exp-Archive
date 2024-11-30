.model small
.stack
.data
    source db 41h, 42h, 43h, 44h
    target db 80 dup(?)
.code
.startup
    mov si, offset source
    mov di, offset target
    mov cx, 80
again1:
    mov al, [si]
    mov [di], al
    inc si
    inc di
    loop again1
    mov di, 00h
again2:
    mov dl, target[di]
    mov ah, 02h
    int 21h
    inc di
    cmp di, 80
    jb again2
.exit 0
end