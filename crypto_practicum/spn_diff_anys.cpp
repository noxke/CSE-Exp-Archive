#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

#define MAX_BUFSIZE 0x50000
char _b[MAX_BUFSIZE], *_b1, *_b2;

char output_buf[MAX_BUFSIZE];
char *p = output_buf;
#define putch(c) (*p++ = c)
#define flush() (fwrite(output_buf, 1, p - output_buf, stdout), p = output_buf)
// MAX_BUFSIZE是读写函数的最大缓冲，比实际读写的数据小，所以到一定的时候就要清空，否则就会溢出。


// 读一行数据
void read_line(unsigned int ciphers[]);
// 写一行数据
void write_hex(unsigned int n);

#define TABLE_LEN 1 << 16
#define NUM 0x3000
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

// 16位数中1个个数
char num_one_bit[0x10000];

// 将1位16进制转换为整数
char hex2int[256];
char dec2hex[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

// 计算sp表
void calc_sp_table();

// 加密
unsigned int encrypt(unsigned int key, unsigned int plain);

// 差分密码分析
unsigned int differ_anys(unsigned int *ciphers);

// 密文对
unsigned int ciphers[0x10000] = {0};



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
    // 初始化1比特个数表
    timer_start();
    for (int i = 0; i < 0x10000; i++)
    {
        char cnt = 0;
        int tmp = i;
        for (int j = 0; j < 16; j++)
        {
            cnt = cnt + (tmp & 1);
            tmp = tmp >> 1;
        }
        num_one_bit[i] = cnt;
    }
    // 初始化16进制转换整数表
    for (int i = 0; i < 16; i++)
    {
        hex2int[dec2hex[i]] = i;
    }
    // 初始化sp表
    calc_sp_table();
    int n;
    scanf("%d\n", &n);
    for (int i = 0; i < n; i++)
    {
        // 读取一行数据
        // timer_start();
        read_line(ciphers);
        // timer_stop();
        // 进行差分密码分析计算密钥
        // timer_start();
        unsigned int key = differ_anys(ciphers);
        // timer_stop();
        // 输出
        write_hex(key);
    }
    timer_stop();
    // 退出时输出剩余缓冲区内容
    flush();
    return 0;
}

