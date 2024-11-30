;UID:U202100000:
;Flag:1fccdd:
;Name:noxke:
;Date:2023年12月22日  
;FileName:task6.asm
;Other comments： 

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
    fName   db  "                                "
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
    invoke InitCommonControls
    jmp _Start

K32_api_ordinal_retrieve proc Base:DWORD,sApi:DWORD   ;****从kernel32.dll中查找函数序号****
; ****** Your code 3 begin task6-2******
    ;保存现场
    push ebx
    push ecx
    push edx
    push esi
    push edi
    ;取参数到寄存器中	
    ;edi=AddressOfNames
    ;ecx=NumberOfNames
    ;edx=AddressOfNameOrdinals
    add edx, dword ptr [Base]
    push edx
    push ecx
    mov edi, esi
    add edi, dword ptr [Base]
    push edi
    ;esi=sApi
    mov esi, dword ptr [sApi]
    xor eax, eax
    xor ebx, ebx
    xor edx, edx
loop1:
    mov edi, dword ptr [esp]
    mov edi, dword ptr [edi+eax*4]
    add edi, dword ptr [Base]
    xor ecx, ecx
loop2:
    mov bl, byte ptr [esi+ecx]
    mov dl, byte ptr [edi+ecx]
    inc ecx
    cmp bl, dl
    jne loop2_end
    test bl, bl
    jz loop1_end
    jmp loop2
loop2_end:
    inc eax
    cmp eax, dword ptr [esp+4]
    jl loop1
    invoke ExitProcess, NULL  ;未找到 发生错误
loop1_end:
    pop edi
    pop ecx
    pop edx
    ;准备循环条件
    ;根据名字，找出序数,存入eax
    mov eax, dword ptr [edx+eax*2]
    and eax, 0ffffh
    pop edi
    pop esi
    pop edx
    pop ecx
    pop ebx
; ****** Your code 3 end ******
    ret
K32_api_ordinal_retrieve endp

GetApiA proc Base:DWORD,sApi:DWORD   ;已知DLL Base 及API函数名，查找该DLL的多个API地址*****
    local ADDRofFun:DWORD
    ;******  Your code 2 begin task6-1******
    ;保存现场
    push ebx
    push ecx
    push edx
    push esi
    push edi
    ;指针指向DLL基址
    mov ebx, dword ptr [Base]
    ;利用PE文件偏移，找到可选文件头的导出函数表地址
    mov eax, dword ptr [ebx+IMAGE_DOS_HEADER.e_lfanew]  ;PE头
    add eax, IMAGE_NT_HEADERS.OptionalHeader    ;OptionalHeader头
    add eax, IMAGE_OPTIONAL_HEADER32.DataDirectory
    mov eax, dword ptr [ebx+eax]    ;导出表va
    add ebx, eax

    ;ecx=NumberOfNames
    mov ecx, dword ptr [ebx+IMAGE_EXPORT_DIRECTORY.NumberOfNames]
    ;edx=AddressOfNameOrdinals
    mov edx, dword ptr [ebx+IMAGE_EXPORT_DIRECTORY.AddressOfNameOrdinals]
    ;esi=AddressOfNames
    mov esi, dword ptr [ebx+IMAGE_EXPORT_DIRECTORY.AddressOfNames]
    
    invoke K32_api_ordinal_retrieve,Base,sApi	;获得sApi的序号ordinal，存入eax
    ;根据序号获得Api rva地址
    ;edx=AddressOfFunctions
    ;找到导出函数地址的首部AddressOfFunctions
    mov edx, dword ptr [ebx+IMAGE_EXPORT_DIRECTORY.AddressOfFunctions]
    add edx, dword ptr [Base]
    mov eax, dword ptr [edx+eax*4]
    ;+ImageBase后获得api VA地址
    add eax, dword ptr [Base]
    ;eax返回api地址
    ;恢复现场
    pop edi
    pop esi
    pop edx
    pop ecx
    pop ebx
    ; ****** Your code 2 end ******
    ret
GetApiA endp

appBase dd ?
k32Base dd ?
lpApiAddrs label near
    dd offset sGetProcAddress
    dd offset sLoadLibrary
    dd 0,0

sGetProcAddress db "GetProcAddress",0
sLoadLibrary 	db "LoadLibraryA",0


aGetProcAddress dd 0
aLoadLibrary 	dd 0
;
_Start:
    call _delta                         ;-----重定位-------
_delta:
    pop ebp
    sub ebp,offset _delta
    mov dword ptr[ebp+appBase],ebp

    ; ******* Your code 1 begin task 5******
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

    lea edi,[ebp+aGetProcAddress]		;-----seach Kernel32.dll for two api address
    lea esi,[ebp+lpApiAddrs]			;esi指向api名字的地址，以0,0为结束
lop_get:
    lodsd								;get api name address offset into eax
    cmp eax,0							;is it end?
    jz End_Get
    add eax,ebp							;get api name
    lea ebx, [ebp+fName]                ; 复制函数名到fName
    xor ecx, ecx
lop_copy1:
    mov dl, byte ptr[eax+ecx]
    test dl, dl
    jz lop_copy2
    mov [ebx+ecx], dl
    inc ecx
    jmp lop_copy1
lop_copy2:
    mov byte ptr[ebx+ecx], " "
    inc ecx
    cmp ecx, 20h
    jl lop_copy2

    push eax							;arg of GetApiA
    push dword ptr[ebp+k32Base]			;arg of GetApiA
    call GetApiA 						;Call GetApiA to retrive two functions address from Kerenel32.dll
    stosd								;return value:eax 存入edi指向地址
    call 	saveEax						;Save Eax into val
    invoke MessageBox, NULL, addr fName, addr szMsg, MB_OK	;MessageBox for two api ,here just use user32.dll 
    jmp lop_get
End_Get:
_Exit:
    ;push 0
    invoke ExitProcess, NULL 
    end _Start0

