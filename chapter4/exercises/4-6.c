#include "apue.h"
#include <fcntl.h>

#define BUFSIZE 4096



/* Please notice that the codes can only be tested in linux os.
 * in addition, if you use gcc for compiling, you need to add argument '-D_GNU_SOURCE' to support SEEK_DATA and SEEK_HOLE
 * */
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
	/* in fact, the most important part of the function is four lines of codes below
	 * first, we must set the currentPosition at the start of the DATA block
	 * second, we need to set the offset of the targetfile same as currentPosition to reserve hole in source file 
	 * third, similar to first line, we should set the holePosition at the start of the HOLE block 
	 * last, we need the set the offset to currentPosition because in second line, we change the offset of the source file 
	 *  */
    currentPosition = lseek(sourcefd, 0, SEEK_DATA);
    lseek(targetfd, currentPosition, SEEK_SET);
    holePosition = lseek(sourcefd, currentPosition, SEEK_HOLE);
    lseek(sourcefd, currentPosition, SEEK_SET);
	/* copyFlag is used to signify whether copying data has completed or not */
    int copyFlag = 1;
    int numToCopy = 0;
    char buf[BUFSIZE];
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
            if(read(sourcefd, buf, numToCopy) != numToCopy)
                err_sys("read error");
            if(write(targetfd, buf, numToCopy) != numToCopy)
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
