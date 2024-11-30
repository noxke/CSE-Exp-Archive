#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

#define MAX_BUFSIZE (1 << 22)
char _b[MAX_BUFSIZE], *_b1, *_b2;
// 读一个字符
#define getch() (_b1 == _b2 ? _b2 = _b + fread(_b, 1, MAX_BUFSIZE, stdin), _b1 = _b, *(_b1++) : *(_b1++))

char output_buf[MAX_BUFSIZE];
char *p = output_buf;
#define putch(c) (*p++ = c)
#define flush() (fwrite(output_buf, 1, p - output_buf, stdout), p = output_buf)
// MAX_BUFSIZE是读写函数的最大缓冲，比实际读写的数据小，所以到一定的时候就要清空，否则就会溢出。

// 读一个整数
int read_int();
// 读一行数据
void read_line(unsigned int *n1, unsigned int *n2);
// 写一行数据
void write_hex(unsigned int n);

#define TABLE_LEN 1 << 16

// S盒
int s_box[16] = {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7};
// 逆S盒
int res_box[16] = {14, 3, 4, 8, 1, 12, 10, 15, 7, 13, 9, 6, 11, 2, 0, 5};
// P盒
int p_box[16] = {0, 4, 8, 12, 1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15};
// 逆P盒
int rep_box[16] = {0, 4, 8, 12, 1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15};

// SP表
unsigned int sp_table[TABLE_LEN];

// 计算sp表
void calc_sp_table();

// 加密
unsigned int encrypto(unsigned int key, unsigned int plain);

// 明密文对
unsigned int plains[10000] = {0};
unsigned int ciphers[10000] = {0};

// 线性密码分析
unsigned int liner_anys(unsigned int *plains, unsigned int *ciphers, int num);

bool cmp(vector<int> a, vector<int> b)
{
    return a[0] > b[0];
}

struct timespec t_start;
struct timespec t_end;
void timer_start()
{
    clock_gettime(CLOCK_MONOTONIC, &t_start);
}
void timer_stop()
{
    clock_gettime(CLOCK_MONOTONIC, &t_end);
    printf("Seconds = %ld \t Nanoseconds = %ld\n", (t_end.tv_sec - t_start.tv_sec), (t_end.tv_nsec - t_start.tv_nsec));
}

int main()
{
    // 初始化sp表
    calc_sp_table();
    int n = read_int();
    timer_start();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 8000; j++)
        {
            // 读取一行数据
            read_line(plains + j, ciphers + j);
        }
        // 进行线性密码分析计算密钥
        unsigned int key = liner_anys(plains, ciphers, 8000);
        // 输出
        write_hex(key);
    }
    timer_stop();
    // 退出时输出剩余缓冲区内容
    flush();
    return 0;
}

unsigned int liner_anys(unsigned int *plains, unsigned int *ciphers, int num)
{
    // 通过两条链的计算得到偏差最大的几个16位子密钥
    // 保存偏差最大的几个子密钥
    int save_max = 13;
    // 后16位子密钥
    vector<int> subkeys;
    // 中间子密钥计数器
    vector<vector<int>> cnts1;
    vector<vector<int>> cnts2;
    // 提前线性运算存储结果
    unsigned char z1_2[16][8000]; // x_5 ^ x_7 ^ x_8 ^ u_6 ^ u_8;
    unsigned char z1_4[16][8000]; // u_14 ^ u_16;
    unsigned char z2_1[16][8000]; // u_2 ^ u_4;
    unsigned char z2_2[16][8000]; // x_5 ^ x_6 ^ u_6 ^ u_8;
    unsigned char z2_3[16][8000]; // u_10 ^ u_12;
    for (int i = 0; i < 16; i++)
    {
        int k1 = i;
        int k2 = i;
        int k3 = i;
        int k4 = i;
        for (int j = 0; j < num; j++)
        {
            unsigned int plain = *(plains + j);
            unsigned int cipher = *(ciphers + j);
            int y1 = (cipher >> 12) & 0xf;
            int y2 = (cipher >> 8) & 0xf;
            int y3 = (cipher >> 4) & 0xf;
            int y4 = cipher & 0xf;
            int u1 = res_box[y1 ^ k1];
            int u2 = res_box[y2 ^ k2];
            int u3 = res_box[y3 ^ k3];
            int u4 = res_box[y4 ^ k4];
            int x_5 = (plain >> 11) & 1;
            int x_6 = (plain >> 10) & 1;
            int x_7 = (plain >> 9) & 1;
            int x_8 = (plain >> 8) & 1;
            int u_2 = (u1 >> 2) & 1;
            int u_4 = u1 & 1;
            int u_6 = (u2 >> 2) & 1;
            int u_8 = u2 & 1;
            int u_10 = (u3 >> 2) & 1;
            int u_12 = u3 & 1;
            int u_14 = (u4 >> 2) & 1;
            int u_16 = u4 & 1;
            // 计算随机变量
            z1_2[k2][j] = x_5 ^ x_7 ^ x_8 ^ u_6 ^ u_8;
            z1_4[k4][j] = u_14 ^ u_16;

            z2_1[k1][j] = u_2 ^ u_4;
            z2_2[k2][j] = x_5 ^ x_6 ^ u_6 ^ u_8;
            z2_3[k3][j] = u_10 ^ u_12;
        }
    }
    // 第一条链
    for (int i = 0; i < 256; i++)
    {
        int cnt = 0;
        int k2 = i >> 4;
        int k4 = i & 0xf;
        for (int j = 0; j < num; j++)
        {
            cnt += z1_2[k2][j] ^ z1_4[k4][j];
        }
        cnt = cnt - num / 2;
        if (cnt < 0)
        {
            cnt = -cnt;
        }
        vector<int> v_tmp = {cnt, i};
        cnts1.push_back(v_tmp);
    }
    // 第一条链偏差最大的几个子密钥
    sort(cnts1.begin(), cnts1.end(), cmp);
    // 第二条链
    // timer_start();
    for (int k = 0; k < save_max; k++)
    {
        int k2 = (cnts1[k][1] >> 4) & 0xf;
        int k4 = cnts1[k][1] & 0xf;
        for (int i = 0; i < 256; i++)
        {
            int cnt = 0;
            int k1 = (i >> 4) & 0xf;
            int k3 = i & 0xf;
            for (int j = 0; j < num; j++)
            {
                cnt += z2_1[k1][j] ^ z2_2[k2][j] ^ z2_3[k3][j];
            }
            cnt = cnt - num / 2;
            if (cnt < 0)
            {
                cnt = -cnt;
            }
            // 合并为一个子密钥
            int subkey = (k1 << 12) | (k2 << 8) | (k3 << 4) | k4;
            vector<int> v_tmp = {cnt, subkey};
            cnts2.push_back(v_tmp);
        }
    }
    // timer_stop();
    for (int i = 0; i < save_max; i++)
    {
        vector<vector<int>>::iterator max_iter = cnts2.begin();
        for (auto iter = cnts2.begin(); iter != cnts2.end(); iter++)
        {
            if ((*iter)[0] >= (*max_iter)[0])
            {
                max_iter = iter;
            }
        }
        subkeys.push_back((*max_iter)[1]);
        (*max_iter)[0] = 0;
    }
    // 16位子密钥
    for (auto subkey : subkeys)
    {
        // 爆破剩余16位密钥
        for (int i = 0; i < (1 << 16); i++)
        {
            // 组合成完整密钥
            unsigned int key = (i << 16) | (subkey & 0xffff);
            // unsigned int key = ((i << 8) & 0xfffff000) | ((i << 4) & 0xf0) | ((subkey << 4) & 0xf00) | (subkey & 0xf0);
            // 密钥正确
            if (encrypto(key, *plains) == *ciphers)
            {
                if (encrypto(key, *(plains + 1)) == *(ciphers + 1))
                {
                    if (encrypto(key, *(plains + 2)) == *(ciphers + 2))
                    {
                        return key;
                    }
                }
            }
        }
    }
    // 未找到密钥
    return 0xffffffff;
}

