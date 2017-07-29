#include "apue.h"
/* we need this header file to use macros major and minor. 
 * this header used to be included in <sys/types.h>, but in 
 * some recent releases, it is removed from <sys/types.h>
 * */
#include <sys/sysmacros.h>


#ifdef SOLARIS
#include <sys/mkdev.h>
#endif

int main(int argc, char **argv)
{
	int i;
	struct stat buf;
	for(i = 1; i<argc;++i)
	{
		printf("%s: ",argv[i]);
		if(stat(argv[i],&buf) < 0)
		{
			err_ret("stat error");
			continue;
		}
		printf("dev = %d/%d",major(buf.st_dev),minor(buf.st_dev));
		if(S_ISCHR(buf.st_mode) || S_ISBLK(buf.st_mode))
		{
			printf(" (%s) rdev = %d/%d",(S_ISCHR(buf.st_mode)) ? "character" : "block", major(buf.st_dev),minor(buf.st_dev));
		}
		printf("\n");
	}
	exit(0);
}