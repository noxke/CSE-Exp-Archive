.model small
.stack
.data
string db 'Hello world', 0dh, '$'
.code
.startup
mov dx, offset string
mov ah, 09h
int 21h
.exit 0
end