#include "apue.h"

int globvar = 6;					/* external variable in initialized data */

int main(void)
{
	int var;				/* automatic variable on the stack */
	pid_t pid;

	var = 88;
	printf("before fork\n");		/* we don't flush stdout */
	if((pid = fork()) < 0)
		err_sys("fork error");
	else if(pid == 0){				/* child */
		globvar++;					/* modify variables */
		var++;
		_exit(0);					/* child terminates */
	}
	/* parent continues here */
	printf("pid = %ld, glob = %d, var = %d\n",(long)getpid(),globvar,var);
	exit(0);
}
