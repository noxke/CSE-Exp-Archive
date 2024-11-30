;UID:U202100000:
;Flag:00da2f
;Name:noxke
;Date:2023年12月22日  
;FileName:mype1.asm
;Other comments：
.386
.model flat,stdcall
option casemap:none
include c:\masm32\include\windows.inc
include c:\masm32\include\kernel32.inc
includelib c:\masm32\lib\kernel32.lib
include c:\masm32\include\user32.inc
includelib c:\masm32\lib\user32.lib
.data
MsgBoxCaption db "PETest",0
MsgBoxText1 db "ID:U202100000;Name:noxke;PEHost:MessageBox1",0
MsgBoxText2 db "ID:U202100000;Name:noxke;PEHost:MessageBox2",0
.code
start:
invoke MessageBox, NULL, addr MsgBoxText1, addr MsgBoxCaption, MB_OK; 查看 Using invoke;调用弹窗API
invoke MessageBox, NULL, addr MsgBoxText2, addr MsgBoxCaption, MB_OK; 查看 Using invoke;调用弹窗API
invoke ExitProcess, NULL; 调用结束进程API
end start
