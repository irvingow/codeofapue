#include "apue.h"

#define BUFSIZE 1000000000
char buf[BUFSIZE];

void sig_alrm(int signo)
{
	printf("SIGALRM caught");
}

/* The os will blocks the signals from getting the process 
 * until the 'fwrite' completes. Notice this is really what 
 * happens rather than alarm firing before 'fwrite' is called.
 * */
int main(void)
{
	FILE *fp;
	signal(SIGALRM,sig_alrm);
	if((fp = fopen("temp.txt","wb+")) == NULL)
		err_sys("fopen error");

	alarm(1);/* alarm time should be shorter than how long fwrite takes */

	int writeBytes = fwrite(buf,1,BUFSIZE,fp);

	if(writeBytes <= 0)
		err_sys("fwrite error");
	printf("we write %d bytes\n",writeBytes);
	exit(0);
}
