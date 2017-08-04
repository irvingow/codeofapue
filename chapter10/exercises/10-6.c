#include "apue.h"

FILE *fp;

void writeFile(const char *);
#define NUM 100
int counter = 1;

/* Note: this program has an implicit deadlock,if we set NUM to an even number,
 * parent process will never exit, because parent is blocked at WAIT_CHILD,
 * while child process has exited. In this program, we can easily avoid this
 * problem but it should be a warning to us.
 * */
int main(void)
{
    /* read and write temp.txt, if temp.txt doesn't exist, create it. */
    if((fp = fopen("temp.txt", "wb+")) == NULL)
        err_sys("fopen error");
    if(fprintf(fp, "0\n") == EOF)
        err_sys("fwrite error");
    fflush(fp);/* we must do this because we use 'fprintf' which is full buffered when opening files */
    pid_t pid;
    TELL_WAIT();
    if((pid = fork()) < 0)
        err_sys("fork error");
    else if(pid == 0)
    {
        ++counter;
        while(counter < NUM)
        {
            TELL_WAIT();
            WAIT_PARENT();
            writeFile("child");
            TELL_PARENT(getppid());
        }
        TELL_WAIT();
        WAIT_PARENT();
        TELL_PARENT(getppid());
        exit(0);
    }
    else
    {
        while(counter < NUM)
        {
            TELL_WAIT();
            writeFile("parent");
            TELL_CHILD(pid);
            WAIT_CHILD();
        }
        exit(0);
    }
}

void writeFile(const char *name)
{

    if(fprintf(fp, "%d %s write\n", counter, name) == EOF)
        err_sys("fwrite error");
	fflush(fp);
    counter += 2;
}
