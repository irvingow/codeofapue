#include "apue.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUFSIZE 256

int main(int argc, char **argv)
{
    struct sockaddr_in server_addr;
    struct in_addr address;
    int serverfd;
    char buf[BUFSIZE];

    if(argc != 3)
    {
        printf("Usage: %s <address> <port>\n",argv[0]);
        exit(1);
    }
    server_addr.sin_family = AF_INET;
    if(inet_aton(argv[1],&address) != 1)
    {
        fprintf(stderr,"Invalid address format. Use ipv4 dot notation.\n");
        exit(1);
    }
    server_addr.sin_addr.s_addr = address.s_addr;
    server_addr.sin_port = htons(atoi(argv[2]));

    if((serverfd = socket(AF_INET,SOCK_STREAM,0)) < 0)
        err_sys("socket error");

    if(connect(serverfd,(struct sockaddr *)&server_addr,sizeof(server_addr)) == -1)
        err_sys("connect error");

    if(recv(serverfd,buf,BUFSIZE,0) < 0)
        err_sys("recv error");

    close(serverfd);
}
