#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>


int main() {
  
  
  struct sockaddr_in server_addr, client_addr ; 
  
  
  int sockfd  , clientfd ; 
  if ((sockfd = socket(AF_INET , SOCK_STREAM , 0)) < 0) {
    perror("Error connecting socket\n"); 
    exit(1); 
  }
  
  
  server_addr.sin_family = AF_INET ; 
  server_addr.sin_port = htons(5000); 
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  
  
  if((bind(sockfd , (struct sockaddr* ) &server_addr , sizeof(server_addr))) < 0 ) {
    perror("Unable to bind the connection \n" ); 
    exit(1); 
  }
    
  if ((listen(sockfd , 3)) < 0 ) {
    perror("Unable to listen\n");
    exit(1);
    
  }
  
  socklen_t client_addr_len = sizeof(client_addr);
  if((clientfd = accept(sockfd , (struct sockaddr* ) &client_addr , &client_addr_len)) < 0) {
    perror("Unable to accept \n"); 
    exit(1);
  }
  
  char buffer[1024]; 
  
  if((recv(clientfd , buffer , sizeof(buffer)-1 , 0 )) < 0) {
    perror("Error receiving content from client");
    exit(1);
  }
  
  
  printf("String from client: %s\n", buffer);
  char command[5] , filename[50] , content[1024];
  sscanf(buffer , "%s %s", command , filename );  
  if (strcmp(command  , "GET" ) == 0) {
    FILE* fptr = fopen(filename , "r"); 
    while(fgets( content , sizeof(content) , fptr)) {
      send(clientfd, content , strlen(content) , 0 );
    
    }
    fclose(fptr); 
    printf("Successfully send data to client"); 
  }
  else if (strcmp(command , "PUT" ) == 0 ) {
    FILE *fp = fopen(filename , "w"); 
  	while((recv(clientfd , content , sizeof(content) , 0 )) > 0) {
                
  		fputs(content, fp); 
  		
  	}
  	
  	fclose(fp); 
        printf("File successfully uploaded to server!\n"); 
  } 
  

  return 0 ; 
}