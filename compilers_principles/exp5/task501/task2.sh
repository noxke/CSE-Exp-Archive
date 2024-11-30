#!/bin/bash
opt -S -mem2reg test.txt -o test.ll
llc test.ll -march=x86 -o test.s
clang -m32 test.s -o test