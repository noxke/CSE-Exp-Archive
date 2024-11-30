#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define PAGEMAP_ENTRY 8

int main(int argc, const char **argv)
{
    char pagemap_path[0x20];
    __uint64_t pagemap_data = 0;
    int pid;
    int page_size = getpagesize(); // 获取页面大小
    __uint64_t virt_addr;
    __uint64_t file_offset;
    FILE *pagemap_file = NULL;
    if (argc != 3)
    {
        printf("usage: %s pid vaddr\n", argv[0]);
        return 0;
    }
    pid = atoi(argv[1]);
    virt_addr = strtoull(argv[2], NULL, 16);
    if (pid == -1)
    {
        snprintf(pagemap_path, 0x20, "/proc/self/pagemap");
    }
    else
    {
        snprintf(pagemap_path, 0x20, "/proc/%d/pagemap", pid);
    }
    printf("pagemap path : %s\nvirt_addr : 0x%lx\npage_size : 0x%x\n", pagemap_path, virt_addr, page_size);
    // 打开pagemap文件
    pagemap_file = fopen(pagemap_path, "rb");
    if (pagemap_file == NULL)
    {
        printf("open %s failedn\n", pagemap_path);
        return 0;
    }
    // 计算页号
    file_offset = virt_addr / page_size * PAGEMAP_ENTRY;
    fseek(pagemap_file, file_offset, SEEK_SET);
    fread(&pagemap_data, PAGEMAP_ENTRY, 1, pagemap_file);
    fclose(pagemap_file);
    printf("pagemap : %lx\n", pagemap_data);
    if ((pagemap_data >> 56) & 1)
    {
        // 页面独占
        printf("page exclusively mapped\n");
    }
    if ((pagemap_data >> 62) & 1)
    {
        printf("page swapped\n");
    }
    else
    {
        if ((pagemap_data >> 63) & 1)
        {
            __uint64_t pfn = pagemap_data & 0x7FFFFFFFFFFFFF;
            printf("PFN : 0x%lx\nphysical addr : 0x%lx\n", pfn, pfn * page_size + virt_addr % page_size);
        }
        else
        {
            printf("page not present\n");
        }
    }
    return 0;
}