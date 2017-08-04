#include "apue.h"

static void sig_int(int);

/* Note: we should use 'signal' function defined by apue in Figure 10-14 instead of system call */
int main(void)
{
	sigset_t newmask, oldmask, waitmask;

	pr_mask("program start: ");

	if(signal(SIGINT,sig_int) == SIG_ERR)
		err_sys("signal(SIGINT) error");
	sigemptyset(&waitmask);/* we need do this every time we want to use a sigset_t */
	sigaddset(&waitmask,SIGUSR1);
	sigemptyset(&newmask);
	sigaddset(&newmask,SIGINT);

	/*
	 * Block SIGINT and save current signal mask.
	 * */
	if(sigprocmask(SIG_BLOCK,&newmask,&oldmask) < 0)
		err_sys("SIG_BLOCK error");

	/*
	 * Critical region of code.
	 * */
	pr_mask("in critical region: ");

	/*
	 * Pause, allowing all signals except SIGUSR1 
	 * */
	if(sigsuspend(&waitmask) != -1)
		err_sys("sigsuspend error");

	pr_mask("after return from sigsuspend: ");

	/*
	 * Reset signal mask which unblocks SIGINT 
	 * */
	if(sigprocmask(SIG_SETMASK,&oldmask,NULL) < 0)
		err_sys("SIG_SETMASK error");

	/*
	 * And continue processing ...
	 * */
	pr_mask("program exit: ");

	exit(0);
}

static void sig_int(int signo)
{
	pr_mask("\nin sig_int: ");
}
