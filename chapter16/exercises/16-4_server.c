#include "apue.h"
#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define MYPORT 4321
#define QUEUE_LEN 10
#define BUFLEN 256

extern int initserver(int, const struct sockaddr *, socklen_t , int);
int get_num_proc();

int main(void)
{
    struct sockaddr_in myaddr, client;
    int serverfd, clientfd;
    char buf[BUFLEN];
    
    myaddr.sin_family = AF_INET;
    myaddr.sin_addr.s_addr = INADDR_ANY;
    myaddr.sin_port = htons(MYPORT);

    if((serverfd = initserver(SOCK_STREAM,(struct sockaddr *) &myaddr,sizeof(myaddr),QUEUE_LEN)) < 0)
        err_sys("initserver error");

    socklen_t clen = (socklen_t) sizeof(client);
    while((clientfd = accept(serverfd,(struct sockaddr *)&client,&clen)) != -1)
    {
        //we store the result in buf, and send it to clientfd.
        if(get_num_proc(&buf,BUFLEN) == -1)
            err_sys("get_num_proc error");
        if(send(clientfd,buf,strlen(buf) + 1,0) != strlen(buf) + 1)
            err_sys("send error");
    }
    return 0;
}

/* 'wc -l' print the newline counts. Another ex:
 * if we use 'ls -l | wc -l', this command will 
 * return the numbers of objects in the current
 * dictonary. It uses the 'ls' command to produce 
 * a single-column listing of the dictonary contents,
 * which outputs one line per objects; this output 
 * is piped to wc, which counts the lines(-l), 
 * and returns that number.
 * */
int get_num_proc(char *buf, int len)
{
    FILE *fp;

    if((fp = popen("ps aux | wc -l","r")) == NULL)
        return -1;

    if(fgets(buf,len,fp))
        err_sys("fgets error");
    pclose(fp);
    return 0;
}
