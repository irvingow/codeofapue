#include "apue.h"
#include <fcntl.h>
#include <sys/mman.h>

#define COPYING (1024*1024*1024)    /* 1 GB */

int main(int argc, char **argv)
{
    int fdin, fout;
    void *src, *dst;
    size_t copysz;
    struct stat sbuf;
    off_t fsz = 0;

    if(argc != 3)
        err_quit("usage: %s <fromfile> <tofile>",argv[0]);

    if((fdin = open(argv[1],O_RDONLY)) < 0)
        err_sys("can't open %s for reading",argv[1]);
    if((fout = open(argv[2],O_RDWR|O_CREAT|O_TRUNC,FILE_MODE)) < 0)
        err_sys("can't create %s for writing",argv[2]);

    if(fstat(fdin,&sbuf) < 0)   /* need size of input file */
        err_sys("fstat error");

    if(ftruncate(fout,sbuf.st_size) < 0)    /* set output file size */
        err_sys("ftruncate error");

    while(fsz < sbuf.st_size)
    {
        if((sbuf.st_size - fsz) > COPYING)
            copysz = COPYING;
        else 
            copysz = sbuf.st_size - fsz;

        if((src = mmap(0,copysz,PROT_READ,MAP_SHARED,fdin,fsz)) == MAP_FAILED)
            err_sys("mmap error for input");
        if((dst = mmap(0,copysz,PROT_READ | PROT_WRITE,MAP_SHARED,fout,fsz)) == MAP_FAILED)
            err_sys("mmap error for output");

        /* We close the input and output file to test whether mappings will be invalid.
         * Obviously, mappings will still be valid and the copy action will succeed.
         *  */
        close(fdin);
        close(fout);

        memcpy(dst,src,copysz);         /* does file copy */
        munmap(src,copysz);
        munmap(dst,copysz);
        fsz += copysz;
    }
    exit(0);
    
}
