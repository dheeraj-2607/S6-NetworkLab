#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

#define MAX 800
#define PORT 4050
#define SA struct sockaddr

int main()
{
    int sockfd, connfd;
    socklen_t len;
    struct sockaddr_in servaddr, cli;
    char buffer[MAX];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socket creation failed");
        exit(1);
    }
    printf("Socket successfully created..\n");

    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    if (bind(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
        perror("socket bind failed");
        exit(1);
    }
    printf("Socket successfully binded..\n");

    if (listen(sockfd, 5) != 0) {
        perror("Listen failed");
        exit(1);
    }
    printf("Server listening..\n");

    len = sizeof(cli);
    connfd = accept(sockfd, (SA*)&cli, &len);
    if (connfd < 0) {
        perror("server accept failed");
        exit(1);
    }

    printf("Client connected from %s:%d\n",
           inet_ntoa(cli.sin_addr), ntohs(cli.sin_port));

    int n = read(connfd, buffer, MAX-1);
    if (n <= 0) {
        perror("Read failed");
        close(connfd);
        close(sockfd);
        return 1;
    }

    buffer[n] = '\0';
    printf("Client message: %s\n", buffer);

    int l = strlen(buffer);
    for (int i = 0; i < l / 2; i++) {
        char temp = buffer[i];
        buffer[i] = buffer[l - i - 1];
        buffer[l - i - 1] = temp;
    }

    write(connfd, buffer, strlen(buffer) + 1);

    close(connfd);
    close(sockfd);
    return 0;
}
