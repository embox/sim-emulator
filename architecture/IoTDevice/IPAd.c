// IPAd.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#define PORT 4433
#define HOST "127.0.0.1"

void init_openssl() {
    SSL_load_error_strings();
    OpenSSL_add_ssl_algorithms();
}

void cleanup_openssl() {
    EVP_cleanup();
}

SSL_CTX *create_context() {
    const SSL_METHOD *method;
    SSL_CTX *ctx;

    method = SSLv23_client_method();

    ctx = SSL_CTX_new(method);
    if (!ctx) {
        perror("Unable to create SSL context\n");
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }
    else{
        printf("SSL context created from client successfully\n");
    }

    return ctx;
}

int main() {
    int sockfd;
    struct sockaddr_in addr;
    SSL_CTX *ctx;
    SSL *ssl;

    init_openssl();
    ctx = create_context();

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Unable to create socket\n");
        exit(EXIT_FAILURE);
    }
    printf("Socket created succesffuly on client\n");

    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = inet_addr(HOST);

    if (connect(sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("Unable to connect\n");
        exit(EXIT_FAILURE);
    }
    else{
        printf("Client connected successfully\n");
    }

    ssl = SSL_new(ctx);
    SSL_set_fd(ssl, sockfd);

    if (SSL_connect(ssl) <= 0) {
        ERR_print_errors_fp(stderr);
    } else {
        char request[] = "GET / HTTP/1.1\r\nHost: 127.0.0.1\r\n\r\n";
        SSL_write(ssl, request, strlen(request));

        char buf[1024] = {0};
        SSL_read(ssl, buf, sizeof(buf) - 1);

        // Parsing received package from eIM
        printf("\nParsing the received activation code on IPAd from eIM\n\n"); 
        // Delimiter
        const char delim[] = "$";

        // Variables to store each part
        char *AC_Format = NULL;
        char *SM_DP_Address = NULL;
        char *AC_Token = NULL;
        char *SM_DP_OID = NULL;
        char *ConfirmationCodeRequiredFlag = NULL;

        // Tokenize the string and store in respective variables
        char *token = strtok(buf, delim);
        if (token != NULL) {
            AC_Format = token;
            token = strtok(NULL, delim);
        }
        if (token != NULL) {
            SM_DP_Address = token;
            token = strtok(NULL, delim);
        }
        if (token != NULL) {
            AC_Token = token;
            token = strtok(NULL, delim);
        }
        if (token != NULL) {
            SM_DP_OID = token;
            token = strtok(NULL, delim);
        }
        if (token != NULL) {
            ConfirmationCodeRequiredFlag = token;
        }

        // Print the results to verify
        printf("AC_Format: %s\n", AC_Format);
        printf("SM-DP+ Address: %s\n", SM_DP_Address);
        printf("AC_Token: %s\n", AC_Token);
        printf("SM-DP+ OID: %s\n", SM_DP_OID);
        printf("Confirmation Code Required Flag: %s\n", ConfirmationCodeRequiredFlag);

    }

    SSL_shutdown(ssl);
    SSL_free(ssl);
    close(sockfd);
    SSL_CTX_free(ctx);
    cleanup_openssl();

    return 0;
}
