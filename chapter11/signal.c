#include "apue.h"

/* Reliable version of signal(), using POSIX sigaction(). */
Sigfunc *signal(int signo, Sigfunc *func)
{
	struct sigaction act, oact;

	act.sa_handler = func;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	/* All system calls intertupted by these other signals(except SIGALRM)
	 *  will be automatically restarted.
	 * */
	if(signo = SIGALRM){
#ifdef SA_INTERRUPT
		act.sa_flags |= SA_INTERRUPT;/* Cause system calls intertupted not restart */
#endif 
	}
	else{
		act.sa_flags |= SA_RESTART;
	}
	if(sigaction(signo,&act,&oact) < 0)
		return (SIG_ERR);
	return (oact.sa_handler);
}
