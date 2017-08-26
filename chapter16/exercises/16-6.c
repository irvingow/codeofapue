#include "apue.h"
#include <errno.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#if defined(BSD) || defined(MACOS) || defined(SOLARIS)
#include <sys/filio.h>
#endif

int enable_asyno_io(int sockfd)
{
    if(fcntl(sockfd,F_SETOWN,getpid()) == -1)
        return -1;
    int n = 1;
    if(ioctl(sockfd,FIOASYNC,&n) == -1)
        return -1;
    return 0;
}

int disable_async_io(int sockfd)
{
    int n = 0;/* set this behaviour off */
    if(ioctl(sockfd,FIOASYNC,&n) == -1)
        return -1;
    return 0;
}
