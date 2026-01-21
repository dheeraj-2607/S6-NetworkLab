#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define MAX 800
#define PORT 4050
#define SA struct sockaddr

int main()
{
    int sockfd;
    struct sockaddr_in servaddr;
    char buffer[MAX];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socket creation failed");
        exit(1);
    }
    printf("Socket successfully created..\n");

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);

    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
        perror("connection with server failed");
        exit(1);
    }
    printf("Connected to the server..\n");

    printf("Enter a string:\n");
    fgets(buffer, MAX, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';

    write(sockfd, buffer, strlen(buffer) + 1);

    int n = read(sockfd, buffer, MAX-1);
    if (n <= 0) {
        perror("Read failed");
        close(sockfd);
        return 1;
    }

    buffer[n] = '\0';
    printf("From Server : %s\n", buffer);

    close(sockfd);
    return 0;
}
