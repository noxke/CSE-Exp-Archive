#!/usr/bin/env python

from hashlib import md5



table = "1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFHJKLZXCVBNM-+/"

ans = "DiQJxw0tpL97"

part1 = "DiQJ"
part2 = "xw0t"
part3 = "pL97"

# 第二部分
c0 = table.index(part2[0]) << 2
c1 = (table.index(part2[1]) ^ (c0 >> 2)) << 2
c2 = (table.index(part2[2]) ^ (c1 >> 2)) << 2
c3 = (table.index(part2[3]) ^ (c2 >> 2)) << 2

part2 = chr(c0) + chr(c1) + chr(c2) + chr(c3)


# 第三部分
d0 = table.index(part3[0])
d1 = table.index(part3[1])
d2 = table.index(part3[2])
d3 = table.index(part3[3])
c0 = (d0 << 2) & 0x7F
c0 = c0 | (d1 >> 4)
c1 = (d1 << 4) & 0x7F
c1 = c1 | (d2 >> 2)
c2 = (d2 << 6) & 0x7F   # 0
c2 = 48
c3 = d3 ^ c2
print(c3)
part3 = chr(c0) + chr(c1) + chr(c2) + chr(c3)

def md5_crack():
    md5_ans = b'\xec\xcf\xb5\x19'
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
