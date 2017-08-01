#include "apue.h"
#include <dirent.h>
#include <fcntl.h>

int main(void)
{
	int flag, fd;

	DIR *dir;
	if((dir= opendir("/")) == NULL)
		err_sys("opendir error");
	if((flag = fcntl(dirfd(dir),F_GETFD)) == -1)
		err_sys("fcntl error");
	/* result will be 1 */
	printf("FD_CLOEXEC is %d\n",flag & FD_CLOEXEC);/* FD_CLOEXEC causes the descriptor to be closed if you use any of exec... functions */

	if((fd = open("/",O_RDONLY)) == -1)
		err_sys("open error");
	if((flag = fcntl(fd,F_GETFD)) == -1)
		err_sys("fcntl error");
	/* result will be 0 */
	printf("FD_CLOEXEC is %d\n",flag & FD_CLOEXEC);

	exit(0);
}
