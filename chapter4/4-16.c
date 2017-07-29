#include "apue.h"
#include <fcntl.h>

int main(void)
{
	if(open("tempfile",O_RDWR) < 0)
	    err_sys("open error");
	if(unlink("a")<0)
		err_sys("unlink error");
	printf("file unlinked");
	sleep(15);
	printf("done!\n");
	exit(0);
}
