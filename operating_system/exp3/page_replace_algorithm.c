#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#define PAGE_SIZE 0x10    // 页大小
#define MEM_SIZE 0x100    // 内存大小
#define PAGE_FRAME_SIZE 4 // 页框大小

#define REPLACE_ALGORITHM lru_algorithm // 使用的算法
#define SEQ 0                           // 顺序访问
#define JMP 1                           // 跳转访问
#define LOP 2                           // 循环访问
#define RDM 3                           // 随机访问
#define ACCESS_TYPE JMP                 // 访问类型

#define INSTRUCTION_NUM 0x3e8 // 指令条数

// 页表结构体
struct __page_item
{
    int page_index;        // 页号
    int page_frame_index;  // 页框号
    __uint16_t cnt;        // 计数器
    __uint16_t access_cnt; // 访问计数器
    __uint8_t page_fault;  // 缺页
};

__uint8_t process_mem[MEM_SIZE][PAGE_SIZE];       // 进程内存
__uint8_t page_frame[PAGE_FRAME_SIZE][PAGE_SIZE]; // 页框

struct __page_item page_table[PAGE_FRAME_SIZE]; // 页表

int ins_seq[INSTRUCTION_NUM]; // 访问次序
int cur_ins_index;            // 当前访问指令的位置

#define RECORD

#ifdef RECORD
int page_fault_cnt; // 缺页计数器
int replace_record[INSTRUCTION_NUM][3];    // 置换记录
#endif

/*
opt 最佳淘汰算法
返回页框号
*/
int opt_algorithm(int page_index)
{
    int replace_index = 0;
    int cnt = -1;
    for (int i = 0; i < PAGE_FRAME_SIZE; i++)
    {
        // 优先查找空项
        if (page_table[i].page_fault == 1)
        {
            page_table[i].page_fault = 0;
            replace_index = i;
            break;
        }
        // 查找将来最远会被用到的页面
        int cur_page_index = page_table[i].page_index;
        for (int j = cur_ins_index + 1; j < INSTRUCTION_NUM; j++)
        {
            if (ins_seq[j] / PAGE_SIZE == cur_page_index)
            {
                if (j - cur_ins_index > cnt)
                {
                    cnt = j - cur_ins_index;
                    replace_index = i;
                }
                break;
            }
        }
    }
    #ifdef RECORD
    replace_record[cur_ins_index][0] = page_table[replace_index].page_frame_index;
    replace_record[cur_ins_index][1] = page_table[replace_index].page_index;
    replace_record[cur_ins_index][2] = page_index;
    #endif
    // 将页面调入页框
    page_table[replace_index].page_index = page_index;
    page_table[replace_index].cnt = 0;
    page_table[replace_index].access_cnt = 0;
    int page_frame_index = page_table[replace_index].page_frame_index;
    for (int i = 0; i < PAGE_SIZE; i++)
    {
        page_frame[page_frame_index][i] = process_mem[page_index][i];
    }
    return page_frame_index;
}

/*
fifo 先进先出算法
返回页框号
*/
int fifo_algorithm(int page_index)
{
    int replace_index = 0;
    int cnt = -1;
    for (int i = 0; i < PAGE_FRAME_SIZE; i++)
    {
        // 优先查找空项
        if (page_table[i].page_fault == 1)
        {
            page_table[i].page_fault = 0;
            replace_index = i;
            break;
        }
        // 找cnt最大的项
        if (page_table[i].cnt > cnt)
        {
            cnt = page_table[i].cnt;
            replace_index = i;
        }
    }
    #ifdef RECORD
    replace_record[cur_ins_index][0] = page_table[replace_index].page_frame_index;
    replace_record[cur_ins_index][1] = page_table[replace_index].page_index;
    replace_record[cur_ins_index][2] = page_index;
    #endif
    // 将页面调入页框
    page_table[replace_index].page_index = page_index;
    page_table[replace_index].cnt = 0;
    page_table[replace_index].access_cnt = 0;
    int page_frame_index = page_table[replace_index].page_frame_index;
    for (int i = 0; i < PAGE_SIZE; i++)
    {
        page_frame[page_frame_index][i] = process_mem[page_index][i];
    }
    // 更新所有页面cnt
    for (int i = 0; i < PAGE_FRAME_SIZE; i++)
    {
        page_table[i].cnt += 1;
    }
    return page_frame_index;
}

