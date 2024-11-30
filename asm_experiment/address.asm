.model small
.stack
.data
    x dw 1234h, 5678h
.code
.startup
    mov ax, seg x
    mov bx, offset x
    mov dx, x
    mov ax, 0002h
    mov si, ax
    mov dx, [si + x]
.exit 0
end
