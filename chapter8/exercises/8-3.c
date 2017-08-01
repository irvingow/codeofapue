#include "apue.h"
#include <sys/wait.h>

void pr_info(siginfo_t infop)
{
	switch(infop.si_code)
	{
		case CLD_EXITED:	/* child called '_exit'*/
			printf("normal termination, exit status = %d\n",infop.si_status);
			break;
		case CLD_KILLED:	/* child killed by signal */
			printf("abnormal termination, signal number = %d\n",infop.si_status);
			break;
		case CLD_DUMPED:	/* dump core generated */
			printf("abnormal termination, signal number = %d (core file generated)\n",infop.si_status);
			break;
		default:
			err_quit("Unknown type of infop.si_code %d\n",infop.si_code);
	}
}

int main(void)
{
    pid_t pid;
	siginfo_t infop;
	int status;

    if((pid = fork()) < 0)
    {
        err_sys("fork error");
    }
    else if(pid == 0)			/* child */
    {
        exit(7);
    }

    if(waitid(P_PID,pid,&infop,WEXITED | WSTOPPED ) != 0)	/* wait for child */
        err_sys("wait error");
    pr_info(infop);			/* and print its status */

    if((pid = fork()) < 0)
        err_sys("fork error");
    else if(pid == 0)			/* child */
        abort();				/* generates SIGABRT */

    if(waitid(P_PID,pid,&infop,WEXITED | WSTOPPED ) != 0)	/* wait for child */
        err_sys("wait error");
    pr_info(infop);			/* and print its status */

    if((pid = fork()) < 0)
        err_sys("fork error");
    else if(pid == 0)			/* child */
        status /= 0;			/* divide by 0 generates SIGFPE */

    if(waitid(P_PID,pid,&infop,WEXITED | WSTOPPED ) != 0)	/* wait for child */
        err_sys("wait error");
    pr_info(infop);			/* and print its status */

    exit(0);
}
