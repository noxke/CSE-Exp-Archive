#!/usr/bin/python3

import pwn

proc = pwn.process("/challenge/pwntools-tutorials-level2.3")
# copy 8-bytes memory starting at 0x404000 to 8-bytes memory starting at 0x405000
payload = pwn.asm("""
                    mov rax, 0x404000;
                    mov rbx, [rax];
                    mov rax, 0x405000
                    mov [rax], rbx
                """,
                    arch = "amd64")
print(payload)
proc.send_raw(payload)

result = proc.recvall().decode()
for line in result.split('\n'):
    print(line)