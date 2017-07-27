#include "apue.h"
#include <fcntl.h>

/* testlseek.txt content:
 * abcdefghijklmnopqrstuvwxyz
 * */

int main(void)
{
	int fd;
	if((fd = open("testlseek.txt",O_RDWR | O_APPEND, FILE_MODE)) < 0)
		err_sys("open file error");
	if(lseek(fd, 10, SEEK_SET) < 0)
		err_sys("lseek error");
	char buf[5];
	buf[4] = '\0';
	read(fd,(void *)buf,4);		/* lseek will work for reading and we will get "klmn" after read function invoked */
	printf("buf is %s\n",buf);
	write(fd,buf,4);			/* however, lseek won't work for the reason that we have set O_APPEND when opening the file */
	/*
	 * after write the content of testlseek.txt is:
	 * abcdefghijklmnopqrstuvwxyz
	 * klmn
	 * */
	if(close(fd) < 0)
		err_sys("close fd error");
	exit(0);
}
