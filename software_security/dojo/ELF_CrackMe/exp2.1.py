#!/usr/bin/python

import os
import pwn

def readlines(proc):
    try:
        line = proc.recvline(timeout=0.01)
        while (len(line) != 0):
            print(line.decode(), end='')
            line = proc.recvline(timeout=0.01)
    except:
        pass


offset = 0x3000
data = b'\x00\x00\x00\x00\x00\x00\x00\x00\x08@\x00\x00\x00\x00\x00\x00\x01\x00\x00\x00\x08\x00\x00\x00'

os.chdir("/challenge")
proc = pwn.process("./utility.py")
readlines(proc)

for i, d in enumerate(data):
    posi = offset + i
    payload = b'1'
    print(payload)
    proc.sendline(payload)
    readlines(proc)
    payload = hex(posi).encode()
    print(payload)
    proc.sendline(payload)
    readlines(proc)
    payload = hex(d).encode()
    print(payload)
    proc.sendline(payload)
    readlines(proc)

payload = b'2';
print(payload)
proc.sendline(payload)
readlines(proc)

payload = b'3';
print(payload)
proc.sendline(payload)
readlines(proc)


proc = pwn.process("./elf-crackme-level2.1")
readlines(proc)