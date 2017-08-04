#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
int system(const char *cmdstring)	/* with appropriate signal handling */
{
	printf("my system call\n");
    pid_t pid;
    int status;
	struct sigaction ignore, saveintr, savequit;
	sigset_t chldmask, savemask;

    if(cmdstring == NULL)
        return (1);					/* always a command processor with UNIX */

	ignore.sa_handler = SIG_IGN;	/* ignore SIGINT and SIGQUIT */
	sigemptyset(&ignore.sa_mask);
	ignore.sa_flags = 0;
	/* before fork(), we ignore SIGINT, SIGQUIT and save the previous action in saveintr and savequit */
	if(sigaction(SIGINT,&ignore,&saveintr) < 0)
		return(-1);
	if(sigaction(SIGQUIT,&ignore,&savequit) < 0)
		return(-1);
	sigemptyset(&chldmask);			/* now block SIGCHLD */
	sigaddset(&chldmask,SIGCHLD);
	if(sigprocmask(SIG_BLOCK,&chldmask,&savemask) < 0)
		return -1;

    if((pid = fork()) < 0)
    {
        status = -1;	/* probably out of processes */
    }
    else if(pid == 0)
    {
		/* restore previous signal actions & reset signal mask */
		sigaction(SIGINT,&saveintr,NULL);
		sigaction(SIGQUIT,&savequit,NULL);
		sigprocmask(SIG_SETMASK,&savemask,NULL);

        execl("/bin/sh", "sh", "-c", cmdstring, (char *)0);
		/* Only when 'execl' failed will '_exit' be called, otherwise child process will execute another program. */
        _exit(127);		/* execl error */
    }
    else
    {
		/* Use status to store return status of child */
        while(waitpid(pid, &status, 0) < 0)
        {
            if(errno != EINTR)
            {
                status = -1;		/* error other than EINTR from waitpid */
                break;
            }
        }
    }

	/* restore previous signal actions & reset signal mask */
	/* before parent get the status of child process, SIGINT and SIGQUIT is ignored and SIGCHLD is blocked */
	if(sigaction(SIGINT,&saveintr,NULL) < 0)
		return(-1);
	if(sigaction(SIGQUIT,&savequit,NULL) < 0)
		return(-1);
	if(sigprocmask(SIG_SETMASK,&savemask,NULL) < 0)
		return -1;

	return(status);
}

