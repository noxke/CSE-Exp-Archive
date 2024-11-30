#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <openssl/pkcs7.h>
#include <openssl/x509.h>
#include <openssl/x509_vfy.h>
#include <openssl/objects.h>
#include <openssl/pem.h>
#include <openssl/err.h>

const char cacert[] = "\
-----BEGIN CERTIFICATE----- \n\
MIIB/zCCAaagAwIBAgIJAKKa0PAt9M1FMAoGCCqBHM9VAYN1MFsxCzAJBgNVBAYT \n\
AkNOMQ4wDAYDVQQIDAVIdUJlaTEOMAwGA1UEBwwFV3VIYW4xDTALBgNVBAoMBEhV \n\
U1QxDDAKBgNVBAsMA0NTRTEPMA0GA1UEAwwGY2Fyb290MB4XDTIwMDkyMDIwNTkx \n\
OVoXDTMwMDkxODIwNTkxOVowWzELMAkGA1UEBhMCQ04xDjAMBgNVBAgMBUh1QmVp \n\
MQ4wDAYDVQQHDAVXdUhhbjENMAsGA1UECgwESFVTVDEMMAoGA1UECwwDQ1NFMQ8w \n\
DQYDVQQDDAZjYXJvb3QwWTATBgcqhkjOPQIBBggqgRzPVQGCLQNCAASJ8mm28JJR \n\
bZKLr6DCo1+KWimpKEsiTfZM19Zi5ao7Au6YLosyN71256MWmjwkwXxJeLa0lCfm \n\
kF/YWCX6qGQ0o1MwUTAdBgNVHQ4EFgQUAL5hW3RUzqvsiTzIc1gUHeK5uzQwHwYD \n\
VR0jBBgwFoAUAL5hW3RUzqvsiTzIc1gUHeK5uzQwDwYDVR0TAQH/BAUwAwEB/zAK \n\
BggqgRzPVQGDdQNHADBEAiAaZMmvE5zzXHx/TBgdUhjtpRH3Jpd6OZ+SOAfMtKxD \n\
LAIgdKq/v2Jkmn37Y9U8FHYDfFqk5I0qlQOAmuvbVUi3yvM= \n\
-----END CERTIFICATE----- \n\
";

const char privkey[] = "\
-----BEGIN EC PARAMETERS----- \n\
BggqgRzPVQGCLQ== \n\
-----END EC PARAMETERS----- \n\
-----BEGIN EC PRIVATE KEY----- \n\
MHcCAQEEINQhCKslrI3tKt6cK4Kxkor/LBvM8PSv699Xea7kTXTToAoGCCqBHM9V \n\
AYItoUQDQgAEH7rLLiFASe3SWSsGbxFUtfPY//pXqLvgM6ROyiYhLkPxEulwrTe8 \n\
kv5R8/NA7kSSvcsGIQ9EPWhr6HnCULpklw== \n\
-----END EC PRIVATE KEY----- \n\
";

char pem_buf[4096];
char message_buf[4096];

// 读取证书公钥
X509 *getX509(const char *cert)
{
    BIO *bio;
    bio = BIO_new(BIO_s_mem());
    BIO_puts(bio, cert);
    return PEM_read_bio_X509(bio, NULL, NULL, NULL);
}

// 读取私钥
EVP_PKEY *getpkey(const char *private_key)
{
    BIO *bio_pkey = BIO_new_mem_buf((char *)private_key, strlen(private_key));
    if (bio_pkey == NULL)
        return NULL;
    return PEM_read_bio_PrivateKey(bio_pkey, NULL, NULL, NULL);
}

// 验证和解密pkcs7消息的签名
int verify_and_decrypt(PKCS7 *p7, X509 *ca_cert, EVP_PKEY *private_key)
{
    if (PKCS7_type_is_signedAndEnveloped(p7) != 1)
    {
        // 未签名
        return 0;
    }

    // 解密部分
    BIO *p7bio = PKCS7_dataDecode(p7, private_key, NULL, NULL);
    if (!p7bio)
    {
        BIO_free(p7bio);
        return 0;
    }
    else
    {
        int len = BIO_read(p7bio, message_buf, 4096);
        message_buf[len] = '\0';
    }

    // 添加ca证书
    X509_STORE *cert_store = X509_STORE_new();
    X509_STORE_add_cert(cert_store, ca_cert);
    // 初始化store_ctx
    X509_STORE_CTX *store_ctx = X509_STORE_CTX_new();

    // 检查数字签名
    STACK_OF(PKCS7_SIGNER_INFO) *signer_info = PKCS7_get_signer_info(p7);
    int n = sk_PKCS7_SIGNER_INFO_num(signer_info);
    PKCS7_SIGNER_INFO *si;
    // 检查每一个签名者的证书
    for (int i = 0; i < n; i++)
    {
        si = sk_PKCS7_SIGNER_INFO_value(signer_info, i);
        if (!PKCS7_dataVerify(cert_store, store_ctx, p7bio, p7, si))
        // if (!PKCS7_signatureVerify(p7bio, p7, si, ca_cert, 0))
        {
            // 校验不通过
            X509_STORE_free(cert_store);
            X509_STORE_CTX_free(store_ctx);
            BIO_free(p7bio);
            return 0;
        }
    }
    X509_STORE_free(cert_store);
    X509_STORE_CTX_free(store_ctx);
    BIO_free(p7bio);
    return 1;
}

int main()
{
    // 初始化openssl算法
    ERR_load_crypto_strings();
    OpenSSL_add_all_algorithms();
    // 读取签名证书公钥
    X509 *ca_cert = getX509(cacert);

    // 读取用户B私钥
    EVP_PKEY *private_key = getpkey(privkey);

    // 从标准输入读取pem格式pkcs7消息
    int i = 0;
    *(pem_buf + i) = getchar();
    while (*(pem_buf + i) != EOF)
    {
        i++;
        *(pem_buf + i) = getchar();
    }
    // 读取pkcs7消息
    BIO *bio = BIO_new_mem_buf(pem_buf, 4096);
    PKCS7 *p7 = PEM_read_bio_PKCS7(bio, NULL, NULL, NULL);
    BIO_free(bio);
    // PKCS7语法错误
    if (p7 == NULL)
    {
        printf("ERROR\n");
        X509_free(ca_cert);
        EVP_PKEY_free(private_key);
        PKCS7_free(p7);
        return 0;
    }

    // 验证签名和解密
    if (verify_and_decrypt(p7, ca_cert, private_key) == 0)
    {
        printf("ERROR\n");
        X509_free(ca_cert);
        EVP_PKEY_free(private_key);
        PKCS7_free(p7);
        return 0;
    }
    // 检验解密数据是否可打印
    int len = strlen(message_buf);
    for (int i = 0; i < len; i++)
    {
        if (!isprint(message_buf[i]))
        {
            printf("ERROR\n");
            X509_free(ca_cert);
            EVP_PKEY_free(private_key);
            PKCS7_free(p7);
            return 0;
        }
    }
    printf("%s", message_buf);
    X509_free(ca_cert);
    EVP_PKEY_free(private_key);
    PKCS7_free(p7);
    return 0;
}