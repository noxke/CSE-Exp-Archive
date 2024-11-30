#!/usr/bin/env python

from hashlib import md5
from z3 import *


table = "1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFHJKLZXCVBNM-+/"

ans = "DiQJxw0tpL97"

part1_ans = "DiQJ"
part2_ans = "xw0t"
part3_ans = "pL97"
part4_ans = b'\xec\xcf\xb5\x19'

part1 = part1_ans

# 第二部分
part2 = ""
solver = Solver()
s = BitVecs('c0 c1 c2 c3', 8)
for i in range(4):
    solver.add(s[i] >= 0x30)
    solver.add(s[i] <= 0x7A)
solver.add((s[0] >> 2) & 0x3F == table.index(part2_ans[0]))
for i in range(1, 4):
    solver.add(((s[i] >> 2) ^ (s[i-1]) >> 2) & 0x3F == table.index(part2_ans[i]))
if solver.check() == sat:
    result = solver.model()
    part2 += chr(result[s[0]].as_long())
    part2 += chr(result[s[1]].as_long())
    part2 += chr(result[s[2]].as_long())
    part2 += chr(result[s[3]].as_long())

# 第三部分
part3 = ""
solver = Solver()
s = BitVecs('c0 c1 c2 c3', 8)
for i in range(4):
    solver.add(s[i] >= 0x30)
    solver.add(s[i] <= 0x7A)
solver.add((s[0] >> 2) & 0x3F == table.index(part3_ans[0]))
solver.add(((s[1] >> 4) & 0xF) | ((s[0] << 4) & 0x30) == table.index(part3_ans[1]))
solver.add(((s[2] >> 6) & 0x3) | ((s[1] << 2) & 0x3C) == table.index(part3_ans[2]))
solver.add(s[3] ^ s[2] & 0x3F  == table.index(part3_ans[3]))
if solver.check() == sat:
    result = solver.model()
    part3 += chr(result[s[0]].as_long())
    part3 += chr(result[s[1]].as_long())
    part3 += chr(result[s[2]].as_long())
    part3 += chr(result[s[3]].as_long())

def md5_crack():
    md5_ans = part4_ans
    for c0 in table:
        for c1 in table:
            for c2 in table:
                for c3 in table:
                    s = c0 + c1 + c2 + c3
                    if (md5(s.encode()).digest()[12:] == md5_ans):
                        return s
    return None

part4 = md5_crack()

lics = part1 + "-" + part2 + "-" + part3 + "-" + part4
print("license: ", lics)
# DiQJ-xTpH-OR06-zm4R
