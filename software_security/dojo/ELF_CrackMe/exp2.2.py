#!/usr/bin/python

import os
import pwn
import hashlib
import itertools

def calculate_md5(data):
    md5_hash = hashlib.md5(data).hexdigest()
    return md5_hash


text_offset = 0x1060
text_len = 405
f = open("/challenge/elf-crackme-level2.2", "rb")
f.seek(text_offset)
data = f.read(text_len)
f.close()
ls = []
for i, d in enumerate(data):
    if (d == 0x90):
        ls.append(i)

# bs = bytearray(data)
# for i in range(0x100000000):
#     if (i % 0x100000 == 0):
#         print(i)
#     b = i.to_bytes(length=4, byteorder="big")
#     bs[ls[0]] = b[0]
#     bs[ls[1]] = b[1]
#     bs[ls[2]] = b[2]
#     bs[ls[3]] = b[3]
#     if (calculate_md5(bytes(bs)) == "d5a7cfeb46121dbb703fe0929ab060b2"):
#         print(bytes(bs))
#         break
for indexs in list(itertools.combinations(ls, 2)):
    flag = False
    bs = bytearray(data)
    for i in range(0x10000):
        b = i.to_bytes(length=2, byteorder="big")
        bs[indexs[0]] = b[0]
        bs[indexs[1]] = b[1]
        if (calculate_md5(bytes(bs)) == "ba4f77d33e8961855bda04916d50f802"):
            flag = True
            break
    if (flag == True):
        data = bytes(bs)
if (calculate_md5(data) != "ba4f77d33e8961855bda04916d50f802"):
    exit()
for i in ls:
    print(i, hex(bs[i]))
# exit()

def readlines(proc):
    try:
        line = proc.recvline(timeout=0.01)
        while (len(line) != 0):
            print(line.decode(), end='')
            line = proc.recvline(timeout=0.01)
    except:
        pass


os.chdir("/challenge")
proc = pwn.process("./utility.py")
readlines(proc)

for i, d in enumerate(data):
    posi = text_offset + i
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

