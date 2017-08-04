#include "apue.h"
#include <sys/wait.h>

static void sig_cld(int);

/* Problem that described in apue probably not happen in modern Unix systems */
int main(void)
{
	pid_t pid;

	if(signal(SIGCLD,sig_cld) == SIG_ERR)
		perror("signal error");
	if(( pid = fork() ) < 0)
		perror("wait error");
	else if(pid == 0)	/* child */
	{
		sleep(2);
		_exit(0);
	}

	pause();
	exit(0);
}


static void sig_cld(int signo)		/* interrupts pause() */
{
	pid_t pid;
	int status;

	printf("SIGCLD received");

	if(signal(SIGCLD,sig_cld) == SIG_ERR)	/* reestablish handler */
		perror("signal error");

	if((pid = wait(&status)) < 0)			/* fetch child status */
		perror("wait error");

	printf("pid = %d\n",pid);
}