/*
lru 最近未使用算法
返回页框号
*/
int lru_algorithm(int page_index)
{
    int replace_index = 0;
    int cnt = -1;
    for (int i = 0; i < PAGE_FRAME_SIZE; i++)
    {
        // 优先查找空项
        if (page_table[i].page_fault == 1)
        {
            page_table[i].page_fault = 0;
            replace_index = i;
            break;
        }
        // 找access_cnt最大的项
        if (page_table[i].access_cnt > cnt)
        {
            cnt = page_table[i].access_cnt;
            replace_index = i;
        }
    }
    #ifdef RECORD
    replace_record[cur_ins_index][0] = page_table[replace_index].page_frame_index;
    replace_record[cur_ins_index][1] = page_table[replace_index].page_index;
    replace_record[cur_ins_index][2] = page_index;
    #endif
    // 将页面调入页框
    page_table[replace_index].page_index = page_index;
    page_table[replace_index].cnt = 0;
    page_table[replace_index].access_cnt = 0;
    int page_frame_index = page_table[replace_index].page_frame_index;
    for (int i = 0; i < PAGE_SIZE; i++)
    {
        page_frame[page_frame_index][i] = process_mem[page_index][i];
    }
    return page_frame_index;
}

/*
访问内存
*/
__uint8_t access_mem(int addr, int (*replace_algorithm)(int))
{
    int page_index = addr / PAGE_SIZE;
    int page_offset = addr % PAGE_SIZE;
    if (page_index >= MEM_SIZE || page_index < 0)
    {
        // 访问的地址不存在
        exit(-1);
    }
    // 查找页号是否在页表中
    int page_frame_index = -1;
    for (int i = 0; i < PAGE_FRAME_SIZE; i++)
    {
        if (page_index == page_table[i].page_index)
        {
            page_frame_index = page_table[i].page_frame_index;
            // 访问的页面计数器置0
            page_table[i].access_cnt = 0;
            break;
        }
    }
    if (page_frame_index == -1)
    {
        // 缺页异常
        page_frame_index = replace_algorithm(page_index);
        #ifdef RECORD
        page_fault_cnt += 1;
        #endif
    }
    // 所有页面访问计数器+1
    for (int i = 0; i < PAGE_FRAME_SIZE; i++)
    {
        page_table[i].access_cnt += 1;
    }
    return page_frame[page_frame_index][page_offset];
}

int main()
{
    srand(time(NULL));
    // 初始化内存
    for (int i = 0; i < MEM_SIZE; i++)
    {
        for (int j = 0; j < PAGE_SIZE; j++)
        {
            process_mem[i][j] = rand() % 0x100;
        }
    }
    // 初始化访问序列
    int i, start, len;
    switch (ACCESS_TYPE)
    {
    case SEQ:
        // 顺序访问
        start = rand() % (MEM_SIZE * PAGE_SIZE);
        for (int i = 0; i < INSTRUCTION_NUM; i++)
        {
            ins_seq[i] = (start + i) % (MEM_SIZE * PAGE_SIZE);
        }
        break;
    case JMP:
        // 跳转访问
        i = 0;
        while (i < INSTRUCTION_NUM)
        {
            len = rand() % PAGE_SIZE;
            start = rand() % (MEM_SIZE * PAGE_SIZE);
            for (int j = 0; (i < INSTRUCTION_NUM) && (j < len); j++)
            {
                ins_seq[i++] = (start + j) % (MEM_SIZE * PAGE_SIZE);
            }
        }
        break;
    case LOP:
        // 循环访问
        i = 0;
        len = rand() % (PAGE_SIZE * PAGE_FRAME_SIZE);
        start = rand() % (MEM_SIZE * PAGE_SIZE);
        while (i < INSTRUCTION_NUM)
        {
            for (int j = 0; (i < INSTRUCTION_NUM) && (j < len); j++)
            {
                ins_seq[i++] = (start + j) % (MEM_SIZE * PAGE_SIZE);
            }
        }
        break;
    case RDM:
        // 随机访问
        for (int i = 0; i < INSTRUCTION_NUM; i++)
        {
            ins_seq[i] = rand() % (MEM_SIZE * PAGE_SIZE);
        }
        break;
    }

    page_fault_cnt = 0;
    // 初始化页表
    for (int i = 0; i < PAGE_FRAME_SIZE; i++)
    {
        page_table[i].page_index = -1;
        page_table[i].page_fault = 1;
        page_table[i].page_frame_index = i;
    }
    // 内存访问
    cur_ins_index = 0;
    // 输出访问序列
    printf("index\t\taddr\t\tdata0\t\tdata1\n");
    for (; cur_ins_index < INSTRUCTION_NUM;)
    {
        int addr = ins_seq[cur_ins_index];
        __uint8_t data = access_mem(addr, REPLACE_ALGORITHM);

        printf("%d\t\t%x\t\t%02x\t\t%02x\n", cur_ins_index, addr, process_mem[addr / PAGE_SIZE][addr % PAGE_SIZE], data);
        cur_ins_index++;
    }
    #ifdef RECORD
    // 输出置换记录
    printf("index\t\tpage_frame\t\told\t\tnew\n");
    for (int i = 0; i < INSTRUCTION_NUM; i++)
    {
        printf("%d\t\t%d\t\t%02x\t\t%02x\n", i, replace_record[i][0], replace_record[i][1], replace_record[i][2]);
    }
    // 计算缺页率
    printf("page fault rate: %d/%d\n", page_fault_cnt, INSTRUCTION_NUM);
    #endif
    return 0;
}