#include "apue.h"
#include <sys/socket.h>

#define MAXSLEEP 128

int connect_retry(int domain, int type, int protocol, const struct sockaddr *addr, socklen_t alen)
{
    int numsec, fd;

    /*
     * Try to connect with exponential backoff.
     * */
    for(numsec = 1; numsec <= MAXSLEEP; numsec <<= 1)
    {
        /* every time we fail to connect to server, we will close 
         * the old socketfd and in next circle we will create a new 
         * socketfd. */
        if((fd = socket(domain, type, protocol)) < 0)
            return (-1);
        if(connect(fd, addr, alen) == 0)
        {
            /*
             * Connection accepted.
             * */
            return (fd);
        }
        close(fd);

        /*
         * Delay before trying again.
         * */
        if(numsec <= MAXSLEEP/2)
            sleep(numsec);
    }
    return -1;
}
