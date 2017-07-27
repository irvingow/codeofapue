#include "apue.h"
#include <errno.h> /* necessary header containing some error variables */

int dupcycle(int oldfd, int newfd);

int mydup2(int oldfd, int newfd)
{
    int fd, maxfd = sysconf(_SC_OPEN_MAX);
    if(oldfd < 0 || oldfd >= maxfd || newfd < 0 || newfd >= maxfd	/* check whether descriptors are valid */
            || (lseek(oldfd, 0, SEEK_CUR) == -1 && errno == EBADF))	/* check whether the oldfd is open */
    {
        errno = EBADF;
        return -1;
    }

    if(oldfd == newfd)		/* if they are sample, we just do nothing but return */
        return newfd;

    /* we invoke the close function to close the newfd without checking whether
     * newfd is closed or open. When newfd is closed, close function will return
     * -1 but it doesn't matter.
     * */
    if(close(newfd) == -1)
        err_sys("close file descriptor error");

    return dupcycle(oldfd, newfd);
}

int dupcycle(int oldfd, int newfd)
{
    int fd = dup(oldfd);
    if(fd == newfd)
        return newfd;
    else
    {
        int fd0 = dupcycle(oldfd, newfd);
        close(fd);			/* notice that this is necessary to avoid opening too many unnecessary fd */
        return fd0;
    }
}
