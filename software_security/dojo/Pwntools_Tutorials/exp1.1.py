#!/usr/bin/python3

import pwn

proc = pwn.process("/challenge/pwntools-tutorials-level1.1")
payload = b'p\x15'
payload += pwn.p32(123456789)
payload += b'Bypass Me:)'
print(payload)
proc.sendline(payload)

result = proc.recvall().decode()
for line in result.split('\n'):
    print(line)