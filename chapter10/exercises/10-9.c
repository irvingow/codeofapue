#include "apue.h"
#include <errno.h>
#define _GNU_SOURCE
#include <signal.h>


/* sample to pr_mask.c */
void pr_mask(const char *str)
{
    sigset_t sigset;
    int errno_save;

    errno_save = errno;			/* we can be called by signal handlers */
    if(sigprocmask(0, NULL, &sigset) < 0)
        err_ret("sigprocmask error");

    printf("%s", str);
	/* we start from 1 beacuse no signal number is 0 */
	for(int i = 1; i < NSIG;i++)
	{
		if(sigismember(&sigset,i))
			printf("%s ",sys_siglist[i]);
	}

    printf("\n");

    errno = errno_save;			/* restore errno */
}
