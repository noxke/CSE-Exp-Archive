#include <stdio.h>
#include <string.h>
#include <openssl/bn.h>

// 检查e p q是否安全
int check(BIGNUM *e_bn, BIGNUM *p_bn, BIGNUM *q_bn, BIGNUM *m_bn);

// 求最大公因数
int gcd(BIGNUM *r, BIGNUM *a, BIGNUM *b);

// 求模逆
int mod_inverse(BIGNUM *r1, BIGNUM *r0, BIGNUM *e, BIGNUM *m, int status);

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        char e_str[1024];
        char p_str[1024];
        char q_str[1024];
        scanf("%s %s %s", e_str, p_str, q_str);
        // 初始化大数
        BIGNUM *e_bn = BN_new();
        BIGNUM *p_bn = BN_new();
        BIGNUM *q_bn = BN_new();
        BIGNUM *m_bn = BN_new();
        BIGNUM *d_bn = BN_new();
        BIGNUM *tmp = BN_new();
        BN_CTX *ctx;
        ctx = BN_CTX_new();
        // 将输入数据转换为大数
        BN_dec2bn(&e_bn, e_str);
        BN_dec2bn(&p_bn, p_str);
        BN_dec2bn(&q_bn, q_str);
        // n = (p - 1)(q - 1)
        BN_sub_word(p_bn, 1);
        BN_sub_word(q_bn, 1);
        BN_mul(m_bn, p_bn, q_bn, ctx);
        BN_add_word(p_bn, 1);
        BN_add_word(q_bn, 1);
        if (check(e_bn, p_bn, q_bn, m_bn) == 1)
        {
            // 求逆 (ed)%m=1
            mod_inverse(d_bn, tmp, e_bn, m_bn, 0);
            puts(BN_bn2dec(d_bn));
        }
        else
        {
            puts("ERROR");
        }
        // 释放大数所占内存
        BN_free(e_bn);
        BN_free(p_bn);
        BN_free(q_bn);
        BN_free(m_bn);
        BN_free(d_bn);
        BN_free(tmp);
        BN_CTX_free(ctx);
    }
    return 0;
}

int check(BIGNUM *e, BIGNUM *p, BIGNUM *q, BIGNUM *m)
{
    BIGNUM *tmp1 = BN_new();
    BIGNUM *tmp2 = BN_new();
    BN_CTX *ctx;
    ctx = BN_CTX_new();
    // 判断p，q是否是素数
    if ((BN_is_prime_ex(p, BN_prime_checks, NULL, NULL) == 0) || (BN_is_prime_ex(q, BN_prime_checks, NULL, NULL) == 0))
    {
        return 0;
    }
    // 模m太小
    if (BN_num_bits(m) < 1000)
    {
        return 0;
    }
    // e太小
    if (BN_num_bits(e) < 16)
    {
        return 0;
    }
    // 判断m和e互素
    gcd(tmp1, m, e);
    if (BN_is_one(tmp1) == 0)
    {
        BN_free(tmp1);
        return 0;
    }
    // p-q的位数需要满足一定条件
    BN_sub(tmp1, p, q);
    BN_mul(tmp2, p, q, ctx);
    int p_q = BN_num_bits(tmp1);
    int pq = BN_num_bits(tmp2);
    if ((p_q < (pq / 2 - 100)) || (p_q < pq / 3))
    {
        return 0;
    }
    // p-1 q-1最大公因数应该小于20
    BN_sub_word(p, 1);
    BN_sub_word(q, 1);
    gcd(tmp1, p, q);
    if (BN_get_word(tmp1) > 20)
    {
        return 0;
    }
    BN_add_word(p, 1);
    BN_add_word(q, 1);
    BN_free(tmp1);
    BN_free(tmp2);
    BN_CTX_free(ctx);
    // 安全性符合
    return 1;
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

int gcd(BIGNUM *r, BIGNUM *a, BIGNUM *b)
{
    if (BN_is_zero(b) == 1)
    {
        BN_copy(r, a);
        return 0;
    }
    BN_CTX *ctx;
    ctx = BN_CTX_new();
    BIGNUM *rem = BN_new();
    BN_mod(rem, a, b, ctx); // tmp = a mod b
    gcd(r, b, rem);         // gcd(b, a % b);
    BN_free(rem);
    BN_CTX_free(ctx);
    return 1;
}