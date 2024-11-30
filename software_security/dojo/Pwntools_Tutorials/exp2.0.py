#!/usr/bin/python3

import pwn

proc = pwn.process("/challenge/pwntools-tutorials-level2.0")
payload = pwn.asm("mov rax, 0x12345678", arch = "amd64")
print(payload)
proc.send_raw(payload)

result = proc.recvall().decode()
for line in result.split('\n'):
    print(line)