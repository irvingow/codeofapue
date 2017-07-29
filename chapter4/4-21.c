#include "apue.h"
#include <fcntl.h>

int main(int argc, char **argv)
{
    int i, fd;
    struct stat statbuf;
    struct timespec times[2];
    for(i = 1; i < argc; i++)
    {
        if(stat(argv[i], &statbuf) < 0)			/* fetch current file */
        {
            err_ret("%s: stat error", argv[i]);
            continue;
        }
		if((fd = open(argv[i],O_RDWR | O_TRUNC)) < 0)	/* truncate */
		{
			err_ret("%s: open error",argv[i]);
			continue;
		}
		times[0] = statbuf.st_atim;				/* last access time */
		times[1] = statbuf.st_mtim;				/* last modified time */
		if(futimens(fd,times) < 0)				/* reset time */
		{
			err_ret("%s: futimens error",argv[i]);
		}
		close(fd);
    }
	exit(0);
}

/*
 * It seems to be some problems when compile the code:
 *		error:'struct stat' has no member named 'st_atim'
 *		error:'struct stat' has no member named 'st_mtim'
 *		warning: implicit declaration of function 'futimens'
 * and I search in google but get no answers.
 * */
