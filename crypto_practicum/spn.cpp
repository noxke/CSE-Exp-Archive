#include <cstdio>

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
void write_line(unsigned int n1, unsigned int n2);

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

// 逆SP表
unsigned int resp_table[TABLE_LEN];

// 计算sp表
void calc_sp_table();
// 计算逆sp表
void calc_resp_table();

// 加密
unsigned int encrypto(unsigned int key, unsigned int plain);
// 解密
unsigned int decrypto(unsigned int key, unsigned int cipher);

int main()
{
    // 计算sp表
    calc_sp_table();
    // 计算逆sp表
    calc_resp_table();
    int n = read_int();
    unsigned int key, cipher, plain, new_plain;
    for (int i = 0; i < n; i++)
    {
        // 读取一行数据
        read_line(&key, &plain);
        // 加密
        cipher = encrypto(key, plain);
        // 最后一位取反解密
        new_plain = decrypto(key, cipher ^ 1);
        // 输出
        write_line(cipher, new_plain);
    }
    // 退出时输出剩余缓冲区内容
    flush();
    return 0;
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

void calc_resp_table()
{
    unsigned int i;
    for (i = 0; i < (1 << 16); i++)
    resp_table[sp_table[i]] = i;
}
// void calc_resp_table()
// {
//     unsigned int i;
//     for (i = 0; i < (1 << 16); i++)
//     {
//         // 进行p盒逆置换
//         unsigned int p = 0;
//         int j;
//         for (j = 0; j < 16; j++)
//         {
//             p = p | ((i >> (15 - j) & 1) << (15 - rep_box[j]));
//         }

//         // 分为4个四位数
//         int d0, d1, d2, d3;
//         d0 = (p >> 12) & 0xf;
//         d1 = (p >> 8) & 0xf;
//         d2 = (p >> 4) & 0xf;
//         d3 = p & 0xf;
//         // s盒逆代换
//         d0 = res_box[d0];
//         d1 = res_box[d1];
//         d2 = res_box[d2];
//         d3 = res_box[d3];

//         unsigned int s = (d0 << 12) | (d1 << 8) | (d2 << 4) | d3;

//         resp_table[i] = s;
//     }
// }

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

unsigned int decrypto(unsigned int key, unsigned int cipher)
{
    unsigned int ki, wi, ui;
    // 第5轮只做异或
    ki = key & 0xffff;
    unsigned int vi = ki ^ cipher;

    // 第4轮只做S逆代换
    // 分为4个4位数
    int d0, d1, d2, d3;
    d0 = (vi >> 12) & 0xf;
    d1 = (vi >> 8) & 0xf;
    d2 = (vi >> 4) & 0xf;
    d3 = vi & 0xf;
    // s盒逆代换
    d0 = res_box[d0];
    d1 = res_box[d1];
    d2 = res_box[d2];
    d3 = res_box[d3];
    ui = (d0 << 12) | (d1 << 8) | (d2 << 4) | d3;
    
    ki = (key >> 4) & 0xffff;
    wi = ui ^ ki;

    // 3轮逆SP查表
    for (int i = 0; i < 3; i++)
    {
        // 逆SP查表
        ui = resp_table[wi];
        // 第i轮秘钥
        ki = (key >> ((i + 2) << 2)) & 0xffff;
        // 轮秘钥异或
        wi = ui ^ ki;
    }

    unsigned int plain = wi;
    // 得到明文
    return plain;
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

void write_line(unsigned int n1, unsigned int n2)
{
    // 分为4个四位数
    char c0, c1, c2, c3;
    c0 = ((n1 >> 12) & 0xf) + '0';
    c1 = ((n1 >> 8) & 0xf) + '0';
    c2 = ((n1 >> 4) & 0xf) + '0';
    c3 = (n1 & 0xf) + '0';
    c0 <= '9' ? putch(c0) : putch(c0 - '0' - 10 + 'a');
    c1 <= '9' ? putch(c1) : putch(c1 - '0' - 10 + 'a');
    c2 <= '9' ? putch(c2) : putch(c2 - '0' - 10 + 'a');
    c3 <= '9' ? putch(c3) : putch(c3 - '0' - 10 + 'a');
    putch(' ');
    c0 = ((n2 >> 12) & 0xf) + '0';
    c1 = ((n2 >> 8) & 0xf) + '0';
    c2 = ((n2 >> 4) & 0xf) + '0';
    c3 = (n2 & 0xf) + '0';
    c0 <= '9' ? putch(c0) : putch(c0 - '0' - 10 + 'a');
    c1 <= '9' ? putch(c1) : putch(c1 - '0' - 10 + 'a');
    c2 <= '9' ? putch(c2) : putch(c2 - '0' - 10 + 'a');
    c3 <= '9' ? putch(c3) : putch(c3 - '0' - 10 + 'a');
    putch('\n');
    if ((p - output_buf) > (MAX_BUFSIZE >> 1))
        flush(); // 清空缓冲区
}