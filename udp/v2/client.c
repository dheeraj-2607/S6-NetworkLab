// Client side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
	
#define PORT	 8000
#define MAX 1024

void func(int sockfd)
{
    char buff[MAX];
    int cnt = 0;
    int n,c;
    for (;;) {
        bzero(buff, sizeof(buff));
        n = 0;
        while ((buff[n++] = getchar()) != '\n');
        buff[n-1] = '\0';  // Replace newline with null terminator

        printf("sending : %s \n",buff);
        write(sockfd, buff, sizeof(buff));

        if ((strncmp(buff, "exit", 4)) == 0) 
        {
            printf("Client Exit...\n");
            break;
        }

        bzero(buff, sizeof(buff));
        read(sockfd, buff, sizeof(buff));
        buff[MAX-1] = '\0';  // Ensure null termination
        printf("From Server  : %s \n", buff);
                
    }
}
	
// Driver code
int main() {
	int sockfd;
	char buffer[MAX];
    char message[MAX];
    struct sockaddr_in	 servaddr;
	
	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
	
	memset(&servaddr, 0, sizeof(servaddr));
		
	// Filling server information
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = INADDR_ANY;
    printf("Enter message: ");
    fgets(message, MAX, stdin);
		
	int n, len;
		
	sendto(sockfd, message, strlen(message), 0,
           (struct sockaddr *)&servaddr, sizeof(servaddr));
	len = sizeof(servaddr);
	n = recvfrom(sockfd, buffer, MAX, 0,
                     (struct sockaddr *)&servaddr, &len);
    if (n < 0) {
        perror("Receive failed");
        close(sockfd);
        return 1;
    }
	buffer[n] = '\0';
	printf("Server : %s\n", buffer);
	
	close(sockfd);
	return 0;
}
