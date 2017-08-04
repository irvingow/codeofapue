#include "apue.h"
#include <sys/resource.h>
#include <signal.h>
#define BUFFSIZE 100

void sig_xfsz(int signo)
{
    printf("SIG_XFSZ caught\n");

}

/* In my test, I didn't catch signal SIGXFSZ, I felt puzzled.
 * But we will see that the last write function will write 24
 * bytes and return, if we try again, we will get file too 
 * large error */
int main(void)
{
    int n, writeBytes;
    char buf[BUFFSIZE];
    struct rlimit rlp;

    rlp.rlim_cur = 1024;
    rlp.rlim_max = 1024;
    if(setrlimit(RLIMIT_FSIZE, &rlp) < 0)
        err_sys("setrlimit error");

    signal_intr(SIGXFSZ, sig_xfsz);
    while((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0)
    {
        if((writeBytes = write(STDOUT_FILENO, buf, n)) != n)
        {
            fprintf(stderr, "wrote %d bytes\n", writeBytes);
            writeBytes = write(STDOUT_FILENO, buf + writeBytes, n - writeBytes);
			err_sys("write error");
        }
    }
    if(n < 0)
        err_sys("read error");

    exit(0);
}
