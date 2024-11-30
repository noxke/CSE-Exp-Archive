#!/usr/bin/python

import os
import pwn

def readlines(proc):
    line = proc.recvline(timeout=0.1)
    while (len(line) != 0):
        print(line.decode())
        line = proc.recvline(timeout=0.1)

offset = 0x48
patchs = [0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00]

os.chdir("/challenge")
proc = pwn.process("./utility.py")
readlines(proc)

for i, d in enumerate(patchs):
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


proc = pwn.process("./elf-crackme-level1.1")
readlines(proc)