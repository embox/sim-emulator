#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#define PORT 4433

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

    method = TLS_server_method(); // Use TLS_server_method for compatibility

    ctx = SSL_CTX_new(method);
    if (!ctx) {
        perror("Unable to create SSL context");
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }

    SSL_CTX_set_min_proto_version(ctx, TLS1_2_VERSION); // Set minimum TLS version to 1.2
    SSL_CTX_set_cipher_list(ctx, "ECDHE-ECDSA-AES256-GCM-SHA384:ECDHE-RSA-AES256-GCM-SHA384"); // Set ciphers

    return ctx;
}

void configure_context(SSL_CTX *ctx) {
    SSL_CTX_use_certificate_file(ctx, "architecture/server.pem", SSL_FILETYPE_PEM);
    SSL_CTX_use_PrivateKey_file(ctx, "architecture/server.key", SSL_FILETYPE_PEM);
}

char* readFile(const char *filename) {
    FILE *file;
    long fileSize;
    char *buffer;

    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s for reading.\n", filename);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    fileSize = ftell(file);
    rewind(file);

    buffer = (char *)malloc((fileSize + 1) * sizeof(char));
    if (buffer == NULL) {
        printf("Error: Memory allocation failed.\n");
        fclose(file);
        return NULL;
    }

    fread(buffer, sizeof(char), fileSize, file);
    buffer[fileSize] = '\0';

    fclose(file);

    return buffer;
}

int main() {
    printf("\nSetting up server for establishing connection\n");

    const char *filename = "architecture/activationCode.txt";
    char *fileContents = readFile(filename);

    if (fileContents == NULL) {
        printf("Please check if activationCode.txt is available\n");
        return EXIT_FAILURE;
    } else {
        printf("\nActivation code file fetched successfully...\n");
    }

    int sockfd, newsockfd;
    struct sockaddr_in addr;
    SSL_CTX *ctx;

    init_openssl();
    ctx = create_context();
    configure_context(ctx);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Unable to create socket");
        exit(EXIT_FAILURE);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("Unable to bind");
        exit(EXIT_FAILURE);
    }

    if (listen(sockfd, 1) < 0) {
        perror("Unable to listen");
        exit(EXIT_FAILURE);
    }

    printf("Listening...\n");

    uint len = sizeof(addr);
    SSL *ssl;

    newsockfd = accept(sockfd, (struct sockaddr*)&addr, &len);
    if (newsockfd < 0) {
        perror("Unable to accept");
        exit(EXIT_FAILURE);
    }

    ssl = SSL_new(ctx);
    SSL_set_fd(ssl, newsockfd);

    if (SSL_accept(ssl) <= 0) {
        ERR_print_errors_fp(stderr);
    } else {
        const char *identifier = "eIM";
        SSL_write(ssl, identifier, strlen(identifier));
        SSL_write(ssl, fileContents, strlen(fileContents));
    }

    SSL_shutdown(ssl);
    SSL_free(ssl);
    close(newsockfd);
    close(sockfd);
    SSL_CTX_free(ctx);
    cleanup_openssl();

    free(fileContents);

    return 0;
}
