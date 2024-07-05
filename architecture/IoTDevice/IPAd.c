#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#define PORT 4433
#define HOST "127.0.0.1"
#define BUFFER_SIZE 1024
#define FILENAME "received.txt"

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

    method = TLS_client_method(); // Use TLS_client_method for compatibility
    ctx = SSL_CTX_new(method);
    if (!ctx) {
        perror("Unable to create SSL context\n");
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }

    SSL_CTX_set_min_proto_version(ctx, TLS1_2_VERSION); // Set minimum TLS version to 1.2
    SSL_CTX_set_cipher_list(ctx, "ECDHE-ECDSA-AES256-GCM-SHA384:ECDHE-RSA-AES256-GCM-SHA384"); // Set ciphers

    return ctx;
}

void write_file(SSL *ssl) {
    FILE *fp = fopen(FILENAME, "wb");
    if (fp == NULL) {
        perror("Unable to open file\n");
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];
    int bytes;

    while ((bytes = SSL_read(ssl, buffer, BUFFER_SIZE)) > 0) {
        fwrite(buffer, 1, bytes, fp);
    }

    fclose(fp);
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

    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = inet_addr(HOST);

    if (connect(sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("Unable to connect\n");
        exit(EXIT_FAILURE);
    }

    ssl = SSL_new(ctx);
    SSL_set_fd(ssl, sockfd);

    if (SSL_connect(ssl) <= 0) {
        ERR_print_errors_fp(stderr);
    } else {
        char buffer[BUFFER_SIZE] = {0};
        int bytes;

        // Receive the identifier message
        bytes = SSL_read(ssl, buffer, sizeof(buffer) - 1);
        if (bytes < 0) {
            perror("Error reading identifier\n");
            exit(EXIT_FAILURE);
        }
        buffer[bytes] = '\0';

        if (strcmp(buffer, "eIM") == 0) {
            // Receive and parse the activation code
            bytes = SSL_read(ssl, buffer, sizeof(buffer) - 1);
            if (bytes < 0) {
                perror("Error reading activation code\n");
                exit(EXIT_FAILURE);
            }
            buffer[bytes] = '\0';

            printf("Parsing the received activation code on IPAd from eIM\n\n");
            const char delim[] = "$";

            char *AC_Format = strtok(buffer, delim);
            char *SM_DP_Address = strtok(NULL, delim);
            char *AC_Token = strtok(NULL, delim);
            char *SM_DP_OID = strtok(NULL, delim);
            char *ConfirmationCodeRequiredFlag = strtok(NULL, delim);

            printf("AC_Format: %s\n", AC_Format);
            printf("SM-DP+ Address: %s\n", SM_DP_Address);
            printf("AC_Token: %s\n", AC_Token);
            printf("SM-DP+ OID: %s\n", SM_DP_OID);
            printf("Confirmation Code Required Flag: %s\n", ConfirmationCodeRequiredFlag);
        } else if (strcmp(buffer, "SM-DPPlus") == 0) {
            // Receive the file
            write_file(ssl);
            printf("File received successfully and written to %s.\n", FILENAME);
        } else {
            printf("Unknown identifier: %s\n", buffer);
        }
    }

    SSL_shutdown(ssl);
    SSL_free(ssl);
    close(sockfd);
    SSL_CTX_free(ctx);
    cleanup_openssl();

    return 0;
}
