#!/usr/bin/env python

import struct
import sys

"""The ELF file header.  This appears at the start of every ELF file."""
Elf32_Ehdr_sruct = "16s"   # e_ident[EI_NIDENT]
Elf32_Ehdr_sruct += "H"    # e_type
Elf32_Ehdr_sruct += "H"    # e_machine
Elf32_Ehdr_sruct += "I"    # e_version
Elf32_Ehdr_sruct += "I"    # e_entry
Elf32_Ehdr_sruct += "I"    # e_phoff
Elf32_Ehdr_sruct += "I"    # e_shoff
Elf32_Ehdr_sruct += "I"    # e_flags
Elf32_Ehdr_sruct += "H"    # e_ehsize
Elf32_Ehdr_sruct += "H"    # e_phentsize
Elf32_Ehdr_sruct += "H"    # e_phnum
Elf32_Ehdr_sruct += "H"    # e_shentsize
Elf32_Ehdr_sruct += "H"    # e_shnum
Elf32_Ehdr_sruct += "H"    # e_shstrndx

Elf64_Ehdr_sruct = "16s"   # e_ident[EI_NIDENT]
Elf64_Ehdr_sruct += "H"    # e_type
Elf64_Ehdr_sruct += "H"    # e_machine
Elf64_Ehdr_sruct += "I"    # e_version
Elf64_Ehdr_sruct += "Q"    # e_entry
Elf64_Ehdr_sruct += "Q"    # e_phoff
Elf64_Ehdr_sruct += "Q"    # e_shoff
Elf64_Ehdr_sruct += "I"    # e_flags
Elf64_Ehdr_sruct += "H"    # e_ehsize
Elf64_Ehdr_sruct += "H"    # e_phentsize
Elf64_Ehdr_sruct += "H"    # e_phnum
Elf64_Ehdr_sruct += "H"    # e_shentsize
Elf64_Ehdr_sruct += "H"    # e_shnum
Elf64_Ehdr_sruct += "H"    # e_shstrndx

Elf32_Ehdr_keys = [
    "e_ident", "e_type", "e_machine", "e_version", "e_entry", "e_phoff", "e_shoff",
    "e_flags", "e_ehsize", "e_phentsize", "e_phnum", "e_shentsize", "e_shnum", "e_shstrndx"]

Elf64_Ehdr_keys = [
    "e_ident", "e_type", "e_machine", "e_version", "e_entry", "e_phoff", "e_shoff",
    "e_flags", "e_ehsize", "e_phentsize", "e_phnum", "e_shentsize", "e_shnum", "e_shstrndx"]


"""Legal values for e_type (object file type)."""
em_machines = ["EM_NONE"]       # 0
em_machines += [""] * 2
em_machines += ["EM_386"]       # 3
em_machines += [""] * 36
em_machines += ["EM_ARM"]       # 40
em_machines += [""] * 21
em_machines += ["EM_X86_64"]    # 62
em_machines += [""] * 120
em_machines += ["EM_AARCH64"]   # 183
em_machines += [""] * 75
em_machines += ["EM_NUM"]       # 259

em32_machines = ["EM_386", "EM_ARM"]
em64_machines = ["EM_X86_64", "EM_AARCH64"]


"""Program segment header."""
Elf32_Phdr_struct = "I"     # p_type
Elf32_Phdr_struct += "I"    # p_offset
Elf32_Phdr_struct += "I"    # p_vaddr
Elf32_Phdr_struct += "I"    # p_paddr
Elf32_Phdr_struct += "I"    # p_filesz
Elf32_Phdr_struct += "I"    # p_memsz
Elf32_Phdr_struct += "I"    # p_flags
Elf32_Phdr_struct += "I"    # p_align

