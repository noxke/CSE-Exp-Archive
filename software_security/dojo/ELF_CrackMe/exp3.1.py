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

offset = 0x348    # 修改plt
data = b'\x08'

os.chdir("/challenge")
proc = pwn.process("./utility.py")
readlines(proc)

posi = offset
readlines(proc)
payload = hex(posi).encode()
print(payload)
proc.sendline(payload)
readlines(proc)
payload = hex(data[0]).encode()
print(payload)
proc.sendline(payload)
readlines(proc)

os.chdir("/usr/bin")
proc = pwn.process("/challenge/elf-crackme-level3.1")
readlines(proc)