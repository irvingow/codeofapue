#include <signal.h>
#include <unistd.h>

/* incomplete implement of 'sleep' and has three problems */
static void sig_alrm(int signo)
{
	/* nothing to do, just return to wake up the pause */
}


unsigned int sleep1(unsigned int seconds)
{
	struct sigaction newact, oldact;
	sigset_t newmask, oldmask, susmask;
	unsigned int unslept;

	/* set our handler, save previous information */
	newact.sa_handler = sig_alrm;
	sigemptyset(&newact.sa_mask);
	newact.sa_flags = 0;
	sigaction(SIGALRM,&newact,&oldact);

	/* block SIGALRM and save current signal mask */
	sigemptyset(&newmask);
	sigaddset(&newmask,SIGALRM);
	sigprocmask(SIG_BLOCK, &newmask, &oldmask);

	alarm(seconds);		/* start the timer */
	susmask = oldmask;

	/* make sure SIGALRM isn't blocked */
	sigdelset(&susmask,SIGALRM);

	/* wait for any signal to be caught */
	sigsuspend(&susmask);

	/* some signal has been caught, SIGALRM is now blocked */

	unslept = alarm(0);

	/* reset previous action */
	sigaction(SIGALRM,&oldact,NULL);

	/* reset signal mask, which unblocks SIGALRM */
	sigprocmask(SIG_SETMASK,&oldmask,NULL);
	return alarm(0);	/* turn off timer, return unslept time */
}
