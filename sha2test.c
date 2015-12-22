#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include <openssl/evp.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int wait_for_connection()
{
    int rc, listening_sock = -1, data_sock = -1;
    struct sockaddr_in sin;

    listening_sock = socket(AF_INET, SOCK_STREAM, 0);

    sin.sin_family = AF_INET;
    sin.sin_port = htons(12345);
    sin.sin_addr.s_addr = 0;

    rc = bind(listening_sock, (struct sockaddr *) &sin, sizeof(sin));
    if (rc) goto err;

    rc = listen(listening_sock, 1);
    if (rc) goto err;

    data_sock = accept(listening_sock, NULL, NULL);
    if (rc) goto err;

    close(listening_sock);
    return data_sock;

err:
    printf("ERROR: %s\n", strerror(errno));
    if (listening_sock >= 0) close(listening_sock);
    if (data_sock >= 0) close(data_sock);
    return -1;
}

int sha2()
{
    EVP_MD_CTX *mdctx;
    const EVP_MD *md;
    unsigned char md_value[EVP_MAX_MD_SIZE];
    int md_len, i;
    char buf[2000];
    int sock, rc;
    char mdname[7] = {0};

    OpenSSL_add_all_digests();

    sock = wait_for_connection();
    if (sock < 0) return 1;

    // read the first 6 bytes that should be one of sha224, sha256, sha384, sha512,
    // for this test, it is ok to assume that they will arrive together
    rc = read(sock, mdname, 6);
    if (rc != 6) {
        printf("failed to read the first 6 bytes\n");
        return 1;
    }

    md = EVP_get_digestbyname(mdname);
    if(!md) {
        printf("Unknown message digest %s\n", mdname);
        return 1;
    }

    mdctx = EVP_MD_CTX_create();
    EVP_DigestInit_ex(mdctx, md, NULL);

    for (;;) {
        rc = read(sock, buf, sizeof(buf));
        if (rc == 0) {
            break;
        }
        if (rc < 0) {
            printf("read error\n");
            return 1;
        }
        EVP_DigestUpdate(mdctx, buf, rc);
    }

    EVP_DigestFinal_ex(mdctx, md_value, &md_len);
    EVP_MD_CTX_destroy(mdctx);
    EVP_cleanup();

    rc = write(sock, md_value, md_len);
    if (rc != md_len) return 1;

    close(sock);
    return 0;
}

int main(int argc, char *argv[])
{
    return sha2();
}
