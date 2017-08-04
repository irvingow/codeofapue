#include "apue.h"
#include <string.h>
#include <signal.h>

/* It seems to be some warnings on my computer.*/
int sig2str(int signo, char *str)
{
	if(signo < 0 || signo > NSIG)
		return -1;
	strcpy(str,strsignal(signo));
	return 0;
}
