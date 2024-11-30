#!/usr/bin/python3

import pwn

proc = pwn.process("/challenge/pwntools-tutorials-level2.4")
# the top value of the stack = the top value of the stack - rbx
payload = pwn.asm("""
                    pop rax;
                    sub rax, rbx;
                    push rax
                """,
                    arch = "amd64")
print(payload)
proc.send_raw(payload)

result = proc.recvall().decode()
for line in result.split('\n'):
    print(line)