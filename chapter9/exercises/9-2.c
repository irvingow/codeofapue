#include "apue.h"


static void pr_ids(char *name)
{
	printf("%s: pid = %ld, ppid = %ld,pgrp = %ld,tpgrp = %ld\n",name,
			(long) getpid(),(long) getppid(),(long) getpgrp(),(long) tcgetpgrp(STDIN_FILENO));
	fflush(stdout);
}


int main(void)
{
	pid_t pid;

	pr_ids("parent");
	if((pid = fork()) < 0)
		err_sys("fork error");
	else if(pid == 0)
	{
		pr_ids("child");
		if((pid = setsid()) < 0)
			err_sys("setsid error");
		/* we will find pgrp equals to pid, it proves that child becomes process group leader,
		 * and we will see tpgrp is -1, it proves that child process nolonger has a controlling
		 * terminal because -1 imply us no process is controlling stdout.
		 * */
		pr_ids("child");
		exit(0);
	}
	else 
		exit(0);
}
