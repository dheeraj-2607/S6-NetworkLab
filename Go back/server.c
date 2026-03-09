#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/time.h>

int main(){
    int server,acpt_sock,rel_val,i=-1;
    char msg[50] = "Received frame",read_buff[50],write_buff[50];
    fd_set set;

    struct sockaddr_in serv_addr,other_addr;
    struct timeval timeout;
    socklen_t len;

    server = socket(AF_INET,SOCK_STREAM,0);
    memset(&serv_addr,0,sizeof(serv_addr));
    memset(&other_addr,0,sizeof(other_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(7891);
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    if(bind(server,(struct sockaddr*)&serv_addr,sizeof(serv_addr))==-1){
        printf("Error in binding\n");
        exit(1);
    }
    printf("-------Sender of Go back N where N=8-------\n");
    listen(server,5);
    len = sizeof(other_addr);
    acpt_sock = accept(server,(struct sockaddr*)&other_addr,&len);
    zero:
    i=i+1;
    strcpy(write_buff,msg);
    write_buff[strlen(msg)] = i + '0';
    printf("To receive -> Frame %d\n",i);
    write(acpt_sock,write_buff,strlen(write_buff));
    i = i + 1;
    sleep(1);
    one:
    strcpy(write_buff,msg);
    write_buff[strlen(msg)] = i + '0';
    printf("To receive -> Frame %d\n",i);
    write(acpt_sock,write_buff,strlen(write_buff));
    FD_ZERO(&set);
    FD_SET(acpt_sock,&set);
    timeout.tv_sec = 2;
    rel_val = select(acpt_sock+1,&set,NULL,NULL,&timeout);
    if(rel_val == -1){
        printf("Error in select\n");
        exit(1);
    }
    else if(rel_val == 0){
        printf("Time out - Packet %d send lost\n",i-1);
        printf("Restart timer Go back n resending packets");
        i=i-2;
        goto zero;
    }
    else{
        read(acpt_sock,read_buff,sizeof(read_buff));
        if((i==6)||(i==4)||(i==1)){
            printf("From Receiver -< %s --CUMULATIVE ACK ----",read_buff);
        }
        else{
            printf("From Receiver <- %s-----INDIVIDUAL ACK----\n",read_buff);

        }
        printf("------------------------------\n");
        i++;
        if((i==5)||(i==3)){
            i--;
            goto zero;
        }
        if(i>7){
            exit(0);
        }
        goto one;
    }
    close(acpt_sock);
    close(server);
    return 0;
}