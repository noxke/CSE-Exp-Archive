#!/usr/bin/python3

import pwn

proc = pwn.process("/challenge/pwntools-tutorials-level2.5")
# the top value of the stack = abs(the top value of the stack)
payload = pwn.asm("""
                    pop rax;
                    mov rbx, 0;
                    sub rbx, rax;
                    jl noneg;
                    mov rax, rbx;
                noneg:
                    push rax
                """,
                    arch = "amd64")
print(payload)
proc.send_raw(payload)

result = proc.recvall().decode()
for line in result.split('\n'):
    print(line)