unsigned int differ_anys(unsigned int *ciphers)
{
    // 先计算每个密钥的偏差，供后面查表使用
    // 每64位压缩存储
    unsigned long long k1_diff[16][NUM / 64];
    unsigned long long k2_diff[16][NUM / 64];
    unsigned long long k3_diff[16][NUM / 64];
    unsigned long long k4_diff[16][NUM / 64];
    unsigned int x, x_, y, y_;
    // timer_start();
    for (int k = 0; k < 16; k++)
    {
        unsigned long long k1_dif = 0;
        unsigned long long k2_dif = 0;
        unsigned long long k3_dif = 0;
        unsigned long long k4_dif = 0;
        // 移位次数
        int shift = 0;
        for (int i = 0; i < NUM; i++)
        {
            x = i;
            y = ciphers[x];
            // 将之前的结果左移一位
            k1_dif = k1_dif << 1;
            k2_dif = k2_dif << 1;
            k3_dif = k3_dif << 1;
            k4_dif = k4_dif << 1;
            shift++;

            // 第一轮计算k2 k4，x'=0x0b00，27/1024
            x_ = x ^ 0x0b00;
            y_ = ciphers[x_];
            if (((y ^ y_) & 0xf0f0) == 0)
            {
                int y2 = (y >> 8) & 0xf;
                int y4 = y & 0xf;
                int y2_ = (y_ >> 8) & 0xf;
                int y4_ = y_ & 0xf;

                int u2 = res_box[y2 ^ k];
                int u4 = res_box[y4 ^ k];
                int u2_ = res_box[y2_ ^ k];
                int u4_ = res_box[y4_ ^ k];
                if ((u2 ^ u2_) == 0x6)
                {
                    k2_dif = k2_dif | 1;
                }
                if ((u4 ^ u4_) == 0x6)
                {
                    k4_dif = k4_dif | 1;
                }
            }
            // 第二轮计算k1 k3，x'=0x0500，3/512
            x_ = x ^ 0x0500;
            y_ = ciphers[x_];
            if (((y ^ y_) & 0x0f0f) == 0)
            {
                int y1 = (y >> 12) & 0xf;
                int y3 = (y >> 4) & 0xf;
                int y1_ = (y_ >> 12) & 0xf;
                int y3_ = (y_ >> 4) & 0xf;

                int u1 = res_box[y1 ^ k];
                int u3 = res_box[y3 ^ k];
                int u1_ = res_box[y1_ ^ k];
                int u3_ = res_box[y3_ ^ k];
                if ((u1 ^ u1_) == 0x6)
                {
                    k1_dif = k1_dif | 1;
                }
                if ((u3 ^ u3_) == 0x6)
                {
                    k3_dif = k3_dif | 1;
                }
            }
            if (shift == 64)
            {
                shift = 0;
                k1_diff[k][i / 64] = k1_dif;
                k2_diff[k][i / 64] = k2_dif;
                k3_diff[k][i / 64] = k3_dif;
                k4_diff[k][i / 64] = k4_dif;
            }
        }
    }
    // timer_stop();

    int save_max = 2;
    // 后16位子密钥
    vector<int> subkeys;
    // 每轮计算的子密钥计数器
    int cnts_k24[256];
    int cnts_k13[256];
    // 第一轮计算k2 k4，x'=0x0b00，27/1024
    // timer_start();
    for (int i = 0; i < 256; i++)
    {
        int k2 = i >> 4;
        int k4 = i & 0x0f;
        int cnt = 0;
        for (int j = 0; j < NUM / 64; j++)
        {
            // 当两个表中都储存1才cnt++，相与之后数1的个数
            unsigned long long a_nd = k2_diff[k2][j] & k4_diff[k4][j];
            cnt += num_one_bit[a_nd & 0xffff];
            cnt += num_one_bit[(a_nd >> 16) & 0xffff];
            cnt += num_one_bit[(a_nd >> 32) & 0xffff];
            cnt += num_one_bit[(a_nd >> 48) & 0xffff];
        }
        cnts_k24[i] = cnt;
    }
    // 第二轮计算k1 k3，x'=0x0500，3/512
    for (int i = 0; i < 256; i++)
    {
        int k1 = i >> 4;
        int k3 = i & 0x0f;
        int cnt = 0;
        for (int j = 0; j < NUM / 64; j++)
        {
            // 当两个表中都储存1才cnt++，相与之后数1的个数
            unsigned long long a_nd = k1_diff[k1][j] & k3_diff[k3][j];
            cnt += num_one_bit[a_nd & 0xffff];
            cnt += num_one_bit[(a_nd >> 16) & 0xffff];
            cnt += num_one_bit[(a_nd >> 32) & 0xffff];
            cnt += num_one_bit[(a_nd >> 48) & 0xffff];
        }
        cnts_k13[i] = cnt;
    }
    // timer_stop();
    // timer_start();
    // 组合16位子秘钥
    for (int i = 0; i < save_max; i++)
    {
        int max_k13 = 0;
        int max_k24 = 0;
        int max = 0;
        for (int k = 0; k < 256; k++)
        {
            if (cnts_k24[k] > max)
            {
                max = cnts_k24[k];
                max_k24 = k;
            }
        }
        cnts_k24[max_k24] = 0;
        for (int j = 0; j < save_max; j++)
        {
            max_k13 = 0;
            max = 0;
            for (int k = 0; k < 256; k++)
            {
                if (cnts_k13[k] > max)
                {
                    max = cnts_k13[k];
                    max_k13 = k;
                }
            }
            cnts_k13[max_k13] = 0;
            int subkey = ((max_k13 & 0xf0) << 8) | ((max_k24 & 0xf0) << 4) | ((max_k13 & 0x0f) << 4) | (max_k24 & 0x0f);
            subkeys.push_back(subkey);
        }
    }
    // timer_stop();
    // 16位子密钥
    for (auto subkey : subkeys)
    {
        // 爆破剩余16位密钥
        for (int i = 0; i < (1 << 16); i++)
        {
            // 组合成完整密钥
            unsigned int key = (i << 16) | (subkey & 0xffff);
            // 密钥正确
            if (encrypt(key, 0x0001) == *(ciphers + 0x0001))
            {
                if (encrypt(key, 0x0010) == *(ciphers + 0x0010))
                {
                    if (encrypt(key, 0x0100) == *(ciphers + 0x0100))
                    {
                        return key;
                    }
                }
            }
        }
    }

    // 未找到秘钥
    return 0xffffffff;
}

void read_line(unsigned int ciphers[])
{
    _b2 = _b + fread(_b, 1, MAX_BUFSIZE, stdin);
    _b1 = _b;
    char *str = _b1;
    char ch1, ch2, ch3, ch4;
    for (int i = 0; i < NUM; i++)
    {
        ch1 = *(str);
        ch2 = *(str + 1);
        ch3 = *(str + 2);
        ch4 = *(str + 3);
        ciphers[i] = (hex2int[ch1] << 12) | (hex2int[ch2] << 8) | (hex2int[ch3] << 4) | hex2int[ch4];
        str = str + 5;
    }
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

unsigned int encrypt(unsigned int key, unsigned int plain)
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