#!/usr/bin/python
cd /challenge


echo 0x12 > ~/tmp.txt
echo 0x3e >> ~/tmp.txt

./utility.py < ~/tmp.txt

./elf-crackme-level1.0
cd -
