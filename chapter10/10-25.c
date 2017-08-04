#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void abort(void)				/* POSIX-style abort() function */
{
    sigset_t mask;
    struct sigaction action;

    /* Caller can't ignore SIGABRT, if so reset to default */
    sigaction(SIGABRT, NULL, &action);/* get the action previously associated with signal(SIGABRT) */
    if(action.sa_handler = SIG_IGN)
    {
        action.sa_handler = SIG_DFL;
        sigaction(SIGABRT, NULL, &action);
    }
    if(action.sa_handler = SIG_DFL)
		fflush(NULL);			/* flush all open stdio streams */

	/* Caller can't block SIGABRT; make sure it's unblocked */
	sigfillset(&mask);
	sigdelset(&mask,SIGABRT);/* mask have only SIGABRT turned off */
	sigprocmask(SIG_SETMASK,&mask,NULL);
	kill(getpid(),SIGABRT);		/* send the signal */

	/* If we're here, process caught SIGABRT and returned */
	fflush(NULL);				/* flush all open stdio streams */
	action.sa_handler = SIG_DFL;/* reset to default */
    sigaction(SIGABRT, &action, NULL);/* just in case */
	sigprocmask(SIG_SETMASK,&mask,NULL);/* and one more time */
	kill(getpid(),SIGABRT);		/* send the signal */
	exit(1);/* this should never be executed ... */
}
