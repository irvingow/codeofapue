#include "apue.h"
#include <fcntl.h>

int main()
{
	int fd;
	if((fd = open("test.txt",O_RDWR | O_CREAT)) < 0)
		err_sys("open error");

	char *buf = "hello cp";
	if(write(fd,buf,strlen(buf))<0)
		err_sys("write error");

	lseek(fd,15000,SEEK_SET);
	if(write(fd,buf,strlen(buf))<0)
		err_sys("write error");
	exit(0);
}
