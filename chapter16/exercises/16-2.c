#include "apue.h"
#include <sys/socket.h>

void print_stat_info(struct stat statbuf);

int main(void)
{
    int sd;
    struct stat stabuf;

    if((sd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
    {
        err_sys("socket error");
        return -1;
    }
    if(fstat(sd, &stabuf) < 0)
    {
        err_sys("fstat error");
        return -1;
    }
    print_stat_info(stabuf);
}

void print_stat_info(struct stat buf)
{
    printf("ID of device containing file: %lld\n",       (long long)buf.st_dev);
    printf("inode number: %lld\n",                       (long long)buf.st_ino);
    printf("protection: %o\n",                           (unsigned int)buf.st_mode);
    printf("number of hard links: %lld\n",               (long long)buf.st_nlink);
    printf("user ID of owner: %lld\n",                   (long long)buf.st_uid);
    printf("group ID of owner: %lld\n",                  (long long)buf.st_gid);
    printf("device ID (if special file): %lld\n",        (long long)buf.st_rdev);
    printf("total size, in bytes: %lld\n",               (long long)buf.st_size);
    printf("blocksize for filesystem I/O: %lld\n",       (long long)buf.st_blksize);
    printf("number of 512B blocks allocated %lld\n",     (long long)buf.st_blocks);
}
