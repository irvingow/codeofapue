#include "apue.h"
#include <fcntl.h>
/* test environment: Ubuntu 16.04 x86_64 gcc5.4.0 gdb7.11.1 */

int main(int argc, char **argv)
{
	int val;

	if(argc != 2)
		err_quit("usage: %s <descriptor#>",argv[0]);

	if((val = fcntl(atoi(argv[1]),F_GETFL,0)) < 0)
		err_sys("fcntl error for fd %d",atoi(argv[1]));

	switch(val & O_ACCMODE)
	{
		case O_RDONLY:/* O_RDONLY:0 */
			printf("read only");
			break;
		case O_WRONLY:/* 1 */
			printf("write only");
			break;
		case O_RDWR:/* 2 */
			printf("read write");
			break;
		default:
			err_dump("unknown access mode");
	}
	if(val & O_APPEND)/* O_APPEND:0x400 */
		printf(", append");
	if(val & O_NONBLOCK)/* 0x800 */
		printf(", nonblocking");
	if(val & O_SYNC)/* 0x101000 */
		printf(", synchronous writes");

#if !defined(_POSIX_C_SOURCE) && defined(O_FSYNC) && (O_FSYNC != O_SYNC)
	if(val & O_FSYNC)/* 0x101000 */
		printf(", synchronous writes");
#endif

	putchar('\n');
	exit(0);
}