Elf64_Phdr_struct = "I"     # p_type
Elf64_Phdr_struct += "I"    # p_flags
Elf64_Phdr_struct += "Q"    # p_offset
Elf64_Phdr_struct += "Q"    # p_vaddr
Elf64_Phdr_struct += "Q"    # p_paddr
Elf64_Phdr_struct += "Q"    # p_filesz
Elf64_Phdr_struct += "Q"    # p_memsz
Elf64_Phdr_struct += "Q"    # p_align

Elf32_Phdr_keys = ["p_type", "p_offset", "p_vaddr", "p_paddr", "p_filesz", "p_memsz", "p_flags", "p_align"]
Elf64_Phdr_keys = ["p_type", "p_flags", "p_offset", "p_vaddr", "p_paddr", "p_filesz", "p_memsz", "p_align"]

Ph_type = {
    "0x0":"PT_NULL", "0x1":"PT_LOAD", "0x2":"PT_DYNAMIC", "0x3":"PT_INTERP", "0x4":"PT_NOTE", "0x5":"PT_SHLIB",
    "0x6":"PT_PHDR", "0x7":"PT_TLS", "0x8":"PT_NUM", "0x60000000":"PT_LOOS", "0x6474e550":"PT_GNU_EH_FRAME", 
    "0x6474e551":"PT_GNU_STACK", "0x6474e552":"PT_GNU_RELRO", "0x6474e553":"PT_GNU_PROPERTY", "0x6474e554":"PT_GNU_SFRAME",
    "0x6ffffffa":"PT_LOSUNW", "0x6ffffffa":"PT_SUNWBSS", "0x6ffffffb":"PT_SUNWSTACK", "0x6fffffff":"PT_HISUNW",
    "0x6fffffff":"PT_HIOS", "0x70000000":"PT_LOPROC", "0x7fffffff":"PT_HIPROC"}

"""Section header."""
Elf32_Shdr_struct = "I"     # sh_name
Elf32_Shdr_struct += "I"    # sh_type
Elf32_Shdr_struct += "I"    # sh_flags
Elf32_Shdr_struct += "I"    # sh_addr
Elf32_Shdr_struct += "I"    # sh_offset
Elf32_Shdr_struct += "I"    # sh_size
Elf32_Shdr_struct += "I"    # sh_link
Elf32_Shdr_struct += "I"    # sh_info
Elf32_Shdr_struct += "I"    # sh_addralign
Elf32_Shdr_struct += "I"    # sh_entsize

Elf64_Shdr_struct = "I"     # sh_name
Elf64_Shdr_struct += "I"    # sh_type
Elf64_Shdr_struct += "Q"    # sh_flags
Elf64_Shdr_struct += "Q"    # sh_addr
Elf64_Shdr_struct += "Q"    # sh_offset
Elf64_Shdr_struct += "Q"    # sh_size
Elf64_Shdr_struct += "I"    # sh_link
Elf64_Shdr_struct += "I"    # sh_info
Elf64_Shdr_struct += "Q"    # sh_addralign
Elf64_Shdr_struct += "Q"    # sh_entsize

Elf32_Shdr_keys = ["sh_name", "sh_type", "sh_flags", "sh_addr", "sh_offset", "sh_size", "sh_link", "sh_info", "sh_addralign", "sh_entsize"]
Elf64_Shdr_keys = ["sh_name", "sh_type", "sh_flags", "sh_addr", "sh_offset", "sh_size", "sh_link", "sh_info", "sh_addralign", "sh_entsize"]

