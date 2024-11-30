#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct timespec start;
struct timespec end;
void timer_start()
{
    clock_gettime(CLOCK_MONOTONIC, &start);
}
void timer_stop()
{
    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("Seconds = %ld \t Nanoseconds = %ld\n", (end.tv_sec - start.tv_sec), (end.tv_nsec - start.tv_nsec));
}

// R函数
void getstr(unsigned int n, char str[8]);
void R(unsigned int sha1[5], char str[8], int i);
// SHA1函数
int UnitSHA1(const char *str, int length, unsigned int sha1[5]);

// 使用树状结构代替线性结构加速查表
typedef struct _strTreeNode
{
    int is_leaf;
    int value;
    struct _strTreeNode *next[36];
} strTreeNode;

typedef struct
{
    char head[8];
    char tail[8];
} rainbowTable[10000];

// 在彩虹表的链尾查找字符串
int find_rainbow_table(strTreeNode *strTree, char str[8]);
// 检查彩虹表的链, index是链在彩虹表中的编号
int chek_rainbow_table(rainbowTable rbt, int index, int i, unsigned int hash[5], char str[8]);

int main()
{
    int table_len;
    char sha1_str[50];
    unsigned int sha1[5];
    // 彩虹表
    rainbowTable rainbow_table;
    // 字符串树
    strTreeNode *strTree = (strTreeNode *)malloc(sizeof(strTreeNode));
    strTree->is_leaf = 0;
    for (int i = 0; i < 36; i++)
    {
        strTree->next[i] = NULL;
    }
    scanf("%d", &table_len);
    for (int i = 0; i < table_len; i++)
    {
        scanf("%s %s", rainbow_table[i].head, rainbow_table[i].tail);
        // 建立字符串树
        strTreeNode *tmpNode = strTree;
        for (int j = 0; j < 8; j++)
        {
            int ch = rainbow_table[i].tail[j];
            if (ch >= 'a')
            {
                ch = ch - 'a' + 10;
            }
            else
            {
                ch = ch - '0';
            }
            if (tmpNode->next[ch] == NULL)
            {
                strTreeNode *newNode = (strTreeNode *)malloc(sizeof(strTreeNode));
                newNode->is_leaf = 0;
                for (int k = 0; k < 36; k++)
                {
                    newNode->next[k] = NULL;
                }
                tmpNode->next[ch] = newNode;
                tmpNode = newNode;
            }
            else
            {
                tmpNode = tmpNode->next[ch];
            }
        }
        tmpNode->is_leaf = 1;
        tmpNode->value = i;
    }
    // 读取sha1输入
    scanf("%s", sha1_str);
    for (int i = 0; i < 5; i++)
    {
        unsigned int d = 0;
        for (int j = 0; j < 8; j++)
        {
            d = d << 4;
            char ch = sha1_str[8 * i + j];
            if (ch >= '0' && ch <= '9')
            {
                d = d | (ch - '0');
            }
            else
            {
                d = d | (ch - 'a' + 10);
            }
        }
        sha1[i] = d;
    }
    char tmp_str[8];
    // timer_start();
    // 从1到100开始都可能
    for (int j = 1; j <= 100; j++)
    {
        // 复制sha1
        unsigned int tmp_sha1[5];
        strncpy((char *)tmp_sha1, (char *)sha1, 20);
        // R(tmp_sha1, tmp_str, 100);
        // puts(tmp_str);
        // return 0;
        for (int i = 0; i < 10001 - j; i++)
        {
            R(tmp_sha1, tmp_str, ((i + j - 1) % 100) + 1);
            // 检查R运算后得到的字符串是否在彩虹表中
            int index = find_rainbow_table(strTree, tmp_str);
            if (index != -1 && (i + j) % 100 == 0)
            {
                // printf("index: %d i: %d j: %d\n", index, i, j);
                char ret_str[9];
                // 检查是否在index链中
                if (chek_rainbow_table(rainbow_table, index, i, sha1, ret_str) == 1)
                {
                    ret_str[8] = '\0';
                    // printf("index: %d i: %d j: %d\n", index, i, j);
                    // timer_stop();
                    puts(ret_str);
                    return 0;
                }
            }
            UnitSHA1(tmp_str, 8, tmp_sha1);
        }
    }
    // timer_stop();
    puts("None");
    // 因为是做题，所以malloc没有写free :(
    return 0;
}

int find_rainbow_table(strTreeNode *strTree, char str[8])
{
    strTreeNode *tmpNode = strTree;
    for (int i = 0; i < 8; i++)
    {
        char ch = str[i];
        if (ch >= 'a')
        {
            ch = ch - 'a' + 10;
        }
        else
        {
            ch = ch - '0';
        }
        if (tmpNode->next[ch] != NULL)
        {
            // 不为空，说明可能该字符串
            tmpNode = tmpNode->next[ch];
        }
        else
        {
            // 为空，无该字符串
            return -1;
        }
    }
    return tmpNode->value;
}

