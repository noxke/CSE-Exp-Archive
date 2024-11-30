#!/usr/bin/python3

import pwn

proc = pwn.process("/challenge/pwntools-tutorials-level2.1")
payload = pwn.asm("""xor rax, rbx;
                    xor rbx, rax;
                    xor rax, rbx""",
                    arch = "amd64")
print(payload)
proc.send_raw(payload)

result = proc.recvall().decode()
for line in result.split('\n'):
    print(line)