Sht_type = {
"0x0" : "SHT_NULL", "0x1" : "SHT_PROGBITS", "0x2" : "SHT_SYMTAB", "0x3" : "SHT_STRTAB", "0x4" : "SHT_RELA", "0x5" : "SHT_HASH", "0x6" : "SHT_DYNAMIC",
"0x7" : "SHT_NOTE", "0x8" : "SHT_NOBITS", "0x9" : "SHT_REL", "0xa" : "SHT_SHLI", "0xb" : "SHT_DYNSYM", "0xe" : "SHT_INIT_ARRAY", "0xf" : "SHT_FINI_ARRAY",
"0x10" : "SHT_PREINIT_ARRA", "0x11" : "SHT_GROU", "0x12" : "SHT_SYMTAB_SHNDX", "0x13" : "SHT_RELR", "0x14" : "SHT_NUM", "0x60000000" : "SHT_LOOS",
"0x6ffffff5" : "SHT_GNU_ATTRIBUTES", "0x6ffffff6" : "SHT_GNU_HASH", "0x6ffffff7" : "SHT_GNU_LIBLIST", "0x6ffffff8" : "SHT_CHECKSUM", "0x6ffffffa" : "SHT_LOSUNW",
"0x6ffffffa" : "SHT_SUNW_mov", "0x6ffffffb" : "SHT_SUNW_COMDAT", "0x6ffffffc" : "SHT_SUNW_syminfo", "0x6ffffffd" : "SHT_GNU_verdef", "0x6ffffffe" : "SHT_GNU_verneed",
"0x6fffffff" : "SHT_GNU_versym", "0x6fffffff" : "SHT_HISUNW", "0x6fffffff" : "SHT_HIOS", "0x70000000" : "SHT_LOPROC", "0x7fffffff" : "SHT_HIPROC", "0x80000000" : "SHT_LOUSER", "0x8fffffff" : "SHT_HIUSER"}


"""Symbol table entry."""
Elf32_Sym_struct = "I"      # st_name
Elf32_Sym_struct += "I"     # st_value
Elf32_Sym_struct += "I"     # st_size
Elf32_Sym_struct += "B"     # st_info
Elf32_Sym_struct += "B"     # st_other
Elf32_Sym_struct += "H"     # st_shndx

Elf64_Sym_struct = "I"      # st_name
Elf64_Sym_struct += "B"     # st_info
Elf64_Sym_struct += "B"     # st_other
Elf64_Sym_struct += "H"     # st_shndx
Elf64_Sym_struct += "Q"     # st_value
Elf64_Sym_struct += "Q"     # st_size

Elf32_Sym_keys = ["st_name", "st_value", "st_size", "st_info", "st_other", "st_shndx"]
Elf64_Sym_keys = ["st_name", "st_info", "st_other", "st_shndx", "st_value", "st_size"]


def readelf_ehdr(buf) -> map:
    """分析ELF头"""
    ehdr_map = {}
    buf.seek(0)
    ehdr_data = buf.read(0x14)
    # 识别32位/64位机器码
    fmt = "16sHH"
    machine_type = em_machines[struct.unpack(fmt, ehdr_data)[-1]]
    # 32位
    if machine_type in em32_machines:
        ehdr_data += buf.read(0x20)
        ehdr_ls = struct.unpack(Elf32_Ehdr_sruct, ehdr_data)
        ehdr_map = dict(zip(Elf32_Ehdr_keys, ehdr_ls))
    # 64位
    elif machine_type in em64_machines:
        ehdr_data += buf.read(0x2C)
        ehdr_ls = struct.unpack(Elf64_Ehdr_sruct, ehdr_data)
        ehdr_map = dict(zip(Elf64_Ehdr_keys, ehdr_ls))
    else:
        ehdr_map = None
    buf.seek(0)
    return ehdr_map

def print_ehdr(ehdr_map) -> None:
    """打印ELF头"""
    print("[elf heaer]")
    for key in ehdr_map:
        if (key == "e_ident"):
            print(key, "\t", end="")
            for b in ehdr_map["e_ident"]:
                h = hex(b).upper()[2:]
                h = "0" * (2 - len(h)) + h
                print(h, end=" ")
            print('')
        elif (key == "e_machine"):
            print("{}  \t{}".format(key, em_machines[ehdr_map["e_machine"]]))
        else:
            print("{}  \t0x{}".format(key, hex(ehdr_map[key])[2:].upper()))
    print("")


