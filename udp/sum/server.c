// Server side implementation of UDP client-server model
/*#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
	
#define PORT	 5050
#define MAXLINE 1024
// Driver code
int main() {
    int a,b,sum;
	int sockfd;
	char buffer[MAXLINE];
	struct sockaddr_in servaddr, cliaddr;
    int n;

	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
		
	memset(&servaddr, 0, sizeof(servaddr));
	memset(&cliaddr, 0, sizeof(cliaddr));
		
	// Filling server information
	servaddr.sin_family = AF_INET; // IPv4
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(PORT);
		
	// Bind the socket with the server address
	if ( bind(sockfd, (const struct sockaddr *)&servaddr,
			sizeof(servaddr)) < 0 )
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	int len = sizeof(cliaddr); //len is value/result
	
    n = recvfrom(sockfd, buffer, MAXLINE, 0,
                 (struct sockaddr *)&cliaddr, &len);	
    sum = a + b;
    if (n < 0) {
        perror("Receive failed");
        close(sockfd);
        return 1;
    }
	printf("Client : %d %d\n", a, b);
	sendto(sockfd, &sum, sizeof(sum), 0,
           (struct sockaddr *)&cliaddr, len);		
	return 0;
}
*/

// UDP Server - Sum of two integers (without array)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5050

int main() {
    int sockfd;
    int a, b, sum;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len = sizeof(cliaddr);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    /* Receive first number */
    recvfrom(sockfd, &a, sizeof(a), 0,
             (struct sockaddr *)&cliaddr, &len);

    /* Receive second number */
    recvfrom(sockfd, &b, sizeof(b), 0,
             (struct sockaddr *)&cliaddr, &len);

    sum = a + b;

    printf("Client : %d %d\n", a, b);

    /* Send sum back to client */
    sendto(sockfd, &sum, sizeof(sum), 0,
           (struct sockaddr *)&cliaddr, len);

    close(sockfd);
    return 0;
}
