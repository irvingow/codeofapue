#include "apue.h"
/* #include <sys/wait.h> */
/*
 * if you invoke 'wait', you will need this header file
 * */
#ifdef SOLARIS 
#define PSCMD "ps -a -o pid,ppid,s,tty,comm"
#else
#define PSCMD "ps -o pid,ppid,state,s,tty,command"
#endif

/* Reason why zombie appears is we generate a child process by 'fork' but 
 * we don't reap it at all. So if you invoke 'wait', then zombie will not 
 * be generated.
 * */
int main(void)
{
	pid_t pid;

	if((pid = fork()) < 0)
		err_sys("fork error");
	else if(pid == 0)		/* child */
		exit(0);

	/* parent */
	/*if(wait(NULL) != pid)
	 *    err_sys("wait error");*/
	sleep(4);
	system(PSCMD);

	exit(0);
}