def readelf_phdr(buf, phoff, phnum, machine) -> list:
    """分析程序头"""
    phdr_maps = []
    machine_type = em_machines[machine]
    if machine_type in em32_machines:
        entsize = 0x20
        for i in range(phnum):
            buf.seek(phoff + i * entsize)
            phdr_data = buf.read(entsize)
            phdr_ls = struct.unpack(Elf32_Phdr_struct, phdr_data)
            phdr_map = dict(zip(Elf32_Phdr_keys, phdr_ls))
            phdr_maps.append(phdr_map)
    elif machine_type in em64_machines:
        entsize = 0x38
        for i in range(phnum):
            buf.seek(phoff + i * entsize)
            phdr_data = buf.read(entsize)
            phdr_ls = struct.unpack(Elf64_Phdr_struct, phdr_data)
            phdr_map = dict(zip(Elf64_Phdr_keys, phdr_ls))
            phdr_maps.append(phdr_map)
    else:
        phdr_maps = None
    buf.seek(0)
    return phdr_maps

def print_phdr(phdr_maps) -> None:
    """打印程序头"""
    print("[program segement heaer table]")
    print("{:<5s}  {:<16s}  {:<6s}  {:<10s}  {:<10s}  {:<10s}  {:<10s}  {:<10s}  {:<10s}".format(
        "index", "type", "flags", "offset", "vaddr", "paddr", "filesz", "memsz", "align"
    ))
    for i, phdr_map in enumerate(phdr_maps):
        p_type = Ph_type[hex(phdr_map["p_type"])]
        p_flags = "PF_"
        if (phdr_map["p_flags"] & 0b010 != 0):
            p_flags += "W"
        else:
            p_flags += "-"
        if (phdr_map["p_flags"] & 0b100 != 0):
            p_flags += "R"
        else:
            p_flags += "-"
        if (phdr_map["p_flags"] & 0b001 != 0):
            p_flags += "X"
        else:
            p_flags += "-"
        p_offset = hex(phdr_map["p_offset"])[2:]
        p_vaddr = hex(phdr_map["p_vaddr"])[2:]
        p_paddr = hex(phdr_map["p_paddr"])[2:]
        p_filesz = hex(phdr_map["p_filesz"])[2:]
        p_memsz = hex(phdr_map["p_memsz"])[2:]
        p_align = hex(phdr_map["p_align"])[2:]
        print("{:^5d}  {:<16s}  {}  0x{:0>8s}  0x{:0>8s}  0x{:0>8s}  0x{:0>8s}  0x{:0>8s}  0x{:0>8s}".format(
            i, p_type, p_flags, p_offset, p_vaddr, p_paddr, p_filesz, p_memsz, p_align
        ))
    print("")


def readelf_shdr(buf, shoff, shnum, machine) -> list:
    """分析节区头"""
    shdr_maps = []
    machine_type = em_machines[machine]
    if machine_type in em32_machines:
        entsize = 0x28
        for i in range(shnum):
            buf.seek(shoff + i * entsize)
            shdr_data = buf.read(entsize)
            shdr_ls = struct.unpack(Elf32_Shdr_struct, shdr_data)
            shdr_map = dict(zip(Elf32_Shdr_keys, shdr_ls))
            shdr_maps.append(shdr_map)
    elif machine_type in em64_machines:
        entsize = 0x40
        for i in range(shnum):
            buf.seek(shoff + i * entsize)
            shdr_data = buf.read(entsize)
            shdr_ls = struct.unpack(Elf64_Shdr_struct, shdr_data)
            shdr_map = dict(zip(Elf64_Shdr_keys, shdr_ls))
            shdr_maps.append(shdr_map)
    else:
        shdr_maps = None
    buf.seek(0)
    return shdr_maps

