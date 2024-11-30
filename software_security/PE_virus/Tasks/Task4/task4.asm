;UID:U202100000:
;Flag:b72393:
;Name:noxke
;Date:2023年12月22日
;FileName:task4.asm
;Other comments：

.586	; ***  ***
;重定位实验
.model flat, stdcall
option casemap :none   ; case sensitive
include c:\masm32\include\windows.inc 
include c:\masm32\include\comctl32.inc 
includelib c:\masm32\lib\comctl32.lib 
include c:\masm32\include\kernel32.inc 
includelib c:\masm32\lib\kernel32.lib 
include c:\masm32\include\user32.inc 
includelib c:\masm32\lib\user32.lib 

.code
VCode:
    szMsg   db	"UID：U202100000，delta value：",0   ;真实地址与预期地址的差值   delta
    val db  "abcdefgh",0
; -----Store Eax into val-----------
binToAscii proc near	; change al into Ascii
    push eax
    and eax,0fh
    add al,30h
    cmp al,39h
    jbe @f
    add al,7
@@:
    stosb   ;save ax into [edi]
    pop eax
    ret
binToAscii endp

saveEax proc near   ;save eax to val in Ascii mode
    mov ecx,8
    cld
    lea edi,val
L1:	
    rol eax,4
    call binToAscii
    loop L1
    ret
saveEax endp
;----------------------------------

Relocate	proc             ;------Return value: ebx, ebx= VA_of_delta - Offset_delta-------
;**** Your Code Begin ****
    call @f
@@:
    pop ebx
    sub ebx,offset @B
;**** Your Code End	  ****
    ret
Relocate	endp


_start:
    ;invoke	InitCommonControls
VCodeStart:
    call	Relocate
    mov 	eax,ebx
    call 	saveEax
	
    invoke MessageBox, NULL, addr val, addr szMsg, MB_OK	
    invoke ExitProcess, NULL 
VCodeEnd:

end	_start