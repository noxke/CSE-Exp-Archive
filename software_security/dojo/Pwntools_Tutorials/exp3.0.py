#!/usr/bin/python3

import pwn

def readlines(proc):
    line = proc.recvline(timeout=0.1)
    while (len(line) != 0):
        print(line.decode(), end='')
        line = proc.recvline(timeout=0.1)

proc = pwn.process("/challenge/pwntools-tutorials-level3.0")
readlines(proc)

# 创建notebook0
payload = b"1"
print(payload)
proc.sendline(payload)
readlines(proc)

payload = b"0" + b'\x00' * (0x10-1)
print(payload)
proc.send_raw(payload)
readlines(proc)

payload = b"hello " + b'\x00' * (0x100-6)
print(payload)
proc.send_raw(payload)
readlines(proc)

# 创建notebook1
payload = b"1"
print(payload)
proc.sendline(payload)
readlines(proc)

payload = b"1" + b'\x00' * (0x10-1)
print(payload)
proc.send_raw(payload)
readlines(proc)

payload = b"world," + b'\x00' * (0x100-6)
print(payload)
proc.send_raw(payload)
readlines(proc)

# 创建notebook3
payload = b"1"
print(payload)
proc.sendline(payload)
readlines(proc)

payload = b"3" + b'\x00' * (0x10-1)
print(payload)
proc.send_raw(payload)
readlines(proc)

payload = b"magic " + b'\x00' * (0x100-6)
print(payload)
proc.send_raw(payload)
readlines(proc)

# 创建notebook5
payload = b"1"
print(payload)
proc.sendline(payload)
readlines(proc)

payload = b"5" + b'\x00' * (0x10-1)
print(payload)
proc.send_raw(payload)
readlines(proc)

payload = b"notebook" + b'\x00' * (0x100-8)
print(payload)
proc.send_raw(payload)
readlines(proc)

# 修改notebook1
payload = b"2"
print(payload)
proc.sendline(payload)
readlines(proc)

payload = b"1" + b'\x00' * (0x10-1)
print(payload)
proc.send_raw(payload)
readlines(proc)

# 修改notebook5
payload = b"2"
print(payload)
proc.sendline(payload)
readlines(proc)

payload = b"5" + b'\x00' * (0x10-1)
print(payload)
proc.send_raw(payload)
readlines(proc)

# 读flag
payload = b"5"
print(payload)
proc.sendline(payload)
readlines(proc)