int read_int()
{
    char ch;
    int ret = 0;
    ch = getch();
    while (ch >= '0' && ch <= '9')
    {
        ret = ret * 10 + ch - '0';
        ch = getch();
    }
    return ret;
}

void read_line(unsigned int *n1, unsigned int *n2)
{
    char ch;
    int n = 0;
    ch = getch();
    while ((ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'f'))
    {
        if (ch >= '0' && ch <= '9')
        {
            n = (n << 4) + ch - '0';
        }
        else
        {
            n = (n << 4) + ch - 'a' + 10;
        }
        ch = getch();
    }
    *n1 = n;
    n = 0;
    ch = getch();
    while ((ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'f'))
    {
        if (ch >= '0' && ch <= '9')
        {
            n = (n << 4) + ch - '0';
        }
        else
        {
            n = (n << 4) + ch - 'a' + 10;
        }
        ch = getch();
    }
    *n2 = n;
}

void calc_sp_table()
{
    unsigned int i;
    for (i = 0; i < (1 << 16); i++)
    {
        // 分为4个四位数
        int d0, d1, d2, d3;
        d0 = (i >> 12) & 0xf;
        d1 = (i >> 8) & 0xf;
        d2 = (i >> 4) & 0xf;
        d3 = i & 0xf;
        // s盒代换
        d0 = s_box[d0];
        d1 = s_box[d1];
        d2 = s_box[d2];
        d3 = s_box[d3];

        unsigned int s = (d0 << 12) | (d1 << 8) | (d2 << 4) | d3;
        unsigned int p = 0;
        // 进行p盒置换
        int j;
        for (j = 0; j < 16; j++)
        {
            p = p | ((s >> (15 - j) & 1) << (15 - p_box[j]));
        }
        sp_table[i] = p;
    }
}

unsigned int encrypto(unsigned int key, unsigned int plain)
{
    unsigned int ki, wi, ui;
    wi = plain;
    // 3轮SP查表
    for (int i = 0; i < 3; i++)
    {
        // 第i轮秘钥
        ki = (key >> ((4 - i) << 2)) & 0xffff;
        // 轮秘钥异或
        ui = wi ^ ki;
        // SP查表
        wi = sp_table[ui];
    }
    // 第4轮只做S代换
    ki = (key >> 4) & 0xffff;
    ui = wi ^ ki;
    // 分为4个4位数
    int d0, d1, d2, d3;
    d0 = (ui >> 12) & 0xf;
    d1 = (ui >> 8) & 0xf;
    d2 = (ui >> 4) & 0xf;
    d3 = ui & 0xf;
    // s盒代换
    d0 = s_box[d0];
    d1 = s_box[d1];
    d2 = s_box[d2];
    d3 = s_box[d3];
    unsigned int vi = (d0 << 12) | (d1 << 8) | (d2 << 4) | d3;
    // 第5轮只做异或
    ki = key & 0xffff;
    unsigned int cipher = ki ^ vi;
    // 得到密文
    return cipher;
}

void write_hex(unsigned int n)
{
    for (int i = 0; i < 8; i++)
    {
        int d = ((n >> (28 - (i << 2))) & 0xf) + '0';
        d <= '9' ? putch(d) : putch(d - '0' - 10 + 'a');
    }
    putch('\n');
    if ((p - output_buf) > (MAX_BUFSIZE >> 1))
        flush(); // 清空缓冲区
}