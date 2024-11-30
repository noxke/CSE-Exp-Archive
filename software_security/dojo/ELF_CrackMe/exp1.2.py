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

offset = 0x4060
patchs = [0xB0, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xB0, 0x2F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00]

os.chdir("/challenge")
proc = pwn.process("./utility.py")

for i, d in enumerate(patchs):
    proc.kill()
    proc = pwn.process("./utility.py")
    readlines(proc)
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


proc = pwn.process("./utility.py")
payload = b'2';
print(payload)
proc.sendline(payload)
readlines(proc)


proc = pwn.process("./elf-crackme-level1.2")
readlines(proc)