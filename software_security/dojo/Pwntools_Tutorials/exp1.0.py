#!/usr/bin/python3

import pwn

proc = pwn.process("/challenge/pwntools-tutorials-level1.0")
payload = pwn.p64(0xdeadbeef)
print(payload)
proc.send_raw(payload)

result = proc.recvall().decode()
for line in result.split('\n'):
    print(line)
