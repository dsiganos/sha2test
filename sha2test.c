#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>

int sha2(const char *mdname)
{
    EVP_MD_CTX *mdctx;
    const EVP_MD *md;
    char mess1[] = "Test Message\n";
    char mess2[] = "Hello World\n";
    unsigned char md_value[EVP_MAX_MD_SIZE];
    int md_len, i;

    OpenSSL_add_all_digests();

    md = EVP_get_digestbyname(mdname);
    if(!md) {
        printf("Unknown message digest %s\n", mdname);
        return 1;
    }

    mdctx = EVP_MD_CTX_create();
    EVP_DigestInit_ex(mdctx, md, NULL);
    EVP_DigestUpdate(mdctx, mess1, strlen(mess1));
    EVP_DigestUpdate(mdctx, mess2, strlen(mess2));
    EVP_DigestFinal_ex(mdctx, md_value, &md_len);
    EVP_MD_CTX_destroy(mdctx);

    for(i = 0; i < md_len; i++)
        printf("%02x", md_value[i]);
    printf("\n");

    EVP_cleanup();
    return 0;
}

int main(int argc, char *argv[])
{
    return sha2(argv[1]);
}