int chek_rainbow_table(rainbowTable rbt, int index, int i, unsigned int hash[5], char str[8])
{
    char tmp_str[8];
    unsigned int tmp_sha1[5];
    strncpy(tmp_str, rbt[index].head, 8);
    for (int k = 0; k < 10000 - i; k++)
    {
        UnitSHA1(tmp_str, 8, tmp_sha1);
        if (strncmp((char *)hash, (char *)tmp_sha1, 20) == 0)
        {
            strncpy(str, tmp_str, 8);
            return 1;
        }
        R(tmp_sha1, tmp_str, (k % 100) + 1);
    }
    return 0;
}

void getstr(unsigned int n, char str[8])
{
    str[0] = 'a';
    str[1] = '0';
    str[2] = '0';
    str[3] = '0';
    str[4] = '0';
    str[5] = '0';
    str[6] = '0';
    str[7] = '0';
    int i = 2;
    while (n)
    {
        unsigned tmp = n % 36;
        if (tmp < 10)
            str[i++] = tmp + '0';
        else
            str[i++] = tmp - 10 + 'a';
        n = n / 36;
    }
}

void R(unsigned int sha1[5], char str[8], int i)
{
    getstr((sha1[0] + sha1[1] * i) % 2176782336, str);
}

unsigned int SHA1_tmp;

#define SHA1_ROTL(a, b) (SHA1_tmp = (a), ((SHA1_tmp >> (32 - b)) & (0x7fffffff >> (31 - b))) | (SHA1_tmp << b))

#define SHA1_F(B, C, D, t) ((t < 40) ? ((t < 20) ? ((B & C) | ((~B) & D)) : (B ^ C ^ D)) : ((t < 60) ? ((B & C) | (B & D) | (C & D)) : (B ^ C ^ D)))

int UnitSHA1(const char *str, int length, unsigned int sha1[5])
{
    /*
    计算字符串SHA-1
    参数说明：
    str         字符串指针
    length      字符串长度
    sha1         用于保存SHA-1的字符串指针
    返回值为参数sha1
    */
    unsigned char *pp, *ppend;
    unsigned int l, i, K[80], W[80], TEMP, A, B, C, D, E, H0, H1, H2, H3, H4;
    H0 = 0x67452301, H1 = 0xEFCDAB89, H2 = 0x98BADCFE, H3 = 0x10325476, H4 = 0xC3D2E1F0;
    for (i = 0; i < 20; K[i++] = 0x5A827999)
        ;
    for (i = 20; i < 40; K[i++] = 0x6ED9EBA1)
        ;
    for (i = 40; i < 60; K[i++] = 0x8F1BBCDC)
        ;
    for (i = 60; i < 80; K[i++] = 0xCA62C1D6)
        ;
    l = length + ((length % 64 > 56) ? (128 - length % 64) : (64 - length % 64));
    if (!(pp = (unsigned char *)malloc((unsigned int)l)))
        return -1;
    for (i = 0; i < length; pp[i + 3 - 2 * (i % 4)] = str[i], i++)
        ;
    for (pp[i + 3 - 2 * (i % 4)] = 128, i++; i < l; pp[i + 3 - 2 * (i % 4)] = 0, i++)
        ;
    *((unsigned int *)(pp + l - 4)) = length << 3;
    *((unsigned int *)(pp + l - 8)) = length >> 29;
    for (ppend = pp + l; pp < ppend; pp += 64)
    {
        for (i = 0; i < 16; W[i] = ((unsigned int *)pp)[i], i++)
            ;
        for (i = 16; i < 80; W[i] = SHA1_ROTL((W[i - 3] ^ W[i - 8] ^ W[i - 14] ^ W[i - 16]), 1), i++)
            ;
        A = H0, B = H1, C = H2, D = H3, E = H4;
        for (i = 0; i < 80; i++)
        {
            TEMP = SHA1_ROTL(A, 5) + SHA1_F(B, C, D, i) + E + W[i] + K[i];
            E = D, D = C, C = SHA1_ROTL(B, 30), B = A, A = TEMP;
        }
        H0 += A, H1 += B, H2 += C, H3 += D, H4 += E;
    }
    free(pp - l);
    sha1[0] = H0, sha1[1] = H1, sha1[2] = H2, sha1[3] = H3, sha1[4] = H4;
    return 0;
}

// int main()
// {
//     char str[9] = "a0000000";
//     unsigned int sha1[5];
//     for (int i = 0; i < 1999; i++)
//     {
//         UnitSHA1(str, 8, sha1);
//         R(sha1, str, (i % 100) + 1);
//     }
//     puts(str);
//     return 0;
// }
