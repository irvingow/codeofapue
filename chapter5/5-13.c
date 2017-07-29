#include "apue.h"
#include <errno.h>

void make_temp(char *template);

int main(void)
{
	char good_template[] = "/tmp/dirXXXXXX";	/* right way */
	char *bad_template = "/tmp/dirXXXXXX";	/* wrong way */

	printf("trying to create first temp file...\n");
	make_temp(good_template);
	printf("trying to create second temp file...\n");
	/* call 'mkstemp' with argument 'bad_template' will failed 
	 * because we can't change the contents that bad_template 
	 * points to
	 * */
	make_temp(bad_template);
	bad_template[0] = ',';
	printf("bad_template:%s\n",bad_template);
	exit(0);
}


void make_temp(char *template)
{
	int fd;
	struct stat sbuf;

	if((fd = mkstemp(template)) < 0)
		err_sys("can't create temp file");
	printf("temp name = %s\n",template);
	close(fd);
	if(stat(template,&sbuf) < 0)
	{
		if(errno == ENOENT)
			printf("file doesn't exist\n");
		else 
			err_sys("stat failed");
	}
	else 
	{
		printf("file exists\n");
		unlink(template);					/* unlink the flie by ourselves */
	}
}
