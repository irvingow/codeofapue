#include "apue.h"
#include <fcntl.h>

#define BUFSIZE 4096

int main(int argc, char **argv)
{
    if(argc != 3)
    {
        err_sys("usage: %s <src file> <des file>", argv[0]);
    }
    struct stat filestat;
    int sourcefd, targetfd;

    if((sourcefd = open(argv[1], O_RDONLY) ) < 0)
        err_sys("open source file error");
    if((targetfd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC)) < 0)
        err_sys("open target file error");

    off_t currentPosition = 0, holePosition = 0;
    currentPosition = lseek(sourcefd, 0, SEEK_DATA);
    lseek(targetfd, currentPosition, SEEK_SET);
    holePosition = lseek(sourcefd, currentPosition, SEEK_HOLE);
    lseek(sourcefd, currentPosition, SEEK_SET);
    int copyFlag = 1;
    int numToCopy = 0;
    char buf[BUFSIZE];
    int temp;
    while(currentPosition < holePosition)
    {
        if(copyFlag)
        {
            numToCopy = holePosition - currentPosition ;
            if(numToCopy > BUFSIZE)
            {
                numToCopy = BUFSIZE;
            }
            else
            {
                copyFlag = 0;
            }
            if((temp = read(sourcefd, buf, numToCopy)) != numToCopy)
                err_sys("read error");
            if((temp = write(targetfd, buf, numToCopy)) != numToCopy)
                err_sys("read error");
            currentPosition += numToCopy;
        }
        else
        {
            copyFlag = 1;
        }
        currentPosition = lseek(sourcefd, currentPosition, SEEK_DATA);
        holePosition = lseek(sourcefd, currentPosition, SEEK_HOLE);
        lseek(targetfd, currentPosition, SEEK_SET);
        lseek(sourcefd, currentPosition, SEEK_SET);

    }
    exit(0);
}
