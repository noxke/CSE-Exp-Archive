.model small
.stack
.data
    buffer db 80
    db 0
    db 80 dup(0)    ;将80个字节内存填充为0 
.code
.startup
    mov dx, seg buffer
    mov ds, dx
    mov dx, offset buffer
    mov ah, 0ah
    int 21h
.exit 0
end