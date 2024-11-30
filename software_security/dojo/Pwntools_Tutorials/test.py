from unicorn import*
from unicorn.x86_const import*

mu=Uc(UC_ARCH_X86,UC_MODE_64)
ADDRESS=0x1000000
mu.mem_map(ADDRESS,2*1024*1024)

asm_CODE=b'H\xc7\xc0xV4\x12'

mu.mem_write(ADDRESS,asm_CODE)
mu.emu_start(ADDRESS,ADDRESS+len(asm_CODE))
r_rax=mu.reg_read(UC_X86_REG_RAX)
print('rax:',hex(r_rax))