from unicorn import*
from unicorn.x86_const import*

mu = Uc(UC_ARCH_X86,UC_MODE_64)
code_addr = 0x400000
code_size = 0x1000000
stack_addr = 0x7FFFFF000000
stack_size = 0x1000000

mu.mem_map(code_addr, code_size)
mu.mem_map(stack_addr, stack_size)

mu.reg_write(UC_X86_REG_RAX, code_addr)
mu.reg_write(UC_X86_REG_RSP, stack_addr+stack_size)
mu.reg_write(UC_X86_REG_RBP, stack_addr)

asm_CODE = b'PP^_j [SZjPSSSS*T$ *T$ SSSSSSSSSPH\x81\xc6\x00\x01\x00\x00H\x81\xc7\x00\x02\x00\x00H\xc7\xc1\x00\x01\x00\x00\x8a\x070\x06H\xff\xc6H\xff\xc7\xe2\xf4X'

mu.mem_write(code_addr, asm_CODE)
mu.emu_start(code_addr, code_addr+len(asm_CODE))

r_rbx = mu.reg_read(UC_X86_REG_RBX)
print('rbx:',hex(r_rbx))
r_rdx = mu.reg_read(UC_X86_REG_RDX)
print('rdx:',hex(r_rdx))