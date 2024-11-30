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

int main()
{
    int n;
    scanf("%d", &n);
    char e_str[4096];
    char m_str[4096];
    char p_str[4096];
    char q_str[4096];
    // 初始化大数
    BIGNUM *e_bn = BN_new();
    BIGNUM *m_bn = BN_new();
    BIGNUM *p_bn = BN_new();
    BIGNUM *q_bn = BN_new();
    BIGNUM *n_bn = BN_new();
    BIGNUM *result_bn = BN_new();
    BN_CTX *ctx;
    ctx = BN_CTX_new();
    for (int i = 0; i < n; i++)
    {

        scanf("%s %s %s %s", e_str, m_str, p_str, q_str);

        // 将输入数据转换为大数
        BN_dec2bn(&e_bn, e_str);
        BN_dec2bn(&m_bn, m_str);
        BN_dec2bn(&p_bn, p_str);
        BN_dec2bn(&q_bn, q_str);

        // n=pq
        BN_mul(n_bn, p_bn, q_bn, ctx);
        // timer_start();
        mod_exp(result_bn, m_bn, e_bn, n_bn, ctx);
        // timer_stop();
        puts(BN_bn2dec(result_bn));
    }
    // 释放大数所占内存
    BN_free(e_bn);
    BN_free(m_bn);
    BN_free(p_bn);
    BN_free(q_bn);
    BN_free(n_bn);
    BN_free(result_bn);
    BN_CTX_free(ctx);
    return 0;
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
    BN_free(m2i);
    BN_MONT_CTX_free(mont);
    return 1;
}