def print_shdr(buf, shdr_maps, shstrndx=-1) -> None:
    """打印节区头"""
    print("[section header table]")
    print("{:<5s}  {:<20s}  {:<s}".format("index", "type", "name"))
    print("{:<10s}  {:<10s}  {:<10s}  {:<10s}  {:<10s}  {:<10s}  {:<10s}  {:<10s}".format(
        "flags", "offset", "addr", "size", "info", "link", "entsize", "addralign"
    ))
    names = ""
    # 获取节区名
    if (shstrndx != -1 and shstrndx < len(shdr_maps)):
        str_map = shdr_maps[shstrndx]
        str_offset = str_map["sh_offset"]
        str_size = str_map["sh_size"]
        buf.seek(str_offset)
        names = buf.read(str_size).decode()
    for i, shdr_map in enumerate(shdr_maps):
        sh_name = "None"
        sh_name_index = shdr_map["sh_name"]
        if (sh_name_index < len(names)):
            sh_name = "." + names[sh_name_index:].split('.')[1]
        sh_type = Sht_type[hex(shdr_map["sh_type"])]
        sh_flags = hex(shdr_map["sh_flags"])[2:]
        sh_addr = hex(shdr_map["sh_addr"])[2:]
        sh_offset = hex(shdr_map["sh_offset"])[2:]
        sh_size = hex(shdr_map["sh_size"])[2:]
        sh_link = hex(shdr_map["sh_link"])[2:]
        sh_info = hex(shdr_map["sh_info"])[2:]
        sh_addralign = hex(shdr_map["sh_addralign"])[2:]
        sh_entsize = hex(shdr_map["sh_entsize"])[2:]
        print("{:^5d}  {:<20s}  {}".format(i, sh_type, sh_name))
        print("0x{:0>8s}  0x{:0>8s}  0x{:0>8s}  0x{:0>8s}  0x{:0>8s}  0x{:0>8s}  0x{:0>8s}  0x{:0>8s}".format(
            sh_flags, sh_offset, sh_addr, sh_size, sh_info, sh_link, sh_entsize, sh_addralign
        ))
    buf.seek(0)
    print("")


#TODO
def readelf_sym(buf, symoff, symnum, machine) -> list:
    """分析符号表"""
    sym_maps = []
    machine_type = em_machines[machine]
    if machine_type in em32_machines:
        entsize = 0x10
        for i in range(symnum):
            buf.seek(symoff + i * entsize)
            sym_data = buf.read(entsize)
            sym_ls = struct.unpack(Elf32_Sym_struct, sym_data)
            sym_map = dict(zip(Elf32_Sym_keys, sym_ls))
            sym_maps.append(sym_map)
    elif machine_type in em64_machines:
        entsize = 0x18
        for i in range(symnum):
            buf.seek(symoff + i * entsize)
            sym_data = buf.read(entsize)
            sym_ls = struct.unpack(Elf32_Sym_struct, sym_data)
            sym_map = dict(zip(Elf32_Sym_keys, sym_ls))
            sym_maps.append(sym_map)
    else:
        sym_maps = None
    buf.seek(0)
    return sym_maps

#TODO
def print_sym(buf, sym_maps) -> None:
    """打印符号表"""
    return


def main():
    file_path = sys.argv[1]
    with open(file=file_path, mode="rb") as f:
        # 解析ELF文件头
        ehdr_map = readelf_ehdr(f)
        print_ehdr(ehdr_map)
        # 解析程序段头
        phdr_maps = readelf_phdr(f, ehdr_map["e_phoff"], ehdr_map["e_phnum"], ehdr_map["e_machine"])
        print_phdr(phdr_maps)
        # 解析节区头
        shdr_maps = readelf_shdr(f, ehdr_map["e_shoff"], ehdr_map["e_shnum"], ehdr_map["e_machine"])
        print_shdr(f, shdr_maps, ehdr_map["e_shstrndx"])


if __name__ == "__main__":
    main()
