#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <openssl/bn.h>

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

// 模平方算法
int mod_exp(BIGNUM *r, BIGNUM *m, BIGNUM *e, BIGNUM *n, BN_CTX *ctx);

// 求模逆
int mod_inverse(BIGNUM *r1, BIGNUM *r0, BIGNUM *e, BIGNUM *m, int status);

int main()
{
    int n;
    char p_str[4096];
    char q_str[4096];
    char e_str[4096];
    scanf("%d", &n);
    scanf("%s %s %s", p_str, q_str, e_str);
    // 初始化大数
    BIGNUM *p_bn = BN_new();
    BIGNUM *q_bn = BN_new();
    BIGNUM *e_bn = BN_new();
    BIGNUM *d_bn = BN_new();
    BIGNUM *n_bn = BN_new();
    BIGNUM *result_bn = BN_new();
    BIGNUM *tmp1 = BN_new();
    BIGNUM *tmp2 = BN_new();
    BIGNUM *tmp3 = BN_new();
    BIGNUM *tmp4 = BN_new();
    BN_CTX *ctx;
    ctx = BN_CTX_new();
    // 将输入数据转换为大数
    BN_dec2bn(&p_bn, p_str);
    BN_dec2bn(&q_bn, q_str);
    BN_dec2bn(&e_bn, e_str);
    // n=pq
    BN_mul(n_bn, p_bn, q_bn, ctx);
    // tmp1 = (p - 1) * (q - 1)
    BN_sub_word(p_bn, 1);
    BN_sub_word(q_bn, 1);
    BN_mul(tmp1, p_bn, q_bn, ctx);
    BN_add_word(p_bn, 1);
    BN_add_word(q_bn, 1);
    // 求e关于模tmp1的逆d
    mod_inverse(d_bn, tmp2, e_bn, tmp1, 0);

    for (int i = 0; i < n; i++)
    {
        char c_str[4096];
        BIGNUM *c_bn = BN_new();
        scanf("%s", c_str);
        BN_dec2bn(&c_bn, c_str);
        
        mod_exp(tmp1, c_bn, d_bn, p_bn, ctx);
        mod_exp(tmp2, c_bn, d_bn, q_bn, ctx);

        // 中国剩余定理
        // tmp1 * q * inverse(q, p)
        mod_inverse(tmp3, tmp4, q_bn, p_bn, 0);
        BN_mod_mul(tmp1, tmp1, q_bn, n_bn, ctx);
        BN_mod_mul(tmp1, tmp1, tmp3, n_bn, ctx);
        // tmp2 * p * inverse(p, q)
        mod_inverse(tmp3, tmp4, p_bn, q_bn, 0);
        BN_mod_mul(tmp2, tmp2, p_bn, n_bn, ctx);
        BN_mod_mul(tmp2, tmp2, tmp3, n_bn, ctx);
        // 求和
        BN_mod_add(result_bn, tmp1, tmp2, n_bn, ctx);
        // mod_exp(result_bn, c_bn, d_bn, n_bn, ctx);
        puts(BN_bn2dec(result_bn));
        BN_free(c_bn);
    }
    // 释放大数所占内存
    BN_free(p_bn);
    BN_free(q_bn);
    BN_free(e_bn);
    BN_free(d_bn);
    BN_free(n_bn);
    BN_free(result_bn);
    BN_free(tmp1);
    BN_free(tmp2);
    BN_free(tmp3);
    BN_free(tmp4);
    BN_CTX_free(ctx);
    return 0;
}

int mod_inverse(BIGNUM *r1, BIGNUM *r0, BIGNUM *e, BIGNUM *m, int status)
{
    // 使用辗转相除法求逆
    BN_CTX *ctx;
    ctx = BN_CTX_new();
    BIGNUM *rem = BN_new();
    BIGNUM *dv = BN_new();
    BIGNUM *tmp1 = BN_new();
    BIGNUM *tmp2 = BN_new();
    // dv = m / e; rem = m % e;
    BN_div(dv, rem, m, e, ctx);
    if (BN_is_zero(rem) == 1)
    {
        // 余数为0时返回1
        BN_set_word(r0, 0);
        BN_set_word(r1, 1);
        return 0;
    }
    // 递归
    mod_inverse(r1, r0, rem, e, 1);
    BN_mul(tmp1, r1, dv, ctx);
    BN_add(tmp2, r0, tmp1);
    BN_copy(r0, r1);   // r1 = r0 + r1 * dv
    BN_copy(r1, tmp2); // r0 = r1
    // 当e*r1 mod m != 1时，
    if (status == 0)
    {
        BN_mod_mul(tmp1, e, r1, m, ctx);
        if (BN_is_one(tmp1) == 0)
        {
            BN_sub(tmp1, m, r1);
            BN_copy(r1, tmp1);
        }
    }
    BN_free(rem);
    BN_free(dv);
    BN_free(tmp1);
    BN_free(tmp2);
    BN_CTX_free(ctx);
    return 1;
}

int mod_exp(BIGNUM *r, BIGNUM *m, BIGNUM *e, BIGNUM *n, BN_CTX *ctx)
{
    BN_MONT_CTX *mont = BN_MONT_CTX_new();
    BN_MONT_CTX_set(mont, n, ctx);
    // e的字节数
    int bytes = BN_num_bytes(e);
    // unsigned char *e_bin = (unsigned char *)malloc(sizeof(1024));
    unsigned char e_bin[1024];
    BN_bn2bin(e, e_bin);
    int debug_r = BN_get_word(r);
    BN_set_word(r, 1);
    // m的2**i次方
    BIGNUM *m2i = BN_new();
    // ri = ri_1 * (m ** (2 ** i))
    BN_to_montgomery(m2i, m2i, mont, ctx);
    BN_to_montgomery(r, r, mont, ctx);
    BN_to_montgomery(m, m, mont, ctx);
    for (int i = 0; i < bytes; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (i * 8 + j == 0)
            {
                BN_copy(m2i, m);
            }
            else
            {
                BN_mod_mul_montgomery(m2i, m2i, m2i, mont, ctx);
                // BN_mod_mul(m2i, m2i, m2i, n, ctx);
            }
            int ei = (*(e_bin + bytes - 1 - i) >> j) & 1;
            if (ei == 1)
            {
                BN_mod_mul_montgomery(r, r, m2i, mont, ctx);
                // BN_mod_mul(r, r, m2i, n, ctx);
            }
        }
    }
    BN_from_montgomery(r, r, mont, ctx);
    BN_from_montgomery(m, m, mont, ctx);
    BN_free(m2i);
    BN_MONT_CTX_free(mont);
    return 1;
}