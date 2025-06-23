#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main() {
    int sock = 0; // file descriptor
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    char message[1024];

    // create an IPv4 TCP socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Socket creation error\n");
        exit(EXIT_FAILURE);
    }

    // setup server address
    serv_addr.sin_family = AF_INET;
    // htons converts a 16-bit number (like a port) from your
    // computer's byte order to network byte order (big-endian)
    serv_addr.sin_port = htons(8080);

    // inet_pton converts human-readable
    // IP address into binary network format
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("Invalid address\n");
        exit(EXIT_FAILURE);
    }

    // connect to server
    // (struct sockaddr *): cast to generic sockaddr pointer
    // &serv_addr: address of our specific struct
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("Connection failed\n");
        exit(EXIT_FAILURE);
    }

    printf("Connected to server. Type messages (Ctrl+C to exit):\n");

    // send/receive loop
    while (1) {
        printf("> ");
        fgets(message, 1024, stdin);

        send(sock, message, strlen(message), 0);
        int bytes_read = read(sock, buffer, 1024);
        printf("Echo: %.*s", bytes_read, buffer);
    }

    close(sock);
    return 0;
}
