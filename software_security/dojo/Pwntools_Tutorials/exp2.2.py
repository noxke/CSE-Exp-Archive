#!/usr/bin/python3

import pwn

proc = pwn.process("/challenge/pwntools-tutorials-level2.2")
# rax = rax % rbx + rcx - rsi
payload = pwn.asm("""div rbx;
                    mov rax, rdx;
                    add rax, rcx;
                    sub rax, rsi""",
                    arch = "amd64")
print(payload)
proc.send_raw(payload)

result = proc.recvall().decode()
for line in result.split('\n'):
    print(line)