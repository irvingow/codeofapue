#include "apue.h"
#include <sys/wait.h>

/*
 * In my computer, the result is:
 * > second child, parent pid = 1141
 * We can use 'ps 1141' to see which process does 
 * 1141 signify, it turns out to be '/sbin/upstart', 
 * so I think '/sbin/upstart' take the place of 
 * 'sbin/init' and adopt running processes without
 *  parent.
 * */
int main(void)
{
	pid_t pid;
	if((pid = fork()) < 0)
		err_sys("fork error");
	else if(pid == 0)
	{
		if((pid = fork()) < 0)
			err_sys("fork error");
		else if(pid > 0)
		{
			/*sleep(5);*/
			exit(0);					/* parent from second fork == first child */ 
		}
		/* 
		 * We're the second child; our parent becomes init as soon
		 * as our real parent calls exit() in the statement above.
		 * Here's where we'd continue executing, knowing that when
		 * we're done, init will reap our status.
		 * */
		sleep(5);
		printf("second child, parent pid = %ld\n",(long)getppid());
		exit(0);
	}
	
	/* 
	 * Notice that pid is pid of first child rather than the second child,
	 * after 'fork' pid in child process has no connections with pid in parent 
	 * process.
	 * */
	if(waitpid(pid,NULL,0) != pid)		/* wait for first child */
		err_sys("waitpid error");

	/*
	 * We're the parent (the original process); we continue executing,
	 * knowing that we're not the parent of the second child.
	 * */
	exit(0);
}
