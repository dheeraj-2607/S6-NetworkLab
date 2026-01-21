#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#define MAX 800
#define PORT 8088
#define SA struct sockaddr


void func(int connfd)
{
    char buff[MAX];
    int n,a=0,l;
    char b[MAX]; // copy of the string sent from the client

    // infinite loop for chat
    for (;;) {
        bzero(buff, MAX);
   
        // read the message from client and copy it in buffer
        read(connfd, buff, sizeof(buff));


        // if msg contains "Exit" then server exit and chat ended.
        if (strncmp("exit", buff, 4) == 0) 
        {
            printf("Server Exit...\n");
            break;
        }

        char ch = buff[0]; //Contains the info what operation to perform
        strcpy(b,buff);
        bzero(buff, MAX);
        int i = 0,j = 0;

        for (i = 0; i < strlen(b); i++)
        { 
          buff[i] = b[i]; // updating the buffer with just the string to be processed
        }
        buff[i] = '\0';  // Add null terminator after extracting string
        
        char buffer[MAX];
        if(ch<'7')
        printf("From client: %s \n", buff);
        if(ch=='7'){
           int i=0;
            int j=0,a=0;
        while(buff[i]!='#')
          i++;
          a=i;
          i++;
        while(buff[i]){
          buffer[j]=buff[i];
          i++;
          j++;
        }
        buff[a]=0;
        buffer[j]=0;
        printf("From client: %s and %s\n", buff,buffer);
        }
        write(connfd, buff, strlen(buff)+1);  // Write only the actual string + null terminator

    }
}

int main()
{
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;
   
    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));
   
    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);
   
    // Binding newly created socket to given IP and verification
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
        printf("socket bind failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully binded..\n");
   
    // Now server is ready to listen and verification
    if ((listen(sockfd, 5)) != 0) {
        printf("Listen failed...\n");
        exit(0);
    }
    else
        printf("Server listening..\n");
    len = sizeof(cli);
   
    // Accept the data packet from client and verification
    connfd = accept(sockfd, (SA*)&cli, &len);
    if (connfd < 0) {
        printf("server accept failed...\n");
        exit(0);
    }
    else
        printf("server accept the client...\n");
   
    // Function for chatting between client and server
    func(connfd);
   
    // After chatting close the socket
    close(sockfd);
}