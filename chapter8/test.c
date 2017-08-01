#include "apue.h"
#include <sys/wait.h>

char *env_init[] = { "USER=unknown","PATH=/tmp",NULL };

int main(void)
{
	pid_t pid;

	if((pid = fork())<0)
		err_sys("fork error");
	else if(pid == 0)		/* specify pathname, specify environment */
	{
		if(execle("/home/lwj/Documents/program/c/8-17","echoall","myarg1","MY ARG2",(char *)0,env_init) < 0)
			err_sys("execle error");
	}

	if(waitpid(pid,NULL,0) < 0) /* although child process called 'execle', but its pid didn't change, so we can also use 'waitpid'*/
		err_sys("wait error");

	if((pid = fork())<0)
		err_sys("fork error");
	else if(pid == 0)		/* specify pathname, inherit environment */
	{
		if(execlp("/home/lwj/Documents/program/c/8-17","echoall","only 1 arg",(char *)0) < 0)
			err_sys("execle error");
	}
	exit(0);
}
