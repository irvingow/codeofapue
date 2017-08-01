#include "apue.h"

static void f1(void), f2(void);

int main(void)
{
    f1();
    f2();
    _exit(0);
}

/* I get core dump on my computer, because 'vfork' will generate child process sharing sapce with parent 
 * and child will run before, after child return from 'f1', it called 'f2' and 'f2' overwrites previous
 * stack for 'f1'. Then child zeros out the automatic variable buf, setting 1000 bytes of the stack frame
 * to 0. Child return from 'f2' and call '_exit',but the contents of the stack frame beneath the stack 
 * frame for main has been changed. The parent then resumes after the call to 'vfork' and does a return 
 * from 'f1'. However, the return information is often stored in the stack frame, and that information 
 * has probably been changed by child process. So the parent's behavior is undefined, what will happen
 * depends on your system.
 * */
static void f1(void)
{
	pid_t pid;

	if((pid=vfork()) < 0)
		err_sys("vfork error");
	/* child and parent both return */
}

static void f2(void)
{
	char buf[1000];		/* automatic variables */
	int i;

	for(i = 0; i<sizeof(buf);i++)
		buf[i] = 0;
}
