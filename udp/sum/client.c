/*#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT	 5050
#define MAX 1024

// Driver code
int main() {
    int a,b,sum;
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
    printf("Enter any two numbers to sum:\n");
    scanf("%d %d",&a,&b);		
	int n, len;
		
	sendto(sockfd, &a, sizeof(a), MAX,
           (struct sockaddr *)&servaddr, sizeof(servaddr));
    sendto(sockfd, &b, sizeof(b), MAX,
           (struct sockaddr *)&servaddr, sizeof(servaddr));
	len = sizeof(servaddr);
	n = recvfrom(sockfd, &sum, sizeof(sum), MAX,
                     (struct sockaddr *)&servaddr, &len);
    if (n < 0) {
        perror("Receive failed");
        close(sockfd);
        return 1;
    }
	printf("Server : %d\n", sum);
	
	close(sockfd);
	return 0;
}
*/
// UDP Client - Sum of two integers (without array)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5050

int main() {
    int sockfd;
    int a, b, sum;
    struct sockaddr_in servaddr;
    socklen_t len = sizeof(servaddr);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("Enter any two numbers to sum:\n");
    scanf("%d %d", &a, &b);

    /* Send first number */
    sendto(sockfd, &a, sizeof(a), 0,
           (struct sockaddr *)&servaddr, len);

    /* Send second number */
    sendto(sockfd, &b, sizeof(b), 0,
           (struct sockaddr *)&servaddr, len);

    /* Receive sum */
    recvfrom(sockfd, &sum, sizeof(sum), 0,
             (struct sockaddr *)&servaddr, &len);

    printf("Server : %d\n", sum);

    close(sockfd);
    return 0;
}
