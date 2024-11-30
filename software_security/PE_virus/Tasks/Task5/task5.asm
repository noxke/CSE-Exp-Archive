;UID:U202100000:
;Flag:cf7e1c:
;Name:noxke
;Date:2023年12月22日
;FileName:task5.asm
;Other comments

.586
.model flat,stdcall
option casemap:none

include c:\masm32\include\windows.inc 
include c:\masm32\include\comctl32.inc 
includelib c:\masm32\lib\comctl32.lib 
include c:\masm32\include\kernel32.inc 
includelib c:\masm32\lib\kernel32.lib 
include c:\masm32\include\user32.inc 
includelib c:\masm32\lib\user32.lib 

GetApiA proto:DWORD,:DWORD			;函数原型

.code
VCode:
    szMsg   db  "UID:U202100000",0   ;改为你自己的学号 Your UID
    k32Str  db  "kernel32.dll base: 0x"
    val     db  "abcdefgh",0        ;address of functions in Ascii
;--------------------------------------------------------------------------------------------------
;code start
;--------------------------------------------------------------------------------------------------
;------proc to save eax into Ascii value 'val' for messagebox-----------
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
    push ecx
    push edi
    push eax

    mov ecx,8
    cld
    lea edi,val
L1:	
    rol eax,4
    call binToAscii
    loop L1

    pop eax
    pop edi
    pop ecx
    ret
saveEax endp
;-------------------------------------------------------------------

_Start0:
    ;invoke InitCommonControls
    jmp _Start



appBase dd ?
k32Base dd ?

_Start:
    call _delta                         ;-----重定位-------
_delta:
    pop ebp
    sub ebp,offset _delta
    mov dword ptr[ebp+appBase],ebp

; ******* Your code 1 begin task5******
;-----获取Kerenel32.dll模块地址
    mov eax,[esp]    ;from stack
    and eax, 0ffff0000h
    add eax, 10000h
    xor edx,edx
getK32Base:
    sub eax, 10000h
    mov edx,dword ptr[eax+IMAGE_DOS_HEADER.e_lfanew]    ;3ch
    cmp edx,0f8h                                ;check f8
    jnz getK32Base
    cmp eax,dword ptr[eax+edx+IMAGE_NT_HEADERS.OptionalHeader.ImageBase] ;double check ImageBase value with eax
    jnz getK32Base
    mov [ebp+k32Base],eax                ;save ImageBase into k32Base
;-----save ImageBase into k32Base
; *******   Your code 1 end ******

    call 	saveEax						;Save Eax into val
    invoke MessageBox, NULL, addr k32Str, addr szMsg, MB_OK	;MessageBox for two api ,here just use user32.dll 
    End_Get:
_Exit:
    ;push 0
    invoke ExitProcess, NULL 
    end _Start0
