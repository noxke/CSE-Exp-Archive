#!/usr/bin/python3

import pwn

proc = pwn.process("/challenge/pwntools-tutorials-level2.6")
# rax = the sum from 1 to rcx
payload = pwn.asm("""
                    mov rax, 0 
                again:
                    add rax, rcx
                    loop again
                """,
                    arch = "amd64")
print(payload)
proc.send_raw(payload)

result = proc.recvall().decode()
for line in result.split('\n'):
    print(line)