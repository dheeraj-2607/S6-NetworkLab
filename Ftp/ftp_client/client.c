#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define size 1024

int main() {

	struct sockaddr_in server_addr; 
	
	int sockfd; 
	
	if((sockfd = socket(AF_INET , SOCK_STREAM , 0 )) < 0) {
		
		perror("Unable to create socket\n");
		exit(0); 
	}
	
	
	
	server_addr.sin_family = AF_INET; 
	server_addr.sin_port = htons(5000); 
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	
	
	socklen_t server_addr_len = sizeof(server_addr);
	  if((connect(sockfd , (struct sockaddr * )& server_addr , server_addr_len)) < 0 ) {
	    perror("Error connecting to server!\n");
	    exit(1);
	    
	  }
	char buffer[1024] , command[10] , filename[10]; 
	// Read filename from user
	  printf("Enter command (GET/ PUT filename): ");
	  fgets(buffer ,sizeof(buffer) , stdin);
	  
	  send(sockfd , buffer, sizeof(buffer) , 0); 
	 
	  sscanf(buffer , "%s %s", command , filename);  
	  
	  if(strcmp(command , "GET" ) == 0 )  {
	  
	  	FILE *fp = fopen(filename , "w"); 
	  	while((recv(sockfd , buffer , size , 0 )) > 0) {
	  		fputs(buffer, fp); 
	  		if(strlen(buffer) < size) break;
	  		
	  	}
	  	
	  	fclose(fp); 
	  	printf("FILE download successfully\n");
	  
	  } else if (strcmp(command , "PUT" ) == 0) {
	  	FILE *fp = fopen(filename, "r"); 
	  	if (fp == NULL ) {
	  		printf("FILE NOT FOUND\n");
	  		exit(0);  
	  	} else {
	  		while(fgets(buffer , size ,fp)) {
	  			send(sockfd , buffer , strlen(buffer) , 0 ); 
	  		}
	  		fclose(fp); 
	  		printf("file uploaded successfully\n"); 
	  	
	  	}
	  } else {
	    perror("Provide proper commands such as 'GET' or 'POST'\n");
	    exit(1);
	  }
	  
	  close(sockfd);
	  
	  
	return 0 ; 

}
